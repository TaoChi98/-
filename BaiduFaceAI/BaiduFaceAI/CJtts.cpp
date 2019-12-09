#include "stdafx.h"
#include "CJtts.h"
HANDLE hMutex;
BOOL gbEnd;
TSpeakArray gSpeakArray;
HANDLE ghandle;
#define SPEAKNUM 30
string strText;

CJTTS::CJTTS()
{
}

CJTTS::~CJTTS()
{
}

BOOL CJTTS::Open()
{
	char g_szInitPath[_MAX_PATH];
	char g_szSerialNo[_MAX_PATH];
	JTTS_CONFIG g_config;
	memset(&g_config, 0, sizeof(JTTS_CONFIG));
	g_config.nCodePage = CODEPAGE_GB;
	g_config.nDigitMode = 0;
	g_config.nEngMode = 0;
	g_config.nPitch = 5;
	g_config.nSpeed = 5;
	g_config.nVolume = 5;
	g_config.nPuncMode = 0;
	g_config.wVersion = JTTS_VERSION4;
	g_config.nDomain = 0;
	g_config.nTagMode = 0;
	g_config.nVoiceStyle = 1;
	g_config.nBackAudio = 0;
	g_config.nBackAudioVolume = 50;
	g_config.wBackAudioFlag = 0;
	g_config.nVoiceBufSize = 0;
	g_config.nInsertInfoSize = 0;
	strcpy(g_config.szVoiceID, "84316E85-143E-4410-B00B-9DF681684C6C");
	memset(g_szInitPath, 0, sizeof(g_szInitPath));
	memset(g_szSerialNo, 0, sizeof(g_szSerialNo));
	ERRCODE err = jTTS_Init(g_szInitPath, g_szSerialNo);
	if (err != ERR_NONE)
	{
		return false;
	}
	// 预载当前音色
	jTTS_PreLoad(g_config.szVoiceID);
	// 设置当前属性
	jTTS_Set(&g_config);
	//互斥对象
	hMutex = CreateMutex(NULL, FALSE, NULL);
	ghandle = NULL;
	gbEnd = FALSE;
	for (int i = 0; i<SPEAKNUM; i++)
	{
		tSpeak tspeak;
		gSpeakArray.push_back(tspeak);
	}
	return true;
}

void CJTTS::Close()
{
	gbEnd = TRUE;
	WaitForSingleObject(ghandle, INFINITE);
	if (ghandle)
	{
		CloseHandle(ghandle);
		ghandle = NULL;
	}
	jTTS_End();
}

void CJTTS::SpeakText(LPCTSTR lpszText)
{
	//WaitForSingleObject(ghandle,INFINITE);
	int nsize = strlen((const char *)lpszText);
	char *text = new char[nsize + 1];
	memset(text, 0, nsize + 1);
	memcpy(text, lpszText, nsize);
	if (ghandle)
	{
		CloseHandle(ghandle);
		ghandle = NULL;
	}
	ghandle = CreateThread(NULL, 0, OnSpeakText, (LPVOID)text, 0, NULL);
}

DWORD WINAPI OnSpeakText(LPVOID pParam)
{
	char *text = (char *)pParam;
	WaitForSingleObject(hMutex, INFINITE);
	if (gbEnd)
	{
		delete text;
		text = NULL;
		ReleaseMutex(hMutex);//关闭
		return 1;
	}
	jTTS_Stop();
	jTTS_Play(text, 0);
	while (TRUE)
	{
		int nStatus = jTTS_GetStatus();
		if (nStatus == STATUS_IDLE || gbEnd)
		{
			delete text;
			text = NULL;
			ReleaseMutex(hMutex);//正常结束
			break;
		}
		Sleep(100);
	}
	return 1;
}
