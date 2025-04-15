cmake_minimum_required(VERSION 3.10)

project(kcf)

#cmake 选项设置
#设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../out")

# 设置构建类型为Debug
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-fPIC -O0 -g -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -O2 -Wall")



find_package(OpenCV 4 REQUIRED)
message(STATUS "\n[FindLibrary]  ---------OpenCV library status-----------")
message(STATUS "        version: ${OpenCV_VERSION}")
message(STATUS "        libraries: ${OpenCV_LIBS}")
message(STATUS "        include path: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "-------------------------------------------------------")
include_directories(${OpenCV_INCLUDE_DIRS})




add_executable(kcf main.cpp)
target_link_libraries(kcf  ${OpenCV_LIBS})
