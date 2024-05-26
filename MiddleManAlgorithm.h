#pragma once

#include <iostream>
#include <vector>

using namespace std;

class MiddleManAlgorithm
{
	//Fields
public:
	vector<int> Alpha;
	vector<int> Beta;
	vector<vector<int>> Tactic;
	vector<vector<bool>> Lock;
	vector<vector<int>> Delta;
private:
	//Methods
public:
	MiddleManAlgorithm(vector<int>& Podaz, vector<int>& Popyt, vector<vector<double>>& Ref,bool delta_control);
	void coutBetaAndAlpha();
	void coutTactic();
	void compressTactic();
	// if delta control is true we are working on middleman problem and with false we are talking about transportation problem
	//Ref contains unit abs profit or transport cost depending on the problem accounted for
private:
	pair<int, int> findLowestUnlocked(vector<vector<double>>& Ref);
	pair<int, int> findHighestUnlocked(vector<vector<double>>& Ref);
	//Algorithm
//Fill tactic with loads based on lowest/highest element method
// 	   1. Find lowest/highest element in matrix that is not locked
// 	   2. Fill as much load as Popyt and Poda¿ related to it allow to
// 	   3. Lock it
//		Repeat to fill up table //[Popyt][Podaz]
//Flag1
 //calc Alphas and Betas
 //calc Deltas
 //check if deltas are all of the same sign dependant on the algorithm in question
//if not
	//compres tactic bu searching highest or lowest element
	// go to Flag1
//if yes return tactics table
	//calc cost or profit
};

