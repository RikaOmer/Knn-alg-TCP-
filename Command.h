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
    DefaultIO *dio;

public:
    string description;
    virtual void execute() = 0;
    Command(DefaultIO *dio)
    {
        this->dio = dio;
    }
};

class UploadCommand : public Command
{
public:
    list<string> *data;
    map<string, list<vector<double>>> *dataSet;
    UploadCommand(DefaultIO *dio, list<string> *data,map<string, list<vector<double>>> *dataSet);
    void execute();
};

class SettingsCommand : public Command
{
private:
    int *k;
    string *dm;

public:
    SettingsCommand(DefaultIO *dio, int *k, string *dm);
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
    AlgorithmCommand(DefaultIO *dio, int k, string dm, list<string> data, map<string, list<vector<double>>> dataSet, vector<string> *names);
    void execute();
};

class ResultsCommand : public Command
{
private:
    vector<string> names;
    list<string> data;

public:
    ResultsCommand(DefaultIO *dio, vector<string> names, list<string> data);
    void execute();
};

class DResultCommand : public Command
{
private:
    vector<string> names;
    list<string> data;

public:
    DResultCommand(DefaultIO *dio, vector<string> names, list<string> data);
    static void WriteToFile(string path,vector<string> names);
    void execute();
};

class ExitCommand : public Command
{
public:
    bool *flag;
    ExitCommand(DefaultIO *dio, bool *flag);
    void execute();
};

#endif