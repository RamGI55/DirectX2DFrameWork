//
// Framework for the Direct X 2D
//

#include "D2DFramework.h"
#include <sstream>


#pragma comment (lib, "d2d1.lib")

int main(int argc, char* argv[])
{

    return 0;
}

// Let's move the init windows to the framework!
HRESULT D2DFramework::InitWindow(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height) {

    HWND hwnd;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = reinterpret_cast<LPCSTR>(WindowClassName);
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.lpfnWndProc = D2DFramework::WndProc; // how I can move window procceure
    wc.cbSize = sizeof(WNDCLASSEX);
    if (!RegisterClassEx(&wc))
    {
        MessageBox(
            nullptr, reinterpret_cast<LPCSTR>(L"Failed to register the window class!"),reinterpret_cast<LPCSTR>(L"Error"),
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    RECT wr = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height)};
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
    hwnd = CreateWindowEx(0,
        reinterpret_cast<LPCSTR>(WindowClassName),
        reinterpret_cast<LPCSTR>(title),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        wr.right-wr.left,
        wr.bottom-wr.top,
        NULL,
        NULL,
        hInstance,
        nullptr);

    SetWindowLongPtr (mHwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    if (hwnd == nullptr)
    {
        MessageBox(
            nullptr, reinterpret_cast<LPCSTR>(L"Failed to create window!"),reinterpret_cast<LPCSTR>(L"Error"),
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
}

HRESULT D2DFramework::InitD2D() {

    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
       mspD2DFactory.GetAddressOf()
       );
    // single threaded and get address of the factory.
    ThrowFailed(hr);


    return CreateDeviceResources();

}

HRESULT D2DFramework::CreateDeviceResources() {

    RECT wr;
    GetClientRect(mHwnd, &wr);

    D2D1_SIZE_U  size = D2D1::SizeU(wr.right-wr.left, wr.bottom-wr.top);
    HRESULT hr = mspD2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(mHwnd,
            size),
            mspRenderTarget.GetAddressOf()
            );

    ThrowFailed(hr);
    return hr;
}

HRESULT D2DFramework::Initialize(HINSTANCE hinstance, LPCWSTR title, UINT width, UINT height) {

    HRESULT ret;
    ret = InitWindow (hinstance, title, width, height);
    ThrowFailed(ret);

    ret=InitD2D();
    ThrowFailed(ret);
    return ret;
}

void D2DFramework::Release()
{
}

int D2DFramework::GameLoop() {
    MSG msg{};
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if ( msg.message == WM_QUIT) {
                 break;
            }

        }
        else {
            Render();
        }
    }
    return static_cast<int>(msg.wParam);
}

void D2DFramework::Render()
{
    HRESULT hr;
    mspRenderTarget->BeginDraw();
    mspRenderTarget->Clear(D2D1::ColorF(0.f,0.2f, 0.4f, 1.0f));
    // TODO
    hr = mspRenderTarget->EndDraw();

    if (hr == D2DERR_RECREATE_TARGET) {
        CreateDeviceResources();
    }
}

void D2DFramework::ShowErrorMsg(LPCWSTR msg, HRESULT error, LPCSTR title)
{
    std::wostringstream oss;
    oss << "ERROR : 0x" << std::hex << error << std::endl;
    oss << msg;
    OutputDebugString(reinterpret_cast<LPCSTR>(oss.str().c_str()));

    MessageBox(
        nullptr, reinterpret_cast<LPCSTR>(oss.str().c_str()), title, MB_ICONEXCLAMATION | MB_OK);


}

LRESULT D2DFramework::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    D2DFramework* pFramework = reinterpret_cast<D2DFramework*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    switch (uMsg) {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 1;

}
