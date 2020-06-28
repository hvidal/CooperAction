#include "Objeto.h"

#ifndef ListaEncadeadaObjH

// Classe que cria uma lista duplamente encadeada
// de objetos.
struct nodeObj
{
   	Objeto *Obj;
   	struct nodeObj *Next;
   	struct nodeObj *Prior;
};
typedef struct nodeObj *FilaObjetos;

class ListaEncadeadaObj
{
	public:
	FilaObjetos listaPTR, FinalListaPTR;

	ListaEncadeadaObj()
	{
		listaPTR = 0;
		FinalListaPTR = 0;
	}
	~ListaEncadeadaObj()
	{
    	Clear();
	}
	bool ListaVazia();
    void Clear();
	void Esvazia();    
	void InsereLista(Objeto *Novo);
	void RemoveLista(Objeto *VaiMorrer);
};
void ListaEncadeadaObj::Clear()
{
	FilaObjetos p, lixo;
    Objeto *OLixo;
	if(!ListaVazia())
	{
	 	p = listaPTR;
	 	while(p != 0)
        {
        	OLixo = p->Obj;
       		lixo = p;
            p = p->Next;
       		delete OLixo, lixo;
        }
	}
	listaPTR = 0;
    FinalListaPTR = 0;
}
void ListaEncadeadaObj::Esvazia()
{
	FilaObjetos p, lixo;
	if(!ListaVazia())
	{
	 	p = listaPTR;
	 	while(p != 0)
        {
			*p->Obj->isSelected = false;
		    *p->Obj->GroupSelected = false;
            lixo = p;
            p = p->Next;
            delete lixo;
        }
	}
	listaPTR = 0;
    FinalListaPTR = 0;
}
bool ListaEncadeadaObj::ListaVazia()
{
	return (listaPTR == 0);
}

void ListaEncadeadaObj::InsereLista(Objeto *Novo)
{
	FilaObjetos NovoNode;
   	NovoNode = new nodeObj;
   	NovoNode->Obj = Novo;
   	NovoNode->Prior = 0;
   	NovoNode->Next = listaPTR;
   	if(listaPTR != 0)
		listaPTR->Prior = NovoNode;
   	else
   		FinalListaPTR = NovoNode;

	listaPTR = NovoNode;
}
void ListaEncadeadaObj::RemoveLista(Objeto *VaiMorrer)
{
	// Apaga o objeto selecionado

   	FilaObjetos p, q;

  	p=listaPTR;
   	q=0;
   	while(p!=0)
   	{
       	if (p->Obj == VaiMorrer)
       	{
          	if(q == 0) // p é o primeiro Objeto da lista
               	listaPTR = p->Next;
           	else
               	q->Next = p->Next;

           	if(p->Next != 0)
            	p->Next->Prior = q;

			if(FinalListaPTR == p) // P é o último
				FinalListaPTR = p->Prior;

	        delete p;
	        break;
		}
	    q=p;
	    p=p->Next;
	}

}

#define ListaEncadeadaObjH
#endif