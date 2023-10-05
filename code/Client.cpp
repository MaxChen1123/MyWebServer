#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include"./Buffer/Buffer.h"

#define BUFFER_SIZE 1024 

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    Buffer* buf=new Buffer();

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);

    connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr));
    printf("connect success!\n");
    
    while(true){
        buf->getline();
        ssize_t write_bytes = write(sockfd, buf->c_str(), buf->size());
        printf("write bytes: %ld\n",buf->size());
        
        if(write_bytes == -1){
            printf("socket already disconnected, can't write any more!\n");
            break;
        }
    }
    close(sockfd);
    return 0;
}
