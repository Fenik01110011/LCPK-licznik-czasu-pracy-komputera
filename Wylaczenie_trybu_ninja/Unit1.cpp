//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include <iostream>
#include <fstream>

using namespace std;

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        fstream plik;

        bool czy_wszystko_gra = true;
        string ustawienia[9];

        plik.open("Dane/Ustawienia.txt", std::ios::in);

        if(plik.good()==true)
        {
                for(int i=0; i<=8; i++)
                {
                        if(plik.eof()) {czy_wszystko_gra = false; break;}
                        plik>>ustawienia[i];
                }
                plik.close();
                plik.clear();
        }
        else czy_wszystko_gra = false;

        if(czy_wszystko_gra == true)
        {
                plik.open("Dane/Ustawienia.txt", ios::out);

                plik<<ustawienia[0]<<endl;
                plik<<ustawienia[1]<<endl;
                plik<<"1"<<endl;
                plik<<"0"<<endl;
                plik<<ustawienia[4]<<endl;
                plik<<ustawienia[5]<<endl;
                plik<<ustawienia[6]<<endl;
                plik<<ustawienia[7]<<endl;
                plik<<ustawienia[8];

                plik.close();
                plik.clear();

                ShowMessage("Zmiana ustawieñ zakoñczy³a siê pomyœlnie. Teraz program \"LCPK.exe\" bêdzie minimalizowaæ siê do treya");

        }
        else
        {
                ShowMessage("Wyst¹pi³ b³¹d przy zmianie ustawieñ programu \"LCPK.exe\". Mo¿liwa jest zmiana ustawieñ rêcznie poprzez zmiane danych w pliku \"Dane\\Ustawienia.txt\". Nale¿y zamieniæ wartoœci 3 linii z \"0\" na \"1\" oraz 4 linii z \"1\" na \"0\" i zapisaæ plik. Mo¿na tak¿e usun¹æ plik \"Dane\\Ustawienia.txt\" co spowoduje przywrócenie ustawieñ domyœlnych. Folder jak i pliki w nim mog¹ byæ ukryte, dlatego w celu ich ukazania nale¿y zmieniæ ustawienia widocznoœci folderów i plików na pokazywanie plików ukrytych i systemowych. Po dokonaniu zmiany ustawieñ program \"LCPK.exe\" powinien minimalizowaæ siê do treya.");
        }
        Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
        Application->Terminate();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
        Application->Terminate();
}
//---------------------------------------------------------------------------
