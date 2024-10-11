#include "RenderWindow.h"

int initWindow(HINSTANCE hInstance, int nWinMode, static const TCHAR windowName[])
{
    // create an instance of the window class structure
    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
    wc.hIconSm = (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
    wc.hCursor = (HCURSOR)LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = windowName;

    if (0 == RegisterClassEx(&wc))
    {
        MessageBox(NULL, TEXT("Can't Register the Window Class!"), windowName, MB_OK | MB_ICONERROR);
        return E_FAIL;
    }

    // define the application title
    static const TCHAR szAppTitle[] = TEXT("Win32 API Skeletal Application");

    // create the window
    HWND hwnd = CreateWindow(windowName, szAppTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);

    // check if the window was created, exit if fail
    if (NULL == hwnd)
    {
        MessageBox(NULL, TEXT("Unable to Create the Main Window!"), windowName, MB_OK | MB_ICONERROR);
        return E_FAIL;
    }

    // show and update the window
    ShowWindow(hwnd, nWinMode);
    UpdateWindow(hwnd);
}


// processes the messages that Windows sends to the application ================
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // choose which Windows messages you want to use
    switch (message)
    {
    case WM_PAINT:
        HDC         hdc;
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);

        // draw some text centered in the client area
        RECT rect;
        GetClientRect(hwnd, &rect);
        DrawText(hdc, TEXT("Hello, Windows!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        EndPaint(hwnd, &ps);
        return S_OK;

    case WM_DESTROY:
        // exit the application
        PostQuitMessage(0);
        return S_OK;
    }

    // let Windows process any unhandled messages
    return DefWindowProc(hwnd, message, wParam, lParam);
}