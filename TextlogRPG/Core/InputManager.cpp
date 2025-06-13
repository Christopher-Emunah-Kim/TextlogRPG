#include "InputManager.h"
#include <iostream>
#include <limits>
#include <stdio.h>
#include <conio.h>

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

//PauseAndSleep대신 입력 받기.

bool InputManager::HasInput() const
{
	//_kbhit() : 키입력을 인식해 0이 아닌 값을 반환.
	return _kbhit() != 0;
}

char InputManager::GetNonBlockingCharInput()
{
	if (_kbhit())
	{
		//_getch() : 0이 아닌 키입력값이 버퍼에 저장되면 콘솔에서 단일문자를 읽어옴.
		m_lastInput = static_cast<char>(_getch());
		m_hasInput = true;
		return m_lastInput;
	}

	m_hasInput = false;
	return 0;
}

void InputManager::FlushInputBuffer()
{
	while (_kbhit())
	{
		char trashWord = _getch();
	}
	m_hasInput = false;
	m_lastInput = 0;
}
