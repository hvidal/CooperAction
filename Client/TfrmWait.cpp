//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TfrmWait.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmWait *frmWait;
//---------------------------------------------------------------------------
__fastcall TfrmWait::TfrmWait(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmWait::TimerTimer(TObject *Sender)
{
    if(lb_response->Caption != "")
    {
        Timer->Enabled = false;
        Close();
    }
}
//---------------------------------------------------------------------------
