#pragma once

#include<thread>
#include<vector>
#include<queue>
#include<functional>
#include<mutex>
#include<condition_variable>

class Threadpool{
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    bool stop;
    std::mutex mtx;
    std::condition_variable cv;
public:
    void addTask(std::function<void()>&& task);
    Threadpool(int threadNum);

};
