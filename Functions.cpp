//---------------------------------------------------------------------------

#pragma hdrstop

#include "Functions.h"
//---------------------------------------------------------------------------

extern vector<TEdit*> CustomerControls;
extern vector<TEdit*> SupplyControls;
extern vector<TEdit*> PurchaseControls;
extern vector<TEdit*> SellingControls;

#define TEDIT_WIDTH 70
#define TEDIT_HEIGHT 20
//---------------------------------------------------------------------------
void DistributeCustomers(){

	int formWidth = 1500;
	int formHeight = 800;
	int topPosition = 100; // Vertical position of the Customer Labels
	int edgeSpacing = 200; // Minimum distance from the edges
	int availableWidth = formWidth - 2 * edgeSpacing;

	int totalSpacing = availableWidth - CustomerControls.size() * EDIT_WIDTH;
	int spacing = totalSpacing / (CustomerControls.size() + 1);

	int currentX = edgeSpacing + spacing;

	for (int i = 0; i < CustomerControls.size(); i++){
			CustomerControls[i]->Left = currentX;  				 //Set X coordinated
			CustomerControls[i]->Top = topPosition;              //Set Y cooridnates
			currentX += EDIT_WIDTH + spacing;                     //Modify future X_cord for next
	}
}

void DistributeSupply(){
    int xPosition = 50; // Horizontal position for the column
    int edgeSpacing = 100; // Spacing from each edge
	int startY = edgeSpacing; // Starting vertical position
	int formHeight = 800;


	int availableHeight = formHeight - 2 * edgeSpacing;

	int totalHeight = SupplyControls.size() * SupplyControls[0]->Height;

    int spacing = (availableHeight - totalHeight) / (SupplyControls.size() + 1);

	int currentY = startY + spacing;

    for (size_t i = 0; i < SupplyControls.size(); i++)
	{
		SupplyControls[i]->Left = xPosition;
        SupplyControls[i]->Top = currentY;
        currentY += SupplyControls[i]->Height + spacing;
	}
}

void DistributePurchase(){
	int xPosition = 1500-140; // Horizontal position for the column
    int edgeSpacing = 100; // Spacing from each edge
	int startY = edgeSpacing; // Starting vertical position
	int formHeight = 800;


    int availableHeight = formHeight - 2 * edgeSpacing;

	int totalHeight = PurchaseControls.size() * PurchaseControls[0]->Height;

	int spacing = (availableHeight - totalHeight) / (PurchaseControls.size() + 1);

	int currentY = startY + spacing;

	for (size_t i = 0; i < PurchaseControls.size(); i++)
	{
		PurchaseControls[i]->Left = xPosition;
		PurchaseControls[i]->Top = currentY;
		currentY += PurchaseControls[i]->Height + spacing;
	}
}

void DistributeSelling(){

	int formWidth = 1500;
	int formHeight = 800;
	int topPosition = 700; // Vertical position of the Customer Labels
	int edgeSpacing = 200; // Minimum distance from the edges
	int availableWidth = formWidth - 2 * edgeSpacing;

	int totalSpacing = availableWidth - SellingControls.size() * EDIT_WIDTH;
	int spacing = totalSpacing / (SellingControls.size() + 1);

	int currentX = edgeSpacing + spacing;

	for (int i = 0; i < SellingControls.size(); i++){
			SellingControls[i]->Left = currentX;  				 //Set X coordinated
			SellingControls[i]->Top = topPosition;              //Set Y cooridnates
			currentX += EDIT_WIDTH + spacing;                     //Modify future X_cord for next
	}
}

void DistributeAll(){
	DistributeCustomers();
	DistributeSupply();
	DistributePurchase();
	DistributeSelling();
}


void addTEdit(TForm *parentForm, vector<TEdit*> &WantedVector){
	TEdit *newEdit = new TEdit(parentForm);
	newEdit->Parent = parentForm; // Set the form as the parent
	newEdit->Width = TEDIT_WIDTH;
	newEdit->Height = TEDIT_HEIGHT;
	newEdit->Text = WantedVector.size();
	WantedVector.push_back(newEdit);
}

void RemoveLastEdit(vector<TEdit*> &WantedVector)
{
	if (WantedVector.size()>2)
	{
		TEdit *lastEdit = WantedVector.back(); // Get pointer
		WantedVector.pop_back(); // Remove from vector
		delete lastEdit;    //Free memory
    }
}



#pragma package(smart_init)
