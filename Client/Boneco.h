#include "Objeto.h"

#ifndef BonecoH

class Boneco: public Objeto
{
    int *DefaultHeight, *DefaultWidth;
 public:
    Boneco(int _Type, int _Id): Objeto(_Type, _Id)
    {
        DefaultHeight = new int;
        DefaultWidth = new int;
        *DefaultHeight = 60;
        *DefaultWidth = 40;
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

    void Paint(TCanvas *Board);
    void Drag(TPaintBox *Board, int X, int Y);
	void Salva(int Ordem, TIniFile *INITIAL);
	void Carrega(int Ordem, TIniFile *INITIAL);

};

void Boneco::Paint(TCanvas *Board)
{
    if(*Visible == false) return;

    // Pinta o Retângulo
    Board->Pen->Color = clWhite;
    Board->Pen->Style = psSolid;
    Board->Brush->Color = clWhite;
    Board->Brush->Style = bsSolid;

    Board->Rectangle(*Xpos, *Ypos, *Xpos + *Width, *Ypos - *Height);

    Board->Pen->Color = clBlack;
    Board->Ellipse(*Xpos + *Width/2 - 7, *Ypos - *Height, *Xpos + *Width/2 + 7, *Ypos - *Height + 14);

    // Tronco
    Board->MoveTo(*Xpos + *Width/2, *Ypos - *Height + 14);
    Board->LineTo(*Xpos + *Width/2, *Ypos - *Height + 35);

    // Perna Esquerda
    Board->LineTo(*Xpos + *Width/2 - 8, *Ypos - *Height + 45);

    // Perna Direita
    Board->MoveTo(*Xpos + *Width/2, *Ypos - *Height + 35);
    Board->LineTo(*Xpos + *Width/2 + 8, *Ypos - *Height + 45);

    // Braço Esquerdo
    Board->MoveTo(*Xpos + *Width/2, *Ypos - *Height + 20);
    Board->LineTo(*Xpos + *Width/2 - 9, *Ypos - *Height + 28);

    // Braço Direito
    Board->MoveTo(*Xpos + *Width/2, *Ypos - *Height + 20);
    Board->LineTo(*Xpos + *Width/2 + 9, *Ypos - *Height + 28);

    Board->Font->Color = clNavy;

    // Texto Alinhado
    Board->Font->Color = clNavy;
    Board->Brush->Style = bsClear;
    PaintTextCustom(*Ypos - *Height + 45, Board);

    Seleciona(Board);
}
void Boneco::Drag(TPaintBox *Board, int X, int Y)
{
    // Pinta o Fantasma do Objeto
    // Obs.:
    // 1 - Deve estar em função de X e Y
    // 2 - X e Y estão no meio do Objeto

    Board->Canvas->Brush->Style = bsClear;

    Board->Canvas->Ellipse(X - 7, Y - *Height/2, X + 7, Y - *Height/2 + 14);

    // Tronco
    Board->Canvas->MoveTo(X , Y - *Height/2 + 14);
    Board->Canvas->LineTo(X, Y - *Height/2 + 35);

    // Perna Esquerda
    Board->Canvas->LineTo(X - 8, Y - *Height/2 + 45);

    // Perna Direita
    Board->Canvas->MoveTo(X, Y - *Height/2 + 35);
    Board->Canvas->LineTo(X + 8, Y - *Height/2 + 45);

    // Braço Esquerdo
    Board->Canvas->MoveTo(X, Y - *Height/2 + 20);
    Board->Canvas->LineTo(X - 9, Y - *Height/2 + 28);

    // Braço Direito
    Board->Canvas->MoveTo(X, Y - *Height/2 + 20);
    Board->Canvas->LineTo(X + 9, Y - *Height/2 + 28);

    *Xpos = X - *Width/2;
    *Ypos = Y + *Height/2;
}
void Boneco::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaObjeto(Ordem, INITIAL);
}

void Boneco::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaObjeto(Ordem, INITIAL);
}


#define BonecoH
#endif