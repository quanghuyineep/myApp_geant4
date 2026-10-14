cmake_minimum_required(VERSION 3.16)
project(myApp)

find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

add_executable(myApp myApp.cc)
target_link_libraries(myApp ${Geant4_LIBRARIES})

