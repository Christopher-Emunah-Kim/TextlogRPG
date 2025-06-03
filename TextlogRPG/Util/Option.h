#pragma once
#include "../Util/Common.h"


class Option {
public:
	Option(int32_t idx, int32_t nextDialogIdx, const string& text)
		: optionIdx(idx), nextDialogIdx(nextDialogIdx), text(text) {
	}

private:
    int32_t optionIdx;
    int32_t nextDialogIdx;
    string text;


public:
    string GetText() const { return text; }
	int32_t GetIdx() const { return optionIdx; }
    int32_t GetNextDialogId() const { return nextDialogIdx; }

};