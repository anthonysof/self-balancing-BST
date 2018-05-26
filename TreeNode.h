#ifndef TREE_NODE
#define TREE_NODE

template <typename T>
class BSTree;

template <typename T>
class Tree_Node
{
	friend class BSTree<T>;
private:
	T data;
	Tree_Node* leftChild;
	Tree_Node* rightChild;

public:
	Tree_Node(T);
	~Tree_Node();

};

template <typename T>
Tree_Node<T>::Tree_Node(T dataIn)
{
	data = dataIn;
	leftChild = 0;
	rightChild = 0;
}

template <typename T>
Tree_Node<T>::~Tree_Node()
{
	if (leftChild) delete leftChild;
	if (rightChild) delete rightChild;
}
#endif
