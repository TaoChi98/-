#ifndef HJIMI_CAMERA_H
#define HJIMI_CAMERA_H



typedef enum {
    IMI_DRIVER_NONE = 0x00,
    IMI_DRIVER_USB = 0x01,
    IMI_DRIVER_FILE = 0x02,
    IMI_DRIVER_NET = 0x03,
} ImiDriverType;

typedef uint32_t ImiFrameType;
enum {
    IMI_DEPTH_FRAME = 0x00,
    IMI_DEPTH_SKELETON_FRAME = 0x01,
    IMI_USER_INDEX_SKELETON_FRAME = 0x02,
    IMI_SKELETON_FRAME = 0x03,
    IMI_COLOR_FRAME = 0x04,
    IMI_IR_FRAME = 0x06,
};

typedef enum {
    IMI_COLOR_DATA = 0x00,
    IMI_DEPTH_DATA = 0x04,
    IMI_DEPTH_ORG_DATA = 0x05,
    IMI_DEPTH_SKELETON_DATA = 0x08,
    IMI_USER_INDEX_SKELETON_DATA = 0x0c,
    IMI_SKELETON_DATA = 0x10
} ImiDataType;

typedef enum {
    IMI_DEVICE_STATE_CONNECT = 0,
    IMI_DEVICE_STATE_DISCONNECT = 1
} ImiDeviceState;

typedef uint32_t ImiCoordinateConvertMode;
enum {
    IMI_COORDINATE_VGATOVGA = 0,
    IMI_COORDINATE_VGATO720P = 1,
    IMI_COORDINATE_VGATO1080P = 2,

    IMI_COORDINATE_QVGATOVGA = 3,
    IMI_COORDINATE_QVGATO720P = 4,
    IMI_COORDINATE_QVGATO1080P = 5
};

//basic struct
typedef struct tagImiDriverInfo {
    ImiDriverType		driverType;
    int32_t		 netListenPort;        // required when driverType is IMI_DRIVER_NET
    char			recordFilePath[255];  // required when driverType is IMI_DRIVER_FILE
} ImiDriverInfo;

#define MAX_SN_SIZE 64
typedef struct tagImiDeviceAttribute {
    uint16_t vendorId;
    uint16_t productId;
    uint32_t deviceAddress;
    char     serialNumber[MAX_SN_SIZE];
    char     uri[255];
} ImiDeviceAttribute;

typedef struct tagVector4I {
    int32_t x;
    int32_t y;
    int32_t z;
    int32_t w;
} ImiVector4I;

typedef struct tagVector4 {
    float x;
    float y;
    float z;
    float w;
} ImiVector4;

typedef struct tagPoint3D {
    float x;
    float y;
    float z;
}ImiPoint3D;
typedef enum
{
    IMI_PIXEL_FORMAT_DEP_16BIT = 0x00, //Depth

    IMI_PIXEL_FORMAT_IMAGE_YUV422 = 0x01, //Rgb
    IMI_PIXEL_FORMAT_IMAGE_H264 = 0x02, //H264 Compressed
    IMI_PIXEL_FORMAT_IMAGE_RGB24 = 0x03,
    IMI_PIXEL_FORMAT_IMAGE_YUV420SP = 0x04,  //NV21

    IMI_PIXEL_FORMAT_IR_16BIT = 0x09,
} ImiPixelFormat;
typedef int16_t ImiDepthPixel;
typedef struct tagImiFrame {
    ImiPixelFormat pixelFormat;
    ImiFrameType   type;
    uint32_t       frameNum;
    uint64_t       timeStamp;

    uint32_t       fps;
    int32_t        width;
    int32_t        height;

    void*		   pData;//depth color pixel data, if not null
    void*          pSkeletonData;//skeleton frame if not null
    uint32_t	   size;
} ImiImageFrame;


typedef enum
{
    CAMERA_PIXEL_FORMAT_RGB888 = 0x00,
    CAMERA_PIXEL_FORMAT_MJPEG = 0x01,
    CAMERA_PIXEL_FORMAT_YUYV = 0x02,
    CAMERA_PIXEL_FORMAT_YUV420SP = 0x03

}ImiCameraPixelFormat;


typedef struct tagImiCameraFrame
{
    ImiCameraPixelFormat      pixelFormat;
    uint32_t                  frameNum;
    uint64_t                  timeStamp;

    uint32_t                  fps;
    int32_t                   width;
    int32_t                   height;

    void*					  pData;
    uint32_t	              size;
}ImiCameraFrame;

#include "opencv2\opencv.hpp"

class  HjimiCamera
{
public:
	HjimiCamera();
	~HjimiCamera();
    bool open_camera(cv::Mat &rgb, cv::Mat &depth);
    bool open_camera(ImiCameraFrame *& rgb_frame, ImiImageFrame *& depth_frame);
    void frame_release(ImiCameraFrame *& rgb_frame, ImiImageFrame *& depth_frame);
  	
};
#endif