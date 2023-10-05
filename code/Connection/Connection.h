#pragma once

#include<memory>
#include<unistd.h>
#include<string.h>

#include"../Channel/Channel.h"
#include"../Epoller/Epoller.h"
#include"../Buffer/Buffer.h"

class Socket;
class Connection{
private:
    Channel* ch;
    Socket* sk;   
    Buffer* buf;
public:
    Connection(Channel*,Socket*);
    ~Connection();
    void connect();
    void setChannel(std::unique_ptr<Epoller>&);
};