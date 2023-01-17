#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#include <map>
#include "StreamFiles.h"
 
using namespace std;

map<string, list<vector<double>>> StreamFiles::dataMake(string fname) 
{               
 map<string, list<vector<double>>> dataSet;  //dataset that we create and return
list<vector<double>> content;   //list of vectors
vector<string> getRow;          //the first vector we get in string
vector<double> convertRow;      //the converted vector
std::map<string,list<vector<double>>>::iterator it; //serch for existing element
string line, word;
fstream file (fname, ios::in);
if(file.is_open())
{
    while(getline(file, line))
    {
        getRow.clear();
        convertRow.clear();
        stringstream str(line);
        while(getline(str, word, ',')){
        getRow.push_back(word);
        }
        for (auto it = begin(getRow); it != end(getRow); ++it) {
        if(*it != getRow.back())
        convertRow.push_back(stod(*it));
        }
        try
        {
            it = dataSet.find(getRow.back());
            if(dataSet.count(getRow.back()) == 0){
                dataSet.insert(pair<string, list<vector<double>>>(getRow.back(), content));
            } else {
                it->second.push_back(convertRow);
            }
        }
        catch(const std::exception& e)
        {
            cout << "error\n";
        }
    }
}
else
    cout<<"Could not open the file\n";
return dataSet;
}
