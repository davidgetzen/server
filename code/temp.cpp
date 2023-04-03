#include <iostream>
#include <WS2tcpip.h>


#pragma comment(lib, "ws2_32.lib")

using namespace std;

void main(){

    //Step 1. Initialize winsock

    //Below: instantiating a WSADATA struct, which is a struct
    //dedicated to containing information about the windows sockets
    //implementation
    WSADATA wsData;
    //Below:
    WORD ver = MAKEWORD(2,2);
    //Below
    int wsOk = WSAStartup(ver, &wsData);

    if (wsOk != 0){
        cerr << "Can't initialize winsock! Quitting!" << endl; 
        return; 
    }


    //Create a socket (just an endpoint, matched with a port and an IP address, a file descriptor/number in unix systems)
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET){
        cerr << "can't create a socket! Quitting" << endl;
        return; 
    }

    //Bind the IP address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;
    //Tell winsock the socket is for listening 

    //Wait for connection

    //Close listening socket 

    //While loop: accept and echo message back to client

    //Close the socket

    //Shut down winsock


    return;
}