//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
                                           
#include "frmConn.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TfrmConnProp *frmConnProp;
//---------------------------------------------------------------------------
__fastcall TfrmConnProp::TfrmConnProp(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TfrmConnProp::btnOKClick(TObject *Sender)
{
	Flag->Caption = "1";
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmConnProp::btnCancelarClick(TObject *Sender)
{
	Flag->Caption = "0";
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmConnProp::FormShow(TObject *Sender)
{
	Name->SetFocus();	
}
//---------------------------------------------------------------------------
