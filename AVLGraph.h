#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iomanip>
#include "GraphNode.h"

template <class T>
class AVLGraph {
    private:
        GraphNode<T> * root = nullptr;
        int indent_increase = 6;
        
        void recursivePrintInOrder (GraphNode<T> * _root);
        void recursivePrintTree (GraphNode<T> * _root, int indent, char branch);
        void recursiveClear (GraphNode<T> * _root);
        GraphNode<T> * recursiveInsert (GraphNode<T> * _root, GraphNode<T> * _node);
        bool recursiveSearch (GraphNode<T> * _root, T _data);
        GraphNode<T> * recursiveRemove (GraphNode<T> * _root, T _data);
        int recursiveCountLeaves (GraphNode<T> * _root);

        // Methods for balancing the tree
        GraphNode<T> * recursiveGetMin (GraphNode<T> * _root);
        int getBalanceFactor (GraphNode<T> * _root);
        void updateHeights (GraphNode<T> * _root);
        GraphNode<T> * balance (GraphNode<T> * _root);
        GraphNode<T> * rotateLeft (GraphNode<T> * _root);
        GraphNode<T> * rotateRight (GraphNode<T> * _root);
    public:
        AVLGraph () {}
        AVLGraph (GraphNode<T> * _node) { root = _node; }
        ~AVLGraph () { clear(); }
        
        void setRoot (GraphNode<T> * _node) { root = _node; }
        GraphNode<T> * getRoot () { return root; }
        void clear  ();
        void insert (T _data);
        void insert (GraphNode<T> * _node);
        bool search (T _data);
        void remove (T _data);
        void printInOrder ();
        void printTree ();
        GraphNode<T> * getMin();
        int countLeaves ();
};

template <class T>
void AVLGraph<T>::printInOrder()
{
    std::cout << "In-order: ";
    recursivePrintInOrder(root);
    std::cout << std::endl;
}

template <class T>
void AVLGraph<T>::recursivePrintInOrder(GraphNode<T> * _root)
{
    if (_root)
    {
        recursivePrintInOrder(_root->getLeft());
        std::cout << _root->getData() << " ";
        recursivePrintInOrder(_root->getRight());
    }
}

template <class T>
void AVLGraph<T>::printTree()
{
    std::cout << "Tree printed vertically:" << std::endl;
    recursivePrintTree(root, indent_increase, '-');
}

template <class T>
void AVLGraph<T>::recursivePrintTree(GraphNode<T> * _root, int indent, char branch)
{
    if (_root)
    {
        recursivePrintTree(_root->getRight(), indent + indent_increase, '/');
        //std::cout << std::setw(indent) << branch << " " << std::setw(4) << _root->getData() << " (" << _root->getHeight() << ")" << std::endl;
        std::cout << std::setfill(' ') << std::setw(indent) << branch << std::setfill('=') << std::setw(4) << _root->getData() << " (" << _root->getHeight() << ")" << std::endl;
        recursivePrintTree(_root->getLeft(), indent + indent_increase, '\\');
    }
}

template <class T>
void AVLGraph<T>::clear()
{
    recursiveClear(root);
    // Set the pointer to null to indicate an empty tree
    root = nullptr;
}

template <class T>
void AVLGraph<T>::recursiveClear(GraphNode<T> * _root)
{
    if (_root == nullptr)
        return;
    // Delete the subtrees first
    recursiveClear(_root->getLeft());
    recursiveClear(_root->getRight());
    // Delete this node
    delete _root;
}

template <class T>
void AVLGraph<T>::insert(T _data)
{
    GraphNode<T> * node = new GraphNode<T> (_data);
    insert(node);
}

template <class T>
void AVLGraph<T>::insert(GraphNode<T> * _node)
{
    if (root == nullptr)
        root = _node;
    else
        root = recursiveInsert(root, _node);
}

template <class T>
GraphNode<T> * AVLGraph<T>::recursiveInsert(GraphNode<T> * _root, GraphNode<T> * _node)
{
    // Do not insert the same data item twice
    if (_root->getData() == _node->getData())
        return _root;
    if (_node->getData() < _root->getData())
    {
        if (_root->getLeft() == nullptr)
            _root->setLeft(_node);
        else
            _root->setLeft(recursiveInsert(_root->getLeft(), _node));
    }
    else if (_node->getData() > _root->getData())
    {
        if (_root->getRight() == nullptr)
            _root->setRight(_node);
        else
            _root->setRight(recursiveInsert(_root->getRight(), _node));
    }
    return balance(_root);
}

template <class T>
bool AVLGraph<T>::search(T _data)
{
    return recursiveSearch(root, _data);
}

template <class T>
bool AVLGraph<T>::recursiveSearch(GraphNode<T> * _root, T _data)
{
    if (_root == nullptr)
        return false;
    if (_data == _root->getData())
        return true;
    if (_data < _root->getData())
        return recursiveSearch(_root->getLeft(), _data);
    else
        return recursiveSearch(_root->getRight(), _data);
}

template <class T>
void AVLGraph<T>::remove(T _data)
{
    root = recursiveRemove(root, _data);
}

template <class T>
GraphNode<T> * AVLGraph<T>::recursiveRemove(GraphNode<T> * _root, T _data)
{
   if (_root == nullptr)
        return nullptr;
    else if (_data < _root->getData())
    {
        _root->setLeft(recursiveRemove(_root->getLeft(), _data));
    }
    else if (_data > _root->getData())
    {
        _root->setRight(recursiveRemove(_root->getRight(), _data));
    }
    else
    {
        // Case 1: Leaf
        if (_root->getLeft() == nullptr && _root->getRight() == nullptr)
        {
            delete _root;
            return nullptr;
        }
        // Case 2: Right child only
        else if (_root->getLeft() == nullptr)
        {
            GraphNode<T> * tmp = _root;
            _root = tmp->getRight();
            delete tmp;
        }
        // Case 3: Left child only
        else if (_root->getRight() == nullptr)
        {
            GraphNode<T> * tmp = _root;
            _root = tmp->getLeft();
            delete tmp;
        }
        // Case 4: Two children
        else
        {
            GraphNode<T> * tmp = recursiveGetMin(_root->getRight());
            _root->setData(tmp->getData());
            _root->setRight(recursiveRemove(_root->getRight(), tmp->getData()));
        }
    }
    return balance(_root);
}

template <class T>
GraphNode<T> * AVLGraph<T>::getMin()
{
    return recursiveGetMin(root);
}

template <class T>
GraphNode<T> * AVLGraph<T>::recursiveGetMin(GraphNode<T> * _root)
{
    if (_root == nullptr)
        return nullptr;
    if (_root->getLeft() == nullptr)
        return _root;
    return recursiveGetMin(_root->getLeft());
}

template <class T>
int AVLGraph<T>::countLeaves()
{
    return recursiveCountLeaves(root);
}

template <class T>
int AVLGraph<T>::recursiveCountLeaves(GraphNode<T> * _root)
{
    if (_root == nullptr)
        return 0;
    if (_root->getLeft() == nullptr && _root->getRight() == nullptr)
        return 1;
    return recursiveCountLeaves(_root->getLeft()) + recursiveCountLeaves(_root->getRight());
}

///// Methods for balancing the tree /////
template <class T>
int AVLGraph<T>::getBalanceFactor (GraphNode<T> * _root)
{
    int left_height = 0;
    int right_height = 0;

    if (_root == nullptr)
        return 0;

    if (_root->getLeft())
        left_height = _root->getLeft()->getHeight();
    if (_root->getRight())
        right_height = _root->getRight()->getHeight();

    return left_height - right_height;
}

template <class T>
void AVLGraph<T>::updateHeights (GraphNode<T> * _root)
{
    int left_height = 0;
    int right_height = 0;

    if (_root->getLeft())
        left_height = _root->getLeft()->getHeight();
    if (_root->getRight())
        right_height = _root->getRight()->getHeight();

    _root->setHeight ( std::max(left_height, right_height) + 1 );
}

template <class T>
GraphNode<T> * AVLGraph<T>::balance (GraphNode<T> * _root)
{
    if (root == nullptr)
        return nullptr;

    updateHeights(_root);
    int balance_factor = getBalanceFactor(_root);

    // Left is heavier
    if (balance_factor > 1)
    {
        // Right sub-branch is heavier
        if (getBalanceFactor(_root->getLeft()) < 0)
        {
            // LR case
            _root->setLeft(rotateLeft(_root->getLeft()));
        }
        // LL case
        _root = rotateRight(_root);
    }
    // Right is heavier
    else if (balance_factor < -1)
    {
        // Right sub-branch is heavier
        if (getBalanceFactor(_root->getRight()) > 0)
        {
            // RL case
            _root->setRight(rotateRight(_root->getRight()));
        }
        // RR case
        _root = rotateLeft(_root);
    }
    return _root;
}

template <class T>
GraphNode<T> * AVLGraph<T>::rotateLeft (GraphNode<T> * _root)
{
    GraphNode<T> * tmp = _root->getRight();
    _root->setRight( tmp->getLeft() );
    tmp->setLeft(_root);
    updateHeights(_root);
    updateHeights(tmp);
    return tmp;
}

template <class T>
GraphNode<T> * AVLGraph<T>::rotateRight (GraphNode<T> * _root)
{
    GraphNode<T> * tmp = _root->getLeft();
    _root->setLeft( tmp->getRight() );
    tmp->setRight(_root);
    updateHeights(_root);
    updateHeights(tmp);
    return tmp;
}

#endif
