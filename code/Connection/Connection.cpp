#include"Connection.h"
#include"../Socket/Socket.h"

Connection::Connection(Channel* _ch,Socket* _sock,std::shared_ptr<Logger>& _logger){
    ch = _ch;
    sk=_sock;
    logger=_logger;
    buf=new Buffer();
    ch->setCallback(std::bind(&Connection::connect, this));
}

Connection::~Connection(){
    delete ch;
    delete sk;
    delete buf;
}

void Connection::connect(){
    char temp_buf[1024];    
    printf("client fd %d connected\n", ch->getFd());
    logger.get()->log(INFO, "client fd %d connected", ch->getFd());
    while(true){
        bzero(&temp_buf, sizeof(temp_buf));
        ssize_t bytes_read = read(ch->getFd(), temp_buf, sizeof(temp_buf));
        if(bytes_read > 0){
           buf->append(temp_buf, bytes_read);
        } else if(bytes_read == -1 && errno == EINTR){  //客户端正常中断、继续读取
            printf("continue reading");
            continue;
        } else if(bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){//非阻塞IO，这个条件表示数据全部读取完毕
            printf("finish reading once\n");
            printf("client fd %d send data %s\n", ch->getFd(), buf->c_str());
            logger.get()->log(INFO, "client fd %d send data %s", ch->getFd(), buf->c_str());
            buf->clear();
            break;
        } else if(bytes_read == 0){  //EOF，客户端断开连接
            printf("EOF, client fd %d disconnected\n", ch->getFd());
            logger.get()->log(INFO, "EOF, client fd %d disconnected", ch->getFd());
            break;
        }
    }

}

void Connection::setChannel(std::unique_ptr<Epoller>&_epoller){
    ch->putInEpoll(_epoller);
}