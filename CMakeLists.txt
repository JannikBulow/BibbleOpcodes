cmake_minimum_required(VERSION 3.26)
project(BibbleOpcodes VERSION 1.0.0 LANGUAGES CXX)

include(CMakePackageConfigHelpers)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES src/opcodes.cpp include/Bibble/opcodes.h)

add_library(BibbleOpcodes STATIC src/opcodes.cpp include/Bibble/opcodes.h)

target_include_directories(BibbleOpcodes PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include
    $<INSTALL_INTERFACE:include>
)

target_compile_features(BibbleOpcodes PUBLIC cxx_std_20)

set_target_properties(BibbleOpcodes PROPERTIES
    EXPORT_NAME Opcodes
    OUTPUT_NAME "bibble-opcodes"
    VERSION 1.0.0
)

configure_package_config_file(
    cmake/BibbleOpcodesConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/BibbleOpcodesConfig.cmake
    INSTALL_DESTINATION lib/cmake/BibbleOpcodes
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/BibbleOpcodesConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    TARGETS BibbleOpcodes
    EXPORT BibbleOpcodesTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
)

install(
    EXPORT BibbleOpcodesTargets
    FILE BibbleOpcodesTargets.cmake
    NAMESPACE Bibble::
    DESTINATION lib/cmake/BibbleOpcodes
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/BibbleOpcodesConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/BibbleOpcodesConfigVersion.cmake
    DESTINATION lib/cmake/BibbleOpcodes
)