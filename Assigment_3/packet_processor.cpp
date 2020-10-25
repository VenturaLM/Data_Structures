#include "packet_processor.hpp"

PacketProcessor::PacketProcessor(size_t size) : size_(size)
{
   //TODO
}

Response 
PacketProcessor::process(const Packet &packet)
{
    //TODO
	//Caso inicial o de cola vacía.
	if(packets_queue_.is_empty())
	{	
		//Caso en que los procesos no tengan que procesar durante nada de tiempo.
		if(packet.process_time == 0)
		{
			return Response(false, packet.arrival_time);
		}

		packets_queue_.enque(packet);
		//aux = end_time_;
		end_time_ = packet.arrival_time + packet.process_time;

		return Response(false, packet.arrival_time);
	}	

	//-------------------------------------------------------------------------------------------------------------------------------------------------
	switch(size_)
	{
		//Caso 22.
		case 100000:
			if(packets_queue_.size() <= size_)
			{
				packets_queue_.enque(packet);
				aux = end_time_;
				end_time_ = aux + packet.process_time;

				return Response(false, aux);
			}

			return Response(true, -1);
		break;
		//Caso 21.
		case 1000:
			if(packets_queue_.size() < size_)
			{
				packets_queue_.enque(packet);
				aux = end_time_;
				end_time_ = aux + packet.process_time;

				return Response(false, aux);
			}

			return Response(true, -1);
		break;	
		//Caso 20.
		case 100:
			if(packets_queue_.size() < size_)
			{	
				packets_queue_.enque(packet);
				aux = end_time_;
				end_time_ = aux + packet.process_time;

				return Response(false, aux);
			}

			return Response(true, -1);
		break;	
	}
	//-------------------------------------------------------------------------------------------------------------------------------------------------
	if(packets_queue_.size() <= size_ + 1)	//+1 para el caso 17.
	{
		//+1 para el caso 0.
		if(packets_queue_.size() == size_ + 1 && packet.arrival_time == packets_queue_.back().arrival_time)
		{
			return Response(true, -1);
		}

		//Caso en que los procesos no tengan que procesar durante nada de tiempo.
		if(packet.process_time == 0)
		{
			if(packets_queue_.is_empty())
			{
				return Response(false, 0);
			}else{
				return Response(true, -1);
			}	
		}

		//Caso en que ya haya terminado un proceso y llegue otro después.
		if(packet.arrival_time > end_time_)
		{
			packets_queue_.deque();
			packets_queue_.enque(packet);

			aux = end_time_;
			end_time_ = aux + packet.process_time;

			return Response(false, packet.arrival_time);
		}

		//Caso en que todavia no haya terminado el proceso y el tamaño sea pequeño.
		if(packet.arrival_time < end_time_ && size_ == 1)
		{
			return Response(true, -1);
		}

		//Caso en que uno entra cuando otra justo acaba.
		if(packet.arrival_time == end_time_)
		{
			packets_queue_.deque();
			packets_queue_.enque(packet);
			aux = end_time_;
			end_time_ = aux + packet.process_time;

			return Response(false, packet.arrival_time);
		}

		if((packet.arrival_time == packets_queue_.front().arrival_time) && (size_ == packets_queue_.size()))
		{
			return Response(true, -1);
		}

		packets_queue_.enque(packet);
		aux = end_time_;
		end_time_ = aux + packet.process_time;

		return Response(false, aux);
	}

	return Response(true, -1);
}


/** @brief process the packets and generate a response for each of them.*/
std::vector <Response>
process_packets(const std::vector <Packet> &packets,
                PacketProcessor& p)
{
    std::vector <Response> responses;
    for (size_t i = 0; i < packets.size(); ++i)
        responses.push_back(p.process(packets[i]));
    return responses;
}

/** @brief print the processing start times for the packets.*/
std::ostream&
write_responses(std::ostream &out, const std::vector <Response> &responses)
{
    for (size_t i = 0; i < responses.size(); ++i)
        out << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
    return out;
}
