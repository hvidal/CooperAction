//---------------------------------------------------------------------------
#ifndef TfrmPrincipalH
#define TfrmPrincipalH                             
//---------------------------------------------------------------------------
#include <Classes.hpp>            
#include <ExtCtrls.hpp>      
#include <Dialogs.hpp>            
#include <FileCtrl.hpp>
#include <ImgList.hpp>                      
#include <ScktComp.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>

//---------------------------------------------------------------------------
class TfrmPrincipal : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu1;
    TMenuItem *Model1;
    TMenuItem *mNew;
    TMenuItem *mOpen;
    TMenuItem *mSave;
    TMenuItem *mSaveAs;
    TMenuItem *N1;
    TMenuItem *Exit1;
    TMenuItem *Object1;
    TMenuItem *NewObject;
    TMenuItem *DeleteObject;
    TMenuItem *N2;
    TMenuItem *mProperties;
    TMenuItem *Window1;
    TMenuItem *Refresh1;
    TMenuItem *Help1;
    TMenuItem *About1;
    TToolBar *ToolBar1;
    TScrollBox *sbArea;
    TPaintBox *BBoard;
    TToolButton *tb_NewDiagram;
    TToolButton *tb_OpenDiagram;
    TToolButton *tb_SaveDiagram;
    TToolButton *ToolButton4;
    TOpenDialog *OpenDialog;
    TSaveDialog *SaveDialog;
    TDirectoryListBox *DirInicial;
    TImageList *ImageList1;
    TToolButton *tb_Properties;
    TToolButton *tb_ConnectServer;
    TToolButton *ToolButton15;
    TClientSocket *ClientSocket;
    TStatusBar *StatusBar1;
    TPanel *pn_Info;
    TPanel *Panel1;
    TActionList *actList;
    TAction *actCheckSaved;
    TAction *actNewModel;
    TMenuItem *ItemSpecification1;
    TMenuItem *N3;
    TMenuItem *mnuConnectServer;
    TPanel *ToolBar;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton3;
    TSpeedButton *SpeedButton4;
    TSpeedButton *SpeedButton5;
    TSpeedButton *SpeedButton6;
    TSpeedButton *SpeedButton7;
    TImage *im_seta;
    TLabel *lb_Mouse;
    TSplitter *spl_Divide;
    TPageControl *pc_Grupo;
    TTabSheet *ts_General;
    TSplitter *Splitter2;
    TPanel *Panel5;
    TListBox *lb_Users;
    TPanel *Panel6;
    TPanel *Panel9;
    TMemo *mm_Chat;
    TPanel *Panel2;
    TEdit *ed_Fala;
    TTabSheet *ts_DataExchange;
    TPanel *Panel7;
    TMemo *mm_Data;
    TPanel *Panel8;
    TMenuItem *mnuSaveChat;
    TPanel *pn_ModelName;
    TToolButton *ToolButton1;
    TSpeedButton *SpeedButton8;
    TToolButton *tb_Movie;
    TToolButton *ToolButton3;
    TPanel *pn_Movie;
    TTrackBar *track;
    TBitBtn *btnEndMovie;
    TBitBtn *btnOpenMovie;
    TBitBtn *btnPlay;
    TBevel *Bevel1;
    TBitBtn *btnStop;
    TLabel *lb_Speed;
    TBitBtn *btnRewind;
    TMenuItem *N4;
    TMenuItem *mnuMovie;
    TMemo *mm_Movie;
    TTimer *tm_Movie;
    TProgressBar *pg_Movie;
    TLabel *Label1;
    TAction *actStartMovie;
    void __fastcall BBoardMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall BBoardMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall BBoardMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall tb_NewDiagramClick(TObject *Sender);
    void __fastcall Exit1Click(TObject *Sender);
    void __fastcall mSaveClick(TObject *Sender);
    void __fastcall tb_OpenDiagramClick(TObject *Sender);
    void __fastcall About1Click(TObject *Sender);
    void __fastcall mSaveAsClick(TObject *Sender);
    void __fastcall DeleteObjectClick(TObject *Sender);
    void __fastcall mPropertiesClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall BBoardPaint(TObject *Sender);
    void __fastcall Refresh1Click(TObject *Sender);
    void __fastcall tb_PropertiesClick(TObject *Sender);
    void __fastcall NewObjectClick(TObject *Sender);
    void __fastcall mNewClick(TObject *Sender);
    void __fastcall mOpenClick(TObject *Sender);
    void __fastcall tb_SaveDiagramClick(TObject *Sender);
    void __fastcall ClientSocketConnect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ClientSocketDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ClientSocketError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
    void __fastcall ClientSocketRead(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall tb_ConnectServerClick(TObject *Sender);
    void __fastcall ed_FalaKeyPress(TObject *Sender, char &Key);
    void __fastcall actCheckSavedExecute(TObject *Sender);
    void __fastcall actNewModelExecute(TObject *Sender);
    void __fastcall ItemSpecification1Click(TObject *Sender);
    void __fastcall mnuConnectServerClick(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall SpeedButton4Click(TObject *Sender);
    void __fastcall SpeedButton3Click(TObject *Sender);
    void __fastcall SpeedButton5Click(TObject *Sender);
    void __fastcall SpeedButton6Click(TObject *Sender);
    void __fastcall SpeedButton7Click(TObject *Sender);
    void __fastcall SpeedButton8Click(TObject *Sender);
    void __fastcall mnuMovieClick(TObject *Sender);
    void __fastcall tb_MovieClick(TObject *Sender);
    void __fastcall btnEndMovieClick(TObject *Sender);
    void __fastcall btnOpenMovieClick(TObject *Sender);
    void __fastcall btnPlayClick(TObject *Sender);
    void __fastcall btnStopClick(TObject *Sender);
    void __fastcall btnRewindClick(TObject *Sender);
    void __fastcall trackChange(TObject *Sender);
    void __fastcall tm_MovieTimer(TObject *Sender);
    void __fastcall actStartMovieExecute(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall mnuSaveChatClick(TObject *Sender);
private:	// User declarations
    void SetVisibleMouse(int indice, bool value);
public:		// User declarations
    AnsiString NickName;
    int ConnectionId;                                  
    int MovieMode, StartMovie, MoviePosition;
    AnsiString ParteComando;
    TList *Mouses, *Setas;
    TStringList *ListaArquivos;
    bool block;

    void __fastcall ParseData(AnsiString data);

    void __fastcall SendSelecionaObjeto(int IdObjeto, int xoffset, int yoffset);
    void __fastcall SendArrasta(int X, int Y);
    void __fastcall SendFimArrasta();
    void __fastcall SendRedimensiona(int pin, int X, int Y);
    void __fastcall SendFimRedimensiona(int pin);
    void __fastcall SendMouseMove(int X, int Y);
    void __fastcall SendLigacao(int IdObjeto);
    void __fastcall SendMoveLigacao(int X, int Y);
    void __fastcall SendFimLigacao(int type, int IdObjeto);
    void __fastcall SendFimLigacaoAssociativa(int type, int IdA, int IdB);
    void __fastcall SendPrepareToInsert();
    void __fastcall SendMoveInsercao(int X, int Y);
    void __fastcall SendInsercao(int Type, AnsiString nomeObjeto, double Id, int X, int Y);
    void __fastcall SendDeleteObjeto(double Id);
    void __fastcall SendDeleteConector(double IdA, double IdB);
    void __fastcall SendDeleteConectorAssociacao(double IdA, double IdEndA, double IdEndB);

    __fastcall TfrmPrincipal(TComponent* Owner);
    __fastcall TfrmPrincipal(TComponent* Owner, int Dummy);    
    void __fastcall MoveMouse2(int indice, int X, int Y);

    int __fastcall GetFunctionNumber(int member);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPrincipal *frmPrincipal;
//---------------------------------------------------------------------------
#endif
