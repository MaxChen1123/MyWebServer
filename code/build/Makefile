CXX = g++
CFLAGS = -std=c++14 -O2 -Wall -g 

TARGET = server
OBJS = ../Acceptor/*.cpp ../Channel/*.cpp ../Connection/*.cpp ../Epoller/*.cpp \
 ../InetAddress/*.cpp ../Socket/*.cpp ../Threadpool/*.cpp ../Server/*.cpp ../main.cpp \
 ../Buffer/*.cpp ../Logger/*.cpp
all: $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o ../bin/$(TARGET)  -pthread 

client: ../Client.cpp ../Buffer/*.cpp
	$(CXX) $(CFLAGS) ../Client.cpp ../Buffer/*.cpp -o ../bin/client