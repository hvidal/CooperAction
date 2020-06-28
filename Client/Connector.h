#include <math.h>

#ifndef ConnectorH

typedef struct Ponto
{                        
        int X,Y;
}Ponto;                                        

class Connector
{
  public:

    AnsiString *Label;
    int *Align;

    // Position: É o valor inteiro que informa qual das seis posicoes
    // o usuário quer que o texto apareça
    int *Position;

    int *Maior;

    Objeto *A, *B;
    int *ID;
    bool *isSelected, *isDragging;
    bool *Visible;

    Connector(int ConnId)
    {
        isSelected = new bool;
        isDragging = new bool;
        ID = new int;
        Visible = new bool;
        Label = new AnsiString();
        Align = new int;
        Position = new int;
        Maior = new int;

        *Align = 2;
        *Label = "";
        *isDragging = false;
        *isSelected = false;
        *ID = ConnId;
        *Position = 3;
        *Visible = true;
    }
    ~Connector()
    {
        // Não posso desalocar o A e o B porque os objetos sempre
        // são desalocados primeiros pelo ModelHandler.
        // Se colocá-los aqui vai dar problema!
        delete isSelected, isDragging, Visible, Label, Position;
        delete Align, Maior;
    }
    Connect(Objeto *AX, Objeto *BX)
    {
        A=AX;
        B=BX;
    }
    void Selected();
    void NotSelected();
    float DistanceToBreakLine(float x, float y);
    float DistanceToLine(float x, float y);

	void Escreve(int X, int Y, TCanvas *Board);
    void AlinhaEsquerda(int X, int Y, TCanvas *Board);
    void AlinhaDireita(int X, int Y, TCanvas *Board);
    void AlinhaCentro(int X, int Y, TCanvas *Board);

	void DesenhaRetaBasica(TCanvas *Board, TColor cor);

	void PaintTextCustom(TCanvas *Board, TColor cor, Ponto pA, Ponto pB);

    virtual void Paint(TCanvas *Board, TColor cor) {}
    virtual float DistanciaAoPonto(float x, float y) {}
	void SetaCor(TCanvas *Board, TColor cor, TPenStyle notdrag, TPenStyle drag);
    Ponto Fronteira(int XDest, int YDest, int BHeight, int BWidth, int XOrig, int YOrig, int AHeight, int AWidth);

    void setText(AnsiString L, int align, int pos, int maior)
    {
    	*Label = L;
        *Align = align;
        *Position = 3; // <- Sempre no meio
        *Maior = maior;
    }

	void SalvaConector(int Ordem, TIniFile *INITIAL);
    virtual void Salva(int Ordem, TIniFile *INITIAL){}

	void CarregaConector(int Ordem, TIniFile *INITIAL);
    virtual void Carrega(int Ordem, TIniFile *INITIAL){}

};
void Connector::Selected()
{
    *isSelected = true;
}
void Connector::NotSelected()
{
    *isSelected = false;
}
void Connector::PaintTextCustom(TCanvas *Board, TColor cor, Ponto pA, Ponto pB)
{
// Posição:
//            (1)         (3)          (5)
//  Origin  --------------------------------   Dest
//            (2)         (4)          (6)
	if(*isDragging) return;

	float Vx, Vy, SomaQuadrados, CosAngulo, Angulo;
    int desvio;

    Board->Brush->Style = bsClear;
    Board->Font->Color = cor;

    if(*Position == 1)
    {
        desvio = +30;
    }
    else if(*Position == 2)
    {
        desvio = -30;
    }
    else if(*Position == 3)
	{
        float middleX = Modulo(pA.X - pB.X)/2;
        float middleY = Modulo(pA.Y - pB.Y)/2;
        middleX += Menor(pA.X, pB.X);
        middleY += Menor(pA.Y, pB.Y);

	    Board->Brush->Style = bsSolid;
        Board->Brush->Color = clWhite;
	    Escreve(middleX - *Maior/2, middleY - (Board->TextHeight("X"))/2, Board);
    	Board->Font->Color = clBlack;
        return;
    }
    else if(*Position == 4)
    {
    	Ponto Aux;
        Aux = pA;
        pA = pB;
        pB = Aux;
        desvio = -30;
    }
    else if(*Position == 5)
    {
    	Ponto Aux;
        Aux = pA;
        pA = pB;
        pB = Aux;
        desvio = +30;
    }


	Vx = pA.X - pB.X;
    Vy = pA.Y - pB.Y;

    SomaQuadrados = Vx*Vx + Vy*Vy;

	// Se o centro do objeto Origem está sobre o
	// ponto base...
	if(SomaQuadrados == 0)
	  	return;

	CosAngulo = Vx/sqrt(SomaQuadrados);

	//Consigo o angulo em Radianos
	Angulo = acos(CosAngulo);

    // Converto para Graus
	Angulo = Angulo * 180 / M_PI;

    // Se a origem (X1,Y1) estiver no 3º ou 4º quadrante
	// em relação ao ponto base, então tem que mudar o
	// sinal do angulo, pois o calculo vetorial fornece
	// o cosseno do menor ângulo entre os vetores, e não o maior...
	if(pA.X <= pB.X && pA.Y >= pB.Y)
	{
	 	// 3º Quadrante
	    Angulo = -Angulo;
	}
	else if(pA.X >= pB.X && pA.Y >= pB.Y)
	{
	    // 4º Quadrante
	    Angulo = -Angulo;
	}

	// Agora acharemos os dois pontos principais.
	// Para isso, precisamos rodar em torno do ponto base
	// um ponto que está à 10 pixels de distância do mesmo.
	// Usamos o angulo achado acima para saber qual a direção
	// da origem. Então, somamos 25 graus no sentido horário
    // e anti-horário para buscar os pontos A e B, respectivamente.

	// Não podemos nos esquecer que o nosso angulo está em graus
	// e a função cos() e sin() usam angulos em radianos, por isso
	// temos que fazer a conversão...
    POINT p;

	p.x = pB.X + 12 * cos(((Angulo + desvio)*M_PI)/180.0);
	p.y = pB.Y - 12 * sin(((Angulo + desvio)*M_PI)/180.0);

    if(*Position == 1)
    {
    	if(pA.X >= pB.X && pA.Y >= pB.Y && p.x > (*A->Xpos + *A->Width))
        	p.y -= (Board->TextHeight("X"));
    	else if(pA.X <= pB.X && pA.Y >= pB.Y && p.y < *A->Ypos)
        	p.x -= *Maior;
    	else if(pA.X <= pB.X && pA.Y <= pB.Y)
        {
            if(p.x >= *A->Xpos)
            	p.y -= (Board->TextHeight("X"));

        	p.x -= *Maior;
        }
    	else if(pA.X >= pB.X && pA.Y < pB.Y)
        {
            if(p.y <= (*A->Ypos - *A->Height))
	            p.x -= *Maior;

        	p.y -= (Board->TextHeight("X"));
        }
    }
    else if(*Position == 2)
    {
    	if(pA.X > pB.X && pA.Y > pB.Y && p.y > *A->Ypos)
        	p.x -= *Maior;
    	else if(pA.X <= pB.X && pA.Y > pB.Y)
        {
        	if(p.x < *A->Xpos)
				p.y -= (Board->TextHeight("X"));
        	p.x -= *Maior;
        }
    	else if(pA.X < pB.X && pA.Y <= pB.Y)
        {
            if(p.y > (*A->Ypos - *A->Height))
				p.x -= *Maior;
            p.y -= (Board->TextHeight("X"));
        }
    	else if(pA.X >= pB.X && pA.Y < pB.Y)
        {
            if(p.x < (*A->Xpos + *A->Width))
		       	p.y -= (Board->TextHeight("X"));
        }
    }
    else if(*Position == 4)
    {
    	if(pA.X > pB.X && pA.Y > pB.Y && p.y > *B->Ypos)
        	p.x -= *Maior;
    	else if(pA.X <= pB.X && pA.Y > pB.Y)
        {
        	if(p.x < *B->Xpos)
				p.y -= (Board->TextHeight("X"));
        	p.x -= *Maior;
        }
    	else if(pA.X < pB.X && pA.Y <= pB.Y)
        {
            if(p.y > (*B->Ypos - *B->Height))
				p.x -= *Maior;
            p.y -= (Board->TextHeight("X"));
        }
    	else if(pA.X >= pB.X && pA.Y < pB.Y)
        {
            if(p.x < (*B->Xpos + *B->Width))
		       	p.y -= (Board->TextHeight("X"));
        }
    }
    else if(*Position == 5)
    {
    	if(pA.X >= pB.X && pA.Y >= pB.Y && p.x > (*B->Xpos + *B->Width))
        	p.y -= (Board->TextHeight("X"));
    	else if(pA.X < pB.X && pA.Y >= pB.Y && p.y < *B->Ypos)
        	p.x -= *Maior;
    	else if(pA.X <= pB.X && pA.Y <= pB.Y)
        {
            if(p.x >= *B->Xpos)
            	p.y -= (Board->TextHeight("X"));

        	p.x -= *Maior;
        }
    	else if(pA.X > pB.X && pA.Y < pB.Y)
        {
            if(p.y < (*B->Ypos - *B->Height))
	            p.x -= *Maior;

        	p.y -= (Board->TextHeight("X"));
        }
    }


    Escreve(p.x, p.y, Board);

    Board->Font->Color = clBlack;
}

void Connector::Escreve(int X, int Y, TCanvas *Board)
{
	// Alinhamento:
	// 1 - Esquerda
	// 2 - Centro
	// 3 - Direita
	switch(*Align)
	{
		case 1:
			AlinhaEsquerda(X, Y, Board);
			break;
		case 2:
			AlinhaCentro(X, Y, Board);
			break;
		case 3:
			AlinhaDireita(X, Y, Board);
			break;
	}
}
void Connector::AlinhaEsquerda(int X, int Y, TCanvas *Board)
{
   	Board->TextOut(X, Y, *Label);
}

void Connector::AlinhaDireita(int X, int Y, TCanvas *Board)
{
    int x;
	x = Board->TextWidth(*Label);
   	Board->TextOut(X + *Maior - x, Y, *Label);
}
void Connector::AlinhaCentro(int X, int Y, TCanvas *Board)
{
    int x;
   	x = Board->TextWidth(*Label) - *Maior;
   	Board->TextOut(X - x/2, Y, *Label);
}

void Connector::DesenhaRetaBasica(TCanvas *Board, TColor cor)
{
	Ponto PontoBase1, PontoBase2;

    if(*Visible == false) return;

    PontoBase1 = Fronteira(*B->Xpos, *B->Ypos, *B->Height, *B->Width, *A->Xpos, *A->Ypos, *A->Height, *A->Width);
    PontoBase2 = Fronteira(*A->Xpos, *A->Ypos, *A->Height, *A->Width, *B->Xpos, *B->Ypos, *B->Height, *B->Width);

    Board->MoveTo(PontoBase1.X,PontoBase1.Y);
    Board->LineTo(PontoBase2.X,PontoBase2.Y);

    PaintTextCustom(Board, cor, PontoBase1, PontoBase2);    
}

void Connector::SetaCor(TCanvas *Board, TColor cor, TPenStyle notdrag, TPenStyle drag)
{
    Board->Pen->Color = cor;
    Board->Brush->Color = cor;

    if(*isDragging==false)
    {
        Board->Brush->Style = bsSolid;
        Board->Pen->Style = notdrag;
        if(*isSelected)
            Board->Pen->Color = clRed;
    }
    else
    {
        Board->Brush->Style = bsClear;
        Board->Pen->Style = drag;
    }
}

Ponto Connector::Fronteira(int XDest, int YDest, int BHeight, int BWidth, int XOrig, int YOrig, int AHeight, int AWidth)
{
    Ponto G;
    float X1, Y1, X2, Y2;
    X1 = XOrig + AWidth/2;
    Y1 = YOrig - AHeight/2;

    X2 = XDest + BWidth/2;;
    Y2 = YDest - BHeight/2;

    float a, b, denominador; // Coeficientes da reta: y = ax + b

    denominador = (X2 - X1);

    if(denominador==0)
    {
        if(Y1>Y2)
        {
            // A linha corta pela borda inferior...
            G.X = X1;
            G.Y = YDest;
            return G;
        }
        else
        {
            // A linha corta pela borda superior...
            G.X = X1;
            G.Y = YDest - BHeight;
            return G;
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

        Ax = YDest - BHeight;
        Bx = YDest;

        Yaux = a * (XDest) + b;

        if(Yaux >= Ax && Yaux <= Bx)
        {
            // A linha corta pela lateral esquerda...
            Yaux = a * (XDest) + b;

            G.X = XDest;
            G.Y = Yaux + 1;
            return G;
        }
        else if(Yaux > Bx && Yaux > Ax)
        {
            // A linha corta pela borda inferior...
            Xaux = ((YDest) - b)/a;

            G.X = Xaux;
            G.Y = YDest;
            return G;
        }
        else if(Yaux < Bx && Yaux < Ax)
        {
            // A linha corta pela borda superior...
            Xaux = ((YDest - BHeight) - b)/a;

            G.X = Xaux;
            G.Y = YDest - BHeight;
            return G;
        }
    }
    else // [A]<------[B]
    {
        //    +-------+ <-Ax
        //    |  Obj  |
        //    |       |
        //    +-------+ <-Bx
        float Yaux, Xaux, Ax, Bx;

        Ax = YDest - BHeight;
        Bx = YDest;

        Yaux = a * (XDest + BWidth) + b;

        if(Yaux >= Ax && Yaux <= Bx)
        {
            // A linha corta pela lateral direita...
            Yaux = a * (XDest + BWidth) + b;

            G.X = XDest + BWidth;
            G.Y = Yaux + 1;
            return G;
        }
        else if(Yaux > Bx && Yaux > Ax)
        {
            // A linha corta pela borda inferior...
            Xaux = ((YDest) - b)/a;

            G.X = Xaux;
            G.Y = YDest;
            return G;
        }
        else if(Yaux < Bx && Yaux < Ax)
        {
            // A linha corta pela borda superior...
            Xaux = ((YDest - BHeight) - b)/a;

            G.X = Xaux;
            G.Y = YDest - BHeight;
            return G;
        }
    }
}
float Connector::DistanceToLine(float c, float d)
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

    x2 = *B->Xpos + *B->Width/2;;
    y2 = *B->Ypos - *B->Height/2;
 
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
float Connector::DistanceToBreakLine(float x, float y)
{
    float X1, Y1, X2, Y2, Hdiff, Meio, Menor, distancia = 30;
    float MaiorX, MenorX, MaiorY, MenorY;

    // Centro dos Objetos
    X1 = *A->Xpos + *A->Width/2;
    Y1 = *A->Ypos - *A->Height/2;

    X2 = *B->Xpos + *B->Width/2;
    Y2 = *B->Ypos - *B->Height/2;

    Hdiff = Modulo(X1 - X2);

    if(Hdiff < (*A->Width/2 + *B->Width/2 + 20))
    {
        // Linha do meio é horizontal
        Meio = (Y1-Y2)/2.0;
        if(Meio < 0.0) Meio = -Meio;

        Menor = (Y1<Y2)?Y1:Y2;

        if(Between(y, Y1, Menor + Meio))
                distancia = Modulo(x - X1);

        if(Between(x, X1, X2) && (Modulo(y - Menor - Meio) < distancia))
        {
                distancia = Modulo(y - Menor - Meio);
        }

        if(Between(y, Menor + Meio, Y2) && (Modulo(x - X2) < distancia))
        {
                distancia = Modulo(x - X2);
        }
    }
    else
    {
        // Linha do meio é vertical
        Meio = (X1-X2)/2.0;
        if(Meio < 0.0) Meio = -Meio;

        MenorX = (X1<X2)?X1:X2;
        MaiorX = (X1>X2)?X1:X2;
        MenorY = (X1<X2)?Y1:Y2;
        MaiorY = (X1>X2)?Y1:Y2;

        if(Between(x, MenorX, MenorX + Meio))
                distancia = Modulo(y - MenorY);

        if(Between(y, Y1, Y2) && (Modulo(x - MenorX - Meio) < distancia))
        {
                distancia = Modulo(x - MenorX - Meio);
        }

        if(Between(x, MenorX + Meio, MaiorX) && (Modulo(y - MaiorY) < distancia))
        {
                distancia = Modulo(y - MaiorY);
        }
    }
    return distancia;
}

void Connector::SalvaConector(int Ordem, TIniFile *INITIAL)
{
	AnsiString Linha;

    Linha = *ID;

    INITIAL->WriteString("Conector" + AnsiString(Ordem), "chave", Linha);

    Linha = *A->Id;
    Linha += " ";
    if(B != 0)
	    Linha += *B->Id;
    else
	    Linha += "-1";

    INITIAL->WriteString("Conector" + AnsiString(Ordem), "basico", Linha);

    Linha = *Label;

    INITIAL->WriteString("Conector" + AnsiString(Ordem),"label", Linha);
    INITIAL->WriteInteger("Conector" + AnsiString(Ordem),"maior", *Maior);
    INITIAL->WriteInteger("Conector" + AnsiString(Ordem),"position", *Position);
}

void Connector::CarregaConector(int Ordem, TIniFile *INITIAL)
{
 	// Carrega a label
    *Label = IniStrToStr(INITIAL->ReadString("Conector" + AnsiString(Ordem), "label", ""));
    *Maior = INITIAL->ReadInteger("Conector" + AnsiString(Ordem), "maior", 0);
    *Position = INITIAL->ReadInteger("Conector" + AnsiString(Ordem), "position", 1);
}

#define ConnectorH
#endif