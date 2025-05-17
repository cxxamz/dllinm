### dllinm: dynamic link library inside memory
------------------

load library from memory

> dll.h

```C
extern "C" __declspec(dllexport) void* ABI(void*);
```

> dll.cxx

```CXX
#include <string>

#include "dll.h"

extern "C" __declspec(dllexport) void* ABI(void* _)
{
    static auto s = std::string();
    s.append(std::string_view((char*)_));
    return &s;
}
```

> app.cxx

```C
#include <print>
#include <string>
#include <fstream>
#include <filesystem>
#include <Windows.h>

#include "dll.h"
#include "dllinm.h"

auto main(int argc, char** argv) -> int
{
    auto h = (void*)0;
    if (auto f = std::ifstream(std::filesystem::absolute(argv[0]).parent_path() / "dll.dll", std::ios::ate | std::ios::binary); f.is_open())
    {
        auto s = std::string(f.tellg(), '\0');
        f.seekg(0);
        f.read(s.data(), s.size());
        dllinmAttach(s.data(), s.size(), &h);
    }
    if (!h) return -1;

    auto pfn = (decltype(ABI)*)GetProcAddress((HMODULE)h, "ABI");

    auto str = (std::string*)pfn((void*)"");

    std::println("{}", *(std::string const*)pfn((void*)"A")); // print: A
    std::println("{}", *(std::string const*)pfn((void*)"B")); // print: AB
    (*str) = "C";
    std::println("{}", *(std::string const*)pfn((void*)"D")); // print: CD
    std::println("{}", *(std::string const*)pfn((void*)"E")); // print: CDE

    dllinmDetach(h);
}
```
