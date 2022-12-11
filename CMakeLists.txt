# DISTRHO Plugin Framework (DPF)
# Copyright (C) 2022 Filipe Coelho <falktx@falktx.com>
# SPDX-License-Identifier: ISC

cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

# if (APPLE)
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -UMAC_OS_X_VERSION_MAX_ALLOWED -DMAC_OS_X_VERSION_MAX_ALLOWED=MAC_OS_X_VERSION_10_15")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -UMAC_OS_X_VERSION_MIN_REQUIRED -DMAC_OS_X_VERSION_MIN_REQUIRED=MAC_OS_X_VERSION_10_15")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=10.15 -stdlib=libc++")
# endif ()

set(NAME elements-demo-plugin)
project(${NAME})

add_subdirectory(dpf)

dpf_add_plugin("${NAME}"
  TARGETS clap lv2 vst2 vst3 jack
  UI_TYPE cairo
  NO_SHARED_RESOURCES
  FILES_DSP
      src/PluginDSP.cpp
  FILES_UI
      src/PluginUI.cpp
      dpf-widgets/cairo/Elements.cpp)

target_include_directories("${NAME}" PUBLIC src)
target_include_directories("${NAME}" PUBLIC dpf-widgets/cairo)
target_include_directories("${NAME}" PUBLIC dpf-widgets/generic)

# the elements library requires fontconfig, freetype and threads
find_package(PkgConfig)
find_package(Threads)
pkg_check_modules(FONTCONFIG "fontconfig" REQUIRED)
pkg_check_modules(FREETYPE2 "freetype2" REQUIRED)
target_include_directories("${NAME}" PUBLIC ${FONTCONFIG_INCLUDE_DIRS} ${FREETYPE2_INCLUDE_DIRS})
target_link_directories("${NAME}" PUBLIC ${FONTCONFIG_LIBRARY_DIRS} ${FREETYPE2_LIBRARY_DIRS})
target_link_libraries("${NAME}" PRIVATE ${CMAKE_THREAD_LIBS_INIT} ${FONTCONFIG_LIBRARIES} ${FREETYPE2_LIBRARIES})

# fix build with old mingw
if (WIN32)
target_include_directories("${NAME}" PUBLIC mingw-compat)
target_include_directories("${NAME}" PUBLIC mingw-compat/mingw-std-threads)
endif ()
