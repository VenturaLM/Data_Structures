#ifndef __ED_Heap_HPP__
#define __ED_Heap_HPP__

#include <cassert>
#include <iostream>
#include <functional>
#include <memory>
#include <algorithm>
#include <new>

/**
 * @brief Implement the Heap ADT.
 * The parameter template Comp must implement the interface:
 *          bool operator()(T const& a, T const& b)
 * to compare two values a, b.
 * For instance, std::less_equal<T> could be used  --> true if a <= b, false otherwise.
 *
 * It is interesting to note that the heap can both manage its own storage as well as
 * use an external storage (a given array).
 *
 * For this, you can use two attributes, i.e., my_storage_ and data_.
 *
 * When the heap is created empty with a capacity of elements, my_storage_ and data_ will
 * point to a new block of data with "capacity" number of elements. Then when the heap variable is destroyed,
 * you must free this memory.
 *
 * When an external storage is used, (i. e. heapify a given vector), my_storage_ is null and data_ points to
 * the first value of the vector. Then when, the heap variable is destroyed,
 * you MUST NOT free the memory (my_storage_ is null) because this memory is owned
 * by other external object.
 *
 * The type std::unique_ptr<> is strongly recommended to use for my_storage_ attribute.
 *
 */
template<class T, class Comp = std::less_equal<T> >
class Heap
{
  public:

  /** @name Life cicle.*/
  /** @{*/

    /**
     * @brief Create an empty Heap with a given capacity.
     * @warning the heap is the owner of the reserved memory.
     * @post is_empty()
     */
    Heap (int capacity=0) : capacity_(capacity), size_(0)
    {
        //TODO
        my_storage_ = std::unique_ptr<T[]> (new T[capacity_]);
        data_ = my_storage_.get();
        //

        assert(is_a_heap());
        assert(is_empty());
    }

    /**
     * @brief Create a Heap from an array of items.
     * @warning The heap is not the responsable of the memory pointed by @arg data.
     * @post is_full()
     */

    /*Este constructor además de inicializar los atributos del heap, debe asegurar
    que el vector se ha convertido en un heap llamando a Heap<T,Comp>::heapify() (el constructor
    puede llamar a cualquier método público, protegido o privado de su clase).
    En resumen, el usuario llama de forma indirecta a heapify cuando crea un heap sobre un vector
    que es lo que necesitamos como paso previo para ordenarlo.*/

    Heap (T* data, size_t size) : capacity_(size), size_(size)
    {        
        //TODO
        my_storage_ = nullptr;

        for(int i = 0; i < size; i++)
        {
          insert(data[i]);
        }
        //

        assert(is_a_heap());
        assert(is_full());
    }

    /** @brief Destroy a Heap.**/
    ~Heap()
    {}

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /** @brief is the list empty?.*/
    bool is_empty () const
    {
        //TODO
        if(size_ == 0)
        {
            return true;
        }else{
			return false;
		}
    }

  /** @brief is the heap full?.*/
    bool is_full () const
    {
        //TODO
        if(size_ == capacity_)
        {
            return true;
        }else{
			return false;
		}
    }

  /** @brief Get the heap size. */
  int size() const
  {
      //TODO
      return size_;
  }

  /** @brief Get the heap capacity. */
  int capacity() const
  {
      //TODO
      return capacity_;
  }

  /** @brief Get the root item.
   * @pre not is_empty();
   */
  T const& top() const
  {
      assert(! is_empty());
      //TODO
      return data_[0];
  }

  /** @brief Get the raw vector with the heap data.*/
  T const* data() const
  {
      //TODO
      return data_;
  }

  /** @}*/

  /** @name Modifiers*/

  /** @{*/

  /** @brief insert a new item.
   * @pre not is_full()
   */
  void insert (T const& new_it)
  {
      assert(! is_full());      
      //TODO
        data_[size_] = new_it;
        size_++;
        shift_up(size_ - 1);
      //
      //assert(is_a_heap());
  }

  /** @brief Remove the root item.
   * @pre not is_empty()
   */
  void remove()
  {
      assert(! is_empty());
      //TODO
      data_[0] = data_[size_-1];
      size_--;
      shift_down(0);
      //
      //assert(is_a_heap());
  }

  /** @}*/
private:

  /** @brief disable copy constructor.*/
  Heap(Heap<T, Comp> const& other);

  /** @brief disable assign operator.*/
  Heap<T, Comp>& operator=(Heap<T, Comp> const& other);

protected:

  /**
   * @brief get the parent of node i
   * @pre i>0
   */
    int parent(int i) const
    {
        //assert(i>0);
        //TODO
        return ((i + 1) / 2) - 1;
    }

  /**
   * @brief get the left child of node i.
   */
  int left(int i) const
  {
      //TODO
      return (i * 2) + 1;
  }

  /**
   * @brief get the right child of node i.
   */
  int right(int i) const
  {
      //TODO
      return (i + 1) * 2;
  }

  /**
   * @brief Check the head invariant for the subtree.
   * @pre 0<=root && root < size()
   */
    bool is_a_heap(int root=0) const
    {      
    //TODO
	    int l, r;

	    for (int i = root; i < size(); ++i)
	    {
	      l = left(i);
	      r = right(i);

	      if(l < size() and !comp_ (data_[i] ,data_[l]))
	        return false;

	      if(r < size() and !comp_ (data_[i] ,data_[r]))
	        return false;
	    }

	    return true;
    }

  /** @brief Shift up a node.*/
    void shift_up(int i)
    {
        //int p = parent(i);

        //if _comp(item(i), item(p)), swap i with p and shift up p.
        //TODO
        if(i>0)
        {
      		int p = parent(i);
      		if(comp_(data_[i] , data_[p]))
      		{
		        T aux_item = data_[i];
		        data_[i] = data_[p];
		        data_[p] = aux_item;
		        shift_up(p);
	      	}
    	}
    }

  /** @brief shift down a node. */
    void shift_down(int i)
    {
        int n = i; //n will have the node to swap with. by default is the root i.

        int l = left(i); //the left child of i.
        int r = right(i); //the right child of i.

        //if l is a valid index and comp_(item(l), item(n) then now n is l
        //TODO
        if(l < size_ && comp_(data_[l], data_[n]) )
        {
            n = l;
        }

        //if r is a valid index and comp_(item(r), item(n) then now n is r
        //TODO
        if(r < size_ && comp_(data_[r], data_[n]))
        {
            n = r;
        }

        //if i != n then invariant is not meet, swap i with n and shift down n.
        //TODO
        if(i != n)
        {
            std::swap(data_[i], data_[n]);
            shift_down(n); //Recursive function
        }
    }

  /** @brief make the subtree starting in root to be a heap.*/
  //void heapify(/*int root=0*/)
  void heapify(T* root)
  {
      //TODO
      //Remember that there are two ways to implement.
      //The best is to use shift downs from the second to last level (|size/2| ... 0)
      shift_down(root);
      //
      assert(is_a_heap());
  }

    Comp comp_; //Functor to compare heap items. comp_(it1, it2)

    //TODO
    std::unique_ptr<T[]> my_storage_;
    T* data_;
    int capacity_;
    int size_;
};


#endif
