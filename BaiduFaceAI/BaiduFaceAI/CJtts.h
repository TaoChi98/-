#ifndef __CJTTS_H__
#define __CJTTS_H__
#include "../include/Jtts/jTTS_ML.h"
#include <string>
#include <vector>
using namespace std;
#		pragma comment(lib, "..\\include\\Jtts\\lib\\jTTS_ML.lib")

struct tSpeak
{
	tSpeak()
	{
		bUse = FALSE;
	}
	BOOL bUse;
	string strSpeak;
};
typedef vector<tSpeak> TSpeakArray;

DWORD WINAPI OnSpeakText(LPVOID pParam);

class CJTTS
{
public:
	static BOOL Open();
	static void Close();
	static void SpeakText(LPCTSTR lpszText);

protected:
	CJTTS();
	~CJTTS();
};

#endif