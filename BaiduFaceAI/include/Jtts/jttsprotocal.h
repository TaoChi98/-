/*
jTTS Protocal 4.0
*/

#ifndef __jTTSPROTOCAL_H__
#define __jTTSPROTOCAL_H__

#include <crtdbg.h>
#include "mytrace.h"

// �������ݽṹ�ͺ�����Ϊ��1.0�汾����
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

//������Socket�й�
#define jTTS_ID				0x5A5A5A5A	//Socket��ʶ���

#define jTTS_PACK_MAXLEN	1024	//ÿ��Socket����󳤶ȣ��ֽ���
									//�ı��ϳ���������������ݰ����ܴ˳�������

//����ΪSocketָ��
//��ʽ��jTTS_X1_X2
//X1==REQ�����Կͻ���; X1==ANS�����Է�������
//X2Ϊ��������
#define jTTS_REQ_SETPARAM			0x1001	//���������ϳɲ�������(V1.0)
#define jTTS_REQ_TEXT				0x1002	//�����ı�����
#define jTTS_REQ_CANCELSYNTH		0x1003	//ȡ����ǰ�ϳɹ���
#define jTTS_REQ_SETPARAM2			0x1004	//���������ϳɲ�������(V2.0)
#define jTTS_REQ_SETPARAM4			0x1010	//���������ϳɲ�������(V4.0)
#define jTTS_REQ_VOICECOUNT			0x1011	//��ѯ������Ŀ
#define jTTS_REQ_VOICEATTRIB		0x1012	//��ѯĳ����ŵ���������
#define jTTS_REQ_ISVOICESUPPORTED	0x1013	//��ѯ�������Ƿ�֧��ĳ������
#define jTTS_REQ_FINDVOICE			0x1014	//ѡ��һ������
#define jTTS_REQ_QUIT				0x1100	//��������
#define jTTS_REQ_TEXT4				0x1015	//jTTS4��Ӻϳ��ı���jTTSService��ʼһ����Session
#define jTTS_REQ_ADDTEXT4			0x1016	//����ı����ǰ��ĺϳ��Ѿ���ʱ���������ִ����ϳɡ�
#define jTTS_REQ_LICENCENUM		0x1017	//�����Ȩ��

#define jTTS_REQ_VOICEATTRIBBYID 0x1018	//ͨ��voiceId �����������

#define jTTS_REQ_LANGATTRIBUTE	0x1019	//ͨ��index�����������
#define jTTS_REQ_LANGATTRIBUTEBYVALUE 0x1020 //ͨ������ֵ�����������

#define jTTS_REQ_COUNTERS			 0x1021	//���������

#define jTTS_REQ_DOMAINATTRIBUTE			0x1022		//ͨ��index�����������
#define jTTS_REQ_DOMAINATTRIBUTEBYVALUE		0x1023		//ͨ������ֵ�����������

#define jTTS_REQ_LANGCOUNT		0x1024					//�������ֵ�ĸ���
#define jTTS_REQ_DOMAINCOUNT		0x1025				//�������ֵ�ĸ���
#define jTTS_REQ_LICENSEINFO	0x1026					//�����Ȩ��Ϣ

//-----Xiaohai Add for 3.0---------
#define jTTS_REQ_WFSYN			0x1005	//�ʿ�ͬ������
#define jTTS_REQ_WFSYNEND		0x1006	//�ʿ�ͬ����������Ҫ�����������ʹ�´ʿ���Ч
#define jTTS_REQ_LBAUTHENADD	0x1007	//���ؾ��������֤����(����һ�������ϳ��߳�)
#define jTTS_REQ_LBAUTHENSUB	0x1008	//���ؾ��������֤����(����һ�������ϳ��߳�)
//---------------------------------

#define jTTS_ANS_CONNECT			0x4000	//���ӷ�����Ӧ��
#define jTTS_ANS_SETPARAM			0x4001	//���������ϳɲ���Ӧ��
#define jTTS_ANS_SOUND				0x4002	//����������
#define jTTS_ANS_SOUND4				0x4003	//����������V4
#define jTTS_ANS_UNKNOWN			0x4080	//���������յ�һ��δ֪�����Socket��
#define jTTS_ANS_SHUTDOWN			0x4100	//�������쳣�˳�,������CjTTSConfig������StopServer����
#define	jTTS_ANS_OUTOFTIME		0x4101	//�ͻ���ʱ��������ʱ�䳬���趨��ֵ
#define jTTS_ANS_VOICECOUNT		0x4011	//����������Ŀ
#define jTTS_ANS_VOICEATTRIB		0x4012	//����ĳ����ŵ���������
#define jTTS_ANS_ISVOICESUPPORTED	0x4013	//���ط������Ƿ�֧��ĳ������
#define jTTS_ANS_FINDVOICE			0x4014	//����ѡ������Ľ��
#define jTTS_ANS_ADDTEXT4			0x4015	//����ı�Ӧ��
#define jTTS_ANS_LICENCENUM		0x4016	//������Ȩ��
#define jTTS_ANS_LANGATTRIBUTE	0x4017	//������������
#define jTTS_ANS_COUNTERS		0x4018	//���ؼ�����
#define jTTS_ANS_DOMAINATTRIBUTE	0x4019	//������������
#define jTTS_ANS_LANGCOUNT		0x4020					//��������ֵ�ĸ���
#define jTTS_ANS_DOMAINCOUNT		0x4021				//��������ֵ�ĸ���
#define jTTS_ANS_LICENSEINFO	0x4022	 //������Ȩ��Ϣ 	

//------Xiaohai Add for 3.0----------
#define jTTS_ANS_WFSYN			0x4005	//�ʿ�ͬ������Ӧ��
#define jTTS_ANS_SERVICERESTART 0x4006	//ʹ�´ʿ���Ч�����������������ɣ���������һ�����������дʿ�ͬ��
#define jTTS_ANS_LBAUTHEN		0x4007	//���ؾ��������֤Ӧ��
//-----------------------------------

//����Ϊϵͳ����
#define jTTS_PORTMAX			32767	//�˿ں����ֵ
#define jTTS_PORTMIN			1		//�˿ں���Сֵ
#define jTTS_REQNUMMAX			255		//�������������ֵ
#define jTTS_REQNUMMIN			1		//������������Сֵ
#define jTTS_IDLETIMEMAX		100		//����ʱ�����ֵ
#define jTTS_IDLETIMEMIN		0		//����ʱ����Сֵ  //xiaohai ��1�޸�Ϊ0��0��ʾû�г�ʱ���ơ�02-01-17


//����Ϊ������
#define jTTS_NOERROR				0	//������ȷ���
#define jTTS_AUTODISCONNECT			1	//�û���ʱ
#define jTTS_SYNTHCOMPLETE			2	//�����ϳ����
#define jTTS_SERVERSTART			3	//����������
#define jTTS_SERVERSHUTDOWN			4	//�������˳�
#define jTTS_PARAMOUTOFRANGE		0xA0010001//�����������趨��Χ
#define jTTS_PARAMERR				0xA0010002//��������
#define jTTS_INVALIDTEXT			0xA0010003//������ı��������������ı�ָ��ָ��һ�����ַ���
#define jTTS_TOOMANYCONNECTIONS		0xA0020001//���������Ӵ����趨����ֵ
#define jTTS_PREVSYNTHNOTCOMPLETE	0xA0020002//�ϴ������ϳɹ��̲�δ��ȫ����
#define jTTS_ERRMASK				0xA0030000//jTTS��������
#define jTTS_MOREDATA				0xA0040001//��������û�з����꣬�����������������
#define jTTS_SYNTHBECANCELED		0xA0050001//�û�ȡ���������ϳɹ���
#define jTTS_SOCKETERR				0xA0100001//����socket����
#define jTTS_JTTSINITERR			0xA0100002//jTTS SDK��ʼ������
#define jTTS_DOGERR					0xA0100003//�������ȡ����
#define jTTS_STOPERR				0xA0100010//ֹͣsocket����
#define jTTS_MEMALLOCERR			0xA0110001//�ڴ�������
#define jTTS_ERRPACK				0xA0120001//���յ�һ������İ�������ΪID���������ȴ���
#define jTTS_VOICENOTSUPPORTED		0xA0130001//û�в鵽���ʵ�Voice
#define jTTS_ADDTEXT4				0xA0140001//AddText֮ǰ��û��SessionStart,��û�з���jTTS_REQ_TEXT4
#define jTTS_TEXT4					0xA0140002//jTTS_REQ_TEXT4����jTTS_REQ_TEXT�����ĺϳ��̻߳�������
#define jTTS_ERRUNKNOWN				0xA0200001//δ֪����

#pragma warning( push )
#pragma warning( disable : 4244 )

//�������Releaseѡ���Ż��Ժ���Ż�,��Ϊsizeof���ڱ����ʱ��Ϳ���ȷ����,���Բ��ص���Ч��

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
/*	CjTTSSocketProtocalΪ����Socket����Ļ���					*/
/*  ��Ա������													*/
/*	DWORD m_dwID;		jTTSʶ������̶�ΪjTTS_ID, ��0x5A5A5A5A	*/
/*	DWORD m_dwCommand;  Socketָ�����Ϊ�����ᵽ��9��֮һ		*/
/*	DWORD m_dwLen;		�������ĳ��ȣ��ֽ�����					*/
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
#ifdef CHECK_DEBUG  //������������ظ���������,���һ��
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
#ifdef CHECK_DEBUG  //������������ظ���������,���һ��
		m_checkntoh ++;
		_ASSERTE(m_checkntoh < 2);
		_ASSERTE(m_checkhton == 1);	//ȷ����֮ǰ���ù�htonheader
#endif		

		N2H(m_dwID);
		N2H(m_dwCommand);
		N2H(m_dwLen);
		MYTRACE("CjTTSSocketProtocal::ntohheader()\n");
	}
};

#define	JTTS_HEADERLEN		sizeof(CjTTSSocketProtocal)

//////////////////////////////////////////////////
//  xiaohai add ���ؾ��������֤�����			//
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
// xiaohai add ���ؾ��������֤Ӧ���			//
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
//	CjTTSReqWFSyn: ���ʹʿ�ͬ�����ݰ�			//
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
		m_dwLen = sizeof(*this);	//������Ϊ�����ʿ�ͬ���ı���ʵ�ʰ�����
		m_ptszText[0] = '\0';					//���ʿ�ͬ���ı���������λ��
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
//  Xiaohai add for �ʿ�ͬ����������Ҫ���������	//
//  CjTTSReqWFSynEnd: �ʿ�ͬ���������ݰ�			//
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
//	CjTTSAnsWFSyn: �ʿ�ͬ����Ӧ���ݰ�				//
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
//  Xiaohai add for ʹ�´ʿ���Ч�ķ����������Ѿ����	//
//  CjTTSAnsServiceRestart: ����������������ݰ�		//
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


//�����Ȩ��
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

//����Ϊ�ͻ���Socket������ǰ�汾����3��

/****************************************************************/
/*	CjTTSPtlReqSetParam: �趨�����ϳɲ�������					*/
/*		Ϊ��Ӧ�������Ӧ���ΪCjTTSPtlAnsSetParam				*/
/*		m_dwCommand = jTTS_REQ_SETPARAM							*/
/*  ��Ա������													*/
/*	JTTSCONFIG 	m_jTTSConfig;�����ϳɲ���						*/
/*	int			m_nFormat;   �����ʽ��������������ļ����		*/
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
/*	CjTTSPtlReqSetParam2: �趨�����ϳɲ�������					*/
/*		Ϊ��Ӧ�������Ӧ���ΪCjTTSPtlAnsSetParam2			*/
/*		m_dwCommand = jTTS_REQ_SETPARAM							*/
/*  ��Ա������													*/
/*	JTTSCONFIG2	m_jTTSConfig2;�����ϳɲ���						*/
/*	int			m_nFormat;   �����ʽ��������������ļ����		*/
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
/*	CjTTSPtlReqText: �����ϳ�����								*/
/*		Ϊ��Ӧ�������Ӧ���ΪCjTTSPtlAnsSound				*/
/*		DWORD m_dwCommand = jTTS_REQ_TEXT						*/
/*  ��Ա������													*/
/*	DWORD m_dwTextLen���ϳ��ı�char�ַ��ĸ�����				*/
/*		������UNICODE�汾��ʵ���ַ���Ϊ2*m_dwTextLen			*/
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
/*	CjTTSPtlReqText4: �����ϳ�����V4							*/
/*		Ϊ��Ӧ�������Ӧ���ΪCjTTSPtlAnsSound				*/
/*		DWORD m_dwCommand = jTTS_REQ_TEXT4						*/
/*  ��Ա������													*/
/*	DWORD m_dwTextLen���ϳ��ı�char�ַ��ĸ�����				*/
/*		������UNICODE�汾��ʵ���ַ���Ϊ2*m_dwTextLen			*/
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
/*	CjTTSPtlReqCancelSynth: ȡ����ǰ�����ϳɹ��̣���Ӧ��		*/
/*		DWORD m_dwCommand = jTTS_REQ_CANCELSYNTH				*/
/*  ��Ա��������												*/
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
/*	CjTTSPtlReqQuit: �ͻ��˳�������Ӧ��						*/
/*		DWORD m_dwCommand = jTTS_REQ_QUIT						*/
/*  ��Ա��������												*/
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

//���������ϳɲ�������(V4.0)
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

	//����JTTS_CONFIG��ʱ���Ӧ���޸��������
	void htonJTTS_CONFIG(JTTS_CONFIG & jconfig)
	{
		//���������Բ�����˵����� JTTS_CONFIG�ṹ�����޸�,��Ӧ����Ӧ�޸��������,
		//����sizeof(jconfig)���ĳ���ȷ��ֵ
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

	//����JTTS_CONFIG��ʱ���Ӧ���޸��������
	void ntohJTTS_CONFIG(JTTS_CONFIG & jconfig)
	{
		//���������Բ�����˵����� JTTS_CONFIG�ṹ�����޸�,��Ӧ����Ӧ�޸��������,
		//����sizeof(jconfig)���ĳ���ȷ��ֵ
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
//��ѯ������Ŀ
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

//��ѯĳ����ŵ���������
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

//��ѯ�������Ƿ�֧��ĳ������
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
//ѡ��һ������
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


//����Ϊ��������Socket������ǰ�汾����5��

/****************************************************************/
/*	CjTTSPtlAnsConnect: ���ͻ���ͼ�ͷ�������������ʱ��			*/
/*		��������ͻ���������Ӧ��ָʾ�����Ƿ�ɹ�������		*/
/*		DWORD m_dwCommand = jTTS_ANS_CONNECT					*/
/*  ��Ա������													*/
/*	UINT 	m_nErrorCode; �����룬����Ϊ����ֵ��				*/
/*		1)jTTS_NOERROR�����ӽ����ɹ�							*/
/*		2)jTTS_TOOMANYCONNECTIONS����ǰ�����������Ѵﵽ�趨��ֵ	*/
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
/*	CjTTSPtlAnsSetParam: ���ͻ����������ϳɲ����趨����ʱ��		*/
/*		��������ͻ�����Ӧ��ָʾ�����趨�Ƿ�ɹ���			*/
/*		DWORD m_dwCommand = jTTS_ANS_SETPARAM					*/
/*  ��Ա������													*/
/*	UINT 	m_nErrorCode; �����룬����Ϊ����ֵ��				*/
/*		1)jTTS_NOERROR�����ӽ����ɹ�							*/
/*		2)jTTS_ERRPACK�������Ȳ���ȷ�����ʻ���Ϊ0				*/
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
/*	CjTTSPtlAnsSound: ���ͻ����������ϳ�����ʱ��				*/
/*		��������ͻ�����Ӧ��ָʾ���������Ƿ�ɹ���ɡ�		*/
/*		DWORD m_dwCommand = jTTS_ANS_SOUND						*/
/*  ��Ա������													*/
/*	int		m_nBitsPerSample;//������ÿ������λ��				*/
/*	int		m_nSamplesPerSec;//������ÿ��Ĳ�����				*/
/*	DWORD	m_dwSoundLen;//�����������ĳ���						*/
/*	UINT 	m_nErrorCode; �����룬����Ϊ����ֵ��				*/
/*		1)jTTS_NOERROR�����ӽ����ɹ�							*/
/*		2)jTTS_MOREDATA�����ݻ�û�з����꣬���������			*/
/*		3)jTTS_ERRPACK�������Ȳ���ȷ�����ʻ���Ϊ0				*/
/*		4)jTTS_INVALIDTEXT�����������ı��������󣬿�����		*/
/*							�ı�ָ��ָ��һ�����ַ���			*/
/*		5)jTTS_MEMALLOCERR���ڴ�������						*/
/*		6)������jTTS_ERRMASK | jTTSSDK�Ĵ�����					*/
/*				Ϊ�����ϳ�ʱjTTS SDK�����Ĵ���					*/
/*																*/
/* !!!!ע�⣺													*/
/*	�������ݰ��в������������ݻ�����!							*/
/*	����˵�������ݰ�������һ����ͷ��							*/
/*	ֻҪm_dwSoundLen��Ϊ0										*/
/*	��󽫷���һ������m_dwSoundLen��byte����������.				*/
/*																*/
/*һ���򵥵Ľ��չ�������(�����Ǵ���)��							*/
/*	1)�����������ݰ�											*/
/*	2)m_dwSoundLen==0 ? ��� : ����m_dwSoundLen���ȵ���������	*/
/*	3)m_nErrorCode==jTTS_MOREDATA ? ת����һ������ִ�� : ���	*/
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
		//Ф����Service�����п�������m_dwLen��ʵ�ʺ���
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
		//Ф����Service�����п�������m_dwLen��ʵ�ʺ���
		//m_dwLen = offsetof(CjTTSPtlAnsSound, m_pData) + m_dwSoundLen + m_dwInsertInfoNum*sizeof(InsertInfo);
		//Sound����m_dwReadBytes֮��InsertInfo�����
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
/*	CjTTSPtlAnsUnknown: �޷�ʶ����յ��Ŀͻ����󣬸���Ϊ0		*/
/*		DWORD m_dwCommand = jTTS_ANS_UNKNOWN					*/
/*  ��Ա��������												*/
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
/*	CjTTSPtlAnsShutdown:  �������˳�							*/
/*		DWORD m_dwCommand = jTTS_ANS_SHUTDOWN					*/
/*  ��Ա��������												*/
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
/*	CjTTSPtlAnsOutoftime:  �ͻ�����ʱ�䳬���趨��ֵ				*/
/*		DWORD m_dwCommand = jTTS_ANS_OUTOFTIME					*/
/*  ��Ա��������												*/
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

// ����������Ŀ
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

// ����ĳ����ŵ���������
// m_nErrorCode �����룬������ֵ��
// jTTS_NOERROR: û�д���
// jTTS_ERRPACK: ���ݰ����մ�
// jTTS_PARAMOUTOFRANGE: Voice��Index����������Χ
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

// ���ط������Ƿ�֧��ĳ������
// m_nErrorCode �����룬������ֵ��
// jTTS_NOERROR: û�д���
// jTTS_ERRPACK: ���ݰ����մ�
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

// ����ѡ������Ľ��
// m_nErrorCode �����룬������ֵ��
// jTTS_NOERROR: û�д���
// jTTS_ERRPACK: ���ݰ����մ�
// jTTS_VOICENOTSUPPORTED: û�в鵽����������Voice
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

//������Ȩ��
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