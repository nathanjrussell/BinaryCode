#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "BinaryCodeWord::binarycodeword" for configuration ""
set_property(TARGET BinaryCodeWord::binarycodeword APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(BinaryCodeWord::binarycodeword PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libbinarycodeword.a"
  )

list(APPEND _cmake_import_check_targets BinaryCodeWord::binarycodeword )
list(APPEND _cmake_import_check_files_for_BinaryCodeWord::binarycodeword "${_IMPORT_PREFIX}/lib/libbinarycodeword.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
