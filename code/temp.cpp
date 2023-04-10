#include <iostream>
//#define _WIN32_WINNT_WIN10 0x0A00
//#define _WIN32_WINNT 0x502
#include <ws2tcpip.h>
#include <winsock2.h>

// g++ temp.cpp -o test.exe -lwsock32 -lWs2_32



#pragma comment(lib, "ws2_32.lib")
// #define _WIN32_WINNT 0x0501
// #define _WIN32_WINNT 0x501
// #define _WIN32_WINNT 0x0501
using namespace std;

int main(){

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
        return -1; 
    }


    //Create a socket (just an endpoint, matched with a port and an IP address, a file descriptor/number in unix systems)
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET){
        cerr << "can't create a socket! Quitting" << endl;
        return -1; 
    }

    //Bind the IP address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    //Below: we want to bind to any address (could also use inet_pton)
    hint.sin_addr.S_un.S_addr = INADDR_ANY; 

    //binding the socket to the network
    bind(listening, (sockaddr*)&hint, sizeof(hint));

     //Tell Winsock the socket is for listening
     listen(listening, SOMAXCONN);

    //Wait for connection

    //below: creating an input socket address
    sockaddr_in client;
    int clientSize = sizeof(client);

    //listening for connection, below is where connection happens
    SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

    //Below: printing cetain data about socket object 
    char host[NI_MAXHOST]; // client's remote name 
    char service[NI_MAXHOST]; // service (i.e. port) the client is connected on

    ZeroMemory(host, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    ZeroMemory(service, NI_MAXHOST);

    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0){
        cout << host << " connected on port " << service << endl;
    }else{
        // do something else
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << 
            ntohs(client.sin_port) << endl; 
    }

    // if (clientSocket == INVALID_SOCKET) do something

    //Close listening socket 
    closesocket(listening);

    //While loop: accept and echo message back to client
    char buf[4096]; 

    while (true) 
    {
        ZeroMemory(buf, 4096);
        // Wait for client to send data 
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == SOCKET_ERROR){
            cerr << "Error in recv(). Quitting" << endl;
            break;
        }
        if (bytesReceived == 0){
            cout << "Client disconnected " << endl;
            break;
        }
        //bytesReceived+1 because it automatically send zero buffer out
        // Echo message back to client 
        send(clientSocket, buf, bytesReceived + 1, 0);
    }
    //Close the socket
    closesocket(clientSocket);

    //Shut down winsock
    WSACleanup();


    return 0;
}
