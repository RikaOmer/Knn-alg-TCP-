#include "CLI.h"

using namespace std;

void CLI::start()
{
    while (flag)
    {
        int option = menu();
        commands[option]->execute();
    }
}

CLI::CLI(SocketIO *dio)
{
    this->dio = dio;
    this->flag = true;
    commands.push_back(new UploadCommand(dio, &data, &dataSet));
    commands.push_back(new SettingsCommand(dio, &k, &dm));
    commands.push_back(new AlgorithmCommand(dio, k, dm, data, dataSet, &names));
    commands.push_back(new ResultsCommand(dio, names, data));
    commands.push_back(new DResultCommand(dio, names, data));
    commands.push_back(new ExitCommand(dio, &flag));
}

int CLI::menu()
{
    dio->write("Welcome to the KNN Calssifier Server.\nPlease choose an option:\n");
    for (Command *command : commands)
    {
        dio->write(command->description);
    }
    string option = dio->read();
    return stoi(option) == 8 ? 5 : stoi(option) - 1;
} 
