#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <iostream> // For std::ostream in operator<<
#include <stdexcept> // For std::out_of_range in getFirst()

// Forward declaration of SortedList class
class SortedList;

// Forward declaration of operator<< for friend declaration
std::ostream& operator<<(std::ostream& os, const SortedList& list);

class SortedList {
private:
    int data;
    SortedList* next;

    // Sentinel value to indicate an "empty" list state for the isEmpty() method,
    // assuming 0 is not a valid data point for a non-empty list.
    static const int EMPTY_LIST_SENTINEL = 0;

    // Private helper constructor for creating new nodes easily
    SortedList(int val);

    // Private helper for recursive insertion
    SortedList* _insert_node(SortedList* current_node, int value);
    // Private helper for recursive removal
    SortedList* _remove_node(SortedList* current_node, int value, bool& removed_flag);
    // Private helper for recursive search
    bool _search_node(const SortedList* current_node, int value) const;
    // Private helper for recursive print
    void _print_nodes(const SortedList* current_node) const; // Marked const
    // Private helper for deep copy (used in copy constructor and assignment operator)
    SortedList* _copy_nodes(const SortedList* other_node);
    // Private helper for deep destruction
    void _destroy_nodes(SortedList* current_node);
    // Private helper to get the last node for concatenation for efficient appending
    SortedList* _getLastNode(SortedList* current_node);
    // Private helper to check for equality recursively (for operator==)
    bool _are_equal_nodes(const SortedList* list1, const SortedList* list2) const;


public:
    // Constructor. Initializes to conceptually empty state or with a value.
    SortedList(); // Default constructor for an empty list head
    SortedList(int val); // Constructor for creating a node with a value

    // Destructor. Cleans up dynamically allocated nodes.
    ~SortedList();

    // Rule of Three/Five: Copy Constructor and Assignment Operator for deep copy
    SortedList(const SortedList& other);
    SortedList& operator=(const SortedList& other);


    // Public Members
    // Returns true if the list is empty (conceptually, based on sentinel data and null next).
    bool isEmpty() const;
    // Inserts a new element to the list while maintaining sorted order.
    void insert(int value);
    // Removes an element from the list. Returns true if removed, false otherwise.
    bool remove(int value);
    // Returns true if element exists in the list, false otherwise.
    bool search(int value) const;
    // Prints the values in ascending order.
    void printList() const;
    // Returns the first item in the list. Throws std::out_of_range if list is empty.
    int getFirst() const;

    // Operators
    // 1) Concatenate 'SortedList' objects. i.e. sl1 + sl2 returns sorted list with {sl1, sl2} items.
    SortedList operator+(const SortedList& other) const;

    // 2) Concatenate 'SortedList' object with an integer. i.e. sl1 + 3 or 3 + sl1 returns sorted list with {sl1, 3} items.
    SortedList operator+(int value) const;
    friend SortedList operator+(int value, const SortedList& list); // For 3 + sl1 syntax

    // 3) += - Pushes an integer to the list (uses insert function).
    SortedList& operator+=(int value);

    // 4) == - Compares two lists and returns true if they contain the same elements in the same order, and false otherwise.
    bool operator==(const SortedList& other) const;
    bool operator!=(const SortedList& other) const; // Added for completeness

    // 5) << - Insertion operator for easy printing.
    friend std::ostream& operator<<(std::ostream& os, const SortedList& list);
};

#endif // SORTED_LIST_H