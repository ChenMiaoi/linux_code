#ifndef INC_3_LESSON_UDP_SERVER_HPP
#define INC_3_LESSON_UDP_SERVER_HPP

#include <iostream>
#include <string>
#include <sys/socket.h>

class UdpServer{
public:
    UdpServer(){}
    ~UdpServer(){}
public:
    void InitUdpServer(){

    }
    void Start(){

    }
private:
    int _port;  //端口
    std::string ip; //去掉
};
#endif //INC_3_LESSON_UDP_SERVER_HPP
