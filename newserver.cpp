#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <string.h>
#include <string>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "AlgoRun.h"
#include <cctype>

using namespace std;
 
int main(int length,char** args)
{
    const int server_port = atoi(args[2]); // get port as a argument
    const string fileName = args[1]; //classified file
    // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening < 0)
    {
        perror("Can't create a socket! Quitting");
        return -1;
    }
 
    // Bind the ip address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(server_port); 
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    if(bind(listening, (sockaddr*)&hint, sizeof(hint)) < 0)
    {
        perror("error binding socket");
        return -1;
    }
    if (listen(listening, 5) < 0)
    {
        perror("error listening to a socket");
        return -1;
    }
 
    listen(listening, SOMAXCONN); // Tell Winsock the socket is for listening
    while (true)
    {
    // Wait for a connection
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
     if (clientSocket < 0)
    {
        perror("error accepting client");
        return -1;
    }
 
    // Close listening socket
    // close(listening); 
 
    // While loop: accept and echo message back to client
    char buf[4096];
 
    while (true)
    {
        memset(buf, 0, 4096);
 
        // Wait for client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            perror("Connection issue");
            break;
        }
 
        if (bytesReceived == 0)
        {
            perror("Client disconnected");
            break;
        }
 
        string getInfo = string(buf, 0, bytesReceived); // the information that recived from the client *****
        int i = 0;
        string funcName;
        
        

        while(isalpha(getInfo[i]) == 0){
            i++;
        }
        int j = i;
        string vectorString = getInfo.substr(0,i-1);
        while(isalpha(getInfo[i]) != 0){
            i++;
        }
        funcName = getInfo.substr(j,i-j);
        string kstr = getInfo.substr(i,getInfo.length()-i);
        int k = stoi(kstr);

        cout << vectorString << endl;
        cout << funcName << endl;
        cout << k << endl;
        cout << fileName << endl;
        AlgoRun runner;
        string messege = runner.setKnnAlgo(vectorString, k, fileName, funcName); 
        const int length = messege.length();
        char* char_array = new char[length + 1];
        strcpy(char_array, messege.c_str());

        // // Echo message back to client
        send(clientSocket, char_array, length + 1, 0);  // sent a message for client
        cout << messege << endl;
        // send(clientSocket, buf, bytesReceived + 1, 0); 
    }
    }
 
    // // Close the socket
    // close(clientSocket);
    return 0;
}