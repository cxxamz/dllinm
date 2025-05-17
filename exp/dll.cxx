#include <string>

#include "dll.h"

extern "C" __declspec(dllexport) void* ABI(void* _)
{
    static auto s = std::string();
    s.append(std::string_view((char*)_));
    return &s;
}
