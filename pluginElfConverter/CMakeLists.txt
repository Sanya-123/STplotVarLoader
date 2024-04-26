cmake_minimum_required(VERSION 3.5)

# create plugin and app
set(PLUGIN_NAME pluginElfConverter)

project(${PLUGIN_NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Network Widgets REQUIRED)

# BEGIN PLUGIN
add_library(${PLUGIN_NAME} SHARED
	${PATH_INTERFACE}/varreaderinterface.h
        elfconverter.h elfconverter.cpp
)

# set(BUILD_SHARED_LIBS ON)
# add_subdirectory(conf2var)

target_include_directories(${PLUGIN_NAME} PRIVATE ../conf2var)

set_target_properties(${PLUGIN_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_PATH}
)

target_link_libraries(${PLUGIN_NAME} PRIVATE Qt5::Core Qt5::Network Qt5::Widgets conf2var)

if (WIN32)
    install(TARGETS ${PLUGIN_NAME} DESTINATION ${PLUGINS_PATH})
endif()

# END PLUGIN

