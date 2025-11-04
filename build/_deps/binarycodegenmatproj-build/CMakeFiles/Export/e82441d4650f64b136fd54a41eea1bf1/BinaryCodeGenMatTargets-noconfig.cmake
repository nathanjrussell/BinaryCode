#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "BinaryCodeGenMat::binarycodegenmat" for configuration ""
set_property(TARGET BinaryCodeGenMat::binarycodegenmat APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(BinaryCodeGenMat::binarycodegenmat PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libbinarycodegenmat.a"
  )

list(APPEND _cmake_import_check_targets BinaryCodeGenMat::binarycodegenmat )
list(APPEND _cmake_import_check_files_for_BinaryCodeGenMat::binarycodegenmat "${_IMPORT_PREFIX}/lib/libbinarycodegenmat.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
