#pragma once

#include "Common.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;

class Dialogue {
public:
   Dialogue(
       int32 id, const string& content)
       : dialogId(id), content(content) {
   }

   ~Dialogue() = default;
   
private:
   int32 dialogId;
   string content;

public:

   string GetText() const { return content; }
   int32 GetId() const { return dialogId; }

   static Dialogue NewText(int32 id, const string& content) {
       return Dialogue(id, content);
   }

   static void ShowDialogs(const vector<Dialogue>& dialogs) {
       for (vector<Dialogue>::const_iterator it = dialogs.begin(); it != dialogs.end(); ++it) 
       {
           const Dialogue& dialog = *it;
           cout << "\n===========================================\n\n";
           cout << dialog.GetText() << "\n";
           cout << "\n===========================================\n";
           cout << "Enter 키를 눌러 계속 진행하세요.\n" << endl;
           cin.ignore(1024, '\n');
       }
   }
};
