#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "BinaryCode::binarycode" for configuration ""
set_property(TARGET BinaryCode::binarycode APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(BinaryCode::binarycode PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libbinarycode.a"
  )

list(APPEND _cmake_import_check_targets BinaryCode::binarycode )
list(APPEND _cmake_import_check_files_for_BinaryCode::binarycode "${_IMPORT_PREFIX}/lib/libbinarycode.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
