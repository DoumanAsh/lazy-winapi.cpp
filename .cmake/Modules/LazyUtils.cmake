# Set flags if compiler accepts GCC flags
macro(set_gcc_flags_if)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(CMAKE_CXX_FLAGS  "${CMAKE_C_FLAGS} ${ARGV0}")
    endif()
endmacro(set_gcc_flags_if)

# Set MVSC flags
macro(set_msvc_flags_if)
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set(CMAKE_CXX_FLAGS  "${CMAKE_C_FLAGS} ${ARGV0}")
    endif()
endmacro(set_msvc_flags_if)
