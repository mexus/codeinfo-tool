cmake_minimum_required (VERSION 3.1)
project("vk-message-loader")
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_EXTRA_FLAGS "-Wall -Wextra -Werror")
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    SET(CMAKE_CXX_EXTRA_FLAGS "${CMAKE_CXX_EXTRA_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif()
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_EXTRA_FLAGS}")

enable_testing()

include_directories(".")
add_subdirectory("clangxx")
add_subdirectory("tool")

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} "--output-on-failure")
