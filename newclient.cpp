#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "DefaultIO.h"
#include "DefaultIO.cpp"

using namespace std;

int main(int length, char **args)
{
    const string ipAddress = (args[1]);
    const int port = atoi(args[2]);
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
    SocketIO *socketio;
    socketio = new SocketIO(sock);
    //	Connect to the server on the socket
    int connectRes = connect(sock, (sockaddr *)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        cout << "connection error";
        return 1;
    }
    //	While loop:
    // char buf[4096];
    string userInput;
    string getRead;
    do
    {
        //		print and send
        getRead = socketio->read();
        if(getRead == "break"){
            break;
        }
        cout << getRead;
        getline(cin, userInput);
        if(!userInput.empty()){
        socketio->write(userInput);
        }
        else{
            socketio->write("empty");
        }
    } while (true);
    //	Close the socket
    close(sock);

    return 0;
}