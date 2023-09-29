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
    Acceptor(std::shared_ptr<Epoller> epoller);
    void acceptConnection();

private:
    std::shared_ptr<Epoller> epoller;
    std::unique_ptr<Socket> socket_p;
    Channel* acceptChannel;
};