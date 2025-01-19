cmake_minimum_required(VERSION 3.16)
project(equation VERSION 1.0.0 LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)
qt_standard_project_setup()

add_executable(equation
    main.cpp
    widget.hpp
    widget.cpp
)

target_link_libraries(equation PRIVATE Qt6::Widgets Qt6::Charts)