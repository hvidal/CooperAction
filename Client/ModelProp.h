//---------------------------------------------------------------------------
#ifndef ModelPropH                                                
#define ModelPropH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>                  
#include <vcl\ComCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\OleCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TMProp : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *btnOK;
	TBitBtn *btnCancelar;
	TLabel *Flag;
	TLabel *Label1;
	TEdit *MName;
	TLabel *Label2;
	TBevel *Bevel1;
	TImage *Image2;
    TLabel *Model;
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall btnCancelarClick(TObject *Sender);
	
	
	void __fastcall HSizeKeyPress(TObject *Sender, char &Key);
	void __fastcall VSizeKeyPress(TObject *Sender, char &Key);
	
	                                        
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMProp(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMProp *MProp;
//---------------------------------------------------------------------------
#endif
