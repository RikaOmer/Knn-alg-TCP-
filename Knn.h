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
};
#endif