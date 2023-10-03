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
    int getFd();
    void setCallback(std::function<void()>&&);
    std::function<void()> getCallback();
    void handleEvent();
    uint32_t getEvent();
    void putInEpoll(Epoller*);
};