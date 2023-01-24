#include <iostream>
#include "Command.h"
#include "CLI.h"
#include "VectorDistance.h"

UploadCommand::UploadCommand(SocketIO *dio, list<string> *data, map<string, list<vector<double>>> *dataSet) : Command(dio)
{
    this->data = data;
    this->dataSet = dataSet;
    this->description = "1. upload an uncalssified csv data file\n";
}
string UploadCommand::execute()
{
    dio->write("Please upload your local train CSV file.\n");
    *dataSet = StreamFiles().dataSetMake(dio->read()); // read classified file
    dio->write("Upload complete.\n Please upload your local test CSV file.\n");
    *data = StreamFiles().dataMake(dio->read()); // read unclassified file
    return "Upload complete.\n";
}

SettingsCommand::SettingsCommand(SocketIO *dio, int *k, string *dm) : Command(dio)
{
    this->description = "2. algorithm settings\n";
    this->k = k;
    this->dm = dm;
}
string SettingsCommand::execute()
{
    string output;
    bool flag = true;
    dio->write("The current KNN parameters are: K = " + to_string(*k) + ", distance metric = " + *dm + "\n");
    string input = dio->read();
    if (!input.compare("empty") == 0)
    {
        string ktemp = input.substr(0, input.find(" "));
        string dmtemp = input.substr(input.find(" ") + 1, input.length());
        VectorDistance vec;
        for (int i = 0; i < ktemp.size(); i++) {
            if(!isdigit(ktemp[i])){
                output = "invalid value for K\n";
                flag = false;
            }
        }   
        if (vec.convertFunctionNum(dmtemp) == 0)
        {
            output += "invalid value for metric\n";
            flag = false;
        }
        if (flag == false)
        {
            return output;
        }
        *k = stoi(ktemp);
        *dm = dmtemp;
    }
    return "";
}

AlgorithmCommand::AlgorithmCommand(SocketIO *dio, int *k, string* dm, list<string> *data, map<string, list<vector<double>>> *dataSet, vector<string> *names) : Command(dio)
{
    this->description = "3. classify data\n";
    this->k = k;
    this->dm = dm;
    this->data = data;
    this->dataSet = dataSet;
    this->names = names;

}
string AlgorithmCommand::execute()
{
    if (data->empty())
    {
        return "Please upload data\n";
    }

    *names = Knn().fullKnnAlgo(*data, *k, *dataSet, *dm);
    return "Classifying data complete\n";
}

ResultsCommand::ResultsCommand(SocketIO *dio, vector<string>* names, list<string>* data) : Command(dio)
{
    this->description = "4. display results\n";
    this->names = names;
    this->data = data;

}
string ResultsCommand::execute()
{
    if (data->empty())
    {
        return "Please upload data\n";
    }
    else if (names->empty())
    {
        return"Please classify data\n";
    }
    int counter = 1;
    string output = "";
    int size = names->size();
    int i = 0;
    for (; i < size ; i++)
    {
        output += to_string(counter) + "\t" + names->at(i) + "\n";
        counter++;
    }
    output += "Done.\n";
    return output;
}

DResultCommand::DResultCommand(SocketIO *dio, vector<string> *names, list<string> *data) : Command(dio)
{
    this->description = "5. download results\n";
    this->names = names;
    this->data = data;
}
string DResultCommand::execute()
{
    if (data->empty())
    {
        return "Please upload data\n";
    }
    else if (names->empty())
    {
        return "Please classify data\n";
    }
    string filePath = dio->read();
    // new thread
    // thread t(ref(WriteToFile), ref(filePath), ref(names));
    // t.detach();
    WriteToFile(filePath, *names);
    return "";
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
string ExitCommand::execute()
{
    *flag = false;
    return "break";
}
