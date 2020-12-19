//
// Created by RedmiBook on 16.12.2020.
//

#include "MainWindowController.h"
#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include "MainWindowController.h"

MainWindowController::MainWindowController(RecordSupplier* mainService)
{
    isPassword = FALSE;
    this->recordSupplier = mainService;
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

        if (uMsg == WM_CONTEXTMENU)
        {
            _this->onContextMenu(wParam, lParam);
        }
        else if (uMsg == WM_COMMAND)
        {
            _this->onCommand(wParam, lParam);
        }
        else if ((uMsg == WM_DESTROY) || (uMsg == WM_CLOSE)) {
            _this->onDestroy(wParam, lParam);
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
    AppendMenu(hMenu, MF_STRING, IDM_RECORDS_SHOW, L"&Show");
    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&Records");

    hMenu = CreateMenu();
    AppendMenu(hMenu, MF_STRING, IDM_ABOUT, L"&About");
    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&Help");

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

    listLabel_hwnd = CreateWindowEx(
            list_label_args,
            mainWindow_hwnd,
            (HMENU) ID_LIST_LABEL,
            hInstance,
            NULL);

    hListContextMenu = CreatePopupMenu();
    AppendMenu(hListContextMenu, MF_BYCOMMAND | MF_STRING | MF_ENABLED, IDM_RECORD_DELETE, L"Delete selected");
    EnableMenuItem(hListContextMenu, IDM_RECORD_DELETE, MF_GRAYED);
    list_hwnd = CreateWindowEx(
            list_args,
            mainWindow_hwnd,
            (HMENU) ID_LIST,
            hInstance,
            NULL);


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

    hMonospacedFont  = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                                        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Courier New"));
    SendMessage(outputText_hwnd, WM_SETFONT, WPARAM(hMonospacedFont), TRUE);

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


    auto* records = recordSupplier->getAllRecords();
    loadRecords(records);
    delete(records);

    isPassword = false;
    onAbout(0,0);

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

void MainWindowController::onCommand(WPARAM wParam, LPARAM lParam) {
    if (LOWORD(wParam) == ID_LIST) {
        if (HIWORD(wParam) == LBN_SELCHANGE){
            onListItemSelected(wParam, lParam);
        }
    }
    if (LOWORD(wParam) == IDM_RECORD_DELETE) {
        onRecordDelete(wParam, lParam);
    }
    if (LOWORD(wParam) == IDM_FILE_OPEN){
        onOpenFile(wParam, lParam);
    }

    if(LOWORD(wParam) == IDM_FILE_SAVE){
        onSaveFile(wParam, lParam);
    }

    if(LOWORD(wParam) == IDM_FILE_NEW){
        onNewFile(wParam, lParam);
    }

    if(LOWORD(wParam) == ID_SEARCH_BUTTON){
        onSearchButtonClick(wParam, lParam);
    }

    if(LOWORD(wParam) == ID_INPUT_BUTTON){
        onInputButtonClick(wParam, lParam);
    }

    if(LOWORD(wParam) == IDM_RECORDS_SHOW){
        onRecordsShow(wParam, lParam);
    }

    if(LOWORD(wParam) == IDM_RECORD_NEW){
        onNewRecord(wParam, lParam);
    }

    if(LOWORD(wParam) == IDM_ABOUT){
        onAbout(wParam, lParam);
    }

}

void MainWindowController::onContextMenu(WPARAM wParam, LPARAM lParam) {
    if ((HWND)wParam == list_hwnd){
        onListContextMenu(wParam, lParam);
    }
}

void MainWindowController::onListContextMenu(WPARAM wParam, LPARAM lParam) {
    if (isRecords) {
        TrackPopupMenu(hListContextMenu, TPM_TOPALIGN | TPM_LEFTALIGN, LOWORD(lParam), HIWORD(lParam), 0,
                       mainWindow_hwnd, NULL);
    }
}

void MainWindowController::loadRecords(std::deque<Record *> *records) {
    clearOutput();
    isRecords = true;
    isRecordTypes = false;
    SendMessage(list_hwnd, LB_RESETCONTENT, 0, 0);
    listPositionToItemId->clear();
    int i = 0;
    for(auto* record: *records){
        SendMessage(list_hwnd, LB_ADDSTRING, 0, (LPARAM) stringToWString(record->getName()).c_str());
        listPositionToItemId->insert(std::make_pair(i, record->getId()));
        i++;
    }
    SetWindowText(listLabel_hwnd, L"Records");
}

std::wstring MainWindowController::stringToWString(const std::string& str) {
    int len;
    int strLen = (int)str.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), strLen, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), strLen, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

void MainWindowController::loadRecordTypes(std::deque<RecordTypeInfo *> *typeInfos) {
    clearOutput();
    isRecordTypes = true;
    isRecords = false;
    SendMessage(list_hwnd, LB_RESETCONTENT, 0, 0);
    listPositionToItemId->clear();
    int i = 0;
    for(auto* typeInfo: *typeInfos){
        SendMessage(list_hwnd, LB_ADDSTRING, 0, (LPARAM) stringToWString(typeInfo->getName()).c_str());
        listPositionToItemId->insert(std::make_pair(i, typeInfo->getIdentifier()));
        i++;
    }
    SetWindowText(listLabel_hwnd, L"Record types");
}

void MainWindowController::onListItemSelected(WPARAM wParam, LPARAM lParam) {
    int position = SendMessage(list_hwnd, LB_GETCURSEL, 0, 0);
    isPassword= false;
    if (isRecords){
        if (position > -1){
            EnableMenuItem(hListContextMenu, IDM_RECORD_DELETE, MF_ENABLED);
            onRecordSelected(wParam, lParam, position);
        } else {
            EnableMenuItem(hListContextMenu, IDM_RECORD_DELETE, MF_GRAYED);
        }
    }
    if (isRecordTypes){
        if (position > -1) {
            EnableMenuItem(hListContextMenu, IDM_RECORD_DELETE, MF_DISABLED);
            onRecordTypeSelected(wParam, lParam, position);
        }
    }
}

void MainWindowController::onRecordDelete(WPARAM wParam, LPARAM lParam) {
    int position = SendMessage(list_hwnd, LB_GETCURSEL, 0, 0);
    if (listPositionToItemId->find(position) != listPositionToItemId->end()){
        recordSupplier->removeRecordById(listPositionToItemId->at(position));
        listPositionToItemId->erase(position);
        auto *records = recordSupplier->getAllRecords();
        loadRecords(records);
        delete(records);
    }
    clearOutput();
}

void MainWindowController::onOpenFile(WPARAM wParam, LPARAM lParam) {
    enterPassword([](MainWindowController *_this,std::string password){
        try{
            OPENFILENAME ofn;
            TCHAR szFileName[MAX_PATH] = L"";

            ZeroMemory(&ofn, sizeof(ofn));

            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = _this->mainWindow_hwnd;
            ofn.lpstrFilter = L"Encrypted Files (*.enc)\0*.enc\0All Files (*.*)\0*.*\0";
            ofn.lpstrFile = szFileName;
            ofn.nMaxFile = MAX_PATH;
            ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
            ofn.lpstrDefExt = L"enc";

            if (GetOpenFileName(&ofn)) {
                std::wstring tmp(&szFileName[0]);
                std::string pathToFile(tmp.begin(), tmp.end());
                _this->recordSupplier->loadFile(pathToFile, password);
            }
            _this->onRecordsShow(0, 0);
        }catch(...){
            _this->showWrongPassword(password);
        }
    });
//    OPENFILENAME ofn;
//    TCHAR szFileName[MAX_PATH] = L"";
//
//    ZeroMemory(&ofn, sizeof(ofn));
//
//    ofn.lStructSize = sizeof(ofn);
//    ofn.hwndOwner = mainWindow_hwnd;
//    ofn.lpstrFilter = L"Encrypted Files (*.enc)\0*.enc\0All Files (*.*)\0*.*\0";
//    ofn.lpstrFile = szFileName;
//    ofn.nMaxFile = MAX_PATH;
//    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
//    ofn.lpstrDefExt = L"enc";
//
//    if (GetOpenFileName(&ofn)) {
//        std::wstring tmp(&szFileName[0]);
//        std::string pathToFile(tmp.begin(), tmp.end());
//        recordSupplier->loadFile(pathToFile, "Hello");
//    }
//    onRecordsShow(0,0);
}

void MainWindowController::onSaveFile(WPARAM wParam, LPARAM lParam) {

    enterPassword([](MainWindowController *_this,std::string password){
        OPENFILENAME ofn;
        TCHAR szFileName[MAX_PATH] = L"";

        ZeroMemory(&ofn, sizeof(ofn));

        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = _this->mainWindow_hwnd;
        ofn.lpstrFilter = L"Encrypted Files (*.enc)\0*.enc\0All Files (*.*)\0*.*\0";
        ofn.lpstrFile = szFileName;
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
        ofn.lpstrDefExt = L"enc";

        if(GetSaveFileName(&ofn))
        {
            std::wstring tmp(&szFileName[0]);
            std::string pathToFile(tmp.begin(), tmp.end());
            _this->recordSupplier->saveFile(pathToFile, password);
        }
        _this->clearOutput();
    });
//    OPENFILENAME ofn;
//    TCHAR szFileName[MAX_PATH] = L"";
//
//    ZeroMemory(&ofn, sizeof(ofn));
//
//    ofn.lStructSize = sizeof(ofn);
//    ofn.hwndOwner = mainWindow_hwnd;
//    ofn.lpstrFilter = L"Encrypted Files (*.enc)\0*.enc\0All Files (*.*)\0*.*\0";
//    ofn.lpstrFile = szFileName;
//    ofn.nMaxFile = MAX_PATH;
//    ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
//    ofn.lpstrDefExt = L"enc";
//
//    if(GetSaveFileName(&ofn))
//    {
//        std::wstring tmp(&szFileName[0]);
//        std::string pathToFile(tmp.begin(), tmp.end());
//        recordSupplier->saveFile(pathToFile, "Hello");
//    }
//    clearOutput();
}

void MainWindowController::onNewFile(WPARAM wParam, LPARAM lParam) {
    recordSupplier->removeAllRecords();
    loadRecords(recordSupplier->getAllRecords());
}

void MainWindowController::onSearchButtonClick(WPARAM wParam, LPARAM lParam) {

    clearOutput();

    GetWindowText(searchEdit_hwnd, editBuffer, sizeof(editBuffer));
    std::wstring tmp(&editBuffer[0]);
    std::string searchQuery(tmp.begin(), tmp.end());
    if(isRecords)
    {
        auto *records = recordSupplier->findRecordsBySearchQuery(searchQuery);
        loadRecords(records);
        delete (records);
    }
    if (isRecordTypes){
        auto *records = recordSupplier->findTypesBySearchQuery(searchQuery);
        loadRecordTypes(records);
        delete (records);
    }
}

void MainWindowController::onInputButtonClick(WPARAM wParam, LPARAM lParam) {
    GetWindowText(inputEdit_hwnd, editBuffer, sizeof(editBuffer));
    std::wstring tmp(&editBuffer[0]);
    std::string inputQuery(tmp.begin(), tmp.end());
    if (isPassword) {
        passwordOperation(this, inputQuery);
        isPassword = false;
    } else if (isRecords) {
        int position = SendMessage(list_hwnd, LB_GETCURSEL, 0, 0);
        if (listPositionToItemId->find(position) != listPositionToItemId->end()) {
            auto *record = recordSupplier->getRecordById(listPositionToItemId->at(position));

            record->manipulate(inputQuery);
            recordSupplier->saveRecord(record);
            onRecordSelected(wParam, lParam, position);
        }
    } else if (isRecordTypes) {
        int position = SendMessage(list_hwnd, LB_GETCURSEL, 0, 0);
        if (listPositionToItemId->find(position) != listPositionToItemId->end()) {
            auto *typeInfo = recordSupplier->getTypeInfoById(listPositionToItemId->at(position));
            createNewRecord(typeInfo);
        }
    }
    clearInput();
}

void MainWindowController::onRecordsShow(WPARAM wParam, LPARAM lParam) {
    auto *records = recordSupplier->getAllRecords();
    loadRecords(records);
    delete (records);
}

void MainWindowController::onNewRecord(WPARAM wParam, LPARAM lParam) {
    auto *typeInfos = recordSupplier->getAllRecordTypeInfos();
    loadRecordTypes(typeInfos);
    delete (typeInfos);
}

void MainWindowController::onRecordSelected(WPARAM wParam, LPARAM lParam, int listPosition) {
    auto *record = recordSupplier->getRecordById(listPositionToItemId->at(listPosition));
    auto info = record->getInfo();
    std::string::size_type pos = 0;
    while ((pos = info.find('\n', pos)) != std::string::npos) {
        info.insert(pos, 1, '\r');
        pos += 2;
    }
    SetWindowText(outputText_hwnd, stringToWString(info).c_str());
}

void MainWindowController::onRecordTypeSelected(WPARAM wParam, LPARAM lParam, int listPosition) {
    auto *typeInfo = recordSupplier->getTypeInfoById(listPositionToItemId->at(listPosition));
    auto info = typeInfo->getDescription();
    info.append("\n");
    info.append("\n");
    info.append(CREATE_RECORD_TEXT);
    std::string::size_type pos = 0;
    while ((pos = info.find('\n', pos)) != std::string::npos) {
        info.insert(pos, 1, '\r');
        pos += 2;
    }
    SetWindowText(outputText_hwnd, stringToWString(info).c_str());
}

void MainWindowController::onDestroy(WPARAM wParam, LPARAM lParam) {

    DeleteObject(hMonospacedFont);

}

void MainWindowController::onAbout(WPARAM wParam, LPARAM lParam) {
    std::string info(ABOUT_TEXT);
    std::string::size_type pos = 0;
    while ((pos = info.find('\n', pos)) != std::string::npos) {
        info.insert(pos, 1, '\r');
        pos += 2;
    }
    SetWindowText(outputText_hwnd, stringToWString(info).c_str());
    SendMessage(list_hwnd, LB_SETCURSEL, -1, 0);
    onListItemSelected(wParam, lParam);
}

void MainWindowController::clearOutput() {
    SetWindowText(outputText_hwnd, L"");
}

void MainWindowController::enterPassword(PasswordOperation passwordOperation) {

    this->passwordOperation = passwordOperation;
    SetWindowText(outputText_hwnd, ENTER_PASSWORD_TEXT);
    isPassword = true;
}

void MainWindowController::clearInput() {
    SetWindowText(inputEdit_hwnd, L"");
}

void MainWindowController::createNewRecord(RecordTypeInfo *typeInfo) {
    auto *record = (typeInfo->getConstructor())();
    recordSupplier->addRecord(record);
    auto* records = recordSupplier->getAllRecords();
    loadRecords(records);
    delete(records);
}

void MainWindowController::showWrongPassword(std::string password) {
//    SetWindowText(outputText_hwnd, WRONG_PASSWORD_TEXT);
    MessageBox(
            NULL,
            (LPCWSTR)WRONG_PASSWORD_TEXT,
            (LPCWSTR)L"Error occurred",
            MB_ICONERROR | MB_OK
    );

    clearOutput();
}
