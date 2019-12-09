#include "stdafx.h"
#include "BaiduFaceAI.h"
#include "BaiduFaceAIDlg.h"
#include "MainWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CBaiduFaceAIApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CBaiduFaceAIApp::CBaiduFaceAIApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}

CBaiduFaceAIApp theApp;


BOOL CBaiduFaceAIApp::InitInstance()
{
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	CString szCurPath = CPaintManagerUI::GetCurrentPath();
	int n = szCurPath.GetLength(), nPos;
	nPos = szCurPath.ReverseFind('\\');
	szCurPath = szCurPath.Left(nPos);
	szCurPath += "\\Skin\\";
	CDuiString szResourePath;
	szResourePath.Format(_T("%s"), szCurPath);
	CPaintManagerUI::SetInstance(AfxGetInstanceHandle());
	CPaintManagerUI::SetResourcePath(szResourePath);
	CMainWnd *pMainWnd = new CMainWnd(_T("MainWnd.xml"));
	pMainWnd->Create(NULL, _T("Duilib"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pMainWnd->CenterWindow();
	pMainWnd->ShowModal();
	delete pMainWnd;
	return FALSE;

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif
	return FALSE;
}

