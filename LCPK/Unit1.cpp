//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"

#include <fstream>
#include <time.h>
#include <windows.h>

#include "Unit2.h"
#include "Unit3.h"
#include "Unit6.h"
#include "Unit7.h"
#include "Unit8.h"


TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        LCPKm f;

        if(f.sprawdzenie_czy_program_jest_juz_uruchomiony("LCPK.exe"))
        {
                ShowMessage("Program \"LCPK.exe\" jest ju¿ uruchomiony");
                Application->Terminate();
                return;
        }
        if(!(f.czy_plik_istnieje("LCPK.exe")))
        {
                ShowMessage("Program \"LCPK.exe\" nie mo¿e zostaæ uruchomiony z tej lokalizacji, poniewa¿ mog³oby to skutkowaæ niepoprawnym dzia³aniem aplikacji");
                Application->Terminate();
                return;
        }

        if(f.odczyt_danych("Dane/Ustawienia.txt", 9) == "1")
        {
                tworzenie_bufora_danych_poprzedniej_aktywnosci();
        }
        else f.dodanie_danych();
///////////////////////////////////////////////////////////////////////////////
        time(&czas_roz);

        czy_stworzono_folder = false;

        nieprawidlowe_podania_hasla = 0;

        nadwyzkowy_czas = 0;

        arok = "1970"; amiesiac = "01"; adzien = "01"; agodz = "00"; amin = "00"; asek = "00";

        s[0]=0; s[1]=0; s[2]=0;

        ustawienia[0] = "300";
        ustawienia[1] = "0";
        ustawienia[2] = "1";
        ustawienia[3] = "0";
        ustawienia[4] = "1";
        ustawienia[5] = "1";
        ustawienia[6] = "0";
        ustawienia[7] = "1510440600";
        ustawienia[8] = "0"; //0 - zapisuje dane, 1 - nie zapisuje danych

        autozapis = atoi(ustawienia[0].c_str());
///////////////////////////////////////////////////////////////////////////////

        tworzenie_plikow();

        wprowadzenie_ustawien();
        
        autozapis = atoi(ustawienia[0].c_str());
        autozapis = ustawianie_autozapisu(autozapis);

        ustawianie_widocznosci();

        ustawianie_pokazywania();

        zapis_ustawien();

        s[0]=0;

        s[1]=atoi(f.odczyt_danych("Dane/Bufor_danych.txt", 5).c_str());
        Czas2->Caption = f.sek_na_czas(s[1]).c_str();

        ustawianie_daty(atof(ustawienia[7].c_str()));
        Czas3->Caption = f.sek_na_czas(s[2]).c_str();

        f.zapis_danych("Dane/Bufor_danych.txt", czas_roz, s[0], s[1], autozapis, "Uruchomienie programu");

        if(czy_stworzono_folder)
        {
                Visible = true;

                f.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "Pierwsze uruchomienie programu");
                if(f.instalacja_do_autostartu())
                {
                        ShowMessage("Skrót programu \"LCPK.exe\" zosta³ poprawnie zainstalowany do autostartu u¿ytkownika. W przypadku zmiany po³o¿enia folderu z programem nale¿y u¿yæ opcji \"Opcje->Narzêdzia->Zainstaluj do autostartu\" w celu poprawnego dzia³ania skrótu.");
                }
                else
                {
                        ShowMessage("Wyst¹pi³ b³¹d przy instalacji skrótu programu do autostartu. W celu poprawnego dzia³ania aplikacji nale¿y rêcznie umieœci skrót programu \"LCPK.exe\" w folderze \"Autostart\"");
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormActivate(TObject *Sender)
{
        LCPKm f;
        ustawianie_daty(atoi(ustawienia[7].c_str()));
        f.zapis_danych("Dane/Bufor_danych.txt", czas_roz, s[0], s[1], autozapis, "Aktywacja g³ównego okna programu");
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        LCPKm f;
        Action = caNone;
        f.zapis_danych("Dane/Bufor_danych.txt", czas_roz, s[0], s[1], autozapis, "Ukrycie poprzez wciœniêcie \"x\"");
        Visible = false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ZegarTimer(TObject *Sender)
{
        LCPKm f;
        s[0]++;
        s[1]++;
        if(nadwyzkowy_czas < s[0]) s[2]++;

        if(x[0]==1) Czas1->Caption = f.sek_na_czas(s[0]).c_str();
        if(x[1]==1) Czas2->Caption = f.sek_na_czas(s[1]).c_str();
        if(x[2]==1) Czas3->Caption = f.sek_na_czas(s[2]).c_str();

        if(autozapis == 0) autozapis = 60;
        if(s[0] % autozapis == 0)
        {
                f.zapis_danych("Dane/Bufor_danych.txt", czas_roz, s[0], s[1], autozapis, "Autozapis");
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrayIcon1Click(TObject *Sender)
{
        Show();
        Application->BringToFront();
}
//---------------------------------------------------------------------------



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void __fastcall TForm1::Zapiszczas1Click(TObject *Sender)
{
        LCPKm f;
        f.zapis_danych("Dane/Bufor_danych.txt", czas_roz, s[0], s[1], autozapis, "Zapis rêczny");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zainstalujdoautostartu1Click(TObject *Sender)
{
        LCPKm f;
        if(Application->MessageBox(
        "Czy na pewno zainstalowa skrót programu \"LCPK.exe\" do autostartu u¿ytkownika?", "PotwierdŸ",
        MB_YESNOCANCEL | MB_ICONQUESTION) == IDYES)
        {
                f.zapis_danych("Dane/Bufor_danych.txt", czas_roz, s[0], s[1], autozapis, "Instalacja skrótu do autostartu");

                if(f.instalacja_do_autostartu())
                {
                        ShowMessage("Skrót programu \"LCPK.exe\" zosta³ poprawnie zainstalowany do autostartu u¿ytkownika. W przypadku zmiany po³o¿enia folderu z programem nale¿y u¿yæ ponownie opcji \"Opcje->Narzêdzia->Zainstaluj do autostartu\" w celu poprawnego dzia³ania skrótu.");
                        f.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "Zainstalowanie skrótu programu \"LCPK.exe\" do autostartu");
                }
                else
                {
                        ShowMessage("Wyst¹pi³ b³¹d przy instalacji skrótu programu do autostartu. W celu poprawnego dzia³ania aplikacji nale¿y rêcznie umieœci skrót programu \"LCPK.exe\" w folderze \"Autostart\"");
                        f.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "Nieudana instalacja skrótu programu \"LCPK.exe\" do autostartu");
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Odinstalujzautostartu1Click(TObject *Sender)
{
        LCPKm f;

        if(Application->MessageBox(
        "Czy na pewno usun¹æ skrót programu \"LCPK.exe\" z autostartu u¿ytkownika?", "PotwierdŸ",
        MB_YESNOCANCEL | MB_ICONQUESTION) == IDYES)
        {
                f.zapis_danych("Dane/Bufor_danych.txt", czas_roz, s[0], s[1], autozapis, "Usuwanie skrótu programu \"LCPK.exe\" z autostartu");

                Form7->co_wybrac = 7;
                Form7->ShowModal();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zmiehaso1Click(TObject *Sender)
{
        Form8->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ZakonczClick(TObject *Sender)
{
        LCPKm f;
        if(Application->MessageBox(
        "Czy na pewno zakoñczyæ dzia³anie programu?", "PotwierdŸ",
        MB_YESNOCANCEL | MB_ICONQUESTION) == IDYES)
        {
                f.zapis_danych("Dane/Bufor_danych.txt", czas_roz, s[0], s[1], autozapis, "Zamkniêcie programu");
                f.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "Zamkniêcie programu przez u¿ytkownika");
                Application->Terminate();
        }
        else
        {
                f.zapis_danych("Dane/Bufor_danych.txt", czas_roz, s[0], s[1], autozapis, "Wstrzymanie wy³¹czania programu");
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::minuty1Click(TObject *Sender)
{
        przycisk_autozapisu(60);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::minuty2Click(TObject *Sender)
{
        przycisk_autozapisu(120);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::minuty5Click(TObject *Sender)
{
        przycisk_autozapisu(300);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::minuty10Click(TObject *Sender)
{
        przycisk_autozapisu(600);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::minuty15Click(TObject *Sender)
{
        przycisk_autozapisu(900);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::minuty30Click(TObject *Sender)
{
        przycisk_autozapisu(1800);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::minuty60Click(TObject *Sender)
{
        przycisk_autozapisu(3600);
}
//---------------------------------------------------------------------------





void __fastcall TForm1::Minimalizujdotreya1Click(TObject *Sender)
{
        przycisk_widocznosci("0", "1", "0", "Minimalizuj do treya");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Trybninja1Click(TObject *Sender)
{
        if(Trybninja1->Checked == true) return;
        if(Application->MessageBox(
        "Czy na pewno za³¹czyæ tryb ninja? Sprawi on, ¿e Twoja aplikacja bêdzie nieuchwytna niczym ninja!", "PotwierdŸ",
        MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
                Form7->co_wybrac = 6;
                Form7->ShowModal();
        }
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Aktualnyczas1Click(TObject *Sender)
{
        if(Aktualnyczas1->Checked == true) przycisk_pokazywania(4, "0","Ukrycie aktualnego czasu pracy");
        else przycisk_pokazywania(4, "1","Wyœwietlenie aktualnego czasu pracy");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Calkowityczaspracy1Click(TObject *Sender)
{
        if(Calkowityczaspracy1->Checked == true) przycisk_pokazywania(5, "0","Ukrycie ca³kowitego czasu pracy");
        else przycisk_pokazywania(5, "1","Wyœwietlenie ca³kowitego czasu pracy");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Pokazdate1Click(TObject *Sender)
{
        if(Pokazdate1->Checked == true) przycisk_pokazywania(6, "0","Ukrycie czasu pracy od daty");
        else przycisk_pokazywania(6, "1","Wyœwietlenie czasu pracy od daty\nPokazywanie daty");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Dataigodzina1Click(TObject *Sender)
{
        if(Dataigodzina1->Checked == true) przycisk_pokazywania(6, "0","Ukrycie czasu pracy od daty");
        else przycisk_pokazywania(6, "2","Wyœwietlenie czasu pracy od daty\nPokazywanie daty i godziny");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Niepokazujdaty1Click(TObject *Sender)
{
        if(Niepokazujdaty1->Checked == true) przycisk_pokazywania(6, "0","Ukrycie czasu pracy od daty");
        else przycisk_pokazywania(6, "3","Wyœwietlenie czasu pracy od daty\nBez pokazywania daty");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Ustawdate1Click(TObject *Sender)
{
        Form6->Visible = true;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Aktywno1Click(TObject *Sender)
{
        Form3->wyswietlenie_danych("Dane/Lista_aktywnosci.txt");
        Form3->Visible = true;
}
//---------------------------------------------------------------------------



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int TForm1::ustawianie_autozapisu(int co_ile_zapis)
{
        minuty1->Checked = false;
        minuty2->Checked = false;
        minuty5->Checked = false;
        minuty10->Checked = false;
        minuty15->Checked = false;
        minuty30->Checked = false;
        minuty60->Checked = false;
        switch(co_ile_zapis)
        {
                case 60: minuty1->Checked = true; break;
                case 120: minuty2->Checked = true; break;
                case 300: minuty5->Checked = true; break;
                case 600: minuty10->Checked = true; break;
                case 900: minuty15->Checked = true; break;
                case 1800: minuty30->Checked = true; break;
                case 3600: minuty60->Checked = true; break;
                default:
                {
                        co_ile_zapis = 300;
                        minuty5->Checked = true;
                        break;
                }
        }
        return co_ile_zapis;
}

void TForm1::przycisk_autozapisu(int co_ile_zapis)
{
        LCPKm f;
        autozapis = ustawianie_autozapisu(co_ile_zapis);
        zapis_ustawien();
        f.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 1, f.int_na_str(autozapis));
}

///////////////////////////////////////

void TForm1::ustawianie_widocznosci()
{
        Minimalizuj1->Checked = false;
        Minimalizujdotreya1->Checked = false;
        Trybninja1->Checked = false;
        WindowState = wsNormal;
        if(TrayIcon1->Visible == true) TrayIcon1->Visible = false;
        if((ustawienia[1]!="1")&&(ustawienia[2]!="1")&&(ustawienia[3]!="1"))
        {
                ustawienia[1]="0";
                ustawienia[2]="1";
                ustawienia[3]="0";
        }

        if(ustawienia[3]=="1")
        {
                ustawienia[1]="0";
                ustawienia[2]="0";
                Trybninja1->Checked = true;
        }
        else ustawienia[3]="0";

        if(ustawienia[1]=="1")
        {
                ustawienia[1]="0";
                ustawienia[2]="1";
        }
        else ustawienia[1]="0";

        if(ustawienia[2]=="1")
        {
                TrayIcon1->Visible = true;
                Minimalizujdotreya1->Checked = true;
        }
        else ustawienia[2]="0";
}

void TForm1::przycisk_widocznosci(AnsiString ustawienia1, AnsiString ustawienia2, AnsiString ustawienia3, AnsiString tekst)
{
        LCPKm f;
        ustawienia[1]=ustawienia1;
        ustawienia[2]=ustawienia2;
        ustawienia[3]=ustawienia3;
        ustawianie_widocznosci();
        zapis_ustawien();
        f.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 2, tekst.c_str());
}

///////////////////////////////////////

void TForm1::ustawianie_pokazywania()
{
        LCPKm f;
        sek_na_date(atoi(ustawienia[7].c_str()));
        astr_data = adzien + "." + amiesiac + "." + arok;
        astr_godzina = agodz + ":" + amin + ":" + asek;

        Napis1->Visible = false;
        Czas1->Visible = false;
        Aktualnyczas1->Checked = false;
        x[0]=0;
        Napis2->Visible = false;
        Czas2->Visible = false;
        Calkowityczaspracy1->Checked = false;
        x[1]=0;
        Napis3->Visible = false;
        Czas3->Visible = false;
        Czaspracyoddaty1->Checked = false;
        x[2]=0;
        if(ustawienia[4]=="1")
        {
                Napis1->Visible = true;
                Czas1->Visible = true;
                Aktualnyczas1->Checked = true;
                x[0]=1;
        }
        else ustawienia[4]="0";

        if(ustawienia[5]=="1")
        {
                Napis2->Visible = true;
                Czas2->Visible = true;
                Calkowityczaspracy1->Checked = true;
                x[1]=1;
        }
        else ustawienia[5]="0";

        Pokazdate1->Checked = false;
        Dataigodzina1->Checked = false;
        Niepokazujdaty1->Checked = false;
        if(ustawienia[6]!="0")
        {
                Napis3->Visible = true;
                Czas3->Visible = true;
                Czaspracyoddaty1->Checked = true;
                Czas3->Caption = f.sek_na_czas(s[2]).c_str();
                x[2]=1;
        }
        if(ustawienia[6]=="1")
        {
                Pokazdate1->Checked = true;
                Napis3->Caption = "Czas pracy programu od "+astr_data+"r.";
        }
        else if(ustawienia[6]=="2")
        {
                Dataigodzina1->Checked = true;
                Napis3->Caption = "Czas pracy programu od "+astr_data+"r.  "+astr_godzina;
        }
        else if(ustawienia[6]=="3")
        {
                if(Niepokazujdaty1->Checked == false) Napis3->Top +=30;
                Niepokazujdaty1->Checked = true;
                Napis3->Caption = "Czas pracy programu od daty";
        }
        else
        {
                Napis3->Visible = false;
                Czas3->Visible = false;
                Czaspracyoddaty1->Checked = false;
                x[2]=0;
                ustawienia[6]="0";
        }

        licznik[0]=0;
        if(Aktualnyczas1->Checked == true) licznik[0] += 2;
        if(Calkowityczaspracy1->Checked == true) licznik[0] += 2;
        if(Czaspracyoddaty1->Checked == true) licznik[0] += 2;
        if(licznik[0]==6) Height = 480;
        else Height = 360;
        licznik[1]=1;
        if(Aktualnyczas1->Checked == true)
        {
                Napis1->Top = f.pozycja_napisu(licznik[0],licznik[1]); licznik[1]++;
                Czas1->Top = f.pozycja_napisu(licznik[0],licznik[1]); licznik[1]++;
        }
        if(Calkowityczaspracy1->Checked == true)
        {
                Napis2->Top = f.pozycja_napisu(licznik[0],licznik[1]); licznik[1]++;
                Czas2->Top = f.pozycja_napisu(licznik[0],licznik[1]); licznik[1]++;
        }
        if(Czaspracyoddaty1->Checked == true)
        {
                Napis3->Top = f.pozycja_napisu(licznik[0],licznik[1]); licznik[1]++;
                Czas3->Top = f.pozycja_napisu(licznik[0],licznik[1]); licznik[1]++;
                if(Niepokazujdaty1->Checked == false) Napis3->Top -= 30;
        }
}

void TForm1::przycisk_pokazywania(int numer_ustawienia, AnsiString ustaw_na, AnsiString tekst)
{
        LCPKm f;
        if((numer_ustawienia >= 4)&&(numer_ustawienia <= 6))
        {
                ustawienia[numer_ustawienia] = ustaw_na;
                ustawianie_pokazywania();
                zapis_ustawien();
                f.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 3, tekst.c_str());
        }
}

///////////////////////////////////////

void TForm1::wprowadzenie_ustawien()
{
        int numer=0;
        std::string ustawienia0[9];

        plik.open("Dane/Ustawienia.txt", std::ios::in);

        if(plik.good()==true)
        {
                for(int i=0; i<=8; i++)
                {
                        if(plik.eof()) break;
                        plik>>ustawienia0[numer];
                        numer++;
                }
                plik.close();
                plik.clear();

                if(numer==9)
                {
                        for(int i=0; i<=7; i++)
                        {
                                ustawienia[i]=ustawienia0[i].c_str();
                        }
                }
        }
}

void TForm1::zapis_ustawien()
{
        plik.open("Dane/Ustawienia.txt", ios::out);

        plik<<autozapis<<endl;
        plik<<ustawienia[1].c_str()<<endl;
        plik<<ustawienia[2].c_str()<<endl;
        plik<<ustawienia[3].c_str()<<endl;
        plik<<ustawienia[4].c_str()<<endl;
        plik<<ustawienia[5].c_str()<<endl;
        plik<<ustawienia[6].c_str()<<endl;
        plik<<ustawienia[7].c_str()<<endl;
        plik<<ustawienia[8].c_str();

        plik.close();
        plik.clear();
}

void TForm1::ustawianie_daty(double cws)
{
        LCPKm f;

        f.zapis_danych("Dane/Bufor_danych.txt", czas_roz, s[0], s[1], autozapis, "Ustawianie daty");

        int od_ktorego_zaczac;
        int ilosc_wierszy[2];
        double czas_bufor[4];
        double calkowity_czas_b[2];
        bool znaleziono = false;

        TStringList *dane = new TStringList;
        TStringList *bufor_danych = new TStringList;

        dane->LoadFromFile("Dane/Dane.txt");
        bufor_danych->LoadFromFile("Dane/Bufor_danych.txt");
        ilosc_wierszy[0] = dane->Count;
        ilosc_wierszy[1] = bufor_danych->Count;

        if((ilosc_wierszy[1] != 8)||(ilosc_wierszy[0] % 8 != 0)) return;

        czas_bufor[0] = atof(bufor_danych->Strings[1].c_str());
        czas_bufor[1] = atof(bufor_danych->Strings[2].c_str());

        if(cws > czas_bufor[0])
        {
                s[2] = 0;
                nadwyzkowy_czas = cws - czas_bufor[1];
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

        Form1->s[2] = calkowity_czas_b[1] - calkowity_czas_b[0];
}


void TForm1::tworzenie_plikow()
{
        LCPKm f;

        HANDLE hplik;
        czy_stworzono_folder = CreateDirectory("Dane", NULL);

        if(czy_stworzono_folder)
        {
                system("attrib +s +h Dane");
        }

        if(!(f.czy_plik_istnieje("Dane/Bufor_danych.txt")))
        {
                hplik = CreateFile("Dane/Bufor_danych.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN, NULL);
                CloseHandle(hplik);
                f.zapis_danych("Dane/Bufor_danych.txt", czas_roz, s[0], s[1], autozapis, "Utworzenie pliku");
        }
        if(!(f.czy_plik_istnieje("Dane/Dane.txt")))
        {
                hplik = CreateFile("Dane/Dane.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN, NULL);
                CloseHandle(hplik);
        }
        if(!(f.czy_plik_istnieje("Dane/Dzialania_uzytkownika.txt")))
        {
                hplik = CreateFile("Dane/Dzialania_uzytkownika.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN, NULL);
                CloseHandle(hplik);
        }
        if(!(f.czy_plik_istnieje("Dane/Haslo.txt")))
        {
                hplik = CreateFile("Dane/Haslo.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN, NULL);
                CloseHandle(hplik);
                plik.open("Dane/Haslo.txt", ios::out);
                plik << f.losowe_haslo("de83jflxho3p95hksdu3i2878952hfdfksh", "brak hasla axc0wa896321c4342b8hgfh35dgfdj52gg") << endl;
                plik.close();
                plik.clear();
        }
        if(!(f.czy_plik_istnieje("Dane/Lista_aktywnosci.txt")))
        {
                hplik = CreateFile("Dane/Lista_aktywnosci.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN, NULL);
                CloseHandle(hplik);
        }
        if(!(f.czy_plik_istnieje("Dane/Ustawienia.txt")))
        {
                hplik = CreateFile("Dane/Ustawienia.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN, NULL);
                CloseHandle(hplik);
                zapis_ustawien();
        }
        if(!(f.czy_plik_istnieje("Dane/Ustawienia2.txt")))
        {
                hplik = CreateFile("Dane/Ustawienia2.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN, NULL);
                CloseHandle(hplik);
                plik.open("Dane/Ustawienia2.txt", ios::out);
                plik << f.szyfrowanie_hasla("de83jflxho3p95hksdu3i2878952hfdfksh", "brak hasla axc0wa896321c4b8") << endl;
                plik.close();
                plik.clear();
        }
}

void TForm1::sek_na_date(double czas_w_sek)
{
        LCPKm f;

        f.sek_na_date(czas_w_sek);

        arok = f.mrok.c_str();                  agodz = f.mgodz.c_str();
        amiesiac = f.mmiesiac.c_str();          amin = f.mmin.c_str();
        adzien = f.mdzien.c_str();              asek = f.msek.c_str();
}

void TForm1::data_na_sek(AnsiString rok, AnsiString miesiac, AnsiString dzien, AnsiString godziny, AnsiString minuty, AnsiString sekundy)
{
        LCPKm f;

        f.mrok = rok.c_str();                   f.mgodz = godziny.c_str();
        f.mmiesiac = miesiac.c_str();           f.mmin = minuty.c_str();
        f.mdzien = dzien.c_str();               f.msek = sekundy.c_str();

        f.data_na_sek(f.mrok, f.mmiesiac, f.mdzien, f.mgodz, f.mmin, f.msek);

        arok = f.mrok.c_str();                  agodz = f.mgodz.c_str();
        amiesiac = f.mmiesiac.c_str();          amin = f.mmin.c_str();
        adzien = f.mdzien.c_str();              asek = f.msek.c_str();
}

void TForm1::tworzenie_bufora_danych_poprzedniej_aktywnosci()
{
        int ilosc_wierszy;

        TStringList *dane = new TStringList;
        dane->LoadFromFile("Dane/Dane.txt");
        ilosc_wierszy = dane->Count;

        if(ilosc_wierszy >= 8)
        {
                plik.open("Dane/Bufor_danych.txt", ios::out);

                for(int i = 8; i > 0; i--)
                {
                        plik << dane->Strings[ilosc_wierszy - i].c_str() << endl;
                }

                plik.close();
                plik.clear();
        }
        else DeleteFile("Dane/Bufor_danych.txt" );

        delete dane;
}

