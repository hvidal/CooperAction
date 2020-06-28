#include "Objeto.h"

#ifndef RetanguloH

class Retangulo: public Objeto
{
    int *DefaultHeight, *DefaultWidth;
 public:
    Retangulo(int _Type, int _Id): Objeto(_Type, _Id)
    {
        DefaultHeight = new int;
        DefaultWidth = new int;
        *DefaultHeight = 30;
        *DefaultWidth = 60;
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
        return 25;
    }
    int MinWidth()
    {
        return 30;
    }
    int MaxHeight()
    {
        return 60;
    }
    int MaxWidth()
    {
        return 120;
    }

    void Salva(int Ordem, TIniFile *INITIAL);
    void Carrega(int Ordem, TIniFile *INITIAL);

    void Paint(TCanvas *Board);
    void Drag(TPaintBox *Board, int X, int Y);
};

void Retangulo::Paint(TCanvas *Board)
{
    if(!*Visible) return;

    // Pinta o Retângulo
    Board->Pen->Color = clBlack;
    Board->Pen->Style = psSolid;
    Board->Brush->Color = clWhite;
    Board->Brush->Style = bsSolid;

    Board->Rectangle(*Xpos, *Ypos, *Xpos + *Width, *Ypos - *Height);
    Board->MoveTo(*Xpos, *Ypos - 3);
    Board->LineTo(*Xpos  + *Width, *Ypos - 3);

    Board->MoveTo(*Xpos, *Ypos - 5);
    Board->LineTo(*Xpos  + *Width, *Ypos - 5);

    // Texto Alinhado
    Board->Font->Color = clNavy;
    Board->Brush->Style = bsClear;
    PaintText(Board);
    Seleciona(Board);
}
void Retangulo::Drag(TPaintBox *Board, int X, int Y)
{
    // Pinta o Fantasma do Objeto
    // Obs.:
    // 1 - Deve estar em função de X e Y
    // 2 - X e Y estão no meio do Objeto

    Board->Canvas->Brush->Style = bsClear;

    Board->Canvas->Rectangle(X - *Width/2, Y - *Height/2, X + *Width/2, Y + *Height/2);

    Board->Canvas->MoveTo(X - *Width/2 + 1, Y + *Height/2 - 3);
    Board->Canvas->LineTo(X  + *Width/2 - 1, Y + *Height/2 - 3);

    Board->Canvas->MoveTo(X - *Width/2 + 1, Y + *Height/2 - 5);
    Board->Canvas->LineTo(X  + *Width/2 - 1, Y + *Height/2 - 5);

    *Xpos = X - *Width/2;
    *Ypos = Y + *Height/2;
}

void Retangulo::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaObjeto(Ordem, INITIAL);
}
void Retangulo::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaObjeto(Ordem, INITIAL);
}


#define RetanguloH
#endif