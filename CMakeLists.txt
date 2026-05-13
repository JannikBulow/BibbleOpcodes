cmake_minimum_required(VERSION 3.26)
project(BibbleOpcodes CXX)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES src/opcodes.cpp include/Bibble/opcodes.h)

add_library(BibbleOpcodes STATIC src/opcodes.cpp include/Bibble/opcodes.h)

target_include_directories(BibbleOpcodes PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(BibbleOpcodes PUBLIC cxx_std_20)