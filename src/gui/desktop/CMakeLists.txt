cmake_minimum_required(VERSION 3.5)

project(BrickGame VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        gamewidgetmenu.cpp
        gamewidgetmenu.h
        
        gamewidgetsnake.cpp
        gamewidgetsnake.h

        gamewidgettetris.cpp
        gamewidgettetris.h

        ../../brick_game/tetris/fsm.h
        ../../brick_game/tetris/objects.h
        ../../brick_game/tetris/tetris.h

        ../../brick_game/tetris/fsm.c
        ../../brick_game/tetris/tetris.c

        ../../brick_game/snake/model.h
        ../../brick_game/snake/controller.h
        ../../brick_game/snake/defines.h

        ../../brick_game/snake/model.cc
        ../../brick_game/snake/controller.cc
)

# Указываем язык для C-файлов
set_source_files_properties(
    ../../brick_game/tetris/fsm.c
    ../../brick_game/tetris/tetris.c
    PROPERTIES LANGUAGE C
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BrickGame
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(BrickGame SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(BrickGame
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BrickGame PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(BrickGame PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BrickGame)
endif()
