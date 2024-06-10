#include "MiddleManAlgorithm.h"
#include <iostream>
#include <vector>

using namespace std;

MiddleManAlgorithm::MiddleManAlgorithm(vector<int>& Podaz, vector<int>& Popyt, vector<vector<double>>& Ref, bool delta_control)//Poúrednik == true
{

	this->StableRef = Ref;
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
	this->StableRef = Ref;
	do
	{
		//Algorithm
//Fill tactic with loads based on lowest/highest element method
// 	   1. Find lowest/highest element in matrix that is not locked
		pair<int, int> temp_pair;
		if (delta_control)temp_pair = findHighestUnlocked(Ref);
		else temp_pair = findLowestUnlocked(Ref);
		// 	   2. Fill as much load as Popyt and Podaø related to it allow to
		if (Popyt[temp_pair.first] >= Podaz[temp_pair.second]) {
			this->Tactic[temp_pair.first][temp_pair.second] = Podaz[temp_pair.second];
			Popyt[temp_pair.first] -= Podaz[temp_pair.second]; Podaz[temp_pair.second] = 0;
		}
		else {
			this->Tactic[temp_pair.first][temp_pair.second] = Popyt[temp_pair.first];
			Podaz[temp_pair.second] -= Popyt[temp_pair.first]; Popyt[temp_pair.first] = 0;
		}
		//Blokada
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

 // 1. Set first alpha to zero and make it sus
	for (int i = 0; i < Popyt.size(); i++)
		this->Alpha.push_back(0);
	for (int k = 0; k < Podaz.size(); k++)
		this->Beta.push_back(0);

vector<int> sus;
vector<int> bus;

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
	calcDelta();
 //check if deltas are all of the same sign dependant on the algorithm in question
//if not
	//compres tactic bu searching highest or lowest element
	// go to Flag1
//if yes return tactics table
	//calc cost or profit
	//this->StableRef = Ref;
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

int MiddleManAlgorithm::compressTactic(bool control)
{
	//Flag1
	//Sprawdzamy czy wszystkie delty nie majπ znaku zgodnego z controlnym
		// Jeøeli tak koÒczymy i zwracamy iloúÊ wykonanych kompresji "counter" - do debugowania
		//Zliczamy kompresje do debugowania
		//Jeølei nie to kontynuujemy
		//Zaleønie od zmiennej controlnej ustalenie taktyki poszukiwaÒ w celu maksymalizacji lub minimalizacji celu
		//Szukamy najmnijeszej lub najwiÍkszej delty
		pair<int, int> delta_pos = { 0,0 };
		pair<int, int> cross_pos = { 0,0 };
		double last;
		//Fill cover for search algorithm in first iteration
		if (control)last = 9999;
		else last = -9999;

		do {

			//if (control == !bool(last))return counter;//check if next found delta is 0 or in conjuction with argument

			if (control) {
				if (last <= 0)return 1;
			}
			else{
				if (last >= 0)return 1;
			}

			if (control)delta_pos = findPositiveDelta(last);//find delta closer to zero than last
			else delta_pos = findNegativeDelta(last);
			//znajdü element ukoúny
			cross_pos = findCrossElement(delta_pos);
			last = Delta[delta_pos.first][delta_pos.second];
		} while (cross_pos == delta_pos);
		int difference = 0;
		//Znajdz najmniejszy element na ujemnym krzyøu.
		if (Tactic[delta_pos.first][cross_pos.second] < Tactic[cross_pos.first][delta_pos.second]) {
			difference = Tactic[delta_pos.first][cross_pos.second];
		}
		else {
			difference = Tactic[cross_pos.first][delta_pos.second];
		}
		//Przemigruj zasoby z minusÛw na plusy o wartoúÊ krokÛw.
		//- - - -
		Tactic[delta_pos.first][cross_pos.second]-=difference;
		Tactic[cross_pos.first][delta_pos.second]-=difference;
		//+ + + +
		Tactic[delta_pos.first][delta_pos.second]+=difference;
		Tactic[cross_pos.first][cross_pos.second]+=difference;
		//Go to Flag1


	return 1;
}

int MiddleManAlgorithm::getTarget()
{
	double target = 0;
	for(int i=0;i<this->StableRef.size();i++)
		for (int k = 0; k < this->StableRef[0].size(); k++)
		{
			target += StableRef[i][k] * Tactic[i][k];
		}
	return target;
}

void MiddleManAlgorithm::calcBetaAndAlpha()
{
	vector<int> sus;
	vector<int> bus;

	bus.push_back(0);
	//2. Find non zero Tactics in sus row
	for (int lock = 0; lock < Alpha.size() + Beta.size(); lock++)
	{
		for (int b = 0; b < bus.size(); b++)
		{
			for (int i = 0; i < Tactic.size(); i++)
				if (Tactic[i][bus[b]])
				{
					sus.push_back(i);
					Alpha[i] = this->StableRef[i][bus[b]] - Beta[bus[b]];
				}
		}
		bus.empty();
		for (int a = 0; a < sus.size(); a++)
		{
			for (int k = 0; k < Tactic[0].size(); k++)//MaybeSeg with bad data
				if (Tactic[sus[a]][k] != 0)
				{
					bus.push_back(k);
					Beta[k] = this->StableRef[sus[a]][k] - Alpha[sus[a]];
				}
		}
		sus.empty();
	}
}

void MiddleManAlgorithm::calcDelta()
{
	for (int i = 0; i < Alpha.size(); i++) {
		cout << endl;
		for (int k = 0; k < Beta.size(); k++)
		{
			Delta[i][k] = StableRef[i][k] - Alpha[i] - Beta[k];
			cout << Delta[i][k] << " ";
		}
	}
	cout << endl;
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

			}
		}
	this->Lock[x][y] = true;
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

			}
		}
	this->Lock[x][y] = true;
	return pair<int, int>(x, y);
}

pair<int, int> MiddleManAlgorithm::findNegativeDelta(double& last)
{
	double curr_min = 0;
	int x, y,i,k;
	for (i = 0; i < Delta.size(); i++)
		for (k = 0; k < Delta[0].size(); k++)
			if (Delta[i][k] > last && Delta[i][k] < curr_min) {
				x = i;
				y = k;
				curr_min = Delta[i][k];
			}
	return pair<int, int>({ x,y });
}

pair<int, int> MiddleManAlgorithm::findPositiveDelta(double& last)
{
	double curr_min = 0;
	int x=0, y=0, i=0, k=0;
	for (i = 0; i < Delta.size(); i++)
		for (k = 0; k < Delta[0].size(); k++)
			if (Delta[i][k] < last && Delta[i][k] > curr_min) {
				x = i;
				y = k;
				curr_min = Delta[i][k];
			}
	return pair<int, int>({ x,y });
}

pair<int, int> MiddleManAlgorithm::findCrossElement(pair<int, int> delta_pos)
{
	for (int i = 0; i < Delta.size(); i++)
		for (int k = 0; k < Delta[0].size(); k++)
		{
				if (i == delta_pos.first || k == delta_pos.second)continue;
				if (this->Delta[i][k] == 0 && this->Delta[delta_pos.first][k] == 0 && this->Delta[i][delta_pos.second] == 0) {
					return pair<int, int>({ i,k });
				}
			//[i,k]<->[delta_pos.first,k]
			//^
			//v
			//[i,delta_pos.second]<->[delta_pos.first,delta_pos.second]
		}
	return delta_pos;
}

int MiddleManAlgorithm::optimize(bool control)
{
	//Check if sign is constant
	while (!checkForConstantSign(!control))
	{
		//Compress system
		this->compressTactic(control);
		//Zero out conjuction data
			fill(this->Alpha.begin(), this->Alpha.end(),0);
			fill(this->Beta.begin(), this->Beta.end(), 0);
			for(int i=0;i<Delta.size();i++)
				for (int k = 0; k < Delta[i].size(); k++)
				{
					Delta[i][k] = 0;
				}
			//Calc new conjuction Data
			calcBetaAndAlpha();
			calcDelta();
	}
	return 1;
}

//Fasada
bool MiddleManAlgorithm::checkForConstantSign(bool sign)
{
	if (sign)return checkForConstantPositive();
	else return checkForConstantNegative();
}

bool MiddleManAlgorithm::checkForConstantPositive()
{
	for (int i = 0; i < Delta.size(); i++)
		for (int k = 0; k < Delta[0].size(); k++)
			if (Delta[i][k]<0)return false;

	return true;
}

bool MiddleManAlgorithm::checkForConstantNegative()
{
	for (int i = 0; i < Delta.size(); i++)
		for (int k = 0; k < Delta[0].size(); k++)
			if (Delta[i][k] > 0)return false;

	return true;
}

