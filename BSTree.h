#ifndef BSTree
#define BSTree
#include <iostream>
#include "TreeNode.h"
using namespace std;

template <typename T>
class BSTree
{
public:
	BSTree();
	BSTree(const BSTree & src);	//cpy cstor
	~BSTree();
	bool isEmpty();
	bool search(const T& key, T& found);
	int insert(const T& elem);
	int deleteNode(const T& key, T& deleted);
	void printTree(char order, TreeNode* node);
	T printNode(const TreeNode* node);
	int height();
private:
	TreeNode<T> *root;
};

template <typename T>
BSTree<T>::BSTree()
{
	root = NULL;
}

BSTree<T>::~BSTree()
{
	if(!isEmpty())
	{
		delete root;
	}
}

bool BSTree<T>::isEmpty()
{
	if(root == NULL)
		return 1;
	else
		return 0;
}

template<typename T>
T BSTree<T>::printNode(const TreeNode* node)
{
	return node->data;
}

template<typename T>
void BSTree<T>::printTree(char order, TreeNode* node)
{
	if (order == 'p')
	{
		if(node)
		{
			cout<<printNode(node)<<endl;
			printTree('p',node->leftChild)
			printTree('p',node->rightChild)
		}
	}
	else if (order == 'i')
	{
		if(node)
		{
			printTree('i',node->leftChild)
			cout<<printNode(node)<<endl;
			printTree('i',node->rightChild)
		}
	}
	else if (order == 's')
	{
		if(node)
		{
			printTree('s',node->leftChild)
			printTree('s',node->rightChild)
			cout<<printNode(node)<<endl;
		}
	}
}

template<typename T>
bool BSTree<T>::search(const T& key, T& e)
{
	TreeNode<T> *current = root;
	while(current)
	{
		if (k < current->data)
			current = current->leftChild;
		else if (k > p->data)
			current = current->rightChild;
		else 
		{
			e = current->data;
			return true;
		}
	}
	return false;
}

template<typename T>
int BSTree<T>::insert(const T& elem)
{
	TreeNode<T> *current = root;
	TreeNode<T> *parent = 0;
	while (current)
	{
		parent = current;
		if(elem < current->data) 
			current = current->leftChild;
		else if (elem > current->data)
			current = current->rightChild;
		else
			return 0;
	}
	TreeNode<T> *newnode = new TreeNode<T>(e);
	if (!isEmpty())
	{
		if (e < parent->data)
			parent->leftChild = newnode;
		else
			parent->rightChild = newnode;
	}
	else
		root = newnode;
	return 1;
}






#endif