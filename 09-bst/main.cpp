#include <iostream>
#include <string>
#include <sstream>

using std::string;
using std::stringstream;
struct Node
{
	int data;
	Node* left, * right;
	Node(int d = 0, Node* l = nullptr, Node* r = nullptr) : data(d), left(l), right(r) {}
};
int parseInt(stringstream& ss)
{
	int num = 0;
	char c;
	while (isdigit(ss.peek()))
	{
		ss >> c;
		num *= 10;
		num += c - '0';
	}
	return num;
}
Node* parseTree(stringstream& ss)
{
	char c;
	ss >> c;
	if (ss.peek() == ')')
	{
		while (ss.peek() == ')')
			ss >> c;
		return nullptr;
	}
	else
	{
		int num = parseInt(ss);
		Node* left = parseTree(ss);
		Node* right = parseTree(ss);
		return new Node(num, left, right);
	}
}

//1 zad
void printInOrder(const Node* root)
{
	if (!root)
		return;
	printInOrder(root->left);
	std::cout << root->data << " ";
	printInOrder(root->right);
}

//2 zad
void printReverseOrder(const Node* root)
{
	if (!root)
		return;
	printReverseOrder(root->right);
	std::cout << root->data << " ";
	printReverseOrder(root->left);
}

//3 zad
int sum(const Node* root)
{
	if (!root)
		return 0;

	return sum(root->left) + root->data + sum(root->right);
}

//5 zad
int weight(const Node* root)
{
	if (!root)
		return 0;
	return weight(root->left) + weight(root->left) + 1;
}
int countSubtrees(const Node* root, int n)
{
	if (!root)
		return 0;
	if (weight(root) == n)
		return 1;
	int leftCount = countSubtrees(root->left, n);
	int rightCount = countSubtrees(root->right, n);
	return leftCount + rightCount;
}
int main()
{
	string input = "(10(7(2()())(8()()))(12(11()())(15()())))";
	stringstream ss(input);
	Node* tree = parseTree(ss);
	printInOrder(tree);
	std::cout << std::endl;
	printReverseOrder(tree);
	std::cout << std::endl;
	std::cout << sum(tree) << std::endl;
	std::cout << countSubtrees(tree, 7);
	return 0;
}