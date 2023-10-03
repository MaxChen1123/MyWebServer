#include"Channel.h"

Channel::Channel(int _fd){
    fd=_fd;
    
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

void Channel::putInEpoll(std::unique_ptr<Epoller> &_epoller){
    event=EPOLLIN|EPOLLET;
    _epoller.get()->add(this);
}

std::function<void()> Channel::getCallback(){
    return callback;
}   