//---------------------------------------------------------------------------

#include <vcl.h>
#include <fstream>
#pragma hdrstop

#include "Unit3.h"
#include "Unit2.h"
#include <pngimage.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

int jumpPower = 25; //  ���� ������
TImage *platforms[10]; //������ ��������
AnsiString horizontalD = "stay"; // right left �������������� �����������
int scores = 0; // ����

void __fastcall TForm3::startGame() // ������� ������ ����
{
	for(int i = 0; i < 10; i ++) // �������� ��������� 10 ��������
	{
		platforms[i]->Left = platforms[i]->Width + (rand() % (Form3->Width-platforms[i]->Width*2));
		if(i == 0 ) platforms[i]->Top = Form3->Height - 200;
		else platforms[i]->Top = platforms[i-1]->Top - (220 + rand() % 80);
	}
	horizontalD = "stay";
	scores = 0;
	score->Caption = "����: 0";
    doodle->Top = platforms[0]->Top - doodle->Height - 20;
	doodle->Left = platforms[0]->Left;
	Timer1->Enabled = true;
}


void __fastcall TForm3::Timer1Timer(TObject *Sender)
{
	doodle->Top -= jumpPower;

	if(jumpPower > -22) jumpPower--;

	for(int i = 0; i < 10; i++) // ��������� ��������� ������� �� ���������
	{
		// ���� ����� �� ���������
		 if(jumpPower < 0 && ((doodle->Left+doodle->Width - 20) >= platforms[i]->Left) && ((doodle->Left) <= (platforms[i]->Left + platforms[i]->Width))  && (  abs((doodle->Top+doodle->Height) - platforms[i]->Top) <= 25 )){
			doodle->Top = platforms[i]->Top - doodle->Height; // ������ ��� ����� �� ���������
			jumpPower = 25; // ����������� ���� ������
			if(platforms[i]->Top < Form3->Height - 200) // ���� �������� ���������� �����
			if(!Timer2->Enabled)
			{
				Timer2->Enabled = true; // �������� ��� ��������� ���� � ���������� ����
                scores++;
				score->Caption = "����: " + AnsiString(scores);
				break;
			}
		 }
	}

	// ����������� �� ����������� ���� ������ �������
	if(horizontalD == "left") doodle->Left -= 15;
	else if(horizontalD == "right") doodle->Left += 15;


	// ���� ����� �� ������� ����� - ����������� ��������� �� ������ �������
	if((doodle->Left+doodle->Width) < 0) doodle->Left = Form3->Width;
	else if(doodle->Left > Form3->Width) doodle->Left = 1-doodle->Width;

	if( (doodle->Top+doodle->Height) > Form3->Height) // �������� �� ������
	{
		Timer1->Enabled = false; // ��������� ������� ������
		Form2->scoreLabel->Caption = score->Caption;
		fstream f;
		f.open("games.txt", ios::app);
		f << scores; // ���������� ��������� � ���������
		f << "\n";
		f.close();

		Form2->history->Caption = "";
		TStringList *text= new TStringList;
		text->LoadFromFile("games.txt");
		for(int i = text->Count-1; i >= 0; i --)
		{
			Form2->history->Caption += "����: " + text->Strings[i] + "\n"; // ������� ���������� ���������� � ����
		}

		ShowMessage("��������!");
		Form2->Left = Form3->Left;
		Form2->Top = Form3->Top;
		Form2->Show();
		Form3->Hide();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormCreate(TObject *Sender)
{

BorderStyle = bsSingle;
Form3->Caption = "Doodle Jump";
DoubleBuffered = true;
srand(time(0));

for(int i = 0; i < 10; i ++) // ������� � ��������� 10 ��������
{
	platforms[i] = new TImage(this);
	platforms[i]->Parent = this;
	platforms[i]->Name = "platform"+AnsiString(i+1);
	platforms[i]->AutoSize = true;
	platforms[i]->Left = platforms[i]->Width + (rand() % (Form3->Width-platforms[i]->Width*2));
	if(i == 0 ) platforms[i]->Top = Form3->Height - 200;
	else platforms[i]->Top = platforms[i-1]->Top - (220 + rand() % 80);
	platforms[i]->Picture->LoadFromFile("plat1.png");
}

doodle->BringToFront();

}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
if(Key == 65 || Key == 37 && horizontalD != "left"){ // ���� ������ ����� �������
	horizontalD = "left"; // ������ �������������� ��������� � ��������� ����� ��������
	doodle->Picture->LoadFromFile(left_doodle_model);
}
else if(Key == 68 ||  Key == 39 && horizontalD != "right")  // ���� ������ ������ �������
{
	horizontalD = "right";  // ������ �������������� ��������� � ��������� ������ ��������
	doodle->Picture->LoadFromFile(right_doodle_model);
}
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
horizontalD = "stay"; // ���� ��������� ������ - �������������� �������� ���������������
}
//---------------------------------------------------------------------------


int timesChanged = 0;
void __fastcall TForm3::Timer2Timer(TObject *Sender) // ������ ��� ��������� ��������
{
	 if(timesChanged > 25)
	 {
		 timesChanged = 0;
		 Timer2->Enabled = false;
	 }
	 else{

	 for(int i = 0; i < 10; i ++){
		platforms[i]->Top += 25-timesChanged;
	 }
	 timesChanged++;

	 jumpPower = 4; // ����������

	 for(int i = 0; i < 10; i ++){
	 if(platforms[i]->Top  > Form3->Height)  // ���� ��������� ���������� ���� �����
	 {
		 int min = 0;
		 for(int i = 0; i < 10; i ++) if(platforms[i]->Top < min) min = platforms[i]->Top; // ������� ������ ����������� ������� ���������
		 platforms[i]->Top = min - (220 + rand() % 80); // ����������� �� ���� ���� ������
		 platforms[i]->Left = platforms[i]->Width + (rand() % (Form3->Width-platforms[i]->Width*2));
	 }
	 }
}
}
//---------------------------------------------------------------------------
