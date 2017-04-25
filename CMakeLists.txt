project(lazy_winapi CXX)

cmake_minimum_required(VERSION 3.0)

set(MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.cmake/Modules")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${MODULE_DIR})
include(LazyUtils)

include_directories("include/")

set_msvc_flags_if("/W4")
set_gcc_flags_if("-Wall -Wextra")
# For MinGW we assume that minimum runtime is Vista
set_gcc_flags_if("-D_WIN32_WINNT=0x0600")

file(GLOB lazy_winapi_SRC "src/*.cpp")

option(BUILD_SHARED "Build shared library" OFF)

if(BUILD_SHARED)
    add_library(lazy_winapi SHARED ${lazy_winapi_SRC})
else()
    add_library(lazy_winapi STATIC ${lazy_winapi_SRC})
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

###########################
# cppcheck
##########################
add_custom_target(
    cppcheck
    COMMAND cppcheck
    --enable=all
    --suppress=unusedFunction:*:*
    ${lazy_winapi_SRC}
)

############
# Tests
############
option(UNIT_TEST "Build unit tests" OFF)
if (UNIT_TEST)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    include(DownloadProject)
    download_project(
        PROJ googletest
        URL  https://github.com/google/googletest/archive/release-1.8.0.zip
    )

    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

    file(GLOB test_SRC "test/*.cpp")
    add_executable(utest "${test_SRC}")
    target_link_libraries(utest gtest gtest_main lazy_winapi)
endif()
