#include "Menu.h"

// Constructor: Initializes the BinaryTree and SortedList objects.
Menu::Menu() : tree(), list() {
    // The 'tree' and 'list' objects are default-constructed,
    // making them conceptually empty as per their class definitions.
}

// Runs the main menu loop, displaying options and handling user choices.
void Menu::run() {
    int choice;
    do {
        displayMainMenu(); // Display the main menu options
        choice = getIntegerInput("Enter your choice: "); // Get user input
        handleMainMenuSelection(choice); // Process the user's choice
    } while (choice != 3); // Loop until the user chooses to exit (choice 3)
}

// Displays the options for the main menu.
void Menu::displayMainMenu() {
    std::cout << "\n--- Main Menu ---\n";
    std::cout << "1. Enter Binary Tree Menu\n";
    std::cout << "2. Enter Sorted List Menu\n";
    std::cout << "3. Exit Program\n";
    std::cout << "-----------------\n";
}

// Handles the user's selection from the main menu.
void Menu::handleMainMenuSelection(int choice) {
    switch (choice) {
        case 1: // Enter Binary Tree Menu
            std::cout << "Entering Binary Tree Menu...\n";
            int tree_choice;
            do {
                displayTreeMenu(); // Display tree menu options
                tree_choice = getIntegerInput("Enter your choice: "); // Get user input
                handleTreeMenuSelection(tree_choice); // Process choice
            } while (tree_choice != 5); // Loop until user chooses to exit tree menu (choice 5)
            std::cout << "Exiting Binary Tree Menu and returning to Main Menu.\n";
            break;
        case 2: // Enter Sorted List Menu
            std::cout << "Entering Sorted List Menu...\n";
            int list_choice;
            do {
                displayListMenu(); // Display list menu options
                list_choice = getIntegerInput("Enter your choice: "); // Get user input
                handleListMenuSelection(list_choice); // Process choice
            } while (list_choice != 5); // Loop until user chooses to exit list menu (choice 5)
            std::cout << "Exiting Sorted List Menu and returning to Main Menu.\n";
            break;
        case 3: // Exit Program
            std::cout << "Goodbye!\n";
            break;
        default: // Invalid choice
            std::cout << "Invalid choice. Please try again.\n";
            break;
    }
}

// Displays the options for the Binary Tree menu.
void Menu::displayTreeMenu() {
    std::cout << "\n--- Tree Menu ---\n";
    std::cout << "1. Add item to tree\n";
    std::cout << "2. Search item in tree\n";
    std::cout << "3. Find min value in tree\n";
    std::cout << "4. Print tree items in order\n";
    std::cout << "5. Exit menu and return to Main Menu\n";
    std::cout << "-----------------\n";
}

// Handles the user's selection from the Binary Tree menu.
void Menu::handleTreeMenuSelection(int choice) {
    int value;
    switch (choice) {
        case 1: // Add item to tree
            value = getIntegerInput("Enter value to add: ");
            tree.insert(value);
            std::cout << value << " added to tree.\n";
            break;
        case 2: // Search item in tree
            value = getIntegerInput("Enter value to search: ");
            if (tree.search(value)) {
                std::cout << value << " exists in the tree.\n";
            } else {
                std::cout << value << " does not exist in the tree.\n";
            }
            break;
        case 3: // Find min value in tree
            try {
                int min_val = tree.getMinValue();
                std::cout << "Minimum value in tree: " << min_val << "\n";
            } catch (const std::runtime_error& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
            break;
        case 4: // Print tree items in order
            std::cout << "Tree items (in-order): ";
            std::cout << tree << "\n"; // Using overloaded operator<<
            // tree.printInOrder(); // Alternative: using explicit print function
            // std::cout << "\n";
            break;
        case 5: // Exit menu
            break;
        default: // Invalid choice
            std::cout << "Invalid choice. Please try again.\n";
            break;
    }
}

// Displays the options for the Sorted List menu.
void Menu::displayListMenu() {
    std::cout << "\n--- List Menu ---\n";
    std::cout << "1. Add item to list\n";
    std::cout << "2. Remove item from list\n";
    std::cout << "3. Search item in list\n";
    std::cout << "4. Print list items\n";
    std::cout << "5. Exit menu and return to Main Menu\n";
    std::cout << "-----------------\n";
}

// Handles the user's selection from the Sorted List menu.
void Menu::handleListMenuSelection(int choice) {
    int value;
    switch (choice) {
        case 1: // Add item to list
            value = getIntegerInput("Enter value to add: ");
            list.insert(value);
            std::cout << value << " added to list.\n";
            break;
        case 2: // Remove item from list
            value = getIntegerInput("Enter value to remove: ");
            if (list.remove(value)) {
                std::cout << value << " removed from list.\n";
            } else {
                std::cout << value << " not found in list.\n";
            }
            break;
        case 3: // Search item in list
            value = getIntegerInput("Enter value to search: ");
            if (list.search(value)) {
                std::cout << value << " exists in the list.\n";
            } else {
                std::cout << value << " does not exist in the list.\n";
            }
            break;
        case 4: // Print list items
            std::cout << "List items: ";
            std::cout << list << "\n"; // Using overloaded operator<<
            // list.printList(); // Alternative: using explicit print function
            // std::cout << "\n";
            break;
        case 5: // Exit menu
            break;
        default: // Invalid choice
            std::cout << "Invalid choice. Please try again.\n";
            break;
    }
}

// Helper function to safely get an integer input from the user.
// Handles invalid input (non-integer) by clearing the error state and prompting again.
int Menu::getIntegerInput(const std::string& prompt) {
    int value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cout << "Invalid input. Please enter an integer: ";
        std::cin.clear(); // Clear error flags
        // Ignore the rest of the invalid input in the line
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    // Ignore any remaining characters in the input buffer after reading the integer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}