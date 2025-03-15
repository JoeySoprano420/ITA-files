#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#include <iostream>
#include <fstream>

void extractITA(const std::string& exePath, const std::string& outputDir) {
    std::ifstream exeFile(exePath, std::ios::binary);
    if (!exeFile) {
        MessageBoxA(NULL, "Failed to open the executable!", "Error", MB_ICONERROR);
        return;
    }

    exeFile.seekg(-8, std::ios::end);
    uint64_t itaSize;
    exeFile.read(reinterpret_cast<char*>(&itaSize), sizeof(uint64_t));

    exeFile.seekg(-8 - itaSize, std::ios::end);
    std::vector<uint8_t> itaData(itaSize);
    exeFile.read(reinterpret_cast<char*>(itaData.data()), itaSize);

    std::ofstream itaFile(outputDir + "\\extracted.ita", std::ios::binary);
    itaFile.write(reinterpret_cast<char*>(itaData.data()), itaSize);

    MessageBoxA(NULL, "Extraction Completed!", "Success", MB_OK);
}

std::string selectFolder(HWND hwnd) {
    BROWSEINFO bi = {0};
    bi.lpszTitle = "Select an extraction folder";
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    char path[MAX_PATH];
    
    if (pidl && SHGetPathFromIDList(pidl, path)) {
        return std::string(path);
    }
    return "";
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {  // Extract button
                std::string folder = selectFolder(hwnd);
                if (!folder.empty()) {
                    char exePath[MAX_PATH];
                    GetModuleFileNameA(NULL, exePath, MAX_PATH);
                    extractITA(exePath, folder);
                }
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "ITA SFX Window";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    
    RegisterClass(&wc);
    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "ITA Self-Extractor", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 200, NULL, NULL, hInstance, NULL);
    
    HWND button = CreateWindow("BUTTON", "Extract", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 150, 50, 100, 30, hwnd, (HMENU)1, hInstance, NULL);
    
    ShowWindow(hwnd, nCmdShow);
    MSG msg = {};
    
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}
