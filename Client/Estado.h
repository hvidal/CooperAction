#include "Objeto.h"

#ifndef EstadoH

class Estado: public Objeto
{
    int *DefaultHeight, *DefaultWidth;
 public:
    Estado(int _Type, int _Id): Objeto(_Type, _Id)
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
        return 40;
    }
    int MinWidth()
    {
        return 40;
    }
    int MaxHeight()
    {
        return 100;
    }
    int MaxWidth()
    {
        return 200;
    }

    void Salva(int Ordem, TIniFile *INITIAL);
    void Carrega(int Ordem, TIniFile *INITIAL);

    void Paint(TCanvas *Board);
    void Drag(TPaintBox *Board, int X, int Y);
};

void Estado::Paint(TCanvas *Board)
{
    if(*Visible == false) return;

    // Pinta o Estado
    Board->Pen->Color = clBlack;
    Board->Pen->Style = psSolid;
    Board->Brush->Color = (TColor)RGB(239, 239, 239);
    Board->Brush->Style = bsSolid;

    Board->RoundRect(*Xpos, *Ypos, *Xpos + *Width, *Ypos - *Height, 20, 20);

    // Texto Alinhado
    Board->Font->Color = clNavy;
    Board->Brush->Style = bsClear;
    PaintText(Board);
    Seleciona(Board);
}
void Estado::Drag(TPaintBox *Board, int X, int Y)
{
    // Pinta o Fantasma do Objeto
    // Obs.:
    // 1 - Deve estar em função de X e Y
    // 2 - X e Y estão no meio do Objeto

    Board->Canvas->Brush->Style = bsClear;

    Board->Canvas->RoundRect(X - *Width/2, Y - *Height/2, X + *Width/2, Y + *Height/2, 20, 20);

    *Xpos = X - *Width/2;
    *Ypos = Y + *Height/2;
}

void Estado::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaObjeto(Ordem, INITIAL);
}
void Estado::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaObjeto(Ordem, INITIAL);
}


#define EstadoH
#endif