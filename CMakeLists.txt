cmake_minimum_required(VERSION 3.1)
project(abseil_example)
set(CMAKE_CXX_STANDARD 14)

if (MSVC)
# /wd4005  macro-redefinition
# /wd4068  unknown pragma
# /wd4244  conversion from 'type1' to 'type2'
# /wd4267  conversion from 'size_t' to 'type2'
# /wd4800  force value to bool 'true' or 'false' (performance warning)
add_compile_options(/wd4005 /wd4068 /wd4244 /wd4267 /wd4800)
add_definitions(/DNOMINMAX /DWIN32_LEAN_AND_MEAN=1 /D_CRT_SECURE_NO_WARNINGS)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wthread-safety" )
endif()

option(BUILD_TESTING "" OFF)

add_subdirectory(cctz)
add_subdirectory(abseil)

add_executable(conditional_variable_std conditional_variable_std.cpp)
add_executable(conditional_variable_absl conditional_variable_absl.cpp)
target_link_libraries(conditional_variable_absl absl::base absl::synchronization)
