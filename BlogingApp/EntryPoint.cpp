//#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <string>
#include <Windows.h>

#define ID_EDIT 100
//#define ID_BTN 101
static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Simple APP");

//WCHAR szBuf[128];

WNDPROC DefEditProc;

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
            _T("Simple APP"),
            NULL);
        return 1;
    }


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
    ShowWindow(hWnd, nCmdShow);
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
    static HWND hEdit;
    //static HWND hButton;
    //PAINTSTRUCT ps;
    //HDC hdc;

    switch (message)
    {
    case WM_CREATE:
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
        break;
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
    switch (uMsg)
    {
    case WM_KEYDOWN:
        switch (wParam) {

        case VK_RETURN:
            if (!GetAsyncKeyState(VK_CONTROL)) {
                
                MessageBox(hWnd, _T("ASDF"), _T("QWER"), 128);
            }
            break;
        }
        break;
    default:
        return CallWindowProc(DefEditProc, hWnd, uMsg, wParam, lParam);

    }

    return FALSE;
}