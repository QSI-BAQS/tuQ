cmake_minimum_required(VERSION 3.15)
project(tuQ)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "/usr/lib64/qt5/")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(tuQ src/main.cpp
        src/gui/graphedge.cpp
        src/gui/graphvertex.cpp
        src/gui/graphview.cpp
        src/gui/mainwindow.cpp
        src/layout/gates_lattice_set.cpp
        src/layout/io_circuit.cpp
)

target_link_libraries(tuQ
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

