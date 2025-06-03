#pragma once

#include "Common.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;

class Dialogue {
public:
	Dialogue(uint32 id, const string& content)
		: dialogId(id), content(content) {
	}

	~Dialogue() = default;
	
private:
	uint32 dialogId;
	string content;

public:

	string GetText() const { return content; }
	uint32 GetId() const { return dialogId; }

	static Dialogue NewText(uint32 id, const string& content) {
		return Dialogue(id, content);
	}

	static void ShowDialogs(const vector<Dialogue>& dialogs) {
		for (const auto& dialog : dialogs) 
		{
			cout << "\n===========================================\n\n";
			cout << dialog.GetText() << "\n";
			cout << "\n===========================================\n";
			cout << "Enter 키를 눌러 계속 진행하세요.\n" << endl;
			cin.ignore(1024, '\n');
		}
		Common::PauseAndClearScreen();
	}

	static void ShowOption(const string& text)
	{
		cout << "\n===========================================\n\n";
		cout << text << "\n";
		cout << "\n==========================================="<<endl;
	}
};
