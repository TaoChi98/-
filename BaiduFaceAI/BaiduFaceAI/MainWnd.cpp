#include "stdafx.h"
#include "MainWnd.h"
#include <time.h>
#include <stdio.h>   
#include <sys/timeb.h>
#include <sys/types.h>
#include "liveness.h"
#include "cv_help.h"
#include "json\json.h"
#include "FileManager.h"
#include "HttpManager.h"
#include "CJtts.h"

#define NS_VIDEO				10000
#define NS_IDENTIFY				10001
#define NS_TODAY				10002
#define NS_CHANGEBOTTOM			10003
#define NSTIMER_VIDEO			50
#define NSTIMER_CHANGETIMER		1000
#define NSTIMER_CHANGETIMERS	200

CMainWnd::CMainWnd( LPCTSTR pszXMLPath) : CXMLBaseWnd(pszXMLPath)
{
	m_bVideoOpen = FALSE;
	m_szResult = "";
	m_strPicName = "";
	m_szCurTime = _T("");
	m_szCurDate = _T("");
	m_szLastTime = _T("00:00:00");
	m_szCurTimeInter = _T("打卡成功");
	m_bottomPicWidth = 150;
	m_bSleepDay = FALSE;
}

CMainWnd::~CMainWnd(void)
{
}

void CMainWnd::InitWindow()
{
	//SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	//左边时间
	::SetTimer(GetHWND(), NS_TODAY, NSTIMER_CHANGETIMERS, NULL);
	//下边六张照片
	//::SetTimer(GetHWND(), NS_CHANGEBOTTOM, NSTIMER_CHANGETIMER, NULL);
	//上传打卡
	//m_Thread = ::CreateThread(NULL, 0, ProcessPunchEvent, this, 0, NULL);
	cap.open(0);
	if (cap.isOpened())
	{
		cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
		cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
		m_bVideoOpen = TRUE;
	}
	//检测人脸
	::SetTimer(GetHWND(), NS_VIDEO, NSTIMER_VIDEO, NULL);
	//识别人脸
	::SetTimer(GetHWND(), NS_IDENTIFY, NSTIMER_VIDEO, NULL);

	api = new BaiduFaceApi();
	bool id_card = false;
	api->sdk_init(id_card);
	api->set_min_face_size(30);
	track_info = new std::vector<TrackFaceInfo>();
	track_info->clear();
	
	//初始化语音播报
	BOOL bOpen = CJTTS::Open();
}

void CMainWnd::Notify(TNotifyUI& msg)
{
	__super::Notify(msg);
}

void CMainWnd::OnClick(TNotifyUI& msg)
{
	if (msg.pSender->GetName() == _T("closebtn"))
	{
		CJTTS::Close();
	}
	__super::OnClick(msg);
}

LRESULT CMainWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT lRes = 0;
	bHandled = FALSE;
	switch (uMsg)
	{
		case WM_TIMER:
		{
			if (wParam == NS_VIDEO)
			{
				CheckFaceWithVideo();
			}
			else if(wParam == NS_IDENTIFY)
			{
				Idetify();
			}
			else if (wParam == NS_TODAY)
			{
				ChangeTodayInfoLabel();
			}
			else if (wParam == NS_CHANGEBOTTOM)
			{
				ChangeBottomPic();
			}
		}
		break;
	}
	return 0;
}

BOOL CMainWnd::parse_score(const std::string& res, std::string &strScore, std::string &strGroupID, std::string &strUserID)
{
	float score = 0;
	if (res.length() > 0)
	{
		// 若出现json::reader编译不过，请用下面代码
		Json::Value root;
		Json::Reader reader;
		if (reader.parse(res, root))
		{
			int err = root["errno"].asInt();
			if (err == 0)
			{
				Json::Value result = root["data"];
				if (result.size() > 0)
				{
					result = result["result"][0];
					std::string sss = result["score"].asString();
					score = atof(sss.c_str());
					if (score >= 85) //分数的阈值
					{
						strScore = sss;
						strGroupID = result["group_id"].asString();
						strUserID = result["user_id"].asString();
						return TRUE;
					}
					return FALSE;
				}
			}
			else
			{
				return FALSE;
			}
		}
	}
	return FALSE;
}

//识别
void CMainWnd::CheckFaceWithVideo()
{
	if (m_bVideoOpen)
	{
		struct timeb t;
		ftime(&t);
		long long start = 1000 * t.time + t.millitm;
		CString szPicCount;
		szPicCount.Format(_T("../Skin/VideoPic/%lld.png"), start);
		std::string strPicName = CT2A(szPicCount.GetBuffer());
		cap >> frame;
		if (frame.empty())
		{
			m_bVideoOpen = FALSE;
		}
		//没秒检测4到5张
		if (start % 5 == 0)
		{
			track_info->clear();
			//默认检测一个人脸
			int size = api->track(track_info, frame, 1);
			if (size > 0)
			{
				std::string strRes = api->rgb_liveness_check(frame);
				//活体识别暂不使用,本身就有bug,必须人脸大小大于144
				//float fScore = GetRgbFaceScore(strRes);
				float fScore = 0.6;
				if (fScore < 0.0)
				{
				}
				else //>0.8判断为活体
				{
					TrackFaceInfo info = track_info->at(0);
					FaceInfo box = info.box;
					int nLeft = box.mCenter_x - box.mWidth / 2;
					int nRight = box.mCenter_x + box.mWidth / 2;
					//人脸的范围
					if (box.mWidth > 100 && nLeft > 150 && nRight < 580)
					{
						//确保有人脸
						const char *chResult = api->identify(frame, "crearo", "", 1);
						std::string strResult = chResult;
						std::string strScore, strGroupID, strUserID;
						BOOL bFace = parse_score(strResult, strScore, strGroupID, strUserID);
						if (bFace)
						{
							//人脸识别 
							m_strPicName = strPicName;
							m_szResult = (CString)chResult;
						}
					}
				}
			}
		}

		imwrite(strPicName, frame);
		CLabelUI *pVideoCapLabel = static_cast<CLabelUI *>(m_PaintManager.FindControl(_T("videocaplabel")));
		if (pVideoCapLabel)
		{
			CDuiString szBkImage = pVideoCapLabel->GetBkImage();
			pVideoCapLabel->GetManager()->RemoveImage(szBkImage);
			pVideoCapLabel->SetBkImage(szPicCount); 
		}
		frame.release();
		//删除每次存储的照片，有可能删除不完整，暂不处理
		DeleteFile(szPicCount);
	}
	else
	{
		cap.open(0);
		if (cap.isOpened())
		{
			m_bVideoOpen = TRUE;
		}
	}
}

//解析
void CMainWnd::Idetify()
{
	if (!m_szResult.IsEmpty() && !m_strPicName.empty())
	{
		//解析
		std::string strResult = CT2A(m_szResult.GetBuffer());
		std::string strScore, strGroupID, strUserID;
		BOOL bFace = parse_score(strResult, strScore, strGroupID, strUserID);
		if (bFace)
		{	
			CString szBkImages(m_strPicName.c_str());
			//操作完成之后
			//抓拍照片
			CVerticalLayoutUI *pFaceV = static_cast<CVerticalLayoutUI *>(m_PaintManager.FindControl(_T("videoVerticalLayout")));
			if (pFaceV)
			{
				pFaceV->RemoveAll();
				CLabelUI *pCompareLabel = new CLabelUI();
				pCompareLabel->SetFloat(true);
				pCompareLabel->SetAttribute(_T("pos"), _T("0,0,170,280"));
				pCompareLabel->SetBkImage(szBkImages);
				pFaceV->Add(pCompareLabel);
			}

			//对比图片
			CString szInformation(strUserID.c_str());
			CString szComparePicName = _T("../Skin/AllPeoPicture/") + szInformation + _T(".jpg");
			//创建label
			CVerticalLayoutUI *pCompareV = static_cast<CVerticalLayoutUI *>(m_PaintManager.FindControl(_T("compareVerticalLayout")));
			if (pCompareV)
			{
				pCompareV->RemoveAll();
				CLabelUI *pCompareLabel = new CLabelUI();
				pCompareLabel->SetFloat(true);
				pCompareLabel->SetAttribute(_T("pos"), _T("0,0,170,280"));
				pCompareLabel->SetBkImage(szComparePicName);
				pCompareV->Add(pCompareLabel);
			}

			CVerticalLayoutUI *pComInfoV = static_cast<CVerticalLayoutUI *>(m_PaintManager.FindControl(_T("FaceIcon_Success")));
			if (pCompareV)
			{
				pComInfoV->SetVisible(true);
			}

			//工号
			CString szEmployIndex(strUserID.c_str());
			CLabelUI *pEmplyLabel = static_cast<CLabelUI *>(m_PaintManager.FindControl(_T("EmployLabel")));
			if (pEmplyLabel)
			{
				pEmplyLabel->SetText(szEmployIndex);
			}

			//根据工号查信息
			//时间
			CString szTime = m_szCurTime;
			//显示打卡时间
			CLabelUI *pPunchTimeLabel = static_cast<CLabelUI *>(m_PaintManager.FindControl(_T("PunchTimeLabel")));
			if (pPunchTimeLabel)
			{
				pPunchTimeLabel->SetText(szTime);
			}
			
			//日期
			CString szDate = m_szCurDate;
			//上传打卡的时间
			CString szPunchTime = szDate + _T(" ") + szTime;

			//打卡状态
			CLabelUI *pStateLabel = static_cast<CLabelUI *>(m_PaintManager.FindControl(_T("punchStateLabel")));
			if (pStateLabel)
			{
				pStateLabel->SetVisible(true);
			}
			//笑脸
			CLabelUI *pIconLabel = static_cast<CLabelUI *>(m_PaintManager.FindControl(_T("IconLabel")));
			if (pIconLabel)
			{
				pIconLabel->SetVisible(true);
			}

			CString szInfoFileName = _T("../Skin/Config/Infomation.record"), szName, szDepartment;
			GetPrivateProfileString(szEmployIndex, _T("UserName"), _T(""), szName.GetBuffer(MAX_PATH), MAX_PATH, szInfoFileName);
			GetPrivateProfileString(szEmployIndex, _T("Department"), _T(""), szDepartment.GetBuffer(MAX_PATH), MAX_PATH, szInfoFileName);

			//姓名
			CLabelUI *pNameLabel = static_cast<CLabelUI *>(m_PaintManager.FindControl(_T("nameLabel")));
			if (pNameLabel)
			{
				pNameLabel->SetText(szName);
			}

			//部门 
			CLabelUI *pDepartLabel = static_cast<CLabelUI *>(m_PaintManager.FindControl(_T("DepartmentLabel")));
			if (pDepartLabel)
			{
				pDepartLabel->SetText(szDepartment);
			}
			
			BOOL bRead = TRUE;
			BOOL bWrite = TRUE;
			//szEmployIndex 工号
			CString szFileName, szCount;
			szFileName.Format(_T("../Skin/Data/%s.record"), szDate);
			GetPrivateProfileString(szEmployIndex, _T("Count"), _T("0"), szCount.GetBuffer(MAX_PATH), MAX_PATH, szFileName);
			int nCount = _ttoi(szCount);
			if (nCount != 0)
			{
				CString szThisTime;
				szCount.Format(_T("PunchTime%d"), nCount);
				GetPrivateProfileString(szEmployIndex, szCount, _T("2019-01-01 00:00:00"), szThisTime.GetBuffer(MAX_PATH), MAX_PATH, szFileName);
				int n = CFileManager::ComparePunchTimeWithLast(szThisTime, szTime);
				if (n <= 600) //5分钟之内重复打卡不做记录
				{
					bWrite = FALSE;
				}
				if (m_szLastName == szName)
				{
					int t = CFileManager::ComparePunchTimeWithLast(m_szLastTime, szTime);
					if (t <= 8) //5秒以上才读
					{
						bRead = FALSE;
					}
				}
				m_szLastName = szName;
				m_szLastTime = szTime;
			}
			if (bWrite)
			{
				szCount.Format(_T("%d"), nCount + 1);
				WritePrivateProfileString(szEmployIndex, _T("Count"), szCount, szFileName);
				szCount.Format(_T("PunchTime%d"), nCount + 1);
				WritePrivateProfileString(szEmployIndex, szCount, szPunchTime, szFileName);
			}

			if (bRead)
			{      
				CString szSpeak;
				szSpeak.Format(_T("%s%s"), szName, m_szCurTimeInter);
				string strText = CT2A(szSpeak.GetBuffer());
				CJTTS::SpeakText((LPCTSTR)strText.c_str());
			}
			UpdateWindow(GetHWND());
		}
		m_szResult = "";
		m_strPicName = "";
	}
}

//左边时间显示
void CMainWnd::ChangeTodayInfoLabel()
{
	CTime time;
	time = CTime::GetCurrentTime();
	CString szCurTime = time.Format(_T("%H:%M:%S"));
	m_szCurTime = time.Format(_T("%H:%M:%S"));
	CString szCurWeek = time.Format(_T("%A"));
	CString szCurDate = time.Format(_T("%Y-%m-%d"));
	m_szCurDate = szCurDate;
	CString szCurTimeInter = time.Format(_T("%H"));
	szCurWeek = CFileManager::ChangeEngToChinese(szCurWeek);
	if (szCurWeek == _T("星期六") || szCurWeek == _T("星期日"))
	{
		m_bSleepDay = TRUE;
	}
	else
	{
		m_bSleepDay = FALSE;
	}

	CLabelUI *pTimeLabel = static_cast<CLabelUI *>(m_PaintManager.FindControl(_T("timeLabel")));
	if (pTimeLabel)
	{
		pTimeLabel->SetText(szCurTime);
	}

	CLabelUI *pDateLabel = static_cast<CLabelUI *>(m_PaintManager.FindControl(_T("dateLabel")));
	if (pDateLabel)
	{
		pDateLabel->SetText(szCurDate);
	}

	CLabelUI *pTimeInterLabel = static_cast<CLabelUI *>(m_PaintManager.FindControl(_T("timeIntervalLabel")));
	if (pTimeInterLabel)
	{
		int nHour = _ttoi(szCurTimeInter);
		if (nHour > 5 && nHour <= 9)
		{
			szCurTimeInter = _T("早上好");
		}
		else if (nHour > 9 && nHour <= 11)
		{
			szCurTimeInter = _T("上午好");
		}
		else if (nHour > 11 && nHour <= 13)
		{
			szCurTimeInter = _T("中午好");
		}
		else if (nHour > 13 && nHour <= 18)
		{
			szCurTimeInter = _T("下午好");
		}
		else
		{
			szCurTimeInter = _T("晚上好, 您辛苦了");
		}
		pTimeInterLabel->SetText(szCurTimeInter);
		m_szCurTimeInter = szCurTimeInter;
	}
}

//改变底部照片
void CMainWnd::ChangeBottomPic()
{
	CString szDate = m_szCurDate;
	CString szCount, szFileName;
	szFileName.Format(_T("../Skin/Data/%s.record"), szDate);
	m_szFileName = szFileName;
	GetPrivateProfileString(_T("PunchCount"), _T("Count"), _T("0"), szCount.GetBuffer(MAX_PATH), MAX_PATH, szFileName);
	int nCount = _ttoi(szCount);

	//新增6个不同人打卡
	vector<int> v;
	vector<CString> vecPunchTime;
	vecPunchTime.clear();
	v.clear();
	for (int i = nCount; i >= 1; i--)
	{
		CString szNum, szIndex, szPunchTime;
		szNum.Format(_T("%d"), i);
		GetPrivateProfileString(szNum, _T("EmployeeIndex"), _T(""), szIndex.GetBuffer(MAX_PATH), MAX_PATH, szFileName);
		GetPrivateProfileString(szNum, _T("PunchTime"), _T(""), szPunchTime.GetBuffer(MAX_PATH), MAX_PATH, szFileName);
		CString szCurrentTime = m_szCurTime;
		CString szPunchTimes = szPunchTime;
		
		if (i == nCount)
		{
			BOOL bThanThree = CFileManager::ComparePunchTime(szPunchTimes, szCurrentTime);
			if (bThanThree)
			{
				//清除右侧记录
				CVerticalLayoutUI *pFaceV = static_cast<CVerticalLayoutUI *>(m_PaintManager.FindControl(_T("videoVerticalLayout")));
				if (pFaceV)
				{
					pFaceV->RemoveAll();
				}
				CVerticalLayoutUI *pCompareV = static_cast<CVerticalLayoutUI *>(m_PaintManager.FindControl(_T("compareVerticalLayout")));
				if (pCompareV)
				{
					pCompareV->RemoveAll();
				}
				CVerticalLayoutUI *pComInfoV = static_cast<CVerticalLayoutUI *>(m_PaintManager.FindControl(_T("FaceIcon_Success")));
				if (pComInfoV)
				{
					pComInfoV->SetVisible(false);
				}
				break;
			}
		}

		int nIndex = _ttoi(szIndex);
		vector<int>::iterator it;
		it = find(v.begin(), v.end(), nIndex);
		//不存在
		if (it == v.end())
		{
			v.push_back(nIndex);
			vecPunchTime.push_back(szPunchTime);
		}
		if (v.size() == 4)
		{
			break;
		}
	}

	int nSize = v.size();
	vector<int> v1;
	vector<CString> vecPunchTime1;
	for (int i = 0; i < nSize; i++)
	{
		v1.push_back(v[nSize - i - 1]);
		vecPunchTime1.push_back(vecPunchTime[nSize - i - 1]);
	}
	//CreatLabel(nSize, vecPunchTime1, v1);
	UpdateWindow(GetHWND());
	Sleep(50);
}

//创建底部label
void CMainWnd::CreatLabel(int nLabelNum, vector<CString> vecPunchTime, vector<int> vec)
{
	CVerticalLayoutUI *pVerticalLayout = static_cast<CVerticalLayoutUI *>(m_PaintManager.FindControl(_T("Bottom_VLayout")));
	if (pVerticalLayout)
	{                     
		pVerticalLayout->RemoveAll();
		if (nLabelNum == 0)
		{
			return;
		}
		//创建V容器
		int nWidth = 8;
		for (int i = 0; i < nLabelNum; i++)
		{
			//容器V
			CVerticalLayoutUI *pVLayout = new CVerticalLayoutUI();
			pVLayout->SetFloat(true);
			int nPosX = (i + 1) * nWidth + i * m_bottomPicWidth;
			CDuiString szPos;
			szPos.Format(_T("%d,0,%d,250"), nPosX, nPosX + m_bottomPicWidth);
			pVLayout->SetAttribute(_T("pos"), szPos);

			CHorizontalLayoutUI *pHLayoutPic = new CHorizontalLayoutUI();
			pHLayoutPic->SetAttribute(_T("height"), _T("200"));
			//图片Label
			CLabelUI *pLabel_Pic = new CLabelUI();
			pLabel_Pic->SetFloat(true);
			CDuiString szPos1;
			szPos1.Format(_T("0,0,%d,200"), m_bottomPicWidth);
			pLabel_Pic->SetAttribute(_T("pos"), szPos1);

			int nNum = vec[i];
			CString szNum, szPicName;
			szNum.Format(_T("%d"), nNum);
			szPicName.Format(_T("../Skin/AllPeoPicture/%s.jpg"), szNum);
			pLabel_Pic->SetBkImage(szPicName);
			pHLayoutPic->Add(pLabel_Pic);

			//框架图片
			CLabelUI *pTopLabel = new CLabelUI();
			pTopLabel->SetFloat(true);
			pTopLabel->SetAttribute(_T("pos"), szPos1);
			pTopLabel->SetBkImage(_T("picture/bottonBK.png"));
			pHLayoutPic->Add(pTopLabel);
			pVLayout->Add(pHLayoutPic);

			CVerticalLayoutUI *pVLayoutInfo = new CVerticalLayoutUI();
			pVLayoutInfo->SetAttribute(_T("height"), _T("52"));
			CString szFileName = _T("../Skin/Config/Infomation.record");
			//姓名
			CString szPunchName;
			GetPrivateProfileString(szNum, _T("Name"), _T(""), szPunchName.GetBuffer(MAX_PATH), MAX_PATH, szFileName);
			CLabelUI *pNameLabel = new CLabelUI();
			pNameLabel->SetFloat(true);
			szPos1.Format(_T("0,4,%d,28"), m_bottomPicWidth);
			pNameLabel->SetAttribute(_T("pos"), szPos1);
			pNameLabel->SetText(szPunchName);
			pNameLabel->SetTextColor(0xFFFFFFFF);
			pNameLabel->SetAttribute(_T("font"), _T("5"));
			pNameLabel->SetAttribute(_T("align"), _T("center"));
			pNameLabel->SetAttribute(_T("valign"), _T("center"));
			pVLayoutInfo->Add(pNameLabel);

			//时间
			CString szPunchTime = vecPunchTime[i];
			CDuiString szTime = szPunchTime;
			int nLength = szTime.GetLength();
			int nPos = szTime.Find(' ');
			szTime = szTime.Mid(nPos + 1, nLength - nPos - 1);
			CLabelUI *pTimeLabel = new CLabelUI();
			pTimeLabel->SetFloat(true);
			szPos1.Format(_T("0,28,%d,52"), m_bottomPicWidth);
			pTimeLabel->SetAttribute(_T("pos"), szPos1);
			pTimeLabel->SetText(szTime);
			pTimeLabel->SetTextColor(0xFFFFFFFF);
			pTimeLabel->SetAttribute(_T("font"), _T("5"));
			pTimeLabel->SetAttribute(_T("align"), _T("center"));
			pTimeLabel->SetAttribute(_T("valign"), _T("center"));
			pVLayoutInfo->Add(pTimeLabel);

			pVLayout->Add(pVLayoutInfo);
			pVerticalLayout->Add(pVLayout);
		}
	}
}

//之前版本逻辑废除 
//直接应用其他程序上传
void CMainWnd::Punch()
{
	//获取时间,如果时间大于23点50分,上传打卡记录
	CString szTime = m_szCurTime;
	if (szTime == _T(""))
	{
		return;
	}
	CString szCompareTime = _T("1970-01-01 09:00:00");
	int nThanNight1 = CFileManager::ComparePunchTimeWithLast(szCompareTime, szTime);
	szCompareTime = _T("1970-01-01 09:10:00");
	int nThanNight2 = CFileManager::ComparePunchTimeWithLast(szCompareTime, szTime);
	if (nThanNight1 > 0 && nThanNight2 < 0)
	{
		//取第一个,
		for (int i = 0; i < 1200; i++)
		{
			CString szFileName, szCount, szEmployIndex, szDate;
			szDate = m_szCurDate;
			szFileName.Format(_T("../Skin/Data/%s.record"), szDate);
			szEmployIndex.Format(_T("%d"), i);
			GetPrivateProfileString(szEmployIndex, _T("Count"), _T("0"), szCount.GetBuffer(MAX_PATH), MAX_PATH, szFileName);
			int nCount = _ttoi(szCount);
			if (nCount != 0)
			{
				GetPrivateProfileString(szEmployIndex, _T("IsNightPunched"), _T("0"), szCount.GetBuffer(MAX_PATH), MAX_PATH, szFileName);
				int nPunched = _ttoi(szCount);
				if (nPunched == 0)
				{
					//九点未上传
					vector<CString> vecSzPunchTime;
					CString szPunchCount, szPunchTime;
					szPunchCount = _T("PunchTime1");
					GetPrivateProfileString(szEmployIndex, szPunchCount, _T("1970-01-01 00:00:00"), szPunchTime.GetBuffer(MAX_PATH), MAX_PATH, szFileName);
					vecSzPunchTime.push_back(szPunchTime);
					//从打卡机获取的进行比较
					CString szPunchInTime, szPunchOutTime, szType;
					CHttpManager::GetAllPunchTime(szEmployIndex, szDate, vecSzPunchTime, szPunchInTime, szPunchOutTime);
					szType = _T("in");
					BOOL bPunch = CHttpManager::GetPunchInfo(szEmployIndex, szPunchInTime, szType);
					if (bPunch)
					{
						WritePrivateProfileString(szEmployIndex, _T("IsNightPunched"), _T("1"), szFileName);
					}
				}
			}
		}
	}
	//zhuyankun
    szCompareTime = _T("1970-01-01 23:40:00");
	
	int n = CFileManager::ComparePunchTimeWithLast(szCompareTime, szTime);
	if (n>0)
	{
		//工号的范围
		for (int i = 0; i < 1200; i++)
		{
			//获取工号下的所有打卡时间与打卡机时间进行比较,取出两个进行4点半比较
			//1.获取工号下面打卡次数 0表示未使用过人脸打卡,不管
			//2.获取上传标识,已经上传标识为1,不重复操作,未上传为0
			//3.获取打卡机记录,比较,上传
			CString szFileName, szCount, szEmployIndex, szDate;
			szDate = m_szCurDate;
			szFileName.Format(_T("../Skin/Data/%s.record"), szDate);
			szEmployIndex.Format(_T("%d"), i);
			GetPrivateProfileString(szEmployIndex, _T("Count"), _T("0"), szCount.GetBuffer(MAX_PATH), MAX_PATH, szFileName);
			int nCount = _ttoi(szCount);
			if (nCount != 0)
			{
				//IsPunched zhuyankun
				GetPrivateProfileString(szEmployIndex, _T("IsPunched"), _T("0"), szCount.GetBuffer(MAX_PATH), MAX_PATH, szFileName);
				int nPunched = _ttoi(szCount);
				//未上传
				if (nPunched == 0)
				{
					//获取比较后上传的时间
					CString szPunchInTime = _T("0"), szPunchOutTime = _T("0"), szType;
					//本身打卡时间已经有一个排序,所以无需去排序,会影响效率,直接取1或者2
					vector<CString> vecSzPunchTime;
					CString szPunchCount, szPunchTime;
					szPunchCount = _T("PunchTime1");
					GetPrivateProfileString(szEmployIndex, szPunchCount, _T("1970-01-01 00:00:00"), szPunchTime.GetBuffer(MAX_PATH), MAX_PATH, szFileName);
					szPunchInTime = szPunchTime;
					vecSzPunchTime.push_back(szPunchTime);
					
					if (nCount > 1)
					{
						//最后一个
						szPunchCount.Format(_T("PunchTime%d"), nCount);
						GetPrivateProfileString(szEmployIndex, szPunchCount, _T("1970-01-01 00:00:00"), szPunchTime.GetBuffer(MAX_PATH), MAX_PATH, szFileName);
						szPunchOutTime = szPunchTime;
						vecSzPunchTime.push_back(szPunchTime);
					}
					
					//工作日
					if (!m_bSleepDay)
					{
						//进行比较
						szPunchOutTime = szPunchInTime = _T("0");
						CHttpManager::GetAllPunchTime(szEmployIndex, szDate, vecSzPunchTime, szPunchInTime, szPunchOutTime);
					}
					if (szPunchInTime == _T("0"))
					{
						if (szPunchOutTime != _T("0"))
						{
							//上传out
							szType = _T("out");
							BOOL bPunch = CHttpManager::GetPunchInfo(szEmployIndex, szPunchOutTime, szType);
							if (bPunch)
							{
								//zhuyankun
								WritePrivateProfileString(szEmployIndex, _T("IsPunched"), _T("1"), szFileName);
							}
						}
					}
					else
					{
						//上传in
						szType = _T("in");
						BOOL bPunch = CHttpManager::GetPunchInfo(szEmployIndex, szPunchInTime, szType);
						if (szPunchOutTime != _T("0"))
						{
							//上传out
							szType = _T("out");
						    bPunch = CHttpManager::GetPunchInfo(szEmployIndex, szPunchOutTime, szType);
						}
						if (bPunch)
						{
							WritePrivateProfileString(szEmployIndex, _T("IsPunched"), _T("1"), szFileName);
						}
					}
				}
			}
		}
	}
}

DWORD WINAPI CMainWnd::ProcessPunchEvent(LPVOID pParam)
{
	if (pParam != NULL)
	{
		CMainWnd *pMainWnd = (CMainWnd *)pParam;
		while (1)
		{
			//人脸检测
			pMainWnd->Punch();
			Sleep(2000);
		}
	}
	return 0;
}

float CMainWnd::GetRgbFaceScore(std::string strRes)
{
	float score = 0;
	if (strRes.length() > 0)
	{
		Json::Value root;
		Json::Reader reader;
		if (reader.parse(strRes, root))
		{
			int err = root["errno"].asInt();
			if (err == 0)
			{
				Json::Value result = root["data"];
				if (result.size() > 0)
				{
					std::string sss = result["score"].asString();
					score = atof(sss.c_str());
				}
			}
		}
	}
	return score;
}