//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TfrmPrincipal.h"

#include "Sobre.h"
#include "ObjProp.h"
#include "ModelProp.h"
#include "frmConn.h"
#include "TFrmWait.h"
#include "ConnectDialog.h"

#include "ModelHandler.h"
#include "Interface.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

ModelHandler *H;
TfrmPrincipal *frmPrincipal;

//---------------------------------------------------------------------------
__fastcall TfrmPrincipal::TfrmPrincipal(TComponent* Owner, int Dummy)
    : TForm(Owner, Dummy)
{
    block = false;
}
__fastcall TfrmPrincipal::TfrmPrincipal(TComponent* Owner)
    : TForm(Owner)
{
    block = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SendSelecionaObjeto(int IdObjeto, int xoffset, int yoffset)
{
    try
    {
        ClientSocket->Socket->SendText("<#slct " + AnsiString(ConnectionId) + "~" + IdObjeto + "$" + AnsiString(xoffset) + "," + AnsiString(yoffset) + "#>");
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SendArrasta(int X, int Y)
{
    try
    {
        ClientSocket->Socket->SendText("<#drag " + AnsiString(ConnectionId) + "~" + AnsiString(X) + "," + AnsiString(Y) + "#>");
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SendFimArrasta()
{
    // Fim Drag FmDg
    try
    {
        ClientSocket->Socket->SendText("<#FmDg " + AnsiString(ConnectionId) + "#>");
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SendRedimensiona(int pin, int X, int Y)
{
    try
    {
        ClientSocket->Socket->SendText("<#resz " + AnsiString(ConnectionId) +
        "(" + AnsiString(pin) + ")" + AnsiString(X) + "," + AnsiString(Y) + "#>");
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SendFimRedimensiona(int pin)
{
    try
    {
        ClientSocket->Socket->SendText("<#frsz " + AnsiString(ConnectionId) +
        "~" + AnsiString(pin) + "#>");
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SendMouseMove(int X, int Y)
{
    try
    {
        ClientSocket->Socket->SendText("<#move " + AnsiString(ConnectionId) +
        "~" + AnsiString(X) + "," + AnsiString(Y) + "#>");
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SendLigacao(int IdObjeto)
{
    try
    {
        ClientSocket->Socket->SendText("<#ilig " + AnsiString(ConnectionId) +
        "~" + IdObjeto + "#>");
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SendMoveLigacao(int X, int Y)
{
    try
    {
        ClientSocket->Socket->SendText("<#mlig " + AnsiString(ConnectionId) +
        "~" + AnsiString(X) + "," + AnsiString(Y) + "#>");
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SendFimLigacao(int type, int IdObjeto)
{
    try
    {
        ClientSocket->Socket->SendText("<#flig " + AnsiString(ConnectionId) +
        "~" + AnsiString(type) + "$" + IdObjeto + "#>");
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SendFimLigacaoAssociativa(int type, int IdA, int IdB)
{
    try
    {
        ClientSocket->Socket->SendText("<#flga " + AnsiString(ConnectionId) +
        "~" + AnsiString(type) + "$" + AnsiString(IdA) + "," + AnsiString(IdB) + "#>");
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SendPrepareToInsert()
{
    try
    {
        ClientSocket->Socket->SendText("<#prep " + AnsiString(ConnectionId) + "#>");
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SendMoveInsercao(int X, int Y)
{
    try
    {
        ClientSocket->Socket->SendText("<#mvin " + AnsiString(ConnectionId) +
        "~" + AnsiString(X) + "," + AnsiString(Y) + "#>");
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SendInsercao(int Type, AnsiString nomeObjeto, double Id, int X, int Y)
{
    try
    {
        ClientSocket->Socket->SendText("<#inst " + AnsiString(ConnectionId) +
        "~" + AnsiString(Type) + "$" + nomeObjeto + "@" + AnsiString(Id) + "#" + AnsiString(X) + "," + AnsiString(Y) + "#>");
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SendDeleteObjeto(double Id)
{
    try
    {
        ClientSocket->Socket->SendText("<#delo " + AnsiString(ConnectionId) +
        "~" + AnsiString(Id) + "#>");
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SendDeleteConector(double IdA, double IdB)
{
    try
    {
        ClientSocket->Socket->SendText("<#delc " + AnsiString(ConnectionId) +
        "~" + AnsiString(IdA) + "$" + AnsiString(IdB) + "#>");
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SendDeleteConectorAssociacao(double IdA, double IdEndA, double IdEndB)
{
    try
    {
        ClientSocket->Socket->SendText("<#dlca " + AnsiString(ConnectionId) +
        "~" + AnsiString(IdA) + "$" + AnsiString(IdEndA) + "@" + AnsiString(IdEndB) + "#>");
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::BBoardMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (MovieMode) return;
    H->MouseDown(BBoard, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::BBoardMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    if (MovieMode) return;
    try
    {
        H->MouseMove(BBoard, X, Y);
    }
    catch(...)
    {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::BBoardMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (MovieMode) return;
    H->MouseUp(BBoard, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tb_NewDiagramClick(TObject *Sender)
{
    AnsiString Name = "";

    if(H->Modificado())
    {
        char Msg[1000];
        sprintf(Msg, "Do you want to save the changes in the model '%s' ?", (*H->ModelName).c_str());
        if(MessageBox(0, Msg, "Attention", MB_YESNO | MB_ICONQUESTION)!=7)
        {
              if(*H->ModelFileName != "")
              {
                    H->ExportaModelo(*H->ModelFileName);
              }
              else
              {
                    SaveDialog->FileName= "*.hxm";
                    SaveDialog->Execute();
                    if(SaveDialog->FileName.AnsiPos(".hxm") == 0)
                    {
                         SaveDialog->FileName += ".hxm";
                    }
                    else if(SaveDialog->FileName == "*.hxm")
                         return;
                    H->ExportaModelo(SaveDialog->FileName);
              }
        }
    }

    actNewModelExecute(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::Exit1Click(TObject *Sender)
{
     Close();    
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mSaveClick(TObject *Sender)
{
     if(*H->ModelFileName != "")
     {
          H->ExportaModelo(*H->ModelFileName);
     }
     else
     {
          SaveDialog->FileName= "*.hxm";
          SaveDialog->Execute();
          if(SaveDialog->FileName.AnsiPos(".hxm") == 0)
          {
               SaveDialog->FileName += ".hxm";
          }
          else if(SaveDialog->FileName == "*.hxm")
               return;
          H->ExportaModelo(SaveDialog->FileName);
     }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tb_OpenDiagramClick(TObject *Sender)
{
	// Trata do modelo atual
    if(H->Modificado())
    {
        char Msg[1000];
        sprintf(Msg, "Do you want to save the changes in the model '%s' ?", (*H->ModelName).c_str());
        if(MessageBox(0, Msg, "Attention", MB_YESNO | MB_ICONQUESTION)!=7)
        {
              if(*H->ModelFileName != "")
              {
                    H->ExportaModelo(*H->ModelFileName);
              }
              else
              {
                    if(H->TemNome())
                         SaveDialog->FileName= *H->ModelFileName;
                    else
                         SaveDialog->FileName= "*.hxm";

                    SaveDialog->Execute();
                    if(SaveDialog->FileName.AnsiPos(".hxm") == 0)
                    {
                         SaveDialog->FileName += ".hxm";
                    }
                    else if(SaveDialog->FileName == "*.hxm")
                         return;
                    H->ExportaModelo(SaveDialog->FileName);
              }
        }
    }

     // Abre um modelo novo
     OpenDialog->FileName= "*.hxm";
     OpenDialog->Execute();
     FILE *pf;
     char Path[500];
     strcpy(Path, OpenDialog->FileName.c_str());
     pf=fopen(Path, "r");
     if(pf == NULL) return;
     H->ImportaModelo(OpenDialog->FileName, BBoard);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::About1Click(TObject *Sender)
{
    About->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mSaveAsClick(TObject *Sender)
{
    SaveDialog->FileName= "*.hxm";
    SaveDialog->Execute();
    if(SaveDialog->FileName.AnsiPos(".hxm") == 0)
    {
         SaveDialog->FileName += ".hxm";
    }
    else if(SaveDialog->FileName == "*.hxm")
         return;
    H->ExportaModelo(SaveDialog->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::DeleteObjectClick(TObject *Sender)
{
    H->Delete(BBoard);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mPropertiesClick(TObject *Sender)
{
/*
     // Preenche com os valores atuais...
     MProp->MName->Text = *(H->ModelName);
 	 MProp->MDescription->Clear();
     MProp->MDescription->Lines = (H->LinhasDescricao);
     MProp->MLastModified->Caption = *(H->LastModified);
     MProp->MDomain->Caption = "Telecomunicações";
     MProp->HSize->Text = *H->HSize;
     MProp->VSize->Text = *H->VSize;

     // Chama a janela de propriedades...
     MProp->ShowModal();

     if(MProp->Flag->Caption == "1") // Botão OK
     {
		 AnsiString Name = "";
     	 *(H->ModelName) = MProp->MName->Text;
         H->SetBounds(MProp->HSize->Text.ToInt(), MProp->VSize->Text.ToInt(), BBoard);
		 H->LinhasDescricao->Assign(MProp->MDescription->Lines);
      	 NomeModelo->Caption = MProp->MName->Text;
     }
*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    actCheckSavedExecute(Sender);
    ClientSocket->Close();

    for (int i=0; i<ListaArquivos->Count; i++)
        DeleteFile(DirInicial->Directory + "\\" + ListaArquivos->Strings[i]);

    ListaArquivos->Clear();
    delete ListaArquivos;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::BBoardPaint(TObject *Sender)
{
     if(*H->ScreenLockUpdate == false)
     {
          H->Paint(BBoard->Canvas);
     }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::Refresh1Click(TObject *Sender)
{
	BBoard->Refresh();
	H->Paint(BBoard->Canvas);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tb_PropertiesClick(TObject *Sender)
{
     Objeto *ObjTemp;
     Connector *ConnTemp;

     ObjTemp = H->getSelectedObject();
     ConnTemp = H->getSelectedConnector();

     if(ObjTemp != 0)
     {
         AnsiString nome;
         nome = *ObjTemp->Label;
	     Propriedades(ObjTemp, BBoard);
         if (nome != *ObjTemp->Label)
         {
             // rename Object
             ClientSocket->Socket->SendText(
               "<#rnmo " + AnsiString(ConnectionId) + "~" + *ObjTemp->Id + "$" + *ObjTemp->Label + "#>");
         }
     }
     else if(ConnTemp != 0)
     {
         AnsiString nome;
         nome = *ConnTemp->Label;
	     PropriedadesConn(ConnTemp, BBoard);
         if (nome != *ConnTemp->Label)
         {
             // rename Conector
             ClientSocket->Socket->SendText(
               "<#rnmc " + AnsiString(ConnectionId) + "~" + *ConnTemp->A->Id + "@" + *ConnTemp->B->Id + "$" + *ConnTemp->Label + "#>");
         }
     }

     BBoard->Refresh();
     H->Paint(BBoard->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::NewObjectClick(TObject *Sender)
{
     H->PrepareToInsert(oRetangulo);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::mNewClick(TObject *Sender)
{
    tb_NewDiagramClick(Sender);    
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::mOpenClick(TObject *Sender)
{
    tb_OpenDiagramClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tb_SaveDiagramClick(TObject *Sender)
{
    mSaveClick(Sender);    
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::ClientSocketConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    StatusBar1->Panels->Items[0]->Text = "Connected to Server: " + Socket->RemoteHost;
    ClientSocket->Socket->SendText("<#join " + frmConnect->ed_NickName->Text + "#>");
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::ClientSocketDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    tb_NewDiagram->Enabled = true;
    tb_OpenDiagram->Enabled = true;
    tb_SaveDiagram->Enabled = true;
    mNew->Enabled = true;
    mOpen->Enabled = true;
    mSave->Enabled = true;
    mSaveAs->Enabled = true;
    mProperties->Enabled = true;
    ToolBar->Enabled = true;
    mnuMovie->Enabled = true;
    tb_Movie->Enabled = true;
    tb_ConnectServer->Enabled = true;
    mnuConnectServer->Enabled = true;
    mnuSaveChat->Enabled = true;
    ToolBar->Enabled = true;

    StatusBar1->Panels->Items[0]->Text = "Disconnected...";
    pc_Grupo->Enabled = false;

    // Ponho visible = false nos telepointers
    for (int i=0; i<Mouses->Count;i++)
        ((TLabel*)Mouses->Items[i])->Visible = false;

    for (int i=0; i<Setas->Count;i++)
        ((TImage*)Setas->Items[i])->Visible = false;

    Mouses->Clear();
    Setas->Clear();

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::ClientSocketError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
    StatusBar1->Panels->Items[0]->Text = "Error connecting to: " + frmConnect->ed_ServerName->Text;
    ErrorCode = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::MoveMouse2(int indice, int X, int Y)
{
    if(indice<0) return;
                                        
    BBoard->Canvas->Pen->Mode = pmCopy;
    BBoard->Canvas->Brush->Style = bsClear;
                        
    TImage *img;
    img = (TImage*)Setas->Items[indice];

    TLabel *lbl;
    lbl = (TLabel*)Mouses->Items[indice];

    X -= sbArea->HorzScrollBar->Position;
    Y -= sbArea->VertScrollBar->Position;
    img->Left = X;
    img->Top = Y;
    lbl->Left = X + im_seta->Width;
    lbl->Top = Y + im_seta->Height;
    img->Visible = true;
    lbl->Visible = true;
}
//---------------------------------------------------------------------------
void TfrmPrincipal::SetVisibleMouse(int indice, bool value)
{
    if(indice<0)return;

    TImage *img;
    img = (TImage*)Setas->Items[indice];
    img->Visible = value;

    TLabel *lbl;
    lbl = (TLabel*)Mouses->Items[indice];
    lbl->Visible = value;
}
//---------------------------------------------------------------------------
int __fastcall TfrmPrincipal::GetFunctionNumber(int member)
{
    if (member<0)return member;
    if (MovieMode)
    {
        return member;
    }
    else if (ConnectionId == 0)
    {
        if (member == 1)
            return 0;
        else if(member == 2)
            return 1;
        else
            return 2;
    }
    else if (ConnectionId == 1)
    {
        if (member == 0)
            return 0;
        else if(member == 2)
            return 1;
        else
            return 2;
    }
    else if (ConnectionId == 2)
    {
        if (member == 0)
            return 0;
        else if(member == 1)
            return 1;
        else
            return 2;
    }
    else if (ConnectionId == 3)
    {
        if (member == 0)
            return 0;
        else if(member == 1)
            return 1;
        else
            return 2;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::ParseData(AnsiString data)
{
    AnsiString comando, param;
    comando = data.SubString(3, 4);
    param = data.SubString(8, data.Length()-9);

    if (comando == "move") // mouse move             
    {
        int quem, posTil, posVirg, x, y;
        posTil = param.Pos("~");                         
        posVirg = param.Pos(",");
        quem = param.SubString(1, posTil-1).ToInt();
        x = param.SubString(posTil+1, (posVirg-1)-posTil).ToInt();
        y = param.SubString(posVirg+1, param.Length()).ToInt();
        MoveMouse2(GetFunctionNumber(quem), x, y);
    }
    else if(comando == "drag") // move objeto
    {              
        int quem, posTil, posVirg, x, y;
        posTil = param.Pos("~");
        posVirg = param.Pos(",");       
        quem = param.SubString(1, posTil-1).ToInt();
        x = param.SubString(posTil+1, (posVirg-1)-posTil).ToInt();
        y = param.SubString(posVirg+1, param.Length()).ToInt();
        H->Arrasta2(GetFunctionNumber(quem), BBoard, x, y);
    }
    else if(comando == "mlig") // move ligação
    {
        int quem, posTil, posVirg, x, y;
        posTil = param.Pos("~");
        posVirg = param.Pos(",");
        quem = param.SubString(1, posTil-1).ToInt();
        x = param.SubString(posTil+1, (posVirg-1)-posTil).ToInt();
        y = param.SubString(posVirg+1, param.Length()).ToInt();
        H->FinalizaConexao2(GetFunctionNumber(quem), BBoard, x, y);
    }
    else if(comando == "mvin") // move insercao
    {
        int quem, posTil, posVirg, x, y;
        posTil = param.Pos("~");
        posVirg = param.Pos(",");
        quem = param.SubString(1, posTil-1).ToInt();
        x = param.SubString(posTil+1, (posVirg-1)-posTil).ToInt();
        y = param.SubString(posVirg+1, param.Length()).ToInt();
        H->MoveInsercao2(GetFunctionNumber(quem), BBoard->Canvas, x, y);
        SetVisibleMouse(GetFunctionNumber(quem), false);
    }
    else if (comando == "farq") // fim arquivo
    {
        AnsiString NomeArquivo;

        randomize();
        NomeArquivo = "_temp" + AnsiString(random(1000)) + ".hxm";

        mm_Data->Lines->SaveToFile(NomeArquivo);
        H->ImportaModelo(DirInicial->Directory + "\\" + NomeArquivo, BBoard);

        ListaArquivos->Add(NomeArquivo);

        pn_ModelName->Caption = *H->ModelName;
    }
    else if(comando == "memb") // new member
    {
        lb_Users->Items->Add(param);

        TImage *img;    
        TLabel *lbl;        
        img = new TImage(Application);
        lbl = new TLabel(Application);

        img->Picture = im_seta->Picture;
        img->AutoSize = true;        
        img->Transparent = true;
        lbl->AutoSize = true;
        lbl->Caption = param;
        lbl->Font->Color = clNavy;
        lbl->Transparent = true;

        img->Parent = sbArea;
        lbl->Parent = sbArea;

        img->Visible = false;
        lbl->Visible = false;

        Mouses->Add(lbl);
        Setas->Add(img);
    }
    else if(comando == "chat") // chat
    {
        if (MovieMode)
        {
            AnsiString msg;
            int quem, posTil;
            posTil = param.Pos("~");
            quem = param.SubString(1, posTil-1).ToInt();
            msg = param.SubString(posTil+1, param.Length()-posTil);
            mm_Chat->Lines->Add("<" + lb_Users->Items->Strings[quem] + ">" + msg);
        }
        else
            mm_Chat->Lines->Add(param);
    }
    else if(comando == "line") // line
    {
        mm_Data->Lines->Add(param);
    }
    else if(comando == "resz") // resize
    {
        int quem, posAbre, posFecha, posVirg, pin, x, y;
        posAbre = param.Pos("(");
        posFecha = param.Pos(")");
        posVirg = param.Pos(",");
        quem = param.SubString(1, posAbre-1).ToInt();
        pin = param.SubString(posAbre+1, (posFecha-1)-posAbre).ToInt();
        x = param.SubString(posFecha+1, (posVirg-1)-posFecha).ToInt();
        y = param.SubString(posVirg+1, param.Length()-posVirg).ToInt();
        H->Redimensiona2(GetFunctionNumber(quem), BBoard, pin, x, y);
    }
    else if(comando == "slct") // select
    {
        int posDol, posVirg, xoffset, yoffset, quem, posTil;
        double IdObjeto;
        posTil = param.Pos("~");
        posDol = param.Pos("$");
        posVirg = param.Pos(",");
        quem = param.SubString(1, posTil-1).ToInt();
        IdObjeto = param.SubString(posTil+1, posDol-1-posTil).ToInt();
        xoffset = param.SubString(posDol+1, posVirg-1-posDol).ToInt();
        yoffset = param.SubString(posVirg+1, param.Length()-posVirg).ToInt();

        H->SetSelecionado2(GetFunctionNumber(quem), IdObjeto, xoffset, yoffset);
        SetVisibleMouse(GetFunctionNumber(quem), false);
    }
    else if(comando == "inst") // Inserção de Objeto
    {
        int posDol, posTil, posArr, posTralha, posVirg, type, quem, X, Y;
        double IdObjeto;
        AnsiString nomeObjeto;
        posTil = param.Pos("~");
        posDol = param.Pos("$");
        posArr = param.Pos("@");
        posTralha = param.Pos("#");
        posVirg = param.Pos(",");
        quem = param.SubString(1, posTil-1).ToInt();
        type = param.SubString(posTil+1, posDol-1-posTil).ToInt();
        nomeObjeto = param.SubString(posDol+1, posArr-1-posDol);
        IdObjeto = param.SubString(posArr+1, posTralha-1-posArr).ToDouble();
        X = param.SubString(posTralha+1, posVirg-1-posTralha).ToInt();
        Y = param.SubString(posVirg+1, param.Length()-posVirg).ToInt();
        H->InsereObjeto2(GetFunctionNumber(quem), BBoard, type, nomeObjeto, IdObjeto, X, Y);
    }
    else if(comando == "flig") // Fim ligação
    {
        int posDol, posTil, type, quem;
        double IdObjeto;
        posDol = param.Pos("$");
        posTil = param.Pos("~");
        quem = param.SubString(1, posTil-1).ToInt();
        type = param.SubString(posTil+1, posDol-1-posTil).ToInt();
        IdObjeto = param.SubString(posDol+1, param.Length()-posDol).ToInt();
        H->Conecta2(GetFunctionNumber(quem), BBoard->Canvas, type, IdObjeto);
    }
    else if(comando == "flga") // Fim ligação Associativa
    {
        int posDol, posTil, posVirg, type, quem;
        double IdA, IdB;
        posDol = param.Pos("$");
        posTil = param.Pos("~");
        posVirg = param.Pos(",");
        quem = param.SubString(1, posTil-1).ToInt();
        type = param.SubString(posTil+1, posDol-1-posTil).ToInt();
        IdA = param.SubString(posDol+1, posVirg-1-posDol).ToInt();
        IdB = param.SubString(posVirg+1, param.Length()-posVirg).ToInt();
        H->ConectaAssociativo2(GetFunctionNumber(quem), BBoard->Canvas, type, IdA, IdB);
    }
    else if(comando == "ilig") // inicio ligação
    {
        int quem, posTil;
        double IdObjeto;
        posTil = param.Pos("~");
        quem = param.SubString(1, posTil-1).ToInt();
        IdObjeto = param.SubString(posTil+1, param.Length()-posTil).ToInt();
        H->SetOrigem2(GetFunctionNumber(quem), IdObjeto);
        SetVisibleMouse(GetFunctionNumber(quem), false);
    }
    else if(comando == "delo") // Delete Objeto
    {
        int quem, posTil;
        double IdObjeto;
        posTil = param.Pos("~");
        quem = param.SubString(1, posTil-1).ToInt();
        IdObjeto = param.SubString(posTil+1, param.Length()-posTil).ToInt();
        H->DeleteObjeto2(GetFunctionNumber(quem), BBoard, IdObjeto);
    }
    else if(comando == "delc") // Delete Conector
    {
        AnsiString sender;
        int quem, posTil, posDol;            
        double IdA, IdB;                         
        posTil = param.Pos("~");
        posDol = param.Pos("$");
        quem = param.SubString(1, posTil-1).ToInt();
        IdA = param.SubString(posTil+1, posDol-1-posTil).ToInt();
        IdB = param.SubString(posDol+1, param.Length()-posDol).ToInt();
        H->DeleteConector2(GetFunctionNumber(quem), BBoard, IdA, IdB);
    }
    else if(comando == "join") // join session
    {
        int n = param.ToInt();
        if (n >= 0)
        {
            ConnectionId = n;
            pc_Grupo->Enabled = true;
            pn_Info->Visible = true;
            pc_Grupo->ActivePage = ts_General;
            ed_Fala->SetFocus();
            spl_Divide->Align = alRight;
            lb_Users->Items->Clear();
            lb_Users->Items->Add(frmConnect->ed_NickName->Text);

            tb_NewDiagram->Enabled = false;
            tb_OpenDiagram->Enabled = false;
            tb_SaveDiagram->Enabled = false;
            mNew->Enabled = false;
            mOpen->Enabled = false;
            mSave->Enabled = false;
            mSaveAs->Enabled = false;
            mProperties->Enabled = false;
            ToolBar->Enabled = true;
            mnuMovie->Enabled = false;
            tb_Movie->Enabled = false;
            tb_ConnectServer->Enabled = false;
            mnuConnectServer->Enabled = false;
            mnuSaveChat->Enabled = true;
        }
        else if (n == -1)
        {
            block = true;
            MessageBox(0, "You were not allowed to enter the cooperative diagram session because this session is full.", "Join Error", MB_ICONEXCLAMATION);
            block = false;
            ClientSocket->Close();
        }
        else if (n == -2)      
        {                         
            block = true;
            MessageBox(0, "Someone is already logged with this nickname. Change it and try again!", "Join Error", MB_ICONEXCLAMATION);
            block = false;
            ClientSocket->Close();
        }
        else if (n == -3)
        {
            block = true;
            MessageBox(0, "The diagram session you are trying to join has already started! Users are allowed to join a session only before it starts.", "Join Error", MB_ICONEXCLAMATION);
            block = false;
            ClientSocket->Close();
        }
    }
    else if(comando == "dlca") // Delete Conector Associacao
    {
        AnsiString sender;
        int quem, posTil, posDol, posArr;
        double IdA, IdEndA, IdEndB;
        posTil = param.Pos("~");
        posDol = param.Pos("$");
        posArr = param.Pos("@");
        quem = param.SubString(1, posTil-1).ToInt();
        IdA = param.SubString(posTil+1, posDol-1-posTil).ToInt();
        IdEndA = param.SubString(posDol+1, posArr-1-posDol).ToInt();
        IdEndB = param.SubString(posArr+1, param.Length()-posArr).ToInt();
        H->DeleteConectorAssociacao2(GetFunctionNumber(quem), BBoard, IdA, IdEndA, IdEndB);
    }
    else if(comando == "rnmo") // Rename object
    {
        AnsiString sender, nomeNovo;
        int quem, posTil, posDol, Id;
        posTil = param.Pos("~");
        posDol = param.Pos("$");
        quem = param.SubString(1, posTil-1).ToInt();
        Id = param.SubString(posTil+1, posDol-1-posTil).ToInt();
        nomeNovo = param.SubString(posDol+1, param.Length()-posDol);

        H->RenameSelecionado2(GetFunctionNumber(quem), Id, nomeNovo, BBoard);
        BBoard->Refresh();
        H->Paint(BBoard->Canvas);
    }
    else if(comando == "rnmc") // Rename connector
    {
        AnsiString sender, nomeNovo;
        int quem, posTil, posDol, posArr, IdA, IdB;
        posTil = param.Pos("~");
        posDol = param.Pos("$");
        posArr = param.Pos("@");
        quem = param.SubString(1, posTil-1).ToInt();
        IdA = param.SubString(posTil+1, posArr-1-posTil).ToInt();
        IdB = param.SubString(posArr+1, posArr-1-posTil).ToInt();
        nomeNovo = param.SubString(posDol+1, param.Length()-posDol);
        // Trato o rename
        H->RenameSelecionadoConn2(GetFunctionNumber(quem), IdA, IdB, nomeNovo, BBoard);
        BBoard->Refresh();
        H->Paint(BBoard->Canvas);
    }
    else if(comando == "FmDg") // Fim drag
    {
        int quem;
        quem = param.ToInt();
        H->SetAllVisible2(GetFunctionNumber(quem), BBoard);
    }
    else if(comando == "prep") // PrepareToInsert
    {
        int quem;
        quem = param.ToInt();    
        H->PrepareToInsert2(GetFunctionNumber(quem));
    }
    else if(comando == "newd") // New Diagram
    {
  	    H->NewModel(BBoard, param);
		H->LinhasDescricao->Clear();
        pn_ModelName->Caption = param;

        tb_SaveDiagram->Enabled = true;
        mSave->Enabled = true;
        mSaveAs->Enabled = true;
        ToolBar->Enabled = true;
    }
    else if(comando == "frsz") // fim resize
    {
        int quem, posTil, pin;
        posTil = param.Pos("~");
        quem = param.SubString(1, posTil-1).ToInt();
        pin = param.SubString(posTil+1, param.Length()-posTil).ToInt();
        H->AcertaNovoTamanho2(GetFunctionNumber(quem), BBoard, pin);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::ClientSocketRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
    if (block) return;

    AnsiString data, comando;
    int pos;

    data = Socket->ReceiveText();
    ParteComando += data;

    pos = ParteComando.Pos("#>");
    while(pos != 0)
    {
        comando = ParteComando.SubString(1, pos+1);
        try
        {
            ParseData(comando);
            ParteComando = ParteComando.SubString(pos+2, ParteComando.Length());
            pos = ParteComando.Pos("#>");
        }
        catch(...){}
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tb_ConnectServerClick(TObject *Sender)
{
    actCheckSavedExecute(Sender);
    if (ClientSocket->Active)
    {
        ClientSocket->Active = false;
    }

    if (frmConnect->ed_NickName->Text == "")
    {
        frmConnect->ed_NickName->Text = LoginUserName();
    }
    frmConnect->ShowModal();

    if (frmConnect->Flag->Caption == "1")
    {
        H->NewModel(BBoard, "Groupware model");
        ParteComando = "";
        mm_Data->Lines->Clear();
        ClientSocket->Host = frmConnect->ed_ServerName->Text;
        ClientSocket->Active = true;
        StatusBar1->Panels->Items[0]->Text = "Connecting to: " + frmConnect->ed_ServerName->Text + "...";
        H->setModified(false);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::ed_FalaKeyPress(TObject *Sender, char &Key)
{
    if (Key == VK_RETURN && ed_Fala->Text != "" && !MovieMode)
    {
        ClientSocket->Socket->SendText("<#chat " + AnsiString(ConnectionId) + "~" + ed_Fala->Text + "#>");
        mm_Chat->Lines->Add("<" + AnsiString(frmConnect->ed_NickName->Text) + "> " + ed_Fala->Text);
        ed_Fala->Text = "";
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::actCheckSavedExecute(TObject *Sender)
{
    if(H->Modificado())
    {
        char Msg[1000];
        sprintf(Msg, "Do you want to save the changes in the model '%s' ?", (*H->ModelName).c_str());

        int Resp = MessageBox(0, Msg, "Attention", MB_YESNOCANCEL | MB_ICONQUESTION);
        if(Resp == IDCANCEL)
        {
                Action = caNone;
                return;
        }
        if(Resp!=7)
        {
              if(*H->ModelFileName != "")
              {
                    H->ExportaModelo(*H->ModelFileName);
              }
              else
              {
                    if(H->TemNome())
                         SaveDialog->FileName= *H->ModelFileName;
                    else
                         SaveDialog->FileName= "*.hxm";

                    SaveDialog->Execute();
                    if(SaveDialog->FileName.AnsiPos(".hxm") == 0)
                    {
                         SaveDialog->FileName += ".hxm";
                    }
                    else if(SaveDialog->FileName == "*.hxm")
                         return;
                    H->ExportaModelo(SaveDialog->FileName);
              }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::actNewModelExecute(TObject *Sender)
{
     MProp->MName->Text = "New Class Diagram";
     // Chama a janela de propriedades...
     MProp->ShowModal();

     if(MProp->Flag->Caption == "1") // Botão OK
     {
  	    H->NewModel(BBoard, MProp->MName->Text);
//        *H->Dominio = "Telecomunicações";
//        H->SetBounds(1000, 1000, BBoard);
		H->LinhasDescricao->Clear();
        pn_ModelName->Caption = MProp->MName->Text;
     }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::ItemSpecification1Click(TObject *Sender)
{
    tb_PropertiesClick(Sender);    
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::mnuConnectServerClick(TObject *Sender)
{
    tb_ConnectServerClick(Sender);    
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SpeedButton2Click(TObject *Sender)
{
     H->PrepareToInsert(oRetangulo);    
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::SpeedButton4Click(TObject *Sender)
{
    H->PrepareConnection(cReta);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::SpeedButton3Click(TObject *Sender)
{
    H->PrepareConnection(cAgregacao);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::SpeedButton5Click(TObject *Sender)
{
    H->PrepareConnection(cComposicao);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::SpeedButton6Click(TObject *Sender)
{
    H->PrepareConnection(cDependencia);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SpeedButton7Click(TObject *Sender)
{
    H->PrepareConnection(cSetaHeranca);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SpeedButton8Click(TObject *Sender)
{
    H->PrepareConnection(cAssociacao);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuMovieClick(
      TObject *Sender)
{
    MovieMode = 1;

    mnuMovie->Enabled = false;
    tb_Movie->Enabled = false;
    tb_NewDiagram->Enabled = false;
    tb_OpenDiagram->Enabled = false;
    tb_SaveDiagram->Enabled = false;
    mNew->Enabled = false;
    mOpen->Enabled = false;
    mSave->Enabled = false;
    mSaveAs->Enabled = false;
    mProperties->Enabled = false;
    ToolBar->Enabled = false;
    tb_ConnectServer->Enabled = false;
    mnuConnectServer->Enabled = false;
    mnuSaveChat->Enabled = false;

    pn_Movie->Visible = true;
    pn_Info->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tb_MovieClick(TObject *Sender)
{
    mnuMovieClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnEndMovieClick(TObject *Sender)
{
    tm_Movie->Enabled = false;

    MovieMode = 0;

    mnuMovie->Enabled = true;
    tb_Movie->Enabled = true;
    tb_NewDiagram->Enabled = true;
    tb_OpenDiagram->Enabled = true;
    tb_SaveDiagram->Enabled = true;
    mNew->Enabled = true;
    mOpen->Enabled = true;
    mSave->Enabled = true;
    mSaveAs->Enabled = true;
    mProperties->Enabled = true;
    ToolBar->Enabled = true;
    tb_ConnectServer->Enabled = true;
    mnuConnectServer->Enabled = true;
    mnuSaveChat->Enabled = false;

    pn_Movie->Visible = false;
    pn_Info->Visible = false;

    for (int i=0; i<Mouses->Count;i++)
        ((TLabel*)Mouses->Items[i])->Visible = false;

    for (int i=0; i<Setas->Count;i++)
        ((TImage*)Setas->Items[i])->Visible = false;
    Mouses->Clear();
    Setas->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnOpenMovieClick(TObject *Sender)
{
    // Abre um modelo novo
    StartMovie = 0;
    MoviePosition = 0;
    OpenDialog->FileName= "*.dmf";
    if(OpenDialog->Execute())
    {
        FILE *pf;
        char Path[500];
        strcpy(Path, OpenDialog->FileName.c_str());
        pf=fopen(Path, "r");
        if(pf == NULL) return;
        mm_Movie->Lines->LoadFromFile(OpenDialog->FileName);

        actStartMovieExecute(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPlayClick(TObject *Sender)
{
    tm_Movie->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnStopClick(TObject *Sender)
{
    tm_Movie->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRewindClick(TObject *Sender)
{
    actStartMovieExecute(Sender);
}                                      
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::trackChange(TObject *Sender)
{
    if(track->Position == 1)
      tm_Movie->Interval = 450;
    else if(track->Position == 2)
      tm_Movie->Interval = 350;
    else if(track->Position == 3)
      tm_Movie->Interval = 200;
    else if(track->Position == 4)
      tm_Movie->Interval = 150;
    else if(track->Position == 5)
      tm_Movie->Interval = 100;
    else if(track->Position == 6)
      tm_Movie->Interval = 50;
    else if(track->Position == 7)
      tm_Movie->Interval = 25;
    else if(track->Position == 8)
      tm_Movie->Interval = 12;
    else if(track->Position == 9)
      tm_Movie->Interval = 5;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tm_MovieTimer(TObject *Sender)
{
    if(MoviePosition == mm_Movie->Lines->Count)
    {
        tm_Movie->Enabled = false;
        btnRewind->Enabled = true;                                       
        btnPlay->Enabled = false;
        btnStop->Enabled = false;
    }                                                   
    ParseData(mm_Movie->Lines->Strings[MoviePosition]);
    pg_Movie->Position = (100*(MoviePosition - StartMovie))/(mm_Movie->Lines->Count - StartMovie - 1);
    MoviePosition++;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::actStartMovieExecute(TObject *Sender)
{
    if (mm_Movie->Lines->Strings[0] == "<new>")
    {
        StartMovie = 1;
        MoviePosition = 1;
        H->NewModel(BBoard, "New Diagram");
        H->LinhasDescricao->Clear();
        pn_ModelName->Caption = "New Diagram";
    }
    else
    {
        int FimDiagrama = mm_Movie->Lines->Strings[0].SubString(2, mm_Movie->Lines->Strings[0].Length()-2).ToInt();
        StartMovie = FimDiagrama;
        MoviePosition = FimDiagrama;

        mm_Data->Clear();
        for (int i=1; i<FimDiagrama; i++)
            mm_Data->Lines->Add(mm_Movie->Lines->Strings[i]);

        AnsiString NomeArquivo;
        randomize();
        NomeArquivo = "_temp" + AnsiString(random(1000)) + ".hxm";

        mm_Data->Lines->SaveToFile(DirInicial->Directory + "\\" + NomeArquivo);
        H->ImportaModelo(DirInicial->Directory + "\\" + NomeArquivo, BBoard);
        ListaArquivos->Add(NomeArquivo);

        pn_ModelName->Caption = *H->ModelName;
    }

    BBoard->Refresh();
    lb_Users->Clear();
    mm_Chat->Clear();

    // Ponho visible = false nos telepointers
    for (int i=0; i<Mouses->Count;i++)
        ((TLabel*)Mouses->Items[i])->Visible = false;

    for (int i=0; i<Setas->Count;i++)
        ((TImage*)Setas->Items[i])->Visible = false;

    Mouses->Clear();
    Setas->Clear();

    tm_Movie->Enabled = false;
    btnPlay->Enabled = true;
    btnStop->Enabled = true;

    pg_Movie->Position = 0;

    btnRewind->Enabled = true;
    btnPlay->Enabled = true;
    btnStop->Enabled = true;
    track->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::FormCreate(TObject *Sender)
{
    H = new ModelHandler();

    // Registro os eventos
    H->SetNotificacaoSelecaoObjeto(SendSelecionaObjeto);
    H->SetNotificacaoArrasta(SendArrasta);
    H->SetNotificacaoFimArrasta(SendFimArrasta);
    H->SetNotificacaoRedimensiona(SendRedimensiona);
    H->SetNotificacaoFimRedimensiona(SendFimRedimensiona);
    H->SetNotificacaoMouseMove(SendMouseMove);
    H->SetNotificacaoLigacao(SendLigacao);
    H->SetNotificacaoMoveLigacao(SendMoveLigacao);
    H->SetNotificacaoFimLigacao(SendFimLigacao);
    H->SetNotificacaoFimLigacaoAssociativa(SendFimLigacaoAssociativa);
    H->SetNotificacaoPrepareToInsert(SendPrepareToInsert);
    H->SetNotificacaoMoveInsercao(SendMoveInsercao);
    H->SetNotificacaoInsercao(SendInsercao);
    H->SetNotificacaoDeleteObjeto(SendDeleteObjeto);
    H->SetNotificacaoDeleteConector(SendDeleteConector);
    H->SetNotificacaoDeleteConectorAssociacao(SendDeleteConectorAssociacao);

    H->NewModel(BBoard, "New Model");
    H->setModified(false);

    OpenDialog->InitialDir = DirInicial->Directory;
    SaveDialog->InitialDir = DirInicial->Directory;

    ClientSocket->Active = false;

    Mouses = new TList();
    Setas = new TList();
    ListaArquivos = new TStringList();

    lb_Mouse->Left = -2000;
    lb_Mouse->Top = -2000;
    im_seta->Left = -2000;
    im_seta->Top = -2000;

    MovieMode = 0;
    StartMovie = 0;
    MoviePosition = 0;

    ConnectionId = -1;
    block = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::mnuSaveChatClick(TObject *Sender)
{
    SaveDialog->FileName= "*.txt";
    SaveDialog->Execute();
    if(SaveDialog->FileName.AnsiPos(".txt") == 0)
    {
       SaveDialog->FileName += ".txt";
    }
    else if(SaveDialog->FileName == "*.txt")
       return;
    mm_Chat->Lines->SaveToFile(SaveDialog->FileName);
}
//---------------------------------------------------------------------------

