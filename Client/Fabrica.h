#include "Retangulo.h"
#include "Boneco.h"
#include "Comentario.h"
#include "Estado.h"
#include "BeginEnd.h"

#include "Reta.h"
#include "RetaQuebrada.h"
#include "RetaBola.h"
#include "SetaHeranca.h"
#include "SetaDependencia.h"
#include "RetaLosango.h"
#include "RetaAssociacao.h"

#ifndef FabricaH

#define cRetaBola 		1
#define cReta 			2
#define cRetaQuebrada 	3
#define cSetaHeranca 	4
#define cAgregacao 		5
#define cComposicao 	6
#define cDependencia 	7
#define cTransicao		8
#define cAssociacao		9

#define oRetangulo 	 1
#define oClasse 	 2
#define oBoneco 	 3
#define oEstado 	 4
#define oEstadoBegin 5
#define oEstadoEnd   6
#define oComentario 	-1    

Objeto* FabricaObjetos(int Type, int ID)
{
    Objeto *Produto;
    switch(Type)
    {
        case oRetangulo:
            Produto = new Retangulo(Type, ID);
            break;
        case oBoneco:
            Produto = new Boneco(Type, ID);
            break;
        case oEstado:
            Produto = new Estado(Type, ID);
            break;
        case oEstadoBegin:
            Produto = new BeginEnd(Type, ID, false);
            break;
        case oEstadoEnd:
            Produto = new BeginEnd(Type, ID, true);
            break;
        case oComentario:
            Produto = new Comentario(Type, ID);
            break;
    }
    return Produto;
}

Connector* FabricaConectores(int ID)
{
    Connector *Produto;
    switch(ID)
    {
        case cRetaBola:
            Produto = new RetaBola(ID);
            break;
        case cReta:
            Produto = new Reta(ID);
            break;
        case cRetaQuebrada:
            Produto = new RetaQuebrada(ID);
            break;
        case cSetaHeranca:
            Produto = new SetaHeranca(ID);
            break;
        case cAgregacao:
            Produto = new RetaLosango(ID, false);
            break;
        case cComposicao:
            Produto = new RetaLosango(ID, true);
            break;
        case cDependencia:
            Produto = new SetaDependencia(ID, true);
            break;
        case cTransicao:
            Produto = new SetaDependencia(ID, false);
            break;
        case cAssociacao:
            Produto = new RetaAssociacao(ID);
            break;
    }
    return Produto;
}

#define FabricaH
#endif
