cmake_minimum_required(VERSION 3.16)
project(BinaryCode VERSION 1.0.0 LANGUAGES CXX)

find_package(BinaryCodeGenMatrix 1.2.0 QUIET)
find_package(BinaryCodeWord 2.0.2 QUIET)


include(FetchContent)
if(NOT BinaryCodeWord_FOUND)
  set(BINARY_CODE_WORD_GIT_URL "https://github.com/nathanjrussell/BinaryCodeWord.git")
  set(BINARY_CODE_WORD_VERSION "2.0.2")
  message(STATUS "BinaryCodeWord not found; fetching from ${BINARY_CODE_WORD_GIT_URL} ${BINARY_CODE_WORD_VERSION}")
  FetchContent_Declare(
    BinaryCodeWordProj
    GIT_REPOSITORY ${BINARY_CODE_WORD_GIT_URL}
    GIT_TAG        ${BINARY_CODE_WORD_VERSION}
  )
  FetchContent_MakeAvailable(BinaryCodeWordProj)
endif()
if(NOT BinaryCodeGenMat_FOUND)
  set(BINARY_CODE_GEN_MAT_GIT_URL "https://github.com/nathanjrussell/BinaryCodeGenMatrix.git")
  set(BINARY_CODE_GEN_MAT_VERSION "1.2.0")
  message(STATUS "BinaryCodeGenMat not found; fetching from ${BINARY_CODE_GEN_MAT_GIT_URL} tag ${BINARY_CODE_GEN_MAT_VERSION}")
  FetchContent_Declare(
    BinaryCodeGenMatProj
    GIT_REPOSITORY ${BINARY_CODE_GEN_MAT_GIT_URL}
    GIT_TAG        ${BINARY_CODE_GEN_MAT_VERSION}
  )
  FetchContent_MakeAvailable(BinaryCodeGenMatProj)
endif()

add_library(binarycode src/BinaryCode.cpp)
add_library(BinaryCode::binarycode ALIAS binarycode)
target_compile_features(binarycode PUBLIC cxx_std_17)
target_include_directories(binarycode
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_link_libraries(binarycode
  PUBLIC
    BinaryCodeGenMat::binarycodegenmat
    BinaryCodeWord::binarycodeword)

add_executable(bc_basic_usage examples/bc_basic_usage.cpp)
target_link_libraries(bc_basic_usage PRIVATE BinaryCode::binarycode)
target_compile_features(bc_basic_usage PRIVATE cxx_std_17)

include(CTest)
option(BINARYCODE_BUILD_TESTS "Build unit tests" ON)
if(BINARYCODE_BUILD_TESTS AND BUILD_TESTING)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  add_executable(test_BinaryCode tests/test_BinaryCode.cpp)
  target_link_libraries(test_BinaryCode PRIVATE BinaryCode::binarycode GTest::gtest_main)
  target_compile_features(test_BinaryCode PRIVATE cxx_std_17)
  include(GoogleTest)
  gtest_discover_tests(test_BinaryCode)
endif()

include(CMakePackageConfigHelpers)
set(INSTALL_CONFIGDIR lib/cmake/BinaryCode)
install(TARGETS binarycode
  EXPORT BinaryCodeTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)
install(EXPORT BinaryCodeTargets
  FILE BinaryCodeTargets.cmake
  NAMESPACE BinaryCode::
  DESTINATION ${INSTALL_CONFIGDIR})
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/BinaryCodeConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/BinaryCodeConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/BinaryCodeConfig.cmake"
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR})
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/BinaryCodeConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/BinaryCodeConfigVersion.cmake"
  DESTINATION ${INSTALL_CONFIGDIR})
