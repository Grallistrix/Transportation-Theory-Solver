//---------------------------------------------------------------------------

#ifndef AppWindowH
#define AppWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button_RemSupplier;
	TButton *Button_AddSuplier;
	TEdit *Edit_Customer1;
	TEdit *Edit_Customer2;
	TEdit *Edit_Supply1;
	TEdit *Edit_Supply2;
	TEdit *Edit_Purchase1;
	TEdit *Edit_Purchase2;
	TEdit *Edit_Selling1;
	TEdit *Edit_Selling2;
	TButton *Button_Calculate;
	TButton *Button_AddCustomer;
	TButton *Button_RemCustomer;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TMemo *Memo1;
	void __fastcall Button_RemSupplierClick(TObject *Sender);
	void __fastcall Button_AddSuplierClick(TObject *Sender);
	void __fastcall Button_AddCustomerClick(TObject *Sender);
	void __fastcall Button_RemCustomerClick(TObject *Sender);
	void __fastcall Button_CalculateClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
