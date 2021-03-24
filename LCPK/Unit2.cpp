//---------------------------------------------------------------------------

#define NO_WIN32_LEAN_AND_MEAN
#pragma hdrstop

#include "Unit2.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#include <iostream>
#include <fstream>
#include <time.h>
#include <shlobj.h>

#include "Unit1.h"

#include "Unit3.h"

using namespace std;

LCPKm::LCPKm()
{
        tlat=0; tdni=0; tgodzin=0; tminut=0; tsekund=0;
        tl="0 lat"; td="0 dni"; tgodz="00"; tmin="00"; tsek="00";


        mrok = "1970";          mgodz = "00";
        mmiesiac = "01";        mmin = "00";
        mdzien = "01";          msek = "00";

        frok = 1970;            fgodz = 0;              fczas_w_sek = 0;
        fmiesiac = 1;           fmin = 0;               frok_przestepny = 0;
        fdzien = 1;             fsek = 0;               fdzien_tygodnia = 4;
}

string LCPKm::int_na_str(int liczba)
{
        string napis;
        if(liczba < 0)
        {
                napis = "-";
                liczba = -liczba;
        }

        if(liczba > 9) napis += int_na_str(liczba / 10);
        napis += liczba % 10 + 48;

        return napis;
}

string LCPKm::sek_na_czas(int ss)
{
        tlat = ss/31536000;
        if(tlat >= 0)
        {
                tl = int_na_str(tlat);
                if(tlat == 0) tl+=" lat";
                else if(tlat == 1) tl+=" rok";
                else if((tlat % 10 >= 2)&&(tlat % 10 <= 4)&&((tlat % 100 < 12)||(tlat % 100 > 14))) tl+=" lata";
                else tl+=" lat";
        }

        tdni = (ss - tlat*31536000)/86400;
        if(tdni >= 0)
        {
                td = int_na_str(tdni);
                if(tdni == 0) td+=" dni";
                else if(tdni == 1) td+=" dzieñ";
                else td+=" dni";
        }

        tgodzin = (ss - tlat*31536000 - tdni*86400)/3600;
        tgodz = int_na_str(tgodzin);
        if(tgodzin < 10) tgodz="0"+tgodz;

        tminut = (ss - tlat*31536000 - tdni*86400 - tgodzin*3600)/60;
        tmin = int_na_str(tminut);
        if(tminut < 10) tmin="0"+tmin;

        tsekund = ss - tlat*31536000 - tdni*86400 - tgodzin*3600 - tminut*60;
        tsek = int_na_str(tsekund);
        if(tsekund < 10) tsek="0"+tsek;

        if(tlat > 0) return tl+" "+td+" "+tgodz+":"+tmin+":"+tsek;
        else if(tdni > 0) return td+" "+tgodz+":"+tmin+":"+tsek;
        else return tgodz+":"+tmin+":"+tsek;
}

void LCPKm::zapis_danych(char nazwa_pliku[], time_t czas_roz, int czas_dzialania, int czas_calkowity, int co_ile_zapis, string sposob_zapisu)
{
        time_t czas;
        time(&czas);
        struct tm * data;
        char fbufor[80];

        data = localtime(&czas_roz);
        strftime(fbufor, 80, "%d.%m.%Yr. %X", data);

        plik.open(nazwa_pliku, ios::out);

        plik<<fbufor<<endl;
        plik<<czas<<endl;
        plik<<czas_roz<<endl;
        plik<<czas_dzialania<<endl;
        plik<<czas_calkowity<<endl;
        plik<<co_ile_zapis<<endl;
        plik<<sposob_zapisu<<endl;
        plik<<"------------------------------"<<endl;

        plik.close();
        plik.clear();
}

string LCPKm::odczyt_danych(char nazwa_pliku[], int pozycja)
{
        plik.open(nazwa_pliku, ios::in);

        if(plik.good()==true)
        {
                for(int i=1; i<=pozycja; i++)
                {
                        if(plik.eof())
                        {
                                bufor="0";
                                break;
                        }

                        getline(plik, bufor);
                }
        }
        else bufor="0";

        plik.close();
        plik.clear();

        return bufor;
}

void LCPKm::dodanie_danych()
{
        string fbufor[8];
        double dczas;
        int iczas;
        string tbufor[5];

        plik.open("Dane/Bufor_danych.txt", ios::in);

        if(plik.good()==true)
        {
                for(int i=0; i<8; i++)
                {
                        if(plik.eof())  break;
                        getline(plik, fbufor[i]);
                }
        }
        plik.close();
        plik.clear();

        if(fbufor[7] == "------------------------------")
        {
                plik.open("Dane/Dane.txt", ios::out | ios::app);

                for(int i=0; i<8; i++) plik<<fbufor[i]<<endl;

                plik.close();
                plik.clear();

                /////////////////////////////////////////////////////////

                dczas = atof(fbufor[2].c_str());
                sek_na_date(dczas);
                tbufor[0] = mdzien+"."+mmiesiac+"."+mrok+"r. "+mgodz+":"+mmin+":"+msek;

                dczas = atof(fbufor[1].c_str());
                sek_na_date(dczas);
                tbufor[1] = mdzien+"."+mmiesiac+"."+mrok+"r. "+mgodz+":"+mmin+":"+msek;

                iczas = atoi(fbufor[3].c_str());
                tbufor[2] = sek_na_czas(iczas);

                iczas = atoi(fbufor[4].c_str());
                tbufor[3] = sek_na_czas(iczas);

                iczas = atoi(fbufor[5].c_str());
                iczas /= 60;
                if(iczas == 60) tbufor[4] = "1 godzine";
                else tbufor[4] = int_na_str(iczas)+" min";

                plik.open("Dane/Lista_aktywnosci.txt", ios::out | ios::app);

                plik<<endl<<fbufor[0]<<endl;
                plik<<endl;
                plik<<"Czas aktywnoœci"<<endl;
                plik<<"   od "<<tbufor[0]<<endl;
                plik<<"   do "<<tbufor[1]<<endl;
                plik<<"Czas dzia³ania programu: "<<tbufor[2]<<endl;
                plik<<"Ca³kowity czas: "<<tbufor[3]<<endl;
                plik<<"Autozapis: co "<<tbufor[4]<<endl;
                plik<<"Zapisano poprzez: "<<fbufor[6]<<endl;
                plik<<endl;
                plik<<"--------------------------------------------------"<<endl;

                plik.close();
                plik.clear();
        }
}

void LCPKm::odnotowanie_dzialan_uzytkownika(char nazwa_pliku[],int rodzaj_ustawien, string tekst)
{
        if((rodzaj_ustawien >=1)&&(rodzaj_ustawien <= 5))
        {
                time_t czas;
                int ibufor;

                time(&czas);
                sek_na_date(czas);
                bufor = mdzien+"."+mmiesiac+"."+mrok+"r. "+mgodz+":"+mmin+":"+msek;

                plik.open(nazwa_pliku, ios::out | ios::app);

                plik<<endl<<bufor<<endl;

                if(rodzaj_ustawien == 1)
                {
                        ibufor = atoi(tekst.c_str());
                        ibufor /= 60;
                        if(ibufor == 60) bufor = "1 godzine";
                        else bufor = int_na_str(ibufor)+" min";
                        plik<<"Zmiana autozapisu na: co "<<bufor<<endl;
                }
                else if(rodzaj_ustawien == 2)
                {
                        plik<<"Zmiana widocznoœci na: "<<tekst<<endl;
                }
                else if(rodzaj_ustawien == 3)
                {
                        plik<<"Zmiana pokazywania"<<endl<<tekst<<endl;
                }
                else if(rodzaj_ustawien == 4)
                {
                        plik<<"Zmiana daty"<<endl<<tekst<<endl;
                }
                else if(rodzaj_ustawien == 5)
                {
                        plik<<tekst<<endl;
                }

                plik<<endl<<"--------------------------------------------------"<<endl;

                plik.close();
                plik.clear();
        }
}

bool LCPKm::czy_plik_istnieje(string sciezka_pliku)
{
        plik.open(sciezka_pliku.c_str(), ios::in);
        if(plik.good())
        {
                plik.close();
                plik.clear();
                return true;
        }
        else
        {
                plik.close();
                plik.clear();
                return false;
        }
}

int LCPKm::pozycja_napisu(int ilosc_napisow, int ktory)
{
        switch(ilosc_napisow)
        {
                case 0: return 0;
                break;
                case 1:
                case 2:
                {
                        switch(ktory)
                        {
                                case 1: return 115;
                                break;
                                case 2: return 145;
                                break;
                                default: return 0;
                        }
                        break;
                }
                case 3:
                case 4:
                case 5:
                case 6:
                {
                        switch(ktory)
                        {
                                case 1: return 55;
                                break;
                                case 2: return 85;
                                break;
                                case 3: return 175;
                                break;
                                case 4: return 205;
                                break;
                                case 5: return 295;
                                break;
                                case 6: return 325;
                                break;
                                default: return 0;
                        }
                        break;
                }
                default: return 0;

        }
        return 0;
}

void LCPKm::sek_na_date(double czas_w_sek)
{
        double bufor1 = 0, czas_letni[3] = {0,0,0};
        int bdzien_tygodnia = 0;
        int agodz = 0;
        int lata = 0;
        int dws = 86400;

        frok = 1970;            fgodz = 0;              fczas_w_sek = czas_w_sek;
        fmiesiac = 1;           fmin = 0;               frok_przestepny = 0;
        fdzien = 1;             fsek = 0;               fdzien_tygodnia = 0;

        czas_w_sek += 3600;

        if(czas_w_sek >= 0)
        {
                while(bufor1 <= czas_w_sek)
                {
                        if((1970+lata)%4==0 && (1970+lata)%100!=0 || (1970+lata)%400==0)
                        {
                                frok_przestepny = 1;
                                if(bufor1 <= czas_w_sek - 31622400)
                                {
                                        bufor1 += 31622400;
                                        lata++;
                                }
                                else break;
                        }
                        else
                        {
                                frok_przestepny = 0;
                                if(bufor1 <= czas_w_sek - 31536000)
                                {
                                        bufor1 += 31536000;
                                        lata++;
                                }
                                else break;
                        }
                }
                frok += lata;

                //zmiana na czas letni
                czas_letni[0] = bufor1 + 83*dws + 7200;
                czas_letni[1] = bufor1 + 297*dws + 7200;
                if(frok_przestepny == 1) {czas_letni[0] += dws; czas_letni[1] += dws;}
                for(int i=0; i<=6; i++)
                {
                        bdzien_tygodnia = ((czas_letni[0]+i*dws)/dws)+4;
                        bdzien_tygodnia %= 7;
                        if(bdzien_tygodnia == 0) {czas_letni[0] += i*dws; break;}
                }
                for(int i=0; i<=6; i++)
                {
                        bdzien_tygodnia = ((czas_letni[1]+i*dws)/dws)+4;
                        bdzien_tygodnia %= 7;
                        if(bdzien_tygodnia == 0) {czas_letni[1] += i*dws; break;}
                }
                if((czas_w_sek >= czas_letni[0])&&(czas_w_sek < czas_letni[1]))
                        {czas_w_sek += 3600; czas_letni[2] = 1;}


                if((czas_w_sek >= bufor1+31*dws)&&(fmiesiac == 1)) {bufor1 += 31*dws; fmiesiac = 2;}
                if((czas_w_sek >= bufor1+28*dws)&&(frok_przestepny == 0)&&(fmiesiac == 2)) {bufor1 += 28*dws; fmiesiac = 3;}
                else if((czas_w_sek >= bufor1+29*dws)&&(frok_przestepny == 1)&&(fmiesiac == 2)) {bufor1 += 29*dws; fmiesiac = 3;}
                if((czas_w_sek >= bufor1+31*dws)&&(fmiesiac == 3)) {bufor1 += 31*dws; fmiesiac = 4;}
                if((czas_w_sek >= bufor1+30*dws)&&(fmiesiac == 4)) {bufor1 += 30*dws; fmiesiac = 5;}
                if((czas_w_sek >= bufor1+31*dws)&&(fmiesiac == 5)) {bufor1 += 31*dws; fmiesiac = 6;}
                if((czas_w_sek >= bufor1+30*dws)&&(fmiesiac == 6)) {bufor1 += 30*dws; fmiesiac = 7;}
                if((czas_w_sek >= bufor1+31*dws)&&(fmiesiac == 7)) {bufor1 += 31*dws; fmiesiac = 8;}
                if((czas_w_sek >= bufor1+31*dws)&&(fmiesiac == 8)) {bufor1 += 31*dws; fmiesiac = 9;}
                if((czas_w_sek >= bufor1+30*dws)&&(fmiesiac == 9)) {bufor1 += 30*dws; fmiesiac = 10;}
                if((czas_w_sek >= bufor1+31*dws)&&(fmiesiac == 10)) {bufor1 += 31*dws; fmiesiac = 11;}
                if((czas_w_sek >= bufor1+30*dws)&&(fmiesiac == 11)) {bufor1 += 30*dws; fmiesiac = 12;}

                fdzien = (czas_w_sek - bufor1)/dws;
                bufor1 += fdzien*dws;
                fdzien++;

                fgodz = (czas_w_sek - bufor1)/3600;
                bufor1 += fgodz*3600;
                fmin = (czas_w_sek - bufor1)/60;
                bufor1 += fmin*60;
                fsek = (czas_w_sek - bufor1);

                fdzien_tygodnia = (czas_w_sek/dws)+4;
                fdzien_tygodnia %= 7;

                if((czas_letni[1] <= czas_w_sek)&&(czas_letni[1] + 3600 > czas_w_sek)&&(czas_letni[2] == 0))
                    agodz = 1;
        }
        else if(czas_w_sek < 0)
        {
                czas_w_sek++;
                while(bufor1 >= czas_w_sek)
                {
                        if((1969+lata)%4==0 && (1969+lata)%100!=0 || (1969+lata)%400==0)
                        {
                                frok_przestepny = 1;
                                if(bufor1 >= czas_w_sek + 31622400)
                                {
                                        bufor1 -= 31622400;
                                        lata--;
                                }
                                else break;
                        }
                        else
                        {
                                frok_przestepny = 0;
                                if(bufor1 >= czas_w_sek + 31536000)
                                {
                                        bufor1 -= 31536000;
                                        lata--;
                                }
                                else break;
                        }
                }
                frok += lata - 1;

                //zmiana na czas letni
                czas_letni[0] = bufor1 - 275*dws - 79200;
                czas_letni[1] = bufor1 - 61*dws - 79200;
                for(int i=0; i<=6; i++)
                {
                        bdzien_tygodnia = (-(czas_letni[0]-i*dws)/dws)+3;
                        bdzien_tygodnia %= 7;
                        bdzien_tygodnia = 6 - bdzien_tygodnia;
                        if(bdzien_tygodnia == 0) {czas_letni[0] -= i*dws; break;}
                }
                for(int i=0; i<=6; i++)
                {
                        bdzien_tygodnia = (-(czas_letni[1]-i*dws)/dws)+3;
                        bdzien_tygodnia %= 7;
                        bdzien_tygodnia = 6 - bdzien_tygodnia;
                        if(bdzien_tygodnia == 0) {czas_letni[1] -= i*dws; break;}
                }
                if((czas_w_sek - 1 >= czas_letni[0])&&(czas_w_sek - 1 < czas_letni[1]))
                        {czas_w_sek += 3600; czas_letni[2] = 1;}

                fmiesiac = 12;
                if((czas_w_sek <= bufor1-31*dws)&&(fmiesiac == 12)) {bufor1 -= 31*dws; fmiesiac = 11;}
                if((czas_w_sek <= bufor1-30*dws)&&(fmiesiac == 11)) {bufor1 -= 30*dws; fmiesiac = 10;}
                if((czas_w_sek <= bufor1-31*dws)&&(fmiesiac == 10)) {bufor1 -= 31*dws; fmiesiac = 9;}
                if((czas_w_sek <= bufor1-30*dws)&&(fmiesiac == 9)) {bufor1 -= 30*dws; fmiesiac = 8;}
                if((czas_w_sek <= bufor1-31*dws)&&(fmiesiac == 8)) {bufor1 -= 31*dws; fmiesiac = 7;}
                if((czas_w_sek <= bufor1-31*dws)&&(fmiesiac == 7)) {bufor1 -= 31*dws; fmiesiac = 6;}
                if((czas_w_sek <= bufor1-30*dws)&&(fmiesiac == 6)) {bufor1 -= 30*dws; fmiesiac = 5;}
                if((czas_w_sek <= bufor1-31*dws)&&(fmiesiac == 5)) {bufor1 -= 31*dws; fmiesiac = 4;}
                if((czas_w_sek <= bufor1-30*dws)&&(fmiesiac == 4)) {bufor1 -= 30*dws; fmiesiac = 3;}
                if((czas_w_sek <= bufor1-31*dws)&&(fmiesiac == 3)) {bufor1 -= 31*dws; fmiesiac = 2;}
                if((czas_w_sek <= bufor1-28*dws)&&(frok_przestepny == 0)&&(fmiesiac == 2)) {bufor1 -= 28*dws; fmiesiac = 1;}
                else if((czas_w_sek <= bufor1-29*dws)&&(frok_przestepny == 1)&&(fmiesiac == 2)) {bufor1 -= 29*dws; fmiesiac = 1;}

                fdzien = (-(czas_w_sek - bufor1))/dws;
                bufor1 -= fdzien*dws;
                switch(fmiesiac)
                {
                        case 1:
                        case 3:
                        case 5:
                        case 7:
                        case 8:
                        case 10:
                        case 12: fdzien = 31 - fdzien;
                        break;
                        case 4:
                        case 6:
                        case 9:
                        case 11: fdzien = 30 - fdzien;
                        break;
                        case 2: {if(frok_przestepny == 0) fdzien = 28 - fdzien;
                                 else fdzien = 29 - fdzien;}
                        break;
                }

                fgodz = (-(czas_w_sek - bufor1))/3600;
                bufor1 -= fgodz*3600;
                fgodz = 23 - fgodz;
                fmin = (-(czas_w_sek - bufor1))/60;
                bufor1 -= fmin*60;
                fmin = 59 - fmin;
                fsek = (-(czas_w_sek - bufor1));
                fsek = 59 - fsek;

                fdzien_tygodnia = (-czas_w_sek/dws)+3;
                fdzien_tygodnia %= 7;
                fdzien_tygodnia = 6 - fdzien_tygodnia;

                if((czas_letni[1] <= czas_w_sek - 1)&&(czas_letni[1] + 3600 > czas_w_sek - 1)&&(czas_letni[2] == 0))
                    agodz = 1;
        }

        mrok = int_na_str(frok);                mgodz = int_na_str(fgodz);
        mmiesiac = int_na_str(fmiesiac);        mmin = int_na_str(fmin);
        mdzien = int_na_str(fdzien);            msek = int_na_str(fsek);

        if(agodz == 1) mgodz += "a";

        if(fmiesiac < 10) mmiesiac = "0" + mmiesiac;
        if(fdzien < 10) mdzien = "0" + mdzien;
        if(fgodz < 10) mgodz = "0" + mgodz;
        if(fmin < 10) mmin = "0" + mmin;
        if(fsek < 10) msek = "0" + msek;
}

double LCPKm::data_na_sek(string rok, string miesiac, string dzien, string godziny, string minuty, string sekundy)
{
        double czas_letni[2] = {0,0};
        int bdzien_tygodnia = 0;
        int agodz = 0;
        int lata = 0;
        int dws = 86400;

        mrok = rok;             mgodz = godziny;
        mmiesiac = miesiac;     mmin = minuty;
        mdzien = dzien;         msek = sekundy;

        if((mgodz == "2a")||(mgodz == "02a")) {godziny = "2"; agodz = 1;}
        if((mgodz == "3a")||(mgodz == "03a")) godziny = "3";

        frok = atoi(rok.c_str());             fgodz = atoi(godziny.c_str());        fczas_w_sek = -3600;
        fmiesiac = atoi(miesiac.c_str());     fmin = atoi(minuty.c_str());          frok_przestepny = 0;
        fdzien = atoi(dzien.c_str());         fsek = atoi(sekundy.c_str());         fdzien_tygodnia = 0;

        lata = frok - 1970;

        if(lata >= 0)
        {
                for(int i=0; i<=lata; i++)
                {
                        if((1970+i)%4==0 && (1970+i)%100!=0 || (1970+i)%400==0)
                        {
                                frok_przestepny = 1;
                                if(lata > i) fczas_w_sek += 31622400;
                        }
                        else
                        {
                                frok_przestepny = 0;
                                if(lata > i) fczas_w_sek += 31536000;
                        }
                }

                //zmiana na czas letni
                czas_letni[0] = fczas_w_sek + 83*dws + 7200 + 3600;
                czas_letni[1] = fczas_w_sek + 297*dws + 7200 + 3600;
                if(frok_przestepny == 1) {czas_letni[0] += dws; czas_letni[1] += dws;}
                for(int i=0; i<=6; i++)
                {
                        bdzien_tygodnia = ((czas_letni[0]+i*dws)/dws)+4;
                        bdzien_tygodnia %= 7;
                        if(bdzien_tygodnia == 0) {czas_letni[0] += i*dws; break;}
                }
                for(int i=0; i<=6; i++)
                {
                        bdzien_tygodnia = ((czas_letni[1]+i*dws)/dws)+4;
                        bdzien_tygodnia %= 7;
                        if(bdzien_tygodnia == 0) {czas_letni[1] += i*dws; break;}
                }

                switch(fmiesiac)
                {
                        case 12: fczas_w_sek += 30*dws;
                        case 11: fczas_w_sek += 31*dws;
                        case 10: fczas_w_sek += 30*dws;
                        case 9: fczas_w_sek += 31*dws;
                        case 8: fczas_w_sek += 31*dws;
                        case 7: fczas_w_sek += 30*dws;
                        case 6: fczas_w_sek += 31*dws;
                        case 5: fczas_w_sek += 30*dws;
                        case 4: fczas_w_sek += 31*dws;
                        case 3: {if(frok_przestepny == 0) fczas_w_sek += 28*dws;
                                 else if(frok_przestepny == 1) fczas_w_sek += 29*dws;}
                        case 2: fczas_w_sek += 31*dws;
                        break;
                        default: fczas_w_sek += 0;
                }

                fczas_w_sek += (fdzien - 1)*dws;

                if((czas_letni[0] - 10800 == fczas_w_sek)&&(fgodz == 2)) {fgodz = 3; mgodz = "3";}

                fczas_w_sek += fgodz*3600;
                fczas_w_sek += fmin*60;
                fczas_w_sek += fsek;

                if((fczas_w_sek >= czas_letni[0])&&(fczas_w_sek < czas_letni[1]))
                {
                        fczas_w_sek -= 3600;
                        fdzien_tygodnia = ((fczas_w_sek + 7200)/dws)+4;
                }
                else fdzien_tygodnia = ((fczas_w_sek + 3600)/dws)+4;
                fdzien_tygodnia %= 7;

                if((fczas_w_sek >= czas_letni[1] - 7200)&&(fczas_w_sek < czas_letni[1] - 3600)&&(agodz == 1))
                        fczas_w_sek += 3600;
        }
        else if(lata < 0)
        {
                fczas_w_sek--;
                for(int i=-1; i>=lata; i--)
                {
                        if((1970+i)%4==0 && (1970+i)%100!=0 || (1970+i)%400==0)
                        {
                                frok_przestepny = 1;
                                if(lata < i) fczas_w_sek -= 31622400;
                        }
                        else
                        {
                                frok_przestepny = 0;
                                if(lata < i) fczas_w_sek -= 31536000;
                        }
                }

                //zmiana na czas letni
                czas_letni[0] = fczas_w_sek - 275*dws - 79200 + 3600;
                czas_letni[1] = fczas_w_sek - 61*dws - 79200 + 3600;
                for(int i=0; i<=6; i++)
                {
                        bdzien_tygodnia = (-(czas_letni[0]-i*dws)/dws)+3;
                        bdzien_tygodnia %= 7;
                        bdzien_tygodnia = 6 - bdzien_tygodnia;
                        if(bdzien_tygodnia == 0) {czas_letni[0] -= i*dws; break;}
                }
                for(int i=0; i<=6; i++)
                {
                        bdzien_tygodnia = (-(czas_letni[1]-i*dws)/dws)+3;
                        bdzien_tygodnia %= 7;
                        bdzien_tygodnia = 6 - bdzien_tygodnia;
                        if(bdzien_tygodnia == 0) {czas_letni[1] -= i*dws; break;}
                }

                switch(fmiesiac)
                {
                        case 1: {if(frok_przestepny == 0) fczas_w_sek -= 28*dws;
                                 else if(frok_przestepny == 1) fczas_w_sek -= 29*dws;}
                        case 2: fczas_w_sek -= 31*dws;
                        case 3: fczas_w_sek -= 30*dws;
                        case 4: fczas_w_sek -= 31*dws;
                        case 5: fczas_w_sek -= 30*dws;
                        case 6: fczas_w_sek -= 31*dws;
                        case 7: fczas_w_sek -= 31*dws;
                        case 8: fczas_w_sek -= 30*dws;
                        case 9: fczas_w_sek -= 31*dws;
                        case 10: fczas_w_sek -= 30*dws;
                        case 11: fczas_w_sek -= 31*dws;
                        break;
                        default: fczas_w_sek -= 0;
                }

                switch(fmiesiac)
                {
                        case 1:
                        case 3:
                        case 5:
                        case 7:
                        case 8:
                        case 10:
                        case 12: fczas_w_sek -= (31 - fdzien)*dws;
                        break;
                        case 4:
                        case 6:
                        case 9:
                        case 11: fczas_w_sek -= (30 - fdzien)*dws;
                        break;
                        case 2: {if(frok_przestepny == 0) fczas_w_sek -= (28 - fdzien)*dws;
                                 else fczas_w_sek -= (29 - fdzien)*dws;}
                        break;
                }

                if((czas_letni[0] + 79200 - 3600 == fczas_w_sek)&&(fgodz == 2)) {fgodz = 3; mgodz = "3";}

                fczas_w_sek -= (23 - fgodz)*3600;
                fczas_w_sek -= (59 - fmin)*60;
                fczas_w_sek -= 59 - fsek;

                if((fczas_w_sek - 1 >= czas_letni[0])&&(fczas_w_sek - 1 < czas_letni[1]))
                {
                        fczas_w_sek -= 3600;
                        fdzien_tygodnia = (-(fczas_w_sek + 7200 + 1)/dws)+3;
                }
                else fdzien_tygodnia = (-(fczas_w_sek + 3600 + 1)/dws)+3;
                fdzien_tygodnia %= 7;
                fdzien_tygodnia = 6 - fdzien_tygodnia;

                if((fczas_w_sek - 1 >= czas_letni[1] - 7200)&&(fczas_w_sek - 1 < czas_letni[1] - 3600)&&(agodz == 1))
                        fczas_w_sek += 3600;
        }

        mrok = int_na_str(frok);                mgodz = int_na_str(fgodz);
        mmiesiac = int_na_str(fmiesiac);        mmin = int_na_str(fmin);
        mdzien = int_na_str(fdzien);            msek = int_na_str(fsek);

        if(agodz == 1) mgodz += "a";

        if(fmiesiac < 10) mmiesiac = "0" + mmiesiac;
        if(fdzien < 10) mdzien = "0" + mdzien;
        if(fgodz < 10) mgodz = "0" + mgodz;
        if(fmin < 10) mmin = "0" + mmin;
        if(fsek < 10) msek = "0" + msek;

        return fczas_w_sek;
}

double LCPKm::data_na_sek_c(string data, string godzina)
{
        string b;
        string d, m, r, godz, min, sek;
        d = ""; m = ""; r = ""; godz = ""; min = ""; sek = "";

        b = data[2];

        if((b == "0")||(b == "1")||(b == "2")||(b == "3")||(b == "4")||(b == "5")
                ||(b == "6")||(b == "7")||(b == "8")||(b == "9"))
        {
                d += data[8]; d += data[9];
                m += data[5]; m += data[6];
                r += data[0]; r += data[1]; r += data[2]; r += data[3];
        }
        else
        {
                d += data[0]; d += data[1];
                m += data[3]; m += data[4];
                r += data[6]; r += data[7]; r += data[8]; r += data[9];
        }

        godz += godzina[0]; godz += godzina[1];
        min += godzina[3]; min += godzina[4];
        sek += godzina[6]; sek += godzina[7];

        return data_na_sek(r, m, d, godz, min, sek);
}

bool LCPKm::sprawdzanie_daty(string data, string godzina)
{
/////////////////////////////////////////////////////////
        string d, m, r, godz, min, sek;
        d = ""; m = ""; r = ""; godz = ""; min = ""; sek = "";

        d += data[0]; d += data[1];
        m += data[3]; m += data[4];
        r += data[6]; r += data[7]; r += data[8]; r += data[9];
        godz += godzina[0]; godz += godzina[1];
        min += godzina[3]; min += godzina[4];
        sek += godzina[6]; sek += godzina[7];
/////////////////////////////////////////////////////////

        int rok = atoi(r.c_str());             int godzin = atoi(godz.c_str());
        int miesiac = atoi(m.c_str());         int minut = atoi(min.c_str());
        int dzien = atoi(d.c_str());           int sekund = atoi(sek.c_str());

        if(!((godzin == 2) || ((godzin == 3)&&(minut == 0)&&(sekund == 0)))) return false;

        int lata = 0;
        int dni = 0;
        bool rok_przestepny;
        int czas_letni = 0;
        int dzien_tygodnia = 0;

        lata = rok - 1970;

        if(lata >= 0)
        {
                for(int i=0; i<=lata; i++)
                {
                        if((1970+i)%4==0 && (1970+i)%100!=0 || (1970+i)%400==0)
                        {
                                rok_przestepny = true;
                                if(lata > i) dni += 366;
                        }
                        else
                        {
                                rok_przestepny = false;
                                if(lata > i) dni += 365;
                        }
                }

                czas_letni = dni + 297;
                if(rok_przestepny) czas_letni ++;
                for(int i=0; i<=6; i++)
                {
                        dzien_tygodnia = czas_letni + i + 4;
                        dzien_tygodnia %= 7;
                        if(dzien_tygodnia == 0) {czas_letni += i; break;}
                }

                switch(miesiac)
                {
                        case 12: dni += 30;
                        case 11: dni += 31;
                        case 10: dni += 30;
                        case 9: dni += 31;
                        case 8: dni += 31;
                        case 7: dni += 30;
                        case 6: dni += 31;
                        case 5: dni += 30;
                        case 4: dni += 31;
                        case 3: {if(!(rok_przestepny)) dni += 28;
                                 else if(rok_przestepny) dni += 29;}
                        case 2: dni += 31;
                        break;
                        default: dni += 0;
                }

                dni += dzien - 1;
        }
        else if(lata < 0)
        {
                for(int i=-1; i>=lata; i--)
                {
                        if((1970+i)%4==0 && (1970+i)%100!=0 || (1970+i)%400==0)
                        {
                                rok_przestepny = true;
                                if(lata < i) dni -= 366;
                        }
                        else
                        {
                                rok_przestepny = false;
                                if(lata < i) dni -= 365;
                        }
                }

                czas_letni = dni - 61;
                for(int i=0; i<=6; i++)
                {
                        dzien_tygodnia = -(czas_letni - i) + 3;
                        dzien_tygodnia %= 7;
                        dzien_tygodnia = 6 - dzien_tygodnia;
                        if(dzien_tygodnia == 0) {czas_letni -= i; break;}
                }

                switch(miesiac)
                {
                        case 1: {if(!(rok_przestepny)) dni -= 28;
                                 else if(rok_przestepny) dni -= 29;}
                        case 2: dni -= 31;
                        case 3: dni -= 30;
                        case 4: dni -= 31;
                        case 5: dni -= 30;
                        case 6: dni -= 31;
                        case 7: dni -= 31;
                        case 8: dni -= 30;
                        case 9: dni -= 31;
                        case 10: dni -= 30;
                        case 11: dni -= 31;
                        break;
                        default: dni -= 0;
                }
                switch(miesiac)
                {
                        case 1:
                        case 3:
                        case 5:
                        case 7:
                        case 8:
                        case 10:
                        case 12: dni -= 31 - dzien;
                        break;
                        case 4:
                        case 6:
                        case 9:
                        case 11: dni -= 30 - dzien;
                        break;
                        case 2: {if(!(rok_przestepny)) dni -= 28 - dzien;
                                 else dni -= 29 - dzien;}
                        break;
                }
        }

        if(czas_letni == dni) return true;
        else return false;
}

void LCPKm::tworzenie_pliku(string nazwa_pliku)
{
        HANDLE hplik;
        if(!(czy_plik_istnieje(nazwa_pliku)))
        {
                hplik = CreateFile(nazwa_pliku.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN, NULL);
                CloseHandle(hplik);
        }
}

string LCPKm::szyfrowanie_hasla(string kod_szyfrowania, string haslo)
{
        string bufor1;
        int dlugosc = haslo.size();
        int dlugosc1 = kod_szyfrowania.size();


        if((dlugosc <= 2) || (dlugosc > 300)) return "0";

        if(dlugosc1 < 3) kod_szyfrowania = "cotosazakody";

        string czas = szyfrowanie_czasu(kod_szyfrowania);
        int dlugosc_czas = czas.size();

        int ile_razy1 = 50 + ((czas[0]+0) % 48) + ((czas[1]+0) % 48) + ((czas[2]+0) % 48) + ((kod_szyfrowania[0 % dlugosc1]+0) % 50) + ((kod_szyfrowania[1 % dlugosc1]+0) % 50) + ((kod_szyfrowania[2 % dlugosc1]+0) % 50) + dlugosc1;
        int o_ile_przestawiac = 3 + ((czas[3]+0) % 48) + ((czas[4]+0) % 48) + ((czas[5]+0) % 48) + ((kod_szyfrowania[3 % dlugosc1]+0) % 50) + ((kod_szyfrowania[4 % dlugosc1]+0) % 50) + ((kod_szyfrowania[5 % dlugosc1]+0) % 50) + dlugosc1;
        int ile_razy2 = 55 + ((czas[6]+0) % 48) + ((czas[7]+0) % 48) + ((czas[8]+0) % 48) + ((kod_szyfrowania[6 % dlugosc1]+0) % 50) + ((kod_szyfrowania[7 % dlugosc1]+0) % 50) + ((kod_szyfrowania[8 % dlugosc1]+0) % 50) + dlugosc1;
        int zwiekszanie = 44 + ((czas[9]+0) % 48) + ((czas[10]+0) % 48) + ((czas[11]+0) % 48) + ((kod_szyfrowania[9 % dlugosc1]+0) % 50) + ((kod_szyfrowania[10 % dlugosc1]+0) % 50) + ((kod_szyfrowania[11 % dlugosc1]+0) % 50) + dlugosc1;

        int pozycja_kodu = (10 + ((kod_szyfrowania[9 % dlugosc1]+0) % 50) + ((kod_szyfrowania[10 % dlugosc1]+0) % 50) + ((kod_szyfrowania[11 % dlugosc1]+0) % 50) + dlugosc1) % (910 - (dlugosc * 3));
        int pozycja_czasu = pozycja_kodu + dlugosc * 3 + ((((kod_szyfrowania[6 % dlugosc1]+0) % 50) + ((kod_szyfrowania[7 % dlugosc1]+0) % 50) + ((kod_szyfrowania[8 % dlugosc1]+0) % 50) + dlugosc1) % (999 - (pozycja_kodu + dlugosc * 3 + czas.size())));
        int o_ile_przestawiac_wyjscie = 35 + ((kod_szyfrowania[3 % dlugosc1]+0) % 50) + ((kod_szyfrowania[4 % dlugosc1]+0) % 50) + ((kod_szyfrowania[5 % dlugosc1]+0) % 50) + dlugosc1;
        int ile_razy_wyjscie = 125 + ((kod_szyfrowania[0 % dlugosc1]+0) % 50) + ((kod_szyfrowania[1 % dlugosc1]+0) % 50) + ((kod_szyfrowania[2 % dlugosc1]+0) % 50) + dlugosc1;
        int zwiekszanie_wyjscie = 55 + ((kod_szyfrowania[0 % dlugosc1]+0) % 50) + ((kod_szyfrowania[1 % dlugosc1]+0) % 50) + ((kod_szyfrowania[2 % dlugosc1]+0) % 50) + dlugosc1;

        //1000 znakow
        string duza_liczba = "7360837797965891329008010772123581873681867571728844540915884479609972768541760078408862570103616870003548721104244459120468";
        duza_liczba += "973751366477348173770367296327353948705477504734796754738375725640000021683728516189541980034380395074570076095202774274718499100023389";
        duza_liczba += "4364574206811023254407570563020885301006582836997846844006364998191771788540070692775420900708510525091104739728188438197";
        duza_liczba += "4775719733296076707446626111920296415224140471477872897143307049876334475524773341344294575658375076758873066334106";
        duza_liczba += "84004002764387350324013985122111758235702225070408298447578521654764373376743447031634482721378109808681453730359670090";
        duza_liczba += "34089145237606071211776730483746071409522700204074386740016020569468827741885450630020458662338585864008974671748742373388353444390";
        duza_liczba += "545750417110042717546871075976335778447888031863045753080198470707400927862477309814761431701176751762495643270405786370";
        duza_liczba += "953041253784853003828217570807209336348766098707052537346900273448801082023362247948377837569062208134090272467492747173277617104375265";

        for(int i = 0; i < 1000 * ile_razy2; i++)
        {
                int przestawianie = i % 1000;
                o_ile_przestawiac = (o_ile_przestawiac + kod_szyfrowania[i % dlugosc1] + czas[i % dlugosc_czas]) % 1000;
                bufor1 = duza_liczba[przestawianie];
                duza_liczba[przestawianie] = duza_liczba[((przestawianie + o_ile_przestawiac) % 1000)];
                duza_liczba[((przestawianie + o_ile_przestawiac) % 1000)] = bufor1[0];
        }



        o_ile_przestawiac %= dlugosc;
        if((o_ile_przestawiac == 0) || (o_ile_przestawiac == dlugosc / 2)) o_ile_przestawiac ++;

        //przestawianie znakow

        for(int i = 0; i < dlugosc * ile_razy1; i++)
        {
                int przestawianie = i % dlugosc;
                o_ile_przestawiac = (o_ile_przestawiac + kod_szyfrowania[i % dlugosc1] + czas[i % dlugosc_czas]) % dlugosc;
                bufor1 = haslo[przestawianie];
                haslo[przestawianie] = haslo[((przestawianie + o_ile_przestawiac) % dlugosc)];
                haslo[((przestawianie + o_ile_przestawiac) % dlugosc)] = bufor1[0];
        }

        //zmienianie wartosci znakow
        zwiekszanie = (zwiekszanie % 643) + 100;
        int *bufor2 = new int[dlugosc];
        for(int i = 0; i < dlugosc; i++)
        {
                bufor2[i] = haslo[i];
        }
        for(int i = 0; i < dlugosc * ile_razy2; i++)
        {
                int przestawianie = i % dlugosc;
                bufor2[przestawianie] = ((bufor2[przestawianie] + zwiekszanie) % 899) + 100;
                zwiekszanie = (zwiekszanie + kod_szyfrowania[i % dlugosc1] + czas[i % dlugosc_czas]) % 899;
        }

        //mieszanie cyfr
        string bufor3 = "";
        for(int i = 0; i < dlugosc; i++)
        {
                bufor3 += int_na_str(bufor2[i]);
        }

        dlugosc = bufor3.size();
        for(int i = 0; i < dlugosc * ile_razy1; i++)
        {
                int przestawianie = i % dlugosc;
                o_ile_przestawiac = (o_ile_przestawiac + kod_szyfrowania[i % dlugosc1] + czas[i % dlugosc_czas]) % dlugosc;
                bufor1 = bufor3[przestawianie];
                bufor3[przestawianie] = bufor3[((przestawianie + o_ile_przestawiac) % dlugosc)];
                bufor3[((przestawianie + o_ile_przestawiac) % dlugosc)] = bufor1[0];
        }


        //wstawianie zaszyfrowanego hasla i czasu do liczby z 1000 znakow
        string wyjscie1 = "";

        for(int i = 0; i < pozycja_kodu; i++)
        {
                wyjscie1 += duza_liczba[i];
        }
        for(int i = 0; i < dlugosc; i++)
        {
                wyjscie1 += bufor3[i];
        }
        for(int i = pozycja_kodu + dlugosc; i < pozycja_czasu; i++)
        {
                wyjscie1 += duza_liczba[i];
        }
        for(int i = 0; i < czas.size(); i++)
        {
                wyjscie1 += czas[i];
        }
        for(int i = pozycja_czasu + czas.size(); i < 1000; i++)
        {
                wyjscie1 += duza_liczba[i];
        }

        string wyjscie2 = wyjscie1;

        dlugosc = wyjscie1.size();
        for(int i = 0; i < dlugosc * ile_razy_wyjscie; i++)
        {
                int przestawianie = i % dlugosc;
                o_ile_przestawiac_wyjscie = (o_ile_przestawiac_wyjscie + kod_szyfrowania[i % dlugosc1]) % dlugosc;
                bufor1 = wyjscie2[przestawianie];
                wyjscie2[przestawianie] = wyjscie2[((przestawianie + o_ile_przestawiac_wyjscie) % dlugosc)];
                wyjscie2[((przestawianie + o_ile_przestawiac_wyjscie) % dlugosc)] = bufor1[0];
        }

        string wyjscie3 = wyjscie2;
        int *bufor4 = new int[dlugosc];
        for(int i = 0; i < dlugosc; i++)
        {
                bufor4[i] = wyjscie3[i];
        }
        for(int i = 0; i < dlugosc * ile_razy_wyjscie; i++)
        {
                int przestawianie = i % dlugosc;
                bufor4[przestawianie] = ((bufor4[przestawianie] + zwiekszanie_wyjscie) % 94);
                zwiekszanie_wyjscie = (zwiekszanie_wyjscie + kod_szyfrowania[i % dlugosc1]) % 94;
        }

        wyjscie3 = "";
        for(int i = 0; i < dlugosc; i++)
        {
                wyjscie3 += bufor4[i] + 33;
        }

        delete [] bufor2;
        delete [] bufor4;

        return wyjscie3;
}

string LCPKm::szyfrowanie_czasu(string kod_szyfrowania)
{
        int dlugosc1 = kod_szyfrowania.size();

        int ile_razy_czas = 50 + ((kod_szyfrowania[0 % dlugosc1]+0) % 50) + ((kod_szyfrowania[1 % dlugosc1]+0) % 50) + ((kod_szyfrowania[2 % dlugosc1]+0) % 50) + dlugosc1;
        int zwiekszanie_czas = 100 + ((kod_szyfrowania[6 % dlugosc1]+0) % 50) + ((kod_szyfrowania[7 % dlugosc1]+0) % 50) + ((kod_szyfrowania[8 % dlugosc1]+0) % 50) + dlugosc1;
        int o_ile_przestawiac_czas = 5 + ((kod_szyfrowania[3 % dlugosc1]+0) % 50) + ((kod_szyfrowania[4 % dlugosc1]+0) % 50) + ((kod_szyfrowania[5 % dlugosc1]+0) % 50) + dlugosc1;


        time_t czas;
        time(&czas);

        int czas1 = czas % 1000000000 + 1000000000;

        string czas2 = "";
        string bufor_czas2 = int_na_str(czas1);
        if(bufor_czas2.size() == 10)
        {
                czas2 += bufor_czas2[0]; czas2 += bufor_czas2[7]; czas2 += bufor_czas2[8]; czas2 += bufor_czas2[9];
                for(int i = 4; i < 10; i++) czas2 += bufor_czas2[i];
        }

        int czas_dlugosc = czas2.size();

        o_ile_przestawiac_czas %= czas_dlugosc;
        if((o_ile_przestawiac_czas == 0) || (o_ile_przestawiac_czas == czas_dlugosc / 2)) o_ile_przestawiac_czas ++;

        int *bufor_czas = new int[czas_dlugosc];
        for(int i = 0; i < czas_dlugosc; i++)
        {
                bufor_czas[i] = czas2[i];
        }
        for(int i = 0; i < czas_dlugosc * ile_razy_czas; i++)
        {
                int przestawianie = i % czas_dlugosc;
                bufor_czas[przestawianie] = ((bufor_czas[przestawianie] + zwiekszanie_czas) % 899) + 100;
                zwiekszanie_czas = (zwiekszanie_czas + kod_szyfrowania[i % dlugosc1]) % 899;
        }

        string bufor1 = "";
        for(int i = 0; i < czas_dlugosc; i++)
        {
                bufor1 += int_na_str(bufor_czas[i]);
        }

        czas_dlugosc = bufor1.size();

        if((o_ile_przestawiac_czas == 0) || (o_ile_przestawiac_czas == czas_dlugosc / 2)) o_ile_przestawiac_czas ++;

        string bufor2;
        for(int i = 0; i < czas_dlugosc * ile_razy_czas; i++)
        {
                int przestawianie = i % czas_dlugosc;
                o_ile_przestawiac_czas = (o_ile_przestawiac_czas + kod_szyfrowania[i % dlugosc1]) % czas_dlugosc;
                bufor2 = bufor1[przestawianie];
                bufor1[przestawianie] = bufor1[((przestawianie + o_ile_przestawiac_czas) % czas_dlugosc)];
                bufor1[((przestawianie + o_ile_przestawiac_czas) % czas_dlugosc)] = bufor2[0];
        }

        delete [] bufor_czas;

        return bufor1;
}

bool LCPKm::zgodnosc_hasla_z_zaszyfrowanym_haslem(string kod_szyfrowania, string zaszyfrowane_haslo, string haslo)
{
        int dlugosc = haslo.size();
        int dlugosc1 = kod_szyfrowania.size();
        int dlugosc2 = zaszyfrowane_haslo.size();
        if(dlugosc2 != 1000) return false;

        int pozycja_kodu = (10 + ((kod_szyfrowania[9 % dlugosc1]+0) % 50) + ((kod_szyfrowania[10 % dlugosc1]+0) % 50) + ((kod_szyfrowania[11 % dlugosc1]+0) % 50) + dlugosc1) % (910 - (dlugosc * 3));
        int pozycja_czasu = pozycja_kodu + dlugosc * 3 + ((((kod_szyfrowania[6 % dlugosc1]+0) % 50) + ((kod_szyfrowania[7 % dlugosc1]+0) % 50) + ((kod_szyfrowania[8 % dlugosc1]+0) % 50) + dlugosc1) % (999 - (pozycja_kodu + dlugosc * 3 + 30)));
        int o_ile_przestawiac_wyjscie = 35 + ((kod_szyfrowania[3 % dlugosc1]+0) % 50) + ((kod_szyfrowania[4 % dlugosc1]+0) % 50) + ((kod_szyfrowania[5 % dlugosc1]+0) % 50) + dlugosc1;
        int ile_razy_wyjscie = 125 + ((kod_szyfrowania[0 % dlugosc1]+0) % 50) + ((kod_szyfrowania[1 % dlugosc1]+0) % 50) + ((kod_szyfrowania[2 % dlugosc1]+0) % 50) + dlugosc1;
        int zwiekszanie_wyjscie = 55 + ((kod_szyfrowania[0 % dlugosc1]+0) % 50) + ((kod_szyfrowania[1 % dlugosc1]+0) % 50) + ((kod_szyfrowania[2 % dlugosc1]+0) % 50) + dlugosc1;


        int *etap1 = new int[dlugosc2];
        for(int i = 0; i < dlugosc2; i++)
        {
                etap1[i] = zaszyfrowane_haslo[i] - 33;
        }

        int *etap2 = new int[dlugosc2];
        for(int i = 0; i < dlugosc2; i++)
        {
                etap2[i] = 0;
        }
        for(int i = 0; i < dlugosc2 * ile_razy_wyjscie; i++)
        {
                int przestawianie = i % dlugosc2;
                etap2[przestawianie] = ((etap2[przestawianie] + zwiekszanie_wyjscie) % 94);
                zwiekszanie_wyjscie = (zwiekszanie_wyjscie + kod_szyfrowania[i % dlugosc1]) % 94;
        }

        for(int i = 0; i < dlugosc2; i++)
        {
                etap2[i] = ((etap1[i] - etap2[i]) + 94) % 94;
        }

        string etap3 = "";
        for(int i = 0; i < dlugosc2; i++)
        {
                etap3 += etap2[i];
        }

        for(int i = 0; i < dlugosc2 * ile_razy_wyjscie; i++)
        {
                o_ile_przestawiac_wyjscie = (o_ile_przestawiac_wyjscie + kod_szyfrowania[i % dlugosc1]) % dlugosc2;
        }

        string bufor1;
        for(int i = dlugosc2 - 1 + dlugosc2 * (ile_razy_wyjscie - 1); i >= 0 ; i--)
        {
                int przestawianie = i % dlugosc2;
                bufor1 = etap3[przestawianie];
                etap3[przestawianie] = etap3[((przestawianie + o_ile_przestawiac_wyjscie) % dlugosc2)];
                etap3[((przestawianie + o_ile_przestawiac_wyjscie) % dlugosc2)] = bufor1[0];
                o_ile_przestawiac_wyjscie = (o_ile_przestawiac_wyjscie - kod_szyfrowania[i % dlugosc1] + dlugosc2) % dlugosc2;
        }

        delete [] etap1;
        delete [] etap2;

        string etap4 = "";
        for(int i = pozycja_czasu; i < pozycja_czasu + 30; i++)
        {
                etap4 += etap3[i];
        }


        string czas = etap4;
        int dlugosc_czas = czas.size();

        int ile_razy1 = 50 + ((czas[0]+0) % 48) + ((czas[1]+0) % 48) + ((czas[2]+0) % 48) + ((kod_szyfrowania[0 % dlugosc1]+0) % 50) + ((kod_szyfrowania[1 % dlugosc1]+0) % 50) + ((kod_szyfrowania[2 % dlugosc1]+0) % 50) + dlugosc1;
        int o_ile_przestawiac = 3 + ((czas[3]+0) % 48) + ((czas[4]+0) % 48) + ((czas[5]+0) % 48) + ((kod_szyfrowania[3 % dlugosc1]+0) % 50) + ((kod_szyfrowania[4 % dlugosc1]+0) % 50) + ((kod_szyfrowania[5 % dlugosc1]+0) % 50) + dlugosc1;
        int ile_razy2 = 55 + ((czas[6]+0) % 48) + ((czas[7]+0) % 48) + ((czas[8]+0) % 48) + ((kod_szyfrowania[6 % dlugosc1]+0) % 50) + ((kod_szyfrowania[7 % dlugosc1]+0) % 50) + ((kod_szyfrowania[8 % dlugosc1]+0) % 50) + dlugosc1;
        int zwiekszanie = 44 + ((czas[9]+0) % 48) + ((czas[10]+0) % 48) + ((czas[11]+0) % 48) + ((kod_szyfrowania[9 % dlugosc1]+0) % 50) + ((kod_szyfrowania[10 % dlugosc1]+0) % 50) + ((kod_szyfrowania[11 % dlugosc1]+0) % 50) + dlugosc1;

        //1000 znakow
        string duza_liczba = "7360837797965891329008010772123581873681867571728844540915884479609972768541760078408862570103616870003548721104244459120468";
        duza_liczba += "973751366477348173770367296327353948705477504734796754738375725640000021683728516189541980034380395074570076095202774274718499100023389";
        duza_liczba += "4364574206811023254407570563020885301006582836997846844006364998191771788540070692775420900708510525091104739728188438197";
        duza_liczba += "4775719733296076707446626111920296415224140471477872897143307049876334475524773341344294575658375076758873066334106";
        duza_liczba += "84004002764387350324013985122111758235702225070408298447578521654764373376743447031634482721378109808681453730359670090";
        duza_liczba += "34089145237606071211776730483746071409522700204074386740016020569468827741885450630020458662338585864008974671748742373388353444390";
        duza_liczba += "545750417110042717546871075976335778447888031863045753080198470707400927862477309814761431701176751762495643270405786370";
        duza_liczba += "953041253784853003828217570807209336348766098707052537346900273448801082023362247948377837569062208134090272467492747173277617104375265";

        for(int i = 0; i < 1000 * ile_razy2; i++)
        {
                int przestawianie = i % 1000;
                o_ile_przestawiac = (o_ile_przestawiac + kod_szyfrowania[i % dlugosc1] + czas[i % dlugosc_czas]) % 1000;
                bufor1 = duza_liczba[przestawianie];
                duza_liczba[przestawianie] = duza_liczba[((przestawianie + o_ile_przestawiac) % 1000)];
                duza_liczba[((przestawianie + o_ile_przestawiac) % 1000)] = bufor1[0];
        }



        o_ile_przestawiac %= dlugosc;
        if((o_ile_przestawiac == 0) || (o_ile_przestawiac == dlugosc / 2)) o_ile_przestawiac ++;

        //przestawianie znakow

        for(int i = 0; i < dlugosc * ile_razy1; i++)
        {
                int przestawianie = i % dlugosc;
                o_ile_przestawiac = (o_ile_przestawiac + kod_szyfrowania[i % dlugosc1] + czas[i % dlugosc_czas]) % dlugosc;
                bufor1 = haslo[przestawianie];
                haslo[przestawianie] = haslo[((przestawianie + o_ile_przestawiac) % dlugosc)];
                haslo[((przestawianie + o_ile_przestawiac) % dlugosc)] = bufor1[0];
        }

        //zmienianie wartosci znakow
        zwiekszanie = (zwiekszanie % 643) + 100;
        int *bufor2 = new int[dlugosc];
        for(int i = 0; i < dlugosc; i++)
        {
                bufor2[i] = haslo[i];
        }
        for(int i = 0; i < dlugosc * ile_razy2; i++)
        {
                int przestawianie = i % dlugosc;
                bufor2[przestawianie] = ((bufor2[przestawianie] + zwiekszanie) % 899) + 100;
                zwiekszanie = (zwiekszanie + kod_szyfrowania[i % dlugosc1] + czas[i % dlugosc_czas]) % 899;
        }

        //mieszanie cyfr
        string bufor3 = "";
        for(int i = 0; i < dlugosc; i++)
        {
                bufor3 += int_na_str(bufor2[i]);
        }

        dlugosc = bufor3.size();
        for(int i = 0; i < dlugosc * ile_razy1; i++)
        {
                int przestawianie = i % dlugosc;
                o_ile_przestawiac = (o_ile_przestawiac + kod_szyfrowania[i % dlugosc1] + czas[i % dlugosc_czas]) % dlugosc;
                bufor1 = bufor3[przestawianie];
                bufor3[przestawianie] = bufor3[((przestawianie + o_ile_przestawiac) % dlugosc)];
                bufor3[((przestawianie + o_ile_przestawiac) % dlugosc)] = bufor1[0];
        }


        //wstawianie zaszyfrowanego hasla i czasu do liczby z 1000 znakow
        string wyjscie1 = "";

        for(int i = 0; i < pozycja_kodu; i++)
        {
                wyjscie1 += duza_liczba[i];
        }
        for(int i = 0; i < dlugosc; i++)
        {
                wyjscie1 += bufor3[i];
        }
        for(int i = pozycja_kodu + dlugosc; i < pozycja_czasu; i++)
        {
                wyjscie1 += duza_liczba[i];
        }
        for(int i = 0; i < czas.size(); i++)
        {
                wyjscie1 += czas[i];
        }
        for(int i = pozycja_czasu + czas.size(); i < 1000; i++)
        {
                wyjscie1 += duza_liczba[i];
        }

        delete [] bufor2;

        if(etap3 == wyjscie1) return true;

        return false;
}

string LCPKm::losowe_haslo(string kod_szyfrowania, string haslo)
{
    string bufor1;
    int dlugosc = haslo.size();
    int dlugosc1 = kod_szyfrowania.size();


    if((dlugosc <= 2) || (dlugosc > 300)) return "0";

    if(dlugosc1 < 3) kod_szyfrowania = "cotosazakody";

    string czas = szyfrowanie_czasu(kod_szyfrowania);
    int dlugosc_czas = czas.size();

    cout << endl << "Wyjscie czas: " << czas << endl;

    int o_ile_przestawiac = 3 + ((czas[3]+0) % 48) + ((czas[4]+0) % 48) + ((czas[5]+0) % 48) + ((kod_szyfrowania[3 % dlugosc1]+0) % 50) + ((kod_szyfrowania[4 % dlugosc1]+0) % 50) + ((kod_szyfrowania[5 % dlugosc1]+0) % 50) + dlugosc1 + ((haslo[0 % dlugosc]+0) % 50) + ((haslo[1 % dlugosc]+0) % 50) + ((haslo[2 % dlugosc]+0) % 50) + dlugosc;
    int ile_razy2 = 55 + ((czas[6]+0) % 48) + ((czas[7]+0) % 48) + ((czas[8]+0) % 48) + ((kod_szyfrowania[6 % dlugosc1]+0) % 50) + ((kod_szyfrowania[7 % dlugosc1]+0) % 50) + ((kod_szyfrowania[8 % dlugosc1]+0) % 50) + dlugosc1 + ((haslo[0 % dlugosc]+0) % 50) + ((haslo[1 % dlugosc]+0) % 50) + ((haslo[2 % dlugosc]+0) % 50) + dlugosc;

    //1000 znakow
    string duza_liczba = "7360837797965891329008010772123581873681867571728844540915884479609972768541760078408862570103616870003548721104244459120468";
    duza_liczba += "973751366477348173770367296327353948705477504734796754738375725640000021683728516189541980034380395074570076095202774274718499100023389";
    duza_liczba += "4364574206811023254407570563020885301006582836997846844006364998191771788540070692775420900708510525091104739728188438197";
    duza_liczba += "4775719733296076707446626111920296415224140471477872897143307049876334475524773341344294575658375076758873066334106";
    duza_liczba += "84004002764387350324013985122111758235702225070408298447578521654764373376743447031634482721378109808681453730359670090";
    duza_liczba += "34089145237606071211776730483746071409522700204074386740016020569468827741885450630020458662338585864008974671748742373388353444390";
    duza_liczba += "545750417110042717546871075976335778447888031863045753080198470707400927862477309814761431701176751762495643270405786370";
    duza_liczba += "953041253784853003828217570807209336348766098707052537346900273448801082023362247948377837569062208134090272467492747173277617104375265";

    for(int i = 0; i < 1000 * ile_razy2; i++)
    {
        int przestawianie = i % 1000;
        o_ile_przestawiac = (o_ile_przestawiac + kod_szyfrowania[i % dlugosc1] + czas[i % dlugosc_czas]) % 1000;
        bufor1 = duza_liczba[przestawianie];
        duza_liczba[przestawianie] = duza_liczba[((przestawianie + o_ile_przestawiac) % 1000)];
        duza_liczba[((przestawianie + o_ile_przestawiac) % 1000)] = bufor1[0];
    }

    return duza_liczba;
}

bool LCPKm::instalacja_do_autostartu()
{
      bool wynik_dzialania_funkcji = instalacja_do_autostartu1();
      DeleteFile("Plik_pomocniczy.txt");
      return wynik_dzialania_funkcji;
}

bool LCPKm::instalacja_do_autostartu1()
{
        string bufor1;
        string bufor2;
        string sciezka;

        sciezka = sciezka_skrotu_w_autostarcie();

        system("cd > Plik_pomocniczy.txt");

        plik.open("Plik_pomocniczy.txt", ios::in);
        if((plik.good()) && (!(plik.eof())))
        {
                getline(plik, bufor1);
                plik.close();
                plik.clear();
        }
        else
        {
                plik.close();
                plik.clear();
                return false;
        }

        bufor2 = "cd /d \"" + bufor1 + "\"";

        plik.open(sciezka.c_str(), ios::out);

        plik<<"@echo off"<<endl;
        plik<<bufor2<<endl;
        plik<<"start LCPK.exe";

        plik.close();
        plik.clear();

        if(czy_plik_istnieje(sciezka)) return true;
        else return false;
}

string LCPKm::sciezka_skrotu_w_autostarcie()
{
        char sciezka[1000];
        string sciezka1;
        SHGetSpecialFolderPath(NULL, sciezka, CSIDL_STARTUP, 0);
        sciezka1 = sciezka;

        return sciezka1 + "\\LCPK_skrot.bat";
}

bool LCPKm::sprawdzenie_czy_program_jest_juz_uruchomiony(string nazwa_programu)
{
        bool wynik = false;
        string cale_polecenie;
        string bufor1;

        cale_polecenie = "tasklist | find \"";
        cale_polecenie += nazwa_programu.c_str();
        cale_polecenie += "\" > Plik_pomocniczy.txt";

        system(cale_polecenie.c_str());

        plik.open("Plik_pomocniczy.txt", ios::in);

        if((plik.good()) && (!(plik.eof())))
        {
                getline(plik, bufor1);
                if(!plik.eof())
                {
                        getline(plik, bufor1);
                        if(bufor1.size() >= nazwa_programu.size()) wynik = true;
                }
        }
        plik.close();
        plik.clear();

        DeleteFile("Plik_pomocniczy.txt");

        return wynik;
}
