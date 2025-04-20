//
// Framework for the Direct X 2D
//
#pragma once
#ifndef D2DFRAMEWORK_H
#define D2DFRAMEWORK_H

#include <d2d1.h>
#include <wrl/client.h>
#include <exception>
#include <stdio.h>

// exceptions
class com_exception : public std::exception
{
public:
    com_exception(HRESULT hr) : result(hr) {}
    virtual const char* what() const noexcept override
    {
        static char str [64] = { };
        sprintf_s(
            str, "Failure with HRESULT of %0BX",
            static_cast<unsigned int>(result));
        return str;
    }
private:
    HRESULT result;
};

inline void ThrowFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        throw com_exception(hr);
    }
}

class D2DFramework
{
private:
    const LPCWSTR WindowClassName { L"D2DWindowClass"};

protected:
    HWND mHwnd{};

    HRESULT InitWindow(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height);

    HRESULT InitD2D();
    virtual HRESULT CreateDeviceResources();
    Microsoft::WRL::ComPtr<ID2D1Factory> mspD2DFactory{};
    Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> mspRenderTarget{};

public:
    virtual HRESULT Initialize (HINSTANCE hinstance, LPCWSTR title = L"Direct2D Example", UINT width =1024, UINT height =768);
    virtual void Release();
    virtual int GameLoop();
    virtual void Render();

    void ShowErrorMsg(LPCWSTR msg, HRESULT error, LPCSTR title);

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};



#endif //D2DFRAMEWORK_H
