#include "stdafx.h"
#include "FileManager.h"
#include "assert.h"

CFileManager::CFileManager()
{
}


CFileManager::~CFileManager()
{
}

BOOL CFileManager::TraverseDir(CString& strDir, std::vector<CString>& vecFiles)  
{
	vecFiles.clear();
	CFileFind ff;
	strDir = strDir + _T("/*.*");
	BOOL ret = ff.FindFile(strDir);
	while (ret)
	{
		ret = ff.FindNextFile();
		if (ff.IsDirectory() && !ff.IsDots())
		{
			CString path = ff.GetFilePath();
			TraverseDir(path, vecFiles);
		}
		else if (!ff.IsDirectory() && !ff.IsDots())
		{
			CString name = ff.GetFilePath();
			vecFiles.push_back(name);
		}
	}
	int nSize = vecFiles.size();
	if (nSize > 0)
	{
		return TRUE;
	}
	return FALSE;
}


//分割字符串 获取信息数组
BOOL CFileManager::SplitStringWithString(CString &szString, char c, std::vector<CString>& szResultStringArray)
{
	if (szString.IsEmpty())
	{
		return FALSE;
	}
	int nFind = szString.Find(c);
	if (nFind == -1)
	{
		return FALSE;
	}
	//350_测试部_李凯_男
	CString szNum = szString.Left(nFind);

	//测试部_李凯_男
	szString = szString.Mid(nFind + 1, szString.GetLength() - nFind);
	nFind = szString.Find(c);
	if (nFind == -1)
	{
		return FALSE;
	}
	CString szEmployee = szString.Left(nFind);

	//李凯_男
	szString = szString.Mid(nFind + 1, szString.GetLength() - nFind);
	nFind = szString.Find(c);
	if (nFind == -1)
	{
		return FALSE;
	}
	CString szName = szString.Left(nFind);
	//男
	CString szSex = szString.Mid(nFind + 1, szString.GetLength() - nFind);
	szResultStringArray.clear();
	szResultStringArray.push_back(szNum);
	szResultStringArray.push_back(szEmployee);
	szResultStringArray.push_back(szName);
	szResultStringArray.push_back(szSex);
	if (szResultStringArray.size() == 0)
	{
		return FALSE;
	}
	return TRUE;
}

//中文转utf-8
void CFileManager::UNICODE_to_UTF8(const CString& unicodeString, std::string& str)
{
	int stringLength = ::WideCharToMultiByte(CP_UTF8, NULL, unicodeString, wcslen(unicodeString), NULL, 0, NULL, NULL);
	char* buffer = new char[stringLength + 1];
	::WideCharToMultiByte(CP_UTF8, NULL, unicodeString, wcslen(unicodeString), buffer, stringLength, NULL, NULL);
	buffer[stringLength] = '\0';
	str = buffer;
	delete[] buffer;
}

//utf-8转成中文
CString CFileManager::UTF8_to_UNICODE(const char *utf8_string, int length)
{
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, utf8_string, length, NULL, 0);
	wchar_t* wszString = new wchar_t[wcsLen + 1];
	::MultiByteToWideChar(CP_UTF8, NULL, utf8_string, length, wszString, wcsLen);
	wszString[wcsLen] = '\0';
	CString unicodeText(wszString);
	delete[] wszString;
	return unicodeText;
}

CString CFileManager::ChangeEngToChinese(CString &szChinese)
{
	if (szChinese == _T("Monday"))
	{
		szChinese = _T("星期一");
	}
	else if (szChinese == _T("Tuesday"))
	{
		szChinese = _T("星期二");
	}
	else if (szChinese == _T("Wednesday"))
	{
		szChinese = _T("星期三");
	}
	else if (szChinese == _T("Thursday"))
	{
		szChinese = _T("星期四");
	}
	else if (szChinese == _T("Friday"))
	{
		szChinese = _T("星期五");
	}
	else if (szChinese == _T("Saturday"))
	{
		szChinese = _T("星期六");
	}
	else if (szChinese == _T("Sunday"))
	{
		szChinese = _T("星期日");
	}
	return szChinese;
}

CString CFileManager::SplitPunchTime(CString &szPunchTime)
{
	CString szType;
	assert(!szPunchTime.IsEmpty());
	int nPos1 = szPunchTime.Find(':');
	assert(nPos1 != 0);
	//14:11:11   2  5  7
	CString szHour = szPunchTime.Mid(0, nPos1);
	int nHour = _ttoi(szHour);
	int nPos2 = szPunchTime.ReverseFind(_T(':'));
	CString szMin = szPunchTime.Mid(nPos1 + 1, nPos2 - nPos1 - 1);
	int nMid = _ttoi(szMin);
	if (nHour < 17 || (nHour==17 && nMid<=30))
	{
		szType = _T("in");
	}
	else
	{
		szType = _T("out");
	}
	return szType;
}

CString CFileManager::SplitPunchOutTime(CString &szPunchTime)
{
	CString szType;
	bool b = szPunchTime.IsEmpty();
	assert(!szPunchTime.IsEmpty());
	CStringA szTime = (CStringA)szPunchTime;
	CStringA szHour = szTime.Right(8);
	CString szTimes = (CString)szHour;
	int nHour = _ttoi(szTimes);
	if (nHour >= 23)
	{
		szType = _T("out");
	}
	else
	{
		szType = _T("in");
	}
	return szType;
}

BOOL CFileManager::ComparePunchTime(CString szPunchTime, CString szCurrentTime)
{
	CStringA szTime = (CStringA)szPunchTime;
	CStringA szCurTime = (CStringA)szCurrentTime;
	if (szTime.IsEmpty() || szCurTime.IsEmpty())
	{
		return FALSE;
	}
	int nPos = szTime.Find(':');
	if (nPos < 2)
	{
		return FALSE;
	}
	CStringA szHour = szTime.Mid(nPos - 2, 2);
	CStringA szMin = szTime.Mid(nPos + 1, 2);
	int nHour = _ttoi((CString)szHour);
	int nMin = _ttoi((CString)szMin);
	int nTime = nHour * 60 + nMin;

	nPos = szCurTime.Find(':');
	if (nPos < 2)
	{
		return FALSE;
	}
	szHour = szCurTime.Mid(nPos - 2, 2);
	szMin = szCurTime.Mid(nPos + 1, 2);
	nHour = _ttoi((CString)szHour);
	nMin = _ttoi((CString)szMin);
	int nTimes = nHour * 60 + nMin;
	int n = nTimes - nTime;
	if (n>1)
	{
		return TRUE;
	}
	return FALSE;
}

int CFileManager::ComparePunchTimeWithLast(CString szLastTime, CString szCurrentTime)
{
	CStringA szTime = (CStringA)szLastTime;
	CStringA szCurTime = (CStringA)szCurrentTime;
	if (szTime.IsEmpty() || szCurTime.IsEmpty())
	{
		return FALSE;
	}
	int nPos = szTime.Find(':');
	if (nPos < 2)
	{
		return FALSE;
	}
	CStringA szHour = szTime.Mid(nPos - 2, 2);
	CStringA szMin = szTime.Mid(nPos + 1, 2);
	CStringA szSecond = szTime.Mid(nPos + 4, 2);
	int nHour = _ttoi((CString)szHour);
	int nMin = _ttoi((CString)szMin);
	int nSecond = _ttoi((CString)szSecond);
	int nTime = nHour * 3600 + nMin * 60 + nSecond;

	nPos = szCurTime.Find(':');
	if (nPos < 2)
	{
		return FALSE;
	}
	szHour = szCurTime.Mid(nPos - 2, 2);
	szMin = szCurTime.Mid(nPos + 1, 2);
	szSecond = szCurTime.Mid(nPos + 4, 2);
	nHour = _ttoi((CString)szHour);
	nMin = _ttoi((CString)szMin);
	nSecond = _ttoi((CString)szSecond);
	int nTimes = nHour * 3600 + nMin * 60 + nSecond;
	int n = nTimes - nTime;
	return n;
}

int CFileManager::ChangeTimeToNumber(CString szLastTime)
{
	CStringA szTime = (CStringA)szLastTime;
	if (szTime.IsEmpty())
	{
		return FALSE;
	}
	int nPos = szTime.Find(':');
	if (nPos < 2)
	{
		return FALSE;
	}
	CStringA szHour = szTime.Mid(nPos - 2, 2);
	CStringA szMin = szTime.Mid(nPos + 1, 2);
	CStringA szSecond = szTime.Mid(nPos + 4, 2);
	int nHour = _ttoi((CString)szHour);
	int nMin = _ttoi((CString)szMin);
	int nSecond = _ttoi((CString)szSecond);
	int nTime = nHour * 3600 + nMin * 60 + nSecond;
	return nTime;
}