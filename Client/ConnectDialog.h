//---------------------------------------------------------------------------
#ifndef ConnectDialogH
#define ConnectDialogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>                            
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmConnect : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TBitBtn *btnOK;
    TBitBtn *btnCancel;
    TEdit *ed_NickName;
    TEdit *ed_ServerName;
    TLabel *Flag;
    void __fastcall btnOKClick(TObject *Sender);
    void __fastcall btnCancelClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ed_NickNameKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmConnect(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConnect *frmConnect;
//---------------------------------------------------------------------------
#endif
