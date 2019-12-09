#pragma once
#include <vector>

class CFileManager
{
public:
	CFileManager();
	~CFileManager();

public:
	static CString ChangeEngToChinese(CString &szChinese);//星期英文转中文
	static BOOL TraverseDir(CString& strDir, std::vector<CString>& vecFiles);//获取路径下的图片路径数组 350_测试部_李凯_男array
	static BOOL SplitStringWithString(CString &szString, char c, std::vector<CString>& szResultStringArray);//350_测试部_李凯_男

public:
	static CString SplitPunchTime(CString &szPunchTime);//分割打卡时间
	static CString SplitPunchOutTime(CString &szPunchTime);
	static CString UTF8_to_UNICODE(const char *utf8_string, int length);
	static void UNICODE_to_UTF8(const CString& unicodeString, std::string& str);

	static BOOL ComparePunchTime(CString szPunchTime, CString szCurrentTime);//比较打卡时间是否大于三分钟
	static int ComparePunchTimeWithLast(CString szLastTime, CString szCurrentTime);//比较打卡时间是否相隔五秒钟	
	static int ChangeTimeToNumber(CString szLastTime); //时间转成数字
	

};

