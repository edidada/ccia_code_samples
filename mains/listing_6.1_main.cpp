// Main file for listing_6.1.cpp
// 线程安全栈示例

#include <iostream>
#include <thread>
#include <vector>

// 前向声明 - 定义在 listing_6.1.cpp 中
template<typename T>
class threadsafe_stack;

struct empty_stack;

// 辅助函数声明
void push_items(threadsafe_stack<int>& stack, int start, int count);
void pop_items(threadsafe_stack<int>& stack, int count);

// 辅助函数实现
void push_items(threadsafe_stack<int>& stack, int start, int count) {
    for (int i = 0; i < count; ++i) {
        stack.push(start + i);
        std::cout << "Pushed: " << (start + i) << std::endl;
    }
}

void pop_items(threadsafe_stack<int>& stack, int count) {
    for (int i = 0; i < count; ++i) {
        try {
            int value;
            stack.pop(value);
            std::cout << "Popped: " << value << std::endl;
        } catch (const empty_stack& e) {
            std::cout << "Stack empty: " << e.what() << std::endl;
        }
    }
}

int main() {
    std::cout << "=== Thread-safe Stack Demo (listing_6.1) ===" << std::endl;
    
    threadsafe_stack<int> stack;
    
    // 测试单线程操作
    std::cout << "\n--- Single thread test ---" << std::endl;
    push_items(stack, 1, 5);
    pop_items(stack, 3);
    
    // 测试多线程操作
    std::cout << "\n--- Multi-thread test ---" << std::endl;
    std::thread t1(push_items, std::ref(stack), 100, 3);
    std::thread t2(pop_items, std::ref(stack), 2);
    
    t1.join();
    t2.join();
    
    // 清空栈
    std::cout << "\n--- Emptying stack ---" << std::endl;
    pop_items(stack, 10);
    
    std::cout << "\nStack empty: " << (stack.empty() ? "yes" : "no") << std::endl;
    
    return 0;
}
