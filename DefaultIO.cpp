#include <iostream>
#include "DefaultIO.h"
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

SocketIO::SocketIO(int clientSocket){
        this->clientSocket = clientSocket;
}
string SocketIO::read(){
        char buf[4096];
        memset(buf, 0, 4096);
 
        // Wait for client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            perror("Connection issue");
        }
 
        if (bytesReceived == 0)
        {
            perror("Client disconnected");
        }
        string getInfo = string(buf, 0, bytesReceived); // the information that recived from the client *****
        return getInfo;
    }

void SocketIO::write(string messege){
        const int length = messege.length();
        char* char_array = new char[length + 1];
        strcpy(char_array, messege.c_str());
        send(clientSocket, char_array, length + 1, 0);  // sent a message for client
    }