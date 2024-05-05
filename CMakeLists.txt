cmake_minimum_required(VERSION 3.5)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(BUILD_SHARED_LIBS ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
link_libraries(Qt5::Widgets)

macro(subdirlist result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            list(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()

subdirlist(SUBDIRS ${CMAKE_CURRENT_LIST_DIR})

#example exclude from list: list(REMOVE_ITEM SUBDIRS pluginTemplate)
if(UNIX)
    list(REMOVE_ITEM SUBDIRS pluginElfConverter)
endif()

foreach(subdir ${SUBDIRS})
    add_subdirectory(${subdir})
endforeach()
