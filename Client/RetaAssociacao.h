#include "Connector.h"

#ifndef RetaAssociacaoH

class RetaAssociacao: public Connector
{
	public:
    	Connector *end;    
        RetaAssociacao(int ConnId):Connector(ConnId)
        {
        }
        float DistanciaAoPonto(float x, float y)
        {
              return DistanceToThisLine(x,y);
        }
		void Paint(TCanvas *Board, TColor cor);
	    float DistanceToThisLine(float x, float y);

    	void Salva(int Ordem, TIniFile *INITIAL);
	    void Carrega(int Ordem, TIniFile *INITIAL);
};

void RetaAssociacao::Paint(TCanvas *Board, TColor cor)
{
    SetaCor(Board, cor, psDash, psDot);

    if(*Visible == false) return;

	Ponto PontoBase1, PontoBaseA1, PontoBaseA2, PontoBase2;

    PontoBaseA1 = Fronteira(*end->A->Xpos, *end->A->Ypos, *end->A->Height, *end->A->Width, *end->B->Xpos, *end->B->Ypos, *end->B->Height, *end->B->Width);
    PontoBaseA2 = Fronteira(*end->B->Xpos, *end->B->Ypos, *end->B->Height, *end->B->Width, *end->A->Xpos, *end->A->Ypos, *end->A->Height, *end->A->Width);
    PontoBase2.X = Menor(PontoBaseA1.X, PontoBaseA2.X) + Modulo(PontoBaseA1.X - PontoBaseA2.X)/2;
    PontoBase2.Y = Menor(PontoBaseA1.Y, PontoBaseA2.Y) + Modulo(PontoBaseA1.Y - PontoBaseA2.Y)/2;

    PontoBase1 = Fronteira(*A->Xpos, *A->Ypos, *A->Height, *A->Width, PontoBase2.X, PontoBase2.Y, 0, 0);

    if(*isDragging != true)
    	Board->Brush->Color = clWhite;

    Board->MoveTo(PontoBase1.X,PontoBase1.Y);
    Board->LineTo(PontoBase2.X,PontoBase2.Y);

    PaintTextCustom(Board, cor, PontoBase1, PontoBase2);
}
float RetaAssociacao::DistanceToThisLine(float c, float d)
{
/*
*	Calcula a distância de um ponto (c, d) à reta
*	formada pelos pontos (x1,y1) e (x2,y2).
*	Cálculos: Olhar caderno de C.V.G.A. do
*	prof. Flávio Dickenstein
*/
 	float a, b, x, y, qx, qy;
    float x1, y1, x2, y2;

    x1 = *A->Xpos + *A->Width/2;
    y1 = *A->Ypos - *A->Height/2;

 	Ponto PontoBaseA1, PontoBaseA2;

    // Calculo o ponto (x2, y2) que está no meio da reta apontada por *end;
	PontoBaseA1 = Fronteira(*end->A->Xpos, *end->A->Ypos, *end->A->Height, *end->A->Width, *end->B->Xpos, *end->B->Ypos, *end->B->Height, *end->B->Width);
	PontoBaseA2 = Fronteira(*end->B->Xpos, *end->B->Ypos, *end->B->Height, *end->B->Width, *end->A->Xpos, *end->A->Ypos, *end->A->Height, *end->A->Width);

	x2 = Menor(PontoBaseA1.X, PontoBaseA2.X) + Modulo(PontoBaseA1.X - PontoBaseA2.X)/2;
	y2 = Menor(PontoBaseA1.Y, PontoBaseA2.Y) + Modulo(PontoBaseA1.Y - PontoBaseA2.Y)/2;

	if(Modulo(x1-x2) == 0) // Reta Vertical
    {
        return Modulo(c - x1);
    }
	if(Modulo(y1-y2) == 0) // Reta Horizontal
    {
        return Modulo(d - y1);
    }
	a = (y1-y2)/(x1-x2);
	b = y2 - a * x2;

	x = (c - a*b + a*d)/(a*a + 1);
	y = (c - x + a*d)/a;

	qx = (x-c)*(x-c);
	qy = (y-d)*(y-d);

	return sqrt(qx+qy);
}
void RetaAssociacao::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaConector(Ordem, INITIAL);
    INITIAL->WriteInteger("Conector" + AnsiString(Ordem),"end", *end->ID);
}

void RetaAssociacao::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaConector(Ordem, INITIAL);
}

#define RetaAssociacaoH
#endif