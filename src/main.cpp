#include <iostream>
#include <cassert>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h> //inet_addr
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "zmq.hpp"
#include <thread>
#include <chrono>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("\n Usage: %s <tcp://address:port>\n",argv[0]);
        return 1;
    } 

    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);
    
	int keep_alive = 1;
    socket.setsockopt(ZMQ_TCP_KEEPALIVE, &keep_alive, sizeof(keep_alive));
    
    int keep_alive_idle = 180;
    std::cout << "keep_alive " << keep_alive_idle << "\n";
    socket.setsockopt(ZMQ_TCP_KEEPALIVE_IDLE, &keep_alive_idle, sizeof(keep_alive_idle));

    int keep_alive_intv = 10;
    std::cout << "keep_alive interval " << keep_alive_intv << "\n";
    socket.setsockopt(ZMQ_TCP_KEEPALIVE_INTVL, &keep_alive_intv, sizeof(keep_alive_intv));

    int keep_alive_cnt = 6;
    std::cout << "keep_alive count " << keep_alive_cnt << "\n";
    socket.setsockopt(ZMQ_TCP_KEEPALIVE_CNT, &keep_alive_cnt, sizeof(keep_alive_cnt));

    std::string addr(argv[1]);
    std::cout << "Connecting to hello world server … " <<  addr << std::endl;
     
    socket.connect(addr.c_str());

    //  Do 10 requests, waiting each time for a response
    for (int request_nbr = 0; request_nbr != 100; request_nbr++) {
        zmq::message_t request (5);
        memcpy (request.data (), "Hello", 5);
        std::cout << "Sending Hello " << request_nbr << "…" << std::endl;
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
        std::cout << "Received World " << request_nbr << std::endl;
        std::string str((char*)reply.data(), reply.size());

        std::cout << str << std::endl;
    
        std::this_thread::sleep_for(std::chrono::seconds(2));

    }

    return 0;


/*
 *    int sockfd = 0, n = 0;
 *    char recvBuff[1024];
 *    struct sockaddr_in serv_addr; 
 *
 *    if(argc != 3)
 *    {
 *        printf("\n Usage: %s <ip of server> <port>\n",argv[0]);
 *        return 1;
 *    } 
 *
 *    int port;
 *    try {
 *        port = std::stoi(argv[2]);
 *    }
 *    catch (std::exception& e) {
 *        std::cout << "second argument port is not int." << std::endl;
 *        return 1;
 *    }
 *
 *    memset(recvBuff, '0',sizeof(recvBuff));
 *    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
 *    {
 *        printf("\n Error : Could not create socket \n");
 *        return 1;
 *    } 
 *
 *    memset(&serv_addr, '0', sizeof(serv_addr)); 
 *
 *    serv_addr.sin_family = AF_INET;
 *    serv_addr.sin_port = htons(port); 
 *
 *    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
 *    {
 *        printf("\n inet_pton error occured\n");
 *        return 1;
 *    } 
 *
 *    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
 *    {
 *       printf("\n Error : Connect Failed \n");
 *       return 1;
 *    } 
 *    
 *    int val = 1;
 *    setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &val, sizeof val);
 *
 *    while ( (n = ::read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
 *    {
 *        recvBuff[n] = 0;
 *        if(fputs(recvBuff, stdout) == EOF)
 *        {
 *            printf("\n Error : Fputs error\n");
 *        }
 *    } 
 *
 *    if(n < 0)
 *    {
 *        printf("\n Read error \n");
 *    } 
 *
 */

 //   return 0;
}
