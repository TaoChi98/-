#pragma once
#include "XMLBaseWnd.h"
#include "BaiduFaceAIInclude.h"

using namespace std;
using namespace cv;

class CMainWnd :
	public CXMLBaseWnd
{
public:
	explicit CMainWnd(LPCTSTR pszXMLPath);
	~CMainWnd(void);

protected:
	virtual void InitWindow();
	virtual void Notify(TNotifyUI& msg);

protected:
	virtual void OnClick(TNotifyUI& msg);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
	Mat frame;
	VideoCapture cap;
	BOOL m_bVideoOpen;
	BaiduFaceApi *api;
	std::vector<TrackFaceInfo> *track_info;
	CString m_szResult;
	std::string m_strPicName;
	CString m_szFileName;
	HANDLE m_Thread;;
	CString m_szCurTime;
	CString m_szCurDate;
	int m_bottomPicWidth;
	CString m_szCurTimeInter;
	CString m_szLastName;
	CString m_szLastTime;

private:
	BOOL parse_score(const std::string& res, std::string &strScore, std::string &strGroupID, std::string &strUserID);
	void ChangeTodayInfoLabel();
	void CheckFaceWithVideo();
	void Idetify();
	void ChangeBottomPic();
	void CreatLabel(int nLabelNum, vector<CString> vecPunchTime, vector<int> vec);
	void Punch();
	static DWORD WINAPI ProcessPunchEvent(LPVOID pParam);
	float GetRgbFaceScore(std::string strRes);
	BOOL m_bSleepDay;
};
