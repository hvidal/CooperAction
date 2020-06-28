#include "Objeto.h"

#ifndef BeginEndH

class BeginEnd: public Objeto
{
    int *DefaultHeight, *DefaultWidth;
    bool *end;
 public:
    BeginEnd(int _Type, int _Id, bool stEnd): Objeto(_Type, _Id)
    {
        DefaultHeight = new int;
        DefaultWidth = new int;
        end = new bool;
        *DefaultHeight = 20;
        *DefaultWidth = 20;
        *end = stEnd;
    }
    ~BeginEnd()
    {
    	delete DefaultHeight, DefaultWidth, end;
    }
    int DefaultSize_Height()
    {
        return *DefaultHeight;
    }
    int DefaultSize_Width()
    {
        return *DefaultWidth;
    }
    int MinHeight()
    {
        return 20;
    }
    int MinWidth()
    {
        return 20;
    }
    int MaxHeight()
    {
        return 20;
    }
    int MaxWidth()
    {
        return 20;
    }

    void Salva(int Ordem, TIniFile *INITIAL);
    void Carrega(int Ordem, TIniFile *INITIAL);

    void Paint(TCanvas *Board);
    void Drag(TPaintBox *Board, int X, int Y);
};

void BeginEnd::Paint(TCanvas *Board)
{
    if(*Visible == false) return;

    // Pinta o Retângulo
    Board->Pen->Color = clBlack;
    Board->Pen->Style = psSolid;
    Board->Brush->Style = bsSolid;

    if(*end)
	    Board->Brush->Color = clWhite;
    else
	    Board->Brush->Color = clBlack;

    Board->Ellipse(*Xpos, *Ypos, *Xpos + *Width, *Ypos - *Height);

    Board->Brush->Color = clBlack;
    Board->Ellipse(*Xpos + 5, *Ypos - 5, *Xpos + *Width - 5, *Ypos - *Height + 5);

    Seleciona(Board);
}
void BeginEnd::Drag(TPaintBox *Board, int X, int Y)
{
    // Pinta o Fantasma do Objeto
    // Obs.:
    // 1 - Deve estar em função de X e Y
    // 2 - X e Y estão no meio do Objeto

    *Xpos = X - *Width/2;
    *Ypos = Y + *Height/2;

    Board->Canvas->Brush->Style = bsClear;

    Board->Canvas->Ellipse(*Xpos, *Ypos, *Xpos + *Width, *Ypos - *Height);

}

void BeginEnd::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaObjeto(Ordem, INITIAL);
}
void BeginEnd::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaObjeto(Ordem, INITIAL);
}


#define BeginEndH
#endif