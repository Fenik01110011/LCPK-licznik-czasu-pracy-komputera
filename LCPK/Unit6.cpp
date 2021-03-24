//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Unit1.h"
#include "Unit2.h"
#include "Unit5.h"


TForm6 *Form6;

//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void __fastcall TForm6::Button1Click(TObject *Sender)
{
        LCPKm fu6;

        pobrana_data = DateTimePicker1->Date.DateString();
        pobrana_godzina = DateTimePicker2->Time.TimeString();

        wybor_daty = fu6.sprawdzanie_daty(pobrana_data.c_str(), pobrana_godzina.c_str());

        ustawianie_daty();
}
//---------------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void TForm6::ustawianie_daty()
{
        LCPKm fu6;

        if(wybor_daty)
        {
                Form5->ktora_forma = 6;
                wybor_daty = false;
                Form5->Visible = true;
                return;
        }

        fu6.zapis_danych("Dane/Bufor_danych.txt", Form1->czas_roz, Form1->s[0], Form1->s[1], Form1->autozapis, "Ustawianie daty");

        bool poprawnosc_dane;
        bool poprawnosc_bufor_danych;

        plik6.open("Dane/Dane.txt", ios::in);
        if(plik6.good()) poprawnosc_dane = true;
        else poprawnosc_dane = false;
        plik6.close();
        plik6.clear();
        if(!(poprawnosc_dane))
        {
                bufor_komunikat = "Wyst¹pi³ problem z plikiem \"Dane.txt\"";
                ShowMessage(bufor_komunikat.c_str());
                return;
        }

        plik6.open("Dane/Bufor_danych.txt", ios::in);
        if(plik6.good()) poprawnosc_bufor_danych = true;
        else poprawnosc_bufor_danych = false;
        plik6.close();
        plik6.clear();
        if(!(poprawnosc_bufor_danych))
        {
                bufor_komunikat = "Wyst¹pi³ problem z plikiem \"Bufor_danych.txt\"";
                ShowMessage(bufor_komunikat.c_str());
                return;
        }

        ///////////////////////////////////////////////////////////////////

        double cws;
        int ilosc_wierszy[2];
        double czas_bufor[4];
        double calkowity_czas_b[2];
        bool znaleziono = false;
        int od_ktorego_zaczac;


        TStringList *dane = new TStringList;
        TStringList *bufor_danych = new TStringList;

        dane->LoadFromFile("Dane/Dane.txt");
        bufor_danych->LoadFromFile("Dane/Bufor_danych.txt");
        ilosc_wierszy[0] = dane->Count;
        ilosc_wierszy[1] = bufor_danych->Count;

        cws = fu6.data_na_sek_c(pobrana_data.c_str(), pobrana_godzina.c_str());

        if(ilosc_wierszy[1] != 8)
        {
                bufor_komunikat = "Plik \"Bufor_danych.txt\" jest uszkodzony przez co nie mo¿na ustawiæ daty";
                ShowMessage(bufor_komunikat.c_str());
                return;
        }

        czas_bufor[0] = atof(bufor_danych->Strings[1].c_str());
        czas_bufor[1] = atof(bufor_danych->Strings[2].c_str());
        if(cws > czas_bufor[0])
        {
                Form1->s[2] = 0;
                Form1->nadwyzkowy_czas = cws - czas_bufor[1];
                Form1->ustawienia[7] = fu6.int_na_str(cws).c_str();
                Form1->ustawianie_pokazywania();
                Form1->zapis_ustawien();
                Form6->Visible = false;
                return;
        }

        if(ilosc_wierszy[0] % 8 != 0)
        {
                bufor_komunikat = "Plik \"Dane.txt\" jest uszkodzony przez co nie mo¿na ustawiæ daty";
                ShowMessage(bufor_komunikat.c_str());
                return;
        }

        od_ktorego_zaczac = 1;

        for(od_ktorego_zaczac; od_ktorego_zaczac < ilosc_wierszy[0]; od_ktorego_zaczac += 800)
        {
                if(ilosc_wierszy[0] < od_ktorego_zaczac + 800) break;
                czas_bufor[0] = atof(dane->Strings[od_ktorego_zaczac + 800].c_str());
                if(czas_bufor[0] >= cws) break;
        }
        for(od_ktorego_zaczac; od_ktorego_zaczac < ilosc_wierszy[0]; od_ktorego_zaczac += 80)
        {
                if(ilosc_wierszy[0] < od_ktorego_zaczac + 80) break;
                czas_bufor[0] = atof(dane->Strings[od_ktorego_zaczac + 80].c_str());
                if(czas_bufor[0] >= cws) break;
        }

        for(int i = od_ktorego_zaczac; i < ilosc_wierszy[0]; i += 8)
        {
                czas_bufor[0] = atof(dane->Strings[i].c_str());
                if(czas_bufor[0] >= cws)
                {
                        czas_bufor[1] = atof(dane->Strings[i+1].c_str());
                        czas_bufor[2] = atof(dane->Strings[i+2].c_str());
                        czas_bufor[3] = atof(dane->Strings[i+3].c_str());

                        if(czas_bufor[1] <= cws)
                        {
                                if(czas_bufor[0] - czas_bufor[1] > 0)
                                {
                                        calkowity_czas_b[0] = czas_bufor[3] - ((czas_bufor[0] - cws) * (czas_bufor[2] / (czas_bufor[0] - czas_bufor[1])));
                                }
                                else calkowity_czas_b[0] = czas_bufor[3];
                        }
                        else calkowity_czas_b[0] = czas_bufor[3] - czas_bufor[2];

                        znaleziono = true;
                        break;
                }
        }

        if(!(znaleziono))
        {
                czas_bufor[0] = atof(bufor_danych->Strings[1].c_str());
                czas_bufor[1] = atof(bufor_danych->Strings[2].c_str());
                czas_bufor[2] = atof(bufor_danych->Strings[3].c_str());
                czas_bufor[3] = atof(bufor_danych->Strings[4].c_str());

                if(czas_bufor[1] <= cws)
                {
                        if(czas_bufor[0] - czas_bufor[1] > 0)
                        {
                                calkowity_czas_b[0] = czas_bufor[3] - ((czas_bufor[0] - cws) * (czas_bufor[2] / (czas_bufor[0] - czas_bufor[1])));
                        }
                        else calkowity_czas_b[0] = czas_bufor[3];
                }
                else calkowity_czas_b[0] = czas_bufor[3] - czas_bufor[2];

                znaleziono = true;
        }

        calkowity_czas_b[1] = atof(bufor_danych->Strings[4].c_str());

        fu6.sek_na_date(atof(Form1->ustawienia[7].c_str()));
        bufor_komunikat = "z " + fu6.mdzien + "." + fu6.mmiesiac + "." + fu6.mrok + "r. " + fu6.mgodz + ":" + fu6.mmin + ":" + fu6.msek + "\n";

        Form1->s[2] = calkowity_czas_b[1] - calkowity_czas_b[0];
        Form1->nadwyzkowy_czas = 0;
        Form1->ustawienia[7] = fu6.int_na_str(cws).c_str();
        Form1->ustawianie_pokazywania();
        Form1->zapis_ustawien();

        fu6.sek_na_date(atof(Form1->ustawienia[7].c_str()));
        bufor_komunikat = bufor_komunikat + "na " + fu6.mdzien + "." + fu6.mmiesiac + "." + fu6.mrok + "r. " + fu6.mgodz + ":" + fu6.mmin + ":" + fu6.msek;

        fu6.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 4, bufor_komunikat);

        Form6->Visible = false;
}

