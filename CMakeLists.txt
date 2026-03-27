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

# 检查是否有main函数，并分类
set(LISTINGS_WITH_MAIN "")
set(LISTINGS_WITHOUT_MAIN "")

foreach(SOURCE_FILE ${LISTING_SOURCES})
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME)
    
    # 读取文件内容检查是否有main函数
    file(READ ${SOURCE_FILE} FILE_CONTENT)
    if(FILE_CONTENT MATCHES "int main\\s*\\(")
        list(APPEND LISTINGS_WITH_MAIN ${SOURCE_FILE})
    else()
        list(APPEND LISTINGS_WITHOUT_MAIN ${FILE_NAME})
    endif()
endforeach()

# 为已有main函数的文件创建可执行目标
foreach(SOURCE_FILE ${LISTINGS_WITH_MAIN})
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME)
    # 使用完整文件名作为目标名，避免冲突 (如 listing_5.1 和 listing_5.10)
    string(REPLACE "." "_" EXEC_NAME ${FILE_NAME})
    string(REPLACE ".cpp" "" EXEC_NAME ${EXEC_NAME})
    add_executable(${EXEC_NAME} ${SOURCE_FILE})
    target_link_libraries(${EXEC_NAME} PRIVATE Threads::Threads)
    set_target_properties(${EXEC_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
endforeach()

# 为没有main函数的文件，检查是否有对应的mains/*_main.cpp
set(MAIN_WRAPPERS "")
file(GLOB MAIN_SOURCES mains/*_main.cpp)

foreach(MAIN_FILE ${MAIN_SOURCES})
    get_filename_component(MAIN_NAME ${MAIN_FILE} NAME_WE)
    # 提取对应的listing文件名 (例如: listing_4.4_main -> listing_4.4)
    string(REGEX REPLACE "_main$" "" LISTING_NAME ${MAIN_NAME})
    set(LISTING_FILE "${CMAKE_CURRENT_SOURCE_DIR}/listings/${LISTING_NAME}.cpp")
    
    if(EXISTS ${LISTING_FILE})
        add_executable(${MAIN_NAME} ${MAIN_FILE} ${LISTING_FILE})
        target_include_directories(${MAIN_NAME} PRIVATE 
            ${CMAKE_CURRENT_SOURCE_DIR}/listings
            ${CMAKE_CURRENT_SOURCE_DIR}/mains
        )
        target_link_libraries(${MAIN_NAME} PRIVATE Threads::Threads)
        set_target_properties(${MAIN_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        )
        list(APPEND MAIN_WRAPPERS ${MAIN_NAME})
    endif()
endforeach()

# 需要跳过的文件列表（需要特殊库或不完整）
set(SKIP_LISTINGS
    listing_10.1.cpp  # 需要并行算法库(TBB)
    listing_10.2.cpp  # 需要并行算法库(TBB)
    listing_10.3.cpp  # 需要并行算法库(TBB)
)

# 统计信息
list(LENGTH LISTINGS_WITH_MAIN COUNT_WITH_MAIN)
list(LENGTH LISTINGS_WITHOUT_MAIN COUNT_WITHOUT_MAIN)
list(LENGTH MAIN_WRAPPERS COUNT_MAIN_WRAPPERS)
list(LENGTH LISTING_SOURCES TOTAL_COUNT)

message(STATUS "C++ Concurrency in Action - Build Configuration")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Total listings: ${TOTAL_COUNT}")
message(STATUS "Listings with main(): ${COUNT_WITH_MAIN}")
message(STATUS "Listings without main(): ${COUNT_WITHOUT_MAIN}")
message(STATUS "Main wrapper files: ${COUNT_MAIN_WRAPPERS}")
message(STATUS "Note: Create mains/listing_X.X_main.cpp to add main() for listings without it")
