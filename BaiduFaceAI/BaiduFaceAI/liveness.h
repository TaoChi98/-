#ifndef TESTFACEAPI_TESTFACEAPI_LIVENESS_H
#define TESTFACEAPI_TESTFACEAPI_LIVENESS_H
#include "baidu_face_api.h"
#include "opencv2\opencv.hpp"
// �������Ϊ�޻���ɼ����л���ɼ�(����RGB��Ŀ���弰RGB+IR˫Ŀ����)
class Liveness
{
public:
    Liveness();
    ~Liveness();
public:
    // usb����ͷ��⣬ʵʱ���������Ϣ
    void usb_track_face_info(BaiduFaceApi *api);
    // ͨ��ͼƬ��⣬�������������Ϣ
    void image_track_face_info(BaiduFaceApi *api);
    // ͨ��ͼƬ���(���������ͼƬbuf�����������������Ϣ
    void image_track_face_info_by_buf(BaiduFaceApi *api);
    // usb����ͷ����rgb��Ŀ������
    bool usb_rgb_track(BaiduFaceApi *api, float default_score = 0.8);
    // ˫Ŀ����ͷ����ir,rgb������
    bool ir_rgb_track(BaiduFaceApi *api, float default_score = 0.8);
    // ir����ͼ�������
    float ir_liveness_track_by_img(BaiduFaceApi *api);
    // ir����ͼ�������(���������ͼƬbuffer��
    float ir_liveness_track_by_buf(BaiduFaceApi *api);
    // rgbͼ�������
    float rgb_liveness_track_by_img(BaiduFaceApi *api);
    // rgbͼ�������(���������ͼƬbuffer)
    float rgb_liveness_track_by_buf(BaiduFaceApi *api);
    // ir������Ƶ֡������
    float ir_liveness_track_by_frame(BaiduFaceApi *api, const cv::Mat &frame);
    // rgb��Ƶ֡������
    float rgb_liveness_track_by_frame(BaiduFaceApi *api, const cv::Mat &frame);
    // depth(���)������
    float depth_liveness_track_by_frame(BaiduFaceApi *api, const cv::Mat &frame);

    // ˫Ŀ����ͷ����rgb��depth������
    bool rgb_depth_track_by_buf(BaiduFaceApi *api, float default_score = 0.8);

    // ˫Ŀ����ͷ����rgb��depth������(opencv��Ƶ֡)
    bool rgb_depth_track_by_mat_with_orbe(BaiduFaceApi *api, float default_score = 0.8);

    // ˫Ŀ����ͷ����rgb��depth������(opencv��Ƶ֡)
    bool rgb_depth_track_by_mat_with_hjimi(BaiduFaceApi *api, float default_score = 0.8);

    // ѡ��usb�豸id
    int select_usb_device_id();
    // ��ȡ�����Ƶ�豸����
    int get_devices_count();
};

#endif
