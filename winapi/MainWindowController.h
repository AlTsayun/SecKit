//
// Created by RedmiBook on 16.12.2020.
//

#ifndef SECKIT_MAINWINDOWCONTROLLER_H
#define SECKIT_MAINWINDOWCONTROLLER_H

#include "../framework.h"
#include <Windows.h>
#include "../core/mainService/RecordSupplier.h"

#include "styles.h"

class MainWindowController {
public:
    explicit MainWindowController(RecordSupplier* mainService);
    BOOL show(int nCmdShow);
    BOOL init(HINSTANCE hInstance);

protected:

    std::map<int, std::string>* listPositionToItemId = new std::map<int, std::string>();

    void loadRecords(std::deque<Record *> *records);
    void loadRecordTypes(std::deque<RecordTypeInfo *> *typeInfos);
    std::wstring stringToWString(const std::string& str);

    static LRESULT CALLBACK WindowProc(
            HWND hwnd,
            UINT uMsg,
            WPARAM wParam,
            LPARAM lParam
    );

    int m_font_height_ = 15;
    SCROLLINFO si;
    int yOffset = 0;
    LPCWSTR windowClassName = L"MainWindowController";
    int isInit;

    RecordSupplier *recordSupplier;

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
    #define IDM_RECORDS_SHOW (112)
    #define IDM_ABOUT (113)

    void onContextMenu(WPARAM wParam, LPARAM lParam);

    void onListContextMenu(WPARAM wParam, LPARAM lParam);

    void onOpenFile(WPARAM wParam, LPARAM lParam);
    void onSaveFile(WPARAM wParam, LPARAM lParam);
    void onNewFile(WPARAM wParam, LPARAM lParam);
    void onSearchButtonClick(WPARAM wParam, LPARAM lParam);
    void onInputButtonClick(WPARAM wParam, LPARAM lParam);

    void onListItemSelected(WPARAM wParam, LPARAM lParam);

    void onRecordDelete(WPARAM wParam, LPARAM lParam);

    #define EDIT_BUFFER_SIZE 1024
    TCHAR editBuffer[EDIT_BUFFER_SIZE];

    bool isRecords;
    bool isRecordTypes;

    void onRecordsShow(WPARAM wParam, LPARAM lParam);

    void onNewRecord(WPARAM wParam, LPARAM lParam);

    void onRecordSelected(WPARAM wParam, LPARAM lParam, int listPosition);

    void onRecordTypeSelected(WPARAM wParam, LPARAM lParam, int listPosition);

    #define CREATE_RECORD_TEXT ("To create a record enter any input")
    #define ABOUT_TEXT ("Hello\nThis is an app to store your passwords and other important information.")
    HFONT hMonospacedFont;

    void onDestroy(WPARAM wParam, LPARAM lParam);

    void onAbout(WPARAM wParam, LPARAM lParam);
    void clearOutput();

    std::string enterPassword();
};


#endif //SECKIT_MAINWINDOWCONTROLLER_H
