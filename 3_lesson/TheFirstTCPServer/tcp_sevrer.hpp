#ifndef THEFIRSTTCPSERVER_TCP_SEVRER_HPP
#define THEFIRSTTCPSERVER_TCP_SEVRER_HPP

#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BACKLOG 5

class TcpServer{
public:
    TcpServer(int port) : _port(port), _sock_listen(-1)
    {}

    ~TcpServer(){

    }
public:
    bool InitTcpServer(){
        _sock_listen = socket(AF_INET, SOCK_STREAM, 0);
        if (_sock_listen < 0){
            std::cerr << "socket error!" << std::endl;
            return false;
        }

        struct sockaddr_in local;
        memset(&local, 0, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port  = htons(_port);
        local.sin_addr.s_addr = INADDR_ANY;

        if (bind(_sock_listen, (struct sockaddr*)&local, sizeof(local)) < 0){
            std::cerr  << "bind  error" << std::endl;
            perror("bind");
            return false;
        }

        if (listen(_sock_listen, BACKLOG) < 0) {
            std::cerr << "listen  error" << std::endl;
            return false;
        }
        return true;
    }
    void Loop(){
        while (true){
            struct sockaddr_in peer;
            socklen_t len = sizeof(peer);
            int sock = accept(_sock_listen, (struct sockaddr*)&peer, &len);
            if (sock < 0){
                std::cerr << "accept error" << std::endl;
                continue;
            }
            std::cout << "get a new link : " << sock << std::endl;
        }
    }
private:
    int _port;
    int _sock_listen;
};

#endif //THEFIRSTTCPSERVER_TCP_SEVRER_HPP
