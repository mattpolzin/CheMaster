#ifndef _DEBUG_H
#define _DEBUG_H

#include<windows.h>
#include<string.h>
#include<fstream.h>

#ifndef SCREENWIDTH
#define SCREENWIDTH GetSystemMetrics(SM_CXSCREEN)
#define SCREENHEIGHT GetSystemMetrics(SM_CYSCREEN)
#endif

char diagStr[500];

void charDiag(char filename[500],char text[500]);
void charDiag(char text[500]);
void numDiag(char filename[500],int num);
void numDiag(int num);
void charDiagScreen(HDC hdc,char text[500]);

void charDiagScreen(HDC hdc,char text[500])
{
    TextOut(hdc,SCREENWIDTH-15,SCREENHEIGHT-15,text,strlen(text));
}

void charDiag(char filename[500],char text[500])
{
	ofstream fout;
	fout.open(filename,ios::app);
	fout<<endl;
	fout<<text;
	fout.close();
}

void charDiag(char text[150])
{
	ofstream fout;
	fout.open("log.txt",ios::app);
	fout<<endl;
	fout<<text;
	fout.close();
}

void numDiag(char filename[500],int num)
{
    ofstream fout;
    fout.open(filename,ios::app);
    fout<<endl;
    fout<<num;
    fout.close();
}

void numDiag(int num)
{
    ofstream fout;
    fout.open("log.txt",ios::app);
    fout<<endl;
    fout<<num;
    fout.close();
}

#endif