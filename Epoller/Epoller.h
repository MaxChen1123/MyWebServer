#pragma once
#include<sys/epoll.h>
#include<vector>
#include<memory>

#include"../Threadpool/Threadpool.h"

class Channel;

class Epoller{
    public:
    Epoller();
    std::vector<Channel*> poll();
    void loop();
    Threadpool* threadpool;
    int ep_fd;
    epoll_event* events;
    void add(Channel*);

};