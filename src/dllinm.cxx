
extern "C"
{
    #include "MemoryModule/LoadDllMemoryApi.cpp"
}

#include "dllinm.h"
#include "MemoryModule/LoadDllMemoryApi.h"

DLLINM_ABI int dllinmAttach(void const* d, unsigned long long s, void** h)
{
    if (auto t = LoadLibraryMemoryExW(const_cast<void*>(d), {}, {}, {}, {})) {
        if (h) (*h) = (void*)t; return {};
    } else return (int)GetLastError();
}

DLLINM_ABI int dllinmDetach(void* h)
{
    return (int)FreeLibraryMemory((HMEMORYMODULE)h);
}
