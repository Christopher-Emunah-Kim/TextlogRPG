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

   string	GetText() const { return content; }
   int32	GetId() const { return dialogId; }

   static Dialogue NewText(int32 id, const string& content) {
       return Dialogue(id, content);
   }

};
