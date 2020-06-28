//---------------------------------------------------------------------------
#ifndef SobreH
#define SobreH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>                    
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>                 
#include <vcl\Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TAbout : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TLabel *Label3;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *CLOSE;
    TMemo *Memo1;
    TLabel *Label4;
    TImage *Image1;
        void __fastcall OKClick(TObject *Sender);
	void __fastcall Label2Click(TObject *Sender);
    void __fastcall CLOSEClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAbout *About;
//---------------------------------------------------------------------------
#endif
