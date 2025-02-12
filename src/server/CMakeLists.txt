
# 搜索所有源文件
aux_source_directory(. DIR_SRCS)

# 生成可执行文件
add_executable(ChatServer ${DIR_SRCS})

# 连接库文件
target_link_libraries(ChatServer muduo_net muduo_base pthread)