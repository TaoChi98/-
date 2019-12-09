#include "stdafx.h"
#include "HttpManager.h"
#include "FileManager.h"
#include "json\json.h"

CHttpManager::CHttpManager()
{
}

CHttpManager::~CHttpManager()
{
}

static size_t callback(void *ptr, size_t size, size_t nmemb, void *stream)
{
	((std::string*)stream)->append((char*)ptr, 0, size* nmemb);
	return size* nmemb;
}

BOOL CHttpManager::Post(CString &szBody, string &strResponse)
{
	CURL *curl;
	CURLcode result_code;
	int error_code = 0;
	curl = curl_easy_init();
	string strResult;
	if (curl)
	{
		//http://192.168.43.101/History/CustomERPInterface/get.html
		//http://192.168.43.2:80/CustomERPInterface/php/index.php
		string strUrl = "http://192.168.43.2:80/CustomERPInterface/php/index.php";
		curl_easy_setopt(curl, CURLOPT_URL, strUrl.data());
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		string strBody = "";
		CFileManager::UNICODE_to_UTF8(szBody, strBody);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strBody.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strResult);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/Users/zhu/CProjects/curlposttest.cookie");
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3L);
		result_code = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (result_code != CURLE_OK)
		{
			return FALSE;
		}
		strResponse = strResult;
		if (strResponse.empty())
		{
			return FALSE;
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CHttpManager::CheckEmployeeInfo(CString &szEmployeeInfo)
{
	//350_���Բ�_�_��
	std::vector<CString> strResultStringArray;
	BOOL bResult = CFileManager::SplitStringWithString(szEmployeeInfo, '_', strResultStringArray);
	if (!bResult)
	{
		return FALSE;
	}
	//��ȡ����Ϣ
	//�ж��Ƿ���ȷ  {"request":{"action":"CheckEmployeeInfo","content":{"employeeIndex":"288","username":"������","dept":"ϵͳ��"}}}
	CString szBody = _T("{\"request\":{\"action\":\"CheckEmployeeInfo\",\"content\":{\"employeeIndex\":\"") + strResultStringArray[0] + _T("\",\"username\":\"") + strResultStringArray[2] + _T("\",\"dept\":\"") + strResultStringArray[1] + _T("\"}}}");
	string strResponse;
	BOOL bPost = Post(szBody, strResponse);
	if (!bPost)
	{
		return FALSE;
	}
	//����
	BOOL bCheck = GetCheckFlag(strResponse);
	if (!bCheck)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CHttpManager::GetCheckFlag(string strResponse)
{
	//strResponse��Ϊ��
	Json::Reader reader;
	Json::Value value;
	reader.parse(strResponse, value);
	//{"response":{"errorCode":"0x0000", "time" : 1517877729, "action" : "CheckEmployeeInfo", "content" : {"CheckFlag":"1"}, "time_utc" : 1517877729}}
	Json::Value jsResponse = value["response"];
	Json::Value jsContent = jsResponse["content"];
	string strCheckFlag = jsContent["CheckFlag"].asString();
	if (strCheckFlag == "1")
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CHttpManager::GetPunchInfo(CString szEmployeeIndex, CString szTime, CString szType)
{
	//{ "request":{"action":"AddAttendanceInfo", "content" : {"employeeIndex":"171", "time" : "2018-01-18 17:34:58", "type" : "in"}} }
	string strResponse;
	CString szBody;
	szBody.Format(_T("{\"request\":{\"action\":\"AddAttendanceInfo\",\"content\":{\"employeeIndex\":\"%s\",\"time\":\"%s\",\"type\":\"%s\"}}}"), szEmployeeIndex, szTime, szType);
	BOOL bPost = Post(szBody, strResponse);
	if (bPost)
	{
		//����
		BOOL bPunch = AnalysisPunch(strResponse);
		if (bPunch)
		{
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}

BOOL CHttpManager::AnalysisPunch(string &strResponse)
{
	//{"response":{"errorCode":"0x0000","time":1517896118,"action":"AddAttendanceInfo","content":null,"time_utc":1517896118}}
	Json::Reader reader;
	Json::Value value;
	reader.parse(strResponse, value);
	Json::Value jsResponse = value["response"];
	string strErrorCode = jsResponse["errorCode"].asString();
	if (strErrorCode == "0x0000")
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CHttpManager::GetWeatherInfo(std::string &strWeather)
{
	CURL *curl;
	CURLcode result_code;
	int error_code = 0;
	curl = curl_easy_init();
	std::string strResult;
	if (curl)
	{
		string url = "http://api.yytianqi.com/forecast7d?city=CH220101&key=kjweh7shtibme4a9";
		//string url = "https://www.baidu.com";
		curl_easy_setopt(curl, CURLOPT_URL, url.data());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strResult);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
		result_code = curl_easy_perform(curl);
		if (result_code != CURLE_OK)
		{
			return FALSE;
		}
		strWeather = strResult;
		curl_easy_cleanup(curl);
		return TRUE;
	}
	return FALSE;
}

BOOL CHttpManager::AnalysisWeatherInfo(std::vector<CString>& vecWeather)
{
	string strWeather = "";
	GetWeatherInfo(strWeather);
	Json::Reader reader;
	Json::Value value;
	reader.parse(strWeather, value);
	int nCode = value["code"].asInt();
	if (nCode != 1)
	{
		return FALSE;
	}
	vecWeather.clear();
	//��������
	Json::Value list = value["data"]["list"][0];
	CString szToday1 = CString((list["qw1"].asString()).c_str());
	CString szToday2 = CString((list["qw2"].asString()).c_str());
	//vecWeather[0] [1]
	vecWeather.push_back(szToday1);
	vecWeather.push_back(szToday2);

	//��������
	string strTq1 = list["tq1"].asString();
	CString szDayWea = CFileManager::UTF8_to_UNICODE(strTq1.c_str(), strTq1.length());
	string strTq2 = list["tq2"].asString();
	CString szNigWea = CFileManager::UTF8_to_UNICODE(strTq2.c_str(), strTq2.length());
	CString szTodayWea;
	if (szDayWea == szNigWea)
	{
		szTodayWea = szDayWea;
	}
	else
	{
		szTodayWea = szDayWea + _T("ת") + szNigWea;
	}
	//vecWeather[2] ���� 
	vecWeather.push_back(szDayWea);
	//vecWeather[3] ����
	vecWeather.push_back(szTodayWea);

	//���� ����
	CString szWindPower = CFileManager::UTF8_to_UNICODE((list["fl1"].asString()).c_str(), (list["fl1"].asString()).length());
	CString szWindDec = CFileManager::UTF8_to_UNICODE((list["fx1"].asString()).c_str(), (list["fx1"].asString()).length());
	CString szWind = szWindDec + szWindPower;
	//vecWeather[4] ��
	vecWeather.push_back(szWind);

	//����Ԥ��
	Json::Value listTor = value["data"]["list"][1];
	CString  szTorDayWea = CFileManager::UTF8_to_UNICODE((listTor["tq1"].asString()).c_str(), (listTor["tq1"].asString()).length());
	//ҹ������
	CString szTorNigWea = CFileManager::UTF8_to_UNICODE((listTor["tq2"].asString()).c_str(), (listTor["tq2"].asString()).length());
	CString szTordayWea;
	if (szTorDayWea == szTorNigWea)
	{
		szTordayWea = szTorDayWea;
	}
	else
	{
		szTordayWea = szTorDayWea + _T("ת") + szTorNigWea;
	}
	//vecWeather[5] ���� 
	vecWeather.push_back(szTorDayWea);
	//vecWeather[6] һ��
	vecWeather.push_back(szTordayWea);

	//�������� [7] [8]
	CString szQw1 = CString((listTor["qw1"].asString()).c_str());
	CString szQw2 = CString((listTor["qw2"].asString()).c_str());
	vecWeather.push_back(szQw1);
	vecWeather.push_back(szQw2);

	return TRUE;
}

BOOL CHttpManager::ChangeNetConnect()
{
	CURL *curl;
	CURLcode result_code;
	int error_code = 0;
	curl = curl_easy_init();
	std::string strResult;
	if (curl)
	{
		string url = "https://www.baidu.com";
		curl_easy_setopt(curl, CURLOPT_URL, url.data());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strResult);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
		result_code = curl_easy_perform(curl);
		if (result_code == CURLE_COULDNT_RESOLVE_HOST)
		{
			return FALSE;
		}
		curl_easy_cleanup(curl);
		return TRUE;
	}
	return FALSE;
}

BOOL CHttpManager::GetAllPunchTime(CString szEmployeeIndex, CString szDate, vector<CString> vecSzPunchTime, CString &szPunchInTime, CString &szPunchOutTime)
{
	//�����򿨵ĸ���
	int nFacePunchCount = vecSzPunchTime.size();
	//���ݹ���ȥ��ȡ����
	//{"request":{"action":"QueryEmployeeAttendanceInfo", "content" : {"Time":"2019-02-26", "AttendanceID" : "041515"}}}
	CString szFileName = _T("../Skin/Config/Infomation.record"), szAttendanceID;
	GetPrivateProfileString(szEmployeeIndex, _T("AttendanceID"), _T("0"), szAttendanceID.GetBuffer(MAX_PATH), MAX_PATH, szFileName);

	CString szBody;
	szBody.Format(_T("{\"request\":{\"action\":\"QueryEmployeeAttendanceInfo\",\"content\":{\"Time\":\"%s\",\"AttendanceID\":\"%s\"}}}"), szDate, szAttendanceID);
	string strResponse;
	BOOL bPost = Post(szBody, strResponse);
	/*{"response":{"errorCode":"0x0000","time":1551168138,"action":"QueryEmployeeAttendanceInfo","content":[{"AttendanceID":"041515",
	"PunchedDateTime":"2019-02-26 08:30:00","RowGuid":"ac1ad5d9-395d-11e9-beaf-e069950dc677","ModifyDateTime":"2019-02-26 08:30:15","type":"in"}],"time_utc":1551168138}}*/
	if (bPost)
	{
		Json::Reader reader;
		Json::Value value;
		reader.parse(strResponse, value);
		Json::Value jsResponse = value["response"];
		std::string strErrorCode = jsResponse["errorCode"].asString();
		if (strErrorCode == "0x0000")
		{
			Json::Value jsContent = jsResponse["content"];
			int nPunchSize = jsContent.size(); //�򿨻��򿨵ĸ���
			if (nPunchSize > 0)
			{
				std::string strPunchTime = jsContent[0]["PunchedDateTime"].asString();
				CString szPuncTime1(strPunchTime.c_str());
				vecSzPunchTime.push_back(szPuncTime1);
				if (nPunchSize > 1)
				{
					strPunchTime = jsContent[nPunchSize - 1]["PunchedDateTime"].asString();
					CString szPuncTime2(strPunchTime.c_str());
					vecSzPunchTime.push_back(szPuncTime2);
				}
			}
			//2019-01-01 16:30:00 zhuyankun
			CString szFourThree = _T("2019-01-01 16:30:00");
			int nCom = CFileManager::ChangeTimeToNumber(szFourThree);
			//��ȡ���������
			vector<int> vecnTime;
			for (int i = 0; i < vecSzPunchTime.size(); i++)
			{
				CString szTime = vecSzPunchTime[i];
				int nTime = CFileManager::ChangeTimeToNumber(szTime);
				vecnTime.push_back(nTime);
			}
			std::vector<int>::iterator biggest = std::max_element(std::begin(vecnTime), std::end(vecnTime));
			int nMaxPos = std::distance(std::begin(vecnTime), biggest);
			auto smallest = std::min_element(std::begin(vecnTime), std::end(vecnTime));
			int nMinPos = std::distance(std::begin(vecnTime), smallest);
			//������1��
			if (nFacePunchCount == 1)
			{
				int nTime = vecnTime[0];
				if (nMinPos == 0 )
				{
					if (nTime > nCom) //out
					{
						szPunchInTime = _T("0");
						szPunchOutTime = _T("0");
					}
					else
					{
						szPunchOutTime = _T("0");
						szPunchInTime = vecSzPunchTime[0];
					}
				}
				else if (nMaxPos == 0)
				{
					if (nTime < nCom) //out
					{
						szPunchInTime = _T("0");
						szPunchOutTime = _T("0");
					}
					else
					{
						szPunchInTime = _T("0");
						szPunchOutTime = vecSzPunchTime[0];
					}
				}
				else
				{
					szPunchInTime = _T("0");
					szPunchOutTime = _T("0");
				}
			}
			else if (nFacePunchCount == 2) //��������
			{
				if (nMinPos == 0)
				{
					int nTime = vecnTime[0];
					if (nMaxPos == 1)
					{
						//2 face
						if (nTime > nCom) //out
						{
							szPunchInTime = _T("0");
							szPunchOutTime = vecSzPunchTime[1];
						}
						else
						{
							szPunchInTime = vecSzPunchTime[0];
							nTime = vecnTime[1];
							if (nTime > nCom)
							{
								szPunchOutTime = vecSzPunchTime[1];
							}
							else
							{
								szPunchOutTime = _T("0");
							}
						}
					}
					else
					{
						//1 face
						if (nTime > nCom) //out
						{
							szPunchInTime = _T("0");
							szPunchOutTime = _T("0");
						}
						else
						{
							szPunchOutTime = _T("0");
							szPunchInTime = vecSzPunchTime[0];
						}
					}
				}
				else if (nMinPos == 1)
				{
					int nTime = vecnTime[1];
					if (nMaxPos == 0)
					{
						//2 face
						if (nTime > nCom) //out
						{
							szPunchInTime = _T("0");
							szPunchOutTime = vecSzPunchTime[0];
						}
						else
						{
							szPunchInTime = vecSzPunchTime[1];
							nTime = vecnTime[0];
							if (nTime > nCom)
							{
								szPunchOutTime = vecSzPunchTime[0];
							}
							else
							{
								szPunchOutTime = _T("0");
							}
						}
					}
					else
					{
						//1 face
						if (nTime > nCom) //out
						{
							szPunchInTime = _T("0");
							szPunchOutTime = _T("0");
						}
						else
						{
							szPunchOutTime = _T("0");
							szPunchInTime = vecSzPunchTime[1];
						}
					}
				}
				else
				{
					szPunchInTime = _T("0");
					szPunchOutTime = _T("0");
					if (nMaxPos == 0 || nMaxPos == 1)
					{
						szPunchOutTime = vecSzPunchTime[nMaxPos];
					}
				}
			}
			else
			{
				szPunchInTime = _T("0");
				szPunchOutTime = _T("0");
			}
		}
	}
	return FALSE;
}