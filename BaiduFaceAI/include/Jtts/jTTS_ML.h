#ifndef _JTTS_ML_H_
#define _JTTS_ML_H_

#pragma pack( push, jtts_ml_h )
#pragma pack( 8 )

#ifdef __cplusplus
extern "C"
{
#endif

#define TTSAPI __stdcall

//ERRCODE
typedef enum 
{
	ERR_NONE,			//	0
	ERR_ALREADYINIT,	//	1
	ERR_NOTINIT,		//	2 
	ERR_MEMORY,			//	3
	ERR_INVALIDHWND,	//	4
	ERR_INVALIDFUNC,	//	5
	ERR_OPENLIB,		//	6
	ERR_READLIB,		//	7
	ERR_PLAYING,		//	8
	ERR_DONOTHING,		//	9
	ERR_INVALIDTEXT,	//	10
	ERR_CREATEFILE,		//	11
	ERR_WRITEFILE,		//	12
	ERR_FORMAT,			//	13
	ERR_INVALIDSESSION,	//	14
	ERR_TOOMANYSESSION,	//	15
	ERR_MORETEXT,		//	16
	ERR_CONFIG,			//	17
	ERR_OPENDEVICE,		//	18
	ERR_RESETDEVICE,	//	19
	ERR_PAUSEDEVICE,	//	20
	ERR_RESTARTDEVICE,	//	21
	ERR_STARTTHREAD,	//	22
	ERR_BEGINOLE,		//	23
	ERR_NOTSUPPORT,		//	24
	ERR_SECURITY,		//	25
	ERR_CONVERT,		//	26
	ERR_PARAM,			//	27
	ERR_INPROGRESS,		//  28
	ERR_INITSOCK,		//	29
	ERR_CREATESOCK,		//	30
	ERR_CONNECTSOCK,	//	31
	ERR_TOOMANYCON,		//	32
	ERR_CONREFUSED,		//	33
	ERR_SEND,			//	34
	ERR_RECEIVE,		//	35
	ERR_SERVERSHUTDOWN,	//	36
	ERR_OUTOFTIME,		//	37
	ERR_CONFIGTTS,		//	38
	ERR_SYNTHTEXT,		//	39
	ERR_CONFIGVERSION,	//	40
	ERR_EXPIRED,		//	41
	ERR_NEEDRESTART,	//	42
	ERR_CODEPAGE,		//	43
	ERR_ENGINE,			//	44
	ERR_CREATEEVENT,	//	45
	ERR_PLAYMODE,		//	46
	ERR_OPENFILE,		//	47
	ERR_USERABORT,		//	48
	ERR_LICENSEFULL,	//	49
	ERR_LICENSEFILEINVALID,	//	50
	ERR_LICENSE,            //	51 
	ERR_LICENSEEXPIRED,		//	52

	ERR_ENOUGHSPACE,       //53 ------add by binfeng 2006-12-28
}ERRCODE;

//---------------------------------------------------------------------------
// ϵͳ������ѡ��

//֧�ֶ�����
//
//�����г�����ϵͳ�ڽ������Զ��壬��Ҫ��װ��Ӧ�����������֧��, 
//��Ŀǰ�����������Զ�����Ӧ������
//
//��������û���г������ԣ�����Ҳ���ܻᷢ����Ӧ�����⣬ͬʱ�����һ����ֵ��
//ֻҪ��װ������󣬾Ϳ���ʹ�á�����û���г������ԣ������ʹ�ã�����ֱ��ʹ����ֵ
//
//����ͨ��Langϵ�к����õ�����ϵͳ�ж���ģ�����������չ�ģ�������ֵ������������Ϣ
//
//����ϵͳ������֧�ֵ����ԣ�����ͨ��jTTS_GetVoiceCount, jTTS_GetVoiceAttribute����
//�õ����а�װ�����⣬������������֪��������
//
#define LANGUAGE_MANDARIN				0	// ������ͨ��
#define LANGUAGE_CANTONESE				1	// �㶫��
#define LANGUAGE_CHINESE				LANGUAGE_MANDARIN

#define LANGUAGE_US_ENGLISH				10	// ����Ӣ��
#define LANGUAGE_BRITISH_ENGLISH		11	// Ӣ��Ӣ��
#define LANGUAGE_ENGLISH				LANGUAGE_US_ENGLISH

#define LANGUAGE_FRENCH					20	// ����
#define LANGUAGE_CANADIAN_FRENCH		21	// ���ô���

#define LANGUAGE_SPANISH				30	// ��������
#define LANGUAGE_LATINAMERICAN_SPANISH	31	// ����������������

#define LANGUAGE_PORTUGUESE				40	// ��������
#define LANGUAGE_BRAZILIAN_PORTUGUESE	41	// ������������

#define LANGUAGE_DUTCH					50	// ������
#define LANGUAGE_BELGIAN_DUTCH			51	// ����ʱ������

#define LANGUAGE_GERMAN					60	// ����
#define LANGUAGE_ITALIAN				70	// �������
#define LANGUAGE_SWEDISH				80	// �����
#define LANGUAGE_NORWEGIAN				90	// Ų����
#define LANGUAGE_DANISH					100	// ������
#define LANGUAGE_POLISH					110 // ������
#define LANGUAGE_GREEK					120	// ϣ����
#define LANGUAGE_HUNGARIAN				130 // ��������
#define LANGUAGE_CZECH					140 // �ݿ���
#define LANGUAGE_TURKISH				150 // ��������

#define LANGUAGE_RUSSIAN				500	// ����

#define LANGUAGE_ARABIC					600	// ��������

#define LANGUAGE_JAPANESE				700	// ����
#define LANGUAGE_KOREAN					710 // ����

#define LANGUAGE_VIETNAMESE				720 // Խ����
#define LANGUAGE_MALAY					730	// ������
#define LANGUAGE_THAI					740 // ̩��

//֧�ֶ�����
// 
//�����г�����ϵͳ�ڽ��������壬��Ҫ��װ��Ӧ�������Դ����������֧�֡�
//
//��������û���г������򣬽���Ҳ���ܻᷢ����Ӧ����Դ����ͬʱ�����һ����ֵ��
//ֻҪ��װ����Դ���󣬾Ϳ���ʹ�á�����û���г������������ʹ�ã�����ֱ��ʹ����ֵ
//
//����ͨ��Domainϵ�к����õ�����ϵͳ�ж���ģ�����������չ�ģ�������ֵ������������Ϣ
//
//����ϵͳ������֧�ֵ����򣬿���ͨ��jTTS_GetDomainCount, jTTS_GetDomainAttribute����
//�õ����а�װ������
#define DOMAIN_COMMON			0		// ͨ����������
#define DOMAIN_FINANCE			1		// ����֤ȯ
#define DOMAIN_WEATHER			2		// ����Ԥ��
#define DOMAIN_SPORTS			3		// ��������
#define DOMAIN_TRAFFIC			4		// ������Ϣ
#define DOMAIN_TRAVEL			5		// ���β���
#define DOMAIN_CARBORNE			6		//����
#define DOMAIN_QUEUE			7		//�Ŷ�
#define DOMAIN_SONG				8		//���
#define DOMAIN_INSURANCE		9		//����
#define DOMAIN_VOYAGE			10		//����
#define DOMAIN_REVENUE			11		//˰��
#define DOMAIN_ELECPOWER		12		//����
#define DOMAIN_MESSAGE			13		//����


#define DOMAIN_CUSTOM			30		// һ�㶨������

#define DOMAIN_MIN				0
#define DOMAIN_MAX				31

//֧�ֵ�CODEPAGE
#define CODEPAGE_GB		        936		// ����GB18030, GBK, GB2312
#define CODEPAGE_BIG5		    950
#define CODEPAGE_SHIFTJIS	    932
#define CODEPAGE_KCS			949
#define CODEPAGE_ISO8859_1		1252
#define CODEPAGE_UNICODE		1200
#define CODEPAGE_UNICODE_BIGE	1201	// BIG Endian
#define CODEPAGE_UTF8 			65001

//֧��TAG
#define TAG_AUTO				0x00	// �Զ��ж�
#define TAG_JTTS				0x01	// ��������jTTS 3.0֧�ֵ�TAG: \read=\  
#define TAG_SSML				0x02	// ��������SSML ��TAG: <voice gender="female" />
#define TAG_NONE				0x03	// û��TAG

//DigitMode
#define DIGIT_AUTO_NUMBER		0
#define DIGIT_TELEGRAM			1
#define DIGIT_NUMBER			2
#define DIGIT_AUTO_TELEGRAM		3

#define DIGIT_AUTO				DIGIT_AUTO_NUMBER

// PuncMode
#define PUNC_OFF				0	/* �������ţ��Զ��жϻس������Ƿ�ָ���*/
#define PUNC_ON					1	/* �����ţ�  �Զ��жϻس������Ƿ�ָ���*/
#define PUNC_OFF_RTN			2	/* �������ţ�ǿ�ƽ��س�������Ϊ�ָ���*/
#define PUNC_ON_RTN				3	/* �����ţ�  ǿ�ƽ��س�������Ϊ�ָ���*/

// EngMode
#define ENG_AUTO				0	/* �Զ���ʽ */
#define ENG_SAPI				1	/* ǿ�Ʋ���Ӣ�Ķ��� */
#define ENG_LETTER				2	/* ǿ�Ƶ���ĸ��ʽ */
#define ENG_LETTER_PHRASE		3	/* ǿ�Ʋ�����ĸ����¼���ʻ�ķ�ʽ */

//Gender
#define GENDER_FEMALE			0
#define GENDER_MALE				1
#define GENDER_NEUTRAL			2

//AGE
#define AGE_BABY				0		//0 - 3
#define AGE_CHILD				1		//3 - 12
#define AGE_YOUNG				2		//12 - 18
#define AGE_ADULT				3		//18 - 60
#define AGE_OLD					4		//60 -

//PITCH
#define PITCH_MIN				0
#define PITCH_MAX				9

//VOLUME
#define VOLUME_MIN				0
#define VOLUME_MAX				9

//SPEED
#define SPEED_MIN				0
#define SPEED_MAX				9

//AUDIOVOLUME
#define AUDIOVOLUME_MIN			0
#define AUDIOVOLUME_MAX			100

//BACKAUDIOFLAG
#define BACKAUDIOFLAG_REPEAT	0x01
#define BACKAUDIOFLAG_DEFAULT	0x00

//BACKAUDIO
#define BACKAUDIO_NONE			0		// û�б�������
#define BACKAUDIO_MIN			1		// ��С�ı����������
#define BACKAUDIO_MAX			10000	// ���ı����������

//VOICESYTLE
#define VOICESTYLE_CADENCE		0		// ����ٴ�
#define VOICESTYLE_FLAT			1		// ƽ��ׯ��

//VOICEBUFSIZE
#define VOICEBUFSIZE_DEFAULT	0		// Default: 128K
#define VOICEBUFSIZE_MIN		16		// 16K
#define VOICEBUFSIZE_MAX		8192	// 8M

//INSERTINFOSIZE
#define INSERTINFOSIZE_DEFAULT	0		// Default: 100
#define INSERTINFOSIZE_MIN		1
#define INSERTINFOSIZE_MAX		1000

//---------------------------------------------------------------------------

//jTTS_Play״̬	
#define STATUS_NOTINIT	0
#define STATUS_READING	1
#define STATUS_PAUSE	2
#define STATUS_IDLE		3

//jTTS_PlayToFile���ļ���ʽ
#define FORMAT_WAV			0	// PCM Native (������һ�£�ĿǰΪ16KHz, 16Bit)
#define FORMAT_VOX_6K		1	// OKI ADPCM, 6KHz, 4bit (Dialogic Vox)
#define FORMAT_VOX_8K		2	// OKI ADPCM, 8KHz, 4bit (Dialogic Vox)
#define FORMAT_ALAW_8K		3	// A��, 8KHz, 8Bit
#define FORMAT_uLAW_8K		4	// u��, 8KHz, 8Bit
#define FORMAT_WAV_8K8B		5	// PCM, 8KHz, 8Bit
#define FORMAT_WAV_8K16B	6	// PCM, 8KHz, 16Bit
#define FORMAT_WAV_16K8B	7	// PCM, 16KHz, 8Bit
#define FORMAT_WAV_16K16B	8	// PCM, 16KHz, 16Bit
#define FORMAT_WAV_11K8B	9	// PCM, 11.025KHz, 8Bit
#define FORMAT_WAV_11K16B	10	// PCM, 11.025KHz, 16Bit

#define FORMAT_FIRST		0
#define FORMAT_LAST			10

// jTTS_Play / jTTS_PlayToFile / jTTS_SessionStart ����֧�ֵ�dwFlag����

// �������jTTS_PlayToFile����
#define PLAYTOFILE_DEFAULT		0x0000	//Ĭ��ֵ,д�ļ�ʱֻ����FORMAT_WAV_...��ʽ���ļ�ͷ
#define PLAYTOFILE_NOHEAD		0x0001	//���еĸ�ʽ���������ļ�ͷ
#define PLAYTOFILE_ADDHEAD		0x0002	//����FORMAT_WAV_...��ʽ��FORMAT_ALAW_8K,FORMAT_uLAW_8K��ʽ���ļ�ͷ

#define PLAYTOFILE_MASK			0x000F

// �������jTTS_Play����
#define PLAY_RETURN				0x0000	// ������ڲ��ţ����ش���
#define PLAY_INTERRUPT			0x0010	// ������ڲ��ţ����ԭ���Ĳ��ţ����������µ�����

#define PLAY_MASK				0x00F0

// ���ŵ�����
#define PLAYCONTENT_TEXT		0x0000	// ��������Ϊ�ı�
#define PLAYCONTENT_TEXTFILE	0x0100	// ��������Ϊ�ı��ļ�
#define PLAYCONTENT_AUTOFILE	0x0200	// ��������Ϊ�ļ������ݺ�׺���������Filter DLL��ȡ
										// �޷��жϵĵ����ı��ļ�

#define PLAYCONTENT_MASK		0x0F00

// ���ŵ�ģʽ��ͬʱ����SessionStart
#define PLAYMODE_DEFAULT		0x0000	// ��jTTS_Play��ȱʡ�첽����jTTS_PlayToFile��ȱʡͬ��
										// jTTS_SessionStart��Ϊ������ȡ���ݷ�ʽ
#define PLAYMODE_ASYNC			0x1000	// �첽���ţ����������˳�
#define PLAYMODE_SYNC			0x2000	// ͬ�����ţ�������ɺ��˳�

#define PLAYMODE_MASK			0xF000

// jTTS_FindVoice���ص�ƥ�伶��
#define MATCH_LANGUAGE			0	// ����LANGUAGE��
#define MATCH_GENDER			1	// ����LANGUAGE, GENDER
#define MATCH_AGE				2	// ����LANGUAGE, GENDER, AGE
#define MATCH_NAME				3	// ����LANGUAGE, GENDER��AGE��NAME
#define MATCH_DOMAIN			4	// ����LANGUAGE, GENDER��AGE��NAME, DOMAIN��Ҳ��������������
#define MATCH_ALL				4	// ������������

// InsertInfo��Ϣ
#define INFO_MARK				0
#define INFO_VISEME				1

//������Ϣ���ĳ���
#define VOICENAME_LEN			32
#define VOICEID_LEN				40
#define VENDOR_LEN				32
#define DLLNAME_LEN				256

#define ATTRNAME_LEN			32
#define XMLLANG_LEN				256

//JTTS_PARAM
typedef enum 
{
	PARAM_CODEPAGE,			// CODEPAGE_xxx
	PARAM_VOICEID,			// Voice ID
	PARAM_PITCH,			// PITCH_MIN - PITCH_MAX
	PARAM_VOLUME,		    // VOLUME_MIN - VOLUME_MAX
	PARAM_SPEED,			// SPEED_MIN - SPEED_MAX
	PARAM_PUNCMODE,			// PUNC_xxx
	PARAM_DIGITMODE,		// DIGIT_xxx
	PARAM_ENGMODE,			// ENG_xxx
	PARAM_TAGMODE,			// TAG_xxx
	PARAM_DOMAIN,		    // DOMAIN_xxx
	PARAM_TRYTIMES,         // 0-100
	PARAM_IDLETIME,         // 0-60 (s), default 10, 0 means ���޵ȴ�
	PARAM_LOADBALANCE,		// TRUE, FALSE
	PARAM_VOICESTYLE,		// VOICESTYLE_CADENCE, VOICESTYLE_FLAT
	PARAM_BACKAUDIO,		// BACKAUDIO_NONE, BACKAUDIO_MIN - BACKAUDIO_MAX
	PARAM_BACKAUDIOVOLUME,	// AUDIOVOLUME_MIN - AUDIOVOLUME_MAX
	PARAM_BACKAUDIOFLAG,	// BACKAUDIOFLAG_xxx
	PARAM_VOICEBUFSIZE,		// VOICEBUFSIZE_DEFAULT, or n (K)
	PARAM_INSERTINFOSIZE,	// INSERTINFOSIZE_DEFAULT, or n
}
JTTS_PARAM;


//JTTS_CONFIG
#define JTTS_VERSION4		0x0004	// version 4.0
typedef struct JTTS_CONFIG_T
{
	WORD	wVersion;				// JTTS_VERSION4
	WORD	nCodePage;
	char	szVoiceID[VOICEID_LEN];	// ʹ�õ���ɫ
	short	nDomain;	
	short	nPitch;
	short	nVolume;
	short	nSpeed;
	short	nPuncMode;
	short	nDigitMode;
	short	nEngMode;
	short	nTagMode;
	short   nTryTimes;			// ���Դ���,�˳�Ա������Զ�̺ϳ�
	short	nIdleTime;		//////////////////////////////////////////	
	BOOL    bLoadBalance;		// ����ƽ��,�˳�Ա������Զ�̺ϳ�
	short	nVoiceStyle;		// �ʶ����
	short	nBackAudio;			// BACKAUDIO_NONE: �ޱ������֣�BACKAUDIO_MIN-BACKAUDIO_MAX: ����������ţ�����Դ��������"¼��������"�ж���
	short	nBackAudioVolume;	// �������ֵ�����
	WORD	wBackAudioFlag;		// �������ֵ�����
	short	nVoiceBufSize;		// �����ڲ��������Ĵ�С
	short	nInsertInfoSize;	// �������в�����Ϣ�ĸ���
	short	nReserved[6];		// ����
//	long    nIdleTime;/////////////////////////////////////////////////
}
JTTS_CONFIG;

//JTTS_VOICEATTRIBUTE
typedef struct JTTS_VOICEATTRIBUTE_T
{
	char		szName[VOICENAME_LEN];	// ֻ��ΪӢ������
	char		szVoiceID[VOICEID_LEN];	// ��ɫ��Ψһ��ʶ
	short		nGender;				// GENDER_xxx
	short		nAge;					// AGE_xx
	DWORD		dwDomainArray;			// �ɵ�λ���λ���ֱ��ʾDOMAIN_xxx
	DWORD		nLanguage;				// ֧�ֵ�����, LANGUAGE_xxx
	char		szVendor[VENDOR_LEN];	// �ṩ����
	char		szDLLName[DLLNAME_LEN];	// ��Ӧ��DLL
	DWORD		dwVersionMS;			// ����İ汾�ţ���Ӧ"3.75.0.31"��ǰ����
										// e.g. 0x00030075 = "3.75"
    DWORD		dwVersionLS;			// e.g. 0x00000031 = "0.31"
}
JTTS_VOICEATTRIBUTE;

// ������Ϣ
typedef struct INSERTINFO_T
{
	int nTag;		// �ж��֣�INFO_MARK, INFO_VISEME
	DWORD dwValue; 	// ������Ϣ��
					// MARKʱ����24λmark�ı�ƫ�ƣ���8λ�ı�����
					// VISEMEʱ����ʾ����
	DWORD dwBytes;	// ����������ʲô�ط����룬���밴˳������
}
INSERTINFO;

typedef struct JTTS_LANGATTRIBUTE_T
{
	int	  nValue;
	char  szName[ATTRNAME_LEN];
	char  szEngName[ATTRNAME_LEN];
	char  szXmlLang[XMLLANG_LEN];
}
JTTS_LANGATTRIBUTE;

typedef struct JTTS_DOMAINATTRIBUTE_T
{
	int   nValue;
	char  szName[ATTRNAME_LEN];
	char  szEngName[ATTRNAME_LEN];
}
JTTS_DOMAINATTRIBUTE;

typedef struct JTTS_COUNTERS_T
{	
	int nSession;
}
JTTS_COUNTERS;

// ϵͳ֪ͨ��Ϣ���ص���������

// ϵͳ֪ͨ��Ϣ
#define WM_JTTS_NOTIFY			(WM_USER + 0x4999)

// �ص�����
typedef BOOL (TTSAPI * JTTS_CALLBACKPROC)(WORD wParam, LONG lParam, DWORD dwUserData);
typedef BOOL (TTSAPI * JTTS_DATACALLBACKPROC)(DWORD dwSessionID, WORD wParam, LONG lParam, 
									   unsigned char * pVoiceData, DWORD dwLen, 
									   INSERTINFO* pInsertInfo, int nInsertInfo, 
									   DWORD dwUserData);

// WM_JTTS_NOTIFY / JTTS_CALLBACKPROC / JTTS_DATACALLBACKPROC��wParam�Ķ���
#define NOTIFY_BEGIN			0	// lParam: û��ʹ��
#define NOTIFY_END				1	// lParam: û��ʹ��
#define NOTIFY_SENTEND			2	// lParam: �Ѿ�������ֽ���
#define NOTIFY_SENTBEGIN		3	// lParam: ��Ҫ������λ�ã����ֽ������㣩
#define NOTIFY_MARK				4	// lParam: ���Mark����λ�úͳ���, �ο���GETMARKOFFSET��GETMARKLEN
#define NOTIFY_VISEME			5	// lParam: ��Ǵ�����Ϣ���ְ汾��δʹ��
#define NOTIFY_CHANGECONFIG		6	// ϵͳ����ʹ���봫��Config��ͬ������
#define NOTIFY_DATA				7	// ������ JTTS_DATACALLBACKPROC�����ݺϳ����ݺ�InsertInfo��Ϣ 
									// lParam not use; dwLen��pVoiceData����; pVoiceData�������ݻ���; 
									// nInsertInfo, pInsertInfo�ǲ������ݵ���Ŀ������

// Ϊ���ϰ汾���ݶ�����
#define NOTIFY_PROGRESS			2	
#define NOTIFY_PROGRESS2		3	

// ͨ��NOTIFY_MARK��lParam�õ������Mark String��ƫ�����ͳ���
#define GETMARKOFFSET(lParam)	(lParam >> 8)
#define GETMARKLEN(lParam)		(lParam & 0xFF)

//------------------------------------------------------------------------
// ϵͳ����
ERRCODE TTSAPI jTTS_Init(const char * pcszLibPath, const char * pcszSerialNo);
ERRCODE TTSAPI jTTS_End();

int		TTSAPI jTTS_GetLangCount();
ERRCODE TTSAPI jTTS_GetLangAttribute(int nIndex, JTTS_LANGATTRIBUTE * pAttribute);
ERRCODE TTSAPI jTTS_GetLangAttributeByValue(int nValue, JTTS_LANGATTRIBUTE * pAttribute);

int		TTSAPI jTTS_GetDomainCount();
ERRCODE TTSAPI jTTS_GetDomainAttribute(int nIndex, JTTS_DOMAINATTRIBUTE * pAttribute);
ERRCODE TTSAPI jTTS_GetDomainAttributeByValue(int nValue, JTTS_DOMAINATTRIBUTE * pAttribute);

//-------------------------------------------------------------
// ������Ϣ����
int		TTSAPI jTTS_GetVoiceCount();
ERRCODE TTSAPI jTTS_GetVoiceAttribute(int nIndex, JTTS_VOICEATTRIBUTE * pAttribute);
ERRCODE TTSAPI jTTS_GetVoiceAttributeByID(const char *pszVoiceID, JTTS_VOICEATTRIBUTE * pAttribute);
BOOL	TTSAPI jTTS_IsVoiceSupported(const char *pszVoiceID);
ERRCODE TTSAPI jTTS_FindVoice(int nLanguage, int nGender, int nAge, char * szName, int nDomain, 
					   char * pszVoiceID, WORD * pwMatchFlag);

ERRCODE TTSAPI jTTS_PreLoad (const char *pszVoiceID);

//------------------------------------------------------------------------
// ���ú��� 
ERRCODE TTSAPI jTTS_Set(const JTTS_CONFIG * pConfig);
ERRCODE TTSAPI jTTS_Get(JTTS_CONFIG * pConfig);
ERRCODE TTSAPI jTTS_SetParam(JTTS_PARAM nParam, DWORD dwValue);
ERRCODE TTSAPI jTTS_GetParam(JTTS_PARAM nParam, DWORD *pdwValue);

//------------------------------------------------------------------------
// ���ź��� 
ERRCODE TTSAPI jTTS_SetPlay(UINT uDeviceID, HWND hwnd, JTTS_CALLBACKPROC lpfnCallback, DWORD dwUserData);
ERRCODE TTSAPI jTTS_Play(const char * pcszText, DWORD dwFlag);
ERRCODE TTSAPI jTTS_Stop();
ERRCODE TTSAPI jTTS_Pause();
ERRCODE TTSAPI jTTS_Resume();
int     TTSAPI jTTS_GetStatus();

//------------------------------------------------------------------------
// ���ŵ��ļ����� 
ERRCODE TTSAPI jTTS_PlayToFile(const char *pcszText, const char * pcszFileName, 
							   UINT nFormat, const JTTS_CONFIG * pConfig, 
							   DWORD dwFlag, JTTS_CALLBACKPROC lpfnCallback, 
							   DWORD dwUserData);

//-------------------------------------------------------------
// �ϳɹ��̵ײ㺯��
ERRCODE TTSAPI jTTS_SessionStart(const char * pcszText, DWORD * pdwSessionID, 
								 UINT nFormat, const JTTS_CONFIG *pConfig, DWORD dwFlag, 
								 int * pnBitsPerSample, int * pnSamplesPerSec);
ERRCODE TTSAPI jTTS_SessionGetData(DWORD dwSessionID, int nBufIndex, unsigned char ** ppVoiceData, 
								   DWORD * pdwLen, int nReserveLen, INSERTINFO** ppInsertInfo,
								   int* pnInsertInfo);
ERRCODE TTSAPI jTTS_SessionStop(DWORD dwSessionID);
ERRCODE TTSAPI jTTS_SessionGetReadBytes(DWORD dwSessionID, DWORD * pdwBytes);
ERRCODE TTSAPI jTTS_SessionExec(DWORD dwSessionID, JTTS_DATACALLBACKPROC lpfnDataCallback, DWORD dwUserData);


#ifdef __cplusplus
}
#endif

#pragma pack( pop, jtts_ml_h )

#endif //_JTTS_ML_H_


