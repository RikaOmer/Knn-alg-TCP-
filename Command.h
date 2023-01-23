#ifndef COMMAND
#define COMMAND

#include "DefaultIO.h"
#include <string>
#include "StreamFiles.h"
#include "Knn.h"
#include <iostream>
#include <fstream>
#include <thread>
using namespace std;

class Command
{
protected:
    SocketIO *dio;

public:
    string description;
    string menu;
    virtual void execute() = 0;
    Command(SocketIO *dio)
    {
        this->dio = dio;
    }
};

class UploadCommand : public Command
{
public:
    list<string> *data;
    map<string, list<vector<double>>> *dataSet;
    UploadCommand(SocketIO *dio, list<string> *data,map<string, list<vector<double>>> *dataSet, string menu);
    void execute();
};

class SettingsCommand : public Command
{
private:
    int *k;
    string *dm;

public:
    SettingsCommand(SocketIO *dio, int *k, string *dm, string menu);
    void execute();
};

class AlgorithmCommand : public Command
{
private:
    int k;
    string dm;
    list<string> data;
    vector<string> *names;
    map<string, list<vector<double>>> dataSet;

public:
    AlgorithmCommand(SocketIO *dio, int k, string dm, list<string> data, map<string, list<vector<double>>> dataSet, vector<string> *names, string menu);
    void execute();
};

class ResultsCommand : public Command
{
private:
    vector<string> names;
    list<string> data;

public:
    ResultsCommand(SocketIO *dio, vector<string> names, list<string> data, string menu);
    void execute();
};

class DResultCommand : public Command
{
private:
    vector<string> names;
    list<string> data;

public:
    DResultCommand(SocketIO *dio, vector<string> names, list<string> data, string menu);
    static void WriteToFile(string path,vector<string> names);
    void execute();
};

class ExitCommand : public Command
{
public:
    bool *flag;
    ExitCommand(SocketIO *dio, bool *flag);
    void execute();
};

#endif