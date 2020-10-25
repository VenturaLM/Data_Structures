#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "pattern.hpp"

Pattern::Pattern(const size_t dim, const int class_label):
    valarray_(dim), class_label_(class_label)
{
}

Pattern::Pattern(const float values[], const size_t dim, const int class_label):
valarray_(values, dim), class_label_(class_label)
{
    assert(dim>0);
}

Pattern::Pattern(const Pattern& other):
valarray_(other.valarray_), class_label_(other.class_label_)
{
}

Pattern::~Pattern()
{
}

size_t Pattern::dim() const
{
    return valarray_.size();
}

int Pattern::class_label() const
{
    return class_label_;
}

float Pattern::operator [](const size_t idx) const
{
    assert((0 <= idx) && (idx < dim()));
    return valarray_[idx];
}

float Pattern::sum() const
{
    return valarray_.sum();
}

float Pattern::max() const
{
	return valarray_.max();
}

float Pattern::min() const
{
    return valarray_.min();
}

void Pattern::set_class_label(const int new_label)
{
    class_label_ = new_label;
}

void Pattern::set_dim(size_t new_dim)
{
    valarray_.resize(new_dim);
}

void Pattern::set_value(const size_t i, const float new_v)
{
    assert(0<=i && i<dim());

    valarray_[i] = new_v;
}

void Pattern::set_values(const float values[])
{
   	for (int i = 0; i < dim(); i++)
   	{
   		valarray_[i] = values[i];
   	}
}

Pattern& Pattern::operator += (const Pattern& o)
{
    assert(o.dim()==dim());

    this->valarray_ = this->valarray_ + o.valarray_;

	return *this;
}

Pattern& Pattern::operator -= (const Pattern& o)
{
    assert(o.dim()==dim());

    this->valarray_ = this->valarray_ - o.valarray_;

    return *this;
}

Pattern& Pattern::operator *= (const Pattern& o)
{
    assert(o.dim()==dim());

    this->valarray_ = this->valarray_ * o.valarray_;

    return *this;
}

Pattern& Pattern::operator *= (const float c)
{
	for (int i = 0; i < valarray_.size(); i++)
	{
		valarray_[i] = valarray_[i] * c;
	}

    return *this;
}

float
distance(const Pattern& a, const Pattern& b)
{
    size_t n = a.dim();
    float distance = 0.0;
    float minor_distance = 0.0;

    for (int i = 0; i < n; i++)
    {
    	distance = distance + pow(b.operator [](i) - a.operator [](i), 2);
    }
    minor_distance = sqrt(distance);
	
    return minor_distance;
}


std::ostream& operator << (std::ostream& output, const Pattern& p)
{
    output << p.class_label();
    for (size_t i=0; i<p.dim(); ++i)
        output << ' ' << p[i];
    output << std::endl;
    return output;
}

std::istream& operator >> (std::istream& input, Pattern& p)
    noexcept(false)
{
   std::string line;
   std::getline(input, line);
   if (input && line.size()>0)
   {
       std::istringstream _input;
       _input.str(line);
       int class_label;
       std::vector<float> values;
       _input >> class_label;
       float v;

       while(_input>>v)
       {
          if (_input)
              values.push_back(v);
       }

       p.set_dim(values.size());

       if (values.size() != p.dim())
           throw std::runtime_error("Wrong input format.");
       else
       {
           p.set_class_label(class_label);
           p.set_values(&values[0]);
       }
   }
   return input;
}


std::istream&
load_dataset(std::istream& input,
             std::vector<Pattern>& dts) noexcept(false)
{
    if (input)
    {
        size_t size;
        size_t dim;
        input >> size >> dim;
        if (!input)
            throw (std::runtime_error("Error: wrong input format."));
        input.ignore(); //Skips newline.
        dts.resize(size, Pattern(dim));
        for (size_t i = 0; i<size; ++i)
        {
            input >> dts[i];
            if (!input)
                throw (std::runtime_error("Error: wrong input format."));
        }
    }
    return input;
}
