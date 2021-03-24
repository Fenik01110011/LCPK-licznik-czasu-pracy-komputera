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
                ShowMessage("Odmowa dost�pu. Przekroczono limit b��dnych wprowadze� has�a");
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
                                                ShowMessage("Historia ~ aktywno�ci ~ zosta�a pomy�lnie usuni�ta");
                                                fu7.tworzenie_pliku("Dane/Dane.txt");
                                                fu7.tworzenie_pliku("Dane/Lista_aktywnosci.txt");
                                                fu7.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "Usuni�cie historii aktywno�ci");
                                        }
                                        else
                                        {
                                                if(Form3->dane_na_liste_aktywnosci())
                                                {
                                                        ShowMessage("Nie mo�na by�o usun�� pliku \"Dane.txt\"");
                                                        fu7.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "B��d przy pr�bie usuni�cia historii aktywno�ci\nHistoria aktywno�ci nie zosta�a usuni�ta");
                                                }
                                                else
                                                {
                                                        ShowMessage("Nie mo�na by�o usun�� pliku \"Dane.txt\" oraz wyst�pi� b�ad przy pr�bie odtworzenia pliku \"Lista_aktywnosci.txt\" przez co plik mo�e by� pusty lub niekompletny");
                                                        fu7.tworzenie_pliku("Dane/Lista_aktywnosci.txt");
                                                        fu7.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "B��d przy pr�bie usuni�cia historii aktywno�ci\nHistoria aktywno�ci zosta�a uszkodzona");
                                                }
                                        }

                                }
                                else
                                {
                                        ShowMessage("Nie mo�na by�o usun�� pliku \"Lista_aktywnosci.txt\"");
                                        fu7.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "B��d przy pr�bie usuni�cia historii aktywno�ci\nHistoria aktywno�ci nie zosta�a usuni�ta");
                                }
                        }
                        break;
                        case 2:
                        {
                                if(DeleteFile("Dane/Dzialania_uzytkownika.txt"))
                                {
                                        ShowMessage("Historia ~ dzia�a� u�ytkownika ~ zosta�a pomy�lnie usuni�ta");
                                        fu7.tworzenie_pliku("Dane/Dzialania_uzytkownika.txt");
                                        fu7.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "Usuni�cie historii dzia�a� u�ytkownika");
                                }
                                else
                                {
                                        ShowMessage("Nie mo�na by�o usun�� pliku \"Dzialania_uzytkownika.txt\"");
                                        fu7.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "B��d przy pr�bie usuni�cia historii dzia�a� u�ytkownika\nHistoria dzia�a� u�ytkownika nie zosta�a usuni�ta");
                                }
                        }
                        break;
                        case 3:
                        {
                                string wbufor = "Usuwanie ca�ej historii\n";
                                bool czy_usunieto_wszystko = true;

                                if(DeleteFile("Dane/Lista_aktywnosci.txt"))
                                {
                                        if(DeleteFile("Dane/Dane.txt"))
                                        {
                                                fu7.tworzenie_pliku("Dane/Dane.txt");
                                                fu7.tworzenie_pliku("Dane/Lista_aktywnosci.txt");
                                                wbufor += "Usuni�cie historii aktywno�ci";
                                        }
                                        else
                                        {
                                                if(Form3->dane_na_liste_aktywnosci())
                                                {
                                                        ShowMessage("Nie mo�na by�o usun�� pliku \"Dane.txt\"");
                                                        wbufor += "B��d przy pr�bie usuni�cia historii aktywno�ci\nHistoria aktywno�ci nie zosta�a usuni�ta";
                                                }
                                                else
                                                {
                                                        ShowMessage("Nie mo�na by�o usun�� pliku \"Dane.txt\" oraz wyst�pi� b�ad przy pr�bie odtworzenia pliku \"Lista_aktywnosci.txt\" przez co plik mo�e by� pusty lub niekompletny");
                                                        fu7.tworzenie_pliku("Dane/Lista_aktywnosci.txt");
                                                        wbufor += "B��d przy pr�bie usuni�cia historii aktywno�ci\nHistoria aktywno�ci zosta�a uszkodzona";
                                                }
                                                czy_usunieto_wszystko = false;
                                        }

                                }
                                else
                                {
                                        ShowMessage("Nie mo�na by�o usun�� pliku \"Lista_aktywnosci.txt\"");
                                        wbufor += "B��d przy pr�bie usuni�cia historii aktywno�ci\nHistoria aktywno�ci nie zosta�a usuni�ta";
                                        czy_usunieto_wszystko = false;
                                }
                                ////////////////////////////////////////////////////////////////////////////////////////////////
                                if(DeleteFile("Dane/Dzialania_uzytkownika.txt"))
                                {
                                        fu7.tworzenie_pliku("Dane/Dzialania_uzytkownika.txt");
                                        wbufor += "\nUsuni�cie historii dzia�a� u�ytkownika";
                                }
                                else
                                {
                                        ShowMessage("Nie mo�na by�o usun�� pliku \"Dzialania_uzytkownika.txt\"");
                                        czy_usunieto_wszystko = false;
                                        wbufor += "B��d przy pr�bie usuni�cia historii dzia�a� u�ytkownika\nHistoria dzia�a� u�ytkownika nie zosta�a usuni�ta";
                                }

                                if(czy_usunieto_wszystko)
                                {
                                        ShowMessage("Ca�a historia zosta�a pomy�lnie usuni�ta");
                                        wbufor += "\nCa�a historia zosta�a usuni�ta";
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
                                ShowMessage("W celu zmiany trybu ninja na minimalizacje do treya mo�na skorzysta� z programu \"Wylaczanie_trybu_ninja.exe\", kt�ry znajduje si� w folderze z programem \"LCPK.exe\"");
                        }
                        break;
                        case 7:
                        {
                                string bufor1;

                                bufor1 = fu7.sciezka_skrotu_w_autostarcie();

                                if(bufor1 == "0")
                                {
                                        ShowMessage("Nie uda�o si� pobra� �cie�ki do skr�tu programu \"LCPK.exe\". Skr�t programu powinien znajdowa� si� w folderze autostartu u�ytkownika sk�d mo�na go r�cznie usun��");
                                }
                                else if(DeleteFile(bufor1.c_str()))
                                {
                                        ShowMessage("Skr�t programu \"LCPK.exe\" zosta� usuni�ty z autostartu u�ytkownika. W celu ca�kowitego usuni�cia programu \"LCPK.exe\" z komputera wystarczy usun�� folder \"LCPK\" z ca�� jego zawarto�ci�");
                                        fu7.odnotowanie_dzialan_uzytkownika("Dane/Dzialania_uzytkownika.txt", 5, "Usuni�cie skr�tu programu \"LCPK.exe\" z autostartu");
                                }
                                else
                                {
                                        if(fu7.czy_plik_istnieje(bufor1))
                                        {
                                                ShowMessage("Nie uda�o si� usun�� skr�tu programu \"LCPK.exe\". Skr�t programu powinien znajdowa� si� w folderze autostartu u�ytkownika sk�d mo�na go r�cznie usun��");
                                        }
                                        else
                                        {
                                                ShowMessage("Nie odnaleziono skr�tu programu \"LCPK.exe\" w folderze autostartu u�ytkownika");
                                        }
                                }
                        }
                        break;
                        default: ShowMessage("Co� nie pyk�o");
                }
                Form7->Close();
        }
        else
        {
                Edit1->Text = "";
                ShowMessage("Wpisano niepoprawne has�o");
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
