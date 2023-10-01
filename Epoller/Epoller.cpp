#include"Epoller.h"
#include"../Channel/Channel.h"

#define MAX_EPOLL_SIZE 100

Epoller::Epoller(){
    ep_fd=epoll_create(101);
    events=new epoll_event[MAX_EPOLL_SIZE];
    threadpool=new Threadpool(3);
}

std::vector<Channel*> Epoller::poll(){
    //printf("start polling\n");
    int nfds=epoll_wait(ep_fd,events,MAX_EPOLL_SIZE,1000);
    //printf("end polling\n");
    std::vector<Channel*> channels;
    for(int i=0;i<nfds;i++){
        Channel* ch=(Channel*)events[i].data.ptr;
        channels.emplace_back(ch);
    }
    return channels;
}

void Epoller::loop(){
    std::vector<Channel*> chs;
    while (true)
    {
        chs.clear();
        chs=poll();
        for(auto it:chs){
            threadpool->addTask(it->getCallback());
        }
    }
    
    
}

void Epoller::add(Channel* _ch){
    int fd=_ch->getFd();
    epoll_event ev;
    ev.data.ptr=_ch;
    ev.events=_ch->getEvent();
    epoll_ctl(ep_fd,EPOLL_CTL_ADD,fd,&ev);
    printf("succssed puting in epoll\n");

}