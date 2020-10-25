//	https://www.techiedelight.com/stack-implementation-using-templates/
//  https://www.includehelp.com/code-snippets/stack-implementation-using-cpp-class-with-push-pop-traverse.aspx
#ifndef __Stack_HPP__
#define __Stack_HPP__

#include <cassert>

/**
 * @brief ADT Stack.
 * Models a Single linked list[T].
 */
template<class T>
class Stack
{
  public:

  /** @name Life cicle.*/
  /** @{*/

  /** @brief Create an empty Stack.
   * @post is_empty()
   */
  Stack ():top_(-1)
  {
      //TODO
  }

  /** @brief Destroy a Stack.**/
  ~Stack()
  {
      //TODO
  }

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /** @brief is the list empty?.*/
  bool is_empty () const
  {
      //TODO
  	if(top_ == -1)
    {
      return true;
    }else{
      return false;
    }
  }

  /** @brief get the top item.
   * @pre not is_empty()
   */
  const T& top() const
  {
      //TODO
    if(!is_empty())
    {
    	return num_[top_];
    }
  }

  /**@}*/

  /** @name Modifiers*/

  /** @{*/

  /** @brief Insert a new item.
   * @post top() == new_it
   */
  void push(const T& new_it)
  {
      //TODO
  	top_++;
    num_[top_] = new_it;
  }

  /** Remove the top item.
   * @pre not is_empty()
   */
  void pop()
  {
      //TODO
  	if(!is_empty())
    {
      top_--;
    }
  }

  /** @} */

private:

  /** @brief Copy constructor.
   * @warning we don't want a copy constructor.
   */
  Stack(const Stack<T>& other)
  {}

  /** @brief Assign operator.
   * @warning we don't want the assign operator.
   */
  Stack<T>& operator=(const Stack<T>& other)
  {
      return *this;
  }

protected:

  //TODO
  int top_;
  //	Probar con punteros inteligentes.
  T num_[100000];
};

#endif
