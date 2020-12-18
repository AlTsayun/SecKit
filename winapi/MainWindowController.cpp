//
// Created by RedmiBook on 16.12.2020.
//

#include "MainWindowController.h"
#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include "MainWindowController.h"

MainWindowController::MainWindowController(MainService* mainService)
{
    this->mainService = mainService;
}
LRESULT CALLBACK MainWindowController::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    if (uMsg == WM_CREATE)
    {
        auto* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        auto* _this = reinterpret_cast<MainWindowController*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)_this);

    }
    else
    {
        MainWindowController* _this = reinterpret_cast<MainWindowController*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        if (uMsg == WM_SIZE)
        {
            _this->onWindowResized(HIWORD (lParam));
        }
//        else if (uMsg == WM_PAINT)
//        {
//            _this->onPaint(wParam, lParam);
// //           _this->onFirstPaint();
//        }
        else if (uMsg == WM_CONTEXTMENU)
        {
            _this->onContextMenu(wParam, lParam);
//            HMENU hPopupMenu = CreatePopupMenu();
//            InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_CLOSE, (LPCWSTR)"Exit");
//            InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_EXIT, (LPCWSTR)"Play");
//            SetForegroundWindow(hWnd);
//            TrackPopupMenu(hPopupMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, 0, 0, 0, hWnd, NULL);
        }
        else if (uMsg == WM_VSCROLL)
        {
            _this->onScrolled(wParam, lParam);
        }
        else if (uMsg == WM_COMMAND)
        {
            _this->onCommand(wParam, lParam);
        }
        else if ((uMsg == WM_DESTROY) || (uMsg == WM_CLOSE)) {
            PostQuitMessage(0);
        }
        else {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
        return 0;
    }
}

BOOL MainWindowController::init(HINSTANCE hInstance)
{
    // Register the window class.

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = windowClassName;

    RegisterClass(&wc);

    // Create the menu

    hMenubar = CreateMenu();

    HMENU hMenu = CreateMenu();
    AppendMenu(hMenu, MF_STRING, IDM_FILE_NEW, L"&New");
    AppendMenu(hMenu, MF_STRING, IDM_FILE_OPEN, L"&Open");
    AppendMenu(hMenu, MF_STRING, IDM_FILE_SAVE, L"&Save");
    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&File");

    hMenu = CreateMenu();
    AppendMenu(hMenu, MF_STRING, IDM_RECORD_NEW, L"&New");
    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&Record");


    // Create the window
    mainWindow_hwnd = CreateWindowEx(
            main_window_args,
            NULL,
            hMenubar,
            hInstance,
            this);

    if (mainWindow_hwnd == NULL)
    {
        std::cout << "NullPointerException!!!!";
        return FALSE;
    }

//    if(hWindowIcon!=NULL)
//        DestroyIcon(hWindowIcon);
////    hWindowIcon =LoadIcon(GetModuleHandle(NULL), iconPath);
//    SendMessage(mainWindow_hwnd, WM_SETICON, ICON_BIG, (LPARAM)hWindowIcon);
//    SendMessage(mainWindow_hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hWindowIcon);


    listLabel_hwnd = CreateWindowEx(
            list_label_args,
            mainWindow_hwnd,
            (HMENU) ID_LIST_LABEL,
            hInstance,
            NULL);

    SetWindowText(listLabel_hwnd, L"Records");

    hListContextMenu = CreatePopupMenu();
    AppendMenu(hListContextMenu, MF_BYCOMMAND | MF_STRING | MF_ENABLED, IDM_RECORD_DELETE, L"Delete selected");
    EnableMenuItem(hListContextMenu, IDM_RECORD_DELETE, MF_GRAYED);
    list_hwnd = CreateWindowEx(
            list_args,
            mainWindow_hwnd,
            (HMENU) ID_LIST,
            hInstance,
            NULL);

    SendMessage(list_hwnd, LB_ADDSTRING, 0, (LPARAM) L"first");
    SendMessage(list_hwnd, LB_ADDSTRING, 0, (LPARAM) L"first");
    SendMessage(list_hwnd, LB_ADDSTRING, 0, (LPARAM) L"first");
    SendMessage(list_hwnd, LB_ADDSTRING, 0, (LPARAM) L"first");


    searchEdit_hwnd = CreateWindowEx(
            search_edit_args,
            mainWindow_hwnd,
            (HMENU) ID_LIST,
            hInstance,
            NULL);

    searchButton_hwnd = CreateWindowEx(
            search_button_args,
            mainWindow_hwnd,
            (HMENU) ID_SEARCH_BUTTON,
            hInstance,
            NULL);

    outputText_hwnd = CreateWindowEx(
            output_text_args,
            mainWindow_hwnd,
            (HMENU) ID_OUTPUT_TEXT,
            hInstance,
            NULL);

    inputButton_hwnd = CreateWindowEx(
            input_button_args,
            mainWindow_hwnd,
            (HMENU) ID_INPUT_BUTTON,
            hInstance,
            NULL);

    inputEdit_hwnd = CreateWindowEx(
            input_edit_args,
            mainWindow_hwnd,
            (HMENU) ID_INPUT_EDIT,
            hInstance,
            NULL);

    return TRUE;
}
BOOL MainWindowController::show(int nCmdShow)
{
    std::cout << "preparing to show window";
    if (mainWindow_hwnd == NULL) {
        std::cout << "window is not initialized or an error happend while initializing\n";
        return FALSE;
    }
    UpdateWindow(mainWindow_hwnd);
    return ShowWindow(mainWindow_hwnd, nCmdShow);
}

void MainWindowController::onWindowResized(int clientAreaHeight)
{

}

void MainWindowController::onPaint(WPARAM wParam, LPARAM lParam)
{

}
void MainWindowController::onScrolled(WPARAM wParam, LPARAM lParam)
{

}

void MainWindowController::onCommand(WPARAM wParam, LPARAM lParam) {
    if (LOWORD(wParam) == ID_LIST) {
        if (HIWORD(wParam) == LBN_SELCHANGE){
            int selected = SendMessage(list_hwnd, LB_GETCURSEL, 0, 0);
            SendMessage(list_hwnd, LB_ADDSTRING, 0, (LPARAM) L"added");
            if (selected > -1){
                EnableMenuItem(hListContextMenu, IDM_RECORD_DELETE, MF_ENABLED);
            } else {
                EnableMenuItem(hListContextMenu, IDM_RECORD_DELETE, MF_GRAYED);
            }
        }
    }
    if (LOWORD(wParam) == IDM_RECORD_DELETE) {
        int selected = SendMessage(list_hwnd, LB_GETCURSEL, 0, 0);
        selected +=0;

    }

}

void MainWindowController::onContextMenu(WPARAM wParam, LPARAM lParam) {
    if ((HWND)wParam == list_hwnd){
        onListContextMenu(wParam, lParam);
    }
}

void MainWindowController::onListContextMenu(WPARAM wParam, LPARAM lParam) {
    TrackPopupMenu(hListContextMenu, TPM_TOPALIGN | TPM_LEFTALIGN, LOWORD(lParam), HIWORD(lParam), 0, mainWindow_hwnd, NULL);
}
