# pragma once

#include<string>
#include<iostream>

class Buffer{
private:    
    std::string data;
public:
    Buffer();
    ~Buffer();
    void append(const char*_buffer, int _size);
    void getline();
    ssize_t size();
    const char* c_str();
    void clear();

};