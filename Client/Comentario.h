#include "Objeto.h"

#ifndef ComentarioH

class Comentario : public Objeto
{
    int *DefaultHeight, *DefaultWidth;
    int *TamOrelha;
    TPoint pt[6];
 public:
    Comentario(int _Type, int _Id): Objeto(_Type, _Id)
    {
        DefaultHeight = new int;
        DefaultWidth = new int;
        TamOrelha = new int;
        *DefaultHeight = 30;
        *DefaultWidth = 60;
        *TamOrelha = 5;
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
        return 80;
    }
    int MaxWidth()
    {
        return 200;
    }

    void Paint(TCanvas *Board);
    void Drag(TPaintBox *Board, int X, int Y);
	void Salva(int Ordem, TIniFile *INITIAL);
	void Carrega(int Ordem, TIniFile *INITIAL);
};

void Comentario::Paint(TCanvas *Board)
{
    if(*Visible == false) return;

    // Pinta o Comentario
    Board->Pen->Color = clBlack;
    Board->Pen->Style = psSolid;
    Board->Brush->Color = RGB(255, 254, 234);
    Board->Brush->Style = bsSolid;

    pt[0].x = *Xpos;
    pt[0].y = *Ypos;
    pt[1].x = *Xpos;
    pt[1].y = *Ypos - *Height;
    pt[2].x = *Xpos + *Width - *TamOrelha;
    pt[2].y = *Ypos - *Height;
    pt[3].x = *Xpos + *Width;
    pt[3].y = *Ypos - *Height + *TamOrelha;
    pt[4].x = *Xpos + *Width;
    pt[4].y = *Ypos;
    pt[5].x = *Xpos;
    pt[5].y = *Ypos;

    Board->Polygon(pt, 5);

    Board->MoveTo(*Xpos + *Width - *TamOrelha, *Ypos - *Height);
    Board->LineTo(*Xpos + *Width - *TamOrelha, *Ypos - *Height + *TamOrelha);
    Board->LineTo(*Xpos + *Width, *Ypos - *Height + *TamOrelha);

    // Texto Alinhado
    Board->Font->Color = clNavy;
    Board->Brush->Style = bsClear;
    PaintText(Board);

    Seleciona(Board);
}
void Comentario::Drag(TPaintBox *Board, int X, int Y)
{
    // Pinta o Fantasma do Objeto
    // Obs.:
    // 1 - Deve estar em função de X e Y
    // 2 - X e Y estão no meio do Objeto

    Board->Canvas->Brush->Style = bsClear;

    Board->Canvas->MoveTo(X - *Width/2, Y + *Height/2);
    Board->Canvas->LineTo(X - *Width/2, Y - *Height/2);
    Board->Canvas->LineTo(X + *Width/2 - *TamOrelha, Y - *Height/2);
    Board->Canvas->LineTo(X + *Width/2, Y - *Height/2 + *TamOrelha);
    Board->Canvas->LineTo(X + *Width/2, Y + *Height/2);
    Board->Canvas->LineTo(X - *Width/2, Y + *Height/2);

    Board->Canvas->MoveTo(X + *Width/2 - *TamOrelha, Y - *Height/2 + 1);
    Board->Canvas->LineTo(X + *Width/2 - *TamOrelha, Y - *Height/2 + *TamOrelha);
    Board->Canvas->LineTo(X + *Width/2, Y - *Height/2 + *TamOrelha);

    *Xpos = X - *Width/2;
    *Ypos = Y + *Height/2;
}
void Comentario::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaObjeto(Ordem, INITIAL);
}

void Comentario::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaObjeto(Ordem, INITIAL);
}
#define ComentarioH
#endif