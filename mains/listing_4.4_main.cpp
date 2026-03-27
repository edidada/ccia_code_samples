// Main file for listing_4.4.cpp
// 线程安全队列示例

#include <iostream>
#include <thread>
#include <chrono>

// 前向声明 - 这些定义在 listing_4.4.cpp 中
struct data_chunk;
data_chunk prepare_data();
bool more_data_to_prepare();
void process(data_chunk);
bool is_last_chunk(data_chunk);
void data_preparation_thread();
void data_processing_thread();

// 实现所需的辅助函数
data_chunk prepare_data() {
    static int count = 0;
    data_chunk data;
    std::cout << "Preparing data chunk " << ++count << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return data;
}

bool more_data_to_prepare() {
    static int count = 0;
    return ++count <= 5;  // 准备5个数据块
}

void process(data_chunk) {
    std::cout << "Processing data chunk" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
}

bool is_last_chunk(data_chunk) {
    static int count = 0;
    return ++count >= 5;  // 第5个是最后一个
}

int main() {
    std::cout << "=== Thread-safe Queue Demo (listing_4.4) ===" << std::endl;
    
    std::thread producer(data_preparation_thread);
    std::thread consumer(data_processing_thread);
    
    producer.join();
    consumer.join();
    
    std::cout << "Done!" << std::endl;
    return 0;
}
