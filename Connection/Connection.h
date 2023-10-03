#pragma once

#include<memory>
#include<unistd.h>
#include<string.h>

#include"../Channel/Channel.h"
#include"../Epoller/Epoller.h"

class Connection{
private:
    Channel* ch;   
public:
    Connection(Channel*);
    void connect();
    void setChannel(Epoller*);
};