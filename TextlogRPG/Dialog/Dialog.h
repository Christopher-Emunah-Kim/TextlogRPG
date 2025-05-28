#pragma once
#include "Option.h"

class Option;

//Manage dialogue messages
class Dialog {
private:
    int32_t dialogId;
    string content;
    vector<Option*> options;

public:
	Dialog(int32_t id, const string& content, vector<Option>&& options)
		: dialogId(id), content(content), options(std::move(options)) {	}
	~Dialog() {
		for (Option* opt : options) { delete opt; }
		options.clear();
	}
    
	string ToString() const
	{
		stringstream ss;
		ss << content << '\n';

		for (Option* option : options)
		{
			ss << to_string(dialogId) << ". " << content;

			return ss.str();
		}

		return ss.str();
	}


	static Dialog NewOption(int32_t id, string content, vector<Option>&& options = {})
	{
		return Dialog(id, content, std::move(options));
	}

	bool HasOptions() const { return !options.empty(); }
	size_t OptionCount() const { return options.size(); }
	Option* GetOption(int32_t idx) const { 	return options[idx]; }


	void Display() const
	{
		system("cls");
		cout << "\n===========================================\n";
		cout << content << "\n";
		for (size_t i = 0; i < options.size(); ++i) {
			std::cout << (i + 1) << ". " << options[i]->GetText() << "\n";
		}
		std::cout << "===========================================\n";
		Sleep(2000);
	}
    
};