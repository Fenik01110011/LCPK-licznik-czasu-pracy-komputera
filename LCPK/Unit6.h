//---------------------------------------------------------------------------

#ifndef Unit6H
#define Unit6H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>

class TForm6 : public TForm
{
__published:	// IDE-managed Components
        TDateTimePicker *DateTimePicker1;
        TDateTimePicker *DateTimePicker2;
        TLabel *Label1;
        TLabel *Label3;
        TLabel *Label6;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm6(TComponent* Owner);

        std::fstream plik6;

        std::string bufor_komunikat;

        AnsiString pobrana_data;
        AnsiString pobrana_godzina;
        bool wybor_daty;

        void ustawianie_daty();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm6 *Form6;
//---------------------------------------------------------------------------
#endif
