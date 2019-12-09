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
	//确定是否是本公司的
	static BOOL CheckEmployeeInfo(CString &szEmployeeInfo);
	//天气
	static BOOL AnalysisWeatherInfo(std::vector<CString>& vecWeather);
	//打卡上传
	static BOOL GetPunchInfo(CString szEmployeeIndex, CString szTime, CString szType);
	//获取所有打卡时间
	static BOOL GetAllPunchTime(CString szEmployeeIndex, CString szDate, vector<CString> vecSzPunchTime, CString &szPunchInTime, CString &szPunchOutTime);
	//判断网络状态
	static BOOL ChangeNetConnect();

protected:
	//解析判断人员获取的返回
	static BOOL GetCheckFlag(string strResponse);
	//从网络获取天气信息
	static BOOL GetWeatherInfo(std::string &strWeather);
	//上传信息
	static BOOL Post(CString &szBody, string &strResponse);
	//解析打卡
	static BOOL AnalysisPunch(string &strResponse);
};

