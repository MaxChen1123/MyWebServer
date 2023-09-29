#pragma once

#include<memory>
#include<unistd.h>
#include<string.h>

#include"../Channel/Channel.h"
#include"../Epoller/Epoller.h"

class Connection{
private:
    Channel* ch;
    std::shared_ptr<Epoller> epoller;    
public:
    Connection(Channel*,std::shared_ptr<Epoller>);
    void connect();
};