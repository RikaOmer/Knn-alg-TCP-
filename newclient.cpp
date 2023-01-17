#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main(int length,char** args)
{
    const string ipAddress =(args[1]);
    const int port= atoi(args[2]);
    //	Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        cout << "connection error";
        return 1;
    }

    //	Create a hint structure for the server we're connecting with

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Connect to the server on the socket
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        cout << "connection error";
        return 1;
    }

    //	While loop:
    char buf[4096];
    string userInput;

    do {
        //		Enter lines of text
        getline(cin, userInput);
        if(userInput == "-1"){
            break;
        }
        //		Send to server
        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
        if (sendRes == -1)
        {
            cout << "Messege didnt sent to the server";
            continue;
        }

        //		Wait for response
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cout << "There was an error getting response from server\r\n";
        }
        else
        {
            //		Display response
            cout << string(buf, bytesReceived) << "\r\n";
        }
    } while(true);

    //	Close the socket
    close(sock);

    return 0;
}