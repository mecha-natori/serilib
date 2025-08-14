# serilib CMake config

cmake_minimum_required(VERSION 3.20.3)
cmake_policy(
    SET
    CMP0076
    NEW
)

project(serilib VERSION 0.1.0)
enable_language(C)

option(
    USE_SHARED
    "共有ライブラリを生成する"
    OFF
)
set(PRIMARY_FP_TYPE
    "float"
    CACHE STRING "構造体内部で使用される浮動小数点数の型"
)
set_property(
    CACHE PRIMARY_FP_TYPE
    PROPERTY
        STRINGS
        "float"
        "double"
        "long double"
)

if(USE_SHARED)
    add_library(seri SHARED)
else()
    add_library(seri STATIC)
endif()
target_compile_features(seri PUBLIC c_std_11)
target_include_directories(seri PUBLIC include)
target_compile_definitions(seri PUBLIC SL_FP_T=${PRIMARY_FP_TYPE})
add_subdirectory(src)
