# serilib CMake config

cmake_minimum_required(VERSION 3.20.3)
cmake_policy(
    SET
    CMP0076
    NEW
)

# Project Settings

project(serilib VERSION 0.1.0)
enable_language(C)
include(GNUInstallDirs)

# Build Options

option(
    SERI_USE_SHARED
    "共有ライブラリを生成する"
    OFF
)
set(SERI_PRIMARY_FP_TYPE
    "float"
    CACHE STRING "構造体内部で使用される浮動小数点数の型"
)
set_property(
    CACHE SERI_PRIMARY_FP_TYPE
    PROPERTY
        STRINGS
        "float"
        "double"
        "long double"
)

# Targets

if(SERI_USE_SHARED)
    add_library(seri SHARED)
    set_target_properties(
        seri PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR} VERSION
                                                           ${PROJECT_VERSION}
    )
else()
    add_library(seri STATIC)
endif()
target_compile_features(seri PUBLIC c_std_11)
target_include_directories(seri PUBLIC include)
target_compile_definitions(seri PUBLIC SL_FP_T=${SERI_PRIMARY_FP_TYPE})
add_subdirectory(src)
target_sources(seri PRIVATE ${srcs})

# Installs

install(
    TARGETS seri
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING
    PATTERN "*.h"
)
