#include"Threadpool.h"

Threadpool::Threadpool(int threadNum){
    stop=false;
    //std::function<void()> task;
    for(int i=0;i<threadNum;i++){
        threads.emplace_back([this](){
            while(true){
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock,[this]{return stop||!tasks.empty();});
                    
                    task=std::move(tasks.front());
                    tasks.pop();
                }
                task();
            }
        });};

};

void Threadpool::addTask(std::function<void()>&& task){
    {
        std::unique_lock<std::mutex> lock(mtx);
        tasks.emplace(std::move(task));
    }
    cv.notify_one();
}