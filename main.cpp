#include <windows.h>
#include "winapi/MainWindowController.h"
#include "core/mainService/MainService.h"
#include "framework.h"
//#include<gdiplus.h>

//#pragma comment(lib, "gdiplus.lib")

//using namespace Gdiplus;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

    auto* window = new MainWindowController(MainService::getInstance());
    window->init(hInstance);
    window->show(nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

