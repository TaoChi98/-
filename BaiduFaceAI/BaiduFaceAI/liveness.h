#ifndef TESTFACEAPI_TESTFACEAPI_LIVENESS_H
#define TESTFACEAPI_TESTFACEAPI_LIVENESS_H
#include "baidu_face_api.h"
#include "opencv2\opencv.hpp"
// 该类可作为无活体采集及有活体采集(包括RGB单目活体及RGB+IR双目活体)
class Liveness
{
public:
    Liveness();
    ~Liveness();
public:
    // usb摄像头检测，实时输出人脸信息
    void usb_track_face_info(BaiduFaceApi *api);
    // 通过图片检测，输出检测的人脸信息
    void image_track_face_info(BaiduFaceApi *api);
    // 通过图片检测(传入二进制图片buf），输出检测的人脸信息
    void image_track_face_info_by_buf(BaiduFaceApi *api);
    // usb摄像头进行rgb单目活体检测
    bool usb_rgb_track(BaiduFaceApi *api, float default_score = 0.8);
    // 双目摄像头进行ir,rgb活体检测
    bool ir_rgb_track(BaiduFaceApi *api, float default_score = 0.8);
    // ir红外图像活体检测
    float ir_liveness_track_by_img(BaiduFaceApi *api);
    // ir红外图像活体检测(传入二进制图片buffer）
    float ir_liveness_track_by_buf(BaiduFaceApi *api);
    // rgb图像活体检测
    float rgb_liveness_track_by_img(BaiduFaceApi *api);
    // rgb图像活体检测(传入二进制图片buffer)
    float rgb_liveness_track_by_buf(BaiduFaceApi *api);
    // ir红外视频帧活体检测
    float ir_liveness_track_by_frame(BaiduFaceApi *api, const cv::Mat &frame);
    // rgb视频帧活体检测
    float rgb_liveness_track_by_frame(BaiduFaceApi *api, const cv::Mat &frame);
    // depth(深度)活体检测
    float depth_liveness_track_by_frame(BaiduFaceApi *api, const cv::Mat &frame);

    // 双目摄像头进行rgb，depth活体检测
    bool rgb_depth_track_by_buf(BaiduFaceApi *api, float default_score = 0.8);

    // 双目摄像头进行rgb，depth活体检测(opencv视频帧)
    bool rgb_depth_track_by_mat_with_orbe(BaiduFaceApi *api, float default_score = 0.8);

    // 双目摄像头进行rgb，depth活体检测(opencv视频帧)
    bool rgb_depth_track_by_mat_with_hjimi(BaiduFaceApi *api, float default_score = 0.8);

    // 选择usb设备id
    int select_usb_device_id();
    // 获取外接视频设备数量
    int get_devices_count();
};

#endif
