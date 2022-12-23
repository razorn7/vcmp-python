#pragma once
#ifndef __MAIN_H
#define __MAIN_H

#include <cstdio>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <pybind11/operators.h>

#include "vcmp_wrapper/classes/utility/utility.h"
#include "vcmp_wrapper/sdk/vcmp.h"
#include "vcmp_wrapper/sdk/vcmp_constants.h"

extern PluginFuncs* functions;
extern bool can_load;

#ifdef _WIN32
#include "Windows.h"

#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#define MAX_PATH 250
#endif

#ifdef __cplusplus
extern "C" {
#endif
    DLL_EXPORT    unsigned int            VcmpPluginInit(PluginFuncs* pluginFuncs, PluginCallbacks* pluginCalls, PluginInfo* pluginInfo); // This is a blank function and it's exported (check the #define tags above). VCMP requires it
#ifdef __cplusplus
}
#endif

#endif