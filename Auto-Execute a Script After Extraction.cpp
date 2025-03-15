void runPostExtractionScript(const std::string& outputDir) {
    std::string scriptPath = outputDir + "\\setup.bat";
    
    if (std::ifstream(scriptPath)) {
        ShellExecuteA(NULL, "open", scriptPath.c_str(), NULL, NULL, SW_SHOW);
    } else {
        MessageBoxA(NULL, "No setup script found.", "Info", MB_OK);
    }
}
