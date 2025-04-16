cmake_minimum_required(VERSION 2.8)
project(test)


set(CMAKE_BUILD_TYPE  "Debug" CACHE STRING "Choose the build type: Debug/Release/...")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-Wall -O0 -g)
        # add_definitions(-DDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-Wall -O3)
        add_definitions(-DNDEBUG)
endif()

find_package(OpenCV REQUIRED)

#设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

if(NOT WIN32)
ADD_DEFINITIONS("-std=c++0x -O3")
endif(NOT WIN32)

include_directories(src) 
FILE(GLOB_RECURSE sourcefiles "src/*.cpp")
add_executable( KCF ${sourcefiles} )
target_link_libraries( KCF ${OpenCV_LIBS})




