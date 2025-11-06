
# Overrideable from command line
set(BINARY_CODE_GEN_MAT_GIT_URL "https://github.com/nathanjrussell/BinaryCodeGenMatrix.git" CACHE STRING "Git URL for BinaryCodeGenMat")
set(BINARY_CODE_GEN_MAT_FETCH_TAG "2.14.0" CACHE STRING "Tag/commit to fetch for BinaryCodeGenMat")

# Try installed package first (quiet)
find_package(BinaryCodeGenMatrix ${BINARY_CODE_GEN_MAT_FETCH_TAG} QUIET)

# If the imported target is not available, fetch the project
if(NOT TARGET BinaryCodeGenMat::binarycodegenmat)
    include(FetchContent)
    message(STATUS "BinaryCodeGenMat not found; fetching ${BINARY_CODE_GEN_MAT_GIT_URL}@${BINARY_CODE_GEN_MAT_FETCH_TAG}")
    FetchContent_Declare(
            BinaryCodeGenMatProj
            GIT_REPOSITORY ${BINARY_CODE_GEN_MAT_GIT_URL}
            GIT_TAG        ${BINARY_CODE_GEN_MAT_FETCH_TAG}
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(BinaryCodeGenMatProj)
endif()

# Final verification
if(NOT TARGET BinaryCodeGenMat::binarycodegenmat)
    message(FATAL_ERROR
            "Required target `BinaryCodeGenMat::binarycodegenmat` not found.\n"
            "Either install BinaryCodeGenMat (so find_package() succeeds)\n"
            "or make sure the fetched/subproject creates the imported target BinaryCodeGenMat::binarycodegenmat.")
endif()