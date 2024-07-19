#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <iostream>
#include <vector>
#define queue_size_max 10
template<typename T>
class SafeQueue
{
private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cond_;

public:
    // 禁用拷贝构造函数和赋值操作符
    SafeQueue(const SafeQueue&) = delete;
    SafeQueue& operator=(const SafeQueue&) = delete;

    // 移动构造函数和移动赋值操作符
    SafeQueue(SafeQueue&& other) = default;
    SafeQueue& operator=(SafeQueue&& other) = default;

    SafeQueue() {}

    // 入队操作
    void enqueue(const T& value)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if(queue_.size() >= queue_size_max)
        {
            std::cout<<"queue full"<< queue_.size()<<"\r\n";
            while (!queue_.empty())
            {
                queue_.pop(); // 移除队列前端的元素，直到队列为空
            }
        }
        queue_.push(value);
        //cond_.notify_one(); // 通知一个等待的线程
    }

    // 出队操作
    bool dequeue(T& value)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty())
        {
            return false;
        }
        value = queue_.front();
        queue_.pop();
        return true;
    }

    // 等待并获取队列中的第一个元素
    bool waitAndDequeue(T& value)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if(queue_.empty())
        {
            return false;
        }
        //cond_.wait(lock, [this]{ return !queue_.empty(); }); // 等待直到队列不为空
        value = queue_.front();
        queue_.pop();
        return true;
    }

    // 检查队列是否为空
    bool isEmpty() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    bool isFull() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if(queue_.size() >= queue_size_max)
        {
            queue_ = std::queue<T>();
            return true;
        }
        return false;
    }
};

#endif // SAFEQUEUE_H
