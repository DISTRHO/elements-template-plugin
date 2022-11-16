# DISTRHO Plugin Framework (DPF)
# Copyright (C) 2022 Filipe Coelho <falktx@falktx.com>
# SPDX-License-Identifier: ISC

cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)

set(NAME elements-demo-plugin)
project(${NAME})

add_subdirectory(dpf)

dpf_add_plugin(${NAME}
  TARGETS clap lv2 vst2 vst3 jack
  UI_TYPE cairo
  NO_SHARED_RESOURCES
  FILES_DSP
      src/PluginDSP.cpp
  FILES_UI
      src/PluginUI.cpp
      dpf-widgets/cairo/Elements.cpp)

target_include_directories(${NAME} PUBLIC src)
target_include_directories(${NAME} PUBLIC dpf-widgets/cairo)
target_include_directories(${NAME} PUBLIC dpf-widgets/generic)

# fontconfig and freetype are required by the elements library, handle them here
find_package(PkgConfig)
pkg_check_modules(FONTCONFIG "fontconfig" REQUIRED)
pkg_check_modules(FREETYPE2 "freetype2" REQUIRED)
target_include_directories(${NAME} PRIVATE ${FONTCONFIG_INCLUDE_DIRS})
target_include_directories(${NAME} PRIVATE ${FREETYPE2_INCLUDE_DIRS})
target_link_directories(${NAME} PRIVATE ${FONTCONFIG_LIBRARY_DIRS})
target_link_directories(${NAME} PRIVATE ${FREETYPE2_LIBRARY_DIRS})
target_link_libraries(${NAME} PRIVATE ${FONTCONFIG_LIBRARIES})
target_link_libraries(${NAME} PRIVATE ${FREETYPE2_LIBRARIES})
