//
// Created by meshi on 13/01/2020.
//
#pragma once

#ifndef FINALPROJECTPART2_MYSERIALSERVER_H
#define FINALPROJECTPART2_MYSERIALSERVER_H
#include "Server.h"
using namespace server_side;
class MySerialServer :public Server{
public:
    void open (int port, ClientHandler *clientHandler) override ;
    void stop();
    void serverSide(int socketfd,ClientHandler *clientHandler);
    bool serverStop=false;
};


#endif //FINALPROJECTPART2_MYSERIALSERVER_H
