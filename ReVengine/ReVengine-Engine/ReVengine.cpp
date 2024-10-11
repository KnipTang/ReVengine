#include "ReVengine.h"
#include "DirectX11/RenderWindow.h"
#include "Windows.h"
#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nWinMode)
{
    // define the window class name
    static const TCHAR szAppName[] = TEXT("MinimalWindowsApp");

	initWindow(hInstance, nWinMode, szAppName);

    static BOOL bRet;
    static MSG  msg;

    // enter the main message loop
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) // 0 = WM_QUIT
    {
        // check for error
        if (-1 == bRet)
        {
            // handle the error and possibly exit

            // for this app simply report error and exit
            MessageBox(NULL, TEXT("Unable to Continue!"), szAppName, MB_OK | MB_ICONERROR);
            return E_FAIL;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            mainLoop();
        }
    }

    // the app is done, exit normally, return control to Windows
    return (int)msg.wParam;
}

void mainLoop()
{
    std::cout << "I";
}