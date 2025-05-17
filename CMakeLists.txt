cmake_minimum_required(VERSION 3.30)

project(dllinm VERSION 0.0.0.0 DESCRIPTION "" LANGUAGES CXX)

set(dep ${CMAKE_SOURCE_DIR}/ext/MemoryModulePP)

file(GLOB_RECURSE inc ${dep}/MemoryModule/*.h ${dep}/3rdparty/*.h)
file(GLOB_RECURSE src ${dep}/MemoryModule/*.cpp ${dep}/3rdparty/*.cpp)

list(REMOVE_ITEM src ${dep}/3rdparty/Detours/uimports.cpp)
list(REMOVE_ITEM src ${dep}/MemoryModule/LoadDllMemoryApi.cpp)

option(DLLINM_STC "build static library" ON)

set(LIB_BUILD_TYPE STATIC)

if (NOT DLLINM_STC)
    set(LIB_BUILD_TYPE SHARED)
endif()

configure_file(${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_SOURCE_DIR}/inc/config.h)

add_library(${PROJECT_NAME} ${LIB_BUILD_TYPE})
target_sources(${PROJECT_NAME} PUBLIC inc/dllinm.h PRIVATE src/dllinm.cxx ${inc} ${src})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23 INTERFACE cxx_std_23)
target_include_directories(${PROJECT_NAME} PRIVATE inc ${dep}) 
target_compile_definitions(${PROJECT_NAME} PRIVATE _MEMORY_MODULE _HAS_AUTO_INITIALIZE)
if (DLLINM_STC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _LIB)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE DLLINM_EXP _USRDLL)
endif()

add_subdirectory(exp)
