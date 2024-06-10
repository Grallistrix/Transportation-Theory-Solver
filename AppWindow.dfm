object Form1: TForm1
  Left = 225
  Top = 21
  Caption = 'Form1'
  ClientHeight = 798
  ClientWidth = 1492
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
  TextHeight = 15
  object Label1: TLabel
    Left = 546
    Top = 8
    Width = 113
    Height = 15
    Caption = 'Customers / Demand'
  end
  object Label2: TLabel
    Left = 568
    Top = 724
    Width = 64
    Height = 15
    Caption = 'Selling Price'
  end
  object Label3: TLabel
    Left = 8
    Top = 276
    Width = 87
    Height = 15
    Caption = 'Suppliers Supply'
  end
  object Label4: TLabel
    Left = 1424
    Top = 316
    Width = 77
    Height = 15
    Caption = 'Purchase Price'
  end
  object Button_RemSupplier: TButton
    Left = 0
    Top = 760
    Width = 105
    Height = 41
    Caption = 'Remove Supplier'
    TabOrder = 0
    OnClick = Button_RemSupplierClick
  end
  object Button_AddSuplier: TButton
    Left = 1400
    Top = 759
    Width = 105
    Height = 41
    Caption = 'Add Supplier'
    TabOrder = 1
    OnClick = Button_AddSuplierClick
  end
  object Edit_Customer1: TEdit
    Left = 368
    Top = 192
    Width = 70
    Height = 23
    TabOrder = 2
    Text = 'Customer 1'
  end
  object Edit_Customer2: TEdit
    Left = 680
    Top = 200
    Width = 70
    Height = 23
    TabOrder = 3
    Text = 'Customer 2'
  end
  object Edit_Supply1: TEdit
    Left = 112
    Top = 248
    Width = 70
    Height = 23
    TabOrder = 4
    Text = 'Supplier 1'
  end
  object Edit_Supply2: TEdit
    Left = 112
    Top = 416
    Width = 70
    Height = 23
    TabOrder = 5
    Text = 'Supplier 2'
  end
  object Edit_Purchase1: TEdit
    Left = 952
    Top = 248
    Width = 70
    Height = 23
    TabOrder = 6
    Text = 'Buy Price 1'
  end
  object Edit_Purchase2: TEdit
    Left = 952
    Top = 416
    Width = 70
    Height = 23
    TabOrder = 7
    Text = 'Buy Price 2'
  end
  object Edit_Selling1: TEdit
    Left = 344
    Top = 568
    Width = 70
    Height = 23
    TabOrder = 8
    Text = 'Sell Price 1'
  end
  object Edit_Selling2: TEdit
    Left = 680
    Top = 568
    Width = 70
    Height = 23
    TabOrder = 9
    Text = 'Sell Price 2'
  end
  object Button_Calculate: TButton
    Left = 568
    Top = 759
    Width = 113
    Height = 41
    Caption = 'Calculate'
    TabOrder = 10
    OnClick = Button_CalculateClick
  end
  object Button_AddCustomer: TButton
    Left = 1400
    Top = 712
    Width = 105
    Height = 41
    Caption = 'Add Customer'
    TabOrder = 11
    OnClick = Button_AddCustomerClick
  end
  object Button_RemCustomer: TButton
    Left = 0
    Top = 712
    Width = 105
    Height = 42
    Caption = 'Remove Customer'
    TabOrder = 12
    OnClick = Button_RemCustomerClick
  end
  object Memo1: TMemo
    Left = 104
    Top = 674
    Width = 161
    Height = 126
    Lines.Strings = (
      'Memo1')
    TabOrder = 13
  end
  object CheckBox1: TCheckBox
    Left = 264
    Top = 784
    Width = 97
    Height = 17
    Caption = 'Transport?'
    TabOrder = 14
  end
end
