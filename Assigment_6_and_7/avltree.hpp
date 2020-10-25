#ifndef __ED_AVLTree_HPP__
#define __ED_AVLTree_HPP__

#include <cassert>
#include <exception>
#include <functional>
#include <memory>
#include <iostream>

/** @brief a AVLTree's Node.*/
template <class T>
class AVLTNode
{
public:

    /** @brief Define a shared reference to a AVLTNode.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    typedef std::shared_ptr< AVLTNode<T> > Ref;

    /** @name Life cicle.*/
    /** @{*/

    /** @brief Create a AVLTNode.
     * @post n_children() == 0
     */
    AVLTNode (T const& it=T(), AVLTNode<T>::Ref parent=nullptr, AVLTNode<T>::Ref left=nullptr, AVLTNode<T>::Ref right=nullptr):
        _item(it), parent_(parent), left_(left), right_(right), height_(0)
    {}

    /** @brief Destroy a AVLTNode. **/
    ~AVLTNode()
    {}

    /** @}*/

    /** @name Observers.*/
    /** @{*/

    /** @brief Get the data item.*/
    const T& item() const
    {
        return _item;
    }

    /** @brief Get the node's height.*/
    int height() const
    {
        return height_;
    }

    /** @brief Compute the balance factor of the node.*/
    int balance_factor() const
    {
        //TODO (second send delivery)
      int left_height = 0, right_height = 0;

      if(has_left())
      {
        left_height = left().get()->height() + 1;
      }

      if(has_right())
      {
        right_height = right().get()->height() + 1;
      }

      return right_height - left_height;
    }

    /** @brief Has it a parent?*/
    bool has_parent() const
    {
        return parent_ != nullptr;
    }

    /** @brief get the parent.*/
    const AVLTNode<T>::Ref& parent() const
    {
        return parent_;
    }

    /** @brief get the parent.*/
    AVLTNode<T>::Ref& parent()
    {
        return parent_;
    }

    /** @brief Has it a left child?*/
    bool has_left() const
    {
        return left_ != nullptr;
    }

    /** @brief get the left child.*/
    const AVLTNode<T>::Ref& left() const
    {
        return left_;
    }

    /** @brief get the left child.*/
    AVLTNode<T>::Ref& left()
    {
        return left_;
    }

    /** @brief Has it a right child? */
    bool has_right() const
    {
        return right_ != nullptr;
    }

    /** @brief get the right child.*/
    const AVLTNode<T>::Ref& right() const
    {
        return right_;
    }

    /** @brief get the right child.*/
    AVLTNode<T>::Ref& right()
    {
        return right_;
    }

    /** @}*/

    /** @name Modifiers.*/
    /** @{*/

    /** @brief Set the data item.*/
    void set_item(const T& new_it)
    {
        _item = new_it;
    }

    /** @brief Set the parent.*/
    void set_parent(AVLTNode<T>::Ref const& new_parent)
    {
        parent_ = new_parent;
    }

    /** @brief Remove link to the left child. */
    void remove_parent()
    {
        parent_.reset();
    }

    /** @brief Set the left child.*/
    void set_left(AVLTNode<T>::Ref const& new_child)
    {
        left_ = new_child;
    }

    /** @brief Remove link to the left child. */
    void remove_left()
    {
        left_.reset();
    }

    /** @brief Set the right child.*/
    void set_right(AVLTNode<T>::Ref const& new_child)
    {
        right_ = new_child;
    }

    /** @brief Remove link to the right child. */
    void remove_right()
    {
        right_.reset();
    }

    /** @brief Compute height. */
    void compute_height()
    {
        //TODO (second delivery)
      if(not has_left() && not has_right())
      {
        height_ = 0;
      }else{
        int left_height = 0, right_height = 0;

        if(has_left())
        {
          left_height = left().get()->height() + 1;
        }

        if(has_right())
        {
          right_height = right().get()->height() + 1;
        }

        if(left_height > right_height)
        {
          height_ = left_height;
        }else{
          height_ = right_height;
        }
      }
    }

protected:
    T _item;
    AVLTNode<T>::Ref parent_;
    AVLTNode<T>::Ref left_;
    AVLTNode<T>::Ref right_;
    int height_;
};

/**
 * @brief ADT AVLTree.
 * Models a AVLTree of T.
 */
template<class T>
class AVLTree
{
  public:

  /** @name Life cicle.*/
  /** @{*/

    /** @brief Create an empty AVLTree.
     * @post is_empty()
     */
    AVLTree () : _root(nullptr), current_(nullptr), parent_(nullptr)
    {
        //TODO
    }

    /**
     * @brief Create a AVLTree using a given node as root.
     * @post not is_empty()
     * @post not current_exists()
    */
    AVLTree (typename AVLTNode<T>::Ref& new_root) : _root(new_root), current_(nullptr), parent_(nullptr)
    {
        //TODO
        //
        assert(!is_empty());
        assert(!current_exists());
    }

    /** @brief Destroy a AVLTree.**/
    ~AVLTree()
    {}

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /** @brief is the list empty?.*/
  bool is_empty () const
  {
      //TODO
      return _root == nullptr;
  }

  /** @brief Get the root item.
   * @pre not is_empty();
   */
  T const& item() const
  {
      //TODO
  		//Aqui si uso el get()
      return _root.get()->item();
  }

  /** @brief Is the cursor at a valid position?*/
  bool current_exists() const
  {
      //TODO
      typename AVLTNode<T>::Ref aux = _root;

      if(current_ == nullptr)
      {
        return false;
      }

      while(true)
      {
        if(current_.get()->item() < aux.get()->item())
        {
          if(aux.get()->has_left())
          {
            aux = aux.get()->left();
          }else{
            return false;
          }
        }

        else if(current_.get()->item() > aux.get()->item())
        {
          if(aux.get()->has_right())
          {
            aux = aux.get()->right();
          }else{
            return false;
          }
        }else{
          return true;
        }
      }
  }

  /**
   * @brief Get the current key.
   * @pre current_exists()
   */
  T const& current() const
  {
      //check preconditions.
      assert(current_exists());      
      //TODO
      return current_.get()->item();
  }

  /** @brief Get the root node.*/
  typename AVLTNode<T>::Ref const& root() const
  {
      //TODO
      return _root;
  }

  /** @brief Get the root node.*/
  typename AVLTNode<T>::Ref root()
  {
      //TODO
      return _root;
  }

  /** @brief Has the tree got this key */
  bool has(const T& k) const
  {
      //check invariants.
      assert(is_a_binary_search_subtree(root()));
      assert(is_a_balanced_subtree(root()));

      //TODO

      if(is_empty())
      {
        return false;
      }

      typename AVLTNode<T>::Ref aux = _root;

      while(true)
      {
      	if(k < aux.get()->item())
        {
          if(aux.get()->has_left())
          {
            aux = aux.get()->left();
          }else{
            return false;
          }
        }

        else if(k > aux.get()->item())
        {
          if(aux.get()->has_right())
          {
            aux = aux.get()->right();
          }else{
            return false;
          }
        }else{
          return true;
        }
      }
  }

  /** @}*/

  /** @name Modifiers*/

  /** @{*/

  /** @brief set a new root node.*/
  void set_root(typename AVLTNode<T>::Ref& new_root)
  {
      //TODO
  		_root = new_root;
      //check invariants.
      assert(is_a_binary_search_subtree(root()));
      assert(is_a_balanced_subtree(root()));
  }

  /**
   * @brief Search a key moving the cursor.
   * @post retV implies current()==k
   * @post not retv implies not current_exits()
   */
  bool search(T const& k)
  {
      //check invariants.
      assert(is_a_binary_search_subtree(_root));
      assert(is_a_balanced_subtree(_root));
      bool found = false;

      //TODO
      if(is_empty())
      {
        found = false;
      }else{
        typename AVLTNode<T>::Ref aux = _root;

        while(true)
        {
          if(k < aux.get()->item())
          {
            if(aux.get()->has_left())
            {
              aux = aux.get()->left();
            }else{
              found = false;
              break;
            }
          }

          else if(k > aux.get()->item())
          {
            if(aux.get()->has_right())
            {
              aux = aux.get()->right();
            }else{
              found = false;
              break;
            }
          }else{
            current_ = aux;
            parent_ = current_.get()->parent();
            found = true;
            break;
          }
        }
      }

      //check invariants.
      assert(is_a_binary_search_subtree(_root));
      assert(is_a_balanced_subtree(_root));

      //check postconditions.
      assert(!found || current()==k);
      assert(found || !current_exists());

      return found;
  }

  /**
   * @brief Insert a new key in the tree.
   * @pre not has(k)
   * @post current_exists()
   * @post current()==k
   */
  void insert(T const& k)
  {
      //preconditions.
      assert(! has(k));

      //check invariants.
      assert(is_a_binary_search_subtree(root()));
      assert(is_a_balanced_subtree(root()));

      //TODO
      //First delivery, only the invariant for a Binary Search Tree
      //must be met.
      typename AVLTNode<T>::Ref new_item;

      new_item.reset(new AVLTNode<T>);
      new_item.get()->set_item(k);

      if(_root == nullptr)
      {
        new_item.get()->set_parent(nullptr);
        parent_ = nullptr;
        _root = new_item;
        current_ = new_item;
      }else{
        typename AVLTNode<T>::Ref aux = _root;

        while(true)
        {
          if(k < aux.get()->item())
          {
            if(aux.get()->has_left())
            {
              aux = aux.get()->left();
            }else{
              new_item.get()->set_parent(aux);
              aux.get()->set_left(new_item);
              current_ = new_item;
              parent_ = aux;
              break;
            }
          }

          else if(k > aux.get()->item())
          {
            if(aux.get()->has_right())
            {
              aux = aux.get()->right();
            }else{
              new_item.get()->set_parent(aux);
              aux.get()->set_right(new_item);
              current_ = new_item;
              parent_ = aux;
              break;
            }
          }
        }
      }


      ////////////////////////
      make_balanced();

      //check invariants.
      assert(is_a_binary_search_subtree(root()));
      assert(is_a_balanced_subtree(root()));

      //check postconditions.
      assert(current_exists());
      assert(current()==k);
  }

  /**
   * @brief remove current from the tree.
   * @pre current_exists()
   * @post not current_exists()
   */
  void remove ()
  {
      //check preconditions.
      assert(current_exists());

      // @WARNING Here, we must not check invariants because this function could be called
      // in recursion and then the invariants are not met.

      bool replace_with_subtree = true;
      typename AVLTNode<T>::Ref subtree;


      //TODO: first delivery
      //Check if there is one subtree (may be empty) to replace node to be removed.
      if(current_.get()->has_left() && current_.get()->has_right())
      {
        replace_with_subtree = false;
      }


      ////////

      if (replace_with_subtree)
      {
          //TODO: first delivery
          //Replace the node with the subtree.
        if(current_.get()->has_left())
        {
          if(parent_.get()->left() == current_)
          {
            parent_.get()->set_left(current_.get()->left());
          }else{
            parent_.get()->set_right(current_.get()->left());
          }

          current_.get()->left()->set_parent(parent_);
        }

        else if(current_.get()->has_right())
        {
          if(parent_.get()->left() == current_)
          {
            parent_.get()->set_left(current_.get()->right());
          }else{
            parent_.get()->set_right(current_.get()->right());
          }

          current_.get()->right()->set_parent(parent_);
        }else{
          if(parent_.get()->left() == current_)
          {
            parent_.get()->set_left(nullptr);
          }else{
            parent_.get()->set_right(nullptr);
          }
        }

        current_.reset();
        current_ = nullptr;
          /////////////

          make_balanced();

          //check invariants.
          assert(is_a_binary_search_subtree(root()));
          assert(is_a_balanced_subtree(root()));

          //check postconditions.
          assert(! current_exists());

      }
      else
      {
          //Remove case 3.
          auto tmp = current_;
          find_inorder_sucessor();
          tmp->set_item(current_->item());
          remove();
      }

      // @WARNING Here, we must not check the
      // postconditions and invariants because this function could be called
      // in recursion and then the invariants are not met.
  }

  /** @}*/

private:

  /** @brief desactivate Copy constructor. */
  AVLTree(const AVLTree<T>& other);

  /** @brief desactivate assign operator. */
  AVLTree<T>& operator =(const AVLTree<T>& other);

protected:

  /**
   * @brief Move current to its in order sucessor.
   */
  void find_inorder_sucessor()
  {
      //TODO: first delivery.
      parent_ = current_;
      current_ = current_.get()->right();

      while(current_.get()->has_left())
      {
        parent_ = current_;
        current_ = current_.get()->left();
      }
  }


  /**
   * @brief make a left rotation.
   * @warning it is posible there is none grand parent (==nullptr).
   */
  void rotate_left(typename AVLTNode<T>::Ref& child,
                   typename AVLTNode<T>::Ref& parent,
                   typename AVLTNode<T>::Ref& grand_parent)
  {
      //TODO: second delivery.
      //First update grand parent link.
      //If there is not grand parent, the child will be
      //the new root of the tree.
      if(grand_parent ==nullptr){
        set_root(child);
      }else{
        if(grand_parent.get()->left()==parent)
        {
          grand_parent.get()->set_left(child);
        }else{
          grand_parent.get()->set_right(child);
        }
      }

      //TODO: second delivery.
      //second update child<->parent links.
      parent.get()->set_left(child.get()->right());
      child.get()->set_right(parent);

      //TODO: second delivery.
      //Update heigths for parent, child and grandparent if there is.
      parent.get()->compute_height();
      child.get()->compute_height();

      if(grand_parent != nullptr)
      {
        grand_parent.get()->compute_height();
      }
  }

  /**
   * @brief make a right rotation.
   * @warning it is posible there is none grand parent (==nullptr).
   */
  void rotate_right(typename AVLTNode<T>::Ref& child,
                    typename AVLTNode<T>::Ref& parent,
                    typename AVLTNode<T>::Ref& grand_parent)
  {
      //TODO: second delivery.
      //First update grand parent link.
      //If there is not grand parent, the child will be
      //the new root of the tree.
      if(grand_parent ==nullptr){
        set_root(child);
      }else{
        if(grand_parent.get()->left()==parent)
        {
          grand_parent.get()->set_left(child);
        }else{
          grand_parent.get()->set_right(child);
        }
      }

      //TODO: second delivery.
      //second update child<->parent links.
      parent.get()->set_right(child.get()->left());
      child.get()->set_left(parent);

      //TODO: second delivery.
      //Update heigths for parent, child and grandparent if there is.
      parent.get()->compute_height();
      child.get()->compute_height();

      if(grand_parent != nullptr)
      {
        grand_parent.get()->compute_height();
      }
  }

  /**
   * @brief make a balanced tree.
   */
  void make_balanced()
  {
      while(parent_)
      {
          //TODO: second delivery.
          //First, update parent height.
          parent_->compute_height();

          //TODO: second delivery.
          //Second, check balance factors.
          int bf = parent_->balance_factor();
          if (bf < -1)
          {
              //The subtree is left un-banlaced.
              //Get the grand-parent link.
              auto grand_parent = parent_->parent();
              auto child = parent_->left();

              //Check the left child balanced factor.
              int bf_child = child->balance_factor();

              if (bf_child <= 0)
              {
                  //TODO: second delivery
                  //We have a Case 1.
                  //left-left unbalance.
                  rotate_left(child, parent_, grand_parent);
              }
              else
              {
                  //TODO: second delivery
                  //We have a Case 3.
                  //left-right unbalance
                  grand_parent = parent_;
                  parent_ = child;
                  child = child.get()->right();
                  rotate_right(child, parent_, grand_parent);

                  parent_ = grand_parent;
                  grand_parent = grand_parent.get()->parent();
                  rotate_left(child, parent_, grand_parent);
              }
          }
          else if (bf > 1)
          {              
              //The subtree is right un-balanced.
              //get the grand-parent link.
              auto grand_parent = parent_->parent();
              auto child = parent_->right();

              //Check the child balanced factor.
              int bf_child = child->balance_factor();

              if (bf_child>=0)
              {
                  //TODO: second delivery
                  //We have a Case 2.
                  //right-right unbalanced.
                  rotate_right(child, parent_, grand_parent);
              }
              else
              {
                  //TODO: second delivery
                  //We have a Case 4.
                  //right-left unbalanced.
                  grand_parent = parent_;
                  parent_ = child;
                  child = child.get()->left();
                  rotate_left(child, parent_, grand_parent);

                  parent_ = grand_parent;
                  grand_parent = grand_parent.get()->parent();
                  rotate_right(child, parent_, grand_parent);
              }
          }
          else
          {
              //The subtree is balanced. Go up.
              parent_ = parent_->parent();
          }
      }
  }

  /**
   * @brief Check the binary search tree invariant.
   * @param node is the subtree's root.
   * @return true of the subtree with node as root is a binary search tree.
   */
  bool is_a_binary_search_subtree(typename AVLTNode<T>::Ref const& node) const
  {
      //TODO: first delivery.
      if(node != nullptr)
      {
        if(node.get()->has_left())
        {
          if(node.get()->left().get()->item() < node.get()->item())
          {
            is_a_binary_search_subtree(node.get()->left());
          }else{
            return false;
          }
        }
        else if(node.get()->has_right())
        {
          if(node.get()->right().get()->item() > node.get()->item())
          {
            is_a_binary_search_subtree(node.get()->right());
          }else{
            return false;
          }
        }
      }

      return true;
  }

  /**
   * @brief check the balanced tree invariant.
   * @param node is the subtree's root.
   * @return true if the subtree with node as root is balanced.
   */
  bool is_a_balanced_subtree(typename AVLTNode<T>::Ref const& node) const
  {
      //TODO: second delivery
      return true;
  }

  typename AVLTNode<T>::Ref _root;
  typename AVLTNode<T>::Ref current_;
  typename AVLTNode<T>::Ref parent_;

};


/**  @brief Fold an avl tree node.
 * The output format will be:
 * [<item> : <left> : <right>] or [] if its a empty node.
*/
template<class T>
std::ostream&
fold_AVLTNode (std::ostream& out, typename AVLTNode<T>::Ref const& node)
{
    out << '[';
    if (node != nullptr)
    {
        out << node->item() << " : ";
        fold_AVLTNode<T>(out, node->left());
        out << " : ";
        fold_AVLTNode<T>(out, node->right());
    }
    out << ']';
    return out;
}

/**  @brief Fold an avl tree. */
template<class T>
std::ostream&
operator << ( std::ostream& out, AVLTree<T> const& tree)
{
    fold_AVLTNode<T> (out, tree.root());
    return out;
}

/** @brief Load an AVLTNode from a input stream.
 * @return the node on success.
 * @warning runtime_error will throw if worng input format is found.
 */
template<class T>
std::istream&
operator >> (std::istream& in, typename AVLTNode<T>::Ref& node) noexcept(false)
{
    char sep=' ';
    while(in && sep!='[')
        in >> sep;
    if (!in)
        throw std::runtime_error("Wrong input format.");
    sep = static_cast<char>(in.peek());
    if (sep != ']')
    {
        T item;
        in >> item;
        if (!in)
            throw std::runtime_error("Wrong input format.");
        while(in && sep!=':')
            in >> sep;
        if (!in)
            throw std::runtime_error("Wrong input format.");
        typename AVLTNode<T>::Ref left;
        in >> left;
        if (!in)
            throw std::runtime_error("Wrong input format.");
        while(in && sep!=':')
            in >> sep;
        if (!in)
            throw std::runtime_error("Wrong input format.");
        typename AVLTNode<T>::Ref right;
        in >> right;
        if (!in)
            throw std::runtime_error("Wrong input format.");
        node = std::make_shared< AVLTNode<T> >(item, left, right);
    }
    else
        in >> sep;//remove the close bracket from stream.
    return in;
}

/** @brief Load an avl tree from a input stream.
 * @warning runtime_error will throw if worng input format is found.
 */
template<class T>
std::istream&
operator >> (std::istream& in, AVLTree<T>& tree)
{
    typename AVLTNode<T>::Ref root;
    in >> root;
    if (in)
        tree.set_root(root);
    return in;
}

#endif
