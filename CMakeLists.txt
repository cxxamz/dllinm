cmake_minimum_required(VERSION 3.30)

project(dllinm VERSION 0.0.0.0 DESCRIPTION "" LANGUAGES CXX)

set(dep ${CMAKE_SOURCE_DIR}/ext/MemoryModulePP)

file(GLOB_RECURSE inc ${dep}/MemoryModule/*.h ${dep}/3rdparty/*.h)
file(GLOB_RECURSE src ${dep}/MemoryModule/*.cpp ${dep}/3rdparty/*.cpp)

list(REMOVE_ITEM src ${dep}/3rdparty/Detours/uimports.cpp)
list(REMOVE_ITEM src ${dep}/MemoryModule/LoadDllMemoryApi.cpp)

add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PUBLIC dllinm.h PRIVATE dllinm.cxx ${inc} ${src})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23 INTERFACE cxx_std_23)
target_include_directories(${PROJECT_NAME} PRIVATE ${dep}) 
target_compile_definitions(${PROJECT_NAME} PRIVATE DLLINM_EXP)
