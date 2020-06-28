#include "Connector.h"

#ifndef RetaBolaH

class RetaBola: public Connector
{
	public:
        RetaBola(int ConnId):Connector(ConnId)
        {
        }
        float DistanciaAoPonto(float x, float y)
        {
              return DistanceToLine(x,y);
        }
	void Paint(TCanvas *Board, TColor cor);

    void Salva(int Ordem, TIniFile *INITIAL);
    void Carrega(int Ordem, TIniFile *INITIAL);
};

void RetaBola::Paint(TCanvas *Board, TColor cor)
{
    if(*Visible == false) return;

    Ponto PontoBordaOrigem;
    float X1, Y1, X2, Y2;

    X1 = *A->Xpos + *A->Width/2;
    Y1 = *A->Ypos - *A->Height/2;

    X2 = *B->Xpos + *B->Width/2;;
    Y2 = *B->Ypos - *B->Height/2;

    PontoBordaOrigem = Fronteira(*A->Xpos, *A->Ypos, *A->Height, *A->Width, *B->Xpos, *B->Ypos, *B->Height, *B->Width);

    SetaCor(Board, cor, psSolid, psDot);

    // Bola na ponta
    float a, b, denominador; // Coeficientes da reta: y = ax + b

    denominador = (X2 - X1);

    if(denominador==0)
    {
        int XGem, YGem;
        if(Y1>Y2)
        {
            // A linha corta pela borda inferior...
            XGem = X1;
            YGem = *B->Ypos;

            Board->MoveTo(PontoBordaOrigem.X, PontoBordaOrigem.Y);
            Board->LineTo(XGem, YGem + 3);

            // Desenho a bolinha...
		    SetaCor(Board, cor, psSolid, psDot);

            Board->Ellipse(XGem - 3 , YGem, XGem + 3, YGem + 7);
            Board->Pen->Color = cor;

            Board->Pen->Width = 1;

            return;
        }
        else
        {
            // A linha corta pela borda superior...
            XGem = X1;
            YGem = *B->Ypos - *B->Height;

            Board->MoveTo(PontoBordaOrigem.X, PontoBordaOrigem.Y);
            Board->LineTo(XGem, YGem - 3);

            // Desenho a bolinha...
		    SetaCor(Board, cor, psSolid, psDot);
            Board->Ellipse(XGem - 3 , YGem - 7, XGem + 3, YGem);
            Board->Pen->Color = cor;

            Board->Pen->Width = 1;

            return;
        }
    }

    a = (Y2 - Y1)/denominador;

    b = Y1 - a * X1;

    if(X2 > X1) // [A]------>[B]
    {
        //   Ax-> +-------+
        //        |  Obj  |
        //        |       |
        //   Bx-> +-------+
        float Yaux, Xaux, Ax, Bx;

        Ax = *B->Ypos - *B->Height;
        Bx = *B->Ypos;

        Yaux = a * (*B->Xpos) + b;

        if(Yaux >= Ax && Yaux <= Bx)
        {
            // A linha corta pela lateral esquerda...
            Yaux = a * (*B->Xpos - 3) + b;

            Board->MoveTo(PontoBordaOrigem.X, PontoBordaOrigem.Y);
            Board->LineTo(*B->Xpos - 3,Yaux);

            // Desenho a bolinha...
		    SetaCor(Board, cor, psSolid, psDot);
            Board->Ellipse(*B->Xpos - 6, Yaux - 3, *B->Xpos, Yaux + 3);
            Board->Pen->Color = cor;

            Board->Pen->Width = 1;
        }
        else if(Yaux > Bx && Yaux > Ax)
        {
            // A linha corta pela borda inferior...
            Xaux = ((*B->Ypos + 3) - b)/a;

            Board->MoveTo(PontoBordaOrigem.X, PontoBordaOrigem.Y);
            Board->LineTo(Xaux, *B->Ypos + 3);

            // Desenho a bolinha...
		    SetaCor(Board, cor, psSolid, psDot);
            Board->Ellipse(Xaux - 3 , *B->Ypos, Xaux + 3, *B->Ypos + 7);
            Board->Pen->Color = cor;

            Board->Pen->Width = 1;
        }
        else if(Yaux < Bx && Yaux < Ax)
        {
            // A linha corta pela borda superior...
            Xaux = ((*B->Ypos - *B->Height - 3) - b)/a;

            Board->MoveTo(PontoBordaOrigem.X, PontoBordaOrigem.Y);
            Board->LineTo(Xaux, *B->Ypos - *B->Height - 3);

            // Desenho a bolinha...
		    SetaCor(Board, cor, psSolid, psDot);
            Board->Ellipse(Xaux - 3 , *B->Ypos - *B->Height - 7, Xaux + 3, *B->Ypos - *B->Height);
            Board->Pen->Color = cor;

            Board->Pen->Width = 1;
        }
    }
    else // [A]<------[B]
    {
        //    +-------+ <-Ax
        //    |  Obj  |
        //    |       |
        //    +-------+ <-Bx
        float Yaux, Xaux, Ax, Bx;

        Ax = *B->Ypos - *B->Height;
        Bx = *B->Ypos;

        Yaux = a * (*B->Xpos + *B->Width) + b;

        if(Yaux >= Ax && Yaux <= Bx)
        {
            // A linha corta pela lateral direita...
            Yaux = a * (*B->Xpos + *B->Width + 3) + b;

            Board->MoveTo(PontoBordaOrigem.X, PontoBordaOrigem.Y);
            Board->LineTo(*B->Xpos + *B->Width + 3, Yaux);

            // Desenho a bolinha...
		    SetaCor(Board, cor, psSolid, psDot);
            Board->Ellipse(*B->Xpos + *B->Width + 6, Yaux - 3, *B->Xpos + *B->Width, Yaux + 3);
            Board->Pen->Color = cor;

            Board->Pen->Width = 1;
        }
        else if(Yaux > Bx && Yaux > Ax)
        {
            // A linha corta pela borda inferior...
            Xaux = ((*B->Ypos + 3) - b)/a;

            Board->MoveTo(PontoBordaOrigem.X, PontoBordaOrigem.Y);
            Board->LineTo(Xaux, *B->Ypos + 3);

            // Desenho a bolinha...
		    SetaCor(Board, cor, psSolid, psDot);
            Board->Ellipse(Xaux - 3 , *B->Ypos, Xaux + 3, *B->Ypos + 7);
            Board->Pen->Color = cor;

            Board->Pen->Width = 1;
        }
        else if(Yaux < Bx && Yaux < Ax)
        {
            // A linha corta pela borda superior...
            Xaux = ((*B->Ypos - *B->Height - 3) - b)/a;

            Board->MoveTo(PontoBordaOrigem.X, PontoBordaOrigem.Y);
            Board->LineTo(Xaux, *B->Ypos - *B->Height - 3);

            // Desenho a bolinha...
		    SetaCor(Board, cor, psSolid, psDot);

            Board->Ellipse(Xaux - 3 , *B->Ypos - *B->Height - 7, Xaux + 3, *B->Ypos - *B->Height);
            Board->Pen->Color = cor;

            Board->Pen->Width = 1;
        }
    }
}

void RetaBola::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaConector(Ordem, INITIAL);
}
void RetaBola::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaConector(Ordem, INITIAL);
}

#define RetaBolaH
#endif