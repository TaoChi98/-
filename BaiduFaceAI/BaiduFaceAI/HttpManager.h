#pragma once
#include "MainWnd.h"
#include <string.h>
using namespace std;

class CHttpManager
{
public:
	CHttpManager();
	~CHttpManager();

public:
	//ȷ���Ƿ��Ǳ���˾��
	static BOOL CheckEmployeeInfo(CString &szEmployeeInfo);
	//����
	static BOOL AnalysisWeatherInfo(std::vector<CString>& vecWeather);
	//���ϴ�
	static BOOL GetPunchInfo(CString szEmployeeIndex, CString szTime, CString szType);
	//��ȡ���д�ʱ��
	static BOOL GetAllPunchTime(CString szEmployeeIndex, CString szDate, vector<CString> vecSzPunchTime, CString &szPunchInTime, CString &szPunchOutTime);
	//�ж�����״̬
	static BOOL ChangeNetConnect();

protected:
	//�����ж���Ա��ȡ�ķ���
	static BOOL GetCheckFlag(string strResponse);
	//�������ȡ������Ϣ
	static BOOL GetWeatherInfo(std::string &strWeather);
	//�ϴ���Ϣ
	static BOOL Post(CString &szBody, string &strResponse);
	//������
	static BOOL AnalysisPunch(string &strResponse);
};

