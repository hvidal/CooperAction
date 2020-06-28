#include "FuncoesBasicas.h"
#include <stdio.h>

#ifndef ObjetoH

class Objeto
{
  public:                       
/*
*        *Xpos    *Width  
*           |<------->|
*           v
*           +---------+  -
*           |         |  | *Height
*           |         |  |
*   *Ypos-> +---------+  -
*/
    AnsiString *Label;
    double *Id;
    int *Type;
    int *Xpos;
    int *Ypos;
    int *Height, *Width;
    int *Align;
    bool *GroupSelected;

    virtual int DefaultSize_Height(){}
    virtual int DefaultSize_Width(){}
    virtual int MinHeight(){}
    virtual int MinWidth(){}
    virtual int MaxHeight(){}
    virtual int MaxWidth(){}

    bool *Visible;

    bool *isSelected;

    Objeto(int _Type, int _Id, int _X, int _Y, int _Height, int _Width);
    Objeto(int _Type, int _Id)
    {
        Aloca();
        *Id = _Id;
        *Type = _Type;
        *Label = "";
    }
    ~Objeto()
    {
        delete Id, Xpos, Ypos, Height, Width, isSelected;
        delete Label, Type, Visible, Align, GroupSelected;
    }
    void Inicializa(int _X, int _Y);
    void Aloca();
    void AjustaNome(TPaintBox *Board);
    void PaintText(TCanvas *Board);
    void PaintTextCustom(int Altura, TCanvas *Board);
    void AlinhaEsquerda(int Altura, TCanvas *Board);
    void AlinhaDireita(int Altura, TCanvas *Board);
    void AlinhaCentro(int Altura, TCanvas *Board);
    void setBounds(int newHeight, int newWidth);
	void Restaura(int _X, int _Y, int _Height, int _Width, AnsiString _Label, int _Align);
    void Seleciona(TCanvas *Board);
    bool isHere(int X, int Y);
    int isResize(int X, int Y);
    void Agrupa();
    virtual void Paint(TCanvas *Board) {}
    virtual void Drag(TPaintBox *Board, int X, int Y) {}

	void SalvaObjeto(int Ordem, TIniFile *INITIAL);
    virtual void Salva(int Ordem, TIniFile *INITIAL){}

	void CarregaObjeto(int Ordem, TIniFile *INITIAL);
    virtual void Carrega(int Ordem, TIniFile *INITIAL){}

    void setText(AnsiString L, int align)
    {
    	*Label = L;
        *Align = align;
    }
    void Selected();
};

void Objeto::Aloca()
{
        Id = new double;
        Xpos = new int;
        Ypos = new int;
        Height = new int;
        Width = new int;
        Align = new int;
        isSelected = new bool;
        Label = new AnsiString();
        Type = new int;
        Visible = new bool;
        GroupSelected = new bool;
}
void Objeto::Agrupa()
{
	*GroupSelected = true;
    *isSelected = false;
}
void Objeto::Inicializa(int _X, int _Y)
{
    *Xpos = _X;
    *Ypos = _Y + DefaultSize_Height();
    *Height = DefaultSize_Height();
    *Width = DefaultSize_Width();
    *Label = "";
    *Align = 2;
    *isSelected = false;
    *GroupSelected = false;
    *Visible = true;
}
void Objeto::Restaura(int _X, int _Y, int _Height, int _Width, AnsiString _Label, int _Align)
{
    *Xpos = _X;
    *Ypos = _Y;
    *Height = _Height;
    *Width = _Width;
    *Label = _Label;
    *Align = _Align;
    *isSelected = false;
    *GroupSelected = false;
    *Visible = true;
}
Objeto::Objeto(int _Type, int _Id, int _X, int _Y, int _Height, int _Width)
{
    Aloca();
    *Id = _Id;
    *Type = _Type;
    Inicializa(_X, _Y);
}
bool Objeto::isHere(int X, int Y)
{
    if((X>=(*Xpos - 2) && X<=(*Xpos + *Width + 3)) && (Y>=(*Ypos - *Height - 2) && Y<=(*Ypos + 3)))
        return true;
    return false;
}
void Objeto::Selected()
{
    *isSelected = true;
    *GroupSelected = false;
}
void Objeto::PaintText(TCanvas *Board)
{
	PaintTextCustom(*Ypos - *Height/2 - (Board->TextHeight("X"))/2, Board);
}
void Objeto::PaintTextCustom(int Altura, TCanvas *Board)
{
	// Alinhamento:
	// 1 - Esquerda
	// 2 - Centro
	// 3 - Direita
	switch(*Align)
	{
		case 1:
			AlinhaEsquerda(Altura, Board);
			break;
		case 2:
			AlinhaCentro(Altura, Board);
			break;
		case 3:
			AlinhaDireita(Altura, Board);
			break;
	}
}
void Objeto::AlinhaEsquerda(int Altura, TCanvas *Board)
{
   	Board->TextOut(*Xpos + 2, Altura, *Label);
}
void Objeto::AlinhaDireita(int Altura, TCanvas *Board)
{
    int x;
    AnsiString Linha;

    // Texto Alinhado à direita
	x = Board->TextWidth(*Label);
   	Board->TextOut(*Xpos + *Width - x - 2, Altura, *Label);
}
void Objeto::AlinhaCentro(int Altura, TCanvas *Board)
{
    int x;
   	x = Board->TextWidth(*Label) - *Width;
   	Board->TextOut(*Xpos - x/2, Altura, *Label);
}
void Objeto::AjustaNome(TPaintBox *Board)
{
	// Ajusta o tamanho do objeto
    // de acordo com o texto em seu interior...

	int MaiorHeight, MaiorWidth=0;
   	MaiorWidth = Board->Canvas->TextWidth(*Label);

    MaiorHeight = Board->Canvas->TextHeight("XXX"); // Serve qualquer texto
    if(MaiorWidth > *Width)
    {
         if(MaiorWidth < MaxWidth())
         {
              if((MaiorWidth + 4) < MaxWidth())
                  *Width = MaiorWidth + 4;
              else
                  *Width = MaiorWidth;
         }
         else
         {
              *Width = MaxWidth();
         }
    }
    if(MaiorHeight > *Height)
    {
         if(MaiorHeight < MaxHeight())
         {
              if((MaiorHeight + 4) < MaxHeight())
                  *Height = MaiorHeight + 4;
              else
                  *Height = MaiorHeight;
         }
         else
         {
              *Height = MaxHeight();
         }
    }

}
void Objeto::Seleciona(TCanvas *Board)
{
	bool Pinta = false;

    if(*isSelected)
    {
		Board->Pen->Color = clBlack;
        Board->Brush->Color = clBlack;
        Pinta = true;
    }
    else if(*GroupSelected)
    {
		Board->Pen->Color = clGray;
        Board->Brush->Color = clGray;
        Pinta = true;
    }

    if(Pinta)
    {
        Board->Pen->Style = psSolid;
        Board->Brush->Style = bsSolid;

        Board->Rectangle(*Xpos - 2, *Ypos - 2 , *Xpos + 3, *Ypos + 3);
        Board->Rectangle(*Xpos + *Width/2 - 2, *Ypos - 2 , *Xpos + *Width/2 + 3, *Ypos + 3);
        Board->Rectangle(*Xpos + *Width - 2, *Ypos - 2 , *Xpos + *Width + 3, *Ypos + 3);

        Board->Rectangle(*Xpos + *Width - 2, *Ypos - *Height/2 - 2 , *Xpos + *Width + 3, *Ypos - *Height/2 + 3);

        Board->Rectangle(*Xpos - 2, *Ypos - *Height - 2 , *Xpos + 3, *Ypos - *Height + 3);
        Board->Rectangle(*Xpos + *Width/2 - 2, *Ypos - *Height - 2 , *Xpos + *Width/2 + 3, *Ypos - *Height + 3);
        Board->Rectangle(*Xpos + *Width - 2, *Ypos - *Height - 2 , *Xpos + *Width + 3, *Ypos - *Height + 3);

        Board->Rectangle(*Xpos - 2, *Ypos - *Height/2 - 2 , *Xpos + 3, *Ypos - *Height/2 + 3);
    }
}
int Objeto::isResize(int X, int Y)
{
/*
                         7--6--5
                         |     |
                         8     4
                         |     |
                         1--2--3
*/
    if((X>=(*Xpos - 2) && X<=(*Xpos + 3)) && (Y>=(*Ypos - 2) && Y<=(*Ypos + 3)))
        return 1;
    else if(X>=(*Xpos + *Width/2 - 2) && X<=(*Xpos + *Width/2 + 3) && (Y>=(*Ypos - 2) && Y<=(*Ypos + 3)))
        return 2;
    else if(X>=(*Xpos + *Width - 2) && X<=(*Xpos + *Width + 3) && (Y>=(*Ypos - 2) && Y<=(*Ypos + 3)))
        return 3;
    else if((X>=(*Xpos + *Width - 2) && X<=(*Xpos + *Width + 3)) && (Y>=(*Ypos - *Height/2 - 2) && Y<=(*Ypos - *Height/2 + 3)))
        return 4;
    else if(X>=(*Xpos + *Width - 2) && X<=(*Xpos + *Width + 3) && (Y>=(*Ypos - *Height - 2) && Y<=(*Ypos - *Height + 3)))
        return 5;
    else if(X>=(*Xpos + *Width/2 - 2) && X<=(*Xpos + *Width/2 + 3) && (Y>=(*Ypos - *Height - 2) && Y<=(*Ypos - *Height + 3)))
        return 6;
    else if((X>=(*Xpos - 2) && X<=(*Xpos + 3)) && (Y>=(*Ypos - *Height - 2) && Y<=(*Ypos - *Height + 3)))
        return 7;
    else if((X>=(*Xpos - 2) && X<=(*Xpos + 3)) && (Y>=(*Ypos - *Height/2 - 2) && Y<=(*Ypos - *Height/2 + 3)))
        return 8;
    else
        return 0;
}

void Objeto::SalvaObjeto(int Ordem, TIniFile *INITIAL)
{
	AnsiString Linha;

    Linha = *Type;
    Linha += " ";
    Linha += *Id;

    INITIAL->WriteString("Objeto" + AnsiString(Ordem),"chave", Linha);

    Linha = *Xpos;
    Linha += " ";
    Linha += *Ypos;
    Linha += " ";
    Linha += *Height;
    Linha += " ";
    Linha += *Width;
    Linha += " ";
    Linha += *Align;

    INITIAL->WriteString("Objeto" + AnsiString(Ordem),"basico", Linha);

    Linha = *Label;

    INITIAL->WriteString("Objeto" + AnsiString(Ordem),"label", Linha);

}
void Objeto::CarregaObjeto(int Ordem, TIniFile *INITIAL)
{
    char LinhaArray[200];
    AnsiString Linha;
	int _Xpos, _Ypos, _Width, _Height, _Align;

    Linha = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "basico", ""));

    strcpy(LinhaArray, Linha.c_str());

	// Configurável - Deve-se adicionar ou remover os parâmetros que quizer.
    sscanf(LinhaArray, "%d %d %d %d %d", &_Xpos, &_Ypos, &_Height, &_Width, &_Align);

    Linha = IniStrToStr(INITIAL->ReadString("objeto" + AnsiString(Ordem), "label", ""));

    Restaura(_Xpos, _Ypos, _Height, _Width, Linha, _Align);
}
#define ObjetoH
#endif
