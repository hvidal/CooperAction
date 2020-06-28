//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
                                   
#include "ConnectDialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"         
TfrmConnect *frmConnect;           
//---------------------------------------------------------------------------
__fastcall TfrmConnect::TfrmConnect(TComponent* Owner)
    : TForm(Owner)
{                         
}
//---------------------------------------------------------------------------
void __fastcall TfrmConnect::btnOKClick(TObject *Sender)
{
    if (ed_NickName->Text == "" || ed_ServerName->Text == "")
    {
        ed_NickName->SetFocus();
        return;
    }
    Flag->Caption = 1;
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmConnect::btnCancelClick(TObject *Sender)
{
    Flag->Caption = 0;
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmConnect::FormShow(TObject *Sender)
{
    ed_NickName->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmConnect::ed_NickNameKeyPress(TObject *Sender,
      char &Key)
{
    if(Key == VK_RETURN)
        btnOKClick(Sender);
}
//---------------------------------------------------------------------------

