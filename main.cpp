//
// Framework for the Direct X 2D
//

#include <istream>
#include <windows.h>
#include "D2DFramework.h"

const wchar_t gClassName[] = L"MyWindowsClass";

LRESULT CALLBACK WindowProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam
    );
D2DFramework myFramework;

int WINAPI wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                    _In_ LPWSTR lpCmdLine,
                    _In_ int nShowCmd)
{
    int ret = 0;

    // Try catch exception catch, when it runs, run try, otherwise run catch.
    try
    {
        D2DFramework myFrameWork;

        if (SUCCEEDED(myFrameWork.Initialize(hInstance))) {
            ret = myFrameWork.GameLoop();
        }
    }
    catch (const com_exception& e)
    {
        static wchar_t wstr[64] = { };
        size_t len;

        mbstowcs_s(&len, wstr, e.what(), 64);
        MessageBox(
            nullptr, reinterpret_cast<LPCSTR>(wstr), reinterpret_cast<LPCSTR>(L"DirectX Exception"),
            MB_ICONEXCLAMATION|MB_OK);

    }

  return ret;

}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.