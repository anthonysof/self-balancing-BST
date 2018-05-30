#pragma once
template <typename T>
class BSTree;

template <typename T>
class TreeNode
{
	friend class BSTree<T>;
private:
	T data;
	TreeNode* leftChild;
	TreeNode* rightChild;

public:
	TreeNode(T dataIn);
	TreeNode()
	{};
	~TreeNode();
	T getData();

};

template <typename T>
TreeNode<T>::TreeNode(T dataIn)
{
	data = dataIn;
	leftChild = 0;
	rightChild = 0;
}

template <typename T>
TreeNode<T>::~TreeNode()
{
	if (leftChild) delete leftChild;
	if (rightChild) delete rightChild;
}

template <typename T>
T TreeNode<T>::getData()
{
	return data;
}