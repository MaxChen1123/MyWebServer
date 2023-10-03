#include "Socket.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <string.h>

Socket::Socket() : fd(-1){
    fd = socket(AF_INET, SOCK_STREAM, 0);
    
}
Socket::Socket(int _fd) : fd(_fd){
    
}

Socket::~Socket(){
    if(fd != -1){
        close(fd);
        fd = -1;
    }
}

void Socket::bind(InetAddress *_addr){
    struct sockaddr_in addr = _addr->getAddr();
    socklen_t addr_len = _addr->getAddr_len();
    ::bind(fd, (sockaddr*)&addr, addr_len);
    _addr->setInetAddr(addr, addr_len);
}

void Socket::listen(){
    ::listen(fd, SOMAXCONN);
}
void Socket::setnonblocking(){
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

int Socket::accept(InetAddress *_addr){
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    bzero(&addr, sizeof(addr));
    int clnt_sockfd = ::accept(fd, (sockaddr*)&addr, &addr_len);
    // todo:errorr process 
    _addr->setInetAddr(addr, addr_len);
    return clnt_sockfd;
}
void Socket::connect(InetAddress *_addr){
    struct sockaddr_in addr = _addr->getAddr();
    socklen_t addr_len = _addr->getAddr_len();
   ::connect(fd, (sockaddr*)&addr, addr_len);
}

int Socket::getFd(){
    return fd;
}