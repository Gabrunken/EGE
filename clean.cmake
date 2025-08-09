cmake_minimum_required(VERSION 3.16)

# Nome della cartella da cancellare
set(BUILD_DIR "${CMAKE_SOURCE_DIR}/build")

message(STATUS "Checking for directory: ${BUILD_DIR}")

if(EXISTS "${BUILD_DIR}")
    message(STATUS "Removing: ${BUILD_DIR}")
    file(REMOVE_RECURSE "${BUILD_DIR}")
    message(STATUS "Done.")
else()
    message(STATUS "Directory not found. Nothing to do.")
endif()
