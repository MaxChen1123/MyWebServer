#pragma once

#include<memory>
#include<unordered_map>
#include<vector>
#include<functional>

#include"../Threadpool/Threadpool.h"
#include"../Acceptor/Acceptor.h"
#include"../Connection/Connection.h"
#include"../Logger/Logger.h"

using std::placeholders::_1;

class Server{
private:
    std::unique_ptr<Acceptor> acceptor;
    std::unique_ptr<Epoller> mainepoller;
    std::unordered_map<int, std::unique_ptr<Connection>> connections;
    std::unique_ptr<Threadpool> threadpool;
    std::vector<std::unique_ptr<Epoller>> subReactors;
    std::shared_ptr<Logger> logger;

    int threadnum;

    void connectionEstablished(Socket*);

public:
    Server(const char* _log_file);
    ~Server();
};