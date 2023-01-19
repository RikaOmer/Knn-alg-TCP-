#include "DefaultIO.h"
#include <string>
#include "StreamFiles.h"
#include "Algorun.h"
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

    UploadCommand(DefaultIO *dio, list<string> *data) : Command(dio)
    {
        this->data = data;
        this->description = "1. upload an uncalssified csv data file\n";
    }
    void execute()
    {
        dio->write("Please upload your local train CSV file.\n");
        *data = StreamFiles().dataMake(dio->read()); // changeee !!!!!!
        dio->write("Upload complete.\n");
    }
};

class MacroCommand : public Command
{
protected:
    vector<Command *> commands;

public:
    MacroCommand(DefaultIO *dio) : Command(dio)
    {
    }
    void execute()
    {
        for (Command *command : commands)
        {
            command->execute();
        }
    }
};

class SettingsCommand : public Command
{
private:
    int *k;
    string *dm;

public:
    SettingsCommand(DefaultIO *dio, int *k, string *dm) : Command(dio)
    {
        this->description = "2. algorithm settings\n";
        this->k = k;
        this->dm = dm;
    }
    void execute()
    {
        dio->write("The current KNN parameters are:\n");
        dio->write("K = " + to_string(*k) + ", distance metric = " + *dm + "\n");
        string input = dio->read();
        if (!input.compare("\n") == 0)
        {
            int ktemp = stoi(input.substr(0, input.find(" ")));
            string dmtemp = input.substr(input.find(" ") + 1, input.length());
            // ------------------ check if valid ---------------------------------------
            *k = ktemp;
            *dm = dmtemp;
        }
    }
};

class AlgorithmCommand : public Command
{
private:
    int k;
    string dm;
    list<string> data;
    string fileName;
    vector<string> *names;

public:
    AlgorithmCommand(DefaultIO *dio, int k, string dm, list<string> data, string fileName, vector<string> *names) : Command(dio)
    {
        this->description = "3. classify data\n";
        this->k = k;
        this->dm = dm;
        this->data = data;
        this->fileName = fileName;
        this->names = names;
    }

    void execute()
    {
        if (data.empty())
        {
            dio->write("Please upload data\n");
            return;
        }
        *names = AlgoRun().setKnnAlgo(data, k, fileName, dm);
        dio->write("Classifying data complete\n");
    }
};

class ResultsCommand : public Command
{
private:
    vector<string> names;
    list<string> data;

public:
    ResultsCommand(DefaultIO *dio, vector<string> names, list<string> data) : Command(dio)
    {
        this->description = "4. display results\n";
        this->names = names;
        this->data = data;
    }

    void execute()
    {
        if (data.empty())
        {
            dio->write("Please upload data\n");
            return;
        }
        else if (names.empty())
        {
            dio->write("Please classify data\n");
            return;
        }
        int counter = 1;
        for (string d : data)
        {
            dio->write(to_string(counter) + "\t" + d + "\n");
            counter++;
        }
        dio->write("Done.\n");
    }
};

class DResultCommand : public Command
{
private:
    vector<string> names;
    list<string> data;

public:
    DResultCommand(DefaultIO *dio, vector<string> names, list<string> data) : Command(dio)
    {
        this->description = "4. display results\n";
        this->names = names;
        this->data = data;
    }

    void execute()
    {
        if (data.empty())
        {
            dio->write("Please upload data\n");
            return;
        }
        else if (names.empty())
        {
            dio->write("Please classify data\n");
            return;
        }
        string filePath = dio->read();
        // new thread
        std::thread(
            [](string path, list<string> data) -> void
            {
                fstream file_out;
                int counter = 1;
                file_out.open(path, std::ios_base::out);
                if (!file_out.is_open())
                {
                    // DELETE WHEN DONE !!!!! -----------------
                    cout << "failed to open " << path << '\n';
                }
                else
                {
                    for (string d : data)
                    {
                        // write to file in file path

                        file_out << counter << "\t" << d << endl;

                        counter++;
                    }
                }
            },
            filePath, data)
            .detach();
    }
};

class ExitCommand : public Command
{
public:
    bool *flag;
    ExitCommand(DefaultIO *dio, bool *flag) : Command(dio)
    {
        this->description = "8. exit\n";
        this->flag = flag;
    }
    void execute()
    {
        *flag = false;
    }
};