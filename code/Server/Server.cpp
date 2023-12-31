#include"Server.h"

Server::Server(const char* _log_file){
    mainepoller=std::make_unique<Epoller>();
    acceptor=std::make_unique<Acceptor>();
    logger=std::make_shared<Logger>(_log_file);
    acceptor.get()->setChannel(mainepoller);
    std::function<void(Socket*)> _cb=std::bind(&Server::connectionEstablished,this,_1);
    acceptor.get()->setConnectionCallback(_cb);

    threadnum=static_cast<int>(std::thread::hardware_concurrency());
    threadpool=std::make_unique<Threadpool>(threadnum);
    for(int i=0;i<threadnum;i++){
        subReactors.emplace_back(std::make_unique<Epoller>());
    }
    for(int i=0;i<threadnum;i++){
        threadpool.get()->addTask(std::bind(&Epoller::loop,subReactors[i].get()));
    }

    logger.get()->log(INFO,"server start");
    mainepoller.get()->loop();
}

Server::~Server(){
    
}

void Server::connectionEstablished(Socket* _socket){
    int fd=_socket->getFd();
    int random = fd% subReactors.size();
    connections[fd]=std::make_unique<Connection>(new Channel(fd),_socket,logger);
    connections[fd].get()->setChannel(subReactors[random]);
}