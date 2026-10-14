cmake_minimum_required(VERSION 3.16)
project(g2)

find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

# ← Thêm dòng này:
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(g2 g2.cc)
target_link_libraries(g2 ${Geant4_LIBRARIES})

