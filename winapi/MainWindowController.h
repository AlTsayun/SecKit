//
// Created by RedmiBook on 16.12.2020.
//

#ifndef SECKIT_MAINWINDOWCONTROLLER_H
#define SECKIT_MAINWINDOWCONTROLLER_H

#include "../framework.h"
#include <Windows.h>
#include "../core/mainService/MainService.h"

#include "styles.h"

class MainWindowController {
public:
    explicit MainWindowController(MainService* mainService);
    BOOL show(int nCmdShow);
    void onPaint(WPARAM wParam, LPARAM lParam);
    BOOL init(HINSTANCE hInstance);

private:

    static LRESULT CALLBACK WindowProc(
            HWND hwnd,
            UINT uMsg,
            WPARAM wParam,
            LPARAM lParam
    );
    void onWindowResized(int clientAreaHeight);

    void onScrolled(WPARAM wParam, LPARAM lParam);
protected:
    int m_font_height_ = 15;
    SCROLLINFO si;
    int yOffset = 0;
    LPCWSTR windowClassName = L"MainWindowController";
    int isInit;

    MainService *mainService;

    //controls
    HWND mainWindow_hwnd;

    HWND searchButton_hwnd;
    #define ID_SEARCH_BUTTON (100)

    HWND list_hwnd;
    #define ID_LIST (101)
    HMENU hListContextMenu;

    HWND listLabel_hwnd;
    #define ID_LIST_LABEL (102)

    HWND searchEdit_hwnd;
    #define ID_SEARCH_EDIT (103)

    HWND outputText_hwnd;
    #define ID_OUTPUT_TEXT (104)

    HWND inputEdit_hwnd;
    #define ID_INPUT_EDIT (105)

    HWND inputButton_hwnd;
    #define ID_INPUT_BUTTON (106)


    void onCommand(WPARAM wParam, LPARAM lParam);

    HICON hWindowIcon;
    const LPCWSTR iconPath = L"./resources/";

    HMENU hMenubar;
    #define IDM_FILE_NEW (107)
    #define IDM_FILE_OPEN (108)
    #define IDM_FILE_SAVE (109)
    #define IDM_RECORD_NEW (110)
    #define IDM_RECORD_DELETE (111)

    void onContextMenu(WPARAM wParam, LPARAM lParam);

    void onListContextMenu(WPARAM wParam, LPARAM lParam);

};


#endif //SECKIT_MAINWINDOWCONTROLLER_H
