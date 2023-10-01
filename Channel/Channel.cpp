#include"Channel.h"

Channel::Channel(int _fd,std::shared_ptr<Epoller> _epoller){
    fd=_fd;
    epoller=_epoller;
}

int Channel::getFd(){
    return fd;
}

void Channel::setCallback(std::function<void()>&& _callback){
    callback=_callback;
}

void Channel::handleEvent(){
    callback();
}

uint32_t Channel::getEvent(){
    return event;
}

void Channel::putInEpoll(){
    event=EPOLLIN|EPOLLET;
    epoller.get()->add(this);
    printf("put in epoll\n");
}

std::function<void()> Channel::getCallback(){
    return callback;
}   