# 指定CMake的最小版本要求
cmake_minimum_required(VERSION 3.10)

# 定义测试子项目
project(Tests)

# 启用测试
enable_testing()

# 如果测试需要链接到主项目的库或使用共同的头文件
include_directories(${PROJECT_SOURCE_DIR}/include)

# 可选：如果测试用到了一些公共的工具或辅助函数，可以编译成库
# add_library(testutils STATIC utils.cpp)

# 自动添加所有测试源文件
file(GLOB TEST_SOURCES "*.cpp")
# list(REMOVE_ITEM TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp")  # 移除非测试的源文件

# 为每个测试源文件创建一个可执行文件
foreach(testsourcefile ${TEST_SOURCES})
    get_filename_component(testname ${testsourcefile} NAME_WE)  # 获取文件名，不带路径和扩展名

    # 添加可执行文件
    add_executable(${testname} ${testsourcefile})

    # 如果有公共库，链接它
    # target_link_libraries(${testname} testutils)

    # 添加到CTest测试
    add_test(NAME ${testname} COMMAND ${testname})
endforeach(testsourcefile)
