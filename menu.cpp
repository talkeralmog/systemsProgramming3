/****************************************
Assignment C++: 1
Author: Adar Shapira, ID: 209580208
		Almog Talker, ID: 322546680
*****************************************/
#include "Menu.h"

Menu::Menu() : tree(), list() {
}

void Menu::mainMenu() {
    int choice;
    do {
        displayMainMenu();
        choice = getIntegerInput("Enter your choice: ");
        handleMainMenuSelection(choice);
    } while (choice != 3);
}

void Menu::displayMainMenu() {
    std::cout << "Main Menu:\n";
    std::cout << "1. Binary Tree Menu\n";
    std::cout << "2. Sorted List Menu\n";
    std::cout << "3. Exit\n";
}

void Menu::handleMainMenuSelection(int choice) {
    switch (choice) {
        case 1: // Enter Binary Tree Menu
            int tree_choice;
            do {
                displayTreeMenu();
                tree_choice = getIntegerInput("Enter your choice: ");
                handleTreeMenuSelection(tree_choice);
            }
            while (tree_choice != 5);
            break;
        case 2: // Enter Sorted List Menu
            int list_choice;
            do {
                displayListMenu();
                list_choice = getIntegerInput("Enter your choice: ");
                handleListMenuSelection(list_choice);
            }
            while (list_choice != 5);
            break;
        case 3: // Exit Program
            break;
        default: // Invalid choice
            std::cout << "Invalid choice, please try again.\n";
            break;
    }
}

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
            tree = BinaryTree();
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

int Menu::getIntegerInput(const std::string& prompt) {
    int value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cout << "Invalid input, please enter an integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}