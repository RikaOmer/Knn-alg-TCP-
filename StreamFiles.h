#ifndef UNTITLED60_STR_H
#define UNTITLED60_STR_H
#include <string>
#include <map>
#include <list>
#include <vector>
using namespace std;

class StreamFiles
{
public:
    map<string, list<vector<double>>> dataSetMake(string fname);
    list<string> dataMake(string fname);
    bool canOpen(string fname);
};
#endif 
