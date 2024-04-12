#pragma once

#include <cassert>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <vector>
#include <WinSock2.h>
#include <string>


#define SIZE 1024


namespace Net
{

    class Client
    {
    private:
        WSADATA wsa;
        SOCKET clientsocket;
        std::string ipaddress;
        int port;
        char buffer[SIZE]{};
        std::string message;
        struct sockaddr_in info;
        int infolength;
        int recvlength{};
    public:
        Client(int, std::string);
        ~Client();
    private:
        void init();
        void receive();
        void proccess();
        void send();
    public:
        [[noreturn]] void connect();
    };

} // Net
