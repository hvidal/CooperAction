//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1997 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <vcl\IniFiles.hpp>

#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma link "ScktComp"
#pragma resource "*.dfm"

#define NUsers 3

TfrmServer *frmServer;

int started;

//---------------------------------------------------------------------------
__fastcall TfrmServer::TfrmServer(TComponent* Owner)
        : TForm(Owner)
{
    ParteComando = "";
    nMessages = 0;
    started = 0;
    ListaNMensagens = new TStringList();
    ListaMovendo = new TStringList();
    ListaJoins = new TStringList();    
    PreparaGridUsuarios();
    mm_Movie->Lines->Clear();
    mm_Movie->Lines->Add("");
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ServerSocketClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
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
            if (started)
                mm_Movie->Lines->Add(comando);
            ParteComando = ParteComando.SubString(pos+2, ParteComando.Length());
            pos = ParteComando.Pos("#>");
        }
        catch(...){}
    }
}
//---------------------------------------------------------------------------
void TfrmServer::ParseData(AnsiString data)
{
    AnsiString cmd, param;
    cmd = data.SubString(3, 4);
    param = data.SubString(8, data.Length()-9);

    if(cmd == "move")
    {
        if(!started)return;
        AnsiString sender, x, y;
        int quem, posTil, posVirg;
        posTil = param.Pos("~");
        posVirg = param.Pos(",");
        sender = param.SubString(1, posTil-1);
        quem = sender.ToInt();
        x = param.SubString(posTil+1, (posVirg-1)-posTil);
        y = param.SubString(posVirg+1, param.Length());
        for(int i=0; i<nUsers;i++)
        {
            if(i != quem) // Não preciso enviar para quem me enviou...
                ServerSocket->Socket->Connections[i]->SendText("<#move " + sender + "~" + x + "," + y + "#>");
        }
    }
    else if(cmd == "drag")
    {
        if(!started)return;
        AnsiString sender, x, y;
        int quem, posTil, posVirg;
        posTil = param.Pos("~");
        posVirg = param.Pos(",");
        sender = param.SubString(1, posTil-1);
        quem = sender.ToInt();
        x = param.SubString(posTil+1, (posVirg-1)-posTil);
        y = param.SubString(posVirg+1, param.Length());
        for(int i=0; i<nUsers;i++)
        {
            if(i != quem) // Não preciso enviar para quem me enviou...
                ServerSocket->Socket->Connections[i]->SendText("<#drag " + sender + "~" + x + "," + y + "#>");
        }
    }
    else if(cmd == "mlig")
    {
        if(!started)return;
        AnsiString sender, x, y;
        int quem, posTil, posVirg;
        posTil = param.Pos("~");
        posVirg = param.Pos(",");
        sender = param.SubString(1, posTil-1);
        quem = sender.ToInt();
        x = param.SubString(posTil+1, (posVirg-1)-posTil);
        y = param.SubString(posVirg+1, param.Length());
        for(int i=0; i<nUsers;i++)
        {
            if(i != quem) // Não preciso enviar para quem me enviou...
                ServerSocket->Socket->Connections[i]->SendText("<#mlig " + sender + "~" + x + "," + y + "#>");
        }
    }
    else if(cmd == "resz")
    {
        if(!started)return;
        AnsiString sender, pin, x, y;
        int quem, posAbre, posFecha, posVirg;
        posAbre = param.Pos("(");
        posFecha = param.Pos(")");
        posVirg = param.Pos(",");
        sender = param.SubString(1, posAbre-1);
        quem = sender.ToInt();
        pin = param.SubString(posAbre+1, (posFecha-1)-posAbre);
        x = param.SubString(posFecha+1, (posVirg-1)-posFecha);
        y = param.SubString(posVirg+1, param.Length()-posVirg);

        for(int i=0; i<nUsers;i++)
        {
            if(i != quem)
                ServerSocket->Socket->Connections[i]->SendText("<#resz " + sender +
                  "(" + pin + ")" + x + "," + y + "#>");
        }
    }                             
    else if (cmd == "join")
    {                        
        if (nUsers == NUsers) // Sessão cheia
        {
            ServerSocket->Socket->Connections[nUsers]->SendText("<#join -1#>");
            nUsers++;
            return;
        }
        else if(ListaUsuarios->Items->IndexOf(param) != -1) // Já existe usuário
        {
            ServerSocket->Socket->Connections[nUsers]->SendText("<#join -2#>");
            nUsers++;
            return;
        }
        else if(started) // Sessão já começou
        {
            ServerSocket->Socket->Connections[nUsers]->SendText("<#join -3#>");
            nUsers++;            
            return;
        }

        ServerSocket->Socket->Connections[nUsers]->SendText("<#join " + AnsiString(nUsers) + "#>");
        ListaUsuarios->Items->Add(param);

        for (int i=0; i<nUsers; i++)
            ServerSocket->Socket->Connections[nUsers]->SendText("<#memb " + ListaUsuarios->Items->Strings[i] + "#>");

        ListaJoins->Add("<#memb " + param + "#>");

        ListaNMensagens->Add("0");
        ListaMovendo->Add("");
        if (nUsers != 0)
            sg_Usuarios->RowCount++;
        sg_Usuarios->Cells[0][sg_Usuarios->RowCount-1] = param;
        sg_Usuarios->Cells[1][sg_Usuarios->RowCount-1] = "0";
        sg_Usuarios->Cells[2][sg_Usuarios->RowCount-1] = "0%";
        nUsers++;

        // Espalho para todos a presença do novo membro
        for (int i=0; i<nUsers; i++)
        {
            if(i != nUsers-1)
                ServerSocket->Socket->Connections[i]->SendText("<#memb " + param + "#>");
        }
    }
    else if (cmd == "chat")
    {
        if(!started)return;
        int posTil, quem;
        AnsiString numero, texto;
        posTil = param.Pos("~");
        numero = param.SubString(1, posTil-1);
        quem = numero.ToInt();
        texto = param.SubString(posTil+1, param.Length()-posTil);
        nMessages++;
        ListaNMensagens->Strings[quem] = AnsiString(ListaNMensagens->Strings[quem].ToInt()+1);
        AtualizaValoresComunicacao();
        for(int i=0; i<nUsers;i++)
        {
            if(i != quem)
                ServerSocket->Socket->Connections[i]->SendText("<#chat <" + ListaUsuarios->Items->Strings[quem] + "> " + texto + "#>");
        }
    }
    else if(cmd == "slct")
    {
        if(!started)return;
        AnsiString nomeObjeto, sender, xoffset, yoffset;
        int quem, posTil, posDol, posVirg;
        posTil = param.Pos("~");
        posDol = param.Pos("$");    
        posVirg = param.Pos(",");
        quem = param.SubString(1, posTil-1).ToInt();
        nomeObjeto = param.SubString(posTil+1, posDol-1-posTil);
        xoffset = param.SubString(posDol+1, posVirg-1-posDol);
        yoffset = param.SubString(posVirg+1, param.Length()-posVirg);
                          
        int indice = ListaMovendo->IndexOf(nomeObjeto);
        if(indice != -1 && indice != quem)
        {
            sg_Usuarios->Cells[1][quem+1] = AnsiString(sg_Usuarios->Cells[1][quem+1].ToInt()+1);
        }
        else
        {
            ListaMovendo->Strings[quem] = nomeObjeto;
        }

        for(int i=0; i<nUsers;i++)
        {
            if(i != quem) // Não preciso enviar para quem me enviou...
                ServerSocket->Socket->Connections[i]->SendText(data);//"<#slct " + nomeObjeto + "$" + xoffset + "," + yoffset + "#>");
        }
    }
    else if(cmd == "rnmo" || cmd == "flga" || cmd == "rnmc" || cmd == "mvin" ||
    cmd == "inst" || cmd == "delo" || cmd == "delc" || cmd == "dlca")
    {
        if(!started)return;
        int quem, posTil;
        posTil = param.Pos("~");
        quem = param.SubString(1, posTil-1).ToInt();
        for(int i=0; i<nUsers;i++)
        {
            if(i != quem) // Não preciso enviar para quem me enviou...
                ServerSocket->Socket->Connections[i]->SendText(data);
        }
    }
    else if(cmd == "flig")
    {
        if(!started)return;
        AnsiString nomeObjeto, sender, type;
        int quem, posTil, posDol;
                                         
        posTil = param.Pos("~");
        posDol = param.Pos("$");
        sender = param.SubString(1, posTil-1);
        quem = sender.ToInt();
        type = param.SubString(posTil+1, posDol-1-posTil);
        nomeObjeto = param.SubString(posDol+1, param.Length() - posDol);

        for(int i=0; i<nUsers;i++)
        {
            if(i != quem) // Não preciso enviar para quem me enviou...
                ServerSocket->Socket->Connections[i]->SendText("<#flig " + sender + "~" + type + "$" + nomeObjeto + "#>");
        }
    }
    else if(cmd == "ilig")
    {
        if(!started)return;
        AnsiString nomeObjeto, sender;
        int quem, posTil;
        posTil = param.Pos("~");
        sender = param.SubString(1, posTil-1);
        quem = sender.ToInt();
        nomeObjeto = param.SubString(posTil+1, param.Length()-posTil);
        for(int i=0; i<nUsers;i++)
        {
            if(i != quem) // Não preciso enviar para quem me enviou...
                ServerSocket->Socket->Connections[i]->SendText("<#ilig " + sender + "~" + nomeObjeto + "#>");
        }
    }
    else if (cmd == "FmDg" || cmd == "prep")
    {
        if(!started)return;
        int quem;
        quem = param.ToInt();

        if (cmd == "FmDg")
        {
            ListaMovendo->Strings[quem] = "";
        }

        for(int i=0; i<nUsers;i++)
        {
            if(i != quem) // Não preciso enviar para quem me enviou...
                ServerSocket->Socket->Connections[i]->SendText(data);
        }
    }
    else if (cmd == "frsz")
    {
        if(!started)return;
        AnsiString sender, pin;
        int quem, posTil;
        posTil = param.Pos("~");
        sender = param.SubString(1, posTil-1);
        quem = sender.ToInt();
        pin = param.SubString(posTil+1, param.Length()-posTil);
        for(int i=0; i<nUsers;i++)
        {
            if(i != quem) // Não preciso enviar para quem me enviou...
                ServerSocket->Socket->Connections[i]->SendText("<#frsz " + sender +
                  "~" + pin + "#>");
        }
    }
    else
        MessageBox(0, cmd.c_str(), "Unknown Command", MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ServerSocketAccept(TObject *Sender,
      TCustomWinSocket *Socket)
{
    StatusBar1->Panels->Items[0]->Text = Socket->RemoteAddress;
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::FormActivate(TObject *Sender)
{
    ServerSocket->Active = true;
    StatusBar1->Panels->Items[0]->Text = "Listening...";
    nUsers = 0;
    OpenDialog->InitialDir = DirInicial->Directory;
    DiagramPath->Caption = "";        
    DiagramName->Caption = "";
}
//---------------------------------------------------------------------------
void TfrmServer::AtualizaValoresComunicacao()
{            
    int i;
    AnsiString valor;   
    for (i=1; i<sg_Usuarios->RowCount; i++)
    {
        valor = (float)(ListaNMensagens->Strings[i-1].ToDouble()/(double)nMessages)*100.0;
        valor = valor.SubString(1, 5);
        sg_Usuarios->Cells[2][i] = valor + "%";
    }
}                                        
//---------------------------------------------------------------------------
void __fastcall TfrmServer::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    ServerSocket->Close();            
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ServerSocketClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    nUsers--;
}
//---------------------------------------------------------------------------
void TfrmServer::PreparaGridUsuarios()
{
    sg_Usuarios->Cells[0][0] = "Users";
    sg_Usuarios->Cells[1][0] = "Conflicts";
    sg_Usuarios->Cells[2][0] = "Communication";
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::btnStartClick(TObject *Sender)
{
    StatusBar1->Panels->Items[0]->Text = "Running...Setting up diagram information.";

    FILE *f;
    f = fopen(DiagramPath->Caption.c_str(), "r");
    if (f == NULL)
    {
        StatusBar1->Panels->Items[0]->Text = "File open error...Check whether this file exists.";
    }

    if (nUsers == 0)
    {
        StatusBar1->Panels->Items[0]->Text = "Error... All users must be connected to start.";
        return;
    }

    char linha[80];
    AnsiString info;
    int i, count = 0;

    mm_Movie->Lines->Clear();
    mm_Movie->Lines->Add("<Numero Linhas>");
    while (!feof(f))
    {
        fgets(linha, 80, f);
        info = AnsiString(linha);
        Trim(info);
        info.SetLength(info.Length()-1);               
        for (i=0; i<nUsers; i++)                  
        {
            ServerSocket->Socket->Connections[i]->SendText("<#line " + info + "#>");
        }
        mm_Movie->Lines->Add(info);
        count++;
    }

    mm_Movie->Lines->Strings[0] = "<" + AnsiString(count) + ">";
    AnsiString chain = "";
    for (i=0; i<ListaUsuarios->Items->Count; i++)
    {
        chain += ListaUsuarios->Items->Strings[i] + "<%>";
    }

    for (i=0; i<nUsers; i++)
    {
        ServerSocket->Socket->Connections[i]->SendText("<#farq " + chain + "#>");
    }

    for (int i=0; i<ListaJoins->Count;i++)
        mm_Movie->Lines->Add(ListaJoins->Strings[i]);

    fclose(f);

    btnStart->Enabled = false;
    btnBrowse->Enabled = false;
    started = 1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::btnBrowseClick(TObject *Sender)
{
    if(!btnStart->Enabled)
    {
        if (OpenDialog->Execute())
        {
            DiagramPath->Caption = OpenDialog->FileName;
            TIniFile* INITIAL;
            INITIAL = new TIniFile(OpenDialog->FileName);
            DiagramName->Caption = INITIAL->ReadString("Features","Nome", "");
            delete INITIAL;

            btnStart->Enabled = true;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::btnShutdownClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::btnDisconnectUsersClick(TObject *Sender)
{
    started = 0;
    ListaJoins->Clear();
    ServerSocket->Active = false;
    ServerSocket->Active = true;
    StatusBar1->Panels->Items[0]->Text = "Listening...";
    if (DiagramPath->Caption.Length() != 0)
        btnStart->Enabled = true;

    nUsers = 0;
    ListaUsuarios->Clear();

    if(opt1->Checked)
    {
        btnBrowse->Enabled = true;
        btnStart->Enabled = true;
        ed_Name->Enabled = false;
        btnStartNew->Enabled = false;
        opt2->Checked = false;
    }
    else if(opt2->Checked)
    {
        btnBrowse->Enabled = false;
        btnStart->Enabled = false;
        ed_Name->Enabled = true;
        btnStartNew->Enabled = true;
        opt1->Checked = false;
    }

    for(int i=1; i<sg_Usuarios->RowCount; i++)
        for(int j=0; j<sg_Usuarios->ColCount; j++)
            sg_Usuarios->Cells[j][i] = "";
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::btnSaveMovieClick(TObject *Sender)
{
    SaveDialog->InitialDir = DirInicial->Directory;
    SaveDialog->FileName= "*.dmf";
    if(SaveDialog->Execute())
    {
        if(SaveDialog->FileName.AnsiPos(".dmf") == 0)
        {
             SaveDialog->FileName += ".dmf";
        }
        else if(SaveDialog->FileName == "*.dmf")
             return;
        mm_Movie->Lines->SaveToFile(SaveDialog->FileName);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::opt1Click(TObject *Sender)
{
    if(opt1->Checked && !started)
    {
        btnBrowse->Enabled = true;
        if(DiagramPath->Caption != "")
            btnStart->Enabled = true;
        else                   
            btnStart->Enabled = false;
        ed_Name->Enabled = false;
        btnStartNew->Enabled = false;
        opt2->Checked = false;
    }
    else
        opt1->Checked = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::opt2Click(TObject *Sender)
{
    if(opt2->Checked && !started)
    {
        btnBrowse->Enabled = false;
        btnStart->Enabled = false;
        ed_Name->Enabled = true;
        btnStartNew->Enabled = true;
        opt1->Checked = false;
    }
    else
        opt2->Checked = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::btnStartNewClick(TObject *Sender)
{
    StatusBar1->Panels->Items[0]->Text = "Running...Setting up diagram information.";
    if (nUsers == 0)
    {
        StatusBar1->Panels->Items[0]->Text = "Error... All users must be connected to start.";
        return;
    }

    if (ed_Name->Text == "")
    {
        StatusBar1->Panels->Items[0]->Text = "Error... You must provide the diagram name.";
        return;
    }

    for (int i=0; i<nUsers; i++)
    {
        ServerSocket->Socket->Connections[i]->SendText("<#newd " + ed_Name->Text + "#>");
    }

    started = 1;
    mm_Movie->Lines->Clear();
    mm_Movie->Lines->Strings[0] = "<new>";
    for (int i=0; i<ListaJoins->Count;i++)
        mm_Movie->Lines->Add(ListaJoins->Strings[i]);
    btnStartNew->Enabled = false;
    ed_Name->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::btnCopyClick(TObject *Sender)
{
    mm_Movie->CopyToClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::FormDestroy(TObject *Sender)
{
    delete ListaNMensagens, ListaMovendo, ListaJoins;
}
//---------------------------------------------------------------------------

void __fastcall TfrmServer::ServerSocketClientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
    ErrorCode = 0;
}
//---------------------------------------------------------------------------

