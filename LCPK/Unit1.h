//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "trayicon.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include <time.h>
#include <fstream>

class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Czas1;
        TTimer *Zegar;
        TMainMenu *MainMenu1;
        TMenuItem *Opcje1;
        TLabel *Napis1;
        TLabel *Czas2;
        TLabel *Napis2;
        TMenuItem *Czstotliwo1;
        TMenuItem *minuty1;
        TMenuItem *minuty2;
        TMenuItem *minuty5;
        TMenuItem *minuty10;
        TMenuItem *minuty15;
        TMenuItem *minuty30;
        TMenuItem *minuty60;
        TMenuItem *Widoczno1;
        TMenuItem *Minimalizujdotreya1;
        TMenuItem *Trybninja1;
        TMenuItem *Widok1;
        TMenuItem *Aktualnyczas1;
        TMenuItem *Zapiszczas1;
        TMenuItem *Aktywno1;
        TMenuItem *Calkowityczaspracy1;
        TMenuItem *Czaspracyoddaty1;
        TMenuItem *Niepokazujdaty1;
        TMenuItem *Dataigodzina1;
        TMenuItem *Ustawdate1;
        TMenuItem *Pokazdate1;
        TMenuItem *N1;
        TMenuItem *N3;
        TLabel *Czas3;
        TLabel *Napis3;
        TTrayIcon *TrayIcon1;
        TMenuItem *Minimalizuj1;
        TMenuItem *N2;
        TMenuItem *Zakoncz;
        TMenuItem *N4;
        TMenuItem *Narzdzia1;
        TMenuItem *Zainstalujdoautostartu1;
        TMenuItem *N5;
        TMenuItem *Odinstalujzautostartu1;
        TMenuItem *Zmiehaso1;
        TMenuItem *N6;
        void __fastcall ZegarTimer(TObject *Sender);
        void __fastcall Zapiszczas1Click(TObject *Sender);
        void __fastcall minuty1Click(TObject *Sender);
        void __fastcall minuty2Click(TObject *Sender);
        void __fastcall minuty5Click(TObject *Sender);
        void __fastcall minuty10Click(TObject *Sender);
        void __fastcall minuty15Click(TObject *Sender);
        void __fastcall minuty30Click(TObject *Sender);
        void __fastcall minuty60Click(TObject *Sender);
        void __fastcall Minimalizujdotreya1Click(TObject *Sender);
        void __fastcall Trybninja1Click(TObject *Sender);
        void __fastcall TrayIcon1Click(TObject *Sender);
        void __fastcall Aktualnyczas1Click(TObject *Sender);
        void __fastcall Calkowityczaspracy1Click(TObject *Sender);
        void __fastcall Pokazdate1Click(TObject *Sender);
        void __fastcall Dataigodzina1Click(TObject *Sender);
        void __fastcall Niepokazujdaty1Click(TObject *Sender);
        void __fastcall Aktywno1Click(TObject *Sender);
        void __fastcall Ustawdate1Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ZakonczClick(TObject *Sender);
        void __fastcall Zainstalujdoautostartu1Click(TObject *Sender);
        void __fastcall Odinstalujzautostartu1Click(TObject *Sender);
        void __fastcall Zmiehaso1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);

        std::fstream plik;

        int nieprawidlowe_podania_hasla;

        bool czy_stworzono_folder;

        double nadwyzkowy_czas;

        int s[3];
        int x[3];

        AnsiString ustawienia[9];

        time_t t_data;
        AnsiString astr_data, astr_godzina;

        int autozapis;
        time_t czas_roz;

        AnsiString arok, amiesiac, adzien, agodz, amin, asek;
        AnsiString fbufor[7];

        int licznik[2];

        int ustawianie_autozapisu(int co_ile_zapis);
        void przycisk_autozapisu(int co_ile_zapis);
        void ustawianie_widocznosci();
        void przycisk_widocznosci(AnsiString ustawienia1, AnsiString ustawienia2, AnsiString ustawienia3, AnsiString tekst);
        void ustawianie_pokazywania();
        void przycisk_pokazywania(int numer_ustawienia, AnsiString ustaw_na, AnsiString tekst);

        void wprowadzenie_ustawien();
        void zapis_ustawien();
        void ustawianie_daty(double czas);

        void tworzenie_plikow();

        void sek_na_date(double czas_w_sek);
        void data_na_sek(AnsiString rok, AnsiString miesiac, AnsiString dzien, AnsiString godziny, AnsiString minuty, AnsiString sekundy);

        void tworzenie_bufora_danych_poprzedniej_aktywnosci();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
 