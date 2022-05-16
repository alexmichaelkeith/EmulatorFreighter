cmake_minimum_required(VERSION 3.5)

project(EmulatorFreighter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Python libraries
find_package(PythonLibs 3.10 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

set(PROJECT_SOURCES

    EmulatorFreighter.h
    mainwindow.h
    settings.h

    main.cpp
    mainwindow.cpp
    settings.cpp

    mainwindow.ui
    settings.ui

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(EmulatorFreighter
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET EmulatorFreighter APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(EmulatorFreighter SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(EmulatorFreighter
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Command to copy target file into build USE FOR ICON AND OTHER IMAGES
add_custom_command(
        TARGET EmulatorFreighter PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/scrapeIGDB.py
                ${CMAKE_CURRENT_BINARY_DIR}/scrapeIGDB.py)

target_link_libraries(EmulatorFreighter PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(EmulatorFreighter PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(EmulatorFreighter)
endif()
