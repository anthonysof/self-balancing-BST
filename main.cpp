#include "BSTree.h"
#include "TreeNode.h"
#include <iostream>
using namespace std;
int main()
{
	BSTree<int> d;
	d.insert(30);
	d.insert(10);
	d.insert(20);
	d.insert(40);
	d.insert(0);
	d.printTree('i');
	int deleted = 0;
	cout<<"EAE"<<endl;
	d.printTree('p');
	cout<<"Height: "<<d.maxDepth(d.getRoot())<<endl;
	d.deleteNode(10,deleted);
	cout<<"deleted: "<<deleted<<endl;
	d.deleteNode(30,deleted);
	cout<<"deleted: "<<deleted<<endl;
	d.printTree('i');
	cout<<"Height: "<<d.maxDepth(d.getRoot())<<endl;
	bool found = d.search(20, deleted);
	if(found)
		cout<<"Found "<<deleted<<endl;
	cout<<"Destroying"<<endl;
	delete &d;

	return 0;
}