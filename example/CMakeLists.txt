# Information cmake
cmake_minimum_required(VERSION 3.0.2)

add_executable(VMTHookExample main.cpp)
add_subdirectory( ../sources VMTHook )

target_include_directories (VMTHookExample PRIVATE 
		../
)


target_link_libraries(VMTHookExample PRIVATE "VMTHook" )