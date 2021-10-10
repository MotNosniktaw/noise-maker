#pragma once
#pragma comment(lib, "winmm.lib")

#include <napi.h>
using namespace std;

#include <Windows.h>

Napi::Array Method(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    int nDeviceCount = waveOutGetNumDevs();
    Napi::Array devices = Napi::Array::New(env, nDeviceCount);

    WAVEOUTCAPS woc;
    for (int n = 0; n < nDeviceCount; n++)
        if (waveOutGetDevCaps(n, &woc, sizeof(WAVEOUTCAPS)) == S_OK)
            devices[n] = woc.szPname;

    return devices;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "getAllDevices"),
                Napi::Function::New(env, Method));

    return exports;
}

NODE_API_MODULE(noiseMaker, Init)