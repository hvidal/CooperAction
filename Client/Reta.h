#include "Connector.h"
#include "RetaAssociacao.h"

#ifndef RetaH

class Reta: public Connector
{
	public:
        // Reta de associação que se liga a mim
    	RetaAssociacao *pointingAtMe;

        Reta(int ConnId):Connector(ConnId)
        {
        	pointingAtMe = 0;
        }
        ~Reta()
        {
        	pointingAtMe->end = 0;
        }
        float DistanciaAoPonto(float x, float y)
        {
              return DistanceToLine(x,y);
        }
		void Paint(TCanvas *Board, TColor cor);

    	void Salva(int Ordem, TIniFile *INITIAL);
	    void Carrega(int Ordem, TIniFile *INITIAL);
};

void Reta::Paint(TCanvas *Board, TColor cor)
{
    SetaCor(Board, cor, psSolid, psDot);
	DesenhaRetaBasica(Board, cor);
}

void Reta::Salva(int Ordem, TIniFile *INITIAL)
{
    SalvaConector(Ordem, INITIAL);
    if(pointingAtMe != 0)
    {
	    INITIAL->WriteInteger("Conector" + AnsiString(Ordem),"pointingAtMe", *pointingAtMe->ID);
    }
}

void Reta::Carrega(int Ordem, TIniFile *INITIAL)
{
    CarregaConector(Ordem, INITIAL);
}

#define RetaH
#endif
