#pragma once
#include<sys/epoll.h>
#include<vector>
#include<memory>

class Channel;

class Epoller{
    public:
    Epoller();
    std::vector<Channel*> poll();
    void loop();
    
    int ep_fd;
    epoll_event* events;
    void add(Channel*);

};