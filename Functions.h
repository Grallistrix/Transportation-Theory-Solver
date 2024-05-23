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
void DistributeAll();
//---------------------------------------------------------------------------
void RemoveLastEdit(vector<TEdit*> &WantedVector);
void addTEdit(TForm *parentForm, vector<TEdit*> &WantedVector);
#endif
