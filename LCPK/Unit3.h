//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include <fstream>

class TForm3 : public TForm
{
__published:	// IDE-managed Components
        TMemo *Lista_aktywnosci;
        TMainMenu *MainMenu1;
        TMenuItem *Opcje1;
        TMenuItem *Wy1;
        TMenuItem *Wykazaktywnoci1;
        TMenuItem *Aktywno1;
        TMenuItem *Dziaaniauytkownika1;
        TMenuItem *Usuhistorie1;
        TMenuItem *Aktywno2;
        TMenuItem *Dziaaniauytkownika2;
        TMenuItem *N1;
        TMenuItem *Usucahistio1;
        TMenuItem *N2;
        TMenuItem *Zmianaczcionki1;
        TMenuItem *N4;
        TFontDialog *FontDialog1;
        TMenuItem *Niezapisujtejaktywnoci1;
        TMenuItem *N3;
        void __fastcall Wykazaktywnoci1Click(TObject *Sender);
        void __fastcall Dziaaniauytkownika1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Zmianaczcionki1Click(TObject *Sender);
        void __fastcall Aktywno1Click(TObject *Sender);
        void __fastcall Aktywno2Click(TObject *Sender);
        void __fastcall Dziaaniauytkownika2Click(TObject *Sender);
        void __fastcall Usucahistio1Click(TObject *Sender);
        void __fastcall Niezapisujtejaktywnoci1Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm3(TComponent* Owner);

        std::fstream plik3;

        int c;
        int w[2];
        int d;

        TStringList *Lista_aktywnosci_plik;
        TStringList *Dzialania_uzytkownika_plik;

        void wyswietlenie_danych(AnsiString nazwa_pliku);
        bool dane_na_liste_aktywnosci(); //tworzy plik "Dane/Lista_aktywnosci.txt" na podstawie "Dane/Dane.txt"
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
