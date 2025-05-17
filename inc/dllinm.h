#pragma once

#ifndef DLLINM_H
#define DLLINM_H

#include "config.h"

#ifdef DLLINM_STC
    #define DLLINM_ABI extern "C"
#else
    #ifdef _WIN64
        #define DLLINM_API_IMPORT __declspec(dllimport)
        #define DLLINM_API_EXPORT __declspec(dllexport)
    #else
        #define DLLINM_API_IMPORT
        #define DLLINM_API_EXPORT __attribute__((visibility ("default")))
    #endif
    #ifdef  DLLINM_EXP 
        #define DLLINM_ABI extern "C" DLLINM_API_EXPORT
        #define DLLINM_API extern     DLLINM_API_EXPORT
    #else
        #define DLLINM_ABI extern "C" DLLINM_API_IMPORT
        #define DLLINM_API extern     DLLINM_API_IMPORT
    #endif
#endif

DLLINM_ABI int dllinmAttach(void const* d, unsigned long long s, void** h);
DLLINM_ABI int dllinmDetach(void* h);

#endif
