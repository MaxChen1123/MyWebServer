#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include<memory>
#include<sys/epoll.h>

#include"../Socket/Socket.h"
#include"../Epoller/Epoller.h"
#include"../Connection/Connection.h"

class Acceptor{
public:
    Acceptor();
    ~Acceptor();
    void acceptConnection();
    void setConnectionCallback(std::function<void(Socket*)> callback);
    void setChannel(std::unique_ptr<Epoller>&);

private:
    std::unique_ptr<Socket> socket_p;
    Channel* acceptChannel;
    std::function<void(Socket*)> connectionCallback;
};