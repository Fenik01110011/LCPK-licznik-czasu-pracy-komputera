//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit8.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Unit1.h"
#include "Unit2.h"

TForm8 *Form8;

//---------------------------------------------------------------------------
__fastcall TForm8::TForm8(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm8::FormActivate(TObject *Sender)
{
        LCPKm fu8;

        Edit1->Text = "";
        Edit2->Text = "";
        Edit3->Text = "";
        fu8.zapis_danych("Dane/Bufor_danych.txt", Form1->czas_roz, Form1->s[0], Form1->s[1], Form1->autozapis, "Aktywacja okna zmiany has�a");
}
//---------------------------------------------------------------------------


void __fastcall TForm8::Button1Click(TObject *Sender)
{
        LCPKm fu8;

        if(Form1->nieprawidlowe_podania_hasla >= 5)
        {
                ShowMessage("Odmowa dost�pu. Przekroczono limit b��dnych wprowadze� has�a");
                return;
        }

        if(!(sprawdzanie_poprawnosci_hasla("Dane/Ustawienia2.txt")))
        {
                Edit1->Text = "";
                ShowMessage("Podane has�o nie jest zgodne z obecnym");
                Form1->nieprawidlowe_podania_hasla ++;
                return;
        }
        else Form1->nieprawidlowe_podania_hasla = 0;


        if(Edit2->Text != Edit3->Text)
        {
                Edit2->Text = "";
                Edit3->Text = "";
                ShowMessage("Niepoprawne powt�rzenie nowego has�a");
                return;
        }

        string bufor1;
        int d;

        bufor1 = (Edit2->Text).c_str();
        d = bufor1.size();

        if(d == 0) bufor1 = "brak hasla axc0wa896321c4b8";
        if((d > 0) && (d < 3))
        {
                ShowMessage("Has�o musi zawiera� przynajmniej 3 znaki");
                return;
        }

        if(d > 300)
        {
                Edit2->Text = "";
                Edit3->Text = "";
                ShowMessage("Has�o mo�e mie� maksymalnie 300 znak�w");
                return;
        }

        plik8.open("Dane/Ustawienia2.txt", ios::out);
        plik8 << fu8.szyfrowanie_hasla("de83jflxho3p95hksdu3i2878952hfdfksh", bufor1) << endl;
        plik8.close();
        plik8.clear();

        bufor1 += "sfacvsdsd31353fsd";

        plik8.open("Dane/Haslo.txt", ios::out);
        plik8 << fu8.losowe_haslo("de83jflxho3p95hksdu3i2878952hfdfksh", bufor1) << endl;
        plik8.close();
        plik8.clear();

        Form8->Close();

        fu8.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "Zmiana has�a");

        ShowMessage("Has�o zosta�o pomy�lnie zmienione");
}
//---------------------------------------------------------------------------


bool TForm8::sprawdzanie_poprawnosci_hasla(AnsiString nazwa_pliku)
{
        LCPKm fu8;

        HANDLE hplik;

        if(!(fu8.czy_plik_istnieje("Dane/Ustawienia2.txt")))
        {
                hplik = CreateFile("Dane/Ustawienia2.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN, NULL);
                CloseHandle(hplik);
                plik8.open("Dane/Ustawienia2.txt", ios::out);
                plik8 << fu8.szyfrowanie_hasla("de83jflxho3p95hksdu3i2878952hfdfksh", "brak hasla axc0wa896321c4b8") << endl;
                plik8.close();
                plik8.clear();
        }

        if(!(fu8.czy_plik_istnieje("Dane/Haslo.txt")))
        {
                hplik = CreateFile("Dane/Haslo.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN, NULL);
                CloseHandle(hplik);
                plik8.open("Dane/Haslo.txt", ios::out);
                plik8 << fu8.losowe_haslo("de83jflxho3p95hksdu3i2878952hfdfksh", "brak hasla axc0wa896321c4b8") << endl;
                plik8.close();
                plik8.clear();
        }

        string bufor1;
        int d;
        string bufor2;

        bufor1 = (Edit1->Text).c_str();
        d = bufor1.size();

        if((d < 0) || ((d > 0) && (d < 3)) || (d > 300)) return false;
        if(d == 0) bufor1 = "brak hasla axc0wa896321c4b8";

        plik8.open(nazwa_pliku.c_str(), ios::in);

        if((!(plik8.good())) || (plik8.eof()))
        {
                plik8.close();
                plik8.clear();
                return false;
        }

        getline(plik8, bufor2);

        plik8.close();
        plik8.clear();

        return fu8.zgodnosc_hasla_z_zaszyfrowanym_haslem("de83jflxho3p95hksdu3i2878952hfdfksh", bufor2, bufor1.c_str());
}

