#ifndef UNTITLED60_KNN_H
#define UNTITLED60_KNN_H
#include <string>
#include <vector>
#include <map>
#include <list>
using namespace std;

class Knn
{
public:
struct nameDistance
{
    string name;
    double distance;
};
    string getMostNames(list<nameDistance> arrayDistance);
    string KnnAlgo(map<string, list<vector<double>>> dataSet, int k);
    vector<string> fullKnnAlgo(list<string> userVector, int k, map<string, list<vector<double>>> dataSet, string distanceFunc);
    string setKnnAlgo(string userVector, int k, map<string, list<vector<double>>> dataSet, string distanceFunc);
};
#endif