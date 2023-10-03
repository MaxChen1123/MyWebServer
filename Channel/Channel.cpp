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

void Channel::putInEpoll(Epoller*epoller){
    event=EPOLLIN|EPOLLET;
    epoller->add(this);
}

std::function<void()> Channel::getCallback(){
    return callback;
}   