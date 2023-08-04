# Information cmake
cmake_minimum_required(VERSION 3.0.2)

add_library( VMTHook SHARED VMThook.cpp)

target_include_directories (VMTHook PRIVATE 
		../include/
)

file(GLOB_RECURSE SOURCES
        *.cpp
)

target_sources(VMTHook PRIVATE 
		${SOURCES}
)

