#include "BSTree.h"
#include "TreeNode.h"
#include <iostream>
#include "List.h"
#include <math.h>

int main()
{
	BSTree<int> *d1 = new BSTree<int>(1.2,1);
	//int ceiling1 = ceil(c*log2(n+1+d)); 
	//int ceiling2 = ceil(c*log2(n+1));

	// d1->insert(8);
	// d1->insert(5);
	// d1->insert(16);
	// d1->insert(1);
	// d1->insert(7);
	// d1->insert(14);
	// d1->insert(19);
	// d1->insert(4);
	// d1->insert(6);
	// d1->insert(9);
	// d1->insert(15);
	// d1->insert(18);
	// d1->insert(3);	
	// d1->insert(12);	
	// d1->insert(17);	
	// d1->insert(2);
	// d1->insert(11);	
	// d1->insert(13);	
	// d1->insert(10);
	// d1->insert(40);
	// d1->insert(20);
	// d1->insert(22);
	// d1->insert(30);

	for(int i = 1; i<8; i++)
	{
		d1->insert(i);	
	}
	int var = 0;
	// TreeNode<int> temp = d1->searchTree(13, var);
	// std::cout<<"Found "<<temp.getData()<<std::endl;
	d1->printTree('p');
	std::cout<<"Height of tree is: "<<d1->maxHeight(d1->getRoot())<<std::endl;


	return 0;
}