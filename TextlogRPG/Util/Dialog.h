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
	Dialog(int32_t id, const string& content, vector<Option*>&& options)
		: dialogId(id), content(content), options(move(options)) {	}
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


	static Dialog NewOption(int32_t id, string content, vector<Option*>&& options = {})
	{
		return Dialog(id, content, std::move(options));
	}

	bool HasOptions() const { return !options.empty(); }
	size_t OptionCount() const { return options.size(); }
	const vector<Option*>& GetOptions() const { return options; }
	Option* GetOption(int32_t idx) const { 	return options[idx]; }
	string GetText() const { return content; }

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
    
    static int ShowDialogs(const vector<Dialog>& dialogs, int32_t startIdx = 0) {  
        int32_t currentIdx = startIdx;  
        while (true) {  
            //현재 대화 출력
			const Dialog& dialog = dialogs[currentIdx];  
            cout << "\n===========================================\n" << endl;  
            cout << dialog.GetText() << endl; 

			//(선택지 있는 경우) 선택지 출력
            if (!dialog.GetOptions().empty()) {  
                for (Option* opt : dialog.GetOptions()) {  
                    cout << opt->GetIdx() << ". " << opt->GetText() << endl;  
                }  
                cout << "===========================================\n" << endl;  
                int16_t choice;  
                cin >> choice;  
                cin.ignore(1024, '\n');  
				//입력값과 일치하는 선택지 찾기
				const vector<Option*>& opts = dialog.GetOptions();
				vector<Option*>::const_iterator it = opts.end();
				for (vector<Option*>::const_iterator iter = opts.begin(); iter != opts.end(); ++iter) {
					if ((*iter)->GetIdx() == choice) {
						it = iter;
						break;
					}
				} 

                if (it != dialog.GetOptions().end()) 
				{  
                    currentIdx = (*it)->GetNextDialogId();  //다음 idx 대화로 이동
                }  
                else {  
                    // 잘못된 입력 처리  
					int32_t wrongIdx = -1;
					for (size_t i = 0; i < dialogs.size(); ++i) {
						if (dialogs[i].GetText().find("잘못된 선택") != string::npos) {
							wrongIdx = static_cast<int>(i);
							break;
						}
					}
					if (wrongIdx != -1)
						currentIdx = wrongIdx;
					else
						break;
                }  
            }  
            else {  
                cout << "===========================================\n" << endl;  
                break;  
            }  
        }  
        return currentIdx;  
    }
};