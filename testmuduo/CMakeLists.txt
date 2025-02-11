cmake_minimum_required(VERSION 3.5.0) #camke版本号
project(testmuduo) #项目名称

# 设置C++编译选项
# 配置头文件搜索路径
# include_directories()
# 配置库文件搜索路径
# link_directories()


# 设置需要编译的源文件列表
set(SRC_LIST muduo_server.cpp)

# 把指定目录下的所有源文件的文件名存入变量名SRC_LIST中
# aux_source_directory(. SRC_LIST)

# 设置可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 生成可执行文件
add_executable(server ${SRC_LIST})
# 生成的可执行程序所需要的链接库
target_link_libraries(server muduo_net muduo_base pthread)