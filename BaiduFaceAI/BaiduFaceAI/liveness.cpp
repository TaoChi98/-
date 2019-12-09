#pragma comment(lib, "orbe_camera.lib")  // �þ�Ϊ����±��й�˫Ŀ����ͷ
#pragma comment(lib, "hjimi_camera.lib")  // �þ�Ϊ���뻪�ܰ���˫Ŀ����ͷ
#include "stdafx.h"
#include "liveness.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <regex>
#include <sstream>
#include <fstream>
#include <iterator>
#include <thread>
#include <Windows.h>
#include <io.h>
#include "usb_device\device_enumerator.h"
#include "baidu_face_api.h"
#include "image_base64.h"
#include "cv_help.h"
#include "json\json.h"
#include "image_buf.h"
#include "orbe_camera.h"
#include "hjimi_camera.h"
Liveness::Liveness()
{
}

Liveness::~Liveness()
{
}
// ѡ��usb��Ƶ����ͷid,���������л�ȡ���ӵ�����ͷ�б�����id�����ƺ�·����
int Liveness::select_usb_device_id()
{
    std::map<int, Device> devs = DeviceEnumerator::get_usb_devices();
    int device_id = 0;
    for (auto const &device : devs) {
        std::cout << "== VIDEO DEVICE (id:" << device.first << ") ==" << std::endl;
        std::cout << "Name: " << device.second.deviceName << std::endl;
        std::cout << "Path: " << device.second.devicePath << std::endl;
    }
    if (devs.size() > 0)
    {
        device_id = devs[0].id;
        std::cout << "select device id is:" << device_id << std::endl;
    }
    return device_id;
}

// ��ȡ�����Ƶ�豸����
int Liveness::get_devices_count()
{
    std::map<int, Device> devs = DeviceEnumerator::get_usb_devices();
    int count = 0;
    for (auto const &device : devs) {
        std::cout << "== VIDEO DEVICE (id:" << device.first << ") ==" << std::endl;
        std::cout << "Name: " << device.second.deviceName << std::endl;
        std::cout << "Path: " << device.second.devicePath << std::endl;
    }
    count = devs.size();
    return count;
}

// ͨ��usb����ͷ��ʵʱ����ɼ���������Ϣ
void Liveness::usb_track_face_info(BaiduFaceApi *api)
{
    // deviceΪ0Ĭ�ϴ򿪱ʼǱ������Դ�����ͷ����Ϊ0�򲻿�����usb����ͷ
    // ���device�޸�Ϊ1��2�����ԣ�1����2Ϊusb���ϵ��Ժ󣬵����Ͽɵ�usb�豸id
    // Ҳ��ͨ��select_usb_device_id������ȡid
    int device = select_usb_device_id();
  //  int device = 0;// ��1����2������0,1,2Ϊ����usb����ͷ�ڵ�����ʶ���id���
    cv::VideoCapture cap(device);
    if (!cap.isOpened())
    {
        std::cout << "open camera error" << std::endl;
        return;
    }
    cv::Mat frame;
    bool stop = false;
    int index = 0;
    bool save_file = false;
    cv::RotatedRect box;
    std::vector<TrackFaceInfo> *track_info = new std::vector<TrackFaceInfo>();
    while (!stop)
    {
        cap >> frame;
        track_info->clear();
        int size = api->track(track_info, frame, 3);
        for (int i = 0; i < size; i++)
        {
            TrackFaceInfo info = track_info->at(i);
            std::cout << "in Liveness::usb_track score is:" << info.score << std::endl;
            // ������Ϣ
            FaceInfo ibox = info.box;
            // �Ƕ�
            std::cout << "in Liveness::usb_track mAngle is:" << ibox.mAngle << std::endl;
            // �������
            std::cout << "in Liveness::usb_track mWidth is:" << ibox.mWidth << std::endl;
            // ���ĵ�X,Y����
            std::cout << "in Liveness::usb_track mCenter_x is:" << ibox.mCenter_x << std::endl;
            std::cout << "in Liveness::usb_track mCenter_y is:" << ibox.mCenter_y << std::endl;
            std::vector<float> headPose = info.headPose;
            // ���� x��y��z�����Ƕȵ������Ƕ�
            for (int k = 0; k < headPose.size(); k++)
            {
                float angle = headPose.at(k);
                std::cout << "in Liveness::usb_track angle is:" << angle << std::endl;
            }
            // ��������
            box = CvHelp::bounding_box(info.landmarks);
            CvHelp::draw_rotated_box(frame, box, cv::Scalar(0, 255, 0));
            // ���ؼ�������
            // draw_shape(info.landmarks, frame, Scalar(0, 255, 0));

            // frameΪ��Ƶ֡,�ɸ��ݲɼ�����������Ϣɸѡ��Ҫ��֡
            // ����Ϊ����ͼƬ�����ص�ʾ��,�ɸ��ݲɼ���Ϣ��ѡ��ı���
            if (!save_file)
            {
                save_file = true;
                cv::imwrite("usb_track.jpg", frame);
            }
        } 
        if (!frame.empty())
        {
            imshow("face", frame);
            cv::waitKey(1);
            std::cout << "mat not empty" << std::endl;
        }
        else
        {
            std::cout << "mat is empty" << std::endl;
        }
        frame.release();
       
    }
    delete track_info;
}

// ͨ��ͼƬ��⣬���������Ϣ
void Liveness::image_track_face_info(BaiduFaceApi *api)
{
    api->set_min_face_size(30);
    cv::Mat frame = cv::imread("d:\\multi_face.jpg");
    if (frame.empty())
    {
        std::cout << "frame is empty,please check file path!" << std::endl;
        return;
    }
    cv::RotatedRect box;
    std::vector<TrackFaceInfo> *track_info = new std::vector<TrackFaceInfo>();
  
        track_info->clear();
        int size = api->track(track_info, frame, 6);
        std::cout << "-----track size is-------" << size << std::endl;
        if (size > 0)
        {
            for (int i = 0; i < size; i++)
            {
                TrackFaceInfo info = track_info->at(i);
                std::cout << "in Liveness::image_track_face_info score is:" << info.score << std::endl;
                // ������Ϣ
                FaceInfo ibox = info.box;
                // �Ƕ�
                std::cout << "in Liveness::image_track_face_info mAngle is:" << ibox.mAngle << std::endl;
                // �������
                std::cout << "in Liveness::image_track_face_info mWidth is:" << ibox.mWidth << std::endl;
                // ���ĵ�X,Y����
                std::cout << "in Liveness::image_track_face_info mCenter_x is:" << ibox.mCenter_x << std::endl;
                std::cout << "in Liveness::image_track_face_info mCenter_y is:" << ibox.mCenter_y << std::endl;
                std::vector<float> headPose = info.headPose;
                // ���� x��y��z�����Ƕȵ������Ƕ�
                for (int k = 0; k < headPose.size(); k++)
                {
                    float angle = headPose.at(k);
                    std::cout << "in Liveness::image_track_face_info angle is:" << angle << std::endl;
                }
                // ��������
                box = CvHelp::bounding_box(info.landmarks);
                CvHelp::draw_rotated_box(frame, box, cv::Scalar(0, 255, 0));
                // ���ؼ�������
                // draw_shape(info.landmarks, frame, Scalar(0, 255, 0));
            }
        }
        else
        {
            std::cout << "image has no face!" << std::endl;
        }
        imshow("face", frame);
        cv::waitKey(1);
    
    delete track_info;
}

// ͨ��ͼƬ��⣬���������Ϣ(���������ͼƬbuffer��
void Liveness::image_track_face_info_by_buf(BaiduFaceApi *api)
{
    std::string out_buf;
    int buf_len = ImageBuf::get_buf("d:\\1.jpg", out_buf);

    cv::RotatedRect box;
    std::vector<TrackFaceInfo> *track_info = new std::vector<TrackFaceInfo>();

    track_info->clear();
    int size = api->track_by_buf(track_info, (unsigned char*)out_buf.c_str(), buf_len,1);
    if (size > 0)
    {
        for (int i = 0; i < size; i++)
        {
            TrackFaceInfo info = track_info->at(i);
            std::cout << "in Liveness::image_track_face_info score is:" << info.score << std::endl;
            // ������Ϣ
            FaceInfo ibox = info.box;
            // �Ƕ�
            std::cout << "in Liveness::image_track_face_info mAngle is:" << ibox.mAngle << std::endl;
            // �������
            std::cout << "in Liveness::image_track_face_info mWidth is:" << ibox.mWidth << std::endl;
            // ���ĵ�X,Y����
            std::cout << "in Liveness::image_track_face_info mCenter_x is:" << ibox.mCenter_x << std::endl;
            std::cout << "in Liveness::image_track_face_info mCenter_y is:" << ibox.mCenter_y << std::endl;
            std::vector<float> headPose = info.headPose;
            // ���� x��y��z�����Ƕȵ������Ƕ�
            for (int k = 0; k < headPose.size(); k++)
            {
                float angle = headPose.at(k);
                std::cout << "in Liveness::image_track_face_info angle is:" << angle << std::endl;
            }
           
        }
    }
    else
    {
        std::cout << "image has no face!" << std::endl;
    }
    cv::waitKey(1);
    delete track_info;
}

//usb����ͷ����rgb��Ŀ������
bool Liveness::usb_rgb_track(BaiduFaceApi *api, float default_score)
{
    bool pass = false;
    // deviceΪ0Ĭ�ϴ򿪱ʼǱ������Դ�����ͷ����Ϊ0�򲻿�����usb����ͷ
    // ���device�޸�Ϊ1��2�����ԣ�1����2Ϊusb���ϵ��Ժ󣬵����Ͽɵ�usb�豸id
    // Ҳ��ͨ��select_usb_device_id������ȡid
    int device = select_usb_device_id();
    cv::VideoCapture cap(device);
    if (!cap.isOpened())
    {
        std::cout << "open camera error" << std::endl;
        return pass;
    }
    cv::Mat frame;
    bool stop = false;
    while (!stop)
    {
        cap >> frame;
        float score = rgb_liveness_track_by_frame(api, frame);
        std::string msg = "";
        std::string msg1 = "liveness score:" + std::to_string(score);
        // ����ͨ����ֵ���Ƽ�0.8���û�Ҳ�����Լ��趨ͨ����ֵ
        if (score >= default_score)
        {
            msg = msg1 + ">0.8 pass";
            pass = true;
        }
        else
        {
            msg = msg1 + "<0.8 fail";
            pass = false;
        }
        cv::putText(frame, msg, cv::Point(20, 50), CV_FONT_HERSHEY_COMPLEX,
            1, cv::Scalar(255, 100, 0), 2, 2);
        imshow("face", frame);
        cv::waitKey(1);
    }
    return pass;
}


// ˫Ŀ����ͷ����ir,rgb������
bool Liveness::ir_rgb_track(BaiduFaceApi *api, float default_score)
{
    int device_count = get_devices_count();
    if (device_count<2)
    {
        std::cout << "ir and rgb camera devices needed" << std::endl;
        return false;
    }
    bool pass = true;
    // ���0Ϊ����ʶ���usb����ͷ��ţ���demo��0Ϊir��������ͷ
    // ��ͬ����ͷ�͵���ʶ�����������
    // ���һ���0-10
    int device = select_usb_device_id();
    cv::VideoCapture camera1(device);
    if (!camera1.isOpened())
    {
        std::cout << "camera1 open error" << std::endl;
        return false;
    }
    // ���1Ϊ����ʶ���usb����ͷ��ţ���demo��1Ϊrgb�ɼ�������ͷ
    cv::VideoCapture camera2(device + 1);
    if (!camera2.isOpened())
    {
        std::cout << "camera2 open error" << std::endl;
        return false;
    }
    bool save_file = false;
    while (true) 
    {
        //grab and retrieve each frames of the video sequentially 
        cv::Mat frame1;
        cv::Mat frame2;
        camera1 >> frame1;
        camera2 >> frame2;

        // cv::Size size1 = frame1.size();
        if (!frame1.empty() && !frame2.empty())
        {
            float rgb_score = 0;
            float ir_score = 0;
            std::string res = api->rgb_ir_liveness_check(frame2, frame1, rgb_score, ir_score);
            std::cout << "res is:" << res << std::endl;

            std::string msg1 = "ir score is:" + std::to_string(ir_score);
            cv::putText(frame1, msg1, cv::Point(20, 50), CV_FONT_HERSHEY_COMPLEX,
                1, cv::Scalar(255, 100, 0), 2, 2);
            cv::imshow("Video1", frame1);

            std::string msg2 = "rgb score is:" + std::to_string(rgb_score);
            cv::putText(frame2, msg2, cv::Point(20, 50), CV_FONT_HERSHEY_COMPLEX,
                1, cv::Scalar(255, 100, 0), 2, 2);
            cv::imshow("Video2", frame2);
        }
            cvWaitKey(1);
    }
    return pass;
}

// ����IR������
float Liveness::ir_liveness_track_by_img(BaiduFaceApi *api)
{
    float score = 0;
    std::string file_path = "d:\\ir1.png";
    //����2��ʾ����ͼƬ�ļ�·��
    std::string res = api->ir_liveness_check(file_path.c_str(), 2);
    if (res.length() > 0)
    {
        // ��json���벻�����������汻ע�͵Ĵ��루json����������)
        Json::Value root;
        Json::Reader reader;
        if (reader.parse(res, root))
        {
            int err = root["errno"].asInt();
            if (err == 0)
            {
                Json::Value result = root["data"];
                if (result.size() > 0)
                {
                    std::string sss = result["score"].asString();
                    score = atof(sss.c_str());
                    std::cout << "score rgb is:" << score << std::endl;
                }
            }
        }

        // ��json���벻���������������
     /* Json::CharReaderBuilder b;
        Json::CharReader* reader(b.newCharReader());
        const char* str = res.c_str();

        JSONCPP_STRING errs;
        bool ok = reader->parse(str, str + std::strlen(str), &root, &errs);
        if (ok&&errs.size() == 0)
        {
            int err = root["errno"].asInt();
            if (err == 0)
            {
                Json::Value result = root["data"];
                if (result.size() > 0)
                {
                    std::string sss = result["score"].asString();
                    score = atof(sss.c_str());
                    std::cout << "score rgb is:" << score << std::endl;
                }
            }
        }*/
    }
    std::cout << "ir liveness result is:" << res << std::endl;
    return score;
}

// ����IR������(���������ͼƬbuffer��
float Liveness::ir_liveness_track_by_buf(BaiduFaceApi *api)
{
    float score = 0;
    std::string out_buf;
    int buf_len = ImageBuf::get_buf("d:\\1.jpg", out_buf);
    //����2��ʾ����ͼƬ�ļ�·��
    std::string res = api->ir_liveness_check_by_buf((unsigned char*)out_buf.c_str(), buf_len);
    if (res.length() > 0)
    {
        // ��json���벻�����������汻ע�͵Ĵ��루json����������)
        Json::Value root;
        Json::Reader reader;
        if (reader.parse(res, root))
        {
            int err = root["errno"].asInt();
            if (err == 0)
            {
                Json::Value result = root["data"];
                if (result.size() > 0)
                {
                    std::string sss = result["score"].asString();
                    score = atof(sss.c_str());
                    std::cout << "score rgb is:" << score << std::endl;
                }
            }
        }

        // ��json���벻���������������
        /* Json::CharReaderBuilder b;
        Json::CharReader* reader(b.newCharReader());
        const char* str = res.c_str();

        JSONCPP_STRING errs;
        bool ok = reader->parse(str, str + std::strlen(str), &root, &errs);
        if (ok&&errs.size() == 0)
        {
        int err = root["errno"].asInt();
        if (err == 0)
        {
        Json::Value result = root["data"];
        if (result.size() > 0)
        {
        std::string sss = result["score"].asString();
        score = atof(sss.c_str());
        std::cout << "score rgb is:" << score << std::endl;
        }
        }
        }*/
    }
    std::cout << "ir liveness result is:" << res << std::endl;
    return score;
}

// ��ĿRGB������
float Liveness::rgb_liveness_track_by_img(BaiduFaceApi *api)
{
    float score = 0;
     std::string file_path = "d:\\rgb1.png";
  //  std::string file_path = "d:\\1.jpg";
    //����2��ʾ����ͼƬ�ļ�·��
    std::string res = api->rgb_liveness_check(file_path.c_str(), 2);
    if (res.length() > 0)
    {
        // ��json���벻�����������汻ע�͵Ĵ��루josn�����������)
        Json::Value root;
        Json::Reader reader;
        if (reader.parse(res, root))
        {
            int err = root["errno"].asInt();
            if (err == 0)
            {
                Json::Value result = root["data"];
                if (result.size() > 0)
                {
                    std::string sss = result["score"].asString();
                    score = atof(sss.c_str());
                    std::cout << "score rgb is:" << score << std::endl;
                }
            }
        }

        // ��json���벻���������������
     /* Json::CharReaderBuilder b;
        Json::CharReader* reader(b.newCharReader());
        const char* str = res.c_str();

        JSONCPP_STRING errs;
        bool ok = reader->parse(str, str + std::strlen(str), &root, &errs);
        if (ok&&errs.size() == 0)
        {
            int err = root["errno"].asInt();
            if (err == 0)
            {
                Json::Value result = root["data"];
                if (result.size() > 0)
                {
                    std::string sss = result["score"].asString();
                    score = atof(sss.c_str());
                    std::cout << "score rgb is:" << score << std::endl;
                }
            }
        } */
    }
    std::cout << "rgb liveness result is:" << res << std::endl;
    return score;
}

// ��ĿRGB������(���������ͼƬbuffer)
float Liveness::rgb_liveness_track_by_buf(BaiduFaceApi *api)
{
    float score = 0;
    std::string out_buf;
    int buf_len = ImageBuf::get_buf("d:\\1.jpg", out_buf);
    //����2��ʾ����ͼƬ�ļ�·��
    std::string res = api->rgb_liveness_check_by_buf((unsigned char*)out_buf.c_str(), buf_len);
    if (res.length() > 0)
    {
        // ��json���벻�����������汻ע�͵Ĵ��루josn�����������)
        Json::Value root;
        Json::Reader reader;
        if (reader.parse(res, root))
        {
            int err = root["errno"].asInt();
            if (err == 0)
            {
                Json::Value result = root["data"];
                if (result.size() > 0)
                {
                    std::string sss = result["score"].asString();
                    score = atof(sss.c_str());
                    std::cout << "score rgb is:" << score << std::endl;
                }
            }
        }

        // ��json���벻���������������
        /* Json::CharReaderBuilder b;
        Json::CharReader* reader(b.newCharReader());
        const char* str = res.c_str();

        JSONCPP_STRING errs;
        bool ok = reader->parse(str, str + std::strlen(str), &root, &errs);
        if (ok&&errs.size() == 0)
        {
        int err = root["errno"].asInt();
        if (err == 0)
        {
        Json::Value result = root["data"];
        if (result.size() > 0)
        {
        std::string sss = result["score"].asString();
        score = atof(sss.c_str());
        std::cout << "score rgb is:" << score << std::endl;
        }
        }
        } */
    }
    std::cout << "rgb liveness result is:" << res << std::endl;
    return score;
}

// ���Ե�Ŀir���������(����opencv��Ƶ֡)
float Liveness::ir_liveness_track_by_frame(BaiduFaceApi *api, const cv::Mat &frame)
{
    float score = 0;
    std::string res = api->ir_liveness_check(frame);
    if (res.length() > 0)
    {
        // ��json���벻�����������汻ע�͵Ĵ���Σ�json�����������)
        Json::Value root;
        Json::Reader reader;
        if (reader.parse(res, root))
        {
            int err = root["errno"].asInt();
            if (err == 0)
            {
                Json::Value result = root["data"];
                if (result.size() > 0)
                {
                    std::string sss = result["score"].asString();
                    score = atof(sss.c_str());
                    std::cout << "score ir is:" << score << std::endl;
                }
            }
        }

        // ��json���벻���������������
       /* Json::CharReaderBuilder b;
        Json::CharReader* reader(b.newCharReader());
        const char* str = res.c_str();

        JSONCPP_STRING errs;
        bool ok = reader->parse(str, str + std::strlen(str), &root, &errs);
        if (ok&&errs.size() == 0)
        {
            int err = root["errno"].asInt();
            if (err == 0)
            {
                Json::Value result = root["data"];
                if (result.size() > 0)
                {
                    std::string sss = result["score"].asString();
                    score = atof(sss.c_str());
                    std::cout << "score ir is:" << score << std::endl;
                }
            }
        }*/
    }
    std::cout << "ir liveness result is:" << res << std::endl;
    return score;
}

// ���Ե�ĿRGB������(����opencv��Ƶ֡)
float Liveness::rgb_liveness_track_by_frame(BaiduFaceApi *api, const cv::Mat &frame)
{
    float score = 0;
    std::string res = api->rgb_liveness_check(frame);
    if (res.length() > 0)
    {
        // ��json���벻�����������汻ע�͵Ĵ���Σ�json����������)
        Json::Value root;
        Json::Reader reader;
        if (reader.parse(res, root))
        {
            int err = root["errno"].asInt();
            if (err == 0)
            {
                Json::Value result = root["data"];
                if (result.size() > 0)
                {
                    std::string sss = result["score"].asString();
                    score = atof(sss.c_str());
                    std::cout << "score rgb is:" << score << std::endl;
                }
            }
        }

        // ��json���벻���������������
       /* Json::CharReaderBuilder b;
        Json::CharReader* reader(b.newCharReader());
        const char* str = res.c_str();

        JSONCPP_STRING errs;
        bool ok = reader->parse(str, str + std::strlen(str), &root, &errs);
        if (ok&&errs.size() == 0)
        {
            int err = root["errno"].asInt();
            if (err == 0)
            {
                Json::Value result = root["data"];
                if (result.size() > 0)
                {
                    std::string sss = result["score"].asString();
                    score = atof(sss.c_str());
                    std::cout << "score rgb is:" << score << std::endl;
                }
            }
        } */
    }
    std::cout << "rgb liveness result is:" << res << std::endl;
    return score;
}
// ����depth��Ȼ�����(����opencv��Ƶ֡)
float Liveness::depth_liveness_track_by_frame(BaiduFaceApi*api, const cv::Mat &frame)
{
    float score = 0;
    std::string res;
 //   std::string res = api->depth_liveness_check(frame);
    if (res.length() > 0)
    {
        // ��json���벻�����������汻ע�͵Ĵ���Σ�json����������)
        Json::Value root;
        Json::Reader reader;
        if (reader.parse(res, root))
        {
            int err = root["errno"].asInt();
            if (err == 0)
            {
                Json::Value result = root["data"];
                if (result.size() > 0)
                {
                    std::string sss = result["score"].asString();
                    score = atof(sss.c_str());
                    std::cout << "score rgb is:" << score << std::endl;
                }
            }
        }

        // ��json���벻���������������
        /* Json::CharReaderBuilder b;
        Json::CharReader* reader(b.newCharReader());
        const char* str = res.c_str();

        JSONCPP_STRING errs;
        bool ok = reader->parse(str, str + std::strlen(str), &root, &errs);
        if (ok&&errs.size() == 0)
        {
        int err = root["errno"].asInt();
        if (err == 0)
        {
        Json::Value result = root["data"];
        if (result.size() > 0)
        {
        std::string sss = result["score"].asString();
        score = atof(sss.c_str());
        std::cout << "score rgb is:" << score << std::endl;
        }
        }
        } */
    }
    std::cout << "rgb liveness result is:" << res << std::endl;
    return score;
}


// ˫Ŀ����ͷ����rgb,depth������
bool Liveness::rgb_depth_track_by_buf(BaiduFaceApi *api, float default_score)
{
    std::string rgb_buf;
  //  int rgb_len = ImageBuf::get_buf("d:\\depth_image\\test1.png", rgb_buf);
    int rgb_len = ImageBuf::get_buf("d:\\rgb.png", rgb_buf);

    std::string depth_buf;
//    int depth_len = ImageBuf::get_buf("d:\\depth_image\\depth1.png", depth_buf);
    int depth_len = ImageBuf::get_buf("d:\\depth.png", depth_buf);

    std::string res =api->rgb_depth_liveness_check_by_buf((unsigned char*)rgb_buf.c_str(),
        rgb_len, (unsigned char*)depth_buf.c_str(), depth_len);

    std::cout << "res is:" << res << std::endl;
    return true;
}

// ˫Ŀ����ͷ����rgb,depth������(�˴������˰±��й��˫Ŀ����ͷ)
bool Liveness::rgb_depth_track_by_mat_with_orbe(BaiduFaceApi *api, float default_score)
{
    OrbeCamera *orbe = new OrbeCamera();
    cv::Mat cv_rgb(480, 640, CV_8UC3);
    cv::Mat cv_depth(480, 640, CV_16UC1);
    cvNamedWindow("rgb", 1);
    cvNamedWindow("depth", 2);
    bool pass = false;
    float rgb_score = 0;
    float depth_score = 0;
    while (true)
    {
        orbe->open(cv_rgb, cv_depth);

        std::cout << "cv_rgb.rows" << cv_rgb.rows << "cv_depth rows" << cv_depth.rows << std::endl;

        if (!cv_rgb.empty() && !cv_depth.empty())
        {
            std::string res = api->rgb_depth_liveness_check(cv_rgb, cv_depth, rgb_score, depth_score);
            std::cout << "res is:" << res << std::endl;
        }
        std::string msg1 = "rgb score is:" + std::to_string(rgb_score);
        cv::putText(cv_rgb, msg1, cv::Point(20, 50), CV_FONT_HERSHEY_COMPLEX,
            1, cv::Scalar(255, 100, 0), 2, 2);
        cv::imshow("rgb", cv_rgb);
        std::string msg2 = "depth score is:" + std::to_string(depth_score);
        cv::putText(cv_depth, msg2, cv::Point(20, 50), CV_FONT_HERSHEY_COMPLEX,
            1, cv::Scalar(255, 255, 255), 2, 2);
        cv::imshow("depth", cv_depth);
        int c = cvWaitKey(2);
        if (27 == char(c)) break;
    }
    delete orbe;
    return pass;
}

// ˫Ŀ����ͷ����rgb,depth������(�˴������˻��ܰ��׵�˫Ŀ����ͷ)
bool Liveness::rgb_depth_track_by_mat_with_hjimi(BaiduFaceApi *api, float default_score)
{
    bool pass = false;
  
    std::cout << "hello world" << std::endl;
    HjimiCamera *camera = new HjimiCamera();
    cv::Mat rgb;
    cv::Mat depth;

    cv::namedWindow("rgb", 1);
    cv::namedWindow("depth", 2);
    float rgb_score = 0;
    float depth_score = 0;
    while (true)
    {
        ImiCameraFrame *rgb_frame = NULL;
        ImiImageFrame * depth_frame = NULL;
        bool ok = camera->open_camera(rgb_frame, depth_frame);
        if (!ok)
        {
            camera->frame_release(rgb_frame, depth_frame);
            continue;
        }
        cv::Mat colorMat(rgb_frame->height, rgb_frame->width, CV_8UC3, rgb_frame->pData);
        cv::Mat cv_rgb;
        cvtColor(colorMat, cv_rgb, CV_RGB2BGR);
        cv::Mat cv_depth(depth_frame->height, depth_frame->width, CV_16UC1, depth_frame->pData);

        std::string res = api->rgb_depth_liveness_check(cv_rgb, cv_depth, rgb_score, depth_score);
        std::cout << "res is:" << res << std::endl;

        std::string msg1 = "rgb score is:" + std::to_string(rgb_score);
        cv::putText(cv_rgb, msg1, cv::Point(20, 50), CV_FONT_HERSHEY_COMPLEX,
            1, cv::Scalar(255, 100, 0), 2, 2);

        cv::Mat img;
        cv_depth.convertTo(img, CV_8UC1, 255.0 / 4500);
        std::string msg2 = "depth score is:" + std::to_string(depth_score);
        cv::putText(img, msg2, cv::Point(20, 50), CV_FONT_HERSHEY_COMPLEX,
            1, cv::Scalar(255, 255, 255), 2, 2);

        cv::imshow("rgb", cv_rgb);
        cv::imshow("depth", img);
        camera->frame_release(rgb_frame, depth_frame);
        cv::waitKey(1);
    }

    delete camera;

    return pass;
}

