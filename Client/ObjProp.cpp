//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
                                     
#include "ObjProp.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"

TOProp *OProp;
//---------------------------------------------------------------------------
__fastcall TOProp::TOProp(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TOProp::btnCancelarClick(TObject *Sender)
{
	Flag->Caption = "0";
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TOProp::FormActivate(TObject *Sender)
{
	Name->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TOProp::btnOKClick(TObject *Sender)
{
	if(Name->Text == "")
    {
        Name->SetFocus();
        return;
    }
	Flag->Caption = "1";
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TOProp::NameKeyPress(TObject *Sender, char &Key)
{
    if (Key == VK_RETURN)
        btnOKClick(Sender);
        
    if(!((Key >= '0' && Key <= '9') ||
        (Key >= 'A' && Key <= 'Z') ||
        (Key >= 'a' && Key <= 'z')) &&
        Key != VK_DELETE && Key != VK_BACK)
        Key = 7;
}
//---------------------------------------------------------------------------
