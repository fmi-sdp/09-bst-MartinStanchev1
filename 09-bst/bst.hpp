#pragma once
#include <iostream>
#include <algorithm>
#include <vector>

using std::pair;
using std::vector;

template <typename T>
class BinarySearchTree {
private:
	struct node {
		T key;
		node* left;
		node* right;

		node(const T& key = T(), node* left = nullptr, node* right = nullptr)
			: key(key), left(left), right(right) {}
	};

	struct perfect_pair {
		bool is_perfectly_balanced;
		size_t weight;

		perfect_pair(bool is_perfectly_balanced = false,
			size_t weight = 0)
			: is_perfectly_balanced(is_perfectly_balanced), weight(weight) {}
	};
public:
	BinarySearchTree() : root(nullptr), size(0) {}
	//0 zad
	BinarySearchTree(const char* str)
	{
		size = 0;
		vector<int> numbers = extractNumbers(str);
		for (int el : numbers)
			insert(el);
	}

	BinarySearchTree(const BinarySearchTree& other)
		:root(copy(other.root)), size(other.size) {}

	BinarySearchTree& operator=(const BinarySearchTree& other) {
		if (this != &other) {
			clear(root);
			root = copy(other.root);
			size = other.size;
		}
		return *this;
	}

	~BinarySearchTree() { clear(root); }

	bool find(const T& key) const { return find(root, key); }
	void insert(const T& key) { insert(root, key); }
	bool remove(const T& key) { return remove(root, key); }

	size_t get_size() const { return size; }
	bool is_balanced() const { return is_balanced(root).first; }
	bool is_perfectly_balanced() const
	{
		return is_perfectly_balanced(root).first;
	}

	//1 zad
	void printRightToLeft() const { printRightToLeft(root); std::cout << std::endl; }
	//2 zad
	void printLeftToRight() const { printLeftToRight(root); std::cout << std::endl; }
	//3 zad
	int sum() const { return sum(root); }
	//4 zad
	void map(T(*f)(T)) { map(f, root); };
	//5 zad
	size_t weightNSubtrees(size_t n) const { return weightNSubtrees(root, n); }
private:

	void clear(node* root);
	node* copy(node* root);

	bool find(const node* root, const T& key) const;
	void insert(node*& root, const T& key);
	bool remove(node*& root, const T& key);
	node* extract_min(node*& root);

	int height(const node* root) const;
	int weight(const node* root) const;

	pair<bool, size_t> is_balanced(const node* root) const;
	pair<bool, size_t> is_perfectly_balanced(const node* root) const;

	//1 zad
	static void printRightToLeft(node* root)
	{
		if (!root)
			return;
		printRightToLeft(root->right);
		std::cout << root->key << " ";
		printRightToLeft(root->left);
	}
	//2 zad
	static void printLeftToRight(node* root)
	{
		if (!root)
			return;
		printLeftToRight(root->left);
		std::cout << root->key << " ";
		printLeftToRight(root->right);
	}
	//3 zad
	static int sum(node* root)
	{
		if (!root)
			return 0;
		return root->key + sum(root->left) + sum(root->right);
	}
	//4 zad
	static void map(T(*f)(T), node* root)
	{
		if (!root)
			return;
		root->key = f(root->key);
		map(f, root->left);
		map(f, root->right);
	}
	//5 zad
	static size_t weightNSubtrees(node* root, size_t n)
	{
		if (!root)
			return 0;
		size_t rootWeight = weight(root);
		if (rootWeight < n)
			return 0;
		if (rootWeight == n)
			return 1;
		return weightNSubtrees(root->left, n) + weightNSubtrees(root->right, n);
	}

	static size_t weight(node* root)
	{
		if (!root)
			return 0;
		return 1 + weight(root->left) + weight(root->right);
	}
	//0 zad
	static vector<int> extractNumbers(const char* str)
	{
		vector<int> result;
		while (*str != '\0')
		{
			if (isdigit(*str))
				result.push_back(extractNumber(str));
			else
				++str;
		}
		return result;
	}

	static int extractNumber(const char*& str)
	{
		int num = 0;
		while (isdigit(*str))
		{
			num *= 10;
			num += *str - '0';
			++str;
		}
		return num;
	}

	static bool isdigit(char c)
	{
		return c <= '9' && c >= '0';
	}
private:
	node* root;
	size_t size;
};

template<typename T>
inline void BinarySearchTree<T>::clear(node* root) {
	if (!root)
		return;

	clear(root->left);
	clear(root->right);
	delete root;
}

template<typename T>
inline typename BinarySearchTree<T>::node* BinarySearchTree<T>::copy(node* root) {
	if (!root)
		return nullptr;

	return new node(root->key, copy(root->left), copy(root->right));
}

template<typename T>
inline bool BinarySearchTree<T>::find(const node* root, const T& key) const {
	if (!root)
		return false;

	if (root->key == key)
		return true;

	return key < root->key ?
		find(root->left, key) :
		find(root->right, key);
}

template<typename T>
inline void BinarySearchTree<T>::insert(node*& root, const T& key) {
	if (!root) {
		root = new node(key);
		size++;
		return;
	}

	insert(key < root->key ?
		root->left :
		root->right,
		key);
}

template<typename T>
inline bool BinarySearchTree<T>::remove(node*& root, const T& key) {
	if (!root)
		return false;

	if (root->key == key) {
		node* to_remove = root;
		if (!root->left) {
			root = root->right;
		}
		else if (!root->right) {
			root = root->left;
		}
		else {
			node* min_right = extract_min(root->right);
			min_right->left = root->left;
			min_right->right = root->right;
			root = min_right;
		}
		size--;
		delete to_remove;
		return true;
	}
	else {
		return remove(key < root->key ?
			root->left :
			root->right,
			key);
	}
}

template<typename T>
inline typename BinarySearchTree<T>::node* BinarySearchTree<T>::extract_min(node*& root) {
	if (root->left)
		return extract_min(root->left);

	node* min = root;
	root = root->right;
	return min;
}

template<typename T>
inline int BinarySearchTree<T>::height(const node* root) const {
	if (!root)
		return 0;

	return 1 + std::max(height(root->left), height(root->right));
}

template<typename T>
inline int BinarySearchTree<T>::weight(const node* root) const {
	if (!root)
		return 0;

	return 1 + weight(root->left) + weight(root->right);
}

template<typename T>
inline pair<bool, size_t> BinarySearchTree<T>::is_balanced(const node* root) const {
	if (!root)
		return pair<bool, size_t>(true, 0);

	pair<bool, size_t> left_pair = is_balanced(root->left);
	pair<bool, size_t> right_pair = is_balanced(root->right);

	bool is_balanced_node = left_pair.first
		&& right_pair.first
		&& abs(left_pair.second - right_pair.second) <= 1;

	size_t curr_height = 1 + std::max(left_pair.second, right_pair.second);

	return pair<bool, size_t>(is_balanced_node, curr_height);
}

template<typename T>
inline pair<bool, size_t> BinarySearchTree<T>::is_perfectly_balanced(const node* root) const {
	if (!root)
		return pair<bool, size_t>(true, 0);


	pair<bool, size_t> left_pair = is_perfectly_balanced(root->left);
	pair<bool, size_t> right_pair = is_perfectly_balanced(root->right);

	bool is_balanced_node = left_pair.first
		&& right_pair.first
		&& abs(left_pair.second - right_pair.second) <= 1;

	size_t curr_weight = 1 + left_pair.second + right_pair.second;

	return pair<bool, size_t>(is_balanced_node, curr_weight);
}