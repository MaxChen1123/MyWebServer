#pragma once
#include <unistd.h>
#include<sys/epoll.h>
#include<functional>
#include<memory>

#include"../Epoller/Epoller.h"

class Channel{
    private:
    int fd;
    std::shared_ptr<Epoller> epoller;
    uint32_t event;
    std::function<void()> callback;

    public:
    Channel(int,std::shared_ptr<Epoller>);
    int getFd();
    void setCallback(std::function<void()>&&);
    std::function<void()> getCallback();
    void handleEvent();
    uint32_t getEvent();
    void putInEpoll();
};