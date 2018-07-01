#include "BSTree.h"
#include <iostream>
#include <string>
#include <stdexcept>

bool tryParse(std::string& input, int& output)
{
	try{
		output = std::stoi(input);
	}catch (std::invalid_argument){
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		std::cerr << "Usage: "<<argv[0]<<" c b "<<std::endl;
		return 1;
	}
	double c = atof(argv[1]);
	double b = atof(argv[2]);
	if (c <= 1)
	{
		std::cerr << "C must be bigger than 1"<<std::endl;
		return 1;
	}
	if(b <= 0)
	{
		std::cerr << "B must be bigger than 0"<<std::endl;
		return 1;
	}
	BSTree<int> *d1 = new BSTree<int>(c,b);

	std::string input;
	int x = 1;
	int elem;
	int temp;
	while(x != 0)
	{
		std::cout<<"---Give me an integer according to the operation you want me to execute----"<<std::endl;
		std::cout<<"1. Insert element.\n";
		std::cout<<"2. Delete element.\n";
		std::cout<<"3. Search for element.\n";
		std::cout<<"4. Print tree\n";
		std::cout<<"5. Print tree attributes (height, maximum height, deletions, elements)\n";

		std::cout<<"0. Exit \n";
		std::cout<<"---------------------\n";

		getline(std::cin, input);
		while(!tryParse(input,x))
		{
			std::cout<<"Bad input. Give me an INTEGER: ";
			getline(std::cin, input);
		}

		switch(x){
			case 1:
				std::cout<<"Give me an integer to insert to the tree \n";
				getline(std::cin, input);
				while(!tryParse(input,elem))
				{
					std::cout<<"Bad input. Give me an INTEGER: ";
					getline(std::cin, input);
				}
				if(d1->insert(elem) > -1)
				{
					std::cout<<"Insertion complete...\n";
					break;
				}
				else
				{
					std::cout<<"Insertion failed, try again...\n";
				}
			case 2:
				std::cout<<"Give me an integer to delete from the tree \n";
				getline(std::cin, input);
				while(!tryParse(input,elem))
				{
					std::cout<<"Bad input. Give me an INTEGER: ";
					getline(std::cin, input);
				}
				d1->deleteNode(elem);
				break;
			case 3:
				std::cout<<"Give me an integer to search for in the tree \n";
				getline(std::cin, input);
				while(!tryParse(input,elem))
				{
					std::cout<<"Bad input. Give me an INTEGER: ";
					getline(std::cin, input);
				}
				if(d1->searchTree(elem,temp))
				{
					std::cout<<"Found "<<elem<<std::endl;
					break;
				}
				else
				{
					std::cout<<elem<<" not found.\n";
					break;
				}
			case 4:
				std::cout<<"Give me:\n1 for preorder\n2 for inorder\n3 for postorder\n ";
				getline(std::cin, input);
				while(!tryParse(input,elem))
				{
					std::cout<<"Bad input. Give me an INTEGER: ";
					getline(std::cin, input);
				}
				if(elem == 1)
				{
					d1->printTree('p');
					break;
				}
				else if(elem == 2)
				{
					d1->printTree('i');
					break;
				}
				else if(elem == 3)
				{
					d1->printTree('s');
					break;
				}
				else
				{
					std::cout<<"Invalid input\n";
					break;
				}
			case 0:
				std::cout<<"Bye bye...\n";
				break;
			case 5:
				d1->printTreeStats();
				break;

		}
	}

}