#ifndef TESTFACEAPI_TESTFACEAPI_IMAGE_BUF_H
#define TESTFACEAPI_TESTFACEAPI_IMAGE_BUF_H
#include <string>
// ��ͼƬ���ж�ȡ������buffer
class ImageBuf
{
public:
    // ��ȡͼƬ������buffer
    static const int get_buf(const std::string &file_path, std::string &out);   
};
#endif

