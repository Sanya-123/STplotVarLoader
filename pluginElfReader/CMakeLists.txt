cmake_minimum_required(VERSION 3.5)

# create plugin and app
set(PLUGIN_NAME pluginElfReader)

project(${PLUGIN_NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Network REQUIRED)

# BEGIN PLUGIN
if (WIN32)
    add_library(${PLUGIN_NAME} SHARED
        ${PATH_INTERFACE}/varreaderinterface.h
        elfreader.h elfreader.cpp
    )
else()
    set(BUILD_SHARED_LIBS ON)
    add_subdirectory(elf2var/dwarves)
    add_library(${PLUGIN_NAME} SHARED
        ${PATH_INTERFACE}/varreaderinterface.h
        elfreader.h elfreader.cpp
        elf2var/elf2var.h
        elf2var/elf2var.c
        elf2var/varcommon/varcommon.c
        elf2var/varcommon/varcommon.h
    )
endif()

target_include_directories(${PLUGIN_NAME} PRIVATE elf2var/dwarves elf2var)
if (UNIX)
    target_link_libraries(${PLUGIN_NAME} PRIVATE dwarves )
endif()

set_target_properties(${PLUGIN_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_PATH}
)

target_link_libraries(${PLUGIN_NAME} PRIVATE Qt5::Core Qt5::Network)

if (WIN32)
    install(TARGETS ${PLUGIN_NAME} DESTINATION ${PLUGINS_PATH})
endif()

# END PLUGIN

