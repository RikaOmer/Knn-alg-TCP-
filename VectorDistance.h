#ifndef UNTITLED60_VCT_H
#define UNTITLED60_VCT_H
#include <map>
#include <list>
#include <vector>
#include <string>
using namespace std;

class VectorDistance
{
public:
    double minkowskiDistance(vector<double> x, vector<double> y);
    double euclideanDistance(vector<double> x, vector<double> y);
    double manhattanGeometry(vector<double> x, vector<double> y);
    double chebyshevDistance(vector<double> x, vector<double> y);
    double canberraDistance(vector<double> x, vector<double> y);
    map<string,list<vector<double>>>distanceCalc(map<string,list<vector<double>>> dataSet, vector<double> compVector, string compFunction);
    int convertFunctionNum(string functionName);
    int validCheck(string str);
    vector<double> createVector(string str);
};
#endif // UNTITLED60_EX1_H
