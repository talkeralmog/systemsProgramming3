/****************************************
Assignment C++: 1
Author: Adar Shapira, ID: 209580208
        Almog Talker, ID: 322546680
*****************************************/
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

class BinaryTree;

// Forward declaration of operator<< for friend declaration
std::ostream& operator<<(std::ostream& os, const BinaryTree& tree);

class BinaryTree {
private:
    int data;
    BinaryTree* left;
    BinaryTree* right;
    bool is_empty_root_flag;

    // Private helper constructor for creating new nodes in _insert, _copy, and _remove
    BinaryTree(int val);

    // Helper function for recursive insertion
    BinaryTree* _insert(BinaryTree* node, int value);

    // Helper function for recursive search
    bool _search(const BinaryTree* node, int value) const;

    // Helper function for recursive in-order printing
    void _printInOrder(const BinaryTree* node) const;

    // Helper function to find minimum value recursively
    int _getMinValue(const BinaryTree* node) const;

    // Helper function to find maximum value recursively
    int _getMaxValue(const BinaryTree* node) const;

    // Helper function for deep copy (used in copy constructor/assignment)
    BinaryTree* _copy(const BinaryTree* other_node);

    // Helper function for destructor (post-order traversal for deletion)
    void _destroy(BinaryTree* node);

    // Helper function for recursive removal
    BinaryTree* _remove(BinaryTree* node, int value);

    // Helper function to find the node with the minimum value in a subtree
    BinaryTree* _findMinNode(BinaryTree* node);

public:
    // Constructor
    BinaryTree();
    // Destructor
    ~BinaryTree();

    // Copy Constructor and Assignment Operator (deep copy)
    BinaryTree(const BinaryTree& other);
    BinaryTree& operator=(const BinaryTree& other);

    // Public Members
    // Returns true if the tree (or this node representing the tree) is empty.
    bool isEmpty() const;

    // Inserts a new element to the tree
    void insert(int value);

    // Returns true if the element exists in the tree, false otherwise.
    bool search(int value) const;

    // Prints the values in ascending order (in-order traversal).
    void printInOrder() const;

    // Returns the minimum value in the tree. Throws std::runtime_error if tree is empty.
    int getMinValue() const;

    // Returns the maximum value in the tree. Throws std::runtime_error if tree is empty.
    int getMaxValue() const;

    // Removes a value from the tree. Throws std::runtime_error if tree is empty or value not found.
    void remove(int value);

    // Operators
    // Adds a value to the tree (uses insert function).
    BinaryTree& operator+=(int value);
    // Prints the tree values using the in-order traversal (uses printInOrder function).
    friend std::ostream& operator<<(std::ostream& os, const BinaryTree& tree);
};

#endif // BINARY_SEARCH_TREE_H