//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Unit4.h"
#include "Unit6.h"

TForm5 *Form5;

//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
        : TForm(Owner)
{
        ktora_forma = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm5::FormActivate(TObject *Sender)
{
        if(ktora_forma == 4)
        {
                wwb = Form4->wynik_wawp - 1;
                zg = Form4->pobrana_godzina[wwb];

                zg1 = ""; zgp1 = ""; zg2 = ""; zgp2 = "";

                if(zg == "03:00:00") { zg1 = "2a:00:00"; zgp1 = "02a:00:00"; }
                else { zg1 = zg; zgp1 = zg; }

                zg2 += zg[2]; zg2 += 'a'; zg2 += zg[3]; zg2 += zg[4]; zg2 += zg[5]; zg2 += zg[6]; zg2 += zg[7]; zg2 += zg[8];
                zgp2 += zg[1]; zgp2 += zg[2]; zgp2 += 'a'; zgp2 += zg[3]; zgp2 += zg[4]; zgp2 += zg[5]; zgp2 += zg[6]; zgp2 += zg[7]; zgp2 += zg[8];

                Label2->Caption = Form4->pobrana_data[wwb];
                Button1->Caption = zgp1;
                Button2->Caption = zgp2;
        }
        else if(ktora_forma == 6)
        {
                zg = Form6->pobrana_godzina;

                zg1 = ""; zgp1 = ""; zg2 = ""; zgp2 = "";

                if(zg == "03:00:00") { zg1 = "2a:00:00"; zgp1 = "02a:00:00"; }
                else { zg1 = zg; zgp1 = zg; }

                zg2 += zg[2]; zg2 += 'a'; zg2 += zg[3]; zg2 += zg[4]; zg2 += zg[5]; zg2 += zg[6]; zg2 += zg[7]; zg2 += zg[8];
                zgp2 += zg[1]; zgp2 += zg[2]; zgp2 += 'a'; zgp2 += zg[3]; zgp2 += zg[4]; zgp2 += zg[5]; zgp2 += zg[6]; zgp2 += zg[7]; zgp2 += zg[8];

                Label2->Caption = Form6->pobrana_data;
                Button1->Caption = zgp1;
                Button2->Caption = zgp2;
        }

}
//---------------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void __fastcall TForm5::Button1Click(TObject *Sender)
{
        if(ktora_forma == 4)
        {
                Form4->pobrana_godzina[wwb] = zg1;
                Form4->wyswietlanie_aktywnosci_w_przedziale();
        }
        else if(ktora_forma == 6)
        {
                Form6->pobrana_godzina = zg1;
                Form6->ustawianie_daty();
        }

        Form5->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button2Click(TObject *Sender)
{
        if(ktora_forma == 4)
        {
                Form4->pobrana_godzina[wwb] = zg2;
                Form4->wyswietlanie_aktywnosci_w_przedziale();
        }
        else if(ktora_forma == 6)
        {
                Form6->pobrana_godzina = zg2;
                Form6->ustawianie_daty();
        }

        Form5->Visible = false;
}
//---------------------------------------------------------------------------

