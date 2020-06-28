//---------------------------------------------------------------------------

#ifndef TfrmWaitH
#define TfrmWaitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmWait : public TForm
{
__published:	// IDE-managed Components
    TLabel *lb_Info;
    TTimer *Timer;
    TLabel *lb_response;
    void __fastcall TimerTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmWait(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWait *frmWait;
//---------------------------------------------------------------------------
#endif
