#include "BinarySearchTree.h"
#include <limits> // Required for std::numeric_limits
#include <stdexcept> // For std::runtime_error

// --- Private Helper Constructor ---
// Constructor for creating new nodes within the tree structure.
BinaryTree::BinaryTree(int val) : data(val), left(nullptr), right(nullptr) {}

// --- Private Helper Functions ---

// Helper for recursive insertion.
// Returns the (potentially new) root of the subtree after insertion.
BinaryTree* BinaryTree::_insert(BinaryTree* node, int value) {
    if (node == nullptr) {
        // If the current position is empty, create a new node and return it.
        return new BinaryTree(value);
    }
    if (value < node->data) {
        node->left = _insert(node->left, value);
    } else if (value > node->data) {
        node->right = _insert(node->right, value);
    }
    // If value == node->data, do nothing (assuming no duplicates or specific handling).
    return node;
}

// Helper for recursive search.
// Returns true if the value is found in the subtree, false otherwise.
bool BinaryTree::_search(const BinaryTree* node, int value) const {
    if (node == nullptr) {
        return false;
    }
    if (node->data == value) {
        return true;
    }
    if (value < node->data) {
        return _search(node->left, value);
    } else {
        return _search(node->right, value);
    }
}

// Helper for recursive in-order printing.
// Prints the elements of the subtree in ascending order.
void BinaryTree::_printInOrder(const BinaryTree* node) const {
    if (node == nullptr) {
        return;
    }
    _printInOrder(node->left);
    std::cout << node->data << " ";
    _printInOrder(node->right);
}

// Helper for recursive getMinValue.
// Finds the minimum value in the subtree. Assumes node is not nullptr.
int BinaryTree::_getMinValue(const BinaryTree* node) const {
    // Traverse left until the leftmost node is found.
    if (node->left == nullptr) {
        return node->data;
    }
    return _getMinValue(node->left);
}

// Helper for recursive getMaxValue.
// Finds the maximum value in the subtree. Assumes node is not nullptr.
int BinaryTree::_getMaxValue(const BinaryTree* node) const {
    // Traverse right until the rightmost node is found.
    if (node->right == nullptr) {
        return node->data;
    }
    return _getMaxValue(node->right);
}

// Helper for deep copying a subtree.
// Creates a new subtree that is a deep copy of the given other_node.
BinaryTree* BinaryTree::_copy(const BinaryTree* other_node) {
    if (other_node == nullptr) {
        return nullptr;
    }
    BinaryTree* new_node = new BinaryTree(other_node->data);
    new_node->left = _copy(other_node->left);
    new_node->right = _copy(other_node->right);
    return new_node;
}

// Helper for deep destruction of a subtree (post-order traversal for deletion).
// Deletes all nodes in the given subtree.
void BinaryTree::_destroy(BinaryTree* node) {
    if (node == nullptr) {
        return;
    }
    _destroy(node->left);
    _destroy(node->right);
    delete node;
}


// --- Public Member Functions ---

// Default Constructor.
// Initializes the tree to an "empty" state.
BinaryTree::BinaryTree() : data(EMPTY_TREE_SENTINEL), left(nullptr), right(nullptr) {
    // `data` is initialized to a sentinel value and children to nullptr
    // to indicate an empty tree when created without explicit value.
}

// Destructor.
// Cleans up all dynamically allocated memory in the tree to prevent memory leaks.
BinaryTree::~BinaryTree() {
    // The destructor needs to free all nodes *except* the 'this' node's data.
    // If 'this' is the conceptual root object, and it holds children pointers,
    // we need to delete those children and their subtrees.
    _destroy(left);
    _destroy(right);
    left = nullptr; // Ensure pointers are null after destruction
    right = nullptr;
    // Note: The 'data' member of the root object itself is on the stack/heap where the object is,
    // not dynamically allocated for this specific design.
}

// Copy Constructor (Deep Copy).
// Creates a new BinaryTree object that is a deep copy of 'other'.
BinaryTree::BinaryTree(const BinaryTree& other) : data(EMPTY_TREE_SENTINEL), left(nullptr), right(nullptr) {
    if (!other.isEmpty()) { // Only copy if the other tree is not conceptually empty
        this->data = other.data;
        this->left = _copy(other.left);
        this->right = _copy(other.right);
    }
}

// Assignment Operator (Deep Copy + Self-Assignment Check).
// Assigns the content of 'other' to the current BinaryTree object.
BinaryTree& BinaryTree::operator=(const BinaryTree& other) {
    if (this == &other) { // Handle self-assignment to prevent self-deletion
        return *this;
    }

    // Deallocate existing resources of the current tree
    _destroy(left);
    _destroy(right);
    left = nullptr; // Ensure pointers are null after destruction
    right = nullptr;

    // Copy data from 'other'
    if (other.isEmpty()) {
        this->data = EMPTY_TREE_SENTINEL;
    } else {
        this->data = other.data;
        this->left = _copy(other.left);
        this->right = _copy(other.right);
    }
    return *this;
}

// Check if the tree is empty.
// Returns true if this object represents an empty tree (default-constructed state or cleared).
bool BinaryTree::isEmpty() const {
    // An empty tree is represented by the initial state of a default-constructed BinaryTree object
    // where its data is the sentinel and it has no children.
    return (data == EMPTY_TREE_SENTINEL && left == nullptr && right == nullptr);
}

// Inserts a value into the tree.
// Handles the case where the tree is initially empty and then uses recursive helper.
void BinaryTree::insert(int value) {
    if (isEmpty()) { // If it's the very first insertion into a default-constructed object
        data = value; // Set the root's data
        // left and right are already nullptr
    } else {
        // If the new value is smaller than current root's data, it effectively becomes the new root.
        // This requires "shifting" the current root's content down.
        if (value < this->data) {
            int old_data = this->data;
            BinaryTree* old_left = this->left;
            BinaryTree* old_right = this->right;

            this->data = value; // New value becomes the new root's data
            this->left = nullptr; // New root has no left child yet (will be populated by _insert)
            this->right = new BinaryTree(old_data); // Old root's data goes into a new node in the right subtree
            this->right->left = old_left; // Attach old left subtree to the new right node's left
            this->right->right = old_right; // Attach old right subtree to the new right node's right
            // This is a complex way to handle it for a simple `void insert`.
            // A more standard `insert` on a "node" would either return a new node,
            // or assume it's always inserting into a child.
            // Given the problem's implicit "this is the tree head", this is a workaround.
            // It effectively pushes the current root's contents into its right child to make space for a smaller new root.
            // THIS IS NOT A STANDARD BST INSERT. It's a workaround for the 'void insert' on the root.
            // A more robust solution for `void insert` on a conceptual "tree object" would be to have
            // a `BinaryTree* _root;` member inside a `TreeManager` class.
            // For now, sticking to the single-node-as-tree approach.
        } else {
            // Otherwise, insert into the appropriate subtree
            this->right = _insert(this->right, value); // Use private helper for recursive insertion
        }
    }
}

// Search for a value in the tree.
bool BinaryTree::search(int value) const {
    if (isEmpty()) {
        return false;
    }
    return _search(this, value); // Start recursive search from this node
}

// Print tree elements in-order.
void BinaryTree::printInOrder() const {
    if (isEmpty()) {
        // std::cout << "Tree is empty." << std::endl; // Optional: print a message
        return;
    }
    _printInOrder(this); // Start recursive printing from this node
}

// Get the minimum value in the tree.
// Throws std::runtime_error if the tree is empty.
int BinaryTree::getMinValue() const {
    if (isEmpty()) {
        throw std::runtime_error("Attempted to get min value from an empty tree.");
    }
    return _getMinValue(this); // Start recursive min value search from this node
}

// Get the maximum value in the tree.
// Throws std::runtime_error if the tree is empty.
int BinaryTree::getMaxValue() const {
    if (isEmpty()) {
        throw std::runtime_error("Attempted to get max value from an empty tree.");
    }
    return _getMaxValue(this); // Start recursive max value search from this node
}


// --- Operators ---

// Adds a value to the tree (uses the insert function).
BinaryTree& BinaryTree::operator+=(int value) {
    insert(value);
    return *this;
}

// Prints the tree values (uses the printInOrder function).
std::ostream& operator<<(std::ostream& os, const BinaryTree& tree) {
    if (tree.isEmpty()) {
        os << "[]"; // Represent empty tree
        return os;
    }
    os << "[";
    tree._printInOrder(&tree); // Start recursive printing from the root
    os << "]";
    return os;
}