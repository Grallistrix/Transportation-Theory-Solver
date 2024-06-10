//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AppWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
 #include <windows.h>
#include <vector>
#include "Functions.h"

#include "MiddleManAlgorithm.h"

TForm1 *Form1;

using std::vector;

vector<TEdit*> CustomerControls;
vector<TEdit*> SupplyControls;
vector<TEdit*> PurchaseControls;
vector<TEdit*> SellingControls;
vector<vector<TEdit*>> Values;

//---------------------------------------------------------------------------

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
	 DistributeHandles();

	 InitiateValues(this);

}

void __fastcall TForm1::Button_RemSupplierClick(TObject *Sender)
{
	if(SupplyControls.size()<=2)
		return;

	RemoveLastEdit(SupplyControls);
	RemoveLastEdit(PurchaseControls);

	DistributeHandles();
	ClearLastRow();
	DistributeValues();
}

void __fastcall TForm1::Button_AddSuplierClick(TObject *Sender)
{

	if(SupplyControls.size()>=10)
		return;

	addTEdit(this,SupplyControls);
	addTEdit(this,PurchaseControls);

	DistributeHandles();
	AddRow(this);
	DistributeValues();
}

void __fastcall TForm1::Button_AddCustomerClick(TObject *Sender)
{
	if(CustomerControls.size()>=10)
		return;

	addTEdit(this,CustomerControls);
	addTEdit(this,SellingControls);

	DistributeHandles();
	AddColumn(this);
	DistributeValues();
}

void __fastcall TForm1::Button_RemCustomerClick(TObject *Sender)
{
	if(CustomerControls.size()<=2)
		return;

	RemoveLastEdit(CustomerControls);
	RemoveLastEdit(SellingControls);

	DistributeHandles();
	ClearLastColumn();
	DistributeValues();
}




template <typename T>
vector<vector<T>> InvertVector(const vector<vector<T>>& input)
{
	vector<vector<T>> inverted(input[0].size(), vector<T>(input.size()));

	for (size_t i = 0; i < input.size(); ++i)
		for (size_t j = 0; j < input[i].size(); ++j)
			inverted[j][i] = input[i][j];

	return inverted;
}



template <typename T1, typename T2>
void VectorResizer(vector<vector<T1>>& input, const vector<vector<T2>>& resizer) {

    input.resize(resizer.size());

    for (size_t i = 0; i < resizer.size(); ++i) {
        input[i].resize(resizer[i].size());
    }
}

template <typename T>
void DisplayValues(const std::vector<std::vector<T>>& values, TMemo *Memo1) {
	// Clear the Memo1 before displaying new contents
    Memo1->Lines->Clear();

    // Loop through the values vector and display each row in Memo1
    for (size_t i = 0; i < values.size(); ++i) {
        String row;
        // Concatenate values of the current row
        for (size_t j = 0; j < values[i].size(); ++j) {
            row += FloatToStr(values[i][j]);
            // Add a space between values
            if (j != values[i].size() - 1) {
                row += " ";
            }
        }
        // Add the concatenated row to Memo1
        Memo1->Lines->Add(row);
    }
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


template <typename T>
std::string VectorToString(const std::vector<std::vector<T>>& vec) {
    std::string result;

    for (const auto& row : vec) {
        for (const auto& elem : row) {
            result += std::to_string(elem) + " ";
        }
        // Remove the trailing space and add a newline character
        if (!result.empty()) {
            result.pop_back(); // Remove the trailing space
            result += "\n";
        }
    }

    // Remove the last newline character if present
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }

    return result;
}

void __fastcall TForm1::Button_TestClick(TObject *Sender)
{

	Memo1->Height =500;
	//Get Needed Data
	vector<int> supply = GetSupply();  //Podaz
	vector<int> demand = GetDemand();  //Popyt
	vector<int> purchase = GetPurchase();
	vector<int> selling = GetSelling();

	vector<vector<double>> values = GetValues();
	values = InvertVector(values);


	/*
	vector<vector<double>> referenceTable = { {12, 6}, {1, 4}, {3, -1} };
	vector<int> Popyt = { 10, 28, 27 };      //Demand
	vector<int> Podaz = { 20, 30 };         //Supply
	*/


	// Use the Algorithm to calculate needed stuff
	bool control = true;
	vector<vector<double>> UnitProfits = calcUnitProfit(selling,purchase,values);

	MiddleManAlgorithm calc(supply, demand, UnitProfits, control);
	calc.optimize(control);


	double totalProfit = calc.getTarget();



	calc.Tactic = InvertVector(calc.Tactic);//ALWAYS AFTER GET_TARGET



	double totalCost=0;
	double buyCost = getTotalCost(purchase, calc.Tactic, values);
	values = InvertVector(values);
	double transportCost = getTransportCost(values,calc.Tactic) ;
	totalCost =transportCost + buyCost;

	double totalIncome = totalProfit+totalCost;



	//Display the Data

	String text1 = "Profit:" + FloatToStr(totalProfit);
	String text2 = "Total Cost:" + FloatToStr(totalCost);
	String text3 = "Income:" + FloatToStr(totalIncome);

	String text4 = "Transport Cost:" + FloatToStr(transportCost);
	String text5 = "Buying Cost:" + FloatToStr(buyCost);

	Memo1->Lines->Clear();
	Memo1->Lines->Add(text1);
	Memo1->Lines->Add(text2);
	Memo1->Lines->Add(text3);
	Memo1->Lines->Add(text4);
	Memo1->Lines->Add(text5);


	//Set proper UnitProfits
   UnitProfits = InvertVector(UnitProfits);         //INDIVIDUAL PROFIT
   VectorResizer(UnitProfits, values);

   //	DisplayValues(UnitProfits, Memo1);
	vector<vector<int>> tempTactic = calc.Tactic ; //TRANSPORT
	VectorResizer(tempTactic, values);
  //	DisplayValues(tempTactic, Memo1);


  ShowMessageBox(VectorToString(UnitProfits), "Optimal Cost");
  ShowMessageBox(VectorToString(tempTactic), "Optimal Transport");
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button_CalculateClick(TObject *Sender)
{
       // Set texts for CustomerControls
    CustomerControls[0]->Text = "30";
    CustomerControls[1]->Text = "30";

    // Set texts for SupplyControls
    SupplyControls[0]->Text = "45";
    SupplyControls[1]->Text = "25";

    // Set texts for SellingControls
    SellingControls[0]->Text = "12";
    SellingControls[1]->Text = "13";

    // Set texts for PurchaseControls
    PurchaseControls[0]->Text = "6";
    PurchaseControls[1]->Text = "7";

    // Set values for Values
    Values[0][0]->Text = "7"; // Values[0][0] corresponds to 00
    Values[1][1]->Text = "5"; // Values[1][1] corresponds to 11
	Values[0][1]->Text = "4"; // Values[0][1] corresponds to 01
	Values[1][0]->Text = "3"; // Values[1][0] corresponds to 10
}
//---------------------------------------------------------------------------

