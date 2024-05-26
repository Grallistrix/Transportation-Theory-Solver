
#include <iostream>
#include <vector>
#include "MiddleManAlgorithm.h"

using namespace std;

int main()
{
    vector<vector<double>> referenceTable = {{12,6},{1,4},{3,-1}};
    vector<int> Popyt = {10,28,27};
    vector<int> Podaz = {20,30};

    MiddleManAlgorithm calc(Podaz,Popyt,referenceTable,true);
    calc.coutBetaAndAlpha();
    calc.coutTactic();
 
}

