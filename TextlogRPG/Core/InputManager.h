#pragma once
#include <string>

using namespace std;


class InputManager
{
private:
	InputManager() = default;

private:
	bool	m_hasInput = false;
	char	m_lastInput = 0;

public:

    static InputManager&	GetInstance();

    char	GetCharInput();
    string	GetLineInput();
	bool	HasInput() const;
	char	GetNonBlockingCharInput();
	void	FlushInputBuffer();
    
};