#pragma once
#include <vector>

class CFileManager
{
public:
	CFileManager();
	~CFileManager();

public:
	static CString ChangeEngToChinese(CString &szChinese);//����Ӣ��ת����
	static BOOL TraverseDir(CString& strDir, std::vector<CString>& vecFiles);//��ȡ·���µ�ͼƬ·������ 350_���Բ�_�_��array
	static BOOL SplitStringWithString(CString &szString, char c, std::vector<CString>& szResultStringArray);//350_���Բ�_�_��

public:
	static CString SplitPunchTime(CString &szPunchTime);//�ָ��ʱ��
	static CString SplitPunchOutTime(CString &szPunchTime);
	static CString UTF8_to_UNICODE(const char *utf8_string, int length);
	static void UNICODE_to_UTF8(const CString& unicodeString, std::string& str);

	static BOOL ComparePunchTime(CString szPunchTime, CString szCurrentTime);//�Ƚϴ�ʱ���Ƿ����������
	static int ComparePunchTimeWithLast(CString szLastTime, CString szCurrentTime);//�Ƚϴ�ʱ���Ƿ����������	
	static int ChangeTimeToNumber(CString szLastTime); //ʱ��ת������
	

};

