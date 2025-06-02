/****************************************
Assignment C++: 1
Author: Adar Shapira, ID: 209580208
        Almog Talker, ID: 322546680
*****************************************/
#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <iostream>
#include <stdexcept>

class SortedList;

// Forward declaration of operator<< for friend declaration
std::ostream& operator<<(std::ostream& os, const SortedList& list);

class SortedList {
private:
    int data;
    SortedList* next;
    bool is_empty_head_flag;

    // Helper for recursive insertion
    SortedList* _insert_node(SortedList* current_node, int value);

    // Helper for recursive removal
    SortedList* _remove_node(SortedList* current_node, int value, bool& removed_flag);

    // Helper for recursive search
    bool _search_node(const SortedList* current_node, int value) const;

    // Helper for recursive print
    void _print_nodes(const SortedList* current_node) const;

    // Helper for deep copy (used in copy constructor/assignment)
    SortedList* _copy_nodes(const SortedList* other_node) const;

    // Helper for deep destruction
    void _destroy_nodes(SortedList* current_node);

    // Helper to get the last node for concatenation for efficient appending
    SortedList* _getLastNode(SortedList* current_node);

    // Private helper to check for equality recursively (for operator==)
    bool _are_equal_nodes(const SortedList* list1, const SortedList* list2) const;


public:
    // Constructor
    SortedList();
    SortedList(int val);
    // Destructor
    ~SortedList();

    // Copy Constructor and Assignment Operator (deep copy)
    SortedList(const SortedList& other);
    SortedList& operator=(const SortedList& other);


    // Public Members
    // Returns true if the list is empty
    bool isEmpty() const;

    // Inserts a new element to the list
    void insert(int value);

    // Removes an element from the list
    bool remove(int value);

    // Returns true if element exists in the list, false otherwise
    bool search(int value) const;

    // Prints the values in ascending order
    void printList() const;

    // Returns the first item in the list. Throws std::out_of_range if list is empty.
    int getFirst() const;

    // Operators
    // Concatenate objects
    SortedList operator+(const SortedList& other) const;
    // Concatenateobject with an integer
    SortedList operator+(int value) const;
    friend SortedList operator+(int value, const SortedList& list);
    // Pushes an integer to the list (uses insert function)
    SortedList& operator+=(int value);
    // Compares two lists and returns true if they contain the same elements in the same order
    bool operator==(const SortedList& other) const;
    // Inserts operator for easy printing
    friend std::ostream& operator<<(std::ostream& os, const SortedList& list);
};

#endif // SORTED_LIST_H