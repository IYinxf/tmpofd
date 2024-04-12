cmake_minimum_required(VERSION 3.12)

set(TMPOFD_VERSION_MAJOR 0)
set(TMPOFD_VERSION_MINOR 1)
set(TMPOFD_VERSION_PATCH 0)
set(TMPOFD_VERSION ${TMPOFD_VERSION_MAJOR}.${TMPOFD_VERSION_MINOR}.${TMPOFD_VERSION_PATCH})
set(TMPOFD_VERSION_STRING "${TMPOFD_VERSION}")

project(tmpofd VERSION ${TMPOFD_VERSION} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

option(TMPOFD_TEST "Build ${PROJECT_NAME} test" OFF)

execute_process(
        COMMAND "git" rev-parse HEAD
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        OUTPUT_VARIABLE GIT_SHA1
        ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
)
configure_file("${PROJECT_SOURCE_DIR}/templates/version.h.in" "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/refl/version.h" @ONLY)

if (MSVC)
    add_compile_options(/utf-8)
endif ()

include_directories(${CMAKE_INSTALL_PREFIX}/include ${PROJECT_SOURCE_DIR})

add_executable(ofd_entry ${PROJECT_SOURCE_DIR}/demo/ofd_entry.cc)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)

if (PROJECT_IS_TOP_LEVEL)
    set(TMPOFD_TEST ON CACHE BOOL "Build ${PROJECT_NAME} test" FORCE)
endif()
if (TMPOFD_TEST)
    enable_testing()
    add_subdirectory(test)
endif ()
