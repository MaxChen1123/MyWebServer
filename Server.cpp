#include"Acceptor/Acceptor.h"
#include"Epoller/Epoller.h"
#include<memory>

int main(){
    std::shared_ptr<Epoller> epoller(new Epoller());
    Acceptor acceptor(epoller);
    printf("start\n");
    epoller.get()->loop();
    return 0;

}