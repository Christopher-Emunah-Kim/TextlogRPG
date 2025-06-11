#pragma once
#include <string>

using namespace std;


class InputManager
{
private:
	InputManager() = default;


public:

    static InputManager& GetInstance();

    char GetCharInput();

    string GetLineInput();

    
};