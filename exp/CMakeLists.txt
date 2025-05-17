
add_library(dll SHARED)
target_sources(dll PRIVATE dll.cxx)
target_compile_features(dll PRIVATE cxx_std_23 INTERFACE cxx_std_23)

add_executable(app)
target_sources(app PRIVATE app.cxx)
target_compile_features(app PRIVATE cxx_std_23 INTERFACE cxx_std_23)
target_link_libraries(app PRIVATE dllinm)
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/inc) 
target_compile_definitions(app PRIVATE DLLINM_STC)
