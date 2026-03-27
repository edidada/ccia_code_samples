# C++ Concurrency in Action - CMake Build System
# 《C++并发编程实战》第二版代码构建配置

cmake_minimum_required(VERSION 3.16)
project(CppConcurrencyInAction
    VERSION 2.0.0
    DESCRIPTION "C++ Concurrency in Action 2nd Edition Examples"
    LANGUAGES CXX
)

# 设置C++标准 - 书籍使用C++17特性
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -g
        -O2
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(
        /W4
        /Zi
        /O2
    )
endif()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 查找线程库
find_package(Threads REQUIRED)

# 获取所有listings目录下的cpp文件
file(GLOB LISTING_SOURCES listings/*.cpp)

# 需要跳过的文件列表（不完整代码或需要特殊库）
set(SKIP_LISTINGS
    # 这些文件包含不完整的代码片段，缺少main函数或依赖
    listing_2.1.cpp   # 只有函数定义，没有main
    listing_2.2.cpp   # 只有函数定义，没有main
    listing_2.3.cpp   # 只有函数定义，没有main
    listing_2.4.cpp   # 只有函数定义，没有main
    listing_2.5.cpp   # 只有函数定义，没有main
    listing_2.6.cpp   # 只有函数定义，没有main
    listing_2.7.cpp   # 只有函数定义，没有main
    listing_2.8.cpp   # 只有函数定义，没有main
    listing_3.1.cpp   # 只有类定义
    listing_3.2.cpp   # 只有函数定义
    listing_3.3.cpp   # 只有函数定义
    listing_3.4.cpp   # 只有函数定义
    listing_3.5.cpp   # 只有函数定义
    listing_3.6.cpp   # 只有函数定义
    listing_3.7.cpp   # 只有函数定义
    listing_3.8.cpp   # 只有函数定义
    listing_3.9.cpp   # 只有函数定义
    listing_3.10.cpp  # 只有函数定义
    listing_3.11.cpp  # 只有函数定义
    listing_3.12.cpp  # 只有类定义
    listing_3.13.cpp  # 只有类定义
    listing_4.1.cpp   # 只有函数定义
    listing_4.2.cpp   # 只有函数定义
    listing_4.3.cpp   # 只有函数定义
    listing_4.4.cpp   # 只有函数定义
    listing_4.5.cpp   # 只有函数定义
    listing_4.6.cpp   # 只有函数定义
    listing_4.7.cpp   # 只有函数定义
    listing_4.8.cpp   # 只有函数定义
    listing_4.9.cpp   # 只有函数定义
    listing_4.10.cpp  # 只有函数定义
    listing_4.11.cpp  # 只有函数定义
    listing_4.12.cpp  # 只有函数定义
    listing_4.13.cpp  # 只有函数定义
    listing_4.14.cpp  # 只有函数定义
    listing_4.15.cpp  # 只有函数定义
    listing_4.16.cpp  # 只有函数定义
    listing_4.17.cpp  # 只有函数定义
    listing_4.18.cpp  # 只有函数定义
    listing_4.19.cpp  # 只有函数定义
    listing_4.20.cpp  # 只有函数定义
    listing_4.21.cpp  # 只有函数定义
    listing_4.22.cpp  # 只有函数定义
    listing_4.23.cpp  # 只有函数定义
    listing_4.24.cpp  # 只有函数定义
    listing_4.25.cpp  # 只有函数定义
    listing_4.26.cpp  # 只有函数定义
    listing_4.27.cpp  # 只有函数定义
    listing_5.1.cpp   # 只有函数定义
    listing_5.2.cpp   # 只有函数定义
    listing_5.3.cpp   # 只有函数定义
    listing_5.4.cpp   # 只有函数定义
    listing_5.5.cpp   # 只有函数定义
    listing_5.6.cpp   # 只有函数定义
    listing_5.7.cpp   # 只有函数定义
    listing_5.8.cpp   # 只有函数定义
    listing_5.9.cpp   # 只有函数定义
    listing_5.10.cpp  # 只有函数定义
    listing_5.11.cpp  # 只有函数定义
    listing_5.12.cpp  # 只有函数定义
    listing_5.13.cpp  # 只有函数定义
    listing_6.1.cpp   # 只有类定义
    listing_6.2.cpp   # 只有类定义
    listing_6.3.cpp   # 只有类定义
    listing_6.4.cpp   # 只有类定义
    listing_6.5.cpp   # 只有类定义
    listing_6.6.cpp   # 只有类定义
    listing_6.7.cpp   # 只有类定义
    listing_6.8.cpp   # 只有类定义
    listing_6.9.cpp   # 只有类定义
    listing_6.10.cpp  # 只有类定义
    listing_6.11.cpp  # 只有类定义
    listing_6.12.cpp  # 只有类定义
    listing_6.13.cpp  # 只有类定义
    listing_7.1.cpp   # 只有类定义
    listing_7.2.cpp   # 只有类定义
    listing_7.3.cpp   # 只有类定义
    listing_7.4.cpp   # 只有类定义
    listing_7.5.cpp   # 只有类定义
    listing_7.6.cpp   # 只有类定义
    listing_7.7.cpp   # 只有类定义
    listing_7.8.cpp   # 只有类定义
    listing_7.9.cpp   # 只有类定义
    listing_7.10.cpp  # 只有类定义
    listing_7.11.cpp  # 只有类定义
    listing_7.12.cpp  # 只有类定义
    listing_7.13.cpp  # 只有类定义
    listing_7.14.cpp  # 只有类定义
    listing_7.15.cpp  # 只有类定义
    listing_7.16.cpp  # 只有类定义
    listing_7.17.cpp  # 只有类定义
    listing_7.18.cpp  # 只有类定义
    listing_7.19.cpp  # 只有类定义
    listing_7.20.cpp  # 只有类定义
    listing_7.21.cpp  # 只有类定义
    listing_7.22.cpp  # 只有类定义
    listing_8.1.cpp   # 只有类定义
    listing_8.2.cpp   # 只有类定义
    listing_8.3.cpp   # 只有类定义
    listing_8.4.cpp   # 只有类定义
    listing_8.5.cpp   # 只有类定义
    listing_8.6.cpp   # 只有类定义
    listing_8.7.cpp   # 只有类定义
    listing_8.8.cpp   # 只有类定义
    listing_8.9.cpp   # 只有类定义
    listing_8.10.cpp  # 只有类定义
    listing_8.11.cpp  # 只有类定义
    listing_8.12.cpp  # 只有类定义
    listing_8.13.cpp  # 只有类定义
    listing_9.1.cpp   # 只有类定义
    listing_9.2.cpp   # 只有类定义
    listing_9.3.cpp   # 只有类定义
    listing_9.4.cpp   # 只有类定义
    listing_9.5.cpp   # 只有类定义
    listing_9.6.cpp   # 只有类定义
    listing_9.7.cpp   # 只有类定义
    listing_9.8.cpp   # 只有类定义
    listing_9.9.cpp   # 只有类定义
    listing_9.10.cpp  # 只有类定义
    listing_9.11.cpp  # 只有类定义
    listing_9.12.cpp  # 只有类定义
    listing_9.13.cpp  # 只有类定义
    listing_10.1.cpp  # 需要并行算法库(TBB)
    listing_10.2.cpp  # 需要并行算法库(TBB)
    listing_10.3.cpp  # 需要并行算法库(TBB)
    listing_11.1.cpp  # 只有类定义
    listing_c.1.cpp   # 只有函数定义
    listing_c.2.cpp   # 只有函数定义
    listing_c.3.cpp   # 只有函数定义
    listing_c.4.cpp   # 只有函数定义
    listing_c.5.cpp   # 只有函数定义
    listing_c.6.cpp   # 只有函数定义
    listing_c.7.cpp   # 只有函数定义
    listing_c.8.cpp   # 只有函数定义
    listing_c.9.cpp   # 只有函数定义
    listing_c.10.cpp  # 只有函数定义
    listing_a.1.cpp   # 只有函数定义
    listing_a.2.cpp   # 只有函数定义
    listing_a.3.cpp   # 只有函数定义
    listing_a.4.cpp   # 只有函数定义
)

# 检查是否有可以构建的完整程序
set(BUILDABLE_LISTINGS "")
foreach(SOURCE_FILE ${LISTING_SOURCES})
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME)
    list(FIND SKIP_LISTINGS ${FILE_NAME} SKIP_INDEX)
    if(SKIP_INDEX EQUAL -1)
        list(APPEND BUILDABLE_LISTINGS ${SOURCE_FILE})
    else()
        message(STATUS "Skipping ${FILE_NAME} - incomplete code snippet")
    endif()
endforeach()

# 创建可执行文件
foreach(SOURCE_FILE ${BUILDABLE_LISTINGS})
    get_filename_component(EXEC_NAME ${SOURCE_FILE} NAME_WE)
    add_executable(${EXEC_NAME} ${SOURCE_FILE})
    target_link_libraries(${EXEC_NAME} PRIVATE Threads::Threads)
    set_target_properties(${EXEC_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
endforeach()

# 统计信息
list(LENGTH BUILDABLE_LISTINGS BUILDABLE_COUNT)
list(LENGTH LISTING_SOURCES TOTAL_COUNT)
list(LENGTH SKIP_LISTINGS SKIPPED_COUNT)

message(STATUS "C++ Concurrency in Action - Build Configuration")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Total listings: ${TOTAL_COUNT}")
message(STATUS "Buildable listings: ${BUILDABLE_COUNT}")
message(STATUS "Skipped listings: ${SKIPPED_COUNT}")
message(STATUS "Note: Most listings are code snippets without main()")
