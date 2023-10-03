#pragma once

#include<memory>
#include<unordered_map>
#include<vector>
#include<functional>

#include"../Threadpool/Threadpool.h"
#include"../Acceptor/Acceptor.h"
#include"../Connection/Connection.h"

using std::placeholders::_1;

class Server{
private:
    std::unique_ptr<Acceptor> acceptor;
    std::unique_ptr<Epoller> mainepoller;
    std::unordered_map<int, std::unique_ptr<Connection>> connections;
    std::unique_ptr<Threadpool> threadpool;
    std::vector<std::shared_ptr<Epoller>> subReactors;
    int threadnum;

    void connectionEstablished(Socket*);

public:
    Server();
    ~Server();
};