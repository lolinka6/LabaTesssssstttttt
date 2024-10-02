//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <jpeg.hpp>


#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button1Click(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
DoubleBuffered = true;
Form2->Caption = "Doodle Jump";
BorderStyle = bsSingle;

history->Caption = "";
TStringList *text= new TStringList;
text->LoadFromFile("games.txt");
for(int i = text->Count-1; i >= 0; i --)
{
	 history->Caption += "—чет: " + text->Strings[i] + "\n";
}
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Image4Click(TObject *Sender)
{
Form3->doodle->Picture->LoadFromFile("usual_left.png");
ShowMessage("—кин выбран!");
Form3->left_doodle_model = "usual_left.png";
Form3->right_doodle_model = "usual_right.png";
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image5Click(TObject *Sender)
{
Form3->doodle->Picture->LoadFromFile("ninja_left.png");
ShowMessage("—кин выбран!");
Form3->left_doodle_model = "ninja_left.png";
Form3->right_doodle_model = "ninja_right.png";
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image2Click(TObject *Sender)
{
Form3->background->Picture->LoadFromFile("theme1.jpg");
ShowMessage("‘он выбран!");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image3Click(TObject *Sender)
{
Form3->background->Picture->LoadFromFile("theme2.jpg");
ShowMessage("‘он выбран!");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label3Click(TObject *Sender)
{
Form3->Left = Form2->Left;
Form3->Top = Form2->Top;
Form3->Show();
Form2->Hide();

Form3->startGame();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label4Click(TObject *Sender)
{
Application->Terminate();
}
//---------------------------------------------------------------------------

