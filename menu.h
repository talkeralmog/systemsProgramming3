#ifndef MENU_H
#define MENU_H

#include "BinarySearchTree.h" // Includes the header file for BinaryTree
#include "SortedList.h"       // Includes the header file for SortedList
#include <iostream>
#include <limits> // For std::numeric_limits
#include <string>

class Menu {
private:
    BinaryTree tree;    // An object of the BinaryTree class
    SortedList list;    // An object of the SortedList class (acts as the head/first node)

    // Private menu display functions
    void displayMainMenu();
    void handleMainMenuSelection(int choice);

    void displayTreeMenu();
    void handleTreeMenuSelection(int choice);

    void displayListMenu();
    void handleListMenuSelection(int choice);

    // Helper function to get integer input safely from the user
    int getIntegerInput(const std::string& prompt);

public:
    // Constructor
    Menu();
    // Runs the main menu loop
    void run();
};

#endif // MENU_H