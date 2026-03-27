# C++ Concurrency in Action - 书籍代码总结

> 书籍：《C++ Concurrency in Action》第二版
> 作者：Anthony Williams (C++标准委员会成员，线程库贡献者)
> 出版：Manning Publications, 2019
> 代码仓库：https://github.com/anthonywilliams/ccia_code_samples

## 项目说明

**重要提示**：本书代码以**代码片段**形式组织，大部分文件不包含完整的 `main()` 函数。这些代码片段用于配合书中讲解，而非独立运行的程序。

### 项目结构
```
ccia_code_samples/
├── listings/           # 所有代码清单
│   ├── listing_1.1.cpp    # 第1章第1个代码清单
│   ├── listing_2.1.cpp    # 第2章第1个代码清单
│   └── ...
├── CMakeLists.txt      # CMake构建配置
├── my.md              # 本文件
└── README.md          # 原项目说明
```

### 构建说明

#### 环境要求
- CMake >= 3.16
- C++17 编译器 (GCC/Clang/MSVC)
- POSIX线程库 (pthreads)

#### 构建步骤
```bash
mkdir build && cd build
cmake ..
make
```

#### 构建结果
- **可构建程序**: 1/141 (仅 listing_1.1)
- **代码片段**: 140/141 (供学习参考)

---

## 各章节内容概览

### Chapter 1: 你好，并发世界
**核心概念**：
- 什么是并发和多线程
- 为什么使用并发
- C++中的并发支持历史

**代码清单**：
| 清单 | 内容 | 类型 |
|------|------|------|
| listing_1.1 | Hello Concurrent World | ✅ 完整程序 |

**关键知识点**：
- `std::thread` 基础用法
- `join()` 等待线程完成
- 最简单的多线程程序结构

---

### Chapter 2: 线程管理
**核心概念**：
- 线程启动和结束
- 等待线程完成 vs 后台运行
- 线程标识和传递参数

**代码清单**：
- listing_2.1 - 2.8: 线程启动、RAII等待、detach、参数传递等

**关键知识点**：
- 使用函数对象、lambda、bind启动线程
- `join()` vs `detach()`
- 线程参数传递的陷阱（引用、指针）
- `std::thread` 移动语义

---

### Chapter 3: 共享数据
**核心概念**：
- 竞争条件
- 互斥锁(mutex)保护
- 死锁及避免
- 保护共享数据的最佳实践

**代码清单**：
- listing_3.1 - 3.13: 互斥锁、锁守卫、死锁、层级锁等

**关键知识点**：
- `std::mutex` 和 `std::lock_guard`
- `std::unique_lock` 灵活锁定
- `std::scoped_lock` (C++17) 避免死锁
- 锁的粒度设计
- 线程安全的数据结构设计

---

### Chapter 4: 同步操作
**核心概念**：
- 条件变量(condition variable)
- 等待特定条件
- 使用future等待一次性事件
- 限时等待

**代码清单**：
- listing_4.1 - 4.27: 条件变量、future、promise、async、packaged_task等

**关键知识点**：
- `std::condition_variable` 等待/通知机制
- `std::future` / `std::promise` 一次性事件
- `std::async` 启动异步任务
- `std::packaged_task` 任务包装
- 限时等待函数

---

### Chapter 5: C++内存模型和原子操作
**核心概念**：
- 内存模型基础
- 原子操作和类型
- 同步操作和 happens-before 关系
- 内存序(memory ordering)

**代码清单**：
- listing_5.1 - 5.13: 原子类型、自旋锁、无锁队列、内存序等

**关键知识点**：
- `std::atomic` 基本用法
- 无锁编程(lock-free programming)
- 内存序：sequentially consistent, acquire-release, relaxed
- `std::atomic_flag` 自旋锁
- 原子操作的内存同步效果

---

### Chapter 6: 设计基于锁的并发数据结构
**核心概念**：
- 线程安全数据结构设计原则
- 基于锁的栈、队列实现
- 细粒度锁设计
- 线程安全列表

**代码清单**：
- listing_6.1 - 6.13: 线程安全栈、队列、查找表、列表等

**关键知识点**：
- 线程安全栈(thread-safe stack)
- 线程安全队列(thread-safe queue)
- 细粒度锁(fine-grained locking)
- 迭代器的线程安全问题
- 死锁避免策略

---

### Chapter 7: 设计无锁并发数据结构
**核心概念**：
- 无锁数据结构设计
- 内存序选择
- ABA问题
- 无锁栈和队列实现

**代码清单**：
- listing_7.1 - 7.22: 无锁栈、无锁队列、无锁内存管理、ABA问题等

**关键知识点**：
- 比较交换(compare_exchange_weak/strong)
- 无锁内存管理（风险指针、引用计数）
- ABA问题及解决方案
- 内存序在无锁编程中的应用
- 无锁数据结构的性能考量

---

### Chapter 8: 并发代码设计
**核心概念**：
- 线程划分策略
- 数据划分 vs 任务划分
- 影响并发性能的因素
- 设计实践建议

**代码清单**：
- listing_8.1 - 8.13: 并行快速排序、线程池、中断线程等

**关键知识点**：
- 数据并行(data parallelism)
- 任务并行(task parallelism)
- 并行快速排序实现
- 线程池设计
- 线程中断机制
- 性能优化策略

---

### Chapter 9: 高级线程管理
**核心概念**：
- 线程池实现
- 工作窃取(work stealing)
- 中断线程
- 线程池应用场景

**代码清单**：
- listing_9.1 - 9.13: 简单线程池、等待任务完成、工作窃取线程池等

**关键知识点**：
- 线程池设计模式
- 任务队列管理
- 工作窃取算法
- 线程池大小设置
- 递归任务的并行化

---

### Chapter 10: 并行算法
**核心概念**：
- C++17并行算法
- 执行策略(execution policies)
- 并行算法使用场景
- 性能考量

**代码清单**：
- listing_10.1 - 10.3: 并行for_each、线程安全计数器等

**关键知识点**：
- `std::execution::seq`, `par`, `par_unseq`
- 并行STL算法
- 线程安全的并行计数
- 并行算法的性能陷阱

**注意**：需要支持并行算法的库（如Intel TBB、Microsoft PPL）

---

### Chapter 11: 测试和调试多线程代码
**核心概念**：
- 并发代码中的bug类型
- 测试并发代码的技术
- 调试多线程程序
- 工具使用

**代码清单**：
- listing_11.1: 测试并发队列

**关键知识点**：
- 竞争条件的检测
- 线程安全测试策略
- 使用工具：ThreadSanitizer、Helgrind
- 可测试性设计

---

### Appendix A: 对C++11的简要回顾
**内容**：
- 右值引用和移动语义
- 可变参数模板
- Lambda表达式
- 自动类型推导

**代码清单**：
- listing_a.1 - a.4: 移动语义、完美转发、lambda等

---

### Appendix C: 消息传递框架的完整示例
**内容**：
- 基于Actor模型的并发框架
- 消息传递编程

**代码清单**：
- listing_c.1 - c.10: Actor框架实现

---

## 代码清单类型说明

### 完整程序 (1个)
| 清单 | 说明 |
|------|------|
| listing_1.1 | Hello Concurrent World - 最简单的多线程程序 |

### 代码片段 (140个)
大部分代码清单是**代码片段**，用于：
1. 展示特定概念或技术
2. 配合书中文字讲解
3. 作为更大程序的组成部分

**使用建议**：
- 阅读对应章节理解上下文
- 将代码片段整合到测试程序中
- 参考书中完整示例

---

## 学习路径建议

### 初学者
1. **Chapter 1** → 理解基本概念
2. **Chapter 2** → 掌握线程管理
3. **Chapter 3** → 学习共享数据保护
4. **Chapter 4** → 掌握同步机制

### 进阶
5. **Chapter 5** → 深入内存模型和原子操作
6. **Chapter 6** → 设计线程安全数据结构
7. **Chapter 8** → 学习并发代码设计

### 专家
8. **Chapter 7** → 无锁编程（高难度）
9. **Chapter 9** → 高级线程管理
10. **Chapter 10** → 并行算法

---

## 参考资源

- 书籍官网：https://www.cplusplusconcurrencyinaction.com/
- 作者博客：https://www.justsoftwaresolutions.co.uk/
- C++并发参考：https://en.cppreference.com/w/cpp/thread
- C++标准委员会：http://www.open-std.org/jtc1/sc22/wg21/

---

## 构建统计

| 类别 | 数量 | 说明 |
|------|------|------|
| 总代码清单 | 141 | 覆盖11章+附录 |
| 完整程序 | 1 | listing_1.1 |
| 代码片段 | 140 | 需配合书籍使用 |
| 成功构建 | 1 | 100%完整程序 |

**注意**：本书代码设计理念是"代码片段配合讲解"，而非"独立可运行程序"。建议结合书籍内容学习。
