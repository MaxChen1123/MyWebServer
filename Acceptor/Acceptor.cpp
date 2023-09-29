#include"Acceptor.h"

Acceptor::Acceptor(std::shared_ptr<Epoller> _epoller){
    epoller=_epoller;
    socket_p=std::make_unique<Socket>();
    InetAddress *addr = new InetAddress("127.0.0.1", 1234);
    socket_p.get()->bind(addr);
    socket_p.get()->listen();
    socket_p.get()->setnonblocking();
    acceptChannel=new Channel(socket_p.get()->getFd(),epoller);
    acceptChannel->setCallback(std::bind(&Acceptor::acceptConnection,this));
    acceptChannel->putInEpoll();

    printf("Acceptor::Acceptor\n");    
}

void Acceptor::acceptConnection(){
    InetAddress *addr = new InetAddress();
    Socket *client_socket = new Socket(socket_p.get()->accept(addr));
    Channel *client_channel = new Channel(client_socket->getFd(),epoller);
    //toChange   
    new Connection(client_channel,epoller);

    printf("Acceptor Callbacked\n");
}
