/*
jTTS Protocal 4.0
*/

#ifndef __jTTSPROTOCAL_H__
#define __jTTSPROTOCAL_H__

#include <crtdbg.h>
#include "mytrace.h"

// 以下数据结构和函数仅为和1.0版本兼容
typedef struct 
{
	UINT nCodePage;
	UINT nVoiceID;
	int nPitch;
	int nVolume;
	int nSpeed;
	int nPuncMode;
	int nDigitMode;
}JTTSCONFIG;

//以下与Socket有关
#define jTTS_ID				0x5A5A5A5A	//Socket包识别符

#define jTTS_PACK_MAXLEN	1024	//每个Socket包最大长度，字节数
									//文本合成请求包和语音数据包不受此长度限制

//以下为Socket指令
//格式：jTTS_X1_X2
//X1==REQ，来自客户方; X1==ANS，来自服务器方
//X2为具体命令
#define jTTS_REQ_SETPARAM			0x1001	//设置语音合成参数请求(V1.0)
#define jTTS_REQ_TEXT				0x1002	//发送文本请求
#define jTTS_REQ_CANCELSYNTH		0x1003	//取消当前合成过程
#define jTTS_REQ_SETPARAM2			0x1004	//设置语音合成参数请求(V2.0)
#define jTTS_REQ_SETPARAM4			0x1010	//设置语音合成参数请求(V4.0)
#define jTTS_REQ_VOICECOUNT			0x1011	//查询音库数目
#define jTTS_REQ_VOICEATTRIB		0x1012	//查询某个序号的音库属性
#define jTTS_REQ_ISVOICESUPPORTED	0x1013	//查询服务器是否支持某个音库
#define jTTS_REQ_FINDVOICE			0x1014	//选择一个音库
#define jTTS_REQ_QUIT				0x1100	//结束请求
#define jTTS_REQ_TEXT4				0x1015	//jTTS4添加合成文本，jTTSService开始一个新Session
#define jTTS_REQ_ADDTEXT4			0x1016	//添加文本如果前面的合成已经暂时结束，则又触发合成。
#define jTTS_REQ_LICENCENUM		0x1017	//获得授权数

#define jTTS_REQ_VOICEATTRIBBYID 0x1018	//通过voiceId 获得音库属性

#define jTTS_REQ_LANGATTRIBUTE	0x1019	//通过index获得语言属性
#define jTTS_REQ_LANGATTRIBUTEBYVALUE 0x1020 //通过语言值获得语言属性

#define jTTS_REQ_COUNTERS			 0x1021	//请求计数器

#define jTTS_REQ_DOMAINATTRIBUTE			0x1022		//通过index获得领域属性
#define jTTS_REQ_DOMAINATTRIBUTEBYVALUE		0x1023		//通过领域值获得领域属性

#define jTTS_REQ_LANGCOUNT		0x1024					//获得语言值的个数
#define jTTS_REQ_DOMAINCOUNT		0x1025				//获得领域值的个数
#define jTTS_REQ_LICENSEINFO	0x1026					//获得授权信息

//-----Xiaohai Add for 3.0---------
#define jTTS_REQ_WFSYN			0x1005	//词库同步发送
#define jTTS_REQ_WFSYNEND		0x1006	//词库同步结束，需要重起服务器，使新词库有效
#define jTTS_REQ_LBAUTHENADD	0x1007	//负载均衡加密验证请求(增加一个语音合成线程)
#define jTTS_REQ_LBAUTHENSUB	0x1008	//负载均衡加密验证请求(减少一个语音合成线程)
//---------------------------------

#define jTTS_ANS_CONNECT			0x4000	//连接服务器应答
#define jTTS_ANS_SETPARAM			0x4001	//设置语音合成参数应答
#define jTTS_ANS_SOUND				0x4002	//发送语音流
#define jTTS_ANS_SOUND4				0x4003	//发送语音流V4
#define jTTS_ANS_UNKNOWN			0x4080	//服务器接收到一个未知命令的Socket包
#define jTTS_ANS_SHUTDOWN			0x4100	//服务器异常退出,可能是CjTTSConfig调用了StopServer方法
#define	jTTS_ANS_OUTOFTIME		0x4101	//客户超时，即空闲时间超过设定阈值
#define jTTS_ANS_VOICECOUNT		0x4011	//返回音库数目
#define jTTS_ANS_VOICEATTRIB		0x4012	//返回某个序号的音库属性
#define jTTS_ANS_ISVOICESUPPORTED	0x4013	//返回服务器是否支持某个音库
#define jTTS_ANS_FINDVOICE			0x4014	//返回选择音库的结果
#define jTTS_ANS_ADDTEXT4			0x4015	//添加文本应答
#define jTTS_ANS_LICENCENUM		0x4016	//返回授权数
#define jTTS_ANS_LANGATTRIBUTE	0x4017	//返回语言属性
#define jTTS_ANS_COUNTERS		0x4018	//返回计数器
#define jTTS_ANS_DOMAINATTRIBUTE	0x4019	//返回领域属性
#define jTTS_ANS_LANGCOUNT		0x4020					//返回语言值的个数
#define jTTS_ANS_DOMAINCOUNT		0x4021				//返回领域值的个数
#define jTTS_ANS_LICENSEINFO	0x4022	 //返回授权信息 	

//------Xiaohai Add for 3.0----------
#define jTTS_ANS_WFSYN			0x4005	//词库同步接受应答
#define jTTS_ANS_SERVICERESTART 0x4006	//使新词库有效的重起服务器操作完成，可以与下一个服务器进行词库同步
#define jTTS_ANS_LBAUTHEN		0x4007	//负载均衡加密验证应答
//-----------------------------------

//以下为系统常数
#define jTTS_PORTMAX			32767	//端口号最大值
#define jTTS_PORTMIN			1		//端口号最小值
#define jTTS_REQNUMMAX			255		//并发请求数最大值
#define jTTS_REQNUMMIN			1		//并发请求数最小值
#define jTTS_IDLETIMEMAX		100		//空闲时间最大值
#define jTTS_IDLETIMEMIN		0		//空闲时间最小值  //xiaohai 从1修改为0，0表示没有超时限制。02-01-17


//以下为错误码
#define jTTS_NOERROR				0	//操作正确完成
#define jTTS_AUTODISCONNECT			1	//用户超时
#define jTTS_SYNTHCOMPLETE			2	//语音合成完毕
#define jTTS_SERVERSTART			3	//服务器启动
#define jTTS_SERVERSHUTDOWN			4	//服务器退出
#define jTTS_PARAMOUTOFRANGE		0xA0010001//参数超出了设定范围
#define jTTS_PARAMERR				0xA0010002//参数错误
#define jTTS_INVALIDTEXT			0xA0010003//错误的文本参数，可能是文本指针指向一个空字符串
#define jTTS_TOOMANYCONNECTIONS		0xA0020001//并发的连接大于设定的阈值
#define jTTS_PREVSYNTHNOTCOMPLETE	0xA0020002//上次语音合成过程并未完全结束
#define jTTS_ERRMASK				0xA0030000//jTTS错误掩码
#define jTTS_MOREDATA				0xA0040001//语音数据没有发送完，请继续接收语音数据
#define jTTS_SYNTHBECANCELED		0xA0050001//用户取消该语音合成过程
#define jTTS_SOCKETERR				0xA0100001//启动socket错误
#define jTTS_JTTSINITERR			0xA0100002//jTTS SDK初始化错误
#define jTTS_DOGERR					0xA0100003//软件狗读取错误
#define jTTS_STOPERR				0xA0100010//停止socket错误
#define jTTS_MEMALLOCERR			0xA0110001//内存分配错误
#define jTTS_ERRPACK				0xA0120001//接收到一个错误的包，可能为ID错误或包长度错误
#define jTTS_VOICENOTSUPPORTED		0xA0130001//没有查到合适的Voice
#define jTTS_ADDTEXT4				0xA0140001//AddText之前，没有SessionStart,即没有发送jTTS_REQ_TEXT4
#define jTTS_TEXT4					0xA0140002//jTTS_REQ_TEXT4或者jTTS_REQ_TEXT启动的合成线程还在运行
#define jTTS_ERRUNKNOWN				0xA0200001//未知错误

#pragma warning( push )
#pragma warning( disable : 4244 )

//这个宏在Release选择优化以后会优化,因为sizeof是在编译的时候就可以确定的,所以不必担心效率

#define H2N(x) \
{\
	_ASSERTE(sizeof(x)==2 || sizeof(x)==4); \
	if (sizeof(x) == 2) x = htons(x);else x = htonl(x);\
}

#define N2H(x) \
{\
	_ASSERTE(sizeof(x)==2 || sizeof(x)==4); \
	if (sizeof(x) == 2) x = ntohs(x);else x = ntohl(x);\
}


/****************************************************************/
/*	CjTTSSocketProtocal为所有Socket包类的基类					*/
/*  成员变量：													*/
/*	DWORD m_dwID;		jTTS识别符，固定为jTTS_ID, 即0x5A5A5A5A	*/
/*	DWORD m_dwCommand;  Socket指令，可能为上面提到的9种之一		*/
/*	DWORD m_dwLen;		整个包的长度，字节数。					*/
/****************************************************************/


class CjTTSSocketProtocal
{
public:
	DWORD m_dwID;
	DWORD m_dwCommand;
	DWORD m_dwLen;
#ifdef CHECK_DEBUG
	int m_checkhton;
	int m_checkntoh;
#endif

#ifdef CHECK_DEBUG
	void CheckCallEnd()
	{
		_ASSERTE(m_checkhton ==1 && m_checkntoh==1);
	}
#endif

	CjTTSSocketProtocal()
		: m_dwID(jTTS_ID)
	{
		m_dwCommand = 0;
		m_dwLen = sizeof( *this );
#ifdef CHECK_DEBUG
		m_checkhton = 0;
		m_checkntoh = 0; 
#endif
	}

	void htonheader()
	{
#ifdef CHECK_DEBUG  //这个函数不能重复调用两次,检查一下
		m_checkhton ++;
		_ASSERTE(m_checkhton < 2);
#endif		
		H2N(m_dwID);
		H2N(m_dwCommand);
		H2N(m_dwLen);
		MYTRACE("CjTTSSocketProtocal::htonheader()\n");
	}
	void ntohheader()
	{
#ifdef CHECK_DEBUG  //这个函数不能重复调用两次,检查一下
		m_checkntoh ++;
		_ASSERTE(m_checkntoh < 2);
		_ASSERTE(m_checkhton == 1);	//确认在之前调用过htonheader
#endif		

		N2H(m_dwID);
		N2H(m_dwCommand);
		N2H(m_dwLen);
		MYTRACE("CjTTSSocketProtocal::ntohheader()\n");
	}
};

#define	JTTS_HEADERLEN		sizeof(CjTTSSocketProtocal)

//////////////////////////////////////////////////
//  xiaohai add 负载均衡加密验证请求包			//
//////////////////////////////////////////////////
class CjTTSReqLBAuthenAdd : public CjTTSSocketProtocal
{
public:
	long m_nData;
	char m_szVoiceId[VOICEID_LEN];

	CjTTSReqLBAuthenAdd()
	{
		m_dwCommand = jTTS_REQ_LBAUTHENADD;
		m_dwLen = sizeof(*this);
	}
	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
		H2N(m_nData);
	}
	void ntoh()
	{
		N2H(m_nData);
	}
};

class CjTTSReqLBAuthenSub : public CjTTSSocketProtocal
{
public:
	long m_nData;
	BOOL m_bUseFreeLicense;
	char m_szVoiceId[VOICEID_LEN];

	CjTTSReqLBAuthenSub()
	{
		m_dwCommand = jTTS_REQ_LBAUTHENSUB;
		m_bUseFreeLicense = FALSE;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nData);
		H2N(m_bUseFreeLicense);
	}
	void ntoh()
	{
		N2H(m_nData);
		N2H(m_bUseFreeLicense);
	}
};

//////////////////////////////////////////////////
// xiaohai add 负载均衡加密验证应答包			//
//////////////////////////////////////////////////
class CjTTSAnsLBAuthen : public CjTTSSocketProtocal
{
public:
	long m_nData;
	BOOL m_bUseFreeLicense;

	CjTTSAnsLBAuthen()
	{
		m_dwCommand = jTTS_ANS_LBAUTHEN;
		m_bUseFreeLicense = FALSE;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
		H2N(m_nData);
		H2N(m_bUseFreeLicense);
	}
	void ntoh()
	{
		N2H(m_nData);
		N2H(m_bUseFreeLicense);
	}
};

//////////////////////////////////////////////////
//	Xiaohai add for Words file synchronize		//
//	CjTTSReqWFSyn: 发送词库同步数据包			//
//////////////////////////////////////////////////
class CjTTSReqWFSyn : public CjTTSSocketProtocal
{
public:
	char m_cFileName[MAX_PATH];
	DWORD m_dwTextLen;
	char m_ptszText[1];
	CjTTSReqWFSyn()
	{
		m_dwCommand = jTTS_REQ_WFSYN;
		m_dwLen = sizeof(*this);	//必须置为包含词库同步文本的实际包长度
		m_ptszText[0] = '\0';					//将词库同步文本拷贝到此位置
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_dwTextLen);
	}
	void ntoh()
	{
		N2H(m_dwTextLen);
	}
};

//////////////////////////////////////////////////////
//  Xiaohai add for 词库同步结束，需要重起服务器	//
//  CjTTSReqWFSynEnd: 词库同步结束数据包			//
//////////////////////////////////////////////////////
class CjTTSReqWFSynEnd : public CjTTSSocketProtocal
{
public:
	CjTTSReqWFSynEnd()
	{
		m_dwCommand = jTTS_REQ_WFSYNEND;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
	}
	void ntoh()
	{
		
	}
};

//////////////////////////////////////////////////////
//	xiaohai add for Words file synchronize			//
//	CjTTSAnsWFSyn: 词库同步响应数据包				//
//////////////////////////////////////////////////////
class CjTTSAnsWFSyn : public CjTTSSocketProtocal
{
public:
	UINT m_nErrorCode;
	CjTTSAnsWFSyn()
	{
		m_dwCommand = jTTS_ANS_WFSYN;
		m_dwLen = sizeof(*this);
		m_nErrorCode = jTTS_NOERROR;
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nErrorCode);
	}
	void ntoh()
	{
		N2H(m_nErrorCode);
	}
};

//////////////////////////////////////////////////////////
//  Xiaohai add for 使新词库有效的服务器重起已经完成	//
//  CjTTSAnsServiceRestart: 服务器重起完成数据包		//
//////////////////////////////////////////////////////////
class CjTTSAnsServiceRestart : public CjTTSSocketProtocal
{
public:
	CjTTSAnsServiceRestart()
	{
		m_dwCommand = jTTS_ANS_SERVICERESTART;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
	}
	void ntoh()
	{
	}
};


//获得授权数
class CjTTSPtlReqLicenceNum : public CjTTSSocketProtocal
{
public:

	CjTTSPtlReqLicenceNum()
	{
		m_dwCommand = jTTS_REQ_LICENCENUM;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
	}
	void ntoh()
	{
	}
};

class CjTTSPtlReqLicenseInfo : public CjTTSSocketProtocal
{
public:

	CjTTSPtlReqLicenseInfo()
	{
		m_dwCommand = jTTS_REQ_LICENSEINFO;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
	}

	void ntoh()
	{
	}
};



//
//--------------------------------------------------------

//以下为客户端Socket包，当前版本共计3种

/****************************************************************/
/*	CjTTSPtlReqSetParam: 设定语音合成参数请求					*/
/*		为有应答的请求，应答包为CjTTSPtlAnsSetParam				*/
/*		m_dwCommand = jTTS_REQ_SETPARAM							*/
/*  成员变量：													*/
/*	JTTSCONFIG 	m_jTTSConfig;语音合成参数						*/
/*	int			m_nFormat;   输出格式，声卡输出还是文件输出		*/
/****************************************************************/
class CjTTSPtlReqSetParam : public CjTTSSocketProtocal
{
public:
	JTTSCONFIG 	m_jTTSConfig;
	int			m_nFormat;

	CjTTSPtlReqSetParam()
	{
		m_dwCommand = jTTS_REQ_SETPARAM;
		m_dwLen = sizeof(*this);
		::memset( &m_jTTSConfig, 0, sizeof(JTTSCONFIG) );
		m_nFormat = 0;
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		htonJTTSCONFIG(m_jTTSConfig);
		H2N(m_nFormat);
	}
	void ntoh()
	{
		ntohJTTSCONFIG(m_jTTSConfig);
		N2H(m_nFormat);
	}

private:
	void htonJTTSCONFIG(JTTSCONFIG & jconfig)
	{
		_ASSERTE(sizeof(jconfig) == 28);

		H2N(jconfig.nCodePage);
		H2N(jconfig.nDigitMode);
		H2N(jconfig.nPitch);
		H2N(jconfig.nPuncMode);
		H2N(jconfig.nSpeed);
		H2N(jconfig.nVoiceID);
		H2N(jconfig.nVolume);
		H2N(jconfig.nVoiceID);
	}
	void ntohJTTSCONFIG(JTTSCONFIG & jconfig)
	{
		_ASSERTE(sizeof(jconfig) == 28);

		N2H(jconfig.nCodePage);
		N2H(jconfig.nDigitMode);
		N2H(jconfig.nPitch);
		N2H(jconfig.nPuncMode);
		N2H(jconfig.nSpeed);
		N2H(jconfig.nVoiceID);
		N2H(jconfig.nVolume);
		N2H(jconfig.nVoiceID);
	}


};

/****************************************************************/
/*	CjTTSPtlReqSetParam2: 设定语音合成参数请求					*/
/*		为有应答的请求，应答包为CjTTSPtlAnsSetParam2			*/
/*		m_dwCommand = jTTS_REQ_SETPARAM							*/
/*  成员变量：													*/
/*	JTTSCONFIG2	m_jTTSConfig2;语音合成参数						*/
/*	int			m_nFormat;   输出格式，声卡输出还是文件输出		*/
/****************************************************************/
class CjTTSPtlReqSetParam2 : public CjTTSSocketProtocal
{
public:
	JTTSCONFIG2	m_jTTSConfig2;
	int			m_nFormat;

	CjTTSPtlReqSetParam2()
	{
		m_dwCommand = jTTS_REQ_SETPARAM2;
		m_dwLen = sizeof(*this);
		::memset( &m_jTTSConfig2, 0, sizeof(JTTSCONFIG2) );
		m_nFormat = 0;
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		htonJTTSCONFIG2(m_jTTSConfig2);
		H2N(m_nFormat);
	}
	void ntoh()
	{
		ntohJTTSCONFIG2(m_jTTSConfig2);
		N2H(m_nFormat);
	}

private:
	void htonJTTSCONFIG2(JTTSCONFIG2 & jconfig2)
	{
		_ASSERTE(sizeof(jconfig2) == 36);

		H2N(jconfig2.nCodePage);
		H2N(jconfig2.nDigitMode);
		H2N(jconfig2.nEngMode);
		H2N(jconfig2.nPitch);
		H2N(jconfig2.nPuncMode);
		H2N(jconfig2.nSpeed);
		H2N(jconfig2.nVolume);
		H2N(jconfig2.wVersion);
		H2N(jconfig2.nVoiceID);
	}

	void ntohJTTSCONFIG2(JTTSCONFIG2 & jconfig2)
	{
		_ASSERTE(sizeof(jconfig2) == 36);

		N2H(jconfig2.nCodePage);
		N2H(jconfig2.nDigitMode);
		N2H(jconfig2.nEngMode);
		N2H(jconfig2.nPitch);
		N2H(jconfig2.nPuncMode);
		N2H(jconfig2.nSpeed);
		N2H(jconfig2.nVolume);
		N2H(jconfig2.wVersion);
		N2H(jconfig2.nVoiceID);
	}


};

/****************************************************************/
/*	CjTTSPtlReqText: 语音合成请求								*/
/*		为有应答的请求，应答包为CjTTSPtlAnsSound				*/
/*		DWORD m_dwCommand = jTTS_REQ_TEXT						*/
/*  成员变量：													*/
/*	DWORD m_dwTextLen待合成文本char字符的个数，				*/
/*		即对于UNICODE版本，实际字符数为2*m_dwTextLen			*/
/****************************************************************/
class CjTTSPtlReqText : public CjTTSSocketProtocal
{
public:
	DWORD m_dwTextLen;
	char m_ptszText[1];
	CjTTSPtlReqText()
	{
		m_dwCommand = jTTS_REQ_TEXT;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
		H2N(m_dwTextLen);
	}
	void ntoh()
	{
		N2H(m_dwTextLen);
	}
};

/****************************************************************/
/*	CjTTSPtlReqText4: 语音合成请求V4							*/
/*		为有应答的请求，应答包为CjTTSPtlAnsSound				*/
/*		DWORD m_dwCommand = jTTS_REQ_TEXT4						*/
/*  成员变量：													*/
/*	DWORD m_dwTextLen待合成文本char字符的个数，				*/
/*		即对于UNICODE版本，实际字符数为2*m_dwTextLen			*/
/****************************************************************/
class CjTTSPtlReqText4 : public CjTTSSocketProtocal
{
public:
	DWORD m_dwTextLen;
	char m_ptszText[1];
	CjTTSPtlReqText4()
	{
		m_dwCommand = jTTS_REQ_TEXT4;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
		H2N(m_dwTextLen);
	}
	void ntoh()
	{
		N2H(m_dwTextLen);
	}
};

class CjTTSPtlReqAddText4 : public CjTTSSocketProtocal
{
public:
	DWORD m_dwTextLen;
	char m_ptszText[1];
	CjTTSPtlReqAddText4()
	{
		m_dwCommand = jTTS_REQ_ADDTEXT4;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
		H2N(m_dwTextLen);
	}
	void ntoh()
	{
		
		N2H(m_dwTextLen);
	}
};


/****************************************************************/
/*	CjTTSPtlReqCancelSynth: 取消当前语音合成过程，无应答		*/
/*		DWORD m_dwCommand = jTTS_REQ_CANCELSYNTH				*/
/*  成员变量：无												*/
/****************************************************************/
class CjTTSPtlReqCancelSynth : public CjTTSSocketProtocal
{
public:
	CjTTSPtlReqCancelSynth()
	{
		m_dwCommand = jTTS_REQ_CANCELSYNTH;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
	}
	void ntoh()
	{
		
	}
};

/****************************************************************/
/*	CjTTSPtlReqQuit: 客户退出请求，无应答						*/
/*		DWORD m_dwCommand = jTTS_REQ_QUIT						*/
/*  成员变量：无												*/
/****************************************************************/
class CjTTSPtlReqQuit : public CjTTSSocketProtocal
{
public:
	CjTTSPtlReqQuit()
	{
		m_dwCommand = jTTS_REQ_QUIT;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
	}
	void ntoh()
	{
		
	}
};

//设置语音合成参数请求(V4.0)
class CjTTSPtlReqSetParam4 : public CjTTSSocketProtocal
{
public:
	JTTS_CONFIG 	m_jTTSConfig;
	unsigned short	m_nFormat;
	CjTTSPtlReqSetParam4()
	{
		m_dwCommand = jTTS_REQ_SETPARAM4;
		m_dwLen = sizeof(*this);
	}


	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		htonJTTS_CONFIG(m_jTTSConfig);
		H2N(m_nFormat);
	}
	void ntoh()
	{
		ntohJTTS_CONFIG(m_jTTSConfig);
		N2H(m_nFormat);
	}
private:

	//更改JTTS_CONFIG的时候就应该修改这个函数
	void htonJTTS_CONFIG(JTTS_CONFIG & jconfig)
	{
		//如果这个断言不成立说明你对 JTTS_CONFIG结构做了修改,你应该相应修改这个函数,
		//并把sizeof(jconfig)更改成正确的值
		_ASSERTE(sizeof(jconfig) == 92);

		H2N(jconfig.bLoadBalance);
		H2N(jconfig.nCodePage);
		H2N(jconfig.nDigitMode);
		H2N(jconfig.nDomain);
		H2N(jconfig.nEngMode);
		H2N(jconfig.nPitch);
		H2N(jconfig.nPuncMode);
		H2N(jconfig.nSpeed);
		H2N(jconfig.nTagMode);
		H2N(jconfig.nTryTimes);
		H2N(jconfig.nVolume);
		H2N(jconfig.wVersion);
	
	}

	//更改JTTS_CONFIG的时候就应该修改这个函数
	void ntohJTTS_CONFIG(JTTS_CONFIG & jconfig)
	{
		//如果这个断言不成立说明你对 JTTS_CONFIG结构做了修改,你应该相应修改这个函数,
		//并把sizeof(jconfig)更改成正确的值
		_ASSERTE(sizeof(jconfig) == 92);

		N2H(jconfig.bLoadBalance);
		N2H(jconfig.nCodePage);
		N2H(jconfig.nDigitMode);
		N2H(jconfig.nDomain);
		N2H(jconfig.nEngMode);
		N2H(jconfig.nPitch);
		N2H(jconfig.nPuncMode);
		N2H(jconfig.nSpeed);
		N2H(jconfig.nTagMode);
		N2H(jconfig.nTryTimes);
		N2H(jconfig.nVolume);
		N2H(jconfig.wVersion);
	}


};
//查询音库数目
class CjTTSPtlReqVoiceCount : public CjTTSSocketProtocal
{
public:
	CjTTSPtlReqVoiceCount()
	{
		m_dwCommand = jTTS_REQ_VOICECOUNT;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
		MYTRACE("CjTTSPtlReqVoiceCount::htonall\n");
	}
	void ntoh()
	{
		MYTRACE("CjTTSPtlReqVoiceCount::ntoh\n");
	}
};

//查询某个序号的音库属性
class CjTTSPtlReqVoiceAttrib : public CjTTSSocketProtocal
{
public:
	int	m_nIndex;
	CjTTSPtlReqVoiceAttrib()
	{
		m_dwCommand = jTTS_REQ_VOICEATTRIB;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
		H2N(m_nIndex);
	}
	void ntoh()
	{
		N2H(m_nIndex);
	}
};

class CjTTSPtlReqVoiceAttribByID : public CjTTSSocketProtocal
{
public:
	char m_szVoiceID[VOICEID_LEN];
	CjTTSPtlReqVoiceAttribByID()
	{
		m_dwCommand = jTTS_REQ_VOICEATTRIBBYID;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
	}
	void ntoh()
	{
	}
};

//查询服务器是否支持某个音库
class CjTTSPtlReqIsVoiceSupported : public CjTTSSocketProtocal
{
public:
	char m_szVoiceID[VOICEID_LEN];
	CjTTSPtlReqIsVoiceSupported()
	{
		m_dwCommand = jTTS_REQ_ISVOICESUPPORTED;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
	}
	void ntoh()
	{
		
	}
};
//选择一个音库
class CjTTSPtlReqFindVoice : public CjTTSSocketProtocal
{
public:
	int		m_nLanguage;
	char		m_szName[VOICENAME_LEN];
	int		m_nGender;
	int		m_nAge;
	int		m_nDomain;
	char		m_szVoiceID[VOICEID_LEN];
	DWORD		m_dwMatchFlag;

	CjTTSPtlReqFindVoice()
	{
		m_dwCommand = jTTS_REQ_FINDVOICE;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nLanguage);
		H2N(m_nGender);
		H2N(m_nAge);
		H2N(m_nDomain);
		H2N(m_dwMatchFlag);
	}
	void ntoh()
	{
		N2H(m_nLanguage);
		N2H(m_nGender);
		N2H(m_nAge);
		N2H(m_nDomain);
		N2H(m_dwMatchFlag);
	}
};


//以下为服务器端Socket包，当前版本共计5种

/****************************************************************/
/*	CjTTSPtlAnsConnect: 当客户试图和服务器建立连接时，			*/
/*		服务器向客户发出连接应答，指示连接是否成功建立。		*/
/*		DWORD m_dwCommand = jTTS_ANS_CONNECT					*/
/*  成员变量：													*/
/*	UINT 	m_nErrorCode; 错误码，可能为如下值：				*/
/*		1)jTTS_NOERROR，连接建立成功							*/
/*		2)jTTS_TOOMANYCONNECTIONS，当前并发连接数已达到设定阈值	*/
/****************************************************************/
class CjTTSPtlAnsConnect : public CjTTSSocketProtocal
{
public:
	UINT 	m_nErrorCode;

	CjTTSPtlAnsConnect()
	{
		m_nErrorCode = jTTS_NOERROR;
		m_dwCommand = jTTS_ANS_CONNECT;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nErrorCode);
	}
	void ntoh()
	{
		N2H(m_nErrorCode);
	}
};

/****************************************************************/
/*	CjTTSPtlAnsSetParam: 当客户发送语音合成参数设定请求时，		*/
/*		服务器向客户发出应答，指示参数设定是否成功。			*/
/*		DWORD m_dwCommand = jTTS_ANS_SETPARAM					*/
/*  成员变量：													*/
/*	UINT 	m_nErrorCode; 错误码，可能为如下值：				*/
/*		1)jTTS_NOERROR，连接建立成功							*/
/*		2)jTTS_ERRPACK，包长度不正确，概率基本为0				*/
/****************************************************************/
class CjTTSPtlAnsSetParam : public CjTTSSocketProtocal
{
public:
	UINT 	m_nErrorCode;

	CjTTSPtlAnsSetParam()
	{
		m_nErrorCode = jTTS_NOERROR;
		m_dwCommand = jTTS_ANS_SETPARAM;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nErrorCode);
	}
	void ntoh()
	{
		N2H(m_nErrorCode);
	}
};

/****************************************************************/
/*	CjTTSPtlAnsSound: 当客户发送语音合成请求时，				*/
/*		服务器向客户发出应答，指示语音请求是否成功完成。		*/
/*		DWORD m_dwCommand = jTTS_ANS_SOUND						*/
/*  成员变量：													*/
/*	int		m_nBitsPerSample;//数据流每采样的位数				*/
/*	int		m_nSamplesPerSec;//数据流每秒的采样数				*/
/*	DWORD	m_dwSoundLen;//语音数据流的长度						*/
/*	UINT 	m_nErrorCode; 错误码，可能为如下值：				*/
/*		1)jTTS_NOERROR，连接建立成功							*/
/*		2)jTTS_MOREDATA，数据还没有发送完，请继续接收			*/
/*		3)jTTS_ERRPACK，包长度不正确，概率基本为0				*/
/*		4)jTTS_INVALIDTEXT，语音请求文本参数错误，可能是		*/
/*							文本指针指向一个空字符串			*/
/*		5)jTTS_MEMALLOCERR，内存分配错误						*/
/*		6)其他，jTTS_ERRMASK | jTTSSDK的错误码					*/
/*				为语音合成时jTTS SDK给出的错误					*/
/*																*/
/* !!!!注意：													*/
/*	语音数据包中不包含语音数据缓冲区!							*/
/*	或者说语音数据包仅仅是一个包头。							*/
/*	只要m_dwSoundLen不为0										*/
/*	其后将发送一个长度m_dwSoundLen个byte的语音数据.				*/
/*																*/
/*一个简单的接收过程如下(不考虑错误)：							*/
/*	1)接收语音数据包											*/
/*	2)m_dwSoundLen==0 ? 完成 : 接收m_dwSoundLen长度的语音数据	*/
/*	3)m_nErrorCode==jTTS_MOREDATA ? 转到第一步继续执行 : 完成	*/
/****************************************************************/
class CjTTSPtlAnsSound : public CjTTSSocketProtocal
{
public:
	UINT		m_nErrorCode;
	int			m_nBitsPerSample;
	int			m_nSamplesPerSec;
	DWORD		m_dwSoundLen;
	DWORD		m_dwReadBytes;
	unsigned char m_pData[1];
	CjTTSPtlAnsSound()
	{
		m_nErrorCode = jTTS_NOERROR;
		m_dwCommand = jTTS_ANS_SOUND;
		m_nBitsPerSample = -1;
		m_nSamplesPerSec = -1;
		m_dwSoundLen = 0;
		m_dwReadBytes = 0;
		m_dwLen = sizeof(*this);
		//肖海从Service程序中看出来的m_dwLen的实际含义
		//m_dwLen = offsetof(CjTTSPtlAnsSound, m_pData) + m_dwSoundLen;

	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		if (m_nBitsPerSample == 16){
			for(DWORD i = 0; i < m_dwSoundLen; i+=2)
			{
				H2N(*(WORD *)(m_pData + i));
			}
		}

		H2N(m_nErrorCode);
		H2N(m_nBitsPerSample);
		H2N(m_nSamplesPerSec);
		H2N(m_dwSoundLen);
		H2N(m_dwReadBytes);
	}
	void ntoh()
	{
		N2H(m_nErrorCode);
		N2H(m_nBitsPerSample);
		N2H(m_nSamplesPerSec);
		N2H(m_dwSoundLen);
		N2H(m_dwReadBytes);

		if (m_nBitsPerSample == 16){
			for(DWORD i = 0; i < m_dwSoundLen; i+=2)
			{
				N2H(*(WORD *)(m_pData + i));
			}
		}
	}
};

class CjTTSPtlAnsSound4 : public CjTTSSocketProtocal
{
public:
	UINT		m_nErrorCode;
	int			m_nBitsPerSample;
	int			m_nSamplesPerSec;
	DWORD		m_dwSoundLen;
	DWORD		m_dwInsertInfoNum;
	DWORD		m_dwReadBytes;
	unsigned char m_pData[1];
	CjTTSPtlAnsSound4()
	{
		m_nErrorCode = jTTS_NOERROR;
		m_dwCommand = jTTS_ANS_SOUND4;
		m_nBitsPerSample = -1;
		m_nSamplesPerSec = -1;
		m_dwSoundLen = 0;
		m_dwInsertInfoNum = 0;
		m_dwReadBytes = 0;
		m_dwLen = sizeof(*this);
		//肖海从Service程序中看出来的m_dwLen的实际含义
		//m_dwLen = offsetof(CjTTSPtlAnsSound, m_pData) + m_dwSoundLen + m_dwInsertInfoNum*sizeof(InsertInfo);
		//Sound紧跟m_dwReadBytes之后，InsertInfo在最后。
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();


		if (m_nBitsPerSample == 16){
			for(DWORD i = 0; i < m_dwSoundLen; i+=2)
			{
				H2N(*(WORD *)(m_pData + i));
			}
		}

		H2N(m_nErrorCode);
		H2N(m_nBitsPerSample);
		H2N(m_nSamplesPerSec);
		H2N(m_dwSoundLen);
		H2N(m_dwInsertInfoNum);
		H2N(m_dwReadBytes);
	}
	void ntoh()
	{
		N2H(m_nErrorCode);
		N2H(m_nBitsPerSample);
		N2H(m_nSamplesPerSec);
		N2H(m_dwSoundLen);
		N2H(m_dwInsertInfoNum);
		N2H(m_dwReadBytes);

		if (m_nBitsPerSample == 16){
			for(DWORD i = 0; i < m_dwSoundLen; i+=2)
			{
				N2H(*(WORD *)(m_pData + i));
			}
		}

	}
};

/****************************************************************/
/*	CjTTSPtlAnsUnknown: 无法识别接收到的客户请求，概率为0		*/
/*		DWORD m_dwCommand = jTTS_ANS_UNKNOWN					*/
/*  成员变量：无												*/
/****************************************************************/
class CjTTSPtlAnsUnknown : public CjTTSSocketProtocal
{
public:
	CjTTSPtlAnsUnknown()
	{
		m_dwCommand = jTTS_ANS_UNKNOWN;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
	}
	void ntoh()
	{
		
	}
};

/****************************************************************/
/*	CjTTSPtlAnsShutdown:  服务器退出							*/
/*		DWORD m_dwCommand = jTTS_ANS_SHUTDOWN					*/
/*  成员变量：无												*/
/****************************************************************/
class CjTTSPtlAnsShutdown : public CjTTSSocketProtocal
{
public:
	CjTTSPtlAnsShutdown()
	{
		m_dwCommand = jTTS_ANS_SHUTDOWN;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
	}
	void ntoh()
	{
		
	}
};

/****************************************************************/
/*	CjTTSPtlAnsOutoftime:  客户空闲时间超出设定阈值				*/
/*		DWORD m_dwCommand = jTTS_ANS_OUTOFTIME					*/
/*  成员变量：无												*/
/****************************************************************/
class CjTTSPtlAnsOutoftime : public CjTTSSocketProtocal
{
public:
	CjTTSPtlAnsOutoftime()
	{
		m_dwCommand = jTTS_ANS_OUTOFTIME;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
	}
	void ntoh()
	{
		
	}
};

// 返回音库数目
class CjTTSPtlAnsVoiceCount : public CjTTSSocketProtocal
{
public:
	int m_nVoiceCount;
	CjTTSPtlAnsVoiceCount()
	{
		m_dwCommand = jTTS_ANS_VOICECOUNT;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nVoiceCount);
	}
	void ntoh()
	{
		N2H(m_nVoiceCount);
	}
};

// 返回某个序号的音库属性
// m_nErrorCode 错误码，有如下值：
// jTTS_NOERROR: 没有错误
// jTTS_ERRPACK: 数据包接收错
// jTTS_PARAMOUTOFRANGE: Voice的Index超出正常范围
class CjTTSPtlAnsVoiceAttrib : public CjTTSSocketProtocal
{
public:
	UINT	m_nErrorCode;

	char		m_szName[VOICENAME_LEN];
	char 		m_szVoiceID[VOICEID_LEN];
	int		m_nGender;
	int		m_nAge;
	DWORD		m_dwDomainArray;
	int		m_nLanguage;
	char		m_szVendor[VENDOR_LEN];
	DWORD		m_dwVersionLS;
	DWORD		m_dwVersionMS;

	CjTTSPtlAnsVoiceAttrib()
	{
		m_nErrorCode = jTTS_NOERROR;
		m_dwCommand = jTTS_ANS_VOICEATTRIB;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nGender);
		H2N(m_nAge);
		H2N(m_dwDomainArray);
		H2N(m_nLanguage);
		H2N(m_dwVersionLS);
		H2N(m_dwVersionMS);

	}
	void ntoh()
	{
		N2H(m_nGender);
		N2H(m_nAge);
		N2H(m_dwDomainArray);
		N2H(m_nLanguage);
		N2H(m_dwVersionLS);
		N2H(m_dwVersionMS);
	}
};

// 返回服务器是否支持某个音库
// m_nErrorCode 错误码，有如下值：
// jTTS_NOERROR: 没有错误
// jTTS_ERRPACK: 数据包接收错
class CjTTSPtlAnsIsVoiceSupported : public CjTTSSocketProtocal
{
public:
	UINT	m_nErrorCode;

	int		m_bIsSupported;
	CjTTSPtlAnsIsVoiceSupported()
	{
		m_nErrorCode = jTTS_NOERROR;
		m_dwCommand = jTTS_ANS_ISVOICESUPPORTED;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nErrorCode);
	}
	void ntoh()
	{
		N2H(m_nErrorCode);
	}
};

// 返回选择音库的结果
// m_nErrorCode 错误码，有如下值：
// jTTS_NOERROR: 没有错误
// jTTS_ERRPACK: 数据包接收错
// jTTS_VOICENOTSUPPORTED: 没有查到符合条件的Voice
class CjTTSPtlAnsFindVoice : public CjTTSSocketProtocal
{
public:
	UINT	m_nErrorCode;
	WORD	m_wMatchFlag;
	char 	m_szVoiceID[VOICEID_LEN];
	CjTTSPtlAnsFindVoice()
	{
		m_nErrorCode = jTTS_NOERROR;
		m_dwCommand = jTTS_ANS_FINDVOICE;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nErrorCode);
		H2N(m_wMatchFlag);
	}
	void ntoh()
	{
		N2H(m_nErrorCode);
		N2H(m_wMatchFlag);
	}
};

class CjTTSPtlAnsAddText4 : public CjTTSSocketProtocal
{
public:
	UINT m_nErrorCode;
	CjTTSPtlAnsAddText4()
	{
		m_nErrorCode = jTTS_NOERROR;
		m_dwCommand = jTTS_ANS_ADDTEXT4;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nErrorCode);
	}
	void ntoh()
	{
		H2N(m_nErrorCode);
	}
};

//返回授权数
class CjTTSPtlAnsLicenceNum : public CjTTSSocketProtocal
{
public:
	UINT m_nLicenceNum;
	CjTTSPtlAnsLicenceNum()
	{
		m_dwCommand = jTTS_ANS_LICENCENUM;
		m_dwLen = sizeof(*this);
		m_nLicenceNum = 0;
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nLicenceNum);
	}
	void ntoh()
	{
		N2H(m_nLicenceNum);
	}
};


class CjTTSPtlAnsLicenseInfo : public CjTTSSocketProtocal
{
public:

	JTTS_LICENSEINFO m_licenseInfo;
	CjTTSPtlAnsLicenseInfo()
	{
		m_dwCommand = jTTS_ANS_LICENSEINFO;
		m_dwLen = sizeof(*this);
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
		H2N(m_licenseInfo.bService);
		H2N(m_licenseInfo.nSharedLines);
		H2N(m_licenseInfo.wLicenseType);
		H2N(m_licenseInfo.wVersion);
	}

	void ntoh()
	{
		N2H(m_licenseInfo.bService);
		N2H(m_licenseInfo.nSharedLines);
		N2H(m_licenseInfo.wLicenseType);
		N2H(m_licenseInfo.wVersion);
	}
};


class CjTTSPtlReqLangAttribute: public CjTTSSocketProtocal
{
public:
	int m_nIndex;

	CjTTSPtlReqLangAttribute()
	{
		m_dwCommand = jTTS_REQ_LANGATTRIBUTE;
		m_dwLen = sizeof(*this);
		m_nIndex = 0;
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nIndex);
	}
	void ntoh()
	{
		N2H(m_nIndex);
	}
};
	

class CjTTSPtlReqLangAttributeByValue: public CjTTSSocketProtocal
{
public:
	int m_nValue;

	CjTTSPtlReqLangAttributeByValue()
	{
		m_dwCommand = jTTS_REQ_LANGATTRIBUTEBYVALUE;
		m_dwLen = sizeof(*this);
		m_nValue = 0;
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nValue);
	}
	void ntoh()
	{
		N2H(m_nValue);
	}
};

class CjTTSPtlAnsLangAttribute: public CjTTSSocketProtocal
{
public:
	UINT	m_nErrorCode;
	int	m_nValue;
	char  m_szName[ATTRNAME_LEN];
	char  m_szEngName[ATTRNAME_LEN];
	char  m_szXmlLang[XMLLANG_LEN];

	CjTTSPtlAnsLangAttribute()
	{
		m_nErrorCode = jTTS_NOERROR;
		m_dwCommand = jTTS_ANS_LANGATTRIBUTE;
		m_dwLen = sizeof(*this);
		m_nValue = 0;
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
		
		H2N(m_nErrorCode);
		H2N(m_nValue);
	}

	void ntoh()
	{
		N2H(m_nErrorCode);
		N2H(m_nValue);
	}

};


class CjTTSPtlReqDomainAttribute: public CjTTSSocketProtocal
{
public:
	int m_nIndex;

	CjTTSPtlReqDomainAttribute()
	{
		m_dwCommand = jTTS_REQ_DOMAINATTRIBUTE;
		m_dwLen = sizeof(*this);
		m_nIndex = 0;
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nIndex);
	}
	void ntoh()
	{
		N2H(m_nIndex);
	}
};
	

class CjTTSPtlReqDomainAttributeByValue: public CjTTSSocketProtocal
{
public:
	int m_nValue;

	CjTTSPtlReqDomainAttributeByValue()
	{
		m_dwCommand = jTTS_REQ_DOMAINATTRIBUTEBYVALUE;
		m_dwLen = sizeof(*this);
		m_nValue = 0;
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nValue);
	}
	void ntoh()
	{
		N2H(m_nValue);
	}
};

class CjTTSPtlAnsDomainAttribute: public CjTTSSocketProtocal
{
public:
	UINT	m_nErrorCode;
	int	m_nValue;
	char  m_szName[ATTRNAME_LEN];
	char  m_szEngName[ATTRNAME_LEN];	

	CjTTSPtlAnsDomainAttribute()
	{
		m_nErrorCode = jTTS_NOERROR;
		m_dwCommand = jTTS_ANS_DOMAINATTRIBUTE;
		m_dwLen = sizeof(*this);
		m_nValue = 0;
	}

	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
		
		H2N(m_nErrorCode);
		H2N(m_nValue);
	}

	void ntoh()
	{
		N2H(m_nErrorCode);
		N2H(m_nValue);
	}

};

class CjTTSPtlReqLangCount: public CjTTSSocketProtocal
{
public:
	CjTTSPtlReqLangCount()
	{
		m_dwCommand = jTTS_REQ_LANGCOUNT;
		m_dwLen = sizeof(*this);
	}
	
	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
	}
	void ntoh()
	{
	}
};

class CjTTSPtlAnsLangCount: public CjTTSSocketProtocal
{
public:
	int m_nCount;

	CjTTSPtlAnsLangCount()
	{
		m_dwCommand = jTTS_ANS_LANGCOUNT;
		m_dwLen = sizeof(*this);

		m_nCount=0;
	}
	
	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nCount);
	}
	void ntoh()
	{
		N2H(m_nCount);
	}
};

class CjTTSPtlReqDomainCount: public CjTTSSocketProtocal
{
public:
	CjTTSPtlReqDomainCount()
	{
		m_dwCommand = jTTS_REQ_DOMAINCOUNT;
		m_dwLen = sizeof(*this);
	}
	
	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
	}
	void ntoh()
	{
	}
};

class CjTTSPtlAnsDomainCount: public CjTTSSocketProtocal
{
public:
	int m_nCount;

	CjTTSPtlAnsDomainCount()
	{
		m_dwCommand = jTTS_ANS_DOMAINCOUNT;
		m_dwLen = sizeof(*this);

		m_nCount=0;
	}
	
	void htonall()
	{
		CjTTSSocketProtocal::htonheader();

		H2N(m_nCount);
	}
	void ntoh()
	{
		N2H(m_nCount);
	}
};



class CjTTSPtlReqCounters: public CjTTSSocketProtocal
{
public:
	CjTTSPtlReqCounters()
	{
		m_dwCommand = jTTS_REQ_COUNTERS;
		m_dwLen = sizeof(*this);
	}
	
	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
	}
	void ntoh()
	{
	}
};


class CjTTSPtlAnsCounters : public CjTTSSocketProtocal
{
public:
	int m_nErrorCode;
	int m_nSession;
	CjTTSPtlAnsCounters()
	{
		m_nErrorCode = ERR_NONE;
		m_dwCommand = jTTS_ANS_COUNTERS;
		m_dwLen = sizeof(*this);
	}
	
	void htonall()
	{
		CjTTSSocketProtocal::htonheader();
		
		H2N(m_nErrorCode);
		H2N(m_nSession);
	}
	void ntoh()
	{
		N2H(m_nErrorCode);
		N2H(m_nSession);
	}
};


#pragma warning( pop )

#endif	//__jTTSPROTOCAL_H__