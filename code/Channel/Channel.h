#pragma once
#include <unistd.h>
#include<sys/epoll.h>
#include<functional>
#include<memory>

#include"../Epoller/Epoller.h"

class Channel{
    private:
    int fd;
    uint32_t event;
    std::function<void()> callback;

    public:
    Channel(int);
    void handleEvent();
    void setCallback(std::function<void()>&&);
    void putInEpoll(std::unique_ptr<Epoller>& epoller);
    std::function<void()> getCallback();
    int getFd();
    uint32_t getEvent();
    
};