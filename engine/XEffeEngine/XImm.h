#ifndef _JIA_XIMM_
#define _JIA_XIMM_
#include "windows.h"
#include <string>
#include <imm.h>
#pragma comment(lib, "imm32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "ole32.lib")
namespace XE{

namespace XImm
{
	extern LRESULT inputMsgProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam,bool &end);
	extern bool getIsInputChange();
	extern std::string getImmDescription();
	extern std::string getImmFilename();
	extern void setCompositionPos(float x,float y);
	extern bool getIsCompositionStrChange();
	extern std::string getCompositionStr();
	extern bool getCompositionState();
	extern bool getIsCandidateListChange();
	extern bool getHaveCandidateList();
	extern int getCandidateListCount();
	extern std::string getCandidateListStr(int index);
	extern void showImmUI(bool hideOrShow);

	extern bool getIsImm();
	extern std::string getImeName();
	extern bool getIsEnglish();
	extern bool getIsFullShape();
	extern bool getIsSybol();
}
}
#endif