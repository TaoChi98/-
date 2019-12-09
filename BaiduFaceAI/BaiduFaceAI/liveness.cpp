#pragma comment(lib, "orbe_camera.lib")  // 该句为接入奥比中光双目摄像头
#pragma comment(lib, "hjimi_camera.lib")  // 该句为接入华杰艾米双目摄像头
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
// 选择usb视频摄像头id,方法里面有获取连接的摄像头列表，包括id，名称和路径等
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

// 获取外接视频设备数量
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

// 通过usb摄像头，实时输出采集的人脸信息
void Liveness::usb_track_face_info(BaiduFaceApi *api)
{
    // device为0默认打开笔记本电脑自带摄像头，若为0打不开外置usb摄像头
    // 请把device修改为1或2再重试，1，或2为usb插上电脑后，电脑认可的usb设备id
    // 也可通过select_usb_device_id方法获取id
    int device = select_usb_device_id();
  //  int device = 0;// 或1，或2，数字0,1,2为您的usb摄像头在电脑上识别的id编号
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
            // 人脸信息
            FaceInfo ibox = info.box;
            // 角度
            std::cout << "in Liveness::usb_track mAngle is:" << ibox.mAngle << std::endl;
            // 人脸宽度
            std::cout << "in Liveness::usb_track mWidth is:" << ibox.mWidth << std::endl;
            // 中心点X,Y坐标
            std::cout << "in Liveness::usb_track mCenter_x is:" << ibox.mCenter_x << std::endl;
            std::cout << "in Liveness::usb_track mCenter_y is:" << ibox.mCenter_y << std::endl;
            std::vector<float> headPose = info.headPose;
            // 返回 x，y，z三个角度的人脸角度
            for (int k = 0; k < headPose.size(); k++)
            {
                float angle = headPose.at(k);
                std::cout << "in Liveness::usb_track angle is:" << angle << std::endl;
            }
            // 画人脸框
            box = CvHelp::bounding_box(info.landmarks);
            CvHelp::draw_rotated_box(frame, box, cv::Scalar(0, 255, 0));
            // 画关键点轮廓
            // draw_shape(info.landmarks, frame, Scalar(0, 255, 0));

            // frame为视频帧,可根据采集到的人脸信息筛选需要的帧
            // 以下为保存图片到本地的示例,可根据采集信息有选择的保存
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

// 通过图片检测，输出人脸信息
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
                // 人脸信息
                FaceInfo ibox = info.box;
                // 角度
                std::cout << "in Liveness::image_track_face_info mAngle is:" << ibox.mAngle << std::endl;
                // 人脸宽度
                std::cout << "in Liveness::image_track_face_info mWidth is:" << ibox.mWidth << std::endl;
                // 中心点X,Y坐标
                std::cout << "in Liveness::image_track_face_info mCenter_x is:" << ibox.mCenter_x << std::endl;
                std::cout << "in Liveness::image_track_face_info mCenter_y is:" << ibox.mCenter_y << std::endl;
                std::vector<float> headPose = info.headPose;
                // 返回 x，y，z三个角度的人脸角度
                for (int k = 0; k < headPose.size(); k++)
                {
                    float angle = headPose.at(k);
                    std::cout << "in Liveness::image_track_face_info angle is:" << angle << std::endl;
                }
                // 画人脸框
                box = CvHelp::bounding_box(info.landmarks);
                CvHelp::draw_rotated_box(frame, box, cv::Scalar(0, 255, 0));
                // 画关键点轮廓
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

// 通过图片检测，输出人脸信息(传入二进制图片buffer）
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
            // 人脸信息
            FaceInfo ibox = info.box;
            // 角度
            std::cout << "in Liveness::image_track_face_info mAngle is:" << ibox.mAngle << std::endl;
            // 人脸宽度
            std::cout << "in Liveness::image_track_face_info mWidth is:" << ibox.mWidth << std::endl;
            // 中心点X,Y坐标
            std::cout << "in Liveness::image_track_face_info mCenter_x is:" << ibox.mCenter_x << std::endl;
            std::cout << "in Liveness::image_track_face_info mCenter_y is:" << ibox.mCenter_y << std::endl;
            std::vector<float> headPose = info.headPose;
            // 返回 x，y，z三个角度的人脸角度
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

//usb摄像头进行rgb单目活体检测
bool Liveness::usb_rgb_track(BaiduFaceApi *api, float default_score)
{
    bool pass = false;
    // device为0默认打开笔记本电脑自带摄像头，若为0打不开外置usb摄像头
    // 请把device修改为1或2再重试，1，或2为usb插上电脑后，电脑认可的usb设备id
    // 也可通过select_usb_device_id方法获取id
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
        // 设置通过分值，推荐0.8，用户也可以自己设定通过分值
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


// 双目摄像头进行ir,rgb活体检测
bool Liveness::ir_rgb_track(BaiduFaceApi *api, float default_score)
{
    int device_count = get_devices_count();
    if (device_count<2)
    {
        std::cout << "ir and rgb camera devices needed" << std::endl;
        return false;
    }
    bool pass = true;
    // 序号0为电脑识别的usb摄像头编号，本demo中0为ir红外摄像头
    // 不同摄像头和电脑识别可能有区别
    // 编号一般从0-10
    int device = select_usb_device_id();
    cv::VideoCapture camera1(device);
    if (!camera1.isOpened())
    {
        std::cout << "camera1 open error" << std::endl;
        return false;
    }
    // 序号1为电脑识别的usb摄像头编号，本demo中1为rgb可见光摄像头
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

// 红外IR活体检测
float Liveness::ir_liveness_track_by_img(BaiduFaceApi *api)
{
    float score = 0;
    std::string file_path = "d:\\ir1.png";
    //参数2表示传入图片文件路径
    std::string res = api->ir_liveness_check(file_path.c_str(), 2);
    if (res.length() > 0)
    {
        // 若json编译不过，请用下面被注释的代码（json库适配问题)
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

        // 若json编译不过，请用下面代码
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

// 红外IR活体检测(传入二进制图片buffer）
float Liveness::ir_liveness_track_by_buf(BaiduFaceApi *api)
{
    float score = 0;
    std::string out_buf;
    int buf_len = ImageBuf::get_buf("d:\\1.jpg", out_buf);
    //参数2表示传入图片文件路径
    std::string res = api->ir_liveness_check_by_buf((unsigned char*)out_buf.c_str(), buf_len);
    if (res.length() > 0)
    {
        // 若json编译不过，请用下面被注释的代码（json库适配问题)
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

        // 若json编译不过，请用下面代码
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

// 单目RGB活体检测
float Liveness::rgb_liveness_track_by_img(BaiduFaceApi *api)
{
    float score = 0;
     std::string file_path = "d:\\rgb1.png";
  //  std::string file_path = "d:\\1.jpg";
    //参数2表示传入图片文件路径
    std::string res = api->rgb_liveness_check(file_path.c_str(), 2);
    if (res.length() > 0)
    {
        // 若json编译不过，请用下面被注释的代码（josn库兼容性问题)
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

        // 若json编译不过，请用下面代码
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

// 单目RGB活体检测(传入二进制图片buffer)
float Liveness::rgb_liveness_track_by_buf(BaiduFaceApi *api)
{
    float score = 0;
    std::string out_buf;
    int buf_len = ImageBuf::get_buf("d:\\1.jpg", out_buf);
    //参数2表示传入图片文件路径
    std::string res = api->rgb_liveness_check_by_buf((unsigned char*)out_buf.c_str(), buf_len);
    if (res.length() > 0)
    {
        // 若json编译不过，请用下面被注释的代码（josn库兼容性问题)
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

        // 若json编译不过，请用下面代码
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

// 测试单目ir红外活体检测(传入opencv视频帧)
float Liveness::ir_liveness_track_by_frame(BaiduFaceApi *api, const cv::Mat &frame)
{
    float score = 0;
    std::string res = api->ir_liveness_check(frame);
    if (res.length() > 0)
    {
        // 若json编译不过，请用下面被注释的代码段（json库兼容性问题)
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

        // 若json编译不过，请用下面代码
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

// 测试单目RGB活体检测(传入opencv视频帧)
float Liveness::rgb_liveness_track_by_frame(BaiduFaceApi *api, const cv::Mat &frame)
{
    float score = 0;
    std::string res = api->rgb_liveness_check(frame);
    if (res.length() > 0)
    {
        // 若json编译不过，请用下面被注释的代码段（json兼容性问题)
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

        // 若json编译不过，请用下面代码
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
// 测试depth深度活体检测(传入opencv视频帧)
float Liveness::depth_liveness_track_by_frame(BaiduFaceApi*api, const cv::Mat &frame)
{
    float score = 0;
    std::string res;
 //   std::string res = api->depth_liveness_check(frame);
    if (res.length() > 0)
    {
        // 若json编译不过，请用下面被注释的代码段（json兼容性问题)
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

        // 若json编译不过，请用下面代码
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


// 双目摄像头进行rgb,depth活体检测
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

// 双目摄像头进行rgb,depth活体检测(此处适配了奥比中光的双目摄像头)
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

// 双目摄像头进行rgb,depth活体检测(此处适配了华杰艾米的双目摄像头)
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

