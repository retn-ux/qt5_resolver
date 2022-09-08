#include "plugin.h"

static std::wstring Utf8ToUtf16(const std::string & str)
{
    std::wstring convertedString;
    int requiredSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    if(requiredSize > 0)
    {
        std::vector<wchar_t> buffer(requiredSize);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &buffer[0], requiredSize);
        convertedString.assign(buffer.begin(), buffer.end() - 1);
    }
    return convertedString;
}

static bool ReadAllData(const std::string & fileName, std::vector<uint8_t> & content)
{
    auto hFile = CreateFileW(Utf8ToUtf16(fileName).c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
    auto result = false;
    if(hFile != INVALID_HANDLE_VALUE)
    {
        unsigned int filesize = GetFileSize(hFile, nullptr);
        if(!filesize)
        {
            content.clear();
            result = true;
        }
        else
        {
            content.resize(filesize);
            DWORD read = 0;
            result = !!ReadFile(hFile, content.data(), filesize, &read, nullptr);
        }
        CloseHandle(hFile);
    }
    return result;
}



//Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
    if(!_plugin_registercommand(pluginHandle, PLUGIN_NAME, cbCommand, false))
        _plugin_logputs("[" PLUGIN_NAME "] Error registering the \"" PLUGIN_NAME "\" command!");
    return true; //Return false to cancel loading the plugin.
}

//Deinitialize your plugin data here (clearing menus optional).
bool pluginStop()
{
    return true;
}

//Do GUI/Menu related things here.
void pluginSetup()
{
}


bool cbCommand(int argc, char* argv[])
{
    LogPrintf("success");
    return true;
}