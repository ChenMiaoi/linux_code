#include "tcp_sevrer.hpp"

int main(){
    TcpServer tsvr(8081);
    if (tsvr.InitTcpServer()) {
        tsvr.Loop();
    }
    return 0;
}