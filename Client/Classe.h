#include "Objeto.h"

#include "frmClasse.h"

#ifndef ClasseH

#define IconHeight 15

class Classe: public Objeto
{
    int *DefaultHeight, *DefaultWidth, *FitHeight;
    bool *Hide;

	struct Item
	{
	   	AnsiString *Nome, *Tipo, *Visibility;
	};

 public:
    TList *listaAtributos;
    TList *listaMetodos;

    Classe(int _Type, int _Id): Objeto(_Type, _Id)
    {
        DefaultHeight = new int;
        DefaultWidth = new int;
        FitHeight = new int;
        Hide = new bool;

        listaAtributos = new TList();
        listaMetodos = new TList();

        *DefaultHeight = 50;
        *DefaultWidth = 60;
    }
    ~Classe()
    {
    	delete DefaultHeight, DefaultWidth;
        delete FitHeight, listaAtributos, listaMetodos, Hide;
    }
    int DefaultSize_Height()
    {
        return *DefaultHeight;
    }
    int DefaultSize_Width()
    {
        return *DefaultWidth;
    }

    int MinHeight()
    {
        return *FitHeight;
    }
    int MinWidth()
    {
        return 30;
    }
    int MaxHeight()
    {
        return 300;
    }
    int MaxWidth()
    {
        return 200;
    }
	void InsereAtributo(AnsiString AtribName, AnsiString Tipo, AnsiString Visibilidade);
	void InsereMetodo(AnsiString MethodName, AnsiString Tipo, AnsiString Visibilidade);

    AnsiString getNomeAtributo(int Indice);
    AnsiString getTipoAtributo(int Indice);
    AnsiString getVisibilidadeAtributo(int Indice);
    AnsiString getNomeMetodo(int Indice);
    AnsiString getTipoMetodo(int Indice);
    AnsiString getVisibilidadeMetodo(int Indice);

	void setHeight(TCanvas *Board);

	int getImageIndex(AnsiString Visibilidade, bool Atributo);
	void setHide(bool HideValue);
	bool getHide();

	void EsvaziaAtributos();
	void EsvaziaMetodos();

    void Paint(TCanvas *Board);
    void Drag(TPaintBox *Board, int X, int Y);
	void Salva(int Ordem, TIniFile *INITIAL);
	void Carrega(int Ordem, TIniFile *INITIAL);
};

void Classe::setHide(bool HideValue)
{
	*Hide = HideValue;
}
void Classe::setHeight(TCanvas *Board)
{
    int TextHeight = Board->TextHeight("X");

    if(*Hide)
    {
	    *FitHeight = TextHeight + IconHeight * 2 + 7;
    	*Height = *FitHeight;
    }
    else
    {
	    *FitHeight = TextHeight + IconHeight*(listaAtributos->Count + listaMetodos->Count) + 7;
	    if(*Height < *FitHeight)
	    {
	    	*Height = *FitHeight;
	    }
    }
}
bool Classe::getHide()
{
	return *Hide;
}
void Classe::Paint(TCanvas *Board)
{
    if(*Visible == false) return;

    int TextHeight, c;

    TextHeight = Board->TextHeight("X");

	setHeight(Board);

    // Pinta o Retângulo
    Board->Pen->Color = clBlack;
    Board->Pen->Style = psSolid;
    Board->Brush->Color = (TColor) RGB(239, 239, 239);
    Board->Brush->Style = bsSolid;

    Board->Rectangle(*Xpos, *Ypos, *Xpos + *Width, *Ypos - *Height);

    // Primeira Linha
    Board->MoveTo(*Xpos, *Ypos - *Height + (TextHeight) + 2);
    Board->LineTo(*Xpos  + *Width, *Ypos - *Height + (TextHeight) + 2);

    // segunda Linha
    if(*Hide)
    {
	    Board->MoveTo(*Xpos, *Ypos - *Height + IconHeight + (TextHeight) + 4);
	    Board->LineTo(*Xpos  + *Width, *Ypos - *Height + IconHeight + (TextHeight) + 4);
    }
    else
    {
	    Board->MoveTo(*Xpos, *Ypos - *Height + IconHeight*(listaAtributos->Count) + (TextHeight) + 4);
	    Board->LineTo(*Xpos  + *Width, *Ypos - *Height + IconHeight*(listaAtributos->Count) + (TextHeight) + 4);
    }

    // Texto Alinhado
    Board->Font->Color = clNavy;
    Board->Brush->Style = bsClear;

    int Altura;

    PaintTextCustom(*Ypos - *Height, Board);

    if(*Hide)
    {
	    Seleciona(Board);    
    	return;
    }

    Board->Font->Color = clMaroon;

    AnsiString Nome, Tipo;
    Graphics::TBitmap *Icon;
    Icon = new Graphics::TBitmap();

    // Escreve os Atributos
    Altura = *Ypos - *Height + (TextHeight) + 3;
    for(c = 0; c < listaAtributos->Count; c++)
    {
    	Nome = getNomeAtributo(c);
    	if(Nome != "")
        {
	    	// Pinto o icone da visibilidade
	    	ClassProp->ClassImages->GetBitmap(getImageIndex(getVisibilidadeAtributo(c), true), Icon);

			// Tenho que diminuir o Width da figura porque
            // ela vem (não sei porque) com tamanho 16, e o
            // correto é 15...
            Icon->Width--;

    	    Board->Draw(*Xpos + 2, Altura, Icon);
	        // Escrevo o texto depois do icone
            Tipo = getTipoAtributo(c);
            if(Tipo != "")
            	Tipo = " : " + Tipo;
	    	Board->TextOut(*Xpos + 18, Altura, Nome + Tipo);
			Altura += IconHeight;
        }
    }

    // Escreve os Metodos
    Altura = *Ypos - *Height + IconHeight*(listaAtributos->Count) + (TextHeight) + 5;
    for(c = 0; c < listaMetodos->Count; c++)
    {
    	Nome = getNomeMetodo(c);
    	if(Nome != "")
        {
	    	// Pinto o icone da visibilidade
	    	ClassProp->ClassImages->GetBitmap(getImageIndex(getVisibilidadeMetodo(c), false), Icon);

			// Tenho que diminuir o Width da figura porque
            // ela vem (não sei porque) com tamanho 16, e o
            // correto é 15...
            Icon->Width--;

    	    Board->Draw(*Xpos + 2, Altura, Icon);
	        // Escrevo o texto depois do icone
            Tipo = getTipoMetodo(c);
            if(Tipo != "")
            	Tipo = " : " + Tipo;
	    	Board->TextOut(*Xpos + 18, Altura, Nome + Tipo);
			Altura += IconHeight;
        }
    }
	Board->Font->Color = clBlack;
    Seleciona(Board);
}
void Classe::Drag(TPaintBox *Board, int X, int Y)
{
    // Pinta o Fantasma do Objeto
    // Obs.:
    // 1 - Deve estar em função de X e Y
    // 2 - X e Y estão no meio do Objeto

    Board->Canvas->Brush->Style = bsClear;

    Board->Canvas->Rectangle(X - *Width/2, Y - *Height/2, X + *Width/2, Y + *Height/2);

    int TextHeight;

    TextHeight = Board->Canvas->TextHeight("X");

    Board->Canvas->MoveTo(X - *Width/2 + 1, Y - *Height/2 + (TextHeight) + 2);
    Board->Canvas->LineTo(X  + *Width/2 - 1, Y - *Height/2 + (TextHeight) + 2);

    if(*Hide)
    {
	    Board->Canvas->MoveTo(X - *Width/2 + 1, Y - *Height/2 + TextHeight + IconHeight + 4);
    	Board->Canvas->LineTo(X  + *Width/2 - 1, Y - *Height/2 + TextHeight + IconHeight + 4);
    }
    else
    {
	    Board->Canvas->MoveTo(X - *Width/2 + 1, Y - *Height/2 + TextHeight + IconHeight*listaAtributos->Count + 4);
    	Board->Canvas->LineTo(X  + *Width/2 - 1, Y - *Height/2 + TextHeight + IconHeight*listaAtributos->Count + 4);
    }

    *Xpos = X - *Width/2;
    *Ypos = Y + *Height/2;
}
void Classe::InsereAtributo(AnsiString AtribName, AnsiString Tipo, AnsiString Visibilidade)
{
    Item *NovoAtributo;
    NovoAtributo = new Item;
    NovoAtributo->Nome = new AnsiString;
    NovoAtributo->Tipo = new AnsiString;
    NovoAtributo->Visibility = new AnsiString;
    *NovoAtributo->Nome = AtribName;
    *NovoAtributo->Tipo = Tipo;
    *NovoAtributo->Visibility = Visibilidade;
    listaAtributos->Add(NovoAtributo);
}
void Classe::InsereMetodo(AnsiString MethodName, AnsiString Tipo, AnsiString Visibilidade)
{
    Item *NovoMetodo;
    NovoMetodo = new Item;
    NovoMetodo->Nome = new AnsiString;
    NovoMetodo->Tipo = new AnsiString;
    NovoMetodo->Visibility = new AnsiString;
    *NovoMetodo->Nome = MethodName;
    *NovoMetodo->Tipo = Tipo;
    *NovoMetodo->Visibility = Visibilidade;
    listaMetodos->Add(NovoMetodo);
}
AnsiString Classe::getNomeAtributo(int Indice)
{
	Item *Att;
    Att = (Item*)listaAtributos->Items[Indice];
	return *Att->Nome;
}
AnsiString Classe::getTipoAtributo(int Indice)
{
	Item *Att;
    Att = (Item*)listaAtributos->Items[Indice];
	return *Att->Tipo;
}
AnsiString Classe::getVisibilidadeAtributo(int Indice)
{
	Item *Att;
    Att = (Item*)listaAtributos->Items[Indice];
	return *Att->Visibility;
}

AnsiString Classe::getNomeMetodo(int Indice)
{
	Item *Met;
    Met = (Item*)listaMetodos->Items[Indice];
	return *Met->Nome;
}
AnsiString Classe::getTipoMetodo(int Indice)
{
	Item *Met;
    Met = (Item*)listaMetodos->Items[Indice];
	return *Met->Tipo;
}
AnsiString Classe::getVisibilidadeMetodo(int Indice)
{
	Item *Met;
    Met = (Item*)listaMetodos->Items[Indice];
	return *Met->Visibility;
}

void Classe::EsvaziaAtributos()
{
	listaAtributos->Clear();
}

void Classe::EsvaziaMetodos()
{
	listaMetodos->Clear();
}

int Classe::getImageIndex(AnsiString Visibilidade, bool Atributo)
{
// Pega o indice da imagem que está na ImageList do formulário
// ClassProp...

	if(Atributo)
    {
		if(Visibilidade == "Private")
        	return 0;
		else if(Visibilidade == "Public")
        	return 1;
		else if(Visibilidade == "Protected")
        	return 2;
		else if(Visibilidade == "Implementation")
        	return 3;
    }
    else
    {
		if(Visibilidade == "Private")
        	return 4;
		else if(Visibilidade == "Public")
        	return 5;
		else if(Visibilidade == "Protected")
        	return 6;
		else if(Visibilidade == "Implementation")
        	return 7;
    }
}

void Classe::Salva(int Ordem, TIniFile *INITIAL)
{
	int cont;

    SalvaObjeto(Ordem, INITIAL);

    INITIAL->WriteBool("Objeto" + AnsiString(Ordem), "Hide", *Hide);
    INITIAL->WriteInteger("Objeto" + AnsiString(Ordem), "NAttr", listaAtributos->Count);
    INITIAL->WriteInteger("Objeto" + AnsiString(Ordem), "NMeth", listaMetodos->Count);

    for(cont = 0; cont < listaAtributos->Count; cont++)
    {
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "Attr" + AnsiString(cont), getNomeAtributo(cont));
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "AttrT" + AnsiString(cont), getTipoAtributo(cont));
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "AttrV" + AnsiString(cont), getVisibilidadeAtributo(cont));
    }
    for(cont = 0; cont < listaMetodos->Count; cont++)
    {
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "Meth" + AnsiString(cont), getNomeMetodo(cont));
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "MethT" + AnsiString(cont), getTipoMetodo(cont));
		INITIAL->WriteString("Objeto" + AnsiString(Ordem), "MethV" + AnsiString(cont), getVisibilidadeMetodo(cont));
    }

}

void Classe::Carrega(int Ordem, TIniFile *INITIAL)
{
	int cont, Qtd;
    AnsiString Nome, Tipo, Visibilidade;

    CarregaObjeto(Ordem, INITIAL);

    *Hide = INITIAL->ReadBool("Objeto" + AnsiString(Ordem), "Hide", false);

    Qtd = INITIAL->ReadInteger("Objeto" + AnsiString(Ordem),"NAttr", 0);
    for(cont = 0; cont < Qtd; cont++)
    {
    	Nome = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "Attr" + AnsiString(cont), ""));
        Tipo = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "AttrT" + AnsiString(cont), ""));
        Visibilidade = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "AttrV" + AnsiString(cont), ""));
        InsereAtributo(Nome, Tipo, Visibilidade);
    }

    Qtd = INITIAL->ReadInteger("Objeto" + AnsiString(Ordem),"NMeth", 0);
    for(cont = 0; cont < Qtd; cont++)
    {
    	Nome = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "Meth" + AnsiString(cont), ""));
        Tipo = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "MethT" + AnsiString(cont), ""));
        Visibilidade = IniStrToStr(INITIAL->ReadString("Objeto" + AnsiString(Ordem), "MethV" + AnsiString(cont), ""));
        InsereMetodo(Nome, Tipo, Visibilidade);
    }

}
#define ClasseH
#endif