
# 指定 CMAKE 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(ThreadPool VERSION 1.0.1)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

message(STATUS "Build type : ${CMAKE_BUILD_TYPE}")

# 查找依赖
find_package(Threads REQUIRED)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 添加可执行文件
add_executable(threadpool01
	src/threadPool01.cpp
	src/main01.cpp)

# 链接线程库
target_link_libraries(threadpool01 Threads::Threads)

# 设置输出目录
set_target_properties(threadpool01 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

