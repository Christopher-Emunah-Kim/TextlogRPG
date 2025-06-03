//#pragma once
//#include "Option.h"
//
//class Option;
//
////Manage dialogue messages
//class Dialog {
//public:
//	Dialog(uint32 id, const string& content, vector<Option*>&& options)
//		: dialogId(id), content(content), options(move(options)) {
//	}
//	~Dialog() {
//		for (Option* opt : options) { delete opt; }
//		options.clear();
//	}
//
//private:
//    uint32 dialogId;
//    string content;
//    vector<Option*> options;
//
//
//public: 
//
//	bool HasOptions() const { return !options.empty(); }
//	size_t OptionCount() const { return options.size(); }
//	const vector<Option*>& GetOptions() const { return options; }
//	Option* GetOption(uint32 idx) const { 
//		if (idx < 0 || idx >= options.size())
//		{
//			return nullptr;
//		}
//		return options[idx];
//	}
//	string GetText() const { return content; }
//	string ToString() const
//	{
//		stringstream ss;
//		ss << content << '\n';
//
//		for (Option* option : options)
//		{
//			ss << to_string(dialogId) << ". " << content;
//
//			return ss.str();
//		}
//
//		return ss.str();
//	}
//
//
//	static Dialog NewOption(uint32 id, string content, vector<Option*>&& options = {})
//	{
//		return Dialog(id, content, std::move(options));
//	}
//
//	
//
//	void Display() const
//	{
//		Common::PauseAndClearScreen();
//		cout << "\n===========================================\n";
//		cout << content << "\n";
//		for (size_t i = 0; i < options.size(); ++i) {
//			std::cout << (i + 1) << ". " << options[i]->GetText() << "\n";
//		}
//		std::cout << "\n===========================================\n";
//		
//	}
//    
//    static int ShowDialogs(const vector<Dialog>& dialogs, uint32 startIdx = 0) 
//	{  
//        uint32 currentIdx = startIdx;  
//
//		if (dialogs.empty()) {
//			cout << "[Error] No dialogs available." << endl;
//			return -1;
//		}
//
//        while (true) {  
//            //현재 대화 출력
//			const Dialog& dialog = dialogs[currentIdx];  
//            cout << "\n===========================================\n" << endl;  
//            cout << dialog.GetText() << endl; 
//
//			//(선택지 있는 경우) 선택지 출력
//            if (dialog.GetOptions().empty() == false) 
//			{  
//                for (Option* opt : dialog.GetOptions()) 
//				{  
//                    cout << opt->GetIdx() << ". " << opt->GetText() << endl;  
//                }  
//                cout << "\n===========================================\n" << endl;  
//                uint16 choice;  
//                cin >> choice;  
//                cin.ignore(1024, '\n');  
//				//입력값과 일치하는 선택지 찾기
//				const vector<Option*>& opts = dialog.GetOptions();
//
//				vector<Option*>::const_iterator it = opts.end();
//				for (vector<Option*>::const_iterator iter = opts.begin(); iter != opts.end(); ++iter) {
//					if ((*iter)->GetIdx() == choice) {
//						it = iter;
//						break;
//					}
//				} 
//
//                if (it != dialog.GetOptions().end()) 
//				{  
//                    currentIdx = (*it)->GetNextDialogId();  //다음 idx 대화로 이동
//                }  
//                else 
//				{  
//                    // 잘못된 입력 처리  
//					uint32 wrongIdx = -1;
//					for (size_t i = 0; i < dialogs.size(); ++i) {
//						if (dialogs[i].GetText().find("잘못된 선택") != string::npos) {
//							wrongIdx = static_cast<int>(i);
//							break;
//						}
//					}
//
//					if (wrongIdx != -1)
//						currentIdx = wrongIdx;
//					else
//						break;
//                }  
//            }  
//            else {  
//                cout << "\n===========================================\n" << endl;  
//                break;  
//            }  
//        }  
//        return currentIdx;  
//    }
//
//	
//};