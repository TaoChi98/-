#pragma once
#include "../Include/Duilib/UIlib.h"
using namespace DuiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "..\\Include\\Duilib\\Lib\\DuiLib_ud.lib")
#   else
#       pragma comment(lib, "..\\Include\\Duilib\\Lib\\DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "..\\Include\\Duilib\\Lib\\DuiLib_u.lib")
#   else
#      pragma comment(lib, "..\\Include\\Duilib\\Lib\\DuiLib.lib")
#   endif
#endif

class CXMLBaseWnd : public WindowImplBase
{
public:
	CXMLBaseWnd(void);
	explicit CXMLBaseWnd(LPCTSTR pszXMLPath) : m_strXMLPath(pszXMLPath)
	{
		
	}
	virtual ~CXMLBaseWnd(void);
	virtual LPCTSTR GetWindowClassName() const
	{
		return _T("XMLWnd");
	}

	virtual CDuiString GetSkinFile()
	{
		return m_strXMLPath;
	}

	virtual CDuiString GetSkinFolder()
	{
		return _T("Skin");
	}

protected:
	CDuiString m_strXMLPath;

};
