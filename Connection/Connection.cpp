#include"Connection.h"

Connection::Connection(Channel* _ch,std::shared_ptr<Epoller> _epoller){
    ch = _ch;
    epoller = _epoller;
    ch->setCallback(std::move(std::bind(&Connection::connect, this)));
    ch->putInEpoll();
}

void Connection::connect(){
    char buf[1024];     //这个buf大小无所谓
    printf("client fd %d connected\n", ch->getFd());
    while(true){    //由于使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
        bzero(&buf, sizeof(buf));
        ssize_t bytes_read = read(ch->getFd(), buf, sizeof(buf));
        printf("bytes_read: %ld\n", bytes_read);

        if(bytes_read > 0){
           printf("message from client fd %d: %s\n", ch->getFd(), buf);
           write(ch->getFd(), buf, bytes_read);
        } else if(bytes_read == -1 && errno == EINTR){  //客户端正常中断、继续读取
            printf("continue reading");
            continue;
        } else if(bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){//非阻塞IO，这个条件表示数据全部读取完毕
            printf("finish reading once\n");
            
            break;
        } else if(bytes_read == 0){  //EOF，客户端断开连接
            printf("EOF, client fd %d disconnected\n", ch->getFd());
            // close(sockfd);   //关闭socket会自动将文件描述符从epoll树上移除
            //deleteConnectionCallback(sock);
            break;
        }
    }

}