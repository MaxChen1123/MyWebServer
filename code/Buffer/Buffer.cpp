#include "./Buffer.h"

Buffer::Buffer(){}

Buffer::~Buffer(){}


void Buffer::append(const char* _str, int _size){
    for(int i = 0; i < _size; ++i){
        if(_str[i] == '\0') break;
        data.push_back(_str[i]);
    }
}

ssize_t Buffer::size(){
    return data.size();
}

const char* Buffer::c_str(){
    return data.c_str();
}

void Buffer::clear(){
    data.clear();
}

void Buffer::getline(){
    data.clear();
    std::getline(std::cin, data);
}