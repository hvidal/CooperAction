//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TfrmMessage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmError *frmError;
//---------------------------------------------------------------------------
__fastcall TfrmError::TfrmError(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmError::OKClick(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------
