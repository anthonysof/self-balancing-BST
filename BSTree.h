#pragma once
#include <iostream>
#include "TreeNode.h"
#include "List.h"
#include <math.h>


template <typename T>
class BSTree
{
public:
	BSTree(double, double);		//constructor
	//~BSTree();		//SEGFAULTS
	bool isEmpty();		//bool μέθοδος, επιστρέφει True αν το δένδρο είναι άδειο
	bool searchTree(const T& key, T& found);	//bool, επιστρέφει True αν βρει στο δένδρο το key και το τοποθετεί στο found
	int insert(const T& elem);	//εισάγει στοιχείο στο δένδρο, επιστρέφει 1 άν πέτυχε η εισαγωγή
	TreeNode<T>* deleteNode(const T& key, TreeNode<T>* root, bool &flag); //βοηθητική της παρακάτω για διαγραφή αναδρομικά
	void deleteNode(const T& key); //διαγράφει τον κόμβο με την τιμή key
	TreeNode<T>* minNode(TreeNode<T>* node); //βρίσκει το ελάχιστο στοιχείο ενός υποδένδρου με ρίζα node, χρησιμοποιείται στην διαγραφή
	void printTree(char order, TreeNode<T>* node); //βοηθητική μέθοδος για την παρακάτω για την εκτύπωση με αναδρομικό τρόπο
	void printTree(char order); //εκτυπώνει το δένδρο με ορίσματα 'p': preorder, 'i': inorder, 's':postorder
	void printTreeStats(); //εκτυπώνει διάφορα βοηθητικά στατιστικά όπως αριθμο στοιχείων, διαγραφών, ύψος
	T getNode(const TreeNode<T>* node);	//επιστρέφει τα δεδομένα ενός κόμβου
	int maxHeight(const TreeNode<T>* node);	//υπολογίζει το ύψος ενός υποδένδρου με ριζα node
	TreeNode<T>* getRoot(); //επιστρέφει pointer στην ρίζα του δένδρου
	int bstToList(const TreeNode<T>* node, List<T>& li); //εισάγει ένα δυαδικό δένδρο αναζήτησης στην λίστα li ταξινομημένα
	TreeNode<T>* sortedListToBSTrecur(List<T> &li, int count); //βοηθητική μέθοδος για την παρακάτω
	TreeNode<T>* sortedListToBST(List<T>& li, TreeNode<T>* node); //κατασκευάζει με αναδρομικό τρόπο ένα δυαδικό δένδρο αναζήτησης από ταξινομημένη λίστα με Ο(n)
	void treeReconstruction(TreeNode<T>* node, TreeNode<T>* parentNode, char succession); //ανακατασκευάζει το υποδένδρο με ρίζα node
	//void prettyPrint() bonus challenge
private:
	TreeNode<T> *root;
	int n;	//πλήθος στοιχείων δένδρου
	int d = 0;	//αριθμός διαγραφών
	double c;	//σταθερά c
	double b;	//σταθερά b
};
/* Επιστρέφει αναδρομικά δείκτη στον κόμβο του υποδένδρου με
ρίζα node, με την μικρότερη τιμή, προφανώς σε ΔΔΑ είναι ο κάτω 
αριστερά κόμβος */
template<typename T>
TreeNode<T>* BSTree<T>::minNode(TreeNode<T>* node)
{
	if(node == NULL)
		return NULL;
	else if(node->leftChild == NULL)
		return node;
	else
		return minNode(node->leftChild);
}

/*Κλήση αυτής της μεθόδου με μοναδικό όρισμα την τιμή
του στοιχείου που θέλουμε να διαγράψουμε θα καλέσει την βοηθητική
deleteNode με τα παραπάνω ορίσματα για να γίνει αναδρομικά η διαγραφή
σε αυτό το ΔΔΑ έχει προστεθεί η έξτρα συνθήκη με τον αριθμο διαγραφών
ώστε να γίνεται ανακατασκευή όλου του δένδρου όταν φτάσει το d στην συγκεκριμένη
τιμή*/
template<typename T>
void BSTree<T>::deleteNode(const T& key)
{
	bool flag = true;
	root = deleteNode(key,root,flag);
	if(flag)
	{
		std::cout<<"Deleted: "<<key<<std::endl;
		n--;
		d++;
		if(d >= ceil((pow(2,(b/c))-1)*(n+1)))
		{
			d = 0;
			std::cout<<"Deletion counter limit hit. Reconstructing whole tree..."<<std::endl;
			treeReconstruction(root,root,'l');
			printTreeStats();
		}
	}
	else
	{
		std::cout<<"Deletion failed."<<std::endl;
	}
	
} 

template<typename T>
void BSTree<T>::printTreeStats()
{
	int heightUlt = c*log2(n+1)+b+1;
	std::cout<<"Height of tree is: "<<maxHeight(getRoot())<<std::endl;
	std::cout<<"Number of elements: "<<n<<std::endl;
	std::cout<<"Deletion counter: "<<d<<std::endl;
	std::cout<<"Maximum Height Allowed: "<<heightUlt<<std::endl;
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
/*Constructor τοτ συγκεκριμένου BST
αρχικοποιεί το πλήθος των στοιχείων με 0,
τον αριθμό διαγραφών με 0 και τις τιμές b 
και c σύμφωνα με αυτές που έδωσε ο χρήστης κατα 
την εκτέλεση*/
template <typename T>
BSTree<T>::BSTree(double cusr, double busr)
{
	root = NULL;
	n = 0;
	d = 0;
	c = cusr;
	b = busr;
}
//template<typename T>
// BSTree<T>::~BSTree()
// {
// 	if(!isEmpty())
// 	{
// 		delete root;
// 	}
// }
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
/*Εκτύπωση του ΔΔΑ αναδρομικά με την χρήση μίας ακόμη
βοηθητικής μεθόδου με παραπάνω ορίσματα,
σύμφωνα με τον χαρακτήρα για την διάσχιση που επιθυμεί ο χρήστης
p: προδιάταξη, i: ενδοδιάταξη, s: μεταδιάταξη*/
template<typename T>
void BSTree<T>::printTree(char order)
{
	TreeNode<T> *node = root;
	//preorder
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
	//inorder
	{
		if(node)
		{
			printTree('i',node->leftChild);
			std::cout<<getNode(node)<<std::endl;
			printTree('i',node->rightChild);
		}
	}
	else if (order == 's')
	//postorder
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
/*αναζήτηση στο ΔΔΑ για το στοιχείο με την τιμή key
και τοποθέτηση του εφόσον το βρίσκει στην μεταβλήτη e */
template<typename T>
bool BSTree<T>::searchTree(const T& key, T& e)
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
			return true;
		}
	}
	return false;
}

/*εισαγωγή του στοιχείου elem στο ΔΔΑ
έχει προστεθεί η έξτρα συνθήκη στο συγκεκριμένο ΔΔΑ
για να διατηρεί την ισορροπία του*/
template<typename T>
int BSTree<T>::insert(const T& elem)
{
	TreeNode<T> *current = root;
	TreeNode<T> *parent = 0;
	/*θα χρησιμοποιηθεί μία δομή απλά συνδεδεμένης λίστας
	θα μπορούσε να χρησιμοποιηθεί μία απλή στοίβα αλλά αφού είχαμε 
	υλοποιήσει συναρτήσεις push και pop (insertStart, deleteStart) για την 1η εργασία πρακτικά η 
	λίστα μπορεί να χρησιμοποιηθεί και ως στοίβα*/
	List<TreeNode<T>*> *li = new List<TreeNode<T>*>();
	int depth = 0;
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
	//Έλεγχος βάθους εισαγώμενου κόμβου και ανακατασκευή αν χρειάζεται
	if (depth > ceil(c*log2(n+1+d)))
	{
		TreeNode<T> *temp;
		TreeNode<T> *papatemp;
		int lisz = li->length();
		for(int i = 0; i < lisz; i++)
		{
			li->deleteStart(temp);\
			char dir;
			if(li->deleteStart(papatemp) == 0)
			{
				dir = 'r';
				papatemp = root;
			}
			if(temp->data > papatemp->data)
			{
				dir = 'r';
			}
			else
			{
				dir = 'l';
			}
			if (maxHeight(temp) > ceil(c*log2(li->length()+1)))
			{
				printTree('p');
				printTreeStats();
				/* το όρισμα dir μας δείχνει αν ήταν 
				αριστερό ή δεξί παιδί ο κόμβος ρίζα του υποδένδρου
				που θα ανακατασκευαστεί για την σωστή σύνδεσή του
				αν αυτός ο κόμβος είναι η ρίζα του αρχικού δένδρου
				και έχουμε ολική ανακατασκευή το όρισμα αυτό είναι
				irrelevant */
				treeReconstruction(temp,papatemp, dir);
				std::cout<<"Reconstructing tree..."<<std::endl;
				printTree('p');
				printTreeStats();

				delete(li);
				break;
			}
			li->insertStart(papatemp);
		}
	}
	return depth;
}

/*διαγραφή κόμβου με αναδρομή*/
template<typename T>
TreeNode<T>* BSTree<T>::deleteNode(const T& key, TreeNode<T>* node, bool &flag)
{
	TreeNode<T>* temp;
	if(node == NULL)
	{
		flag = false;
		std::cout<<key<<" not found"<<std::endl;
		return NULL;
	}
	else if(key < node->data)
	{
		node->leftChild = deleteNode(key, node->leftChild,flag);
	}
	else if(key > node->data)
	{
		node->rightChild = deleteNode(key, node->rightChild,flag);
	}
	else if(node->leftChild and node->rightChild)
	{
		temp = minNode(node->rightChild);	//KALO DIORTHOMA
		node->data = temp->data;
		node->rightChild = deleteNode(node->data, node->rightChild,flag);
	}
	else
	{
		temp = node;
		if(node->leftChild == NULL)
			node = node->rightChild;
		else if(node->rightChild == NULL)
			node = node->leftChild;
		delete temp;
	}
	return node;
}

/*αναδρομικός υπολογισμός ύψους υποδένδρου με ρίζα
node */
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


/*Γέμισμα λίστας li με τα στοιχεία του δένδρου node 
ταξινομιμένα, διασχίζοντας το με ενδοδιάταξη*/
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