#pragma once

#include "pluginmain.h"



//plugin data
#define PLUGIN_NAME "qt5_resolver"
#define PLUGIN_VERSION 2

//functions
bool pluginInit(PLUG_INITSTRUCT* initStruct);
bool pluginStop();
void pluginSetup();

static bool cbCommand(int argc, char* argv[]);