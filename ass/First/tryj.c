#include <vcl.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#pragma hdrstop
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
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
	float x,y,x1,y1,eps;
	x1=StrToFloat(Edit2->Text);  // вводими Х
	eps=StrToFloat(Edit1->Text);   // вводимо Е
	Series1->Clear();
	for (x = 0.001; x < 20; x+=0.001) {   	// зображуєио график бібліотечної Ln[x]
		y=log(x);
		Series1->AddXY(x,y);
	}
	Chart1->Refresh();
	Chart1->LeftAxis->Increment=(Chart1->LeftAxis->Maximum-Chart1->LeftAxis->Minimum)/5;
	//Разладання функції в ряд Тейлора
  int n=3;
	float *temp = new float [100];                         // ініціалізуємо масив
	float S = pow(x1-1.0,2)/(2*x1*x1); 		   // загальний член ряду
	temp[0] = ((x1-1.0)/x1);			    // нульовий елемент масиву
	temp[1] = S;
	while(S>eps)					 // цикл підрахунку ряду
	 {
	 S *= (x1-1.0)*(n-1)/(n*x1);

		temp[n-1] = S ;			// запис в тимчасовий масив
		n++;

	 }
	for(n; n >= 0; n--)			// цикл, який рахує суму членів ряду від меншого до більшого
	{ y1 += temp[n]; }
  }//--------------------------------------
	Series2->AddXY(x1,log(x1));
	Series2->AddXY(x1,y1);

	// похибки
	Label2->Caption=FloatToStrF(fabs(log(x1)-y1),ffGeneral,8,5);
	Label4->Caption=FloatToStrF(fabs(log(x1)-y1)*100/y1,ffGeneral,8,5)+ " %";
	Label5->Caption="Истинна: " + FloatToStrF(log(x1),ffGeneral,8,5);
	Label6->Caption="Тейлор: " + FloatToStrF(y1,ffGeneral,8,5);
}
