#include <iostream>
#include "vector"
#include "cmath"
#include <map>
#include <list>
#include <string>
#include "Knn.h"
using namespace std;

struct nameDistance
{
    string name;
    double distance;
};

string Knn::getMostNames(list<nameDistance> arrayDistance){ 
    map<string,int>setMost;
    map<string,int>::iterator it;
    string name;
    int max;
    for (auto listIter = begin(arrayDistance); listIter != end(arrayDistance); ++listIter)
    {
        it = setMost.find(listIter->name);  
        if (it != setMost.end()){
            it->second = it->second+1;
        }
        else{
            setMost.insert(pair<string,int>(listIter->name,1));
        }
    }
    name = setMost.begin()->first;
    max = setMost.begin()->second;
    for (it = setMost.begin(); it != setMost.end(); ++it)
    {
        if(it->second > max) {
            name = it->first;
        }
    }
    return name;
}

string Knn::KnnAlgo(map<string, list<vector<double>>> dataSet, int k){
    int counter = 0;
    list<nameDistance> minDistance;
    list<nameDistance>::iterator bigest;
    nameDistance copy, swap;
    std::map<string,list<vector<double>>>::iterator it;
        for(auto it = begin(dataSet); it != end(dataSet); ++it)
        {
            
            for (std::list<vector<double>>::iterator iter = it->second.begin(); iter != it->second.end(); ++iter){
            
                vector<double> vec = (*iter); //vector for check
                if (counter < k){
                    copy.distance =vec.back();
                    copy.name = it->first;
                    minDistance.push_back(copy);
                    counter++;
                    } else {
                        copy.distance = vec.back();
                        copy.name = it->first;
                        swap = copy;
                        for (auto listIter = begin(minDistance); listIter != end(minDistance); ++listIter)
                        {
                            if (copy.distance < listIter->distance)
                            {
                            copy = *listIter;
                            bigest = listIter;
                            }
                        }
                        if(copy.distance != vec.back()){
                            bigest = minDistance.erase(bigest);
                            minDistance.push_back(swap);
                        }
                }
            }
        }
         string name = Knn::getMostNames(minDistance);
        return name;
}