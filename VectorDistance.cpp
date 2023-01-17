#include <iostream>
#include "vector"
#include "VectorDistance.h"
#include "cmath"
#include <map>
#include <list>
#include <string>
#include <cstring>
using namespace std;
string distanceArray[] = {"AUC","MAN","CHB","CAN","MIN"};

int VectorDistance::validCheck(string str)
{
    for (char a : str)
    {
        if(!isdigit(a) && !isspace(a)){
            return 1;
        }
    }
    return 0;
}
vector<double> VectorDistance::createVector(string str)
{
    char *end;
    vector<double> thisVector;
    double number;
    char * pch;
    char *str1 = new char[str.length() + 1];
    strcpy(str1, str.c_str());
    pch = strtok(str1," ");
    while (pch != NULL)
    {
    number = strtod(pch, &end);
    thisVector.push_back(number);
    pch = strtok (NULL, " ");
    }
    return thisVector;
}

int VectorDistance::convertFunctionNum(string functionName){
    for (size_t i = 0; i < distanceArray->length(); i++)
    {
        if (distanceArray[i] == functionName)
        {
            return i+1;
        }
    }
    return 0;
}

//function that calculate the distance between every vector to the compere vector and add the distance to the last function
map<string,list<vector<double>>>VectorDistance::distanceCalc(map<string,list<vector<double>>> dataSet, vector<double> compVector, string compFunction){

    std::map<string,list<vector<double>>>::iterator it;
    double dist;
    int func = convertFunctionNum(compFunction); // convert the name of the distance function to int

    for(it = dataSet.begin(); it != dataSet.end(); ++it)
    {
        for (std::list<vector<double>>::iterator iter = it->second.begin(); iter != it->second.end(); ++iter){
            vector<double> vec = (*iter); //need to sent him
            switch(func){
            case 1:
            dist = euclideanDistance(vec, compVector);
            break;
            case 2:
            dist = manhattanGeometry(vec, compVector);
            break;
            case 3:
            dist = chebyshevDistance(vec, compVector);
            break;
            case 4:
            dist = canberraDistance(vec, compVector);
            break;
            case 5:
            dist = minkowskiDistance(vec, compVector);
            break;
            default:
            dist = -1; // error
            }

            (*iter).push_back(dist);
        }
    }
    return dataSet;
}

double VectorDistance::euclideanDistance(vector<double> x, vector<double> y)
{
    double result = 0;
    double vec = 0;
    for (int i = 0; i < (int)x.size(); i++)
    {
        vec = (x[i] - y[i]);
        vec = pow(vec, 2);
        result = result + vec;
    }
    result = sqrt(result);

    return result;
}

double VectorDistance::manhattanGeometry(vector<double> x, vector<double> y)
{
    double result = 0;
    double vec = 0;
    for (int i = 0; i < (int)x.size(); i++)
    {
        vec = (x[i] - y[i]);
        result = result + abs(vec);
    }
    return result;
}
double VectorDistance::chebyshevDistance(vector<double> x, vector<double> y)
{
    double max = 0;
    double distance = 0;
    for (int i = 0; i < (int)x.size(); i++)
    {
        distance = abs(x[i] - y[i]);
        if (distance > max)
        {
            max = distance;
        }
    }
    return max;
}
double VectorDistance::canberraDistance(vector<double> x, vector<double> y)
{
    double result = 0;
    double sum = 0;
    double vec = 0;
    for (int i = 0; i < (int)x.size(); i++)
    {
        vec = abs(x[i] - y[i]);
        sum = abs(x[i]) + abs(y[i]);
        result = result + (vec / sum);
    }
    return result;
}

// this function use p = 2;
double VectorDistance::minkowskiDistance(vector<double> x, vector<double> y)
{
    return euclideanDistance(x, y);
}