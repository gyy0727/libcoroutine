# #设置版本要求
# cmake_minimum_required(VERSION 3.0...3.7)
# #设置项目名称
# project(myMuduo)
# #设置可执行文件输出目录
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# #查找源文件并输出到SRC
# file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
# #设置c++标准
# set(CXX_STANDARD 17)
# #设置头文件存放路径
# include_directories(${PROJECT_SOURCE_DIR}/include)
# #设置库文件输出路径
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# # add_library(threadPool SHARED ${SRC})
# #设置根据哪些文件生成可执行文件
# add_executable(myMuDuo ${SRC})
cmake_minimum_required(VERSION 3.0...3.7)
project(libco)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")
set(CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
# file(GLOB libco ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
# file(GLOB CALLER_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/caller/*.cc ${CMAKE_CURRENT_SOURCE_DIR}/src/callee/*.cc)
# list(REMOVE_ITEM CALLER_SRC /home/muqiu0614/desktop/mrpc/src/callee/userservices.cc)

include_directories(${PROJECT_SOURCE_DIR}/)
# set(HEAD_PATH ${PROJECT_SOURCE_DIR}/)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)
# # 查找 MySQL 库
# find_package(MySQL REQUIRED)

# # 查找 Redis 库
# find_package(Redis REQUIRED)
# # add_library(threadPool SHARED ${SRC})


# add_executable(mrpc ${SRC})
# target_include_directories(mrpc PRIVATE ${PROJECT_SOURCE_DIR}/include)
# target_link_libraries(mrpc muduo_net muduo_base protobuf)


add_executable(libco  ${SRC} )
# 为可执行文件1设置私有的头文件搜索路径
target_include_directories(libco PRIVATE  ${PROJECT_SOURCE_DIR}/*.h )
target_link_libraries(libco pthread)

# add_executable(libco ${CALLEE_SRC} ${SRC})
# # 为可执行文件1设置私有的头文件搜索路径
# target_include_directories(libco PRIVATE  ${PROJECT_SOURCE_DIR}/src/**/*.h )
# target_link_libraries(libco  protobuf muduo_net muduo_base )


# 链接 MySQL 库
# target_include_directories(muduo PRIVATE ${MySQL_INCLUDE_DIRS})
# target_link_libraries(muduo ${MySQL_LIBRARIES})

# # 链接 Redis 库
# target_include_directories(muduo PRIVATE ${Redis_INCLUDE_DIRS})
# target_link_libraries(muduo ${Redis_LIBRARIES})