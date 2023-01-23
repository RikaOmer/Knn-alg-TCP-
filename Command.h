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
    virtual string execute() = 0;
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
    UploadCommand(SocketIO *dio, list<string> *data,map<string, list<vector<double>>> *dataSet);
    string execute();
};

class SettingsCommand : public Command
{
private:
    int *k;
    string *dm;

public:
    SettingsCommand(SocketIO *dio, int *k, string *dm);
    string execute();
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
    AlgorithmCommand(SocketIO *dio, int k, string dm, list<string> data, map<string, list<vector<double>>> dataSet, vector<string> *names);
    string execute();
};

class ResultsCommand : public Command
{
private:
    vector<string> names;
    list<string> data;

public:
    ResultsCommand(SocketIO *dio, vector<string> names, list<string> data);
    string execute();
};

class DResultCommand : public Command
{
private:
    vector<string> names;
    list<string> data;

public:
    DResultCommand(SocketIO *dio, vector<string> names, list<string> data);
    static void WriteToFile(string path,vector<string> names);
    string execute();
};

class ExitCommand : public Command
{
public:
    bool *flag;
    ExitCommand(SocketIO *dio, bool *flag);
    string execute();
};

#endif