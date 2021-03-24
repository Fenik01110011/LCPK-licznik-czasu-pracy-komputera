//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#endif

#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

class LCPKm
{

    int tlat, tdni, tgodzin, tminut, tsekund;
    string tl, td, tgodz, tmin, tsek;

    string bufor;

    fstream plik;

public:

    //zmienne funkcji czasu
    int frok_przestepny, frok, fmiesiac, fdzien, fgodz, fmin, fsek, fdzien_tygodnia;
    double fczas_w_sek;
    string mrok, mmiesiac, mdzien, mgodz, mmin, msek;



    LCPKm();

    string int_na_str(int liczba);

    string sek_na_czas(int ss);

    void zapis_danych(char nazwa_pliku[], time_t czas_roz, int czas_dzialania,
                        int czas_calkowity, int co_ile_zapis, string sposob_zapisu);
    string odczyt_danych(char nazwa_pliku[], int pozycja); //pozycja - numer lini na ktorej znajduje sie zmienna do odczytu
    void dodanie_danych(); //dodaje dane do "Dane/Dane.txt" i "Dane/Lista_aktywnosci.txt"
    void odnotowanie_dzialan_uzytkownika(char nazwa_pliku[], int rodzaj_ustawien, string tekst);
    bool czy_plik_istnieje(string sciezka_pliku);

    int pozycja_napisu(int ilosc_napisow, int ktory);

    void sek_na_date(double czas_w_sek);
    double data_na_sek(string rok, string miesiac, string dzien, string godziny, string minuty, string sekundy);
    double data_na_sek_c(string data, string godzina);

    bool sprawdzanie_daty(string data, string godzina); //zwraca prawde jesli podana data jest w przedziale z mozliwoscia dopisania 'a'

    void tworzenie_pliku(string nazwa_pliku);

    string szyfrowanie_hasla(string kod_szyfrowania, string haslo);
    string szyfrowanie_czasu(string kod_szyfrowania);
    bool zgodnosc_hasla_z_zaszyfrowanym_haslem(string kod_szyfrowania, string zaszyfrowane_haslo, string haslo);

    string losowe_haslo(string kod_szyfrowania, string haslo);

    bool instalacja_do_autostartu();
    bool instalacja_do_autostartu1();
    string sciezka_skrotu_w_autostarcie();

    bool sprawdzenie_czy_program_jest_juz_uruchomiony(string nazwa_programu);
};
