//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AppWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include <vector>
#include "Functions.h"

TForm1 *Form1;

using std::vector;

vector<TEdit*> CustomerControls;
vector<TEdit*> SupplyControls;
vector<TEdit*> PurchaseControls;
vector<TEdit*> SellingControls;
vector<vector<TEdit*>> Values (10,vector<TEdit*>(10,nullptr));

//---------------------------------------------------------------------------

void CreateTEditsAtIntersections(TForm *parentForm)
{
	// Iterate over each supply control
	for (int supplyID = 0; supplyID < SupplyControls.size(); supplyID++)
    {
        // Iterate over each customer control
		for (int customerID = 0; customerID < CustomerControls.size(); customerID++)
        {
            // Get the position of the intersection
			int xPosition = CustomerControls[customerID]->Left;
			int yPosition = SupplyControls[supplyID]->Top;

            // Create a new TEdit
			TEdit *newEdit = new TEdit(parentForm);
			newEdit->Parent = parentForm;
			newEdit->Left = xPosition;
            newEdit->Top = yPosition;
            newEdit->Width = CustomerControls[customerID]->Width;
			newEdit->Height = CustomerControls[customerID]->Height;
			String abc =   IntToStr(supplyID) + "=" + IntToStr(customerID);
			newEdit->Text = abc;

			// Store the new TEdit in the Values vector
			Values[supplyID][customerID] = newEdit;
        }
    }
}



__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	//Push all TEdits into their respective vectors

	CustomerControls.push_back(Edit_Customer1);
	CustomerControls.push_back(Edit_Customer2);

	SupplyControls.push_back(Edit_Supply1);
	SupplyControls.push_back(Edit_Supply2);

	PurchaseControls.push_back(Edit_Purchase1);
	PurchaseControls.push_back(Edit_Purchase2);

	SellingControls.push_back(Edit_Selling1);
	SellingControls.push_back(Edit_Selling2);

	 //Sort their Positions
	 DistributeAll();

	 CreateTEditsAtIntersections(this);

}

void clearAllValues(){

	for (auto& row : Values)
	{
		for (auto& editPtr : row)
		{
			// Delete the TEdit pointer if it is not nullptr
			if (editPtr != nullptr)
				delete editPtr;
        }
	}

	// Repopulate the Vector
	Values =  vector<vector<TEdit*>>(10, vector<TEdit*>(10, nullptr));
}

 //Usuñ ostatnie
void clearLastValues(){
	for (auto& row : Values){

		int x = 0;
		int rowSize = CustomerControls.size();
		for (auto& editPtr : row){

			x++;
			// Delete the TEdit pointer if it is not nullptr
			if (editPtr != nullptr && x == rowSize){
				delete editPtr;
				editPtr=nullptr;
			}
		}
	}
}
//Usuñ ostatni Row
void clearLastRow(){

	int x=0;

	for (auto& row : Values){

		x++;

		for (auto& editPtr : row){
			// Delete the TEdit pointer if it is not nullptr
			if (editPtr != nullptr && x==PurchaseControls.size()){
				delete editPtr;
				editPtr=nullptr;
			}

		}
	}
}


void __fastcall TForm1::Button_RemSupplierClick(TObject *Sender)
{
	RemoveLastEdit(SupplyControls);
	RemoveLastEdit(PurchaseControls);

	DistributeAll();
	clearAllValues();
	CreateTEditsAtIntersections(this);

}

void __fastcall TForm1::Button_AddSuplierClick(TObject *Sender)
{

	if(SupplyControls.size()>=10)
		return;

	addTEdit(this,SupplyControls);
	addTEdit(this,PurchaseControls);


	DistributeAll();
    clearAllValues();
	CreateTEditsAtIntersections(this);
}


void RedistributeTEdits(){

	// Iterate through each supply control (rows of Values)
    for (size_t supplyID = 0; supplyID < SupplyControls.size(); supplyID++)
	{
		// Iterate through each customer control (columns of Values)
		for (size_t customerID = 0; customerID < CustomerControls.size(); customerID++)
        {
			TEdit* editPtr = Values[supplyID][customerID];
            // Check if the TEdit pointer is not nullptr
            if (editPtr != nullptr)
            {
                // Get the position of the intersection
                int xPosition = CustomerControls[customerID]->Left;
                int yPosition = SupplyControls[supplyID]->Top;

                // Set the new position of the TEdit
                editPtr->Left = xPosition;
                editPtr->Top = yPosition;
            }
		}
	}
}

void __fastcall TForm1::Button_CalculateClick(TObject *Sender)
{
	if(Values[0][0]!=nullptr)
	   clearAllValues();


	CreateTEditsAtIntersections(this);
}

void __fastcall TForm1::Button_AddCustomerClick(TObject *Sender)
{
	if(CustomerControls.size()>=10)
		return;

	addTEdit(this,CustomerControls);
	addTEdit(this,SellingControls);

	DistributeAll();

	clearAllValues();
	CreateTEditsAtIntersections(this);
}

void __fastcall TForm1::Button_RemCustomerClick(TObject *Sender)
{
	RemoveLastEdit(CustomerControls);
	RemoveLastEdit(SellingControls);
	DistributeAll();

	clearAllValues();
	CreateTEditsAtIntersections(this);
}

void __fastcall TForm1::Button_TestClick(TObject *Sender)
{
	clearLastRow();
	RedistributeTEdits();
}

