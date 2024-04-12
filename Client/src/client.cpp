
#include <iostream>
#include "client.h"

#pragma warning(disable: 4996)
namespace Net {
    Client::Client(int port, std::string ipaddress)
        :
            wsa{ 0 },
            port(port),
            ipaddress(ipaddress),
            clientsocket(INVALID_SOCKET),
            info{ 0 },
            infolength(sizeof(info)) {}

    Client::~Client()
    {
        WSACleanup();
        closesocket(clientsocket);
    }


    void Client::init()
    {
        info.sin_family = AF_INET;
        info.sin_port = htons(port);
        info.sin_addr.s_addr = inet_addr(ipaddress.c_str());

        std::cout << "WSA init" << std::endl;
        WORD wVersionRequested;
        WSADATA wsaData;
        int err;
        wVersionRequested = MAKEWORD(2, 2);

        err = WSAStartup(wVersionRequested, &wsaData);
        if(err != 0)
        {
            __debugbreak();
        }
        std::cout << "WSA success" << std::endl;

        std::cout << "Creating socket" << std::endl;
        clientsocket = socket(AF_INET, SOCK_DGRAM, 0);
        if ( clientsocket == SOCKET_ERROR )
        {
            __debugbreak();
        }

        std::cout << "Socket success" << std::endl;
    }

    void Client::receive()
    {
        recvlength = recvfrom(clientsocket, buffer, SIZE, 0, (struct sockaddr*) & info, &infolength);
        if (recvlength == SOCKET_ERROR)
        {
            std::cout << "Receive failed ..." + std::to_string(WSAGetLastError()) << std::endl;
            exit(EXIT_FAILURE);
        }

    }

    void Client::proccess()
    {
        std::cout << "Pakcet from: " + std::string(inet_ntoa(info.sin_addr)) + ":" + std::to_string(ntohs(info.sin_port)) << std::endl;
        std::cout << "Data: ";
        for (unsigned i = 0; i < recvlength; ++ i)
        {
            std::cout << buffer[i];
        }
        std::cout << "\n" << std::flush;
    }

    void Client::send()
    {
        std::cout << "Enter message : " << std::endl;
        std::getline(std::cin, message);
        int err = sendto(clientsocket, message.c_str(), message.size(), 0, (struct sockaddr *) &info, infolength);
        if (err == SOCKET_ERROR)
        {
            std::cout << "Send failed ... " + std::to_string(WSAGetLastError()) << std::endl;
            exit(EXIT_FAILURE);
        }

    }

    [[noreturn]] void Client::connect()
    {
        init();

        for(;;)
        {
            send();
            receive();
            proccess();
        }

    }


} // Net
