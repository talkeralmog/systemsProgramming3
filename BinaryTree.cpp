/****************************************
Assignment C++: 1
Author: Adar Shapira, ID: 209580208
        Almog Talker, ID: 322546680
*****************************************/
#include "BinaryTree.h"
#include <stdexcept>

// --- Private Helper Constructor ---

// Constructor for creating new nodes within the tree structure.
BinaryTree::BinaryTree(int val) : data(val), left(nullptr), right(nullptr), is_empty_root_flag(false) {}

// --- Private Helper Functions ---

// Helper for recursive insertion
// Returns the root of the subtree after insertion
BinaryTree* BinaryTree::_insert(BinaryTree* node, int value) {
    if (node == nullptr) {
        return new BinaryTree(value);
    }
    if (value < node->data) {
        node->left = _insert(node->left, value);
    }
    else if (value >= node->data) {
        node->right = _insert(node->right, value);
    }
    return node;
}

// Helper for recursive search
// Returns true if the value is found in the subtree, false otherwise
bool BinaryTree::_search(const BinaryTree* node, int value) const {
    if (node == nullptr) {
        return false;
    }
    if (node->data == value) {
        return true;
    }
    if (value < node->data) {
        return _search(node->left, value);
    }
    else {
        return _search(node->right, value);
    }
}

// Helper for recursive in-order printing
// Prints the elements of the subtree in ascending order
void BinaryTree::_printInOrder(const BinaryTree* node) const {
    if (node == nullptr) {
        return;
    }
    _printInOrder(node->left);
    std::cout << node->data << " ";
    _printInOrder(node->right);
}

// Helper for recursive getMinValue
// Finds the minimum value in the subtree
int BinaryTree::_getMinValue(const BinaryTree* node) const {
    if (node == nullptr) {
        // This case should be caught by the public getMinValue()
        throw std::runtime_error("Error: _getMinValue called on nullptr node.");
    }
    // Traverse left until the leftmost node is found.
    if (node->left == nullptr) {
        return node->data;
    }
    return _getMinValue(node->left);
}

// Helper for recursive getMaxValue
// Finds the maximum value in the subtree
int BinaryTree::_getMaxValue(const BinaryTree* node) const {
    if (node == nullptr) {
        // This case should be caught by the public getMaxValue()
        throw std::runtime_error("Error: _getMaxValue called on nullptr node.");
    }
    // Traverse right until the rightmost node is found.
    if (node->right == nullptr) {
        return node->data;
    }
    return _getMaxValue(node->right);
}

// Helper for deep copying a subtree
// Creates a new subtree that is a deep copy of the given other_node
BinaryTree* BinaryTree::_copy(const BinaryTree* otherNode) {
    if (otherNode == nullptr) {
        return nullptr;
    }
    BinaryTree* newNode = new BinaryTree(otherNode->data);
    newNode->left = _copy(otherNode->left);
    newNode->right = _copy(otherNode->right);
    return newNode;
}

// Helper for deep destruction of a subtree (post-order traversal for deletion)
// Deletes all nodes in the given subtree
void BinaryTree::_destroy(BinaryTree* node) {
    if (node == nullptr) {
        return;
    }
    _destroy(node->left);
    _destroy(node->right);
    delete node;
}

// Helper for recursive removal
BinaryTree* BinaryTree::_remove(BinaryTree* node, int value) {
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->data) {
        node->left = _remove(node->left, value);
    }
    else if (value > node->data) {
        node->right = _remove(node->right, value);
    }
    else { // node->data == value. this is the node to be removed
        // No child or one child
        if (node->left == nullptr) {
            BinaryTree* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            BinaryTree* temp = node->left;
            delete node;
            return temp;
        }

        // Two children
        // Get the inorder successor (smallest in the right subtree)
        BinaryTree* temp = _findMinNode(node->right);

        // Copy the inorder successor's content to this node
        node->data = temp->data;

        // Delete the inorder successor from the right subtree
        node->right = _remove(node->right, temp->data);
    }
    return node;
}

// Helper to find node with min value in a subtree (used by _remove)
BinaryTree* BinaryTree::_findMinNode(BinaryTree* node) {
    // Assume node is not nullptr when called
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// --- Public Member Functions ---

// Default Constructor, initializes the tree to an empty state
BinaryTree::BinaryTree() : data(0), left(nullptr), right(nullptr), is_empty_root_flag(true) {}

// Destructor, cleans up all dynamic memory in the tree
BinaryTree::~BinaryTree() {
    // Only destroy if it's not an empty root flag or if it's a non-root node.
    if (!is_empty_root_flag || left != nullptr || right != nullptr) {
        // Destroy the children first
        _destroy(left);
        _destroy(right);
    }
    left = nullptr;
    right = nullptr;
}

// Copy Constructor (Deep Copy), creates a new BinaryTree object that is a deep copy of 'other'
BinaryTree::BinaryTree(const BinaryTree& other) : data(0), left(nullptr), right(nullptr), is_empty_root_flag(true) {
    if (!other.isEmpty()) {
        this->data = other.data;
        this->left = _copy(other.left);
        this->right = _copy(other.right);
        this->is_empty_root_flag = false;
    }
}

// Assigns the content of 'other' to the current BinaryTree object
BinaryTree& BinaryTree::operator=(const BinaryTree& other) {
    if (this == &other) {
        return *this;
    }

    // Deallocate existing resources of the current tree
    _destroy(left);
    _destroy(right);
    left = nullptr;
    right = nullptr;

    // Copy data from 'other'
    if (other.isEmpty()) {
        this->is_empty_root_flag = true;
        this->data = 0; // Default uninitialized value
    } else {
        this->data = other.data;
        this->left = _copy(other.left);
        this->right = _copy(other.right);
        this->is_empty_root_flag = false;
    }
    return *this;
}

// Check if the tree is empty
bool BinaryTree::isEmpty() const {
    return is_empty_root_flag;
}

// Inserts a value into the tree
void BinaryTree::insert(int value) {
    if (isEmpty()) {
        data = value;
        is_empty_root_flag = false; // It's no longer an empty root
        // left and right are already nullptr
    }
    else {
        if (value < this->data) {
            this->left = _insert(this->left, value);
        }
        else if (value >= this->data) {
            this->right = _insert(this->right, value);
        }
    }
}

// Search for a value in the tree
bool BinaryTree::search(int value) const {
    if (isEmpty()) {
        return false;
    }
    return _search(this, value); // Start recursive search
}

// Print tree elements in-order
void BinaryTree::printInOrder() const {
    if (isEmpty()) {
        std::cout << "Tree is empty.\n";
        return;
    }
    _printInOrder(this); // Start recursive printing
    std::cout << std::endl; // Add a new line at the end
}

// Get the minimum value in the tree
int BinaryTree::getMinValue() const {
    if (isEmpty()) {
        throw std::runtime_error("Attempted to get min value from an empty tree.");
    }
    return _getMinValue(this); // Start recursive min value search
}

// Get the maximum value in the tree
int BinaryTree::getMaxValue() const {
    if (isEmpty()) {
        throw std::runtime_error("Attempted to get max value from an empty tree.");
    }
    return _getMaxValue(this); // Start recursive max value search
}

// Remove a value from the tree.
void BinaryTree::remove(int value) {
    if (isEmpty()) {
        throw std::runtime_error("Attempted to remove value from an empty tree.");
    }

    if (this->data == value) {
        // If no children the tree becomes empty
        if (this->left == nullptr && this->right == nullptr) {
            this->is_empty_root_flag = true;
            this->data = 0; // Default
            return;
        }
        // If one child
        else if (this->left == nullptr) {
            BinaryTree* temp = this->right;
            // Transfer data and children from right child to current root
            this->data = temp->data;
            this->left = temp->left;
            this->right = temp->right;
            temp->left = nullptr;
            temp->right = nullptr;
            delete temp;
            return;
        }
        else if (this->right == nullptr) {
            BinaryTree* temp = this->left;
            // Transfer data and children from left child to current root
            this->data = temp->data;
            this->left = temp->left;
            this->right = temp->right;
            temp->left = nullptr;
            temp->right = nullptr;
            delete temp;
            return;
        }
        // If two children
        else {
            BinaryTree* temp = _findMinNode(this->right);
            this->data = temp->data;
            this->right = _remove(this->right, temp->data);
            return;
        }
    }

    // If the value is not the root
    if (value < this->data) {
        this->left = _remove(this->left, value);
    }
    else if (value > this->data) {
        this->right = _remove(this->right, value);
    }
    // Check if the value was actually removed by the _remove helper
    if (search(value)) {
        throw std::runtime_error("Value not found in tree for removal.");
    }
}

// --- Operators ---

// Adds a value to the tree (uses the insert function)
BinaryTree& BinaryTree::operator+=(int value) {
    insert(value);
    return *this;
}

// Prints the tree values (uses the printInOrder function)
std::ostream& operator<<(std::ostream& os, const BinaryTree& tree) {
    if (tree.isEmpty()) {
        os << "Tree is empty.";
    } else {
        tree._printInOrder(&tree); // Start recursive printing
    }
    return os;
}