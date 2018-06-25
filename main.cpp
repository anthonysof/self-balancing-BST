#include "BSTree.h"
#include "TreeNode.h"
#include <iostream>
#include "List.h"
#include <math.h>

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		std::cerr << "Usage: "<<argv[0]<<" c b "<<std::endl;
		return 1;
	}
	double c = atof(argv[1]);
	double b = atof(argv[2]);
	if (c == 0)
	{
		std::cerr << "C must be other than 0"<<std::endl;
		return 1;
	}
	BSTree<int> *d1 = new BSTree<int>(c,b);
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

	for(int i = 1; i<20; i++)
	{
		d1->insert(i);	
	}
	int var = 0;
	// TreeNode<int> temp = d1->searchTree(13, var);
	// std::cout<<"Found "<<temp.getData()<<std::endl;
	//d1->printTree('p');
	//std::cout<<"Height of treess is: "<<d1->maxHeight(d1->getRoot())<<std::endl;
	//d1->treeReconstruction(d1->getRoot());
	//d1->printTree('p');
	//std::cout<<"Height of treess is: "<<d1->maxHeight(d1->getRoot())<<std::endl;
	std::cout<<"-----------------\nAfter Inserts:\n";
	d1->printTree('p');
	d1->printTreeStats();
	int temp;
	// d1->deleteNode(19);
	// d1->printTree('p');
	// d1->deleteNode(18);
	// d1->printTree('p');
	// d1->deleteNode(17);
	// d1->printTree('p');
	// d1->deleteNode(16);
	// d1->printTree('p');
	// d1->deleteNode(2229);
	// d1->printTree('p');
	for(int i = 19; i>5; i--)
	{
		d1->deleteNode(i);
	}
	d1->printTree('p');
	d1->printTreeStats();

	return 0;
}