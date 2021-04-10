#pragma once

#include "pluginmain.h"
#include "DpMain.h"
#include <Cmd.h>
#include <Auxiliary.h>
#include <SREProc.h>
//plugin data
#define PLUGIN_NAME "qt5_resolver"
#define PLUGIN_VERSION 1
#define COMMAND_NAME PLUGIN_NAME

#define Print _plugin_logprintf
//functions
bool pluginInit(PLUG_INITSTRUCT* initStruct);
void pluginStop();
void pluginSetup();
bool cbQtResolver(int argc, char** argv);
bool DeleteSubString(string str, string sub);