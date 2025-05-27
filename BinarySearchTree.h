#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream> // For std::cout, std::endl in printInOrder, operator<<

// Forward declaration of BinaryTree class
class BinaryTree;

// Forward declaration of operator<< for friend declaration
std::ostream& operator<<(std::ostream& os, const BinaryTree& tree);

class BinaryTree {
private:
    int data;
    BinaryTree* left;
    BinaryTree* right;

    // Sentinel value to indicate an "empty" node for the isEmpty() method,
    // assuming 0 is not a valid data point for a non-empty tree node.
    static const int EMPTY_TREE_SENTINEL = 0;

    // Private helper constructor for creating new nodes in _insert and _copy
    BinaryTree(int val);

    // Helper function for recursive insertion
    BinaryTree* _insert(BinaryTree* node, int value);
    // Helper function for recursive search
    bool _search(const BinaryTree* node, int value) const; // Parameter also const
    // Helper function for recursive in-order printing
    void _printInOrder(const BinaryTree* node) const; // Parameter also const
    // Helper function to find minimum value recursively
    int _getMinValue(const BinaryTree* node) const; // Parameter also const
    // Helper function to find maximum value recursively
    int _getMaxValue(const BinaryTree* node) const; // Parameter also const
    // Helper function for deep copy (used in copy constructor/assignment)
    BinaryTree* _copy(const BinaryTree* other_node); // Parameter is const
    // Helper function for destructor (post-order traversal for deletion)
    void _destroy(BinaryTree* node);


public:
    // Constructor (default for an empty tree or the conceptual root)
    BinaryTree();
    // Destructor
    ~BinaryTree();

    // Copy Constructor (Deep Copy)
    BinaryTree(const BinaryTree& other);
    // Assignment Operator (Deep Copy + Self-Assignment Check)
    BinaryTree& operator=(const BinaryTree& other);

    // Public Members
    // Returns true if the tree (or this node representing the tree) is empty.
    // An empty tree is considered to be a default-constructed object where data is the sentinel
    // and no actual elements have been inserted yet.
    bool isEmpty() const;
    // Inserts a new element into the tree while maintaining BST properties.
    void insert(int value);
    // Returns true if the element exists in the tree, false otherwise.
    bool search(int value) const;
    // Prints the values in ascending order (in-order traversal).
    void printInOrder() const;
    // Returns the minimum value in the tree. Throws std::runtime_error if tree is empty.
    int getMinValue() const;
    // Returns the maximum value in the tree. Throws std::runtime_error if tree is empty.
    int getMaxValue() const;

    // Operators
    // Adds a value to the tree (uses insert function).
    BinaryTree& operator+=(int value);
    // Prints the tree values using the in-order traversal (uses printInOrder function).
    friend std::ostream& operator<<(std::ostream& os, const BinaryTree& tree);
};

#endif // BINARY_SEARCH_TREE_H