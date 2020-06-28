//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop                                         

#include "ModelProp.h"                
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TMProp *MProp;
//---------------------------------------------------------------------------
__fastcall TMProp::TMProp(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMProp::btnOKClick(TObject *Sender)
{
	Flag->Caption = "1";
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TMProp::btnCancelarClick(TObject *Sender)
{
	Flag->Caption = "0";
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TMProp::HSizeKeyPress(TObject *Sender, char &Key)
{
	if((Key < '0' || Key > '9') && Key != 8) Key = 7;
}
//---------------------------------------------------------------------------
void __fastcall TMProp::VSizeKeyPress(TObject *Sender, char &Key)
{
	if((Key < '0' || Key > '9') && Key != 8) Key = 7;	
}
//---------------------------------------------------------------------------
void __fastcall TMProp::FormShow(TObject *Sender)
{
    Flag->Caption == "0";
    MName->SetFocus();	

}
//---------------------------------------------------------------------------
