cmake_minimum_required(VERSION 3.10)

if(NOT CMAKE_VERSION VERSION_LESS 3.0)
    cmake_policy(SET CMP0048 NEW)
endif()

project(Rlib VERSION 0.0.1 DESCRIPTION "Rlib is a library for real time robotics applications")

# Find requirements
if(NOT fastcdr_FOUND)
    find_package(fastcdr REQUIRED)
endif()

if(NOT fastrtps_FOUND)
    find_package(fastrtps REQUIRED)
endif()

set(WARNING_FLAGS ON)

# Set C++11
include(CheckCXXCompilerFlag)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG OR
        CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    check_cxx_compiler_flag(-std=c++11 SUPPORTS_CXX11)
    if(SUPPORTS_CXX11)
        add_compile_options(-std=c++11)
    else()
        message(FATAL_ERROR "Compiler doesn't support C++11")
    endif()
endif()

###################
# INCLUDE AND SRC #
###################
set(RLIB_SRC
    ${CMAKE_CURRENT_LIST_DIR}/src/Publisher.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Subscriber.cpp
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
#===============================================================================


# Compile as a library
add_library(Rlib ${RLIB_SRC})

set_target_properties(Rlib PROPERTIES VERSION ${PROJECT_VERSION})

target_link_libraries(Rlib fastrtps fastcdr)
