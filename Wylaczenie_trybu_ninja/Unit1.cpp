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

                ShowMessage("Zmiana ustawie� zako�czy�a si� pomy�lnie. Teraz program \"LCPK.exe\" b�dzie minimalizowa� si� do treya");

        }
        else
        {
                ShowMessage("Wyst�pi� b��d przy zmianie ustawie� programu \"LCPK.exe\". Mo�liwa jest zmiana ustawie� r�cznie poprzez zmiane danych w pliku \"Dane\\Ustawienia.txt\". Nale�y zamieni� warto�ci 3 linii z \"0\" na \"1\" oraz 4 linii z \"1\" na \"0\" i zapisa� plik. Mo�na tak�e usun�� plik \"Dane\\Ustawienia.txt\" co spowoduje przywr�cenie ustawie� domy�lnych. Folder jak i pliki w nim mog� by� ukryte, dlatego w celu ich ukazania nale�y zmieni� ustawienia widoczno�ci folder�w i plik�w na pokazywanie plik�w ukrytych i systemowych. Po dokonaniu zmiany ustawie� program \"LCPK.exe\" powinien minimalizowa� si� do treya.");
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
