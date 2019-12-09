#pragma once
#include "../Include/BaiduFaceAI/baidu_face_api.h"
#include "../Include/BaiduFaceAI/hjimi_camera.h"
#include "../Include/BaiduFaceAI/orbe_camera.h"
#include "../Include/Curl/include/curl/curl.h"

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "..\\Include\\Duilib\\Lib\\DuiLib_ud.lib")
#   else
#       pragma comment(lib, "..\\Include\\Duilib\\Lib\\DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "..\\Include\\BaiduFaceAI\\Lib\\BaiduFaceApi.lib")
#		pragma comment(lib, "..\\Include\\BaiduFaceAI\\Lib\\hjimi_camera.lib")
#		pragma comment(lib, "..\\Include\\BaiduFaceAI\\Lib\\json_vc71_libmt.lib")
#		pragma comment(lib, "..\\Include\\BaiduFaceAI\\Lib\\opencv_world320.lib")
#		pragma comment(lib, "..\\Include\\BaiduFaceAI\\Lib\\orbe_camera.lib")
#		pragma comment(lib, "..\\Include\\Curl\\Lib\\libcurl.lib")
#		pragma comment(lib, "..\\Include\\Curl\\Lib\\libeay32.lib")
#		pragma comment(lib, "..\\Include\\Curl\\Lib\\ssleay32.lib")
#		pragma comment(lib, "..\\include\\Jtts\\lib\\jTTS_ML.lib")
#   else
#      pragma comment(lib, "..\\Include\\Duilib\\Lib\\DuiLib.lib")
#   endif
#endif

class CBaiduFaceAIInclude
{
public:
	CBaiduFaceAIInclude();
	~CBaiduFaceAIInclude();
};

