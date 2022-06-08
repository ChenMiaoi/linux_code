#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

int main(){
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock < 0){
        perror("socket error");
        return 1;
    }

    struct sockaddr_in local;
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(8081);
    local.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_sock, (struct sockaddr*)&local, sizeof(local)) < 0){
        perror("bind error");
        return 2;
    }
    if (listen(listen_sock, 5) < 0){
        perror("listen error");
        return 3;
    }

    struct sockaddr_in peer;
    for (; ;){
        socklen_t len = sizeof(peer);
        int sock = accept(listen_sock, (struct sockaddr*)&peer, &len);
        if (sock < 0){
            perror("accept error");
            continue;
        }
        if (fork() == 0){
            if (fork() > 0){
                exit(0);
            }
            close(listen_sock);
            //read http request
            char buffer[1024] = {};
            recv(sock, buffer, sizeof(buffer), 0);
            std::cout << "######################## http request begin #############################" << std::endl;
            std::cout << buffer << std::endl;
            std::cout << "######################## http request end   #############################" << std::endl;
            exit(0);
        }
        waitpid(-1, nullptr, 0);
    }
    return 0;
}