#include "Connector.h"

#ifndef RetaLosangoH

class RetaLosango: public Connector
{
    bool Pinta;
    public:
    RetaLosango(int ConnId, bool _Pinta):Connector(ConnId)
    {
    	Pinta = _Pinta;
    }
    float DistanciaAoPonto(float x, float y)
    {
	    return DistanceToLine(x,y);
    }
    void Paint(TCanvas *Board, TColor cor);

    void Salva(int Ordem, TIniFile *INITIAL);
    void Carrega(int Ordem, TIniFile *INITIAL);
};

void RetaLosango::Paint(TCanvas *Board, TColor cor)
{
    if(*Visible == false) return;
/*
//	  Ponto 1
//    	    .
// ponto 2 / \
//    ---.<  > Ponto 0 = Ponto 4
//  	   |/
//	       '
//	  Ponto 3
*/
	float X1, Y1, Angulo, CosAngulo, Vx, Vy, SomaQuadrados;
    TColor CorOriginal;

	Ponto PontoBase, PontoBordaOrigem;
    TPoint p[5];

    SetaCor(Board, cor, psSolid, psDot);

	// Centro dos Objetos
  	X1 = *A->Xpos + *A->Width/2;
   	Y1 = *A->Ypos - *A->Height/2;

    // Busco o ponto na borda do objeto
    PontoBase = Fronteira(*B->Xpos, *B->Ypos, *B->Height, *B->Width, *A->Xpos, *A->Ypos, *A->Height, *A->Width);
    p[0].x = PontoBase.X;
    p[0].y = PontoBase.Y;

    // O ponto inicial � igual ao ponto final
    p[4].x = PontoBase.X;
    p[4].y = PontoBase.Y;

    // O vetor (Vx,Vy) � o vetor que parte do ponto base,
    // e atinge a origem (X1,Y1)
    Vx =X1 - p[0].x;
    Vy =Y1 - p[0].y;

    // Agora usaremos a f�rmula
    //        u . v = |u||v| cos �
    // Onde:
    // u . v = Produto Escalar
    // Obs.: Neste caso o produto escalar � feito entre o vetor
    //      (Vx,Vy) com o vetor horizontal (1,0).
    //       Portanto, Produto Escalar = Vx.
    // |u| = m�dulo de u = raiz quadrada de Vx^2 + Vy^2
    // |v| = m�dulo de v = 1
    // cos � = � o que n�s queremos

    SomaQuadrados = Vx*Vx + Vy*Vy;

    // Se o centro do objeto Origem est� sobre o
    // ponto base...
    if(SomaQuadrados == 0)
    	return;

    CosAngulo = Vx/sqrt(SomaQuadrados);

    //Consigo o angulo em Radianos
    Angulo = acos(CosAngulo);

    // Converto para Graus
    Angulo = Angulo * 180 / M_PI;

    // Se a origem (X1,Y1) estiver no 3� ou 4� quadrante
    // em rela��o ao ponto base, ent�o tem que mudar o
    // sinal do angulo, pois o calculo vetorial fornece
    // o cosseno do menor �ngulo entre os vetores, e n�o o maior...
    if(X1 <= p[0].x && Y1 >= p[0].y)
    {
    	// 3� Quadrante
        Angulo = -Angulo;
    }
    else if(X1 >= p[0].x && Y1 >= p[0].y)
    {
        // 4� Quadrante
        Angulo = -Angulo;
    }

    // Agora acharemos os dois pontos principais.
    // Para isso, precisamos rodar em torno do ponto base
    // um ponto que est� � 10 pixels de dist�ncia do mesmo.
    // Usamos o angulo achado acima para saber qual a dire��o
    // da origem. Ent�o, somamos 25 graus no sentido hor�rio
    // e anti-hor�rio para buscar os pontos A e B, respectivamente.

    // N�o podemos nos esquecer que o nosso angulo est� em graus
    // e a fun��o cos() e sin() usam angulos em radianos, por isso
    // temos que fazer a convers�o...

	p[1].x = p[0].x + 10 * cos(((Angulo - 30)*M_PI)/180.0);
	p[1].y = p[0].y - 10 * sin(((Angulo - 30)*M_PI)/180.0);

	p[3].x = p[0].x + 10 * cos(((Angulo + 30)*M_PI)/180.0);
	p[3].y = p[0].y - 10 * sin(((Angulo + 30)*M_PI)/180.0);

    p[2].x = p[0].x + 19 * cos(((Angulo)*M_PI)/180.0);
	p[2].y = p[0].y - 19 * sin(((Angulo)*M_PI)/180.0);

    PontoBase.X = p[0].x + 17 * cos(((Angulo)*M_PI)/180.0);
	PontoBase.Y = p[0].y - 17 * sin(((Angulo)*M_PI)/180.0);

    CorOriginal = Board->Brush->Color;

    Board->Brush->Color = clBlack;
    if(Pinta)
    {
    	Board->Polygon(p, 4);
    }
    else
    {
        Board->Polyline(p, 4);
    }
    Board->Brush->Color = CorOriginal;

    PontoBordaOrigem = Fronteira(*A->Xpos, *A->Ypos, *A->Height, *A->Width, *B->Xpos, *B->Ypos, *B->Height, *B->Width);
    if (*isDragging)
    {
        Board->Brush->Style = bsClear;
        Board->Pen->Style = psDot;
    }    
    Board->MoveTo(PontoBordaOrigem.X, PontoBordaOrigem.Y);
    Board->LineTo(PontoBase.X, PontoBase.Y);
    PaintTextCustom(Board, cor, PontoBase, PontoBordaOrigem);
}

void RetaLosango::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaConector(Ordem, INITIAL);
}

void RetaLosango::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaConector(Ordem, INITIAL);
}
#define RetaLosangoH
#endif