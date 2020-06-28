#include <vcl\IniFiles.hpp>

#include "Fabrica.h"
#include "ListaEncadeadaObj.h"
#include "ListaEncadeadaConn.h"
#include "FuncoesBasicas.h"

#include "ObjProp.h"
#include "frmConn.h"

#include<dos.h>

#ifndef ModelHandlerH

#define MinHSize 400
#define MinVSize 400

#define NUsers 3

String IniStrToStr(const String Str);
AnsiString StrToIniStr(const AnsiString Str);

typedef void __fastcall (__closure *TNotificaSelecaoObjeto)(int IdObjeto, int xoffset, int yoffset);
typedef void __fastcall (__closure *TNotificaArrasta)(int X, int Y);
typedef void __fastcall (__closure *TNotificaFimArrasta)();
typedef void __fastcall (__closure *TNotificaRedimensiona)(int pin, int X, int Y);
typedef void __fastcall (__closure *TNotificaFimRedimensiona)(int pin);
typedef void __fastcall (__closure *TNotificaMouseMove)(int X, int Y);
typedef void __fastcall (__closure *TNotificaLigacao)(int IdObjeto);
typedef void __fastcall (__closure *TNotificaMoveLigacao)(int X, int Y);
typedef void __fastcall (__closure *TNotificaFimLigacao)(int type, int IdObjeto);
typedef void __fastcall (__closure *TNotificaFimLigacaoAssociativa)(int type, int IdA, int IdB);
typedef void __fastcall (__closure *TNotificaPrepareToInsert)();
typedef void __fastcall (__closure *TNotificaMoveInsercao)(int X, int Y);
typedef void __fastcall (__closure *TNotificaInsercao)(int Type, AnsiString nomeObjeto, double Id, int X, int Y);
typedef void __fastcall (__closure *TNotificaDeleteObjeto)(double Id);
typedef void __fastcall (__closure *TNotificaDeleteConector)(double IdA, double IdB);
typedef void __fastcall (__closure *TNotificaDeleteConectorAssociacao)(double IdA, double IdEndA, double IdEndB);

class ModelHandler
{
private:
    TNotificaSelecaoObjeto notificaSelecaoObjeto;
    TNotificaArrasta notificaArrasta;
    TNotificaFimArrasta notificaFimArrasta;
    TNotificaRedimensiona notificaRedimensiona;
    TNotificaFimRedimensiona notificaFimRedimensiona;
    TNotificaMouseMove notificaMouseMove;
    TNotificaLigacao notificaLigacao;
    TNotificaMoveLigacao notificaMoveLigacao;
    TNotificaFimLigacao notificaFimLigacao;
    TNotificaFimLigacaoAssociativa notificaFimLigacaoAssociativa;
    TNotificaPrepareToInsert notificaPrepareToInsert;
    TNotificaMoveInsercao notificaMoveInsercao;
    TNotificaInsercao notificaInsercao;
    TNotificaDeleteObjeto notificaDeleteObjeto;
    TNotificaDeleteConector notificaDeleteConector;
    TNotificaDeleteConectorAssociacao notificaDeleteConectorAssociacao;

	ListaEncadeadaObj ListaObjetos, GrupoObj;
    ListaEncadeadaConn ListaConectores, GrupoConn;

protected:

    // Variáveis que descrevem o estado do diagrama
    bool *Modified;
    bool *Down;
    bool *DownGroup;
    int *WillConnect;
    int *WillResize;
    int *WillInsert;
    bool *ExisteOrigem;
    TList *Distancias;
    POINT *Base;
    bool *SelectGroup;
    Objeto *Origem, *Redimensionado, *Selecionado;
    Connector *SelecionadoConn;
    int *QtdObjetos;
    int *Xant, *Yant, *XOffset, *YOffset, *XFinal, *YFinal;

    // Para os outros usuários
    Objeto *Selecionado2[NUsers],
        *Origem2[NUsers];

    int *Xant2[NUsers],
        *Yant2[NUsers],
        *XOffset2[NUsers],
        *YOffset2[NUsers],
        *XFinal2[NUsers],
        *YFinal2[NUsers];

    void SetaCursor(TPaintBox *Board, int X, int Y);
    void Redimensiona(TPaintBox *Board, int X, int Y);
    void AcertaNovoTamanho(TPaintBox *Board);
    Connector* BuscaConector(int X, int Y);
    void FinalizaConexao(TPaintBox *Board, int X, int Y);
    void Arrasta(TPaintBox *Board, int X, int Y);
    void ArrastaGrupo(TPaintBox *Board, int X, int Y);
    void setAllVisible(TPaintBox *Board);

    bool PreparaArrastaGrupo(TPaintBox *Board, int X, int Y);
    void NewObject(Objeto *Novo);
    void Desaloco();

    void DeleteObject(Objeto *VaiMorrer, TPaintBox *Board);
    void DeleteSelection(TPaintBox *Board);
    void DeleteConnector(TPaintBox *Board);

    void NewConnector(Connector *Novo);

public:
    AnsiString GetTime();
    AnsiString *Dominio, *LastModified;
    TStringList *LinhasDescricao;

    bool *ScreenLockUpdate;

    AnsiString *ModelFileName;
    AnsiString *ModelName;
    int *HSize, *VSize;

    ModelHandler()
    {
        WillConnect = new int;
        WillResize = new int;
        WillInsert = new int;
        Down = new bool;
        DownGroup = new bool;
        SelectGroup = new bool;
        Origem = new Objeto(-55,-55);
        ExisteOrigem = new bool;
        QtdObjetos = new int;
        Xant = new int;
        Yant = new int;
        Base = new POINT;
        XOffset = new int;
        YOffset = new int;
        XFinal = new int;
        YFinal = new int;
        ModelFileName = new AnsiString;
        Modified = new bool;
        ModelName = new AnsiString;
        ScreenLockUpdate = new bool;
        Dominio = new AnsiString;
        LastModified = new AnsiString;
        LinhasDescricao = new TStringList;
        HSize = new int;
        VSize = new int;
	    Distancias = new TList;

        *ScreenLockUpdate = false;

        *WillConnect = 0;
        *WillResize = 0;
        *WillInsert = 0;
        *Down = false;
        *DownGroup = false;
        *SelectGroup = false;
        *ExisteOrigem = false;
        *QtdObjetos = 0;
        *ModelFileName = "";
        Redimensionado = 0;
        Selecionado = 0;
        SelecionadoConn = 0;

        *HSize = 1000;
        *VSize = 1000;

        // Usuarios
        for (int i=0; i<NUsers;i++)
        {
            Selecionado2[i] = 0;
            Xant2[i] = new int;
            Yant2[i] = new int;
            XOffset2[i] = new int;
            YOffset2[i] = new int;
            XFinal2[i] = new int;
            YFinal2[i] = new int;
        }

        // Esta modificado...
        *Modified = false;
    }
    ~ModelHandler()
    {
        FilaObjetos p, q;
        FilaConectores c, d;
        Desaloco();
        delete WillConnect, QtdObjetos, ExisteOrigem, Origem, Down, Xant, Yant, XFinal, YFinal;
        delete ModelFileName, ModelName, Modified, XOffset, YOffset, Redimensionado;
        delete WillInsert, Dominio, LastModified, LinhasDescricao, HSize, VSize;
        delete SelectGroup, Base, Distancias, DownGroup;

        // Usuarios
        for (int i=0; i<NUsers;i++)
        {
            delete Selecionado2[i],
                Xant2[i],
                Yant2[i],
                XOffset2[i],
                YOffset2[i],
                XFinal2[i],
                YFinal2[i];
        }

    }

    int Modificado();
    void setModified(bool newValue)
    {
    	*Modified = newValue;
    }
    int TemNome();
    void SetBounds(int H, int V, TPaintBox *Board);
    void Delete(TPaintBox *Board);
    void Paint(TCanvas *Board);

    Objeto* getSelectedObject();
    Connector* getSelectedConnector();

    // Eventos básicos
    void PrepareConnection(int ConnId);
    void PrepareToInsert(int ConnId);
    void MouseDown(TPaintBox *Board, int X, int Y);
    void MouseMove(TPaintBox *Board, int X, int Y);
    void MouseUp(TPaintBox *Board, int X, int Y);
	void SelecionaGrupo(TPaintBox *Board, int X, int Y);
    Objeto* CriaObjeto(int Type, int Xpos, int Ypos, AnsiString Label, TPaintBox *Board, int align);
    void NewModel(TPaintBox *Board, AnsiString Nome);

    // Trabalha com Arquivos
	void ExportaModelo(AnsiString PathFile);
    void ImportaModelo(AnsiString PathFile, TPaintBox *Board);

    // Notificações
    void SetNotificacaoSelecaoObjeto(TNotificaSelecaoObjeto procedure);
    void NotificaSelecaoObjeto(int IdObjeto, int xoffset, int yoffset);
    void SetNotificacaoArrasta(TNotificaArrasta procedure);
    void NotificaArrasta(int X, int Y);
    void SetNotificacaoFimArrasta(TNotificaFimArrasta procedure);
    void NotificaFimArrasta();
    void SetNotificacaoRedimensiona(TNotificaRedimensiona procedure);
    void NotificaRedimensiona(int pin, int X, int Y);
    void SetNotificacaoFimRedimensiona(TNotificaFimRedimensiona procedure);
    void NotificaFimRedimensiona(int pin);
    void SetNotificacaoMouseMove(TNotificaMouseMove procedure);
    void NotificaMouseMove(int X, int Y);
    void NotificaLigacao(int IdObjeto);
    void SetNotificacaoLigacao(TNotificaLigacao procedure);
    void SetNotificacaoMoveLigacao(TNotificaMoveLigacao procedure);
    void NotificaMoveLigacao(int X, int Y);
    void SetNotificacaoFimLigacao(TNotificaFimLigacao procedure);
    void NotificaFimLigacao(int type, int IdObjeto);
    void SetNotificacaoFimLigacaoAssociativa(TNotificaFimLigacaoAssociativa procedure);
    void NotificaFimLigacaoAssociativa(int type, int IdA, int IdB);
    void NotificaPrepareToInsert();
    void SetNotificacaoPrepareToInsert(TNotificaPrepareToInsert procedure);
    void NotificaMoveInsercao(int X, int Y);
    void SetNotificacaoMoveInsercao(TNotificaMoveInsercao procedure);
    void NotificaInsercao(int Type, AnsiString nomeObjeto, double Id, int X, int Y);
    void SetNotificacaoInsercao(TNotificaInsercao procedure);
    void NotificaDeleteObjeto(double Id);
    void SetNotificacaoDeleteObjeto(TNotificaDeleteObjeto procedure);
    void NotificaDeleteConector(double IdA, double IdB);
    void SetNotificacaoDeleteConector(TNotificaDeleteConector procedure);
    void NotificaDeleteConectorAssociacao(double IdA, double IdEndA, double IdEndB);
    void SetNotificacaoDeleteConectorAssociacao(TNotificaDeleteConectorAssociacao procedure);

    void SetSelecionado2(int indice, int IdObjeto, int Xoffset, int Yoffset);
    void RenameSelecionado2(int indice, int Id, AnsiString nomeNovo, TPaintBox *Board);
    void RenameSelecionadoConn2(int indice, int IdA, int IdB, AnsiString nomeNovo, TPaintBox *Board);
    void Arrasta2(int indice, TPaintBox *Board, int X, int Y);
    void SetAllVisible2(int indice, TPaintBox *Board);
    void Redimensiona2(int indice, TPaintBox *Board, int pin, int X, int Y);
    void AcertaNovoTamanho2(int indice, TPaintBox *Board, int pin);
    void FinalizaConexao2(int indice, TPaintBox *Board, int X, int Y);
    void SetOrigem2(int indice, int IdObjeto);
    void Conecta2(int indice, TCanvas *Board, int type, int IdObjeto);
    void ConectaAssociativo2(int indice, TCanvas *Board, int type, int IdA, int IdB);
    void PrepareToInsert2(int indice);
    void MoveInsercao2(int indice, TCanvas *Board, int X, int Y);
    void InsereObjeto2(int indice, TPaintBox *Board, int type, AnsiString nomeObjeto, int Id, int X, int Y);
    void DeleteObjeto2(int indice, TPaintBox *Board, double Id);
    void DeleteConector2(int indice, TPaintBox *Board, double IdA, double IdB);
    void DeleteConectorAssociacao2(int indice, TPaintBox *Board, double IdA, double IdEndA, double IdEndB);
};

#include "InterfaceHeader.h"

//-----------------------------Notificações-------------------------------------

void ModelHandler::SetNotificacaoSelecaoObjeto(TNotificaSelecaoObjeto procedure)
{
    notificaSelecaoObjeto = procedure;
}
void ModelHandler::NotificaSelecaoObjeto(int IdObjeto, int xoffset, int yoffset)
{
    if (notificaSelecaoObjeto != NULL)
        (notificaSelecaoObjeto)(IdObjeto, xoffset, yoffset);
}
void ModelHandler::SetNotificacaoArrasta(TNotificaArrasta procedure)
{
    notificaArrasta = procedure;
}
void ModelHandler::NotificaArrasta(int X, int Y)
{
    if (notificaArrasta != NULL)
        (notificaArrasta)(X, Y);
}
void ModelHandler::SetNotificacaoFimArrasta(TNotificaFimArrasta procedure)
{
    notificaFimArrasta = procedure;
}
void ModelHandler::NotificaFimArrasta()
{
    if (notificaFimArrasta != NULL)
        (notificaFimArrasta)();
}
void ModelHandler::SetNotificacaoRedimensiona(TNotificaRedimensiona procedure)
{
    notificaRedimensiona = procedure;
}
void ModelHandler::NotificaRedimensiona(int pin, int X, int Y)
{
    if (notificaRedimensiona != NULL)
        (notificaRedimensiona)(pin, X, Y);
}
void ModelHandler::SetNotificacaoFimRedimensiona(TNotificaFimRedimensiona procedure)
{
    notificaFimRedimensiona = procedure;
}
void ModelHandler::NotificaFimRedimensiona(int pin)
{
    if (notificaFimRedimensiona != NULL)
        (notificaFimRedimensiona)(pin);
}
void ModelHandler::SetNotificacaoMouseMove(TNotificaMouseMove procedure)
{
    notificaMouseMove = procedure;
}
void ModelHandler::NotificaMouseMove(int X, int Y)
{
    if (notificaMouseMove != NULL)
        (notificaMouseMove)(X, Y);
}
void ModelHandler::SetNotificacaoLigacao(TNotificaLigacao procedure)
{
    notificaLigacao = procedure;
}
void ModelHandler::NotificaLigacao(int IdObjeto)
{
    if (notificaLigacao != NULL)
        (notificaLigacao)(IdObjeto);
}
void ModelHandler::SetNotificacaoMoveLigacao(TNotificaMoveLigacao procedure)
{
    notificaMoveLigacao = procedure;
}
void ModelHandler::NotificaMoveLigacao(int X, int Y)
{
    if (notificaMoveLigacao != NULL)
        (notificaMoveLigacao)(X, Y);
}
void ModelHandler::SetNotificacaoFimLigacao(TNotificaFimLigacao procedure)
{
    notificaFimLigacao = procedure;
}
void ModelHandler::NotificaFimLigacao(int type, int IdObjeto)
{
    if (notificaFimLigacao != NULL)
        (notificaFimLigacao)(type, IdObjeto);
}
void ModelHandler::SetNotificacaoFimLigacaoAssociativa(TNotificaFimLigacaoAssociativa procedure)
{
    notificaFimLigacaoAssociativa = procedure;
}
void ModelHandler::NotificaFimLigacaoAssociativa(int type, int IdA, int IdB)
{
    if (notificaFimLigacaoAssociativa != NULL)
        (notificaFimLigacaoAssociativa)(type, IdA, IdB);
}
void ModelHandler::NotificaPrepareToInsert()
{
    if (notificaPrepareToInsert != NULL)
        (notificaPrepareToInsert)();
}
void ModelHandler::SetNotificacaoPrepareToInsert(TNotificaPrepareToInsert procedure)
{
    notificaPrepareToInsert = procedure;
}
void ModelHandler::NotificaMoveInsercao(int X, int Y)
{
    if (notificaMoveInsercao != NULL)
        (notificaMoveInsercao)(X, Y);
}
void ModelHandler::SetNotificacaoMoveInsercao(TNotificaMoveInsercao procedure)
{
    notificaMoveInsercao = procedure;
}
void ModelHandler::NotificaInsercao(int Type, AnsiString nomeObjeto, double Id, int X, int Y)
{
    if (notificaInsercao != NULL)
        (notificaInsercao)(Type, nomeObjeto, Id, X, Y);
}
void ModelHandler::SetNotificacaoInsercao(TNotificaInsercao procedure)
{
    notificaInsercao = procedure;
}
void ModelHandler::NotificaDeleteObjeto(double Id)
{
    if (notificaDeleteObjeto != NULL)
        (notificaDeleteObjeto)(Id);
}
void ModelHandler::SetNotificacaoDeleteObjeto(TNotificaDeleteObjeto procedure)
{
    notificaDeleteObjeto = procedure;
}
void ModelHandler::NotificaDeleteConector(double IdA, double IdB)
{
    if (notificaDeleteConector != NULL)
        (notificaDeleteConector)(IdA, IdB);
}
void ModelHandler::SetNotificacaoDeleteConector(TNotificaDeleteConector procedure)
{
    notificaDeleteConector = procedure;
}
void ModelHandler::NotificaDeleteConectorAssociacao(double IdA, double IdEndA, double IdEndB)
{
    if (notificaDeleteConectorAssociacao != NULL)
        (notificaDeleteConectorAssociacao)(IdA, IdEndA, IdEndB);
}
void ModelHandler::SetNotificacaoDeleteConectorAssociacao(TNotificaDeleteConectorAssociacao procedure)
{
    notificaDeleteConectorAssociacao = procedure;
}
//------------------------------------------------------------------------------
int ModelHandler::TemNome()
{
    return (*ModelFileName != "");
}
int ModelHandler::Modificado()
{
    return (*Modified == true);
}
void ModelHandler::SetBounds(int H, int V, TPaintBox *Board)
{
	// Pega o maior entre os valores...
	H = (H<MinHSize)?MinHSize:H;
    V = (V<MinVSize)?MinVSize:V;

	*HSize = H;
    *VSize = V;
    Board->Height = V;
    Board->Width = H;
}
void ModelHandler::PrepareConnection(int ConnId)
{
    *WillConnect = ConnId;
    if(SelecionadoConn != 0)
	    *SelecionadoConn->isSelected = false;
	SelecionadoConn = 0;
    *WillInsert = 0;
    *Modified = true;
}
void ModelHandler::PrepareToInsert(int ObjId)
{
    NotificaPrepareToInsert();
    *WillInsert = ObjId;
    *WillConnect = 0;
    *Modified = true;
    *Xant = -2000;
    *Yant = -2000;
}
void ModelHandler::PrepareToInsert2(int indice)
{
    *Modified = true;
    *Xant2[indice] = -2000;
    *Yant2[indice] = -2000;
}
void ModelHandler::InsereObjeto2(int indice, TPaintBox *Board, int type, AnsiString nomeObjeto, int Id, int X, int Y)
{
    Board->Canvas->Pen->Mode = pmCopy;
    Board->Canvas->Pen->Mode = pmXor;
    Board->Canvas->Rectangle(X - 15, Y + 15, X + 15, Y - 15);
    Board->Canvas->Pen->Mode = pmCopy;

    Objeto *o = CriaObjeto(type, X - 15, Y - 15, nomeObjeto, Board, 2);
    *o->Id = Id;

    Board->Refresh();
    Paint(Board->Canvas);
}
void ModelHandler::Desaloco()
{
    // Desaloco todo mundo

	ListaObjetos.Clear();
    GrupoObj.Clear();
    ListaConectores.Clear();
    GrupoConn.Clear();
}
void ModelHandler::NewModel(TPaintBox *Board, AnsiString Nome)
{
    Desaloco();

    //Reseto as configurações

    *WillConnect = 0;
    *Down = false;
    *ExisteOrigem = false;
    *QtdObjetos = 0;
    *ModelFileName = "";
    *ModelName = Nome;
    *LastModified = GetTime();
    LinhasDescricao = Break("");

    Board->Refresh();
    *Modified = true;
}
AnsiString ModelHandler::GetTime()
{
    AnsiString Time, Data;
    AnsiString hora, min, seg, dia, mes, ano;
    struct  time t;
    struct date d;
    gettime(&t);
    getdate(&d);

    hora = AnsiString((int)t.ti_hour);
    min = AnsiString((int)t.ti_min);
    seg = AnsiString((int)t.ti_sec);

    dia = AnsiString((int)d.da_day);
    mes = AnsiString((int)d.da_mon);
    ano = AnsiString((int)d.da_year);

    if((int)t.ti_hour < 10) hora = AnsiString("0") + AnsiString((int)t.ti_hour);
    if((int)t.ti_min < 10) min = AnsiString("0") + AnsiString((int)t.ti_min);
    if((int)t.ti_sec < 10) seg = AnsiString("0") + AnsiString((int)t.ti_sec);

    if((int)d.da_day < 10) dia = AnsiString("0") + AnsiString((int)d.da_day);
    if((int)d.da_mon < 10) mes = AnsiString("0") + AnsiString((int)d.da_mon);
    if((int)d.da_year < 10) ano = AnsiString("0") + AnsiString((int)d.da_year);

    Time = hora + AnsiString(":") + min + AnsiString(":") + seg;
    Data = dia + AnsiString("/") + mes + AnsiString("/") + ano;
    return (AnsiString(Time) + AnsiString(" - ") + AnsiString(Data));
}
void ModelHandler::NewObject(Objeto *Novo)
{
    ListaObjetos.InsereLista(Novo);
    *WillConnect = 0;
}
Objeto* ModelHandler::getSelectedObject()
{
	return Selecionado;
}
Connector* ModelHandler::getSelectedConnector()
{
	return SelecionadoConn;
}

Objeto* ModelHandler::CriaObjeto(int Type, int Xpos, int Ypos, AnsiString Label, TPaintBox *Board, int align)
{
    Objeto *Temp;

//    Temp = FabricaObjetos(Type, *QtdObjetos);
    Temp = FabricaObjetos(Type, GetNewID());
    (*QtdObjetos)++;

    Temp->Inicializa(Xpos, Ypos);
    Temp->setText(Label, align);
    Temp->AjustaNome(Board);

    NewObject(Temp);
    *Modified = true;
    return Temp;
}
void ModelHandler::NewConnector(Connector *Novo)
{
    ListaConectores.InsereLista(Novo);

    *ExisteOrigem = false;
    *WillConnect = 0;
    *Modified = true;
}
void ModelHandler::DeleteObject(Objeto *VaiMorrer, TPaintBox *Board)
{
	// Apaga o objeto apontado por VaiMorrer e todos os
	// conectores ligados à ele...

    ListaConectores.RemovePorObjeto(VaiMorrer);
	ListaObjetos.RemoveLista(VaiMorrer);

	*Modified = true;
    VaiMorrer = 0;
}
void ModelHandler::DeleteObjeto2(int indice, TPaintBox *Board, double Id)
{
    FilaObjetos p;
    Objeto *o;

    o = NULL;
	for(p = ListaObjetos.listaPTR; p!=0; p = p->Next)
    {
	    if(*p->Obj->Id == Id)
        {
            o = p->Obj;
            break;
        }
    }

    if (o == NULL) return;

    ListaConectores.RemovePorObjeto(o);
	ListaObjetos.RemoveLista(o);

	*Modified = true;

    Board->Refresh();
    Paint(Board->Canvas);
}
void ModelHandler::DeleteSelection(TPaintBox *Board)
{
	// Apaga todos os objetos selecionados...

    FilaObjetos p;

	for(p = GrupoObj.listaPTR; p!=0; p = p->Next)
    {
	    ListaConectores.RemovePorObjeto(p->Obj);
		ListaObjetos.RemoveLista(p->Obj);
    }

    GrupoObj.Esvazia();

	*Modified = true;
}
void ModelHandler::RenameSelecionado2(int indice, int Id, AnsiString nomeNovo, TPaintBox *Board)
{
    FilaObjetos p;

    Selecionado2[indice] = NULL;
	for(p = ListaObjetos.listaPTR; p!=0; p = p->Next)
    {
	    if(*p->Obj->Id == Id)
        {
            Selecionado2[indice] = p->Obj;
            break;
        }
    }

    if (Selecionado2[indice] == NULL) return;
    *Selecionado2[indice]->Label = nomeNovo;
    Selecionado2[indice]->AjustaNome(Board);
}
void ModelHandler::MoveInsercao2(int indice, TCanvas *Board, int X, int Y)
{
    Board->Pen->Mode = pmXor;
    Board->Pen->Color = clWhite;
    Board->Pen->Style = psDot;
    Board->Brush->Color = clBlack;

    Board->Rectangle(*Xant2[indice], *Yant2[indice], *Xant2[indice] + 30, *Yant2[indice] - 30);
    *Xant2[indice] = X - 15;
    *Yant2[indice] = Y + 15;
    Board->Rectangle(*Xant2[indice], *Yant2[indice], *Xant2[indice] + 30, *Yant2[indice] - 30);
}
void ModelHandler::RenameSelecionadoConn2(int indice, int IdA, int IdB, AnsiString nomeNovo, TPaintBox *Board)
{
    FilaConectores c;

    if(!ListaConectores.ListaVazia())
    {
        for(c = ListaConectores.listaPTR; c!=0; c = c->Next)
        {
            if(*c->Conn->A->Id ==IdA && *c->Conn->B->Id ==IdB)
            {
                *c->Conn->Label = nomeNovo;
                *c->Conn->Position = 3;
                break;
            }
        }
    }
}
void ModelHandler::SetSelecionado2(int indice, int IdObjeto, int Xoffset, int Yoffset)
{
    FilaObjetos p;

	for(p = ListaObjetos.listaPTR; p!=0; p = p->Next)
    {
	    if(*p->Obj->Id == IdObjeto)
        {
            Selecionado2[indice] = p->Obj;
            break;
        }
    }
    *Xant2[indice] = -2000;
    *Yant2[indice] = -2000;
    *XOffset2[indice] = Xoffset;
    *YOffset2[indice] = Yoffset;
}
void ModelHandler::SetOrigem2(int indice, int IdObjeto)
{
    FilaObjetos p;

	for(p = ListaObjetos.listaPTR; p!=0; p = p->Next)
    {
	    if(*p->Obj->Id == IdObjeto)
        {
            Origem2[indice] = p->Obj;
            break;
        }
    }
    *Xant2[indice] = -2000;
    *Yant2[indice] = -2000;
}
void ModelHandler::DeleteConnector(TPaintBox *Board)
{
    if (SelecionadoConn != 0)
    {
        // Apaga o conector selecionado...e suas dependências...
        if (*SelecionadoConn->ID == cReta)
        {
            NotificaDeleteConector(*SelecionadoConn->A->Id, *SelecionadoConn->B->Id);        
            Reta *view;
            view = (Reta*)SelecionadoConn;
            if (view->pointingAtMe != NULL)
            {
                view->pointingAtMe->end = NULL;
                ListaConectores.Apaga(view->pointingAtMe);
                view->pointingAtMe = NULL;
            }
        }
        else
        {
            if (*SelecionadoConn->ID == cAssociacao)
            {
                RetaAssociacao *view;
                view = (RetaAssociacao*)SelecionadoConn;
                NotificaDeleteConectorAssociacao(*SelecionadoConn->A->Id, *view->end->A->Id, *view->end->B->Id);
                if (view->end != NULL)
                {
                    ((Reta*)view->end)->pointingAtMe = NULL;
                }
            }
            else
                NotificaDeleteConector(*SelecionadoConn->A->Id, *SelecionadoConn->B->Id);
        }
        ListaConectores.Apaga(SelecionadoConn);
        SelecionadoConn = NULL;
        *Modified = true;
    }
}
void ModelHandler::DeleteConector2(int indice, TPaintBox *Board, double IdA, double IdB)
{
    Connector *con = NULL;

    FilaConectores c;
    FilaObjetos p;

    if(!ListaConectores.ListaVazia())
    {
        for(c = ListaConectores.listaPTR; c!=0; c = c->Next)
        {
            if(*c->Conn->A->Id == IdA && *c->Conn->B->Id == IdB)
            {
                con = c->Conn;
                break;
            }
        }
    }

    // Apaga o conector selecionado...e suas dependências...
    if (*con->ID == cReta)
    {
        Reta *view;
        view = (Reta*)con;
        if (view->pointingAtMe != NULL)
        {
            view->pointingAtMe->end = NULL;
            ListaConectores.Apaga(view->pointingAtMe);
            view->pointingAtMe = NULL;
        }
    }
    else if (*con->ID == cAssociacao)
    {
        RetaAssociacao *view;
        view = (RetaAssociacao*)con;
        if (view->end != NULL)
        {
            ((Reta*)view->end)->pointingAtMe = NULL;
        }
    }
    ListaConectores.Apaga(con);
    con = NULL;
    *Modified = true;
    Board->Refresh();
    Paint(Board->Canvas);
}
void ModelHandler::DeleteConectorAssociacao2(int indice, TPaintBox *Board, double IdA, double IdEndA, double IdEndB)
{
    FilaConectores c;
    FilaObjetos p;
    RetaAssociacao *view = NULL;

    if(!ListaConectores.ListaVazia())
    {
        for(c = ListaConectores.listaPTR; c!=0; c = c->Next)
        {
            if(*c->Conn->ID == cAssociacao)
            {
                view = (RetaAssociacao*)c->Conn;
                if(*c->Conn->A->Id == IdA && *view->end->A->Id == IdEndA && *view->end->B->Id == IdEndB)
                {
                    break;
                }
                view = NULL;
            }
        }
    }
    if (view->end != NULL)
    {
        ((Reta*)view->end)->pointingAtMe = NULL;
    }

    ListaConectores.Apaga(view);
    view = NULL;
    *Modified = true;
    Board->Refresh();
    Paint(Board->Canvas);
}
void ModelHandler::Delete(TPaintBox *Board)
{
    if(*WillConnect != 0)
    {
        *WillConnect = 0;
        Board->Refresh();
        Paint(Board->Canvas);
        return;
    }

    int Resp;

    Resp = MessageBox(0, "Are you sure you want to delete your selection?", "Attention", MB_YESNO | MB_ICONQUESTION);
    if(Resp == 7)
    {
        return;
    }

    *Modified = true;

    if(Selecionado != 0)
    {
        NotificaDeleteObjeto(*Selecionado->Id);
	    DeleteObject(Selecionado, Board);
    }
    else if(!GrupoObj.ListaVazia())
	    DeleteSelection(Board);

    DeleteConnector(Board);

    Board->Refresh();
    Paint(Board->Canvas);
}

void ModelHandler::Paint(TCanvas *Board)
{
    FilaConectores c;
    FilaObjetos p;

    Board->Pen->Mode = pmCopy;
    Board->Pen->Color = clWhite;
    Board->Pen->Style = psSolid;
    Board->Brush->Color = clWhite;

    if(!ListaConectores.ListaVazia())
    {
        for(c = ListaConectores.listaPTR; c!=0; c = c->Next)
        {
            (c->Conn)->Paint(Board, clBlack);
        }
    }

    if(!ListaObjetos.ListaVazia())
    {
        for(p = ListaObjetos.FinalListaPTR; p!=0; p = p->Prior)
        {
            (p->Obj)->Paint(Board);
        }
    }
}
void ModelHandler::MouseDown(TPaintBox *Board, int X, int Y)
{
    FilaObjetos p;
    bool acheiObjeto = false;

    Selecionado = 0;
    SelecionadoConn = 0;

    if(!GrupoObj.ListaVazia() && !(*WillConnect) && !(*WillInsert))
    {
    	if(PreparaArrastaGrupo(Board, X, Y))
        {
        	*Down = false;
            *DownGroup = true;
            ArrastaGrupo(Board, X, Y);
	        return;
        }
        else
        {
			GrupoObj.Esvazia();
            GrupoConn.Esvazia();
        }
    }
    else
    {
    	GrupoObj.Esvazia();
        GrupoConn.Esvazia();
    }

    if(*WillConnect == 0 && !(*WillInsert))
    {
        *ScreenLockUpdate = true;

        if(!ListaObjetos.ListaVazia())
        {
            for(p = ListaObjetos.listaPTR; p!=0; p = p->Next)
            {
                // Busca o Objeto na Posição (X,Y)

                if(p->Obj->isHere(X,Y) == true && !acheiObjeto)
                {
                    Selecionado = p->Obj;

                    acheiObjeto = true;
                    *Down = true;
                    *DownGroup = false;

                    *Xant = -2000;
                    *Yant = -2000;

                    *WillResize = p->Obj->isResize(X,Y);
                    if(*WillResize != 0 && *p->Obj->isSelected)
                    {
                         Redimensionado = p->Obj;
                         *ScreenLockUpdate = false;
                         NotificaRedimensiona(*WillResize, X, Y);
                         Redimensiona(Board, X, Y);
                         return;
                    }

                    Board->Refresh();

                    ListaConectores.UnSelectAllConnectors();

                    *WillResize = 0;
                    p->Obj->Selected();
                    *p->Obj->Visible = false;
                    p->Obj->Drag(Board, *p->Obj->Xpos + *p->Obj->Width/2, *p->Obj->Ypos - *p->Obj->Height/2);

                    Board->Canvas->Font->Color = clWhite;
                    p->Obj->PaintText(Board->Canvas);
                    
                    // Deslocamento em relação ao centro do Objeto arrastado:
                    *XOffset = X - (*p->Obj->Xpos + *p->Obj->Width/2);
                    *YOffset = Y - (*p->Obj->Ypos - *p->Obj->Height/2);

                    *Modified = true;
                }
                else
                {
                    *(p->Obj->isSelected) = false;
                    *(p->Obj->Visible) = true;
                }
            }
            if(!acheiObjeto)
            {
                ListaConectores.UnSelectAllConnectors();
                SelecionadoConn = BuscaConector(X,Y);
                if(SelecionadoConn == 0)
                {
                   	//*SelectGroup = true;
                   	*SelectGroup = false;                    
                    // Esvazia e tiro a seleção de todos os
				    // objetos da lista GrupoObj
					GrupoObj.Esvazia();
                    GrupoConn.Esvazia();

					Base->x = X;
                    Base->y = Y;
                    *Xant = -2000;
                    *Yant = -2000;

                    *Down = false;
                }
                else
                {
                     SelecionadoConn->Selected();
                }
                Board->Refresh();
            }
            else
            {
                NotificaSelecaoObjeto(*Selecionado->Id, *XOffset, *YOffset);
            }

            Paint(Board->Canvas);
            *ScreenLockUpdate = false;
        }
    }
    else if (*WillConnect != 0 && !*ExisteOrigem)
    {
        bool Taqui, achei = false;
        // Haverá uma conexão
        for(p = ListaObjetos.listaPTR; p!=0; p = p->Next)
        {
            // Busca o Objeto na Posição (X,Y)
            Taqui = p->Obj->isHere(X,Y);
            if(Taqui && *p->Obj->Type != oComentario)
            {
                Origem = p->Obj;            
                NotificaLigacao(*Origem->Id);
                p->Obj->Selected();
                *ExisteOrigem = true;
                *Xant = *p->Obj->Xpos + *p->Obj->Width/2;
                *Yant = *p->Obj->Ypos - *p->Obj->Height/2;
                achei = true;
                break;
            }
            else if(*p->Obj->Type == oComentario && Taqui)
            {
                *WillConnect = 0;
                *ExisteOrigem = false;
                p->Obj->Selected();
            }
            else
                *p->Obj->isSelected = false;
        }
        if(!achei)
        {
        	*WillConnect = 0;
        	*ExisteOrigem = false;
        }
        *Modified = true;
    }
    else if(*WillConnect != 0 && *ExisteOrigem == true)
    {
        bool Achei = false;

        *ScreenLockUpdate = true;
        // Fechando a conexão
        if(*WillConnect != cAssociacao)
        {
	        for(p = ListaObjetos.listaPTR; p!=0; p = p->Next)
	        {
	            // Busca o Objeto na Posição (X,Y)
	            if(p->Obj->isHere(X,Y)==true && p->Obj != Origem)
	            {
	                if(ListaConectores.ExisteConexao(Origem, p->Obj))
	                {
	                     *WillConnect = 0;
	                     *ExisteOrigem = false;
	                     MessageBox(0, "Only one conection can exist between two objects at the same time.", "Attention", MB_OK | MB_ICONEXCLAMATION);
	                     Achei = true;
	                     break;
	                }
	                else if(*p->Obj->Type == oComentario)
	                {
	                     *WillConnect = 0;
	                     *ExisteOrigem = false;
	                     Achei = true;
	                     break;
	                }
	                Connector *Temp;
	                Temp = FabricaConectores(*WillConnect);

                    NotificaFimLigacao(*WillConnect, *p->Obj->Id);
	                Temp->Connect(Origem,p->Obj);

	                NewConnector(Temp);
	                Achei = true;
	                *Origem->isSelected = false;
	                p->Obj->Selected();
	                Selecionado = p->Obj;
	                break;
	            }
	        }
        }
        else   // *WillConnect = cAssociacao
        {
			Connector *Fim;
            Fim = BuscaConector(X, Y);
            if(Fim == 0)
            {
            	Achei = false;
            }
           	else if(*Fim->ID == cReta) // Conecta a uma reta
            {
                RetaAssociacao *MinhaReta;
                Reta *Destino;
                Destino = (Reta*)Fim;

                if(Destino->pointingAtMe != 0)
                {
                	AnsiString Msg;
                    Msg = "The association between ";
                    Msg += *Destino->A->Label;
                    Msg += " and ";
                    Msg += *Destino->B->Label;
                    Msg += " already has an association class: ";
                    Msg += *Destino->pointingAtMe->A->Label;
                    MessageBox(0, Msg.c_str(), "Error", MB_OK);
                }
                else
                {
	                Connector *Temp;
	                Temp = FabricaConectores(*WillConnect);

                    NotificaFimLigacaoAssociativa(*WillConnect, *Fim->A->Id, *Fim->B->Id);
	                MinhaReta = (RetaAssociacao*)Temp;

	                MinhaReta->A = Origem;
	                MinhaReta->B = 0;
	                MinhaReta->end = Fim;
	                Destino->pointingAtMe = MinhaReta;

	                NewConnector(MinhaReta);
    	            Achei = true;
	                *Origem->isSelected = false;
                }
            }
        }
        // Verifica se clicou no background
        if(Achei == false)
        {
            *WillConnect = 0;
            *ExisteOrigem = false;
        }
        *Modified = true;

        Board->Canvas->Pen->Mode = pmCopy;
        Board->Canvas->Pen->Color = clWhite;
        Board->Canvas->Brush->Color = clWhite;
        Board->Refresh();
        Paint(Board->Canvas);
        *ScreenLockUpdate = false;
    }
    else if(*WillInsert)
    {
         AnsiString Name = "";
         int Xa, Ya;
         OProp->Name->Text = "";
         Xa = X;
         Ya = Y;
         Board->Canvas->Pen->Mode = pmCopy;
         Board->Canvas->Pen->Mode = pmXor;
         Board->Canvas->Rectangle(Xa - 15, Ya + 15, Xa + 15, Ya - 15);
         Board->Canvas->Pen->Mode = pmCopy;

         Objeto *o = EditaNovoObjeto(*WillInsert, X, Y, Board, this);
         if (o != NULL)
             NotificaInsercao(*o->Type, *o->Label, *o->Id, X, Y);

         *WillInsert = 0;

         Board->Cursor = crArrow;
    }
}
void ModelHandler::MouseMove(TPaintBox *Board, int X, int Y)
{
    SetaCursor(Board, X, Y);

    // Busco a ação do usuário:

    if(*Down)  // Estou arrastando um objeto
    {
        if(*WillResize != 0)
        {
            NotificaRedimensiona(*WillResize, X, Y);
            Redimensiona(Board, X, Y);
        }
        else
        {
            NotificaArrasta(X, Y);
            Arrasta(Board, X, Y);
        }
    }
    else if(*DownGroup)
    {
        ArrastaGrupo(Board, X, Y);
    }
    else if(*SelectGroup)
    {
        SelecionaGrupo(Board, X, Y);
    }
    else if(*WillConnect != 0 && *ExisteOrigem == true)
    {
        NotificaMoveLigacao(X, Y);
        FinalizaConexao(Board, X, Y);
    }
    else if(*WillInsert)
    {
        NotificaMoveInsercao(X, Y);
        Board->Canvas->Pen->Mode = pmXor;
        Board->Canvas->Pen->Color = clWhite;
        Board->Canvas->Pen->Style = psDot;
        Board->Canvas->Brush->Color = clBlack;

        Board->Canvas->Rectangle(*Xant, *Yant, *Xant + 30, *Yant - 30);
        *Xant = X - 15;
        *Yant = Y + 15;
        Board->Canvas->Rectangle(*Xant, *Yant, *Xant + 30, *Yant - 30);
    }                 
    else
    {
        NotificaMouseMove(X, Y);          
    }
}
void ModelHandler::MouseUp(TPaintBox *Board, int X, int Y)
{
    if(*Down)
    {
        if(*WillResize != 0)
        {
            NotificaFimRedimensiona(*WillResize);
            AcertaNovoTamanho(Board);
        }
        if(*Xant == -2000)
        {
		    Board->Canvas->Pen->Mode = pmCopy;
            *Selecionado->Visible = true;
			Selecionado->Paint(Board->Canvas);
            *Down = false;
        }
        else
        {
            NotificaFimArrasta();
        	setAllVisible(Board);
        }
    }
    else if(*SelectGroup)
    {
		bool Pinta = true;

		Selecionado = 0;
        SelecionadoConn = 0;

        // Apaga o último retângulo desenhado
        if(*Xant != -2000)
	    	Board->Canvas->Rectangle(Base->x, Base->y, *Xant, *Yant);
        else
            Pinta = false;

        Board->Canvas->Pen->Mode = pmCopy;

        if(!Pinta)
        {
        	*SelectGroup = false;
        	return;
        }

        // Os pontos do retângulo são:
        // Base.x e Base.y
        // *Xant e *Yant
        FilaObjetos p, r;
        FilaConectores c;

        // A, B, C e D são os pontos das quinas
        // do Objeto
        //    B-----C
        //    |     |
        //    A-----D
        POINT A, B, C, D;

        Pinta = false;
        for(p = ListaObjetos.listaPTR; p != 0; p = p->Next)
        {
        	A.x = *p->Obj->Xpos;
            A.y = *p->Obj->Ypos;
           	B.x = *p->Obj->Xpos;
            B.y = *p->Obj->Ypos - *p->Obj->Height;
        	C.x = *p->Obj->Xpos + *p->Obj->Width;
            C.y = *p->Obj->Ypos - *p->Obj->Height;
        	D.x = *p->Obj->Xpos + *p->Obj->Width;
            D.y = *p->Obj->Ypos;

            // Os quatro pontos do Objeto devem estar dentro o
            // retângulo que o usuário traçou...
        	if(InsideRect(A.x, A.y, Base->x, Base->y, *Xant, *Yant, 1.0) &&
            InsideRect(B.x, B.y, Base->x, Base->y, *Xant, *Yant, 1.0) &&
            InsideRect(C.x, C.y, Base->x, Base->y, *Xant, *Yant, 1.0) &&
            InsideRect(D.x, D.y, Base->x, Base->y, *Xant, *Yant, 1.0))
            {
                GrupoObj.InsereLista(p->Obj);
                p->Obj->Agrupa();
                Pinta = true;
            }
            *p->Obj->isSelected = false;
        }

        // Buscar conectores e colocá-los na
        // lista GrupoConn
        if(Pinta)
        {
	        for(c = ListaConectores.listaPTR; c != 0; c = c->Next)
	        {
    	    	p = GrupoObj.listaPTR;
	            r = GrupoObj.FinalListaPTR;
	            // Busca bidirecional:
		        for(; p != r && p!=r->Next; p = p->Next, r = r->Prior)
		        {
	    			if(c->Conn->A == p->Obj || c->Conn->B == p->Obj || c->Conn->A == r->Obj || c->Conn->B == r->Obj)
		            {
		            	GrupoConn.InsereLista(c->Conn);
	                    break;
		            }
	            }
	            if(p == r) // Só há um elemento em GrupoObj...
	            {
	    			if(c->Conn->A == p->Obj || c->Conn->B == p->Obj || c->Conn->A == r->Obj || c->Conn->B == r->Obj)
		            {
		            	GrupoConn.InsereLista(c->Conn);
    	                continue;
	    	        }
            	}

			}

	        Board->Refresh();
	        Paint(Board->Canvas);
        }
	   	*SelectGroup = false;
    }
    else if(*DownGroup)
    {
    	FilaConectores c;

		*DownGroup = false;

	    if(!GrupoConn.ListaVazia())
    	{
        	for(c = GrupoConn.listaPTR; c!=0; c = c->Next)
          	{
                *c->Conn->isDragging = false;
	        }
    	}

	    Board->Canvas->Pen->Mode = pmCopy;
        Board->Refresh();
        Paint(Board->Canvas);
    }
}
void ModelHandler::FinalizaConexao(TPaintBox *Board, int X, int Y)
{
        // Linha entre o Objeto Origem e o Mouse

        Board->Canvas->Pen->Mode = pmXor;
        Board->Canvas->Pen->Color = clWhite;
        Board->Canvas->Pen->Style = psDot;
        Board->Canvas->Brush->Color = clBlack;

        Board->Canvas->MoveTo(*Origem->Xpos + *Origem->Width/2,*Origem->Ypos - *Origem->Height/2);
        Board->Canvas->LineTo(*Xant,*Yant);

        // Transfiro o ponto antigo para o novo
        *Xant = X;
        *Yant = Y;

        Board->Canvas->MoveTo(*Origem->Xpos + *Origem->Width/2,*Origem->Ypos - *Origem->Height/2);
        Board->Canvas->LineTo(X,Y);
}
void ModelHandler::FinalizaConexao2(int indice, TPaintBox *Board, int X, int Y)
{
    // Linha entre o Objeto Origem e o Mouse
    if(*Xant2[indice] != -2000)
    {
        Board->Canvas->Pen->Mode = pmXor;
        Board->Canvas->Pen->Color = clWhite;
        Board->Canvas->Pen->Style = psDot;
        Board->Canvas->Brush->Color = clBlack;

        Board->Canvas->MoveTo(*Origem2[indice]->Xpos + *Origem2[indice]->Width/2,*Origem2[indice]->Ypos - *Origem2[indice]->Height/2);
        Board->Canvas->LineTo(*Xant2[indice],*Yant2[indice]);
    }
    // Transfiro o ponto antigo para o novo
    *Xant2[indice] = X;
    *Yant2[indice] = Y;

    Board->Canvas->MoveTo(*Origem2[indice]->Xpos + *Origem2[indice]->Width/2,*Origem2[indice]->Ypos - *Origem2[indice]->Height/2);
    Board->Canvas->LineTo(X,Y);
}
void ModelHandler::Conecta2(int indice, TCanvas *Board, int type, int IdObjeto)
{
    Connector *Temp;
    Objeto *obj;
    FilaObjetos p;

    Board->Pen->Mode = pmXor;
    Board->Pen->Color = clWhite;
    Board->Pen->Style = psDot;
    Board->Brush->Color = clBlack;

    Board->MoveTo(*Origem2[indice]->Xpos + *Origem2[indice]->Width/2,*Origem2[indice]->Ypos - *Origem2[indice]->Height/2);
    Board->LineTo(*Xant2[indice],*Yant2[indice]);

    for(p = ListaObjetos.listaPTR; p!=0; p = p->Next)
    {
        // Busca o Objeto na Posição (X,Y)
        if(*p->Obj->Id == IdObjeto)
        {
            obj = p->Obj;
            break;
        }
    }

    Temp = FabricaConectores(type);
    Temp->Connect(Origem2[indice], obj);

    NewConnector(Temp);

    Board->Pen->Mode = pmCopy;
    Board->Pen->Color = clWhite;
    Board->Brush->Color = clWhite;
    Temp->Paint(Board, clBlack);

    *Origem2[indice]->isSelected = false;
    Selecionado2[indice] = obj;
}
void ModelHandler::ConectaAssociativo2(int indice, TCanvas *Board, int type, int IdA, int IdB)
{
    Connector *Temp;   
    Objeto *obj;

    Board->Pen->Mode = pmXor;
    Board->Pen->Color = clWhite;
    Board->Pen->Style = psDot;
    Board->Brush->Color = clBlack;

    Board->MoveTo(*Origem2[indice]->Xpos + *Origem2[indice]->Width/2,*Origem2[indice]->Ypos - *Origem2[indice]->Height/2);
    Board->LineTo(*Xant2[indice],*Yant2[indice]);

    FilaConectores c;
    Connector *Fim;

    Fim = NULL;
	if(!ListaConectores.ListaVazia())
	{
        for(c = ListaConectores.listaPTR; c!=0; c = c->Next)
        {
            if(*c->Conn->A->Id == IdA && *c->Conn->B->Id == IdB)
            {
                Fim = c->Conn;
                break;
            }
    	}
    }

    Temp = FabricaConectores(type);
    RetaAssociacao *MinhaReta;
    Reta *Destino;

    MinhaReta = (RetaAssociacao*)Temp;

    MinhaReta->A = Origem2[indice];
    MinhaReta->B = NULL;
    MinhaReta->end = Fim;

    Destino = (Reta*)Fim;
    Destino->pointingAtMe = MinhaReta;

    NewConnector(MinhaReta);

    Board->Pen->Mode = pmCopy;
    Board->Pen->Color = clWhite;
    Board->Brush->Color = clWhite;
    Temp->Paint(Board, clBlack);

    *Origem2[indice]->isSelected = false;
    Selecionado2[indice] = obj;
}
Connector* ModelHandler::BuscaConector(int X, int Y)
{
     FilaConectores c;
     if(!ListaConectores.ListaVazia())
     {
          float X1, Y1, X2, Y2, diff;
          for(c = ListaConectores.listaPTR; c!=0; c = c->Next)
          {
               X1 = *c->Conn->A->Xpos + *c->Conn->A->Width/2;
               Y1 = *c->Conn->A->Ypos - *c->Conn->A->Height/2;

               if(*c->Conn->ID != cAssociacao)
               {
	               X2 = *c->Conn->B->Xpos + *c->Conn->B->Width/2;;
	               Y2 = *c->Conn->B->Ypos - *c->Conn->B->Height/2;
	               diff = c->Conn->DistanciaAoPonto(X, Y);
               }
               else
               {
					Ponto PontoBaseA1, PontoBaseA2;
                    RetaAssociacao *Reta;
                    Reta = (RetaAssociacao*)c->Conn;
				    PontoBaseA1 = Reta->Fronteira(*Reta->end->A->Xpos, *Reta->end->A->Ypos, *Reta->end->A->Height, *Reta->end->A->Width, *Reta->end->B->Xpos, *Reta->end->B->Ypos, *Reta->end->B->Height, *Reta->end->B->Width);
				    PontoBaseA2 = Reta->Fronteira(*Reta->end->B->Xpos, *Reta->end->B->Ypos, *Reta->end->B->Height, *Reta->end->B->Width, *Reta->end->A->Xpos, *Reta->end->A->Ypos, *Reta->end->A->Height, *Reta->end->A->Width);
				    X2 = Menor(PontoBaseA1.X, PontoBaseA2.X) + Modulo(PontoBaseA1.X - PontoBaseA2.X)/2;
				    Y2 = Menor(PontoBaseA1.Y, PontoBaseA2.Y) + Modulo(PontoBaseA1.Y - PontoBaseA2.Y)/2;
	                diff = Reta->DistanciaAoPonto(X, Y);
               }

               if(diff <= 4.0 && InsideRect(X,Y,X1,Y1,X2,Y2,4.0))
               {
                    return c->Conn;
               }
          }
     }
     return 0;
}
void ModelHandler::Arrasta(TPaintBox *Board, int X, int Y)
{
    FilaConectores c;

    *Selecionado->Visible = true;
    Board->Canvas->Pen->Mode = pmXor;
    Board->Canvas->Pen->Color = clWhite;
    Board->Canvas->Pen->Style = psSolid;
    Board->Canvas->Brush->Color = clBlack;

    // Pinto os Conectores ligados a ele
    if(*Xant == -2000) // Apaga o primeiro arraste
    {
           Board->Canvas->Pen->Mode = pmWhite;
	}

    if(!ListaConectores.ListaVazia())
    {
          for(c = ListaConectores.listaPTR; c!=0; c = c->Next)
          {
                *c->Conn->Visible = true;
                if(c->Conn->A == Selecionado || c->Conn->B == Selecionado)
                {
                      c->Conn->Paint(Board->Canvas, clWhite);
                      if(*c->Conn->ID == cReta)
                      {
                      		Reta *Dest = (Reta*)c->Conn;
                            if(Dest->pointingAtMe != 0)
	                      		Dest->pointingAtMe->Paint(Board->Canvas, clWhite);
                      }
                }
          }
    }

    if(*Xant != -2000) // Não mostra o primeiro arraste
    {
           // Apago com o XOR
    	   Board->Canvas->Pen->Style = psDot;
           Board->Canvas->Brush->Style = bsClear;

           Selecionado->Drag(Board, *Xant, *Yant);
    }
    else
    {
		   Board->Canvas->Pen->Style = psSolid;
           Selecionado->Drag(Board, *Selecionado->Xpos + *Selecionado->Width/2, *Selecionado->Ypos - *Selecionado->Height/2);
           Board->Canvas->Pen->Mode = pmWhite;
           if(!ListaConectores.ListaVazia())
           {
                for(c = ListaConectores.listaPTR; c!=0; c = c->Next)
                {
                      if(c->Conn->A == Selecionado || c->Conn->B == Selecionado)
                      {
                           *(c->Conn->isDragging) = true;
                           c->Conn->Paint(Board->Canvas, clWhite);
		                   if(*c->Conn->ID == cReta)
		                   {
    	      	          		Reta *Dest = (Reta*)c->Conn;
            	                if(Dest->pointingAtMe != 0)
                                {
                                	*Dest->pointingAtMe->isDragging = true;
	    	       	     	 		Dest->pointingAtMe->Paint(Board->Canvas, clWhite);
                                }
		                   }

                      }
                }
           }
    	   Board->Canvas->Pen->Style = psDot;
           Board->Canvas->Brush->Style = bsClear;

           Board->Canvas->Pen->Mode = pmXor;
    }

    // Transfiro o ponto antigo para o novo
    *Xant = X - *XOffset;
    *Yant = Y - *YOffset;

    // Mantém o Objeto visível dentro da tela
    if(*Xant < 0) *Xant = 0;
    if(*Yant < 0) *Yant = 0;
    if(*Xant > Board->Width) *Xant = Board->Width;
    if(*Yant > Board->Height) *Yant = Board->Height;

    // Pinto o Objeto Fantasma
    Selecionado->Drag(Board, *Xant, *Yant);

    // Repinto os conectores
    if(!ListaConectores.ListaVazia())
    {
         for(c = ListaConectores.listaPTR; c!=0; c = c->Next)
         {
               if(c->Conn->A == Selecionado || c->Conn->B == Selecionado)
               {
                    c->Conn->Paint(Board->Canvas, clWhite);
                    if(*c->Conn->ID == cReta)
                    {
                   		Reta *Dest = (Reta*)c->Conn;
                        if(Dest->pointingAtMe != 0)
                   			Dest->pointingAtMe->Paint(Board->Canvas, clWhite);
                    }
               }
         }
    }
}

void ModelHandler::Arrasta2(int indice, TPaintBox *Board, int X, int Y)
{
    FilaConectores c;

    *Selecionado2[indice]->Visible = false;
    Board->Canvas->Pen->Mode = pmXor;
    Board->Canvas->Pen->Color = clWhite;
    Board->Canvas->Pen->Style = psSolid;
    Board->Canvas->Brush->Color = clBlack;

    // Pinto os Conectores ligados a ele
    if(*Xant2[indice] == -2000) // Apaga o primeiro arraste
    {
        Board->Canvas->Pen->Mode = pmWhite;
        Board->Canvas->Brush->Style = bsClear;
        Board->Canvas->Font->Color = clWhite;

        Board->Canvas->Pen->Style = psSolid;
        Board->Canvas->Pen->Width = 3;
        Selecionado2[indice]->Drag(Board, *Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width/2, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height/2);
        Board->Canvas->Pen->Width = 1;
        Selecionado2[indice]->PaintText(Board->Canvas);

        if (Selecionado == Selecionado2[indice])
        {
            Board->Canvas->Brush->Color = clWhite;
            Board->Canvas->Pen->Style = psSolid;
            Board->Canvas->Brush->Style = bsSolid;

            Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos - 2, *Selecionado2[indice]->Ypos - 2 , *Selecionado2[indice]->Xpos + 3, *Selecionado2[indice]->Ypos + 3);
            Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width/2 - 2, *Selecionado2[indice]->Ypos - 2 , *Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width/2 + 3, *Selecionado2[indice]->Ypos + 3);
            Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - 2, *Selecionado2[indice]->Ypos - 2 , *Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width + 3, *Selecionado2[indice]->Ypos + 3);

            Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - 2, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height/2 - 2 , *Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width + 3, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height/2 + 3);

            Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos - 2, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height - 2 , *Selecionado2[indice]->Xpos + 3, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height + 3);
            Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width/2 - 2, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height - 2 , *Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width/2 + 3, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height + 3);
            Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - 2, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height - 2 , *Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width + 3, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height + 3);

            Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos - 2, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height/2 - 2 , *Selecionado2[indice]->Xpos + 3, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height/2 + 3);
        }

        Board->Canvas->Pen->Mode = pmWhite;
        Board->Canvas->Brush->Color = clBlack;
	}

    if(!ListaConectores.ListaVazia())
    {
          for(c = ListaConectores.listaPTR; c!=0; c = c->Next)
          {
                *c->Conn->Visible = true;
                if(c->Conn->A == Selecionado2[indice] || c->Conn->B == Selecionado2[indice])
                {
                      c->Conn->Paint(Board->Canvas, clWhite);
                      if(*c->Conn->ID == cReta)
                      {
                      		Reta *Dest = (Reta*)c->Conn;
                            if(Dest->pointingAtMe != 0)
	                      		Dest->pointingAtMe->Paint(Board->Canvas, clWhite);
                      }
                }
          }
    }

    if(*Xant2[indice] != -2000) // Não mostra o primeiro arraste
    {
           // Apago com o XOR
    	   Board->Canvas->Pen->Style = psDot;
           Board->Canvas->Brush->Style = bsClear;
           Selecionado2[indice]->Drag(Board, *Xant2[indice], *Yant2[indice]);
    }
    else
    {
           Board->Canvas->Pen->Mode = pmWhite;
           if(!ListaConectores.ListaVazia())
           {
                for(c = ListaConectores.listaPTR; c!=0; c = c->Next)
                {
                      if(c->Conn->A == Selecionado2[indice] || c->Conn->B == Selecionado2[indice])
                      {
                           *(c->Conn->isDragging) = true;
                           c->Conn->Paint(Board->Canvas, clWhite);
		                   if(*c->Conn->ID == cReta)
		                   {
    	      	          		Reta *Dest = (Reta*)c->Conn;
            	                if(Dest->pointingAtMe != 0)
                                {
                                	*Dest->pointingAtMe->isDragging = true;
	    	       	     	 		Dest->pointingAtMe->Paint(Board->Canvas, clWhite);
                                }
		                   }
                      }
                }
           }
    	   Board->Canvas->Pen->Style = psDot;
           Board->Canvas->Brush->Style = bsClear;

           Board->Canvas->Pen->Mode = pmXor;
    }

    // Transfiro o ponto antigo para o novo
    *Xant2[indice] = X - *XOffset2[indice];
    *Yant2[indice] = Y - *YOffset2[indice];

    // Mantém o Objeto visível dentro da tela
    if(*Xant2[indice] < 0) *Xant2[indice] = 0;
    if(*Yant2[indice] < 0) *Yant2[indice] = 0;
    if(*Xant2[indice] > Board->Width) *Xant2[indice] = Board->Width;
    if(*Yant2[indice] > Board->Height) *Yant2[indice] = Board->Height;

    // Pinto o Objeto Fantasma
    Selecionado2[indice]->Drag(Board, *Xant2[indice], *Yant2[indice]);

    // Repinto os conectores
    if(!ListaConectores.ListaVazia())
    {
         for(c = ListaConectores.listaPTR; c!=0; c = c->Next)
         {
               if(c->Conn->A == Selecionado2[indice] || c->Conn->B == Selecionado2[indice])
               {
                   c->Conn->Paint(Board->Canvas, clWhite);
                   if(*c->Conn->ID == cReta)
                   {
                       Reta *Dest = (Reta*)c->Conn;
                       if(Dest->pointingAtMe != 0)
                   	       Dest->pointingAtMe->Paint(Board->Canvas, clWhite);
                   }
               }
         }
    }
}
void ModelHandler::ArrastaGrupo(TPaintBox *Board, int X, int Y)
{
    FilaConectores c;
    FilaObjetos p;

    // contOFFSET é o contador usado para acessar
    // a distância do ponto (X,Y) ao objeto cujo indice
    // também vale contOFFSET na lista GrupoObj...
    int contOFFSET;

    POINT *Dist;

    Board->Canvas->Pen->Mode = pmXor;
    Board->Canvas->Pen->Color = clWhite;
    Board->Canvas->Pen->Style = psSolid;
    Board->Canvas->Brush->Color = clBlack;

    // Pinto os Conectores ligados a ele
    if(*Xant == -2000) // Apaga o primeiro arraste
    {
           Board->Canvas->Pen->Mode = pmWhite;
	}

    if(!GrupoConn.ListaVazia())
    {
          for(c = GrupoConn.listaPTR; c!=0; c = c->Next)
          {
				c->Conn->Paint(Board->Canvas, clWhite);
          }
    }

    if(*Xant != -2000) // Não mostra o primeiro arraste
    {
           // Apago com o XOR
    	   Board->Canvas->Pen->Style = psDot;
           Board->Canvas->Brush->Style = bsClear;

		   if(!GrupoObj.ListaVazia())
           {
			    contOFFSET = 0;
          		for(p = GrupoObj.listaPTR; p!=0; p = p->Next)
		        {
		            Dist = (POINT *)Distancias->Items[contOFFSET];
		            contOFFSET++;

		 			p->Obj->Drag(Board, *Xant - Dist->x, *Yant - Dist->y);
	            }
	       }
    }
    else
    {
		   Board->Canvas->Pen->Style = psSolid;
		   if(!GrupoObj.ListaVazia())
           {
          		for(p = GrupoObj.listaPTR; p!=0; p = p->Next)
		        {
                	*p->Obj->Visible = true;
					p->Obj->Drag(Board, *p->Obj->Xpos + *p->Obj->Width/2, *p->Obj->Ypos - *p->Obj->Height/2);
	            }
	       }

           Board->Canvas->Pen->Mode = pmWhite;
           if(!GrupoConn.ListaVazia())
           {
                for(c = GrupoConn.listaPTR; c!=0; c = c->Next)
                {
                    *(c->Conn->isDragging) = true;
                    c->Conn->Paint(Board->Canvas, clWhite);
                }
           }
    	   Board->Canvas->Pen->Style = psDot;
           Board->Canvas->Brush->Style = bsClear;

           Board->Canvas->Pen->Mode = pmXor;
    }

	*Xant = X;
  	*Yant = Y;

/*
    // Mantém o Objeto visível dentro da tela
    if(*Xant < 0) *Xant = 0;
    if(*Yant < 0) *Yant = 0;
    if(*Xant > Board->Width) *Xant = Board->Width;
    if(*Yant > Board->Height) *Yant = Board->Height;
*/
    // Pinto o Objeto Fantasma

    contOFFSET = 0;

    if(!GrupoObj.ListaVazia())
    {
 		for(p = GrupoObj.listaPTR; p!=0; p = p->Next)
        {
	 	    // Transfiro o ponto antigo para o novo
            Dist = (POINT *)Distancias->Items[contOFFSET];
            contOFFSET++;

 			p->Obj->Drag(Board, X - Dist->x, Y - Dist->y);
        }
    }

    // Repinto os conectores

    if(!GrupoConn.ListaVazia())
    {
          for(c = GrupoConn.listaPTR; c!=0; c = c->Next)
          {
				c->Conn->Paint(Board->Canvas, clWhite);
          }
    }
}
void ModelHandler::SelecionaGrupo(TPaintBox *Board, int X, int Y)
{
    Board->Canvas->Pen->Mode = pmXor;
    Board->Canvas->Pen->Color = clWhite;
    Board->Canvas->Pen->Style = psDot;
    Board->Canvas->Brush->Color = clBlack;

    if(*Xant != -2000)
    {
    	Board->Canvas->Rectangle(Base->x, Base->y, *Xant, *Yant);
    }
    *Xant = X;
    *Yant = Y;
    Board->Canvas->Rectangle(Base->x, Base->y, *Xant, *Yant);
}
bool ModelHandler::PreparaArrastaGrupo(TPaintBox *Board, int X, int Y)
{
// Esta função retorna true se existe um objeto
// do grupo sob o ponto (X,Y)...

    FilaObjetos s;
    bool achei = false;

    *ScreenLockUpdate = true;

    Board->Refresh();
    Board->Canvas->Pen->Color = clBlack;
    Board->Canvas->Brush->Color = clBlack;

	Distancias->Clear();
    // Calculo e armazeno a distância de todos os
    // objetos selecionados até o ponto (X,Y)
    POINT *Dist;
    for(s = GrupoObj.listaPTR; s!=0; s = s->Next)
    {
    	Dist = new POINT;
		Dist->x = X - (*s->Obj->Xpos + *s->Obj->Width/2);
        Dist->y = Y - (*s->Obj->Ypos - *s->Obj->Height/2);
        Distancias->Add(Dist);

		if(s->Obj->isHere(X,Y) == true)
        {
           	achei = true;
        }
        *s->Obj->Visible = false;
        s->Obj->Drag(Board, *s->Obj->Xpos + *s->Obj->Width/2, *s->Obj->Ypos - *s->Obj->Height/2);
    }
    Paint(Board->Canvas);
    *ScreenLockUpdate = false;
    if(achei)
    {
		*Xant = -2000;
        *Yant = -2000;
        *Modified = true;
    	return true;
    }
	else
    {
    	Distancias->Clear();
	    return false;
    }
}
void ModelHandler::setAllVisible(TPaintBox *Board)
{
    FilaConectores c;

    *ScreenLockUpdate = true;
    Board->Canvas->Pen->Mode = pmCopy;

    // Zero todos os conectores
	if(!ListaConectores.ListaVazia())
	{
        for(c = ListaConectores.listaPTR; c!=0; c = c->Next)
        {
            *c->Conn->Visible = true;
        	*c->Conn->isDragging = false;
    	}
    }
	*Selecionado->Visible = true;
    *Down = false;
    Paint(Board->Canvas);
    *ScreenLockUpdate = false;
}
void ModelHandler::SetAllVisible2(int indice, TPaintBox *Board)
{
    FilaConectores c;

    *ScreenLockUpdate = true;
    Board->Canvas->Pen->Mode = pmCopy;

    // Zero todos os conectores
	if(!ListaConectores.ListaVazia())
	{
        for(c = ListaConectores.listaPTR; c!=0; c = c->Next)
        {
            if(c->Conn->A == Selecionado2[indice] || c->Conn->B == Selecionado2[indice])
            {
                *c->Conn->Visible = true;
            	*c->Conn->isDragging = false;
                c->Conn->Paint(Board->Canvas, clBlack);
            }
    	}
    }
	*Selecionado2[indice]->Visible = true;
	Selecionado2[indice]->Paint(Board->Canvas);
    Board->Invalidate();
    *ScreenLockUpdate = false;
}
void ModelHandler::AcertaNovoTamanho(TPaintBox *Board)
{
     *ScreenLockUpdate = true;
     switch(*WillResize)
     {
          case 1:
               *Redimensionado->Width = *Redimensionado->Width + (*Redimensionado->Xpos - *XFinal);
               *Redimensionado->Height = *Redimensionado->Height + (*YFinal - *Redimensionado->Ypos);
               *Redimensionado->Xpos = *XFinal;
               *Redimensionado->Ypos = *YFinal;
               break;

          case 2:
               *Redimensionado->Height = *Redimensionado->Height + (*YFinal - *Redimensionado->Ypos);
               *Redimensionado->Ypos = *YFinal;
               break;

          case 3:
               *Redimensionado->Width = *XFinal - *Redimensionado->Xpos;
               *Redimensionado->Height = *Redimensionado->Height + (*YFinal - *Redimensionado->Ypos);
               *Redimensionado->Ypos = *YFinal;
               break;

          case 4:
               *Redimensionado->Width = *XFinal - *Redimensionado->Xpos;
               break;

          case 5:
               *Redimensionado->Width = *XFinal - *Redimensionado->Xpos;
               *Redimensionado->Height = *Redimensionado->Ypos - *YFinal;
               break;

          case 6:
               *Redimensionado->Height = *Redimensionado->Ypos - *YFinal;
               break;

          case 7:
               *Redimensionado->Width = *Redimensionado->Xpos + *Redimensionado->Width - *XFinal;
               *Redimensionado->Height = *Redimensionado->Ypos - *YFinal;
               *Redimensionado->Xpos = *XFinal;
               break;

          case 8:
               *Redimensionado->Width = *Redimensionado->Xpos + *Redimensionado->Width - *XFinal;
               *Redimensionado->Xpos = *XFinal;
               break;
          }
          *WillResize = 0;
          *Down = false;
          Board->Refresh();
          Board->Canvas->Pen->Mode = pmCopy;
          Paint(Board->Canvas);
          *ScreenLockUpdate = false;
}
void ModelHandler::AcertaNovoTamanho2(int indice, TPaintBox *Board, int pin)
{
     *ScreenLockUpdate = true;
     switch(pin)
     {
          case 1:
               *Selecionado2[indice]->Width = *Selecionado2[indice]->Width + (*Selecionado2[indice]->Xpos - *XFinal2[indice]);
               *Selecionado2[indice]->Height = *Selecionado2[indice]->Height + (*YFinal2[indice] - *Selecionado2[indice]->Ypos);
               *Selecionado2[indice]->Xpos = *XFinal2[indice];
               *Selecionado2[indice]->Ypos = *YFinal2[indice];
               break;

          case 2:
               *Selecionado2[indice]->Height = *Selecionado2[indice]->Height + (*YFinal2[indice] - *Selecionado2[indice]->Ypos);
               *Selecionado2[indice]->Ypos = *YFinal2[indice];
               break;

          case 3:
               *Selecionado2[indice]->Width = *XFinal2[indice] - *Selecionado2[indice]->Xpos;
               *Selecionado2[indice]->Height = *Selecionado2[indice]->Height + (*YFinal2[indice] - *Selecionado2[indice]->Ypos);
               *Selecionado2[indice]->Ypos = *YFinal2[indice];
               break;

          case 4:
               *Selecionado2[indice]->Width = *XFinal2[indice] - *Selecionado2[indice]->Xpos;
               break;

          case 5:
               *Selecionado2[indice]->Width = *XFinal2[indice] - *Selecionado2[indice]->Xpos;
               *Selecionado2[indice]->Height = *Selecionado2[indice]->Ypos - *YFinal2[indice];
               break;

          case 6:
               *Selecionado2[indice]->Height = *Selecionado2[indice]->Ypos - *YFinal2[indice];
               break;

          case 7:
               *Selecionado2[indice]->Width = *Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - *XFinal2[indice];
               *Selecionado2[indice]->Height = *Selecionado2[indice]->Ypos - *YFinal2[indice];
               *Selecionado2[indice]->Xpos = *XFinal2[indice];
               break;

          case 8:
               *Selecionado2[indice]->Width = *Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - *XFinal2[indice];
               *Selecionado2[indice]->Xpos = *XFinal2[indice];
               break;
          }

          SetAllVisible2(indice, Board);
          Board->Invalidate();
          *ScreenLockUpdate = false;
}
void ModelHandler::Redimensiona(TPaintBox *Board, int X, int Y)
{
    Board->Canvas->Pen->Mode = pmXor;
    Board->Canvas->Pen->Color = clWhite;
    Board->Canvas->Pen->Style = psDot;
    Board->Canvas->Brush->Color = clBlack;

    // Primeiro eu apago o retangulo antigo...
    switch(*WillResize)
    {
         case 1:
             if(X >= (*Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MinWidth()))
                  X = *Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MinWidth();
             if(Y <= (*Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MinHeight()))
                  Y = *Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MinHeight();
             if(X <= (*Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MaxWidth()))
                  X = *Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MaxWidth();
             if(Y >= (*Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MaxHeight()))
                  Y = *Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MaxHeight();

             if(*Xant != -2000)
             {
                  Board->Canvas->Rectangle(*Redimensionado->Xpos + *Redimensionado->Width, *Redimensionado->Ypos - *Redimensionado->Height, *Xant, *Yant);
             }

             *Xant = X;
             *Yant = Y;
             break;

         case 2:
             if(Y <= (*Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MinHeight()))
                  Y = *Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MinHeight();
             if(Y >= (*Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MaxHeight()))
                  Y = *Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MaxHeight();

             if(*Xant != -2000)
             {
                  Board->Canvas->Rectangle(*Redimensionado->Xpos + *Redimensionado->Width, *Redimensionado->Ypos - *Redimensionado->Height, *Xant, *Yant);
             }

             *Xant = *Redimensionado->Xpos;
             *Yant = Y;
		 break;

         case 3:
             if(X <= (*Redimensionado->Xpos + Redimensionado->MinWidth()))
                  X = *Redimensionado->Xpos + Redimensionado->MinWidth();
             if(Y <= (*Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MinHeight()))
                  Y = *Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MinHeight();
             if(X >= (*Redimensionado->Xpos + Redimensionado->MaxWidth()))
                  X = *Redimensionado->Xpos + Redimensionado->MaxWidth();
             if(Y >= (*Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MaxHeight()))
                  Y = *Redimensionado->Ypos - *Redimensionado->Height + Redimensionado->MaxHeight();

             if(*Xant != -2000)
             {
                  Board->Canvas->Rectangle(*Redimensionado->Xpos, *Redimensionado->Ypos - *Redimensionado->Height, *Xant, *Yant);
             }

             *Xant = X;
             *Yant = Y;
		 break;

         case 4:
             if(X <= (*Redimensionado->Xpos + Redimensionado->MinWidth()))
                  X = *Redimensionado->Xpos + Redimensionado->MinWidth();
             if(X >= (*Redimensionado->Xpos + Redimensionado->MaxWidth()))
                  X = *Redimensionado->Xpos + Redimensionado->MaxWidth();

             if(*Xant != -2000)
             {
                  Board->Canvas->Rectangle(*Redimensionado->Xpos, *Redimensionado->Ypos - *Redimensionado->Height, *Xant, *Yant);
             }

             *Xant = X;
             *Yant = *Redimensionado->Ypos;
		 break;

         case 5:
             if(X <= (*Redimensionado->Xpos + Redimensionado->MinWidth()))
                  X = *Redimensionado->Xpos + Redimensionado->MinWidth();
             if(Y >= (*Redimensionado->Ypos - Redimensionado->MinHeight()))
                  Y = *Redimensionado->Ypos - Redimensionado->MinHeight();
             if(X >= (*Redimensionado->Xpos + Redimensionado->MaxWidth()))
                  X = *Redimensionado->Xpos + Redimensionado->MaxWidth();
             if(Y <= (*Redimensionado->Ypos - Redimensionado->MaxHeight()))
                  Y = *Redimensionado->Ypos - Redimensionado->MaxHeight();

             if(*Xant != -2000)
             {
                  Board->Canvas->Rectangle(*Redimensionado->Xpos, *Redimensionado->Ypos, *Xant, *Yant);
             }

             *Xant = X;
             *Yant = Y;
		 break;

         case 6:
             if(Y >= (*Redimensionado->Ypos - Redimensionado->MinHeight()))
                  Y = *Redimensionado->Ypos - Redimensionado->MinHeight();
             if(Y <= (*Redimensionado->Ypos - Redimensionado->MaxHeight()))
                  Y = *Redimensionado->Ypos - Redimensionado->MaxHeight();

             if(*Xant != -2000)
             {
                  Board->Canvas->Rectangle(*Redimensionado->Xpos, *Redimensionado->Ypos, *Xant, *Yant);
             }

             *Xant = *Redimensionado->Xpos + *Redimensionado->Width;
             *Yant = Y;
		 break;

         case 7:
             if(X >= (*Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MinWidth()))
                  X = *Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MinWidth();
             if(Y >= (*Redimensionado->Ypos - Redimensionado->MinHeight()))
                  Y = *Redimensionado->Ypos - Redimensionado->MinHeight();
             if(X <= (*Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MaxWidth()))
                  X = *Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MaxWidth();
             if(Y <= (*Redimensionado->Ypos - Redimensionado->MaxHeight()))
                  Y = *Redimensionado->Ypos - Redimensionado->MaxHeight();

             if(*Xant != -2000)
             {
                  Board->Canvas->Rectangle(*Redimensionado->Xpos + *Redimensionado->Width, *Redimensionado->Ypos, *Xant, *Yant);
             }

             *Xant = X;
             *Yant = Y;
		 break;

         case 8:
             if(X >= (*Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MinWidth()))
                  X = *Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MinWidth();
             if(X <= (*Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MaxWidth()))
                  X = *Redimensionado->Xpos + *Redimensionado->Width - Redimensionado->MaxWidth();

             if(*Xant != -2000)
             {
                  Board->Canvas->Rectangle(*Redimensionado->Xpos + *Redimensionado->Width, *Redimensionado->Ypos, *Xant, *Yant);
             }

             *Xant = X;
             *Yant = *Redimensionado->Ypos - *Redimensionado->Height;
		 break;

    }

    // Desenho o retangulo atual...

    // O primeiro ponto do desenho do retangulo muda de lugar
    // quando eu redimensiono de cima para baixo ou de baixo
    // para cima...por isso devo ver de onde ele vem...
    if(*WillResize == 1 || *WillResize == 2)
    		Board->Canvas->Rectangle(*Redimensionado->Xpos + *Redimensionado->Width, *Redimensionado->Ypos - *Redimensionado->Height, *Xant, *Yant);
    else if(*WillResize == 3 || *WillResize == 4)
		Board->Canvas->Rectangle(*Redimensionado->Xpos, *Redimensionado->Ypos - *Redimensionado->Height, *Xant, *Yant);
    else if(*WillResize == 5 || *WillResize == 6)
		Board->Canvas->Rectangle(*Redimensionado->Xpos, *Redimensionado->Ypos, *Xant, *Yant);
    else if(*WillResize == 7 || *WillResize == 8)
		Board->Canvas->Rectangle(*Redimensionado->Xpos + *Redimensionado->Width, *Redimensionado->Ypos, *Xant, *Yant);

    *XFinal = *Xant;
    *YFinal = *Yant;
}
void ModelHandler::Redimensiona2(int indice, TPaintBox *Board, int pin, int X, int Y)
{
    Board->Canvas->Pen->Mode = pmXor;
    Board->Canvas->Pen->Color = clWhite;
    Board->Canvas->Pen->Style = psDot;
    Board->Canvas->Brush->Color = clBlack;

    // Primeiro eu apago o retangulo antigo...
    switch(pin)
    {
         case 1:
             if(X >= (*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - Selecionado2[indice]->MinWidth()))
                  X = *Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - Selecionado2[indice]->MinWidth();
             if(Y <= (*Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height + Selecionado2[indice]->MinHeight()))
                  Y = *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height + Selecionado2[indice]->MinHeight();
             if(X <= (*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - Selecionado2[indice]->MaxWidth()))
                  X = *Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - Selecionado2[indice]->MaxWidth();
             if(Y >= (*Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height + Selecionado2[indice]->MaxHeight()))
                  Y = *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height + Selecionado2[indice]->MaxHeight();

             if(*Xant2[indice] != -2000)
             {
                  Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height, *Xant2[indice], *Yant2[indice]);
             }

             *Xant2[indice] = X;
             *Yant2[indice] = Y;
             break;

         case 2:
             if(Y <= (*Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height + Selecionado2[indice]->MinHeight()))
                  Y = *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height + Selecionado2[indice]->MinHeight();
             if(Y >= (*Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height + Selecionado2[indice]->MaxHeight()))
                  Y = *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height + Selecionado2[indice]->MaxHeight();

             if(*Xant2[indice] != -2000)
             {
                  Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height, *Xant2[indice], *Yant2[indice]);
             }

             *Xant2[indice] = *Selecionado2[indice]->Xpos;
             *Yant2[indice] = Y;
		 break;

         case 3:
             if(X <= (*Selecionado2[indice]->Xpos + Selecionado2[indice]->MinWidth()))
                  X = *Selecionado2[indice]->Xpos + Selecionado2[indice]->MinWidth();
             if(Y <= (*Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height + Selecionado2[indice]->MinHeight()))
                  Y = *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height + Selecionado2[indice]->MinHeight();
             if(X >= (*Selecionado2[indice]->Xpos + Selecionado2[indice]->MaxWidth()))
                  X = *Selecionado2[indice]->Xpos + Selecionado2[indice]->MaxWidth();
             if(Y >= (*Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height + Selecionado2[indice]->MaxHeight()))
                  Y = *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height + Selecionado2[indice]->MaxHeight();

             if(*Xant2[indice] != -2000)
             {
                  Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height, *Xant2[indice], *Yant2[indice]);
             }

             *Xant2[indice] = X;
             *Yant2[indice] = Y;
		 break;

         case 4:
             if(X <= (*Selecionado2[indice]->Xpos + Selecionado2[indice]->MinWidth()))
                  X = *Selecionado2[indice]->Xpos + Selecionado2[indice]->MinWidth();
             if(X >= (*Selecionado2[indice]->Xpos + Selecionado2[indice]->MaxWidth()))
                  X = *Selecionado2[indice]->Xpos + Selecionado2[indice]->MaxWidth();

             if(*Xant2[indice] != -2000)
             {
                  Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height, *Xant2[indice], *Yant2[indice]);
             }

             *Xant2[indice] = X;
             *Yant2[indice] = *Selecionado2[indice]->Ypos;
		 break;

         case 5:
             if(X <= (*Selecionado2[indice]->Xpos + Selecionado2[indice]->MinWidth()))
                  X = *Selecionado2[indice]->Xpos + Selecionado2[indice]->MinWidth();
             if(Y >= (*Selecionado2[indice]->Ypos - Selecionado2[indice]->MinHeight()))
                  Y = *Selecionado2[indice]->Ypos - Selecionado2[indice]->MinHeight();
             if(X >= (*Selecionado2[indice]->Xpos + Selecionado2[indice]->MaxWidth()))
                  X = *Selecionado2[indice]->Xpos + Selecionado2[indice]->MaxWidth();
             if(Y <= (*Selecionado2[indice]->Ypos - Selecionado2[indice]->MaxHeight()))
                  Y = *Selecionado2[indice]->Ypos - Selecionado2[indice]->MaxHeight();

             if(*Xant2[indice] != -2000)
             {
                  Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos, *Selecionado2[indice]->Ypos, *Xant2[indice], *Yant2[indice]);
             }

             *Xant2[indice] = X;
             *Yant2[indice] = Y;
		 break;

         case 6:
             if(Y >= (*Selecionado2[indice]->Ypos - Selecionado2[indice]->MinHeight()))
                  Y = *Selecionado2[indice]->Ypos - Selecionado2[indice]->MinHeight();
             if(Y <= (*Selecionado2[indice]->Ypos - Selecionado2[indice]->MaxHeight()))
                  Y = *Selecionado2[indice]->Ypos - Selecionado2[indice]->MaxHeight();

             if(*Xant2[indice] != -2000)
             {
                  Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos, *Selecionado2[indice]->Ypos, *Xant2[indice], *Yant2[indice]);
             }

             *Xant2[indice] = *Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width;
             *Yant2[indice] = Y;
		 break;

         case 7:
             if(X >= (*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - Selecionado2[indice]->MinWidth()))
                  X = *Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - Selecionado2[indice]->MinWidth();
             if(Y >= (*Selecionado2[indice]->Ypos - Selecionado2[indice]->MinHeight()))
                  Y = *Selecionado2[indice]->Ypos - Selecionado2[indice]->MinHeight();
             if(X <= (*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - Selecionado2[indice]->MaxWidth()))
                  X = *Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - Selecionado2[indice]->MaxWidth();
             if(Y <= (*Selecionado2[indice]->Ypos - Selecionado2[indice]->MaxHeight()))
                  Y = *Selecionado2[indice]->Ypos - Selecionado2[indice]->MaxHeight();

             if(*Xant2[indice] != -2000)
             {
                  Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width, *Selecionado2[indice]->Ypos, *Xant2[indice], *Yant2[indice]);
             }

             *Xant2[indice] = X;
             *Yant2[indice] = Y;
		 break;

         case 8:
             if(X >= (*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - Selecionado2[indice]->MinWidth()))
                  X = *Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - Selecionado2[indice]->MinWidth();
             if(X <= (*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - Selecionado2[indice]->MaxWidth()))
                  X = *Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width - Selecionado2[indice]->MaxWidth();

             if(*Xant2[indice] != -2000)
             {
                  Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width, *Selecionado2[indice]->Ypos, *Xant2[indice], *Yant2[indice]);
             }

             *Xant2[indice] = X;
             *Yant2[indice] = *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height;
		 break;

    }

    // Desenho o retangulo atual...

    // O primeiro ponto do desenho do retangulo muda de lugar
    // quando eu redimensiono de cima para baixo ou de baixo
    // para cima...por isso devo ver de onde ele vem...
    if(pin == 1 || pin == 2)
  		Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height, *Xant2[indice], *Yant2[indice]);
    else if(pin == 3 || pin == 4)
		Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos, *Selecionado2[indice]->Ypos - *Selecionado2[indice]->Height, *Xant2[indice], *Yant2[indice]);
    else if(pin == 5 || pin == 6)
		Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos, *Selecionado2[indice]->Ypos, *Xant2[indice], *Yant2[indice]);
    else if(pin == 7 || pin == 8)
		Board->Canvas->Rectangle(*Selecionado2[indice]->Xpos + *Selecionado2[indice]->Width, *Selecionado2[indice]->Ypos, *Xant2[indice], *Yant2[indice]);

    *XFinal2[indice] = *Xant2[indice];
    *YFinal2[indice] = *Yant2[indice];
}
void ModelHandler::SetaCursor(TPaintBox *Board, int X, int Y)
{
    // Tenho que Verificar qual o cursor que devo colocar
    int wCursor;
    if(Selecionado != NULL)
        wCursor = Selecionado->isResize(X,Y);
    else if(*WillInsert)
    {
         Board->Cursor = crCross;
         return;
    }
    else if(*WillConnect)
    {
         Board->Cursor = crCross;
         return;
    }
    else
    {
    	Board->Cursor = crArrow;
        return;
    }

    switch(wCursor)
    {
		case 0:
			// seta Default
                        Board->Cursor = crArrow;
			break;
		case 1:
			// seta Diagonal Secundária (/)
                        Board->Cursor = crSizeNESW;
			break;
		case 2:
			// seta Vertical
                        Board->Cursor = crSizeNS;
			break;
		case 3:
			// seta Diagonal Principal (\)
                        Board->Cursor = crSizeNWSE;
			break;
		case 4:
			// seta Horizontal
                        Board->Cursor = crSizeWE;
			break;
		case 5:
			// seta Diagonal Secundária (/)
                        Board->Cursor = crSizeNESW;
			break;
		case 6:
			// seta Vertical
                        Board->Cursor = crSizeNS;
			break;
		case 7:
			// seta Diagonal Principal (\)
                        Board->Cursor = crSizeNWSE;
			break;
		case 8:
			// seta Horizontal
                        Board->Cursor = crSizeWE;
			break;
    }
}
/*************************************************************************/
void ModelHandler::ExportaModelo(AnsiString PathFile)
{
    /***************************************\
    	Gravação do Modelo no Arquivo
    \***************************************/
    FilaObjetos p;
    FilaConectores c;
    int cont;
    AnsiString Linha;

    *ModelFileName = PathFile;

    TIniFile* INITIAL;
    INITIAL = new TIniFile(PathFile);

    *LastModified = GetTime();

    // Zera o Arquivo passado como parâmetros
    INITIAL->EraseSection("Features");
    INITIAL->EraseSection("Descricao");

    // Apago as seções dos Objetos
	cont = INITIAL->ReadInteger("Qtd","Obj", 0);

    for(int i = 1; i <= cont; i++)
    {
		INITIAL->EraseSection("Objeto" + AnsiString(i));
    }

    // Apago as seções dos conectores
	cont = INITIAL->ReadInteger("Qtd","Conn", 0);

    for(int i = 1; i <= cont; i++)
    {
		INITIAL->EraseSection("Conector" + AnsiString(i));
    }

    INITIAL->EraseSection("Qtd");

    // Gravo os objetos...
    cont = 1;
    for(p = ListaObjetos.listaPTR; p!=0; p = p->Next)
    {
		p->Obj->Salva(cont, INITIAL);
        cont++;
    }

    INITIAL->WriteString("Qtd","obj", AnsiString(cont-1));

    // Gravo os conectores...
    cont = 1;
    for(c = ListaConectores.listaPTR; c!=0; c = c->Next)
    {
        c->Conn->Salva(cont, INITIAL);
        cont++;
    }

    INITIAL->WriteString("Qtd","Conn", AnsiString(cont-1));

    // Gravo os detalhes do modelo...

    INITIAL->WriteString("Features","Nome", *ModelName);
    INITIAL->WriteString("Features","LastModified", *LastModified);
    INITIAL->WriteString("Features","Domain", *Dominio);

    // Bounds
    INITIAL->WriteString("Features","HSize", *HSize);
    INITIAL->WriteString("Features","VSize", *VSize);

    // Descrição
    INITIAL->WriteString("Descricao","NumLinhas", AnsiString(LinhasDescricao->Count-1));
    for(cont = 0; cont < LinhasDescricao->Count; cont++)
    {
		INITIAL->WriteString("Descricao","L" + AnsiString(cont), LinhasDescricao->Strings[cont]);
    }

    delete INITIAL;
    *Modified = false;
}

void ModelHandler::ImportaModelo(AnsiString PathFile, TPaintBox *Board)
{
    /***************************************\
    	Recuperação do Modelo no Arquivo
    \***************************************/
    FilaObjetos p;
    int cont, i, TotalLinhas;
    Objeto *Temp, *Origem, *Destino;
    AnsiString Linha, Qtd;
    int Type, ID;
    int A, B;
    char LinhaArray[200];

    TList *ListaConn, *ListaID;
    ListaConn = new TList;
    ListaID = new TList;

    TIniFile* INITIAL;
    INITIAL = new TIniFile(PathFile);

    GrupoObj.Esvazia();
    GrupoConn.Esvazia();
    Distancias->Clear();

    NewModel(Board, "");
    *ModelFileName = PathFile;

    Selecionado = 0;
    // Restaura os Objetos
    *ModelName = IniStrToStr(INITIAL->ReadString("Features","Nome", ""));
    *LastModified = IniStrToStr(INITIAL->ReadString("Features","LastModified", ""));
    *Dominio = IniStrToStr(INITIAL->ReadString("Features","Domain", ""));

    // Bounds
    *HSize = IniStrToStr(INITIAL->ReadString("Features","HSize", "")).ToInt();
    *VSize = IniStrToStr(INITIAL->ReadString("Features","VSize", "")).ToInt();
    Board->Height = *VSize;
    Board->Width = *HSize;

    // Descrição
    LinhasDescricao->Clear();
    Qtd = IniStrToStr(INITIAL->ReadString("Descricao","NumLinhas", ""));
    TotalLinhas = Qtd.ToInt();
    for(cont = 0; cont <= TotalLinhas; cont++)
    {
        LinhasDescricao->Add(IniStrToStr(INITIAL->ReadString("Descricao","L" + AnsiString(cont), "")));
    }

    // Carrega os Objetos
    cont = INITIAL->ReadInteger("Qtd","Obj", 0);
    *QtdObjetos = cont + 1;

    for(i=1; i<=cont; i++)
    {
        Linha = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(i), "chave", ""));

        strcpy(LinhaArray, Linha.c_str());

        sscanf(LinhaArray, "%d %d", &Type, &ID);

        Temp = FabricaObjetos(Type, ID);

        Temp->Carrega(i, INITIAL);
        NewObject(Temp);
    }

    // Restaura os Conectores
    cont = INITIAL->ReadInteger("Qtd","Conn", 0);

    for(i=1; i<=cont; i++)
    {
        Linha = IniStrToStr(INITIAL->ReadString("Conector" + AnsiString(i), "chave", ""));

        strcpy(LinhaArray, Linha.c_str());

        sscanf(LinhaArray, "%d", &ID);

	    Connector *Temp;

        Temp = FabricaConectores(ID);

        Linha = IniStrToStr(INITIAL->ReadString("Conector" + AnsiString(i), "basico", ""));

        strcpy(LinhaArray, Linha.c_str());

        sscanf(LinhaArray, "%d %d", &A, &B);

        // Busco os Objetos Alocados para fazer a conexão
        for(p = ListaObjetos.listaPTR; p!=0; p=p->Next)
        {
            if(*p->Obj->Id == A)
            {
                Origem = p->Obj;
            }
            else if(*p->Obj->Id == B)
            {
                Destino = p->Obj;
            }
        }

        if(ID == cAssociacao)
        {
            int *IDReta;
            IDReta = new int;
			*IDReta = INITIAL->ReadInteger("Conector" + AnsiString(i), "end", 0);
            // Guardo para atualizar quando todos os conectores já estiverem na memória
            ListaID->Add(IDReta);
            ListaConn->Add(Temp);
            Destino = 0;
        }
        else
        {
	        NewConnector(Temp);
        }
        Temp->Connect(Origem,Destino);
        Temp->Carrega(i, INITIAL);
    }

    if(ListaConn->Count != 0)         
    {
    	RetaAssociacao *Reta;
        FilaConectores c;
        int *ID;
        for(int i=0; i < ListaConn->Count; i++)
        {
			Reta = (RetaAssociacao *)ListaConn->Items[i];
            ID = (int *)ListaID->Items[i];

	        for(c = ListaConectores.listaPTR; c!=0; c=c->Next)
	        {
				if(*c->Conn->ID == *ID)
                {
                	Reta->end = c->Conn;
                    NewConnector(Reta);
                    break;
                }
    		}
        }
    }
    Paint(Board->Canvas);
    delete INITIAL;
    *Modified = false;
}

#define ModelHandlerH
#endif
