#include "SortedList.h"
#include <limits> // For std::numeric_limits
#include <stdexcept> // For std::out_of_range

// Private helper constructor for creating new nodes easily.
// This constructor is used internally to create actual data nodes.
SortedList::SortedList(int val) : data(val), next(nullptr) {}

// --- Private Helper Functions ---

// Helper for recursive insertion.
// Returns the (potentially new) head of the subtree after insertion.
SortedList* SortedList::_insert_node(SortedList* current_node, int value) {
    if (current_node == nullptr || value < current_node->data) {
        // Create a new node and insert it before current_node or if current_node is null.
        SortedList* new_node = new SortedList(value);
        new_node->next = current_node;
        return new_node;
    }
    // If value >= current_node->data, move to the next node to find insertion point.
    current_node->next = _insert_node(current_node->next, value);
    return current_node;
}

// Helper for recursive removal.
// Returns the (potentially new) head of the subtree after removal.
SortedList* SortedList::_remove_node(SortedList* current_node, int value, bool& removed_flag) {
    if (current_node == nullptr) {
        removed_flag = false; // Value not found
        return nullptr;
    }
    if (value == current_node->data) {
        // Found the node to remove.
        SortedList* temp = current_node->next;
        current_node->next = nullptr; // Detach before deletion
        delete current_node;
        removed_flag = true; // Value successfully removed
        return temp;
    }
    if (value < current_node->data) {
        // In a sorted list, if the value is smaller than current node's data
        // and we haven't found it, it cannot exist later in the list.
        removed_flag = false;
        return current_node; // Value not found, return current_node unchanged
    }
    // value > current_node->data, so continue searching in the rest of the list.
    current_node->next = _remove_node(current_node->next, value, removed_flag);
    return current_node;
}

// Helper for recursive search.
// Returns true if the value is found in the subtree, false otherwise.
bool SortedList::_search_node(const SortedList* current_node, int value) const {
    if (current_node == nullptr) {
        return false;
    }
    if (current_node->data == value) {
        return true;
    }
    if (value < current_node->data) {
        // In a sorted linked list, if value is smaller than current_node->data
        // and we haven't found it, it cannot exist later in the list.
        return false;
    }
    return _search_node(current_node->next, value);
}

// Helper for recursive print.
// Prints the elements of the subtree.
void SortedList::_print_nodes(const SortedList* current_node) const {
    if (current_node == nullptr) {
        return;
    }
    std::cout << current_node->data;
    if (current_node->next != nullptr) {
        std::cout << ", ";
    }
    _print_nodes(current_node->next);
}

// Helper for deep copying a subtree.
// Creates a new subtree that is a deep copy of the given other_node.
SortedList* SortedList::_copy_nodes(const SortedList* other_node) {
    if (other_node == nullptr) {
        return nullptr;
    }
    SortedList* new_node = new SortedList(other_node->data);
    new_node->next = _copy_nodes(other_node->next);
    return new_node;
}

// Helper for deep destruction of a subtree.
// Deletes all nodes in the given subtree.
void SortedList::_destroy_nodes(SortedList* current_node) {
    while (current_node != nullptr) {
        SortedList* next_node = current_node->next;
        current_node->next = nullptr; // Detach to avoid deep recursion if stack overflow is a concern
        delete current_node;
        current_node = next_node;
    }
}

// Helper to get the last node of a list.
// Used for efficient appending in concatenation operations.
SortedList* SortedList::_getLastNode(SortedList* current_node) {
    if (current_node == nullptr || current_node->next == nullptr) {
        return current_node;
    }
    return _getLastNode(current_node->next);
}

// Helper to check for equality recursively.
bool SortedList::_are_equal_nodes(const SortedList* list1, const SortedList* list2) const {
    if (list1 == nullptr && list2 == nullptr) {
        return true;
    }
    if (list1 == nullptr || list2 == nullptr || list1->data != list2->data) {
        return false;
    }
    return _are_equal_nodes(list1->next, list2->next);
}


// --- Public Member Functions ---

// Default Constructor.
// Initializes the list to an "empty" state.
SortedList::SortedList() : data(EMPTY_LIST_SENTINEL), next(nullptr) {
    // `data` is initialized to a sentinel value and `next` to nullptr
    // to indicate an empty list when created without explicit value.
}

// Destructor.
// Cleans up all dynamically allocated memory in the list to prevent memory leaks.
SortedList::~SortedList() {
    // The destructor needs to free all nodes *except* the 'this' node's data.
    // If 'this' is the conceptual head object, and it holds children pointers,
    // we need to delete those children and their sub-lists.
    _destroy_nodes(this->next);
    this->next = nullptr; // Ensure pointer is null after destruction
}

// Copy Constructor (Deep Copy).
// Creates a new SortedList object that is a deep copy of 'other'.
SortedList::SortedList(const SortedList& other) : data(EMPTY_LIST_SENTINEL), next(nullptr) {
    if (!other.isEmpty()) { // Only copy if the other list is not conceptually empty
        this->data = other.data;
        this->next = _copy_nodes(other.next);
    }
}

// Assignment Operator (Deep Copy + Self-Assignment Check).
// Assigns the content of 'other' to the current SortedList object.
SortedList& SortedList::operator=(const SortedList& other) {
    if (this == &other) { // Handle self-assignment
        return *this;
    }

    // Deallocate existing resources of the current list
    _destroy_nodes(this->next); // Free the rest of the current list
    this->next = nullptr; // Ensure pointer is null after destruction

    // Copy data from 'other'
    if (other.isEmpty()) {
        this->data = EMPTY_LIST_SENTINEL;
    } else {
        this->data = other.data;
        this->next = _copy_nodes(other.next); // Deep copy the other list
    }
    return *this;
}

// Check if the list is empty.
// Returns true if this object represents an empty list (default-constructed state or cleared).
bool SortedList::isEmpty() const {
    // An empty list is represented by the initial state of a default-constructed SortedList object
    // where its data is the sentinel and it has no `next` node.
    return (data == EMPTY_LIST_SENTINEL && next == nullptr);
}

// Inserts a value into the list.
// Handles the case where the list is initially empty and then uses recursive helper.
void SortedList::insert(int value) {
    if (isEmpty()) { // If it's the very first insertion into a default-constructed object
        data = value; // Set the head's data
        // next is already nullptr
    } else {
        // If the new value is smaller than current head's data, it effectively becomes the new head.
        // This requires "shifting" the current head's content down.
        if (value < this->data) {
            int old_data = this->data;
            SortedList* old_next = this->next;

            this->data = value; // New value becomes the new head's data
            this->next = new SortedList(old_data); // Old head's data goes into a new node
            this->next->next = old_next; // Attach old list's tail to the new node
        } else {
            // Otherwise, insert into the rest of the list
            this->next = _insert_node(this->next, value);
        }
    }
}

// Removes a value from the list.
// Returns true if the element was found and removed, false otherwise.
bool SortedList::remove(int value) {
    bool removed_flag = false;
    // Check if the head itself needs to be removed
    if (data == value) {
        if (next == nullptr) { // Removing the only element
            data = EMPTY_LIST_SENTINEL; // Reset to empty state
        } else { // Remove head and promote next element
            data = next->data;
            SortedList* old_next = next;
            next = next->next;
            old_next->next = nullptr; // Detach before deleting
            delete old_next;
        }
        removed_flag = true;
        return true;
    }
    // Search and remove from the rest of the list
    this->next = _remove_node(this->next, value, removed_flag);
    return removed_flag;
}

// Search for a value in the list.
bool SortedList::search(int value) const {
    if (isEmpty()) {
        return false;
    }
    // Check current node first
    if (data == value) {
        return true;
    }
    // If value is smaller than current node's data, it cannot be found (list is sorted)
    if (value < data) {
        return false;
    }
    // Otherwise, search in the rest of the list
    return _search_node(this->next, value);
}

// Print list elements in-order.
void SortedList::printList() const {
    if (isEmpty()) {
        return; // Print nothing if empty
    }
    // Print the first element, then recursively print the rest
    std::cout << data;
    if (next != nullptr) {
        std::cout << ", ";
        _print_nodes(this->next);
    }
}

// Get the first item.
// Throws std::out_of_range if the list is empty.
int SortedList::getFirst() const {
    if (isEmpty()) {
        throw std::out_of_range("Attempted to get first element from an empty list.");
    }
    return data;
}


// --- Operators ---

// 1) Concatenate 'SortedList' objects.
// Creates a new SortedList containing all elements from both lists, maintaining sorted order.
SortedList SortedList::operator+(const SortedList& other) const {
    SortedList result_list; // Create a new empty list

    // Insert elements from the current list
    const SortedList* current_this = this;
    if (!current_this->isEmpty()) {
        // If result_list is currently empty, effectively assign the first part of 'this' to it
        result_list.data = current_this->data;
        result_list.next = _copy_nodes(current_this->next);
    }

    // Insert elements from the 'other' list
    const SortedList* current_other = &other;
    if (!current_other->isEmpty()) {
        // If result_list is still empty (meaning both 'this' and 'other' were initially empty),
        // or 'this' was empty and 'other' has elements.
        if (result_list.isEmpty()) {
            result_list.data = current_other->data;
            result_list.next = _copy_nodes(current_other->next);
        } else {
            // Otherwise, insert elements from 'other' into the already populated result_list
            // This loop iterates through 'other' and inserts each element into 'result_list'
            const SortedList* temp_other = &other;
            while (temp_other != nullptr && !temp_other->isEmpty()) {
                result_list.insert(temp_other->data);
                temp_other = temp_other->next;
            }
        }
    }
    return result_list;
}


// 2) Concatenate 'SortedList' object with an integer.
// Creates a new SortedList containing all elements from the original list plus the new integer.
SortedList SortedList::operator+(int value) const {
    SortedList result_list = *this; // Make a deep copy of the current list
    result_list.insert(value); // Insert the new value into the copy
    return result_list;
}

// Friend function for 3 + sl1 syntax.
SortedList operator+(int value, const SortedList& list) {
    return list + value; // Leverage the existing operator+(int value) const
}

// 3) += - Pushes an integer to the list (uses the insert function).
SortedList& SortedList::operator+=(int value) {
    insert(value);
    return *this;
}

// 4) == - Compares two lists.
// Returns true if both lists contain the same elements in the same order, false otherwise.
bool SortedList::operator==(const SortedList& other) const {
    // Check if both are conceptually empty using the isEmpty() method
    bool this_is_empty = this->isEmpty();
    bool other_is_empty = other.isEmpty();

    if (this_is_empty && other_is_empty) {
        return true; // Both are empty
    }
    if (this_is_empty || other_is_empty) {
        return false; // One is empty, the other isn't
    }

    // If both are non-empty, compare elements starting from this node and other's node.
    return _are_equal_nodes(this, &other);
}

// 4) != - Compares two lists (added for completeness).
// Returns true if the lists are not equal, false otherwise.
bool SortedList::operator!=(const SortedList& other) const {
    return !(*this == other);
}

// 5) << - Insertion operator for easy printing.
std::ostream& operator<<(std::ostream& os, const SortedList& list) {
    // Handle conceptually empty list using isEmpty()
    if (list.isEmpty()) {
        os << "[]";
        return os;
    }
    os << "[";
    list._print_nodes(&list); // Start printing from the actual list object (itself)
    os << "]";
    return os;
}