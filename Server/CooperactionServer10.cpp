//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1997 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>                                
#pragma hdrstop
USERES("CooperactionServer10.res");
USEFORM("main.cpp", frmServer);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
          Application->Initialize();
          Application->Title = "CooperAction Server v1.0";
         Application->CreateForm(__classid(TfrmServer), &frmServer);
         Application->Run();
        }
        catch (Exception &exception)
        {
          Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
