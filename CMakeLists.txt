cmake_minimum_required(VERSION 3.15)
project(tuQ)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(CURL REQUIRED)
find_package(Qt5 COMPONENTS
      Core
      Gui
      Widgets REQUIRED)

add_executable(tuQ src/main.cpp
      src/gui/gui_helpers.cpp
      src/gui/mainwindow.cpp
      src/gui/mode_compiler/compilerview.cpp
      src/gui/mode_modeller/graphedge.cpp
      src/gui/mode_modeller/graphvertex.cpp
      src/gui/mode_modeller/graphview.cpp
      src/gui/mode_modeller/modeller_helpers.cpp
      src/gui/mode_simulator/algorithmlattice.cpp
      src/gui/mode_simulator/operatorpalette.cpp
      src/gui/mode_simulator/signmeasure.cpp
      src/gui/mode_simulator/simulator_helpers.cpp
      src/gui/mode_simulator/simulatorview.cpp
      src/layout/gates_lattice_set.cpp
      src/layout/io_circuit.cpp
)

target_include_directories(tuQ PRIVATE src/layout/)

target_link_libraries(tuQ CURL::libcurl)
target_link_libraries(tuQ
      Qt5::Core
      Qt5::Gui
      Qt5::Widgets
)
