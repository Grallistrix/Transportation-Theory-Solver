#include "MiddleManAlgorithm.h"
#include <iostream>
#include <vector>

using namespace std;

MiddleManAlgorithm::MiddleManAlgorithm(vector<int>& Podaz, vector<int>& Popyt, vector<vector<double>>& Ref, bool delta_control)
{
	int sum_check = 0;
	int Pop=0;
	int Pod=0;
		for (int a : Popyt)Pop += a;
		for (int a : Podaz)Pod += a;
		if (Pop != Pod) {
			Podaz.push_back(Pop);
			Popyt.push_back(Pod);
		}

	vector<bool> temp_bool;//initialize it with false
	vector<int> temp_int;//inirialize it with 0
	vector<double> temp_double;//initialize with 0
	for (int i = 0; i < Podaz.size(); i++) {
		temp_bool.push_back(false);
		temp_int.push_back(0);
		temp_double.push_back(0);
	}
	for (int k = 0; k < Popyt.size(); k++) { 
		this->Lock.push_back(temp_bool); 
		this->Tactic.push_back(temp_int);
		Delta.push_back(temp_int);
	}
	if (Pop != Pod) {
		for (int a = 0; a < Ref.size();a++)Ref[a].push_back(0);
		Ref.push_back(temp_double);
	}
	do
	{
		//Algorithm
//Fill tactic with loads based on lowest/highest element method
// 	   1. Find lowest/highest element in matrix that is not locked
		pair<int, int> temp_pair;
		if (delta_control)temp_pair = findHighestUnlocked(Ref);
		else temp_pair = findLowestUnlocked(Ref);
		// 	   2. Fill as much load as Popyt and Poda¿ related to it allow to
		if (Popyt[temp_pair.first] >= Podaz[temp_pair.second]) {
			this->Tactic[temp_pair.first][temp_pair.second] = Podaz[temp_pair.second];
			Popyt[temp_pair.first] -= Podaz[temp_pair.second]; Podaz[temp_pair.second] = 0;
		}
		else {
			this->Tactic[temp_pair.first][temp_pair.second] = Popyt[temp_pair.first];
			Podaz[temp_pair.second] -= Popyt[temp_pair.first]; Popyt[temp_pair.first] = 0;
		}
		if (Popyt[temp_pair.first] == 0)
			for (int i = 0; i < Podaz.size(); i++)
				this->Lock[temp_pair.first][i]=true;
		if (Podaz[temp_pair.second] == 0)
			for (int i = 0; i < Popyt.size(); i++)
				this->Lock[i][temp_pair.second]=true;
		Pop = 0;
		Pod = 0;
		for (int a : Popyt)Pop += a;
		for (int a : Podaz)Pod += a;
	} while (Pop != 0 || Pod != 0);
// 	   3. Lock it
//		Repeat to fill up table //[Popyt][Podaz]
//
//Flag1
 //calc Alphas and Betas
 vector<int> sus;
 vector<int> bus;
 // 1. Set first alpha to zero and make it sus
	for (int i = 0; i < Popyt.size(); i++)
		this->Alpha.push_back(0);
	for (int k = 0; k < Podaz.size(); k++)
		this->Beta.push_back(0);

	bus.push_back(0);
//2. Find non zero Tactics in sus row
	for (int lock = 0; lock < Alpha.size() + Beta.size(); lock++)
	{
		for (int b = 0; b < bus.size(); b++)
		{
			for (int i = 0; i < Popyt.size(); i++)
				if (Tactic[i][bus[b]])
				{
					sus.push_back(i);
					Alpha[i] = Ref[i][bus[b]] - Beta[bus[b]];
				}
		}
		bus.empty();
		for (int a = 0; a < sus.size(); a++)
		{
			for (int k = 0; k < Podaz.size(); k++)
				if (Tactic[sus[a]][k] != 0)
				{
					bus.push_back(k);
					Beta[k] = Ref[sus[a]][k] - Alpha[sus[a]];
				}
		}
		sus.empty();
	}
	
 //calc Deltas
	for (int i = 0; i < Alpha.size(); i++) {
		cout << endl;
		for (int k = 0; k < Beta.size(); k++)
		{
			Delta[i][k] = Ref[i][k] - Alpha[i] - Beta[k];
			cout << Delta[i][k] << " ";
		}
	}
 //check if deltas are all of the same sign dependant on the algorithm in question
//if not
	//compres tactic bu searching highest or lowest element
	// go to Flag1
//if yes return tactics table
	//calc cost or profit
}

void MiddleManAlgorithm::coutBetaAndAlpha()
{
	cout << "Alphas: ";
		for (int i = 0; i < Alpha.size(); i++)
			cout << this->Alpha[i] << " ";
	cout << "\nBetas: ";
	for (int i = 0; i < Beta.size(); i++)
		cout << this->Beta[i] << " ";
}

void MiddleManAlgorithm::coutTactic()
{
	cout << "Tactic:\n";
		for (int i = 0; i < Alpha.size(); i++)
		{
			cout << endl;
			for (int k = 0; k < Beta.size(); k++)
				cout << Tactic[i][k] << " ";
		}
}

pair<int, int> MiddleManAlgorithm::findLowestUnlocked(vector<vector<double>>& Ref)
{
	int x=-6, y=-6;
	double cur_min = 9999;
	for (int i =0;i<Ref.size();i++)
		for (int k = 0; k < Ref[0].size(); k++)
		{
			if (!this->Lock[i][k] && Ref[i][k] < cur_min)
			{
				x = i;
				y = k;
				cur_min = Ref[i][k];
					this->Lock[i][k] = true;
			}
		}
	return pair<int, int>(x,y);
}

pair<int, int> MiddleManAlgorithm::findHighestUnlocked(vector<vector<double>>& Ref)
{
	int x = -6, y = -6;
	double cur_max = -9999;
	for (int i = 0; i < Ref.size(); i++)
		for (int k = 0; k < Ref[0].size(); k++)
		{
			if (!this->Lock[i][k] && Ref[i][k] > cur_max)
			{
				x = i;
				y = k;
				cur_max = Ref[i][k];
				this->Lock[i][k] = true;
			}
		}
	return pair<int, int>(x, y);
}
