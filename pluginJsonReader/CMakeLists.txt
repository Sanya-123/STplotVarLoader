cmake_minimum_required(VERSION 3.5)

# create plugin and app
set(PLUGIN_NAME pluginJsonReader)

project(${PLUGIN_NAME} LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

# BEGIN PLUGIN
add_library(${PLUGIN_NAME} SHARED
    ${PATH_INTERFACE}/varreaderinterface.h
    jsonreader.h jsonreader.cpp
    json2var/json2var.h json2var/json2var.c
    json2var/varcommon/varcommon.c
    json2var/varcommon/varcommon.h
)

# set(BUILD_SHARED_LIBS ON)
set(ENABLE_CJSON_TEST OFF)
add_subdirectory(json2var/cJSON)

target_link_libraries(${PLUGIN_NAME} PRIVATE cjson Qt5::Core)

target_include_directories(${PLUGIN_NAME} PRIVATE json2var json2var/cJSON)

set_target_properties(${PLUGIN_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_PATH}
)

if (WIN32)
    install(TARGETS ${PLUGIN_NAME} DESTINATION ${PLUGINS_PATH})
endif()

# END PLUGIN

