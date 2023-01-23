#include <iostream>
#include "Command.h"
#include "CLI.h"

UploadCommand::UploadCommand(SocketIO *dio, list<string> *data, map<string, list<vector<double>>> *dataSet, string menu) : Command(dio)
{
    this->data = data;
    this->dataSet = dataSet;
    this->description = "1. upload an uncalssified csv data file\n";
    this->menu = menu;
}
void UploadCommand::execute()
{
    dio->write("Please upload your local train CSV file.\n");
    *dataSet = StreamFiles().dataSetMake(dio->read()); // read classified file
    dio->write("Upload complete.\n Please upload your local test CSV file.\n");
    *data = StreamFiles().dataMake(dio->read()); // read unclassified file
    dio->write("Upload complete.\n" + menu);
    return;
}
SettingsCommand::SettingsCommand(SocketIO *dio, int *k, string *dm, string menu) : Command(dio)
{
    this->description = "2. algorithm settings\n";
    this->k = k;
    this->dm = dm;
    this->menu = menu;
}
void SettingsCommand::execute()
{
    dio->write("The current KNN parameters are: K = " + to_string(*k) + ", distance metric = " + *dm + "\n");
    string input = dio->read();
    if (!input.compare("\n") == 0)
    {
        int ktemp = stoi(input.substr(0, input.find(" ")));
        string dmtemp = input.substr(input.find(" ") + 1, input.length());
        // ------------------ check if valid ---------------------------------------
        *k = ktemp;
        *dm = dmtemp;
    }
    dio->write(menu);
}
AlgorithmCommand::AlgorithmCommand(SocketIO *dio, int k, string dm, list<string> data, map<string, list<vector<double>>> dataSet, vector<string> *names, string menu) : Command(dio)
{
    this->description = "3. classify data\n";
    this->k = k;
    this->dm = dm;
    this->data = data;
    this->dataSet = dataSet;
    this->names = names;
    this->menu = menu;
}
void AlgorithmCommand::execute()
{
    if (data.empty())
    {
        dio->write("Please upload data\n" + menu);
        return;
    }

    *names = Knn().fullKnnAlgo(data, k, dataSet, dm);
    dio->write("Classifying data complete\n" + menu);
}
ResultsCommand::ResultsCommand(SocketIO *dio, vector<string> names, list<string> data, string menu) : Command(dio)
{
    this->description = "4. display results\n";
    this->names = names;
    this->data = data;
    this->menu = menu;
}
void ResultsCommand::execute()
{
    if (data.empty())
    {
        dio->write("Please upload data\n"+ menu);
        return;
    }
    else if (names.empty())
    {
        dio->write("Please classify data\n"+ menu);
        return;
    }
    int counter = 1;
    string output = "";
    for (string n : names)
    {
        output += to_string(counter) + "\t" + n + "\n";
        counter++;
    }
    output += "Done.\n";
    dio->write(output + menu);
}

DResultCommand::DResultCommand(SocketIO *dio, vector<string> names, list<string> data, string menu) : Command(dio)
{
    this->description = "5. download results\n";
    this->names = names;
    this->data = data;
    this->menu = menu;
}
void DResultCommand::execute()
{
    if (data.empty())
    {
        dio->write("Please upload data\n"+menu);
        return;
    }
    else if (names.empty())
    {
        dio->write("Please classify data\n"+menu);
        return;
    }
    string filePath = dio->read();
    // new thread
    // thread t(ref(WriteToFile), ref(filePath), ref(names));
    // t.detach();
    WriteToFile(filePath, names);
}
void DResultCommand::WriteToFile(string path, vector<string> names)
{
    fstream file_out;
    int counter = 1;
    file_out.open(path, std::ios_base::out);
    if (!file_out.is_open())
    {
        cout << "failed to open " << path << '\n';
    }
    else
    {
        for (string n : names)
        {
            // write to file in file path
            file_out << counter << "\t" << n << endl;
            counter++;
        }
        file_out.close();
    }
}

ExitCommand::ExitCommand(SocketIO *dio, bool *flag) : Command(dio)
{
    this->description = "8. exit\n";
    this->flag = flag;
}
void ExitCommand::execute()
{
    *flag = false;
}
