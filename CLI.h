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
    vector<Command *> commands;
    string filename;
    int k = 5;
    string dm = "EUC";
    vector<string> names = {};

    int menu();

public:
    CLI(DefaultIO *dio, string filename);
    void start();
};