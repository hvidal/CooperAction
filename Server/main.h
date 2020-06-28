//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1997 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>           
#include <Forms.hpp>
#include "ScktComp.hpp"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>                  
#include <Dialogs.hpp>
#include <FileCtrl.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmServer : public TForm
{
__published:	// IDE-managed Components
    TBevel *Bevel1;
    TStatusBar *StatusBar1;
    TServerSocket *ServerSocket;
    TPageControl *pc_Server;
    TTabSheet *ts_DiagramSession;
    TGroupBox *gb_1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *DiagramPath;
    TLabel *DiagramName;
    TLabel *ConnectedUsers;
    TListBox *ListaUsuarios;
    TBitBtn *btnBrowse;
    TOpenDialog *OpenDialog;
    TDirectoryListBox *DirInicial;
    TBevel *Bevel2;
    TBevel *Bevel3;
    TPanel *Panel1;
    TBitBtn *btnDisconnectUsers;
    TBitBtn *btnShutdown;
    TTabSheet *ts_Statistics;
    TPanel *Panel4;
    TPanel *Panel2;
    TStringGrid *sg_Usuarios;
    TTabSheet *TabSheet1;
    TPanel *Panel3;
    TMemo *mm_Movie;
    TBitBtn *btnSaveMovie;
    TSaveDialog *SaveDialog;
    TRadioButton *opt1;
    TRadioButton *opt2;
    TBitBtn *btnStart;
    TBevel *Bevel4;
    TBitBtn *btnStartNew;
    TLabel *Label3;
    TEdit *ed_Name;
    TBitBtn *btnCopy;
    void __fastcall ServerSocketClientRead(TObject *Sender,
      TCustomWinSocket *Socket);
    void __fastcall ServerSocketAccept(TObject *Sender,
      TCustomWinSocket *Socket);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall ServerSocketClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket);
    void __fastcall btnStartClick(TObject *Sender);
    void __fastcall btnBrowseClick(TObject *Sender);
    void __fastcall btnShutdownClick(TObject *Sender);
    void __fastcall btnDisconnectUsersClick(TObject *Sender);
    void __fastcall btnSaveMovieClick(TObject *Sender);
    void __fastcall opt1Click(TObject *Sender);
    void __fastcall opt2Click(TObject *Sender);
    void __fastcall btnStartNewClick(TObject *Sender);
    void __fastcall btnCopyClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ServerSocketClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
private:	// User declarations
public:		// User declarations
    int nUsers;                                     
    int nMessages;                                         
    TStringList *ListaNMensagens;
    TStringList *ListaMovendo, *ListaJoins;
    AnsiString ParteComando;
    __fastcall TfrmServer(TComponent* Owner);
    void ParseData(AnsiString data);
    void PreparaGridUsuarios();            
                       
    void AtualizaValoresComunicacao();
};             
                 
//---------------------------------------------------------------------------
extern PACKAGE TfrmServer *frmServer;
//---------------------------------------------------------------------------
#endif
