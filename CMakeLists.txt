# 指定CMake的最小版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(TPCtest VERSION 1.0.0)

# 设置C++标准为C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加include目录
include_directories(include)

# 自动收集所有源文件
file(GLOB SOURCES "src/*.cpp")

# 添加可执行文件
add_executable(TPCtest ${SOURCES})

# 链接库（如果有的话）
# target_link_libraries(MyExecutable PUBLIC MyLibrary)

# 如果有需要，可以启用测试
enable_testing()
add_subdirectory(tests)

# 安装规则，指定安装目录
# install(TARGETS MyExecutable DESTINATION bin)

# 可以选择添加一个配置文件，以便其他项目引用
# include(CMakePackageConfigHelpers)
# write_basic_package_version_file(
#     MyConfigVersion.cmake
#     VERSION ${PROJECT_VERSION}
#     COMPATIBILITY AnyNewerVersion
# )

# install(FILES MyProjectConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/MyConfigVersion.cmake
#         DESTINATION lib/cmake/MyProject)
