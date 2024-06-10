//---------------------------------------------------------------------------

#pragma hdrstop

#include "Functions.h"
//---------------------------------------------------------------------------

extern vector<TEdit*> CustomerControls;
extern vector<TEdit*> SupplyControls;
extern vector<TEdit*> PurchaseControls;
extern vector<TEdit*> SellingControls;
extern vector<vector<TEdit*>> Values;

#define TEDIT_WIDTH 70
#define TEDIT_HEIGHT 20
//------------------------------------------------------------------------------------------------------------------------------------------------------
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
void DistributeHandles(){
	DistributeCustomers();
	DistributeSupply();
	DistributePurchase();
	DistributeSelling();
}
void DistributeValues()
{
	// Iterate over suppliers
	for (int supplyID = 0; supplyID < Values.size(); supplyID++)
	{
		// Iterate over customers
        for (int customerID = 0; customerID < Values[supplyID].size(); customerID++)
		{
			// Make sure there's actually a TEdit
			if (Values[supplyID][customerID] != nullptr)
			{
				// Get intersection position
                int xPosition = CustomerControls[customerID]->Left;
                int yPosition = SupplyControls[supplyID]->Top;

				// Update position
				TEdit *edit = Values[supplyID][customerID];
                edit->Left = xPosition;
                edit->Top = yPosition;
            }
        }
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------------
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
void AddColumn(TForm *parentForm)
{
    int numRows = Values.size();
    int newColumnIndex = Values[0].size(); // Index of the new column
    // Iterate over each row and add a new TEdit at the end
    for (int row = 0; row < numRows; ++row)
    {
        // Create a new TEdit
        TEdit *newEdit = new TEdit(parentForm);
        newEdit->Parent = parentForm;
        // Set position based on existing TEdit in the same row
		int xPosition = CustomerControls[newColumnIndex]->Left;
        int yPosition = SupplyControls[row]->Top;
        newEdit->Left = xPosition;
        newEdit->Top = yPosition;
        newEdit->Width = CustomerControls[newColumnIndex]->Width;
        newEdit->Height = CustomerControls[newColumnIndex]->Height;
	   //	newEdit->NumbersOnly = true;
		// Set the text of the new TEdit
		newEdit->Text = IntToStr(row) + IntToStr(newColumnIndex);
        // Add the new TEdit to the Values vector
        Values[row].push_back(newEdit);
    }
}
void AddRow(TForm *parentForm)
{
    int numRows = Values.size(); // Number of existing rows
    int numColumns = CustomerControls.size(); // Number of columns
    // Add a new row to Values
    Values.push_back(std::vector<TEdit*>());
    // Iterate over each column and add a new TEdit to the new row
    for (int column = 0; column < numColumns; ++column)
    {
        // Create a new TEdit
		TEdit *newEdit = new TEdit(parentForm);
        newEdit->Parent = parentForm;
        // Set position based on existing TEdit in the same column
        int xPosition = CustomerControls[column]->Left;
        int yPosition = SupplyControls[numRows]->Top;
		newEdit->Left = xPosition;
        newEdit->Top = yPosition;
        newEdit->Width = CustomerControls[column]->Width;
        newEdit->Height = CustomerControls[column]->Height;
		//newEdit->NumbersOnly = true;
        // Set the text of the new TEdit
		newEdit->Text = IntToStr(numRows)  + IntToStr(column);
        // Add the new TEdit to the new row
        Values[numRows].push_back(newEdit);
    }
}
void InitiateValues(TForm *parentForm)
{
    // Resize the Values vector to fit the supply and customer controls
    Values.resize(SupplyControls.size());

	// Iterate over each suppliers
    for (int supplyID = 0; supplyID < SupplyControls.size(); supplyID++)
    {
		// Resize inner vector for each supply control
        Values[supplyID].resize(CustomerControls.size());

		// Iterate over each customer
        for (int customerID = 0; customerID < CustomerControls.size(); customerID++)
        {
			// Get intersection position
			int xPosition = CustomerControls[customerID]->Left;
            int yPosition = SupplyControls[supplyID]->Top;

			// Create new TEdit
            TEdit *newEdit = new TEdit(parentForm);
            newEdit->Parent = parentForm;
            newEdit->Left = xPosition;
            newEdit->Top = yPosition;
            newEdit->Width = CustomerControls[customerID]->Width;
            newEdit->Height = CustomerControls[customerID]->Height;
			String abc = IntToStr(supplyID) + IntToStr(customerID);
			newEdit->Text = abc;

		   //	newEdit->NumbersOnly = true;


			// Store new TEdit in Values vector
            Values[supplyID][customerID] = newEdit;
        }
    }
}
void DeleteTEdit(int row, int column)
{
    if (row >= 0 && row < Values.size() && column >= 0 && column < Values[row].size())
	{
		delete Values[row][column]; // Delete the TEdit object
		Values[row][column] = nullptr; // Set the pointer to nullptr
	}
}
void ClearLastRow()
{
	// Iterate over each TEdit in the last row
    for (int column = 0; column < Values.back().size(); ++column)
    {
		DeleteTEdit(Values.size() - 1, column); // Delete TEdit
    }
	// Resize Values to remove the last row
	Values.resize(Values.size() - 1);
}
void ClearLastColumn()
{
	// Iterate over rows
    for (int row = 0; row < Values.size(); ++row)
    {
		// If there is at least one TEdit in current row
        if (!Values[row].empty())
        {
			DeleteTEdit(row, Values[row].size() - 1); // Delete last TEdit in current row
			Values[row].resize(Values[row].size() - 1); // Resize to remove the last column
        }
    }

}
//------------------------------------------------------------------------------------------------------------------------------------------------------
 //GetPopyt
vector<int> GetDemand()
{
	vector<int> demand;
    for (TEdit* edit : CustomerControls)
    {
        if (edit != nullptr)
        {
			// Convert the text of the TEdit to an integer
			int value = edit->Text.ToInt();
            demand.push_back(value);
        }
	}
    return demand;
}
//GetPodaz
vector<int> GetSupply()
{
	vector<int> supply;
	for (TEdit* edit : SupplyControls)
    {
        if (edit != nullptr)
        {
            // Convert the text of the TEdit to an integer
			int value = edit->Text.ToInt();
			supply.push_back(value);
        }
	}
	return supply;
}
vector<int> GetPurchase()
{
	vector<int> purchase;
    for (TEdit* edit : PurchaseControls)
    {
        if (edit != nullptr)
        {
            // Convert the text of the TEdit to an integer
			int value = edit->Text.ToInt();
			purchase.push_back(value);
        }
    }
    return purchase;
}
vector<int> GetSelling()
{
	vector<int> selling;
    for (TEdit* edit : SellingControls)
    {
        if (edit != nullptr)
        {
			// Convert the text of the TEdit to an integer
			int value = edit->Text.ToInt();
            selling.push_back(value);
        }
    }
    return selling;
}
vector<vector<double>> GetValues()
{
	vector<vector<double>> vals;
    for (int i = 0; i < Values.size(); ++i)
    {
		vector<double> rowValues;
        for (int j = 0; j < Values[i].size(); ++j)
        {
            if (Values[i][j] != nullptr)
            {
				// Convert the text of the TEdit to a double
                double value = StrToFloatDef(Values[i][j]->Text, 0.0);
                rowValues.push_back(value);
            }
        }
		vals.push_back(rowValues);
    }
	return vals;
}
vector<vector<double>> calcUnitProfit(vector<int>sellPrice,vector<int>buyPrice,vector<vector<double>> unitCost)
{
	//inicialize variables
	vector<double>tempVec;
	for(int k=0;k<buyPrice.size();k++)
		tempVec.push_back(0);
	vector<vector<double>> tempMat;
	for(int i=0;i<sellPrice.size();i++)
		tempMat.push_back(tempVec);
		//Fill with unit profit: Prof = SellPrice - BuyPrice - Transport
	for(int k=0;k<buyPrice.size();k++)
		for(int i=0;i<sellPrice.size();i++)
			tempMat[i][k]=sellPrice[i]-buyPrice[k]-unitCost[i][k];
			return tempMat;
}

double getTotalCost(vector<int>buyPrice,vector<vector<int>> Tactic,vector<vector<double>> originalRef)
{
    double tempCost=0;
    for(int k=0;k<originalRef[0].size();k++)
        for(int i=0;i<buyPrice.size();i++)
			tempCost+=buyPrice[i]*Tactic[i][k];
    return tempCost;
}

double getTransportCost(vector<vector<double>> values,vector<vector<int>> Tactic)
{
	double tempCost=0;
	for(int k=0;k<values[0].size();k++)
			for(int i=0;i<values.size();i++)
				tempCost+=values[i][k]*Tactic[i][k];
	return tempCost;
}

std::wstring StringToWString(const std::string& str) {
	std::wstring wstr(str.begin(), str.end());
	return wstr;
}

void ShowMessageBox(const std::string& message, const std::string& title) {
	// Convert std::string to std::wstring
	std::wstring wMessage = StringToWString(message);
	std::wstring wTitle = StringToWString(title);
	// Display the message box with OK button
	MessageBoxW(NULL, wMessage.c_str(), wTitle.c_str(), MB_OK | MB_ICONINFORMATION);
}





#pragma package(smart_init)
