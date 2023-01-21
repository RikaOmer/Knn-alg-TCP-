#include <iostream>
#include "Command.h"

   UploadCommand::UploadCommand(DefaultIO *dio, list<string> *data,map<string, list<vector<double>>> *dataSet) : Command(dio)
    {
        this->data = data;
        this->dataSet = dataSet;
        this->description = "1. upload an uncalssified csv data file\n";
    }
    void UploadCommand::execute()
    {
        dio->write("Please upload your local train CSV file.\n");
        *dataSet = StreamFiles().dataSetMake(dio->read()); // read classified file
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        *data = StreamFiles().dataMake(dio->read()); // read unclassified file
        dio->write("Upload complete.\n");
    }
    SettingsCommand::SettingsCommand(DefaultIO *dio, int *k, string *dm) : Command(dio)
    {
        this->description = "2. algorithm settings\n";
        this->k = k;
        this->dm = dm;
    }
    void SettingsCommand::execute()
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
    AlgorithmCommand::AlgorithmCommand(DefaultIO *dio, int k, string dm, list<string> data, map<string, list<vector<double>>> dataSet, vector<string> *names) : Command(dio)
    {
        this->description = "3. classify data\n";
        this->k = k;
        this->dm = dm;
        this->data = data;
        this->dataSet = dataSet;
        this->names = names;
    }
    void AlgorithmCommand::execute()
    {
        if (data.empty())
        {
            dio->write("Please upload data\n");
            return;
        }

        *names = Knn().fullKnnAlgo(data, k, dataSet, dm);
        dio->write("Classifying data complete\n");
    }
    ResultsCommand::ResultsCommand(DefaultIO *dio, vector<string> names, list<string> data) : Command(dio)
    {
        this->description = "4. display results\n";
        this->names = names;
        this->data = data;
    }
    void ResultsCommand::execute()
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
        for (string n : names)
        {
            dio->write(to_string(counter) + "\t" + n + "\n");
            counter++;
        }
        dio->write("Done.\n");
    }

    
    DResultCommand::DResultCommand(DefaultIO *dio, vector<string> names, list<string> data) : Command(dio)
    {
        this->description = "4. display results\n";
        this->names = names;
        this->data = data;
    }
    void DResultCommand::execute()
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
        thread t(WriteToFile,filePath, names);
        t.detach();
    }
    void DResultCommand::WriteToFile(string path, list<string> names)
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


    ExitCommand::ExitCommand(DefaultIO *dio, bool *flag) : Command(dio)
    {
        this->description = "8. exit\n";
        this->flag = flag;
    }
    void ExitCommand::execute()
    {
        *flag = false;
    }


