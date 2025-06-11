#include "InputManager.h"
#include <iostream>
#include <limits>

InputManager& InputManager::GetInstance()
{
    static InputManager instance;

    return instance;
}

char InputManager::GetCharInput()
{
    char ch;
    cin >> ch;
    cin.ignore(1024, '\n'); 

    return ch;
}

string InputManager::GetLineInput()
{
    string line;
    getline(std::cin, line);

    return line;
}