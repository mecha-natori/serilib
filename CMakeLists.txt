cmake_minimum_required(VERSION 3.20.3)
cmake_policy(SET CMP0076 NEW)

project(serilib VERSION 0.1.0)
enable_language(C)

add_library(seri STATIC)
target_compile_features(seri PUBLIC c_std_17)
target_include_directories(seri PUBLIC include)
add_subdirectory(src)
