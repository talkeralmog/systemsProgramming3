/****************************************
Assignment C++: 1
Author: Adar Shapira, ID: 209580208
        Almog Talker, ID: 322546680
*****************************************/
#ifndef MENU_H
#define MENU_H

#include "BinaryTree.h" 
#include "SortedList.h"
#include <iostream>
#include <limits>
#include <string>

class Menu {
private:
    BinaryTree tree;
    SortedList list;

    void displayMainMenu();
    void handleMainMenuSelection(int choice);

    void displayTreeMenu();
    void handleTreeMenuSelection(int choice);

    void displayListMenu();
    void handleListMenuSelection(int choice);

    int getIntegerInput(const std::string& prompt);

public:
    // Constructor
    Menu();
    void mainMenu();
};

#endif