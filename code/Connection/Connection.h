#pragma once

#include<memory>
#include<unistd.h>
#include<string.h>

#include"../Channel/Channel.h"
#include"../Epoller/Epoller.h"
#include"../Buffer/Buffer.h"
#include"../Logger/Logger.h"

class Socket;
class Connection{
private:
    Channel* ch;
    Socket* sk;   
    Buffer* buf;
    std::shared_ptr<Logger> logger;
public:
    Connection(Channel*,Socket*,std::shared_ptr<Logger>&);
    ~Connection();
    void connect();
    void setChannel(std::unique_ptr<Epoller>&);
};