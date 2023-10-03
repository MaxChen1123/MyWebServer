#include"Server.h"

Server::Server(){
    mainepoller=std::make_unique<Epoller>();
    acceptor=std::make_unique<Acceptor>();
    acceptor.get()->setChannel(mainepoller);
    std::function<void(Socket*)> _cb=std::bind(&Server::connectionEstablished,this,_1);
    acceptor.get()->setConnectionCallback(_cb);

    threadnum=3;
    threadpool=std::make_unique<Threadpool>(threadnum);
    for(int i=0;i<threadnum;i++){
        subReactors.emplace_back(std::make_unique<Epoller>());
    }
    for(int i=0;i<threadnum;i++){
        threadpool.get()->addTask(std::bind(&Epoller::loop,subReactors[i].get()));
    }
    mainepoller.get()->loop();
}

Server::~Server(){
    
}

void Server::connectionEstablished(Socket* _socket){
    int fd=_socket->getFd();
    int random = fd% subReactors.size();
    connections[fd]=std::make_unique<Connection>(new Channel(fd),_socket);
    connections[fd].get()->setChannel(subReactors[random]);
}