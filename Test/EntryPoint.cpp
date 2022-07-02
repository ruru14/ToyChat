// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <string>
#include <Windows.h>
#include <windowsx.h>

#define ID_EDIT 100
#define ID_BTN 102
// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

WCHAR sz_Buf[128];
// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Windows Desktop Guided Tour");

// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;
WNDPROC DefEditProc;

HWND hEdit;
//static HWND hButton;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SubEditProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;
    //DefEditProc = (WNDPROC)SetWindowLongPtr()
    //DefEditProc = (WNDPROC)SetWindowLong(hwndEdit, GWL_WNDPROC, (long)EditProc);

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindowEx explained:
    // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application
    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW, //WS_OVERLAPPEDWINDOW, WS_POPUPWINDOW
        10, 10, // Start Position
        310, 510, // Window Size
        NULL,
        NULL,
        hInstance,
        NULL
    );


    //hEdit = CreateWindow(_T("edit"), _T("??"), WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 10, 100, 50, hWnd, (HMENU)ID_EDIT, hInst, NULL);
    

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(hWnd,  nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("aaaaaa");
    static std::basic_string<TCHAR> tstr;
    RECT rt;

    switch (message)
    {
    case WM_CREATE:
        hdc = GetWindowDC(hWnd);
        GetClientRect(hWnd, &rt);
        DrawText(hdc, _T("HELLO"), -1, &rt, DT_SINGLELINE);

        ReleaseDC(hWnd, hdc);
        hEdit = CreateWindowEx(
            0, L"EDIT",   // predefined class 
            NULL,         // no window title 
            WS_CHILD | WS_VISIBLE | WS_BORDER |
            ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN,
            10, 410, 
            270, 50,   // set size in WM_SIZE message 
            hWnd,         // parent window 
            (HMENU)ID_EDIT,   // edit control ID 
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);        // pointer not needed 
        //hButton = CreateWindowEx(
        //    0, L"BUTTON",   // predefined class 
        //    NULL,         // no window title 
        //    BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE,
        //    100, 100, 50, 50,   // set size in WM_SIZE message 
        //    hWnd,         // parent window 
        //    (HMENU)ID_BTN,   // edit control ID 
        //    (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        //    NULL);        // pointer not needed 

        DefEditProc = (WNDPROC)SetWindowLongPtr(hEdit, GWLP_WNDPROC, (LONG_PTR)SubEditProc);
        SetParent(hEdit, hWnd);
        break;
    //case WM_PAINT:
    //    hdc = BeginPaint(hWnd, &ps);
    //    //hdc = GetWindowDC(hWnd);
    //        GetClientRect(hWnd, &rt);
    //        SetTextColor(hdc, 0x00000000);
    //        SetBkMode(hdc, TRANSPARENT);
    //        DrawText(hdc, _T("HELLO"), -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    //    // Here your application is laid out.
    //    // For this introduction, we just print out "Hello, Windows desktop!"
    //    // in the top left corner.
    //    /*TextOut(hdc,
    //        0, 0,
    //        greeting, _tcslen(greeting));*/
    //    // End application-specific layout section.

    //        //ReleaseDC(hWnd, hdc);
    //    EndPaint(hWnd, &ps);
    //    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

//Then add this template
LRESULT CALLBACK SubEditProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rt;

    TCHAR msg[] = _T("asdf");
    switch (uMsg)
    {
    case WM_KEYDOWN:
        switch (wParam) {
        
        case VK_RETURN:
            hdc = GetDC(GetParent(hEdit));
            //hdc = BeginPaint(GetParent(hEdit), &ps);
            //hdc = GetWindowDC(hWnd);
            GetClientRect(GetParent(hEdit), &rt);
            SetTextColor(hdc, 0x00000000);
            SetBkMode(hdc, TRANSPARENT);
            DrawText(hdc, _T("HELLO"), -1, &rt, DT_SINGLELINE|DT_CENTER|DT_VCENTER);


            // Here your application is laid out.
            // For this introduction, we just print out "Hello, Windows desktop!"
            // in the top left corner.
            /*TCHAR buff[1024];
            GetWindowText(hEdit, buff, 1024);
            SetWindowText(hEdit, _T(""));
            DrawText(hdc, buff, -1, &rt, DT_CENTER);*/
            /*TextOut(hdc,
                5, 5,
                msg, _tcslen(msg));*/
            // End application-specific layout section.

            //MessageBox(GetParent(hEdit), _T("ASDF"), _T("QWER"), 128);
            //EndPaint(hWnd, &ps);
            /*if (!GetAsyncKeyState(VK_CONTROL)) {

            }*/
            ReleaseDC(GetParent(hEdit), hdc);
            //EndPaint(GetParent(hEdit), &ps);
            break;
        }
        break;
    default:
        return CallWindowProc(DefEditProc, hWnd, uMsg, wParam, lParam);

    }

    return FALSE;
}