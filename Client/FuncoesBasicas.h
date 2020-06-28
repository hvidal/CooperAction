#ifndef FuncoesBasicasH

AnsiString LoginUserName()
{
    AnsiString Name;
    DWORD size = MAX_PATH + 1;
    char name[MAX_PATH+1];
    name[0] = '\0'; // Initiate
    GetUserName(name, &size);
    Name = AnsiString(name);
    return Name;
}

#include <objbase.h>
unsigned int GetNewID()
{
    GUID guid;
    ::CoCreateGuid(&guid);
    // unsigned int
    return guid.Data1;
}

float Modulo(float x)
{
      if(x <= 0.0)
           return (-x);
      else
          return x;
}

float Menor(float a, float b)
{
      if(a < b)
           return a;
      else
          return b;
}

TStringList* Break(AnsiString S)
{
	AnsiString Token;
    TStringList *Ret;
	int Tam,i,aux;

    Ret = new TStringList;
    Token = "";
    Tam = S.Length();
    aux = 1;
    while(aux <= Tam)
    {
       if (S[aux]=='<')
       {
          if(S[aux+1]=='%' && S[aux+2]=='>')
          {
            aux = aux + 2;
            // Retorno:
            Ret->Add(Token.Trim());
            Token = "";
            aux = aux + 1;
            continue;
          }
          Token = Token + '<';
          aux = aux + 1;
          continue;
       }
       Token = Token + S[aux];
       aux = aux + 1;
    }
    return Ret;
}

AnsiString ColocaFaker(AnsiString Text)
{
	int Pos = 1;
    while(Pos)
    {
    	Pos = Text.AnsiPos("<%>");
        if(Pos != 0)
	        Text.Insert("%", Pos + 1);
    }
    return Text;
}

AnsiString RetiraFaker(AnsiString Text)
{
	int Pos = 1;
    while(Pos)
    {
    	Pos = Text.AnsiPos("<%%>");
        if(Pos != 0)
	        Text.Delete(Pos + 1, 1);
    }
    return Text;
}

void RetiraTodosFakers(TStringList *Linhas)
{
    for(int i=0; i < Linhas->Count; i++)
    {
    	Linhas->Strings[i] = RetiraFaker(Linhas->Strings[i]);
    }
}

bool Between(float valor, float a, float b)
{
	if(a < b)
	{
		if(valor >= a && valor <= b)
			return true;
		else
                	return false;
	}
	else
	{
		if(valor >= b && valor <= a)
			return true;
		else
                	return false;
	}

}

int InsideRect(float x, float y, float xa, float ya, float xb, float yb, float Erro)
{
	float MenorX, MenorY, MaiorX, MaiorY;

    MenorX = (xa<xb)?xa:xb;
    MaiorX = (xa>xb)?xa:xb;
    MenorY = (ya<yb)?ya:yb;
    MaiorY = (ya>yb)?ya:yb;

    if(Modulo(xa - xb) <= 4.0)
    {
    	if(Between(y, ya, yb))
        	return true;
        else
            return false;
    }
    else if(Modulo(ya - yb) <= 4.0)
    {
        if(Between(x, xa, xb))
            return true;
        else
            return false;
    }

	if(Between(x, MenorX - Erro, MaiorX + Erro) && Between(y, MenorY - Erro, MaiorY + Erro))
	      return true;
	else
          return false;
}

AnsiString StrToIniStr(const AnsiString Str)
{
  char Buffer[4096];
  PChar B, S;

  if (Str.Length() > sizeof(Buffer))
  	throw Exception("AnsiString too large to save in INI file");
  S = Str.c_str();
  B = Buffer;
  while (*S != '\0')
  {
  	switch (*S)
     {
     	case 13:
        case 10:
           if ((*S == 13) && (S[1] == 10)) S++;
           else if ((*S == 10) && (S[1] == 13)) S++;
           *B = '\\';
           B++;
           *B = 'n';
           B++;
           S++;
           break;
        default:
      		*B = *S;
      		B++;
      		S++;
     }
  }
  *B = '\0';
  return String(Buffer);
}


String IniStrToStr(const String Str)
{
  char Buffer[4096];
  PChar B, S;

  if (Str.Length() > sizeof(Buffer))
  	throw Exception("String to read from an INI file");
  S = Str.c_str();
  B = Buffer;
  while (*S != '\0')
  {
    if ((S[0] == '\\') && (S[1] == 'n'))
    {
      *B = 13;
      B++;
      *B = 10;
      B++;
      S++;
      S++;
    }
    else
    {
      *B = *S;
      B++;
      S++;
    }
  }
  *B = '\0';
  return String(Buffer);
}

#define FuncoesBasicasH
#endif