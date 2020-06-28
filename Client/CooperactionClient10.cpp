//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("CooperactionClient10.res");
USEFORM("TfrmPrincipal.cpp", frmPrincipal);
USEFORM("ObjProp.cpp", OProp);
USEFORM("Sobre.cpp", About);
USEFORM("frmConn.cpp", frmConnProp);
USEFORM("ModelProp.cpp", MProp);
USEFORM("ConnectDialog.cpp", frmConnect);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->Title = "CooperAction Client v1.0";
         Application->CreateForm(__classid(TfrmPrincipal), &frmPrincipal);
         Application->CreateForm(__classid(TOProp), &OProp);
         Application->CreateForm(__classid(TAbout), &About);
         Application->CreateForm(__classid(TfrmConnProp), &frmConnProp);
         Application->CreateForm(__classid(TMProp), &MProp);
         Application->CreateForm(__classid(TfrmConnect), &frmConnect);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
