//---------------------------------------------------------------------------

#ifndef TfrmMessageH
#define TfrmMessageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmError : public TForm
{
__published:	// IDE-managed Components
    TButton *OK;
    TLabel *lb_Msg;
    TImage *Image1;
    void __fastcall OKClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmError(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmError *frmError;
//---------------------------------------------------------------------------
#endif
