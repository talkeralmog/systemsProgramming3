/****************************************
Assignment C++: 1
Author: Adar Shapira, ID: 209580208
		Almog Talker, ID: 322546680
*****************************************/
#include "Menu.h"

// Constructor: Initializes the BinaryTree and SortedList objects.
Menu::Menu() : tree(), list() {
    // The 'tree' and 'list' objects are default-constructed,
    // making them conceptually empty as per their class definitions.
}

// Runs the main menu loop, displaying options and handling user choices.
void Menu::mainMenu() {
    int choice;
    do {
        displayMainMenu(); // Display the main menu options
        choice = getIntegerInput("Enter your choice: "); // Get user input
        handleMainMenuSelection(choice); // Process the user's choice
    } while (choice != 3); // Loop until the user chooses to exit (choice 3)
}

// Displays the options for the main menu.
void Menu::displayMainMenu() {
    std::cout << "Main Menu:\n";
    std::cout << "1. Binary Tree Menu\n";
    std::cout << "2. Sorted List Menu\n";
    std::cout << "3. Exit\n";
}

// Handles the user's selection from the main menu.
void Menu::handleMainMenuSelection(int choice) {
    switch (choice) {
        case 1: // Enter Binary Tree Menu
            int tree_choice;
            do {
                displayTreeMenu(); // Display tree menu options
                tree_choice = getIntegerInput("Enter your choice: "); // Get user input
                handleTreeMenuSelection(tree_choice); // Process choice
            } while (tree_choice != 5); // Loop until user chooses to exit tree menu (choice 5)
            break;
        case 2: // Enter Sorted List Menu
            int list_choice;
            do {
                displayListMenu(); // Display list menu options
                list_choice = getIntegerInput("Enter your choice: "); // Get user input
                handleListMenuSelection(list_choice); // Process choice
            } while (list_choice != 5); // Loop until user chooses to exit list menu (choice 5)
            break;
        case 3: // Exit Program
            break;
        default: // Invalid choice
            std::cout << "Invalid choice, please try again.\n";
            break;
    }
}

// Displays the options for the Binary Tree menu.
void Menu::displayTreeMenu() {
    std::cout << "Binary Tree Menu:\n";
    std::cout << "1. Add value to tree\n";
    std::cout << "2. Search value in tree\n";
    std::cout << "3. Delete tree\n";
    std::cout << "4. Print tree\n";
    std::cout << "5. Back to main menu\n";
}

// Handles the user's selection from the Binary Tree menu.
void Menu::handleTreeMenuSelection(int choice) {
    int value;
    switch (choice) {
        case 1: // Add item to tree
            value = getIntegerInput("Enter value to add: ");
            tree.insert(value);
            break;
        case 2: // Search item in tree
            if (tree.isEmpty()) {
                std::cout << "Tree is empty.\n";
                break;
            }
            value = getIntegerInput("Enter value to search: ");
            if (tree.search(value)) {
                std::cout << "Value found in tree.\n";
            } else {
                std::cout << "Value not found in tree.\n";
            }
            break;
        case 3: // Delete tree
            tree = BinaryTree();  // Re-initialize tree (old one is destructed)
   			std::cout << "Tree deleted.\n";
    		break;
        case 4: // Print tree items in order
            if (tree.isEmpty()) {
                std::cout << "Tree is empty.\n";
            } else {
                std::cout << "Tree values in order: ";
                std::cout << tree << "\n"; // Using overloaded operator<<
            }
            break;
        case 5: // Exit menu
            break;
        default: // Invalid choice
            std::cout << "Invalid choice, please try again.\n";
            break;
    }
}

// Displays the options for the Sorted List menu.
void Menu::displayListMenu() {
    std::cout << "Sorted List Menu:\n";
    std::cout << "1. Add value to list\n";
    std::cout << "2. Remove value from list\n";
    std::cout << "3. Search value in list\n";
    std::cout << "4. Print list\n";
    std::cout << "5. Back to main menu\n";
}

// Handles the user's selection from the Sorted List menu.
void Menu::handleListMenuSelection(int choice) {
    int value;
    switch (choice) {
        case 1: // Add item to list
            value = getIntegerInput("Enter value to add: ");
            list.insert(value);
            break;
        case 2: // Remove item from list
            if (list.isEmpty()) {
                std::cout << "List is empty.\n";
                break;
            }
            value = getIntegerInput("Enter value to remove: ");
            if (list.remove(value)) {
                std::cout << "Value removed.\n";
            } else {
                std::cout << "Value not found in list.\n";
            }
            break;
        case 3: // Search item in list
            if (list.isEmpty()) {
                std::cout << "List is empty.\n";
                break;
            }
            value = getIntegerInput("Enter value to search: ");
            if (list.search(value)) {
                std::cout << "Value found in list.\n";
            } else {
                std::cout << "Value not found in list.\n";
            }
            break;
        case 4: // Print list items
            if (list.isEmpty()) {
                std::cout << "List is empty.\n";
                break;
            }
            std::cout << "List values: ";
            std::cout << list << "\n"; // Using overloaded operator<<
            break;
        case 5: // Exit menu
            break;
        default: // Invalid choice
            std::cout << "Invalid choice, please try again.\n";
            break;
    }
}

// Helper function to safely get an integer input from the user.
// Handles invalid input (non-integer) by clearing the error state and prompting again.
int Menu::getIntegerInput(const std::string& prompt) {
    int value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cout << "Invalid input, please enter an integer: ";
        std::cin.clear(); // Clear error flags
        // Ignore the rest of the invalid input in the line
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    // Ignore any remaining characters in the input buffer after reading the integer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}