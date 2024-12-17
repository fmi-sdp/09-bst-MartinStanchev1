#include "bst.hpp"

int main()
{
	//0 zad
	char str[] = "(10(7(2()())(8()()))(12(11()())(15()())))";
	BinarySearchTree<int> bst(str);
	//1 zad
	bst.printRightToLeft();
	//2 zad
	bst.printLeftToRight();
	//3 zad
	std::cout << "Sum: " << bst.sum() << std::endl;
	//4 zad
	bst.map([](int x)->int {return x + 1; });
	bst.printLeftToRight();
	//5 zad
	std::cout << bst.weightNSubtrees(9) << std::endl;
	return 0;
}