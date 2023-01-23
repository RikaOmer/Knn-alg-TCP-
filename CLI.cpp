#include "CLI.h"

using namespace std;

void CLI::start()
{
    //print menu
    string menu = CLI::menu();
    dio->write(menu);
    int option = 1;
    while (flag)
    {
        string get = dio->read();
        option = stoi(get) == 8 ? 5 : stoi(get) - 1;
        commands[option]->execute();
    }
}

CLI::CLI(SocketIO *dio)
{
    this->dio = dio;
    this->flag = true;
    string menu = CLI::menu();
    commands.push_back(new UploadCommand(dio, &data, &dataSet, menu));
    commands.push_back(new SettingsCommand(dio, &k, &dm, menu));
    commands.push_back(new AlgorithmCommand(dio, k, dm, data, dataSet, &names, menu));
    commands.push_back(new ResultsCommand(dio, names, data, menu));
    commands.push_back(new DResultCommand(dio, names, data, menu));
    commands.push_back(new ExitCommand(dio, &flag));
}

string CLI::menu()
{
    string printMenu = "Welcome to the KNN Calssifier Server.\nPlease choose an option:\n";
    for (Command *command : commands)
    {
        printMenu = printMenu + command->description;
    }
    return printMenu;
}
