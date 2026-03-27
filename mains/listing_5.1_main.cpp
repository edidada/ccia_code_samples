// Main file for listing_5.1.cpp
// 自旋锁互斥量示例

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

// 前向声明 - spinlock_mutex 定义在 listing_5.1.cpp 中
class spinlock_mutex;
extern spinlock_mutex spin_mutex;

void increment_counter(int id) {
    for (int i = 0; i < 100; ++i) {
        spin_mutex.lock();
        extern int shared_counter;
        ++shared_counter;
        std::cout << "Thread " << id << " incremented counter to " << shared_counter << std::endl;
        spin_mutex.unlock();
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}

int shared_counter = 0;
spinlock_mutex spin_mutex;

int main() {
    std::cout << "=== Spinlock Mutex Demo (listing_5.1) ===" << std::endl;
    
    std::vector<std::thread> threads;
    
    // 创建4个线程同时增加计数器
    for (int i = 0; i < 4; ++i) {
        threads.push_back(std::thread(increment_counter, i));
    }
    
    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "Final counter value: " << shared_counter << std::endl;
    std::cout << "Expected value: 400" << std::endl;
    
    return 0;
}
