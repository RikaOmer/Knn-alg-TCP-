#include <string>
#include <vector>
#include "Command.h"
#include "DefaultIO.h"

using namespace std;

class CLI
{
private:
    bool flag;
    DefaultIO *dio;
    list<string> data = {};
    map<string, list<vector<double>>> dataSet = {};
    vector<Command *> commands;
    string filename;
    int k = 5;
    string dm = "AUC";
    vector<string> names = {};

    int menu();

public:
    CLI(DefaultIO *dio, string filename);
    void start();
};