//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Unit1.h"
#include "Unit2.h"
#include "Unit4.h"
#include "Unit7.h"

#include <fstream>

TForm3 *Form3;

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
        c = 0;
        w[0] = 0; w[1] = 0;
        d = 0;

}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormActivate(TObject *Sender)
{
        LCPKm m;
        m.zapis_danych("Dane/Bufor_danych.txt", Form1->czas_roz, Form1->s[0], Form1->s[1], Form1->autozapis, "Aktywacja okna aktywnoœci");
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
        if(w[0] == 1) {Lista_aktywnosci_plik->Free(); w[0] = 0;}
        if(w[1] == 1) {Dzialania_uzytkownika_plik->Free(); w[1] = 0;}
}
//---------------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void __fastcall TForm3::Wykazaktywnoci1Click(TObject *Sender)
{
        wyswietlenie_danych("Dane/Lista_aktywnosci.txt");
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Aktywno1Click(TObject *Sender)
{
        Form4->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Dziaaniauytkownika1Click(TObject *Sender)
{
        Form7->co_wybrac = 5;
        Form7->ShowModal();
}
//---------------------------------------------------------------------------




////////////////////////////////////////////////////////


void __fastcall TForm3::Zmianaczcionki1Click(TObject *Sender)
{
        if (FontDialog1->Execute())
        {
                //kroj
                Lista_aktywnosci->Font->Name = FontDialog1->Font->Name;

                //kolor
                Lista_aktywnosci->Font->Color = FontDialog1->Font->Color;

                //rozmiar
                Lista_aktywnosci->Font->Size = FontDialog1->Font->Size;

                //styl
                Lista_aktywnosci->Font->Style = FontDialog1->Font->Style;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Aktywno2Click(TObject *Sender)
{
        if(Application->MessageBox(
        "Czy na pewno usun¹æ historiê aktywnoœci?", "PotwierdŸ",
        MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
                Form7->co_wybrac = 1;
                Form7->ShowModal();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Dziaaniauytkownika2Click(TObject *Sender)
{
        if(Application->MessageBox(
        "Czy na pewno usun¹æ historiê dzia³añ u¿ytkownika?", "PotwierdŸ",
        MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
                Form7->co_wybrac = 2;
                Form7->ShowModal();
        }
}
//---------------------------------------------------------------------------



void __fastcall TForm3::Usucahistio1Click(TObject *Sender)
{
        if(Application->MessageBox(
        "Czy na pewno usun¹æ ca³¹ historiê", "PotwierdŸ",
        MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
                Form7->co_wybrac = 3;
                Form7->ShowModal();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Niezapisujtejaktywnoci1Click(TObject *Sender)
{
        LCPKm m;
        if(Niezapisujtejaktywnoci1->Checked == false)
        {
                Form7->co_wybrac = 4;
                Form7->ShowModal();
        }
        else
        {
                Form1->ustawienia[8] = "0";
                Form1->zapis_ustawien();
                m.zapis_danych("Dane/Bufor_danych.txt", Form1->czas_roz, Form1->s[0], Form1->s[1], Form1->autozapis, "Odznaczenie niezapisywania obecnej aktywnoœci");
                Niezapisujtejaktywnoci1->Checked = false;
        }
}
//---------------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void TForm3::wyswietlenie_danych(AnsiString nazwa_pliku)
{
        if(nazwa_pliku == "Dane/Lista_aktywnosci.txt") c = 1;
        else if(nazwa_pliku == "Dane/Dzialania_uzytkownika.txt") c = 2;
        else c = 0;

        d = 0;

        switch(c)
        {
                case 1:
                {
                        if(w[0] == 0)
                        {
                                plik3.open(nazwa_pliku.c_str(), std::ios::in);
                                if(plik3.good())
                                {
                                        int wiersze = 0;

                                        TStringList *bufor_plik = new TStringList;
                                        Lista_aktywnosci_plik = new TStringList;

                                        bufor_plik->LoadFromFile(nazwa_pliku);

                                        wiersze = bufor_plik->Count;

                                        if(wiersze == 0)
                                        {
                                                Lista_aktywnosci_plik->Append("");
                                                Lista_aktywnosci_plik->Append("Nie znaleziono ¿adnych wczeœniejszych aktywnoœci");
                                        }

                                        for(int i = wiersze; i >= 12; i -= 12)
                                        {
                                                i -= 12;
                                                for(int j = 0; j <= 11; j++)
                                                {
                                                        if(i >= 0) Lista_aktywnosci_plik->Add(bufor_plik->Strings[i]);
                                                        i++;
                                                }
                                        }
                                        delete bufor_plik;

                                        w[0] = 1;
                                }
                        }
                        if(w[0] == 1)
                        {
                                Form3->Lista_aktywnosci->Lines = Lista_aktywnosci_plik;
                                d = 1;
                        }
                        break;
                }
                case 2:
                {
                        if(w[1] == 0)
                        {
                                plik3.open(nazwa_pliku.c_str(), std::ios::in);
                                if(plik3.good())
                                {
                                        int wiersze = 0;
                                        int k = 4;

                                        TStringList *bufor_plik = new TStringList;
                                        Dzialania_uzytkownika_plik = new TStringList;

                                        bufor_plik->LoadFromFile(nazwa_pliku);

                                        wiersze = bufor_plik->Count;

                                        if(wiersze == 0)
                                        {
                                                Dzialania_uzytkownika_plik->Append("");
                                                Dzialania_uzytkownika_plik->Append("Nie zarejestrowano ¿adnych dzia³añ u¿ytkownika");
                                        }

                                        for(int i = wiersze -1 ; i >= 4; i -= k)
                                        {
                                                for(k = 4; k <= 7; k++)
                                                {
                                                        if(i - k < 0) break;
                                                        if(bufor_plik->Strings[i-k] == "--------------------------------------------------")
                                                                break;
                                                }

                                                i -= k;
                                                for(int j = 0; j < k; j++)
                                                {
                                                        i++;
                                                        if(i >= 0) Dzialania_uzytkownika_plik->Add(bufor_plik->Strings[i]);
                                                }
                                        }
                                        delete bufor_plik;

                                        w[1] = 1;
                                }
                        }
                        if(w[1] == 1)
                        {
                                Form3->Lista_aktywnosci->Lines = Dzialania_uzytkownika_plik;
                                d = 1;
                        }
                        break;
                }

                default: d = 0;
        }

        plik3.close();
        plik3.clear();

        if(d == 0)
        {
                AnsiString tresc_bledu;

                switch(c)
                {
                        case 0: tresc_bledu = "B³¹d aplikacji. Nie mo¿na wyœwietliæ danych";
                        break;
                        case 1: tresc_bledu = "Wyst¹pi³ b³¹d przy odczycie pliku \"Lista_aktywnosci.txt\"";
                        break;
                        case 2: tresc_bledu = "Wyst¹pi³ b³¹d przy odczycie pliku \"Dzialania_uzytkownika.txt\"";
                        break;
                        default: tresc_bledu = "B³¹d aplikacji. Nie mo¿na wyœwietliæ danych";
                }

                Form3->Lista_aktywnosci->Lines->Clear();
                Form3->Lista_aktywnosci->Lines->Append(tresc_bledu);
        }
}



bool TForm3::dane_na_liste_aktywnosci()
{
        LCPKm m;
        int ilosc_wierszy;
        string fbufor[8];
        double dczas;
        int iczas;
        string tbufor[5];
        TStringList *dane = new TStringList;

        if(m.czy_plik_istnieje("Dane/Dane.txt"))
        {
                dane->LoadFromFile("Dane/Dane.txt");
                ilosc_wierszy = dane->Count;

                if(ilosc_wierszy % 8 != 0) return false;
        }
        else return false;

        DeleteFile("Dane/Lista_aktywnosci.txt");

        m.tworzenie_pliku("Dane/Lista_aktywnosci.txt");

        plik3.open("Dane/Lista_aktywnosci.txt", ios::out | ios::app);

        for(int i = 0; i < (ilosc_wierszy / 8); i++)
        {
                for(int j = 0; j <= 7; j++)
                {
                        fbufor[j] = dane->Strings[j + i * 8].c_str();
                }

                if(fbufor[7] != "------------------------------") return false;

                dczas = atof(fbufor[2].c_str());
                m.sek_na_date(dczas);
                tbufor[0] = m.mdzien+"."+m.mmiesiac+"."+m.mrok+"r. "+m.mgodz+":"+m.mmin+":"+m.msek;

                dczas = atof(fbufor[1].c_str());
                m.sek_na_date(dczas);
                tbufor[1] = m.mdzien+"."+m.mmiesiac+"."+m.mrok+"r. "+m.mgodz+":"+m.mmin+":"+m.msek;

                iczas = atoi(fbufor[3].c_str());
                tbufor[2] = m.sek_na_czas(iczas);

                iczas = atoi(fbufor[4].c_str());
                tbufor[3] = m.sek_na_czas(iczas);

                iczas = atoi(fbufor[5].c_str());
                iczas /= 60;
                if(iczas == 60) tbufor[4] = "1 godzine";
                else tbufor[4] = m.int_na_str(iczas)+" min";

                plik3<<endl<<fbufor[0]<<endl;
                plik3<<endl;
                plik3<<"Czas aktywnoœci"<<endl;
                plik3<<"   od "<<tbufor[0]<<endl;
                plik3<<"   do "<<tbufor[1]<<endl;
                plik3<<"Czas dzia³ania programu: "<<tbufor[2]<<endl;
                plik3<<"Ca³kowity czas: "<<tbufor[3]<<endl;
                plik3<<"Autozapis: co "<<tbufor[4]<<endl;
                plik3<<"Zapisano poprzez: "<<fbufor[6]<<endl;
                plik3<<endl;
                plik3<<"--------------------------------------------------"<<endl;

        }

        plik3.close();
        plik3.clear();

        delete dane;

        return true;
}
