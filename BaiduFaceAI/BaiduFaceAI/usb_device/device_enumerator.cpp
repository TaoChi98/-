#include "stdafx.h"
#include "device_enumerator.h"
#include <map>
#include <iostream>
// 获取usb视频设备列表
std::map<int, Device> DeviceEnumerator::get_usb_devices()
{
    DeviceEnumerator de;
    // Video Devices
    std::map<int, Device> devices = de.get_video_devices_map();
    // Print information about the devices
  /*  for (auto const &device : devices) {
        std::cout << "== VIDEO DEVICE (id:" << device.first << ") ==" << std::endl;
        std::cout << "Name: " << device.second.deviceName << std::endl;
        std::cout << "Path: " << device.second.devicePath << std::endl;
    }*/
    return devices;
}

std::map<int, Device> DeviceEnumerator::get_video_devices_map() {
    return get_devices_map(CLSID_VideoInputDeviceCategory);
}

// Returns a map of id and devices that can be used
std::map<int, Device> DeviceEnumerator::get_devices_map(const GUID deviceClass)
{
    std::map<int, Device> device_map;

    HRESULT hr = CoInitialize(nullptr);
    if (FAILED(hr)) {
        return device_map; // Empty deviceMap as an error
    }

    // Create the System Device Enumerator
    ICreateDevEnum *p_dev_enum = nullptr;
    hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&p_dev_enum));

    // If succeeded, create an enumerator for the category
    IEnumMoniker *p_enum = nullptr;
    if (SUCCEEDED(hr)) {
        hr = p_dev_enum->CreateClassEnumerator(deviceClass, &p_enum, 0);
        if (hr == S_FALSE) {
            hr = VFW_E_NOT_FOUND;
        }
        p_dev_enum->Release();
    }

    // Now we check if the enumerator creation succeeded
    int device_id = -1;
    if (SUCCEEDED(hr)) {
        // Fill the map with id and friendly device name
        IMoniker *p_moniker = NULL;
        while (p_enum->Next(1, &p_moniker, NULL) == S_OK) {

            IPropertyBag *p_prop_bag = nullptr;
            HRESULT hr = p_moniker->BindToStorage(0, 0, IID_PPV_ARGS(&p_prop_bag));
            if (FAILED(hr)) {
                p_moniker->Release();
                continue;
            }

            // Create variant to hold data
            VARIANT var;
            VariantInit(&var);

            std::string device_name;
            std::string device_path;

            // Read FriendlyName or Description
            hr = p_prop_bag->Read(L"Description", &var, 0); // Read description
            if (FAILED(hr)) {
                // If description fails, try with the friendly name
                hr = p_prop_bag->Read(L"FriendlyName", &var, 0);
            }
            // If still fails, continue with next device
            if (FAILED(hr)) {
                VariantClear(&var);
                continue;
            }
            // Convert to string
            else {
                device_name = convert_bstr2mbs(var.bstrVal);
            }

            VariantClear(&var); // We clean the variable in order to read the next value

                                // We try to read the DevicePath
            hr = p_prop_bag->Read(L"DevicePath", &var, 0);
            if (FAILED(hr)) {
                VariantClear(&var);
                continue; // If it fails we continue with next device
            }
            else {
                device_path = convert_bstr2mbs(var.bstrVal);
            }

            // We populate the map
            device_id++;
            Device current_device;
            current_device.id = device_id;
            current_device.deviceName = device_name;
            current_device.devicePath = device_path;
            device_map[device_id] = current_device;

        }
        p_enum->Release();
    }
    CoUninitialize();
    return device_map;
}

/*
This two methods were taken from
https://stackoverflow.com/questions/6284524/bstr-to-stdstring-stdwstring-and-vice-versa
*/

std::string DeviceEnumerator::convert_bstr2mbs(BSTR bstr)
{
    int wslen = ::SysStringLen(bstr);
    return convert_wcs2mbs((wchar_t*)bstr, wslen);
}

std::string DeviceEnumerator::convert_wcs2mbs(const wchar_t* pstr, long wslen)
{
    int len = ::WideCharToMultiByte(CP_ACP, 0, pstr, wslen, NULL, 0, NULL, NULL);

    std::string dblstr(len, '\0');
    len = ::WideCharToMultiByte(CP_ACP, 0 /* no flags */,
        pstr, wslen /* not necessary NULL-terminated */,
        &dblstr[0], len,
        NULL, NULL /* no default char */);

    return dblstr;
}
