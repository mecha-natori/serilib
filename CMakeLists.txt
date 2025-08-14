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

# Common Parameters

set(compile_definitions SL_FP_T=${SERI_PRIMARY_FP_TYPE})
set(compile_features c_std_11)
set(include_dirs include)

# Targets

add_library(seri STATIC)
target_compile_features(seri PUBLIC ${compile_features})
target_include_directories(seri PUBLIC ${include_dirs})
target_compile_definitions(seri PUBLIC ${compile_definitions})
if(SERI_USE_SHARED)
    add_library(seri_shared SHARED)
    set_target_properties(
        seri_shared
        PROPERTIES
            OUTPUT_NAME seri
            SOVERSION ${PROJECT_VERSION_MAJOR}
            VERSION ${PROJECT_VERSION}
    )
    target_compile_features(seri_shared PUBLIC ${compile_features})
    target_include_directories(seri_shared PUBLIC ${include_dirs})
    target_compile_definitions(seri_shared PUBLIC ${compile_definitions})
endif()
add_subdirectory(src)
target_sources(seri PRIVATE ${srcs})
if(SERI_USE_SHARED)
    target_sources(seri_shared PRIVATE ${srcs})
endif()

# Installs

install(TARGETS seri ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING
    PATTERN "*.h"
)
if(SERI_USE_SHARED)
    install(
        TARGETS seri_shared
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()
