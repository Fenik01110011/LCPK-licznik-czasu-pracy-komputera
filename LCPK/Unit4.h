//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <fstream>

class TForm4 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TDateTimePicker *DateTimePicker1;
        TDateTimePicker *DateTimePicker2;
        TDateTimePicker *DateTimePicker3;
        TDateTimePicker *DateTimePicker4;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm4(TComponent* Owner);

        std::fstream plik4;

        int rezultat;
        AnsiString blad_napis;
        int wynik_wawp;
        AnsiString pobrana_data[2];
        AnsiString pobrana_godzina[2];
        bool wybor_daty[2];

//////////////////////////////////////////////////////////////////////////////

        double cws[2];

        int ilosc_wierszy;
        int znaleziono[2];
        int nr_wiersza_b[2];
        int gdzie_znaleziono[2];
        int ilosc_aktywnosci;
        double czas_bufor[4];
        double czas_poczatkowy; //kiedy nastapila pierwsza aktywnosc w tym przedziale czasowym
        double czas_koncowy; //kiedy nastapila ostatnia aktywnosc w tym przedziale czasowym
        double calkowity_czas_b[2];
        int calkowity_czas_r;
        int najdluzszy_czas;
        AnsiString najdluzszy_czas_czas;
        AnsiString najdluzszy_czas_data[2];
        bool poprawnosc_dane;
        bool poprawnosc_bufor_danych;
        bool poprawnosc_lista_aktywnosci;

//////////////////////////////////////////////////////////////////////////////

        int sprawdzanie_aktywnosci_w_przedziale(AnsiString data1, AnsiString godzina1, AnsiString data2, AnsiString godzina2);
        void wyswietlanie_aktywnosci_w_przedziale();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
