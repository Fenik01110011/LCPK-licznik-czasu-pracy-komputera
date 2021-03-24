//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit7.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"

TForm7 *Form7;

//---------------------------------------------------------------------------
__fastcall TForm7::TForm7(TComponent* Owner)
        : TForm(Owner)
{
        co_wybrac = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm7::FormActivate(TObject *Sender)
{
        Edit1->Text = "";
}
//---------------------------------------------------------------------------


void __fastcall TForm7::Button1Click(TObject *Sender)
{
        LCPKm fu7;

        if(Form1->nieprawidlowe_podania_hasla >= 5)
        {
                ShowMessage("Odmowa dostêpu. Przekroczono limit b³êdnych wprowadzeñ has³a");
                return;
        }
        if(sprawdzanie_poprawnosci_hasla("Dane/Ustawienia2.txt"))
        {
                Form1->nieprawidlowe_podania_hasla = 0;

                switch(co_wybrac)
                {
                        case 1:
                        {
                                if(DeleteFile("Dane/Lista_aktywnosci.txt"))
                                {
                                        if(DeleteFile("Dane/Dane.txt"))
                                        {
                                                ShowMessage("Historia ~ aktywnoœci ~ zosta³a pomyœlnie usuniêta");
                                                fu7.tworzenie_pliku("Dane/Dane.txt");
                                                fu7.tworzenie_pliku("Dane/Lista_aktywnosci.txt");
                                                fu7.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "Usuniêcie historii aktywnoœci");
                                        }
                                        else
                                        {
                                                if(Form3->dane_na_liste_aktywnosci())
                                                {
                                                        ShowMessage("Nie mo¿na by³o usun¹æ pliku \"Dane.txt\"");
                                                        fu7.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "B³¹d przy próbie usuniêcia historii aktywnoœci\nHistoria aktywnoœci nie zosta³a usuniêta");
                                                }
                                                else
                                                {
                                                        ShowMessage("Nie mo¿na by³o usun¹æ pliku \"Dane.txt\" oraz wyst¹pi³ b³ad przy próbie odtworzenia pliku \"Lista_aktywnosci.txt\" przez co plik mo¿e byæ pusty lub niekompletny");
                                                        fu7.tworzenie_pliku("Dane/Lista_aktywnosci.txt");
                                                        fu7.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "B³¹d przy próbie usuniêcia historii aktywnoœci\nHistoria aktywnoœci zosta³a uszkodzona");
                                                }
                                        }

                                }
                                else
                                {
                                        ShowMessage("Nie mo¿na by³o usun¹æ pliku \"Lista_aktywnosci.txt\"");
                                        fu7.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "B³¹d przy próbie usuniêcia historii aktywnoœci\nHistoria aktywnoœci nie zosta³a usuniêta");
                                }
                        }
                        break;
                        case 2:
                        {
                                if(DeleteFile("Dane/Dzialania_uzytkownika.txt"))
                                {
                                        ShowMessage("Historia ~ dzia³añ u¿ytkownika ~ zosta³a pomyœlnie usuniêta");
                                        fu7.tworzenie_pliku("Dane/Dzialania_uzytkownika.txt");
                                        fu7.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "Usuniêcie historii dzia³añ u¿ytkownika");
                                }
                                else
                                {
                                        ShowMessage("Nie mo¿na by³o usun¹æ pliku \"Dzialania_uzytkownika.txt\"");
                                        fu7.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "B³¹d przy próbie usuniêcia historii dzia³añ u¿ytkownika\nHistoria dzia³añ u¿ytkownika nie zosta³a usuniêta");
                                }
                        }
                        break;
                        case 3:
                        {
                                string wbufor = "Usuwanie ca³ej historii\n";
                                bool czy_usunieto_wszystko = true;

                                if(DeleteFile("Dane/Lista_aktywnosci.txt"))
                                {
                                        if(DeleteFile("Dane/Dane.txt"))
                                        {
                                                fu7.tworzenie_pliku("Dane/Dane.txt");
                                                fu7.tworzenie_pliku("Dane/Lista_aktywnosci.txt");
                                                wbufor += "Usuniêcie historii aktywnoœci";
                                        }
                                        else
                                        {
                                                if(Form3->dane_na_liste_aktywnosci())
                                                {
                                                        ShowMessage("Nie mo¿na by³o usun¹æ pliku \"Dane.txt\"");
                                                        wbufor += "B³¹d przy próbie usuniêcia historii aktywnoœci\nHistoria aktywnoœci nie zosta³a usuniêta";
                                                }
                                                else
                                                {
                                                        ShowMessage("Nie mo¿na by³o usun¹æ pliku \"Dane.txt\" oraz wyst¹pi³ b³ad przy próbie odtworzenia pliku \"Lista_aktywnosci.txt\" przez co plik mo¿e byæ pusty lub niekompletny");
                                                        fu7.tworzenie_pliku("Dane/Lista_aktywnosci.txt");
                                                        wbufor += "B³¹d przy próbie usuniêcia historii aktywnoœci\nHistoria aktywnoœci zosta³a uszkodzona";
                                                }
                                                czy_usunieto_wszystko = false;
                                        }

                                }
                                else
                                {
                                        ShowMessage("Nie mo¿na by³o usun¹æ pliku \"Lista_aktywnosci.txt\"");
                                        wbufor += "B³¹d przy próbie usuniêcia historii aktywnoœci\nHistoria aktywnoœci nie zosta³a usuniêta";
                                        czy_usunieto_wszystko = false;
                                }
                                ////////////////////////////////////////////////////////////////////////////////////////////////
                                if(DeleteFile("Dane/Dzialania_uzytkownika.txt"))
                                {
                                        fu7.tworzenie_pliku("Dane/Dzialania_uzytkownika.txt");
                                        wbufor += "\nUsuniêcie historii dzia³añ u¿ytkownika";
                                }
                                else
                                {
                                        ShowMessage("Nie mo¿na by³o usun¹æ pliku \"Dzialania_uzytkownika.txt\"");
                                        czy_usunieto_wszystko = false;
                                        wbufor += "B³¹d przy próbie usuniêcia historii dzia³añ u¿ytkownika\nHistoria dzia³añ u¿ytkownika nie zosta³a usuniêta";
                                }

                                if(czy_usunieto_wszystko)
                                {
                                        ShowMessage("Ca³a historia zosta³a pomyœlnie usuniêta");
                                        wbufor += "\nCa³a historia zosta³a usuniêta";
                                }

                                fu7.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, wbufor);
                        }
                        break;
                        case 4:
                        {
                                Form1->ustawienia[8] = "1";
                                Form1->zapis_ustawien();
                                Form3->Niezapisujtejaktywnoci1->Checked = true;
                        }
                        break;
                        case 5:
                        {
                                Form3->wyswietlenie_danych("Dane/Dzialania_uzytkownika.txt");
                        }
                        break;
                        case 6:
                        {
                                Form1->przycisk_widocznosci("0", "0", "1", "Tryb ninja");
                                ShowMessage("W celu zmiany trybu ninja na minimalizacje do treya mo¿na skorzystaæ z programu \"Wylaczanie_trybu_ninja.exe\", który znajduje siê w folderze z programem \"LCPK.exe\"");
                        }
                        break;
                        case 7:
                        {
                                string bufor1;

                                bufor1 = fu7.sciezka_skrotu_w_autostarcie();

                                if(bufor1 == "0")
                                {
                                        ShowMessage("Nie uda³o siê pobraæ œcie¿ki do skrótu programu \"LCPK.exe\". Skrót programu powinien znajdowaæ siê w folderze autostartu u¿ytkownika sk¹d mo¿na go rêcznie usun¹æ");
                                }
                                else if(DeleteFile(bufor1.c_str()))
                                {
                                        ShowMessage("Skrót programu \"LCPK.exe\" zosta³ usuniêty z autostartu u¿ytkownika. W celu ca³kowitego usuniêcia programu \"LCPK.exe\" z komputera wystarczy usun¹æ folder \"LCPK\" z ca³¹ jego zawartoœci¹");
                                        fu7.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "Usuniêcie skrótu programu \"LCPK.exe\" z autostartu");
                                }
                                else
                                {
                                        if(fu7.czy_plik_istnieje(bufor1))
                                        {
                                                ShowMessage("Nie uda³o siê usun¹æ skrótu programu \"LCPK.exe\". Skrót programu powinien znajdowaæ siê w folderze autostartu u¿ytkownika sk¹d mo¿na go rêcznie usun¹æ");
                                        }
                                        else
                                        {
                                                ShowMessage("Nie odnaleziono skrótu programu \"LCPK.exe\" w folderze autostartu u¿ytkownika");
                                        }
                                }
                        }
                        break;
                        default: ShowMessage("Coœ nie pyk³o");
                }
                Form7->Close();
        }
        else
        {
                Edit1->Text = "";
                ShowMessage("Wpisano niepoprawne has³o");
                Form1->nieprawidlowe_podania_hasla ++;
        }
}
//---------------------------------------------------------------------------


bool TForm7::sprawdzanie_poprawnosci_hasla(AnsiString nazwa_pliku)
{
        LCPKm fu7;

        HANDLE hplik;

        if(!(fu7.czy_plik_istnieje("Dane/Ustawienia2.txt")))
        {
                hplik = CreateFile("Dane/Ustawienia2.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN, NULL);
                CloseHandle(hplik);
                plik7.open("Dane/Ustawienia2.txt", ios::out);
                plik7 << fu7.szyfrowanie_hasla("de83jflxho3p95hksdu3i2878952hfdfksh", "brak hasla axc0wa896321c4b8") << endl;
                plik7.close();
                plik7.clear();
        }

        if(!(fu7.czy_plik_istnieje("Dane/Haslo.txt")))
        {
                hplik = CreateFile("Dane/Haslo.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN, NULL);
                CloseHandle(hplik);
                plik7.open("Dane/Haslo.txt", ios::out);
                plik7 << fu7.losowe_haslo("de83jflxho3p95hksdu3i2878952hfdfksh", "brak hasla axc0wa896321c4b8") << endl;
                plik7.close();
                plik7.clear();
        }

        string bufor1;
        int d;
        string bufor2;

        bufor1 = (Edit1->Text).c_str();
        d = bufor1.size();

        if((d < 0) || ((d > 0) && (d < 3)) || (d > 300)) return false;
        if(d == 0) bufor1 = "brak hasla axc0wa896321c4b8";

        plik7.open(nazwa_pliku.c_str(), ios::in);

        if((!(plik7.good())) || (plik7.eof()))
        {
                plik7.close();
                plik7.clear();
                return false;
        }

        getline(plik7, bufor2);

        plik7.close();
        plik7.clear();

        return fu7.zgodnosc_hasla_z_zaszyfrowanym_haslem("de83jflxho3p95hksdu3i2878952hfdfksh", bufor2, bufor1.c_str());
}
