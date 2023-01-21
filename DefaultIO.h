#ifndef DEFAULTIO
#define DEFAULTIO

#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
using namespace std;

class DefaultIO
{
public:
    virtual string read() const;
    virtual void write(string text);
    /* ... */
};


class SocketIO : public DefaultIO
{
private:
    int clientSocket;

public:

    SocketIO(int clientSocket);
    string read();
    void write(string text);
};

class StandardIO : public DefaultIO
{
public:
    string read(){
        string userInput;
        getline(cin, userInput);
        return userInput;
    }
    void write(string text){
        cout << text;
    }

};

#endif