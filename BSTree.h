#pragma once
#include <iostream>
#include "TreeNode.h"
#include "List.h"
#include <math.h>


template <typename T>
class BSTree
{
public:
	BSTree(double, double);		//done
	//BSTree(const BSTree & src);	//cpy cstor
	~BSTree();		//SEGFAULTS
	bool isEmpty();		//done
	TreeNode<T> searchTree(const T& key, T& found);	//done
	int insert(const T& elem);	//done
	int deleteNode(const T& key, T& deleted);	//done
	void printTree(char order, TreeNode<T>* node);	//done
	void printTree(char order);
	T getNode(const TreeNode<T>* node);	//done
	int maxHeight(const TreeNode<T>* node);	//done
	TreeNode<T>* getRoot();
	int bstToList(const TreeNode<T>* node, List<T>& li);
	TreeNode<T>* sortedListToBSTrecur(List<T> &li, int count);
	TreeNode<T>* sortedListToBST(List<T>& li, TreeNode<T>* node);
	void treeReconstruction(TreeNode<T>* node);
	//void prettyPrint() bonus challenge
private:
	TreeNode<T> *root;
	int n;
	int d;
	double c;
	double b;
};

template<typename T>
void BSTree<T>::treeReconstruction(TreeNode<T>* node)
{
	List<T> *li = new List<T>();
	bstToList(node, *li);
	root = sortedListToBST(*li, node);
	delete(li);
}

template<typename T>
TreeNode<T>* BSTree<T>::sortedListToBST(List<T> &li, TreeNode<T>* node)
{
	int count = li.length();
	node = sortedListToBSTrecur(li, count);
	return node;
}

template<typename T>
TreeNode<T>* BSTree<T>::sortedListToBSTrecur(List<T> &li, int count)
{
	//count = li.length();
	T deleted;
	if (count <= 0)
		return NULL;
	TreeNode<T> *left = sortedListToBSTrecur(li, count/2);
	TreeNode<T> *temp = new TreeNode<T>(li.getHead().getData() );
	temp->leftChild = left;
	li.deleteStart(deleted);
	temp->rightChild = sortedListToBSTrecur(li, count-count/2-1);
	return temp;
}

template<typename T>
TreeNode<T>* BSTree<T>::getRoot()
{
	return root;
}

template <typename T>
BSTree<T>::BSTree(double cusr, double busr)
{
	root = NULL;
	n = 0;
	d = 0;
	c = cusr;
	b = busr;
}
template<typename T>
BSTree<T>::~BSTree()
{
	if(!isEmpty())
	{
		delete root;
	}
}
template<typename T>
bool BSTree<T>::isEmpty()
{
	if(root == NULL)
		return 1;
	else
		return 0;
}

template<typename T>
T BSTree<T>::getNode(const TreeNode<T>* node)
{
	return node->data;
}

template<typename T>
void BSTree<T>::printTree(char order)
{
	TreeNode<T> *node = root;
	if (order == 'p')
	{
		if(node)
		{
			std::cout<<getNode(node)<<std::endl;
			printTree('p',node->leftChild);
			printTree('p',node->rightChild);
		}
	}
	else if (order == 'i')
	{
		if(node)
		{
			printTree('i',node->leftChild);
			std::cout<<getNode(node)<<std::endl;
			printTree('i',node->rightChild);
		}
	}
	else if (order == 's')
	{
		if(node)
		{
			printTree('s',node->leftChild);
			printTree('s',node->rightChild);
			std::cout<<getNode(node)<<std::endl;
		}
	}
}

template<typename T>
void BSTree<T>::printTree(char order, TreeNode<T>* node)
{
	if (order == 'p')
	{
		if(node)
		{
			std::cout<<getNode(node)<<std::endl;
			printTree('p',node->leftChild);
			printTree('p',node->rightChild);
		}
	}
	else if (order == 'i')
	{
		if(node)
		{
			printTree('i',node->leftChild);
			std::cout<<getNode(node)<<std::endl;
			printTree('i',node->rightChild);
		}
	}
	else if (order == 's')
	{
		if(node)
		{
			printTree('s',node->leftChild);
			printTree('s',node->rightChild);
			std::cout<<getNode(node)<<std::endl;
		}
	}
}

template<typename T>
TreeNode<T> BSTree<T>::searchTree(const T& key, T& e)
{
	int count = -1;
	TreeNode<T> *current = root;
	while(current)
	{
		if (key < current->data)
		{
			current = current->leftChild;
			count++;
		}
		else if (key > current->data)
		{
			current = current->rightChild;
			count++;
		}
		else 
		{
			e = current->data;
			return *current;
		}
	}
	return NULL;
}

template<typename T>
int BSTree<T>::insert(const T& elem)
{
	TreeNode<T> *current = root;
	TreeNode<T> *parent = 0;
	List<T> *li = new List<T>();
	int depth = -1;
	while (current)
	{
		parent = current;
		li->insertStart(parent->data);
		if(elem < current->data) 
		{
			current = current->leftChild;
			depth++;
		}
		else if (elem > current->data)
		{
			current = current->rightChild;
			depth++;
		}
		else
			return -1;
	}
	n++;
	TreeNode<T> *newnode = new TreeNode<T>(elem);
	if (!isEmpty())
	{
		if (elem < parent->data)
			parent->leftChild = newnode;
		else
			parent->rightChild = newnode;
	}
	else
		root = newnode;
	if (depth > ceil(c*log2(n+1+d)))
	{
		TreeNode<T> *temp;
		T var;
		T vor;
		for(int i = 0; i < li->length(); i++)
		{
			li->deleteStart(var);
							
			*temp = searchTree(var, vor);
			std::cout<<"ELA GIWRGHHH "<<var<<std::endl;
			if (maxHeight(temp) > ceil(c*log2(li->length()+1)))
			{
				treeReconstruction(temp);
				std::cout<<"Reconstructing tree..."<<std::endl;
				delete(li);
				break;
			}
		}
	}
	return depth;
}

template<typename T>
int BSTree<T>::deleteNode(const T& key, T& deleted)
{
	TreeNode<T> *current = root;
	TreeNode<T> *parent = 0;
			//std::cout<<"PSAXNO PSAXNO"<<std::endl;

	while(current and current->data != key)
	{
		parent = current;
		if (key < current->data)
			current = current->leftChild;
		else
			current = current->rightChild;
	}
	if(!current)
		return 0;
	deleted = current->data;
	d++;
	
	if(current->leftChild and current->rightChild)
	{
		TreeNode<T> *temp = current->leftChild;
		TreeNode<T> *papatemp = current;
		while (temp->rightChild)
		{
			papatemp = temp;
			temp = temp->rightChild;
		}
		current->data = temp->data;
		current = temp;
		parent = papatemp;
	}
	TreeNode<T> *cemp;
	if(current->leftChild)
		cemp = current->leftChild;
	else
		cemp = current->rightChild;

	if(current == root)
		root = cemp;
	else
	{
		if(current == parent->leftChild)
			parent->leftChild = cemp;
		else
			parent->rightChild = cemp;
	}
	delete current;
	return 1;
}

template<typename T>
int BSTree<T>::maxHeight(const TreeNode<T>* node)
{
	if(!node)
		return 0;
	else
	{
		int lDepth = maxHeight(node->leftChild);
		int rDepth = maxHeight(node->rightChild);
		if(lDepth > rDepth)
			return (lDepth+1);
		else
			return (rDepth+1);
	}
}



template<typename T>
int BSTree<T>::bstToList(const TreeNode<T>* node, List<T>& li)
{
		if(node)
		{
			bstToList(node->leftChild, li);
			li.insertEnd(getNode(node));
			bstToList(node->rightChild, li);
		}
	return 1;
}