#include "trie.hpp"


bool
TrieNode::has(char k) const
{
    //TODO
    return children_.find(k) != children_.end();
}

TrieNode::ref const&
TrieNode::child(char k) const
{
    assert(has(k));
    //TODO
    return children_.find(k)->second;
}

TrieNode::ref
TrieNode::child(char k)
{
    assert(has(k));
    //TODO
    return children_.find(k)->second;
}

std::string const&
TrieNode::value() const
{
    //TODO
    return value_;
}

const std::map<char, TrieNode::ref> &TrieNode::children() const
{
    return children_;
}

void
TrieNode::set_value(std::string const& new_v)
{
    //TODO
    value_ = new_v;
}

void
TrieNode::insert(char k, ref node)
{
    //TODO
    //Insertar en el mapa en la posicion k el valor node.
    children_[k] = node;
}

Trie::Trie()
{
    //DO nothing.
}

bool
Trie::find(std::string const& k) const
{
    auto node = find_node(k);
    //The Trie can have a prefix==k but does not store the key k.
    const bool found = (node != nullptr) && (node->value().size()==k.size());
    assert(!found || node->value()==k);
    return found;
}

std::vector<std::string>
Trie::keys(std::string const& pref) const
{
    std::vector<std::string> keys;
    NodeRef node = find_node(pref);
    if (node != nullptr)
        preorder_traversal(node, keys);
    return keys;
}


void
Trie::insert(std::string const& k)
{
    //TODO
    //    Algorithm Trie::insert(k:String)
    //    Begin
    //      If root_ is Void Then
    //         root_ ← TrieNode::make()
    //      End-If
    //      node ← _root
    //      For i ← 1 to k.size() Inc 1 Do
    //        If node.has(k[i]) Then
    //          node ← node.child(k[i])
    //        Else
    //          newNode ← TrieNode::make()
    //          node.insert(k[i], newNode)
    //          node ← newNode
    //        End-If
    //      End-For
    //      node.setValue(k)
    //    End.

    //aux = nuevo
    if(root() == nullptr)
    {
        NodeRef aux;
        aux.reset(new TrieNode);
        aux->set_value("");
        root_ = aux;
    }

    auto node = root_;

    for (unsigned int i = 0; i < k.size(); i++)
    {
        if(node->has(k[i]))
        {
            node = node->child(k[i]);
        }else{
            NodeRef aux;
            aux.reset(new TrieNode);
            aux->set_value("");
            node->insert(k[i], aux);
            node = aux;
        }
    }
    node->set_value(k);

    assert(find(k));
}

Trie::NodeRef
Trie::find_node(std::string const& pref) const
{
    //TODO
    //    Algorithm Trie::findNode(k:String):TrieNode // O(M)
    //    Begin
    //        node ← root_
    //        i ← 0
    //        While i<k.size() And
    //              node.has(k[i]) Do
    //            node ← node.child(k[i])
    //            i ← i+1
    //        End-While
    //      Return node
    //    End.
    auto node = root_;

    unsigned int i = 0;
    while(i < pref.size() && node->has(pref[i]))
    {
        node = node->child(pref[i]);
        i ++;
    }

    return node;
}

void
Trie::preorder_traversal(NodeRef const& node, std::vector<std::string> & keys) const
{
    //TODO
    //    Algorithm Trie::preorderTraversal(node:TrieNode; var keys:DArray[String]) // O(K)
    //    Begin
    //      If node.value()<>"" Then
    //          keys.pushBack(node.value())
    //      End-If
    if(node->value() != "")
    {
        keys.push_back(node->value());
    }

    //      For child In node.Children() Do
    //          preorderTraversal(child, keys)
    //      End-For
    //    End.
    for (auto i = node->children().begin(); i != node->children().end(); i++)
    {
        preorder_traversal(i->second, keys);
    }
}
