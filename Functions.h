//---------------------------------------------------------------------------

#ifndef FunctionsH
#define FunctionsH

#include<vector>
 #include <System.Classes.hpp>
#include <Vcl.Forms.hpp>



#define EDIT_WIDTH 50


using std::vector;


 //---------------------------------------------------------------------------
void DistributeCustomers();
void DistributeSupply();
void DistributePurchase();
void DistributeSelling();
void DistributeHandles();
void DistributeValues();    //Always use after DistributeHandles, NEVER before
//---------------------------------------------------------------------------
void DeleteTEdit(int row, int column);
void ClearLastRow();
void ClearLastColumn();
void AddColumn(TForm *parentForm);
void AddRow(TForm *parentForm);
//---------------------------------------------------------------------------
void InitiateValues(TForm *parentForm);
void RemoveLastEdit(vector<TEdit*> &WantedVector);
void addTEdit(TForm *parentForm, vector<TEdit*> &WantedVector);
 //---------------------------------------------------------------------------
vector<int> GetDemand(); //GetPopyt
vector<int> GetSupply(); //GetPodaz
vector<int> GetPurchase();
vector<int> GetSelling();
vector<vector<double>> GetValues();
 vector<vector<double>> calcUnitProfit(vector<int>sellPrice,vector<int>buyPrice,vector<vector<double>> unitCost);

double getTotalCost(vector<int>buyPrice,vector<vector<int>> Tactic,vector<vector<double>> originalRef);

double getTransportCost(vector<vector<double>> values,vector<vector<int>> Tactic);
#endif
