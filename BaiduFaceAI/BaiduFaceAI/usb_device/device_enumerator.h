#ifndef TESTFACEAPI_TESTFACEAPI_USB_DEVICE_DEVICE_ENUMERATOR_H
#define TESTFACEAPI_TESTFACEAPI_USB_DEVICE_DEVICE_ENUMERATOR_H

#include <Windows.h>
#include <dshow.h>
#pragma comment(lib, "strmiids")
#include <map>
#include <string>

struct Device {
    int id; // This can be used to open the device in OpenCV
    std::string devicePath;
    std::string deviceName; // This can be used to show the devices to the user
};

class DeviceEnumerator {
public:
    // 获取usb视频设备列表
    static std::map<int, Device> get_usb_devices();
public:

    DeviceEnumerator() = default;
    std::map<int, Device> get_devices_map(const GUID deviceClass);
    std::map<int, Device> get_video_devices_map();

private:

    std::string convert_bstr2mbs(BSTR bstr);
    std::string convert_wcs2mbs(const wchar_t* pstr, long wslen);

};
#endif
