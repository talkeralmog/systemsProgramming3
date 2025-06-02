/****************************************
Assignment C++: 1
Author: Adar Shapira, ID: 209580208
        Almog Talker, ID: 322546680
*****************************************/
#include "SortedList.h"
#include <stdexcept>
#include <iostream>

// This constructor is used internally to create data nodes
SortedList::SortedList(int val) : data(val), next(nullptr), is_empty_head_flag(false) {}

// --- Private Helper Functions ---

// Helper for recursive insertion
// Returns the head of the subtree after insertion
SortedList* SortedList::_insert_node(SortedList* current_node, int value) {
    if (current_node == nullptr || value < current_node->data) {
        SortedList* new_node = new SortedList(value);
        new_node->next = current_node;
        return new_node;
    }
    // move to the next node to find insertion point.
    current_node->next = _insert_node(current_node->next, value);
    return current_node;
}

// Helper for recursive removal
// Returns the head of the subtree after removal
SortedList* SortedList::_remove_node(SortedList* current_node, int value, bool& removed_flag) {
    if (current_node == nullptr) {
        removed_flag = false;
        return nullptr;
    }
    if (value == current_node->data) {
        SortedList* temp = current_node->next;
        current_node->next = nullptr; 
        delete current_node;
        removed_flag = true;
        return temp;
    }
    if (value < current_node->data) {
        removed_flag = false;
        return current_node; // Value not found, return unchanged
    }
    current_node->next = _remove_node(current_node->next, value, removed_flag);
    return current_node;
}

// Helper for recursive search
// Returns true if the value is found in the subtree, false otherwise
bool SortedList::_search_node(const SortedList* current_node, int value) const {
    if (current_node == nullptr) {
        return false;
    }
    if (current_node->data == value) {
        return true;
    }
    if (value < current_node->data) {
        return false;
    }
    return _search_node(current_node->next, value);
}

// Helper for recursive print
// Prints the elements of the subtree
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

// Helper for deep copying a subtree
// Creates a new subtree that is a deep copy of the given other node
SortedList* SortedList::_copy_nodes(const SortedList* otherNode) const {
    if (otherNode == nullptr) {
        return nullptr;
    }
    SortedList* new_node = new SortedList(otherNode->data);
    new_node->next = _copy_nodes(otherNode->next);
    return new_node;
}

// Helper for deep destruction of a subtree
// Deletes all nodes in the given subtree
void SortedList::_destroy_nodes(SortedList* current_node) {
    while (current_node != nullptr) {
        SortedList* next_node = current_node->next;
        current_node->next = nullptr;
        delete current_node;
        current_node = next_node;
    }
}

// Helper to get the last node of a list
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

// Default Constructor, initializes the list to an empty state
SortedList::SortedList() : data(0), next(nullptr), is_empty_head_flag(true) {}

// Destructor, cleans up all dynamic memory in the list
SortedList::~SortedList() {
    // Only destroy nodes if this object is not an empty head or if it has children
    if (!is_empty_head_flag) { 
        _destroy_nodes(this->next);
    }
    this->next = nullptr;
}

// Copy Constructor (Deep Copy), creates a new SortedList object that is a deep copy of other
SortedList::SortedList(const SortedList& other) : data(0), next(nullptr), is_empty_head_flag(true) {
    if (!other.isEmpty()) {
        this->data = other.data;
        this->next = _copy_nodes(other.next);
        this->is_empty_head_flag = false;
    }
}

// Assigns content to the current SortedList object
SortedList& SortedList::operator=(const SortedList& other) {
    if (this == &other) {
        return *this;
    }

    // Deallocate existing resources of the current list
    if (!is_empty_head_flag) {
        _destroy_nodes(this->next);
    }
    this->next = nullptr;

    // Copy data from other
    if (other.isEmpty()) {
        this->is_empty_head_flag = true;
        this->data = 0; // Default uninitialized value
    } else {
        this->is_empty_head_flag = false;
        this->data = other.data;
        this->next = _copy_nodes(other.next);
    }
    return *this;
}

// Check if the list is empty
bool SortedList::isEmpty() const {
    return is_empty_head_flag;
}

// Inserts a value into the list
void SortedList::insert(int value) {
    if (isEmpty()) {
        data = value;
        is_empty_head_flag = false; // List is no longer empty
    }
    else {
        if (value < this->data) {
            int old_data = this->data;
            SortedList* old_next = this->next;

            this->data = value; 
            this->next = new SortedList(old_data);
            this->next->next = old_next;
        }
        else {
            this->next = _insert_node(this->next, value);
        }
    }
}

// Removes a value from the list
bool SortedList::remove(int value) {
    bool removedFlag = false;
    if (!isEmpty() && data == value) {
        if (next == nullptr) {
            is_empty_head_flag = true;
            data = 0;
        }
        else {
            SortedList* old_next_node = next;
            data = old_next_node->data;
            next = old_next_node->next;
            old_next_node->next = nullptr;
            delete old_next_node;
        }
        removedFlag = true;
        return true;
    }
    // Search and remove from the rest of the list
    this->next = _remove_node(this->next, value, removedFlag);
    return removedFlag;
}

// Search for a value in the list
bool SortedList::search(int value) const {
    if (isEmpty()) {
        return false;
    }
    if (data == value) {
        return true;
    }
    if (value < data) {
        return false;
    }
    return _search_node(this->next, value);
}

// Print list elements
void SortedList::printList() const {
    if (isEmpty()) {
        std::cout << "List is empty.";
        return;
    }
    std::cout << data;
    if (next != nullptr) {
        std::cout << " ";
        _print_nodes(this->next);
    }
}

// Get the first item
int SortedList::getFirst() const {
    if (isEmpty()) {
        throw std::out_of_range("Attempted to get first element from an empty list.");
    }
    return data;
}


// --- Operators ---

// Concatenate 'SortedList' objects
SortedList SortedList::operator+(const SortedList& other) const {
    SortedList result_list;

    // Insert elements from the current list
    const SortedList* current_this = this;
    if (!current_this->isEmpty()) {
        result_list.insert(current_this->data);
        const SortedList* temp_node = current_this->next;
        while (temp_node != nullptr) {
            result_list.insert(temp_node->data);
            temp_node = temp_node->next;
        }
    }

    const SortedList* current_other = &other;
    if (!current_other->isEmpty()) {
        const SortedList* temp_other = &other;
        while (temp_other != nullptr && !temp_other->isEmpty()) {
            result_list.insert(temp_other->data);
            temp_other = temp_other->next;
        }
    }
    return result_list;
}


// Concatenate 'SortedList' object with an integer
SortedList SortedList::operator+(int value) const {
    SortedList result_list = *this;
    result_list.insert(value);
    return result_list;
}

SortedList operator+(int value, const SortedList& list) {
    return list + value;
}

// Push an integer to the list
SortedList& SortedList::operator+=(int value) {
    insert(value);
    return *this;
}

// Compares two lists
bool SortedList::operator==(const SortedList& other) const {
    bool this_is_empty = this->isEmpty();
    bool other_is_empty = other.isEmpty();

    if (this_is_empty && other_is_empty) {
        return true;
    }
    if (this_is_empty || other_is_empty) {
        return false;
    }
    return _are_equal_nodes(this, &other);
}

// Insert operator
std::ostream& operator<<(std::ostream& os, const SortedList& list) {
    if (list.isEmpty()) {
        os << "List is empty.";
    }
    else {
        list.printList();
    }
    return os;
}