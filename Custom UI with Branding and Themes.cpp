case WM_CREATE: {
    HBITMAP hLogo = (HBITMAP)LoadImage(GetModuleHandle(NULL), "logo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HWND hLogoWnd = CreateWindow("STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 50, 10, 200, 100, hwnd, NULL, GetModuleHandle(NULL), NULL);
    SendMessage(hLogoWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hLogo);

    HWND hText = CreateWindow("STATIC", "Welcome to ITA Extractor", WS_CHILD | WS_VISIBLE, 50, 120, 300, 20, hwnd, NULL, GetModuleHandle(NULL), NULL);
    SendMessage(hText, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
    
    CreateWindow("BUTTON", "Extract", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 150, 100, 30, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
    break;
}
