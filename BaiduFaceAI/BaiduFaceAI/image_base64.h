#ifndef TESTFACEAPI_TESTFACEAPI_IMAGE_BASE64_H
#define TESTFACEAPI_TESTFACEAPI_IMAGE_BASE64_H
#include <string>
// ��ͼƬ����base64���������
class ImageBase64
{
public:

    /*����
    DataByte
    [in]��������ݳ���,���ֽ�Ϊ��λ
    */
    static const std::string encode(const unsigned char* Data, int DataByte);
    /*����
    DataByte
    [in]��������ݳ���,���ֽ�Ϊ��λ
    OutByte
    [out]��������ݳ���,���ֽ�Ϊ��λ,�벻Ҫͨ������ֵ����
    ������ݵĳ���
    */
    static const std::string decode(const char* Data, int DataByte, int& OutByte);
    // ����ͼƬ��ַ����base64����ʾ��
    static std::string file2base64(const std::string& file_path);
};
#endif

