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
	void printTreeStats();
	T getNode(const TreeNode<T>* node);	//done
	int maxHeight(const TreeNode<T>* node);	//done
	TreeNode<T>* getRoot();
	int bstToList(const TreeNode<T>* node, List<T>& li);
	TreeNode<T>* sortedListToBSTrecur(List<T> &li, int count);
	TreeNode<T>* sortedListToBST(List<T>& li, TreeNode<T>* node);
	void treeReconstruction(TreeNode<T>* node, TreeNode<T>* parentNode, char succession);
	//void prettyPrint() bonus challenge
private:
	TreeNode<T> *root;
	int n;
	int d;
	double c;
	double b;
};

template<typename T>
void BSTree<T>::printTreeStats()
{
	std::cout<<"Height of tree is: "<<maxHeight(getRoot())<<std::endl;
	std::cout<<"Number of elements: "<<n<<std::endl;
	std::cout<<"Deletion counter: "<<d<<std::endl;
}

template<typename T>
void BSTree<T>::treeReconstruction(TreeNode<T>* node, TreeNode<T>* parentNode, char succession)
{
	List<T> *li = new List<T>();
	bstToList(node, *li);
	if(node == root){
		root = sortedListToBST(*li, node);
	}
	else{
		if(succession == 'r')
	parentNode->rightChild = sortedListToBST(*li, node);
		else
	parentNode->leftChild = sortedListToBST(*li, node);
}
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
	List<TreeNode<T>*> *li = new List<TreeNode<T>*>();
	int depth = -1;
	while (current)
	{
		parent = current;
		li->insertStart(parent);
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
	std::cout<<"Inserting: "<<elem<<std::endl;
	if (depth > ceil(c*log2(n+1+d)))
	{
		TreeNode<T> *temp;
		TreeNode<T> *papatemp;
		for(int i = 0; i < li->length(); i++)
		{
			li->deleteStart(temp);
			li->deleteStart(papatemp);
			char dir;
			if(temp->data > papatemp->data)
			{
				dir = 'r';
			}
			else
			{
				dir = 'l';
			}
			//std::cout<<"ELA GIWRGHHH "<<var<<std::endl;
			if (maxHeight(temp) > ceil(c*log2(li->length()+1)))
			{
				printTree('p');
				printTreeStats();
				treeReconstruction(temp,papatemp, dir);
				std::cout<<"Reconstructing tree..."<<std::endl;
				printTree('p');
				printTreeStats();

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
	if(isEmpty)
	{
		std::cout<<"Tree is empty..."<<std::endl;
		return 0
	}
	std::cout<<"Deleting "<<key<<"..."<<std::endl;
	TreeNode<T> *current = root;
	TreeNode<T> *parent = 0;
	bool found = false;
			//std::cout<<"PSAXNO PSAXNO"<<std::endl;

	while(current)
	{
		if(current->data == key)
			found = true;
		parent = current;
		if (key < current->data)
			current = current->leftChild;
		else
			current = current->rightChild;
	}
	if(!found)
		std::cout<<key<<" not found."<<std::endl;
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
	if(d >= ceil((pow(2,(b/c))-1)*(n+1)))
	{
		d = 0;
		std::cout<<"Deletion counter limit hit. Reconstructing whole tree..."<<std::endl;
		treeReconstruction(root,root,'l');
		printTreeStats();
	}
	std::cout<<"Deletion Counter: "<<d<<std::endl;
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