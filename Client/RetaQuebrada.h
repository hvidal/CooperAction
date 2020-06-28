#include "Connector.h"

#ifndef RetaQuebradaH

class RetaQuebrada: public Connector
{
	public:
    RetaQuebrada(int ConnId):Connector(ConnId)
    {
    }
    float DistanciaAoPonto(float x, float y)
    {
	    return DistanceToBreakLine(x,y);
    }
	void Paint(TCanvas *Board, TColor cor);

    void Salva(int Ordem, TIniFile *INITIAL);
    void Carrega(int Ordem, TIniFile *INITIAL);
};

void RetaQuebrada::Paint(TCanvas *Board, TColor cor)
{
    if(*Visible == false) return;

    float X1, Y1, X2, Y2, Hdiff, Meio, Menor;

    // Centro dos Objetos
    X1 = *A->Xpos + *A->Width/2;
    Y1 = *A->Ypos - *A->Height/2;

    X2 = *B->Xpos + *B->Width/2;
    Y2 = *B->Ypos - *B->Height/2;

    SetaCor(Board, cor, psSolid, psDot);

    Hdiff = X1 - X2;
    if(Hdiff < 0) Hdiff = -Hdiff;

    if(Hdiff < (*A->Width/2 + *B->Width/2 + 20))
    {

// Linha do meio é horizontal
//        |    |
//        X X  X
//        +----+
//        |Obj |
//        +----+
//        X X  X
//        |    |

        Meio = (Y1-Y2)/2;
        if(Meio < 0) Meio = -Meio;

        Menor = (Y1<Y2)?Y1:Y2;

        Board->MoveTo(X1,Y1);
        Board->LineTo(X1, Menor + Meio);
        Board->LineTo(X2, Menor + Meio);
        Board->LineTo(X2,Y2);
    }
    else
    {

// Linha do meio é vertical
//        |    |
//      X |    | X
//   -----+----+-----
//        |Obj |
//   -----+----+-----
//      X |    | X
//        |    |

        Meio = (X1-X2)/2;
        if(Meio < 0) Meio = -Meio;

        Menor = (X1<X2)?X1:X2;

        Board->MoveTo(X1,Y1);
        Board->LineTo(Menor + Meio ,Y1);
        Board->LineTo(Menor + Meio, Y2);
        Board->LineTo(X2,Y2);
    }
}
void RetaQuebrada::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaConector(Ordem, INITIAL);
}

void RetaQuebrada::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaConector(Ordem, INITIAL);
}
#define RetaQuebradaH
#endif