WNDCLASS wc = {};
wc.lpszClassName = "ITA Extractor";
wc.hIcon = LoadIcon(GetModuleHandle(NULL), "icon.ico");
RegisterClass(&wc);
