//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit5.h"

#include <fstream>

TForm4 *Form4;

//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
        ilosc_wierszy = 0;
        znaleziono[0] = 0; znaleziono[1] = 0;
        nr_wiersza_b[0] = 0; nr_wiersza_b[1] = 0;
        gdzie_znaleziono[0] = 0; gdzie_znaleziono[1] = 0;
        ilosc_aktywnosci = 0;
        czas_bufor[0] = 0; czas_bufor[1] = 0; czas_bufor[2] = 0; czas_bufor[3] = 0;
        czas_poczatkowy = 0; //kiedy nastapila pierwsza aktywnosc w tym przedziale czasowym
        czas_koncowy = 0; //kiedy nastapila ostatnia aktywnosc w tym przedziale czasowym
        calkowity_czas_b[0] = 0; calkowity_czas_b[1] = 0;
}
//---------------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void __fastcall TForm4::Button1Click(TObject *Sender)
{
        LCPKm fu4;

        pobrana_data[0] = DateTimePicker1->Date.DateString();
        pobrana_godzina[0] = DateTimePicker2->Time.TimeString();
        pobrana_data[1] = DateTimePicker3->Date.DateString();
        pobrana_godzina[1] = DateTimePicker4->Time.TimeString();

        wybor_daty[0] = fu4.sprawdzanie_daty(pobrana_data[0].c_str(), pobrana_godzina[0].c_str());
        wybor_daty[1] = fu4.sprawdzanie_daty(pobrana_data[1].c_str(), pobrana_godzina[1].c_str());

        wyswietlanie_aktywnosci_w_przedziale();
}
//---------------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int TForm4::sprawdzanie_aktywnosci_w_przedziale(AnsiString data1, AnsiString godzina1, AnsiString data2, AnsiString godzina2)
{
        //zwraca 0 jesli wszystko posz³o zgodnie z planem
        //zwraca 1 jesli nie mozna bylo otworzyc pliku "Dane/Dane.txt"
        //zwraca 2 jesli nie mozna bylo otworzyc pliku "Dane/Bufor_danych.txt"
        //zwraca 3 jesli nie mozna bylo otworzyc pliku "Dane/Lista_aktywnosci.txt"
        //zwraca 4 jesli podany zakres czasowy jest pozniejszy niz obecna data
        //zwraca 5 jesli podany zakres czasowy jest wczesniejszy niz pierwsza zarejestrowana aktywnosc
        //zwraca 6 jesli podany zakres czasowy nie zawiera zadnych aktywnosci ale jest pomiedzy pierwsza, a ostatnia zarejestrowana aktywnoscia

        LCPKm fu4;

        fu4.zapis_danych("Dane/Bufor_danych.txt", Form1->czas_roz, Form1->s[0], Form1->s[1], Form1->autozapis, "Sprawdzanie aktywnoœci w przedziale");

        ilosc_wierszy = 0;
        znaleziono[0] = 0; znaleziono[1] = 0;
        nr_wiersza_b[0] = 0; nr_wiersza_b[1] = 0;
        gdzie_znaleziono[0] = 0; gdzie_znaleziono[1] = 0;
        ilosc_aktywnosci = 0;
        czas_bufor[0] = 0; czas_bufor[1] = 0; czas_bufor[2] = 0; czas_bufor[3] = 0;
        czas_poczatkowy = 0; //kiedy nastapila pierwsza aktywnosc w tym przedziale czasowym
        czas_koncowy = 0; //kiedy nastapila ostatnia aktywnosc w tym przedziale czasowym
        calkowity_czas_b[0] = 0; calkowity_czas_b[1] = 0;

        TStringList *dane = new TStringList;
        TStringList *bufor_danych = new TStringList;

        cws[0] = fu4.data_na_sek_c(data1.c_str(), godzina1.c_str());
        cws[1] = fu4.data_na_sek_c(data2.c_str(), godzina2.c_str());

        if(cws[0] > cws[1])
        {
                double cws_zamiana_b;
                AnsiString pobrana_data_b;
                AnsiString pobrana_godzina_b;

                cws_zamiana_b = cws[0];
                cws[0] = cws[1];
                cws[1] = cws_zamiana_b;

                pobrana_data_b = pobrana_data[0];
                pobrana_godzina_b = pobrana_godzina[0];
                pobrana_data[0] = pobrana_data[1];
                pobrana_godzina[0] = pobrana_godzina[1];
                pobrana_data[1] = pobrana_data_b;
                pobrana_godzina[1] = pobrana_godzina_b;
        }

        plik4.open("Dane/Dane.txt", ios::in);
        if(plik4.good()) poprawnosc_dane = true;
        else poprawnosc_dane = false;
        plik4.close();
        plik4.clear();
        if(!(poprawnosc_dane)) return 1;

        plik4.open("Dane/Bufor_danych.txt", ios::in);
        if(plik4.good()) poprawnosc_bufor_danych = true;
        else poprawnosc_bufor_danych = false;
        plik4.close();
        plik4.clear();
        if(!(poprawnosc_bufor_danych)) return 2;

        plik4.open("Dane/Lista_aktywnosci.txt", ios::in);
        if(plik4.good()) poprawnosc_lista_aktywnosci = true;
        else poprawnosc_lista_aktywnosci = false;
        plik4.close();
        plik4.clear();
        if(!(poprawnosc_lista_aktywnosci)) return 3;

        if(poprawnosc_dane)
        {
                dane->LoadFromFile("Dane/Dane.txt");
                ilosc_wierszy = dane->Count;

                int od_ktorego_zaczac = 1;

                for(od_ktorego_zaczac; od_ktorego_zaczac < ilosc_wierszy; od_ktorego_zaczac += 800)
                {
                        if(ilosc_wierszy < od_ktorego_zaczac + 800) break;
                        czas_bufor[0] = atof(dane->Strings[od_ktorego_zaczac + 800].c_str());
                        if(czas_bufor[0] >= cws[0]) break;
                }
                for(od_ktorego_zaczac; od_ktorego_zaczac < ilosc_wierszy; od_ktorego_zaczac += 80)
                {
                        if(ilosc_wierszy < od_ktorego_zaczac + 80) break;
                        czas_bufor[0] = atof(dane->Strings[od_ktorego_zaczac + 80].c_str());
                        if(czas_bufor[0] >= cws[0]) break;
                }

                for(int i = od_ktorego_zaczac; i < ilosc_wierszy; i += 8)
                {
                        czas_bufor[0] = atof(dane->Strings[i].c_str());
                        if(czas_bufor[0] >= cws[0])
                        {
                                czas_bufor[1] = atof(dane->Strings[i+1].c_str());
                                czas_bufor[2] = atof(dane->Strings[i+2].c_str());
                                czas_bufor[3] = atof(dane->Strings[i+3].c_str());

                                if(czas_bufor[1] <= cws[0])
                                {
                                        czas_poczatkowy = cws[0];
                                        if(czas_bufor[0] - czas_bufor[1] > 0)
                                        {
                                                calkowity_czas_b[0] = czas_bufor[3] - ((czas_bufor[0] - czas_poczatkowy) * (czas_bufor[2] / (czas_bufor[0] - czas_bufor[1])));
                                        }
                                        else calkowity_czas_b[0] = czas_bufor[3];
                                        gdzie_znaleziono[0] = 2;
                                }
                                else
                                {
                                        czas_poczatkowy = czas_bufor[1];
                                        calkowity_czas_b[0] = czas_bufor[3] - czas_bufor[2];
                                        gdzie_znaleziono[0] = 1;
                                }

                                nr_wiersza_b[0] = i - 1;
                                znaleziono[0] = 1;
                                break;
                        }
                }
        }

        if(znaleziono[0] == 0)
        {
                if(poprawnosc_bufor_danych)
                {
                        bufor_danych->LoadFromFile("Dane/Bufor_danych.txt");
                        czas_bufor[0] = atof(bufor_danych->Strings[1].c_str());

                        if(czas_bufor[0] < cws[0]) return 4;

                        czas_bufor[1] = atof(bufor_danych->Strings[2].c_str());
                        czas_bufor[2] = atof(bufor_danych->Strings[3].c_str());
                        czas_bufor[3] = atof(bufor_danych->Strings[4].c_str());

                        if(czas_bufor[1] <= cws[0])
                        {
                                czas_poczatkowy = cws[0];
                                if(czas_bufor[0] - czas_bufor[1] > 0)
                                {
                                        calkowity_czas_b[0] = czas_bufor[3] - ((czas_bufor[0] - czas_poczatkowy) * (czas_bufor[2] / (czas_bufor[0] - czas_bufor[1])));
                                }
                                else calkowity_czas_b[0] = czas_bufor[3];
                                gdzie_znaleziono[0] = 2;
                        }
                        else
                        {
                                czas_poczatkowy = czas_bufor[1];
                                calkowity_czas_b[0] = czas_bufor[3] - czas_bufor[2];
                                gdzie_znaleziono[0] = 1;
                        }
                        nr_wiersza_b[0] = ilosc_wierszy;
                        znaleziono[0] = 2;
                }
        }

        if(znaleziono[0] == 1)
        {
                for(int i = nr_wiersza_b[0] + 1; i < ilosc_wierszy; i += 8)
                {
                        czas_bufor[0] = atof(dane->Strings[i].c_str());
                        if(czas_bufor[0] >= cws[1])
                        {
                                czas_bufor[1] = atof(dane->Strings[i+1].c_str());
                                czas_bufor[2] = atof(dane->Strings[i+2].c_str());
                                czas_bufor[3] = atof(dane->Strings[i+3].c_str());

                                if(czas_bufor[1] <= cws[1])
                                {
                                        czas_koncowy = cws[1];
                                        if(czas_bufor[0] - czas_bufor[1] > 0)
                                        {
                                                calkowity_czas_b[1] = czas_bufor[3] - ((czas_bufor[0] - czas_koncowy) * (czas_bufor[2] / (czas_bufor[0] - czas_bufor[1])));
                                        }
                                        else calkowity_czas_b[1] = czas_bufor[3];
                                        gdzie_znaleziono[1] = 2;
                                }
                                else
                                {
                                        if(i >= 9) czas_koncowy = atof(dane->Strings[i-7].c_str());
                                        else return 5;
                                        calkowity_czas_b[1] = czas_bufor[3] - czas_bufor[2];
                                        gdzie_znaleziono[1] = 1;
                                }

                                nr_wiersza_b[1] = i - 1;
                                znaleziono[1] = 1;
                                break;
                        }
                }
        }

        if((znaleziono[0] == 2)||(znaleziono[1] == 0))
        {
                        bufor_danych->LoadFromFile("Dane/Bufor_danych.txt");
                        czas_bufor[0] = atof(bufor_danych->Strings[1].c_str());
                        czas_bufor[1] = atof(bufor_danych->Strings[2].c_str());
                        czas_bufor[2] = atof(bufor_danych->Strings[3].c_str());
                        czas_bufor[3] = atof(bufor_danych->Strings[4].c_str());

                        if(czas_bufor[0] >= cws[1])
                        {

                                if(czas_bufor[1] <= cws[1])
                                {
                                        czas_koncowy = cws[1];
                                        if(czas_bufor[0] - czas_bufor[1] > 0)
                                        {
                                                calkowity_czas_b[1] = czas_bufor[3] - ((czas_bufor[0] - czas_koncowy) * (czas_bufor[2] / (czas_bufor[0] - czas_bufor[1])));
                                        }
                                        else calkowity_czas_b[1] = czas_bufor[3];
                                        gdzie_znaleziono[1] = 2;
                                }
                                else
                                {
                                        if(ilosc_wierszy >= 8) czas_koncowy = atof(dane->Strings[ilosc_wierszy - 7].c_str());
                                        else return 5;
                                        calkowity_czas_b[1] = czas_bufor[3] - czas_bufor[2];
                                        gdzie_znaleziono[1] = 1;
                                }

                                nr_wiersza_b[1] = ilosc_wierszy;
                                znaleziono[1] = 2;
                        }
                        else
                        {
                                calkowity_czas_b[1] = czas_bufor[3];
                                gdzie_znaleziono[1] = 2;
                                nr_wiersza_b[1] = ilosc_wierszy;
                                znaleziono[1] = 3;
                        }
        }

        //////////////////

        ilosc_aktywnosci = ((nr_wiersza_b[1] - nr_wiersza_b[0]) / 8) + 1;
        if(gdzie_znaleziono[1] == 1) ilosc_aktywnosci --;

        if(ilosc_aktywnosci <= 0) return 6;

        //////////////////

        calkowity_czas_r = calkowity_czas_b[1] - calkowity_czas_b[0];

        //////////////////

        najdluzszy_czas = 0;

        int do_ktorego_wiersza = nr_wiersza_b[1] + 3;
        if(gdzie_znaleziono[1] == 1) do_ktorego_wiersza -= 8;
        bool czy_bufor = false;
        bool czy_nc_bufor = false;
        if(do_ktorego_wiersza > ilosc_wierszy) { czy_bufor = true; do_ktorego_wiersza -= 8; }
        int bufor_nc = 0;
        int nrw_nc = 1;
        int ktoryzkolei = 0;
        AnsiString bufor_as[2];

        for(int i = nr_wiersza_b[0] + 3; i <= do_ktorego_wiersza; i += 8)
        {
                bufor_nc = atoi(dane->Strings[i].c_str());
                if(najdluzszy_czas < bufor_nc)
                {
                        najdluzszy_czas = bufor_nc;
                        nrw_nc = i - 3;
                }
        }

        double dczas[2] = {0,0};
        string tbufor[3];

        if(nrw_nc + 2 < ilosc_wierszy)
        {
                dczas[0] = atof(dane->Strings[nrw_nc + 2].c_str());
                dczas[1] = atof(dane->Strings[nrw_nc + 1].c_str());
        }
        
        if(czy_bufor)
        {
                bufor_nc = atoi(bufor_danych->Strings[3].c_str());
                if(najdluzszy_czas <= bufor_nc)
                {
                        najdluzszy_czas = bufor_nc;
                        nrw_nc = ilosc_wierszy;
                        dczas[0] = atof(bufor_danych->Strings[2].c_str());
                        dczas[1] = atof(bufor_danych->Strings[1].c_str());
                        czy_nc_bufor = true;
                }
        }

        fu4.sek_na_date(dczas[0]);
        tbufor[0] = fu4.mdzien+"."+fu4.mmiesiac+"."+fu4.mrok+"r. "+fu4.mgodz+":"+fu4.mmin+":"+fu4.msek;

        fu4.sek_na_date(dczas[1]);
        tbufor[1] = fu4.mdzien+"."+fu4.mmiesiac+"."+fu4.mrok+"r. "+fu4.mgodz+":"+fu4.mmin+":"+fu4.msek;

        tbufor[2] = fu4.sek_na_czas(najdluzszy_czas);

        najdluzszy_czas_czas = tbufor[2].c_str();
        if(czy_nc_bufor) najdluzszy_czas_czas += " (obecna aktywnoœæ)";
        else
        {
                ktoryzkolei = ((nrw_nc - nr_wiersza_b[0]) / 8) + 1;
                bufor_as[0] = fu4.int_na_str(ktoryzkolei).c_str();
                bufor_as[1] = " (aktywnoœæ nr " + bufor_as[0] + ")";
                najdluzszy_czas_czas += bufor_as[1];
        }

        bufor_as[0] = tbufor[0].c_str();
        bufor_as[1] = tbufor[1].c_str();

        najdluzszy_czas_data[0] = "od " + bufor_as[0];
        najdluzszy_czas_data[1] = "do " + bufor_as[1];

        //////////////////

        delete dane;
        delete bufor_danych;

        return 0;
}


////////////////////////////////////////////////////////////////////////


void TForm4::wyswietlanie_aktywnosci_w_przedziale()
{
        LCPKm fu4;

        if(wybor_daty[0])
        {
                Form5->ktora_forma = 4;
                wybor_daty[0] = false;
                wynik_wawp = 1;
                Form5->Visible = true;
                return;
        }
        else if(wybor_daty[1])
        {
                Form5->ktora_forma = 4;
                wybor_daty[1] = false;
                wynik_wawp = 2;
                Form5->Visible = true;
                return;
        }

        rezultat = sprawdzanie_aktywnosci_w_przedziale(pobrana_data[0], pobrana_godzina[0], pobrana_data[1], pobrana_godzina[1]);

        Form3->Lista_aktywnosci->Lines->Clear();

        int wiersze_b;
        int bufor_i;
        int bufor_ia;
        AnsiString bufor_as;
        AnsiString bufor_poczatek[7];
        int b_obliczenia[2];
        TStringList *bufor_calosc = new TStringList;
        TStringList *lista_aktywnosci = new TStringList;
        if(fu4.czy_plik_istnieje("Dane/Lista_aktywnosci.txt")) lista_aktywnosci->LoadFromFile("Dane/Lista_aktywnosci.txt");
        wiersze_b = lista_aktywnosci->Count;

        if(ilosc_wierszy / 8 != wiersze_b / 12)
        {
                Form3->Lista_aktywnosci->Lines->Append("Brak zgodnoœci pliku \"Lista_aktywnosci.txt\" z plikiem \"Dane.txt\"");
                return;
        }

        ////////////////////////////////////////////////////////////

        string fbufor[8];
        double dczas;
        int iczas;
        string tbufor[5];
        string bd;
        string bd_wyjscie[12];

        plik4.open("Dane/Bufor_danych.txt", ios::in);

        if(plik4.good()==true)
        {
                for(int i=0; i<8; i++)
                {
                        if(plik4.eof())  break;
                        getline(plik4, fbufor[i]);
                }
        }
        plik4.close();
        plik4.clear();

        if(!(fbufor[7] == "------------------------------"))
        {
                Form3->Lista_aktywnosci->Lines->Append("Coœ nie pyk³o ;b");
                return;
        }
        else if((rezultat == 0) || (rezultat == 4) || (rezultat == 5))
        {
                dczas = atof(fbufor[2].c_str());
                fu4.sek_na_date(dczas);
                tbufor[0] = fu4.mdzien+"."+fu4.mmiesiac+"."+fu4.mrok+"r. "+fu4.mgodz+":"+fu4.mmin+":"+fu4.msek;

                dczas = atof(fbufor[1].c_str());
                fu4.sek_na_date(dczas);
                tbufor[1] = fu4.mdzien+"."+fu4.mmiesiac+"."+fu4.mrok+"r. "+fu4.mgodz+":"+fu4.mmin+":"+fu4.msek;

                iczas = atoi(fbufor[3].c_str());
                tbufor[2] = fu4.sek_na_czas(iczas);

                iczas = atoi(fbufor[4].c_str());
                tbufor[3] = fu4.sek_na_czas(iczas);

                iczas = atoi(fbufor[5].c_str());
                iczas /= 60;
                if(iczas == 60) tbufor[4] = "1 godzine";
                else tbufor[4] = fu4.int_na_str(iczas)+" min";


                bd_wyjscie[0] = "";
                bd_wyjscie[1] = "Obecna aktywnoœæ";
                bd_wyjscie[2] = "";
                bd_wyjscie[3] = "Czas aktywnoœci";
                bd_wyjscie[4] = "   od " + tbufor[0];
                bd_wyjscie[5] = "   do " + tbufor[1] + " + (bie¿¹ca aktywnoœæ)";
                bd_wyjscie[6] = "Czas dzia³ania programu: " + tbufor[2] + " +";
                bd_wyjscie[7] = "Ca³kowity czas: " + tbufor[3] + " +";
                bd_wyjscie[8] = "Autozapis: co " + tbufor[4];
                bd_wyjscie[9] = "Zapisano poprzez: " + fbufor[6];
                bd_wyjscie[10] = "";
                bd_wyjscie[11] = "--------------------------------------------------";
        }

        ////////////////////////////////////////////////////////////

        bufor_poczatek[0] = "";
        bufor_poczatek[1] = "Przedzia³:";
        bufor_poczatek[2] = "od " + pobrana_data[0] + " " + pobrana_godzina[0];
        bufor_poczatek[3] = "do " + pobrana_data[1] + " " + pobrana_godzina[1];
        bufor_poczatek[4] = "";
        bufor_poczatek[5] = "-----------------------------------------------------------------";
        bufor_poczatek[6] = "";

        ////////////////////////////////////////////////////////////
        switch(rezultat)
        {
                case 1: bufor_calosc->Append("Wyst¹pi³ problem przy odczycie pliku \"Dane.txt\"");
                break;
                case 2: bufor_calosc->Append("Wyst¹pi³ problem przy odczycie pliku \"Bufor_danych.txt\"");
                break;
                case 3: bufor_calosc->Append("Wyst¹pi³ problem przy odczycie pliku \"Lista_aktywnosci.txt\"");
                break;
                case 4:
                {
                        for(int i = 0; i < 7; i++) bufor_calosc->Append(bufor_poczatek[i]);

                        bufor_calosc->Append("Podany przedzia³ czasowy jest póŸniejszy od obecnej aktywnoœci");
                        bufor_calosc->Append("");
                        bufor_calosc->Append("-----------------------------------------------------------------");

                        for(int i = 0; i <= 11; i++)
                        {
                                bufor_calosc->Append(bd_wyjscie[i].c_str());
                        }

                        bufor_calosc->Append("");
                        bufor_calosc->Append("Wczeœniejsza aktywnoœæ:");

                        if(wiersze_b >= 12)
                        {
                                for(int i = wiersze_b - 12; i < wiersze_b; i++)
                                {
                                        bufor_calosc->Append(lista_aktywnosci->Strings[i]);
                                }
                        }
                        else
                        {
                                bufor_calosc->Append("");
                                bufor_calosc->Append("Brak wczeœniejszych aktywnoœci");
                        }

                }
                break;
                case 5:
                {
                        for(int i = 0; i < 7; i++) bufor_calosc->Append(bufor_poczatek[i]);

                        bufor_calosc->Append("Podany przedzia³ czasowy jest wczeœniejszy od pierwszej");
                        bufor_calosc->Append(" zarejestrowanej aktywnoœci");
                        bufor_calosc->Append("");
                        bufor_calosc->Append("-----------------------------------------------------------------");
                        bufor_calosc->Append("");
                        bufor_calosc->Append("Najbli¿sza póŸniejsza aktywnoœæ:");

                        if(wiersze_b >= 12)
                        {
                                for(int i = 0; i <= 11; i++)
                                {
                                        bufor_calosc->Append(lista_aktywnosci->Strings[i]);
                                }
                        }
                        else
                        {
                                for(int i = 0; i <= 11; i++)
                                {
                                        bufor_calosc->Append(bd_wyjscie[i].c_str());
                                }
                        }
                }
                break;
                case 6:
                {
                        for(int i = 0; i < 7; i++) bufor_calosc->Append(bufor_poczatek[i]);

                        bufor_calosc->Append("W podanym przedziale nie zarejestrowano ¿adnych aktywnoœci");
                        bufor_calosc->Append("");
                        bufor_calosc->Append("-----------------------------------------------------------------");
                        bufor_calosc->Append("");
                        bufor_calosc->Append("Najbli¿sze aktywnoœci:");

                        bufor_i = ((nr_wiersza_b[1] - 8) / 8) * 12;
                        for(int i = bufor_i; i <= bufor_i + 11; i++)
                        {
                                bufor_calosc->Append(lista_aktywnosci->Strings[i]);
                        }

                        if(nr_wiersza_b[1] > ilosc_wierszy - 8)
                        {
                                for(int i = 0; i <= 11; i++)
                                {
                                        bufor_calosc->Append(bd_wyjscie[i].c_str());
                                }
                        }
                        else
                        {
                                for(int i = bufor_i + 12; i <= bufor_i + 23; i++)
                                {
                                        bufor_calosc->Append(lista_aktywnosci->Strings[i]);
                                }
                        }
                }
                break;
                case 0:
                {
                        for(int i = 0; i < 7; i++) bufor_calosc->Append(bufor_poczatek[i]);

                        bufor_as = fu4.int_na_str(ilosc_aktywnosci).c_str();
                        bufor_calosc->Append("Iloœæ aktywnoœci: " + bufor_as);
                        bufor_calosc->Append("");
                        bufor_as = fu4.sek_na_czas(calkowity_czas_r).c_str();
                        bufor_calosc->Append("Ca³kowity czas dzia³ania: " + bufor_as);
                        bufor_calosc->Append("");
                        bufor_calosc->Append("Najd³u¿szy czas dzia³ania: " + najdluzszy_czas_czas);
                        bufor_calosc->Append(" " + najdluzszy_czas_data[0]);
                        bufor_calosc->Append(" " + najdluzszy_czas_data[1]);

                        bufor_calosc->Append("");
                        bufor_calosc->Append("-----------------------------------------------------------------");
                        bufor_calosc->Append("");
                        bufor_calosc->Append("Lista aktywnoœci z podanego przedzia³u:");

                        bufor_ia = ilosc_aktywnosci;
                        if(nr_wiersza_b[0] + 8 * ilosc_aktywnosci > ilosc_wierszy) bufor_ia --;
                        bufor_i = (nr_wiersza_b[0] / 8) * 12;
                        for(int i = 0; i < bufor_ia; i++)
                        {
                                bufor_as = fu4.int_na_str(i + 1).c_str();
                                bufor_calosc->Append(bufor_as + '.');
                                bufor_i ++;
                                for(int j = 1; j <= 11; j++)
                                {
                                        bufor_calosc->Append(lista_aktywnosci->Strings[bufor_i]);
                                        bufor_i ++;
                                }
                        }
                        if(bufor_ia < ilosc_aktywnosci)
                        {
                                bufor_as = fu4.int_na_str(ilosc_aktywnosci).c_str();
                                bufor_calosc->Append(bufor_as + '.');
                                for(int i = 1; i <= 11; i++)
                                {
                                        bufor_calosc->Append(bd_wyjscie[i].c_str());
                                }
                        }
                }
                break;
                default: bufor_calosc->Append("Coœ nie pyk³o ;b");
        }

        Form3->Lista_aktywnosci->Lines = bufor_calosc;

        delete lista_aktywnosci;
        delete bufor_calosc;

        Form4->Visible = false;
}
