cmake_minimum_required(VERSION 3.26)
project(BibbleOpcodes CXX)

add_library(BibbleOpcodes INTERFACE)

target_include_directories(BibbleOpcodes INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)