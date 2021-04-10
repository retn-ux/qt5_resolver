#include "pch.h"
#include "plugin.h"
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;


bool DeleteSubString(string str, string sub) {
    size_t pos = str.find(sub);
    if (pos == string::npos) {
        return false;
    }
    str.erase(pos, pos + sub.size() - 1);
    return true;
}

//Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
    if (!_plugin_registercommand(pluginHandle, COMMAND_NAME, cbQtResolver, true)) {
        _plugin_logprintf(COMMAND_NAME" plugin registration faild");
        return false;
    }
    Print(COMMAND_NAME" plugin registration Success");
    return true; //Return false to cancel loading the plugin.
}

//Deinitialize your plugin data here.
void pluginStop()
{
}

//Do GUI/Menu related things here.
void pluginSetup()
{
}


void Usage() {
    Print("\n");
    Print("qt_resolver usage:\n");
    Print("-h,--help     help info.\n");
    Print("-n            hook the connect function to get all the signals and slots.\n");
    Print("-d            gets the signal and slot of the object,object address is Hex.\n");
    Print("\n");
}



bool cbQtResolver(int argc, char** argv) {
    using namespace Script::Module;
    using std::stringstream;
    using std::hex;
    vector<string> opts = { "-h","--help","-d","-n","-m" };
    Print("*************************qt5_resolver start**************************\n");
    vector<string> arglist = split(argv[0], " ");
    map<string, vector<string>> args = GetArgs(arglist, opts);
    if (args.size()==0||args.find("-h") != args.end() || args.find("--help") != args.end()) {
        Usage();
        Print("**************************qt5_resolver end*************************\n");
        return true;
    }
    if (DbgIsRunning()) {
        Print("Please pause the debugger first!\n");
        return false;
    }
    ModuleInfo mi;
    GUARD_GENTLE(GetMainModuleInfo(&mi), false);
    PIDB info = OpenProcessByName(StrWStr(mi.path),PROCESS_ALL_ACCESS);

    if (args.find("-d") != args.end()) {
        vector<string> param = args["-d"];
        Gauge addr = stog(param[0]);
        vector<ElaborateData> data = DpObjMain(info.hProc, addr);
        for (auto& i : data) {
            PrintInfo(i);
            Print("\n");
        }
    }
    if (args.find("-m") != args.end()) {

    }

    Print("*************************qt5_resolver end**************************\n");
    return true;

}



 