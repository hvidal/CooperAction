//---------------------------------------------------------------------------
#ifndef ObjPropH
#define ObjPropH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>                                 
#include <vcl\ComCtrls.hpp>
#include <vcl\Buttons.hpp>           
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TOProp : public TForm
{
__published:	// IDE-managed Components
    TLabel *lb_Name;
	TGroupBox *GroupBox1;
	TRadioButton *ALeft;
	TRadioButton *ACenter;
	TRadioButton *ARight;
	TBitBtn *btnOK;
	TBitBtn *btnCancelar;
	TLabel *Flag;
    TEdit *Name;
    TPopupMenu *PopupMenu1;
	void __fastcall btnCancelarClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall btnOKClick(TObject *Sender);
    void __fastcall NameKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations       
	__fastcall TOProp(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOProp *OProp;
//---------------------------------------------------------------------------
#endif
