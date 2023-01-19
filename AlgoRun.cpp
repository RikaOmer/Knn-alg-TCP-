#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include "Knn.h"
#include "VectorDistance.h"
#include "StreamFiles.h"
#include "AlgoRun.h"

using namespace std;

vector<string> AlgoRun::fullKnnAlgo(list<string> userVector, int k, map<string, list<vector<double>>> dataSet, string distanceFunc)
{
    vector<string> result;
    for (string s : userVector)
    {
        result.push_back(setKnnAlgo(s, k, dataSet, distanceFunc));
    }
    return result;
}

string AlgoRun::setKnnAlgo(string userVector, int k, map<string, list<vector<double>>> dataSet, string distanceFunc)
{
    VectorDistance check;
    vector<double> vectorDouble = check.createVector(userVector);
    if (vectorDouble.size() != dataSet.begin()->second.begin()->size())
    {
        cout << "wrong length of vector" << endl;
    }
    else
    {
        dataSet = check.distanceCalc(dataSet, vectorDouble, distanceFunc);
        Knn knn;
        string name = knn.KnnAlgo(dataSet, k);
        return name;
    }
    return ("error");
}
