#ifndef UNTITLED60_ALGO_H
#define UNTITLED60_ALGO_H
#include <string>
#include <vector>
#include <map>
#include <list>
using namespace std;

class AlgoRun
{
public:
    vector<string> AlgoRun::fullKnnAlgo(list<string> userVector, int k, map<string, list<vector<double>>> dataSet, string distanceFunc);
    string AlgoRun::setKnnAlgo(string userVector, int k, map<string, list<vector<double>>> dataSet, string distanceFunc);
};
#endif