#include "ModelHandler.h"

#ifndef InterfaceH

#define MaxLinhas 200

// Esta biblioteca é fundamental para plugar o componente
// X-Model às aplicações que o utilizam...

void AbrePropriedadeClasse(Objeto *Selected, TPaintBox *Board)
{
/*	 Classe *SelectedObject;

     SelectedObject = (Classe*)Selected;

     AnsiString Name;
     int i, align;

     // Preenche com os valores atuais...
     RetiraTodosFakers(SelectedObject->Linhas);
     ClassProp->CName->Lines = SelectedObject->Linhas;
     if(*SelectedObject->Align == 1)
	     ClassProp->ALeft->Checked = true;
     else if(*SelectedObject->Align == 2)
	     ClassProp->ACenter->Checked = true;
     else
	     ClassProp->ARight->Checked = true;

     // Carrega os Atributos no Grid
	 ClassProp->grdAtributos->RowCount = SelectedObject->listaAtributos->Count + 1;
     for(i = 0; i < SelectedObject->listaAtributos->Count; i++)
     {
		ClassProp->grdAtributos->Cells[0][i+1] = SelectedObject->getNomeAtributo(i);
		ClassProp->grdAtributos->Cells[1][i+1] = SelectedObject->getTipoAtributo(i);
		ClassProp->grdAtributos->Cells[2][i+1] = SelectedObject->getVisibilidadeAtributo(i);
     }

     // Carrega os Métodos no Grid
     ClassProp->grdMetodos->RowCount = SelectedObject->listaMetodos->Count + 1;
     for(i = 0; i < SelectedObject->listaMetodos->Count; i++)
     {
		ClassProp->grdMetodos->Cells[0][i+1] = SelectedObject->getNomeMetodo(i);
		ClassProp->grdMetodos->Cells[1][i+1] = SelectedObject->getTipoMetodo(i);
		ClassProp->grdMetodos->Cells[2][i+1] = SelectedObject->getVisibilidadeMetodo(i);
     }

     ClassProp->chkShow->Checked = SelectedObject->getHide();

     // Chama a janela de propriedades...
     ClassProp->ShowModal();

     if(ClassProp->Flag->Caption == "1") // Botão OK
     {
	     for (i = 0; i<= MaxLinhas; i++)
	     {
	     	 if(ClassProp->CName->Lines->Strings[i].Length() != 0)
	       		 Name += (ColocaFaker(ClassProp->CName->Lines->Strings[i]) + "<%>");
	 	 }
	     if(ClassProp->ALeft->Checked)
		     align = 1;
	     else if(ClassProp->ACenter->Checked)
		     align = 2;
	     else
	      	 align = 3;

         SelectedObject->EsvaziaAtributos();
         SelectedObject->EsvaziaMetodos();

         // Carrega os Atributos
         for(i = 1; i < ClassProp->grdAtributos->RowCount; i++)
	         SelectedObject->InsereAtributo(ClassProp->grdAtributos->Cells[0][i], ClassProp->grdAtributos->Cells[1][i], ClassProp->grdAtributos->Cells[2][i]);
         // Carrega os Metodos
         for(i = 1; i < ClassProp->grdMetodos->RowCount; i++)
	         SelectedObject->InsereMetodo(ClassProp->grdMetodos->Cells[0][i], ClassProp->grdMetodos->Cells[1][i], ClassProp->grdMetodos->Cells[2][i]);

         SelectedObject->setHide(ClassProp->chkShow->Checked);

	     SelectedObject->setText(Name, align);
    	 SelectedObject->AjustaNome(Board);
         SelectedObject->setHeight(Board->Canvas);
     }
*/
}
void AbrePropriedadeSimples(Objeto *SelectedObject, TPaintBox *Board)
{
     int i, align;
 	 AnsiString Name;

     // Preenche com os valores atuais...
     OProp->Name->Text = *SelectedObject->Label;

     if(*SelectedObject->Align == 1)
	     OProp->ALeft->Checked = true;
     else if(*SelectedObject->Align == 2)
	     OProp->ACenter->Checked = true;
     else
	     OProp->ARight->Checked = true;

     // Chama a janela de propriedades...
     OProp->ShowModal();

     if(OProp->Flag->Caption == "1") // Botão OK
     {
   		 Name = OProp->Name->Text;
	     if(OProp->ALeft->Checked)
		     align = 1;
	     else if(OProp->ACenter->Checked)
		     align = 2;
	     else
	      	 align = 3;

	     SelectedObject->setText(Name, align);
    	 SelectedObject->AjustaNome(Board);
     }
}

void Propriedades(Objeto *SelectedObject, TPaintBox *Board)
{
	switch(*SelectedObject->Type)
    {
    	case oClasse:
        	AbrePropriedadeClasse(SelectedObject, Board);
            break;
		case oEstadoBegin:
        case oEstadoEnd:
        	break;
        default:
        	AbrePropriedadeSimples(SelectedObject, Board);
	}
}

//------------------------------------------------------------------//

Objeto* EditaNovoClasse(int Type, int X, int Y, TPaintBox *Board, ModelHandler *That)
{
    return NULL;
/*	AnsiString Name = "";
    int i, align;
    Classe *NovaClasse;

    ClassProp->CName->Text = "";
    ClassProp->CDescription->Text = "";

    ClassProp->ACenter->Checked = true;
    ClassProp->chkShow->Checked = true;

	ClassProp->grdAtributos->RowCount = 2;
	ClassProp->grdAtributos->Cells[0][1] = "";
	ClassProp->grdAtributos->Cells[1][1] = "";
	ClassProp->grdAtributos->Cells[2][1] = "";

	ClassProp->grdMetodos->RowCount = 2;
	ClassProp->grdMetodos->Cells[0][1] = "";
	ClassProp->grdMetodos->Cells[1][1] = "";
	ClassProp->grdMetodos->Cells[2][1] = "";

    ClassProp->chkShow->Checked = false;

    ClassProp->ShowModal();

    if(ClassProp->Flag->Caption == "1") // Botão OK
    {
		for (i = 0; i<= MaxLinhas; i++)
	    {
    		if(ClassProp->CName->Lines->Strings[i].Length() != 0)
	       		 Name += (ColocaFaker(ClassProp->CName->Lines->Strings[i]) + "<%>");
        }
	    if(ClassProp->ALeft->Checked)
			align = 1;
        else if(ClassProp->ACenter->Checked)
		    align = 2;
	    else
    		align = 3;

	    if(Name.Length() != 0)
	    {
	    	NovaClasse = (Classe*)That->CriaObjeto(Type, X - 15, Y - 15, Name, Board, align);
	    }

	    // Carrega os Atributos
        for(i = 1; i < ClassProp->grdAtributos->RowCount; i++)
	        NovaClasse->InsereAtributo(ClassProp->grdAtributos->Cells[0][i], ClassProp->grdAtributos->Cells[1][i], ClassProp->grdAtributos->Cells[2][i]);
        // Carrega os Metodos
        for(i = 1; i < ClassProp->grdMetodos->RowCount; i++)
	        NovaClasse->InsereMetodo(ClassProp->grdMetodos->Cells[0][i], ClassProp->grdMetodos->Cells[1][i], ClassProp->grdMetodos->Cells[2][i]);

        NovaClasse->setHide(ClassProp->chkShow->Checked);

        Board->Refresh();
		That->Paint(Board->Canvas);
    }
*/
}

Objeto* EditaNovoSimples(int Type, int X, int Y, TPaintBox *Board, ModelHandler *That)
{
     Objeto *o;
     o = NULL;
     AnsiString Name = "";
     int i, align;
     OProp->Name->Text = "";

     OProp->ShowModal();

     if(OProp->Flag->Caption == "1") // Botão OK
     {
         Name = OProp->Name->Text;
         if(OProp->ALeft->Checked)
             align = 1;
         else if(OProp->ACenter->Checked)
             align = 2;
         else
             align = 3;
     }

     if(Name.Length() != 0)
     {
         o = That->CriaObjeto(Type, X - 15, Y - 15, Name, Board, align);
     }

     Board->Refresh();
     That->Paint(Board->Canvas);
     return o;
}

Objeto* EditaNada(int Type, int X, int Y, TPaintBox *Board, ModelHandler *That)
{
     Objeto *o = NULL;
     o = That->CriaObjeto(Type, X - 15, Y - 15, "", Board, 1);
     Board->Refresh();
     That->Paint(Board->Canvas);
     return o;
}

Objeto* EditaNovoObjeto(int Type, int X, int Y, TPaintBox *Board, ModelHandler *That)
{
	switch(Type)
    {
    	case oClasse:
        	return EditaNovoClasse(Type, X, Y, Board, That);
            break;
		case oEstadoBegin:
        case oEstadoEnd:
        	return EditaNada(Type, X, Y, Board, That);
        	break;
        default:
        	return EditaNovoSimples(Type, X, Y, Board, That);
	}
}
// *******************   CONECTORES   ************************
void AbrePropriedadeConn(Connector *SelectedConn, TPaintBox *Board)
{
     int i, align, pos, maior;
 	 AnsiString Name;

     // Preenche com os valores atuais...
     frmConnProp->Name->Text = *SelectedConn->Label;

     if(*SelectedConn->Align == 1)
	     frmConnProp->ALeft->Checked = true;
     else if(*SelectedConn->Align == 2)
	     frmConnProp->ACenter->Checked = true;
     else
	     frmConnProp->ARight->Checked = true;

     if(*SelectedConn->Position == 2)
	     frmConnProp->opt2->Checked = true;
     else if(*SelectedConn->Position == 3)
	     frmConnProp->optM->Checked = true;
     else if(*SelectedConn->Position == 4)
	     frmConnProp->opt4->Checked = true;
     else if(*SelectedConn->Position == 5)
	     frmConnProp->opt5->Checked = true;
     else // Position == 1
	     frmConnProp->opt1->Checked = true;

     // Chama a janela de propriedades...
     frmConnProp->ShowModal();

     if(frmConnProp->Flag->Caption == "1") // Botão OK
     {
   		 Name = frmConnProp->Name->Text;
	     if(frmConnProp->ALeft->Checked)
		     align = 1;
	     else if(frmConnProp->ACenter->Checked)
		     align = 2;
	     else
	      	 align = 3;

	     if(frmConnProp->opt1->Checked)
		     pos = 1;
	     else if(frmConnProp->opt2->Checked)
		     pos = 2;
	     else if(frmConnProp->optM->Checked)
		     pos = 3;
	     else if(frmConnProp->opt4->Checked)
		     pos = 4;
	     else
		     pos = 5;

	     SelectedConn->setText(Name, align, pos, maior);
     }
}
void PropriedadesConn(Connector *SelectedConn, TPaintBox *Board)
{
	AbrePropriedadeConn(SelectedConn, Board);
}

#define InterfaceH
#endif