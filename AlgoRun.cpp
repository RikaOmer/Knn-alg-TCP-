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

string AlgoRun::setKnnAlgo(string userVector, int k, string fileName, string distanceFunc){
    map<string, list<vector<double>>> dataSet;
    StreamFiles streamer;
    VectorDistance vectorCalculator;
    dataSet = streamer.dataMake(fileName);  
    string vectorString;
    if (vectorCalculator.validCheck(vectorString) == 1)
    {
        cout << "invalid input"<<endl;
    } else {
         vector<double> vectorDouble = vectorCalculator.createVector(userVector);
         if (vectorDouble.size() != dataSet.begin()->second.begin()->size())
         {
             cout << "wrong length of vector"<<endl;
             
         } else {
             
                dataSet =vectorCalculator.distanceCalc(dataSet,vectorDouble, distanceFunc);
                Knn knn;
                string name = knn.KnnAlgo(dataSet,k);
                return name;
                }
            }
     return ("error");
    }



