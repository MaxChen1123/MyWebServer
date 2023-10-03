#include"Acceptor.h"

Acceptor::Acceptor(){
    socket_p=std::make_unique<Socket>();
    InetAddress *addr = new InetAddress("127.0.0.1", 1234);
    socket_p.get()->bind(addr);
    socket_p.get()->listen();
    socket_p.get()->setnonblocking();
    acceptChannel=new Channel(socket_p.get()->getFd());
    acceptChannel->setCallback(std::bind(&Acceptor::acceptConnection,this)); 
}

Acceptor::~Acceptor(){
    delete acceptChannel;
}

void Acceptor::acceptConnection(){
    InetAddress *addr = new InetAddress();
    Socket *client_socket = new Socket(socket_p.get()->accept(addr));
    client_socket->setnonblocking();
    connectionCallback(client_socket);
    delete addr;
}

void Acceptor::setConnectionCallback(std::function<void(Socket*)> _callback){
    connectionCallback=_callback;
}

void Acceptor::setChannel(std::unique_ptr<Epoller>& _epoller){
    acceptChannel->putInEpoll(_epoller);
}
