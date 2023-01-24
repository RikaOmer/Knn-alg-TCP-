#include "CLI.h"

using namespace std;

void CLI::start()
{
    //print menu
    string output;
    string menu = CLI::menu();
    dio->write(menu);
    int option = 1;
    bool inflag = true;
    while (flag)
    {
        string get = dio->read();
        for (int i = 0; i < get.size(); i++) {
            if(!isdigit(get[i])){
                inflag = false;
            }
        } 
        if(inflag == false){
            dio->write("invalid input\n"+menu);
            inflag = true;
        } else {
        option = stoi(get);
        if(option > 8 || option < 1 || option == 6 || option == 7){
            dio->write("invalid input\n" + menu);
        }
        else if(option != 8){
            option = option -1;
            output = commands[option]->execute();
            dio->write(output + menu);
         }
         else{
            output = commands[5]->execute();
            dio->write(output);
         }
        }
    }
}

CLI::CLI(SocketIO *dio)
{
    this->dio = dio;
    this->flag = true;
    commands.push_back(new UploadCommand(dio, &data, &dataSet));
    commands.push_back(new SettingsCommand(dio, &k, &dm));
    commands.push_back(new AlgorithmCommand(dio, &k, &dm, &data, &dataSet, &names));
    commands.push_back(new ResultsCommand(dio, &names, &data));
    commands.push_back(new DResultCommand(dio, &names, &data));
    commands.push_back(new ExitCommand(dio, &flag));
}

string CLI::menu()
{
    string printMenu = "Welcome to the KNN Calssifier Server. Please choose an option:\n";
    for (Command *command : commands)
    {
        printMenu = printMenu + command->description;
    }
    return printMenu;
}
