#include"Connector.h"
#include"Objeto.h"

#ifndef ListaEncadeadaConnH

// Classe que cria uma lista duplamente encadeada
// de conectores.
struct nodeConn
{
  	Connector *Conn;
   	struct nodeConn *Next;
   	struct nodeConn *Prior;
};
typedef struct nodeConn *FilaConectores;

class ListaEncadeadaConn
{
	public:
	FilaConectores listaPTR, FinalListaPTR;

	ListaEncadeadaConn()
	{
		listaPTR = 0;
		FinalListaPTR = 0;
	}
	~ListaEncadeadaConn()
	{
    	Clear();
	}
	bool ListaVazia();
    void Clear();
    void Apaga(Connector *view);
	void Esvazia();
	void InsereLista(Connector *Novo);
	void RemoveLista();
	bool ExisteConexao(Objeto *O1, Objeto *O2);
    void UnSelectAllConnectors();
	void RemovePorObjeto(Objeto *Obj);
};

void ListaEncadeadaConn::Apaga(Connector *conn)
{
   	FilaConectores p, q;

   	p=listaPTR;
   	q=0;
   	while(p!=0)
   	{
       	if (p->Conn == conn)
       	{
           	if(q == 0) // p é o primeiro Conector da lista
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

void ListaEncadeadaConn::Clear()
{
	FilaConectores c, lixo;
    Connector *CLixo;
	if(!ListaVazia())
	{
	 	c = listaPTR;
	 	while(c != 0)
   		{
   			CLixo = c->Conn;
   			lixo = c;
   			c = c->Next;
   			delete CLixo, lixo;
  		}
	}
	listaPTR = 0;
    FinalListaPTR = 0;    
}

bool ListaEncadeadaConn::ListaVazia()
{
	return (listaPTR == 0);
}

void ListaEncadeadaConn::Esvazia()
{
	FilaConectores c, lixo;
	if(!ListaVazia())
	{
	 	c = listaPTR;
	 	while(c != 0)
        {
			*c->Conn->isSelected = false;
            lixo = c;
            c = c->Next;
            delete lixo;
        }
	}
	listaPTR = 0;
    FinalListaPTR = 0;
}

void ListaEncadeadaConn::InsereLista(Connector *Novo)
{
		FilaConectores NovoNode;
    	NovoNode = new nodeConn;
    	NovoNode->Conn = Novo;
    	NovoNode->Prior = 0;
    	NovoNode->Next = listaPTR;
    	if(listaPTR != 0)
		listaPTR->Prior = NovoNode;
    	else
    		FinalListaPTR = NovoNode;

	listaPTR = NovoNode;
}

void ListaEncadeadaConn::RemoveLista()
{
	// Apaga o conector selecionado

   	FilaConectores p, q;

   	p=listaPTR;
   	q=0;
   	while(p!=0)
   	{
       	if (*p->Conn->isSelected)
       	{
           	if(q == 0) // p é o primeiro Conector da lista
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
bool ListaEncadeadaConn::ExisteConexao(Objeto *O1, Objeto *O2)
{
	FilaConectores c;
    if(!ListaVazia())
    {
          for(c = listaPTR; c!=0; c = c->Next)
          {
                if((c->Conn->A == O1 && c->Conn->B == O2) || (c->Conn->A == O2 && c->Conn->B == O1))
                      return true;
          }
    }
    return false;
}

void ListaEncadeadaConn::RemovePorObjeto(Objeto *Obj)
{
/*	// Busco e apago todas as ligações com o Objeto Obj

	FilaConectores c, d, clixo;

	c = listaPTR;
        d=0;

	while(c != 0)
        {
        	if(c->Conn->A == Obj || c->Conn->B == Obj)
                {
                	if(d == 0)  // c é o primeiro conector da lista
                        	listaPTR = c->Next;
	                else
	                        d->Next = c->Next;

	                clixo = c;
	                c = c->Next;
	                delete clixo;
	                continue;
                }
                d=c;
                c = c->Next;
        }
*/
    FilaConectores c;
    TList *ListaDelecao;
    ListaDelecao = new TList();

    if(!ListaVazia())
    {
        for(c = listaPTR; c!=0; c = c->Next)
        {
            if(c->Conn->A == Obj || c->Conn->B == Obj)
            {
                if(*c->Conn->ID == cReta)
                {
                    Reta *view;
                    view = (Reta*)c->Conn;
                    if (view->pointingAtMe != NULL)
                    {
                        view->pointingAtMe->end = NULL;
                        Apaga(view->pointingAtMe);
                        view->pointingAtMe = NULL;
                    }
                }
                else if (*c->Conn->ID == cAssociacao)
                {
                    RetaAssociacao *view;
                    view = (RetaAssociacao*)c->Conn;
                    if (view->end != NULL)
                    {
                        ((Reta*)view->end)->pointingAtMe = NULL;
                    }
                }
                ListaDelecao->Add(c->Conn);
            }
        }
    }

    for(int i = 0; i < ListaDelecao->Count; i++)
    {
        Apaga((Connector*)ListaDelecao->Items[i]);
    }

    delete ListaDelecao;
}

void ListaEncadeadaConn::UnSelectAllConnectors()
{
		FilaConectores c;
	    if(!ListaVazia())
	    {
	          for(c = listaPTR; c!=0; c = c->Next)
	          {
	              (c->Conn)->NotSelected();
	          }
	    }
}
#define ListaEncadeadaConnH
#endif