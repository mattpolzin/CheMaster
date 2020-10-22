//This file defines the class map, and its methods which allow the user to load and display a map with elements on it.


//map.h


#ifndef _MAP_H
#define _MAP_H

#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include"player.h"
#include"defvals.h"
#include"drawBitmap.h"

//define the new command: word, so you do not have to imbed arrays to achieve an array of arrays of characters.
typedef char word[50];

class MAP
{
public:
    //this class must store a copy of the main windows HWND and HINSTANCE structures so it can draw bitmaps to it.
    HWND hwnd;
    HINSTANCE hinstance;
    //array: square - will hold the tile value of each square.
    int square[ROWS][COLS];
    //array: itemCount - will hold the number of the item in a given square.
    int itemCount[ROWS][COLS];
    int playerx,playery;
    //array: itemName - will hold the name of the item in a given square.
    word itemName[ROWS][COLS];
    
    //funcs
    MAP();
    MAP(HINSTANCE bhinstance,HWND bhwnd,char filename[50]);
    //update will initialize or reinitialize the values stored in the map class.
    void update(HINSTANCE bhinstance,HWND bhwnd,char filename[50]);
    //updateSquare will take the column(x) and row(y) of a square to update, and the new value of the square.
    void updateSquare(int x,int y,int newVal);
    //updateItem is similar to updateSquare but this will take the quantity of an item and its name and place the new value in the specified square.
    void updateItem(int x,int y,int newNum,char newVal[50]);
    //draw simply draws the given square, or if no square is given then it draws all of the squares. [overloaded]
    void draw(int x,int y);
    void draw();
};

void MAP::updateItem(int x,int y,int newNum,char newVal[50])
{
    itemCount[x-1][y-1]=newNum;
    strcpy(itemName[x-1][y-1],newVal);
}

void MAP::updateSquare(int x,int y,int newVal)
{
    square[x-1][y-1]=newVal;
}

void MAP::draw()
{
    //if the user wants to draw everything, then why not just call draw(int x,int y) a number of times?
    for(int i=0;i<COLS;i++)
    {
        for(int j=0;j<ROWS;j++)
        {
            draw(j,i);
        }
    }
}

void MAP::draw(int x,int y)
{
    //set value to the tile number located in square[x][y] so you can access it easily later.
    int value=square[x][y];
    //set the xpos and ypos variables equal to x(columb) and y(row) so you can change x and y to their absolute values.
    int xpos=x;
    int ypos=y;
    //multiply by the size of a square (64) and add the original position of the board to get absolute x and y.
    y=(y*64)+DEFMAPY;
    x=(x*64)+DEFMAPX;
    //retrieve the HDC of the current window so you can use it to draw bitmaps or squares.
    HDC hdc;
    hdc=GetDC(hwnd);
    //if the tile number is zero then there is no tile there, draw a black square.
    if(value==0)
    {
        pixelRect(hdc,x,y,x+64,y+64,RGB(0,0,0));
    }
    else
    {
        //if value is 1-9 draw the corresponding tiles in that location.
        if(value==1)
        {
            drawBitmap(hinstance,hdc,x,y,DIRT,SRCCOPY);
        }
        if(value==2)
        {
            drawBitmap(hinstance,hdc,x,y,HOLE,SRCCOPY);
        }
        if(value==3)
        {
            //if the value is 3,4,7, or 8 then the tile might need to be rotated so it looks right.
            //if there is something other than dirt to the right and left (wall, hole, or door) then draw the door horizontal, otherwise draw it vertical.
            if(square[xpos-1][ypos]!=DIRT && square[xpos+1][ypos]!=DIRT && (square[xpos][ypos+1]!=ROCKWALL || square[xpos][ypos-1]!=ROCKWALL))
            {
                drawBitmap(hinstance,hdc,x,y,METALDOOR,SRCCOPY);
            }
            else
            {
                drawBitmap(hinstance,hdc,x,y,METALDOOR2,SRCCOPY);
            }
        }
        if(value==4)
        {
            //see value==3 for info on this code.
            if(square[xpos-1][ypos]!=DIRT && square[xpos+1][ypos]!=DIRT && (square[xpos][ypos+1]!=ROCKWALL || square[xpos][ypos-1]!=ROCKWALL))
            {
                drawBitmap(hinstance,hdc,x,y,METALDOORRUSTED,SRCCOPY);
            }
            else
            {
                drawBitmap(hinstance,hdc,x,y,METALDOORRUSTED2,SRCCOPY);
            }
        }
        if(value==5)
        {
            drawBitmap(hinstance,hdc,x,y,ROCKWALL,SRCCOPY);
        }
        if(value==6)
        {
            drawBitmap(hinstance,hdc,x,y,WATERHOLE,SRCCOPY);
        }
        if(value==7)
        {
            //see value==3 for info on this code.
            if(square[xpos-1][ypos]!=DIRT && square[xpos+1][ypos]!=DIRT && (square[xpos][ypos+1]!=ROCKWALL || square[xpos][ypos-1]!=ROCKWALL))
            {
                drawBitmap(hinstance,hdc,x,y,WOODDOOR,SRCCOPY);
            }
            else
            {
                drawBitmap(hinstance,hdc,x,y,WOODDOOR2,SRCCOPY);
            }
        }
        if(value==8)
        {
            //see value==3 for info on this code.
            if(square[xpos-1][ypos]!=DIRT && square[xpos+1][ypos]!=DIRT && (square[xpos][ypos+1]!=ROCKWALL || square[xpos][ypos-1]!=ROCKWALL))
            {
                drawBitmap(hinstance,hdc,x,y,WOODDOORBURNT,SRCCOPY);
            }
            else
            {
                drawBitmap(hinstance,hdc,x,y,WOODDOORBURNT2,SRCCOPY);
            }
        }
        if(value==9)
        {
            drawBitmap(hinstance,hdc,x,y,EXIT,SRCCOPY);
        }
        //set value2=the number that represents whether the current square has an element on it.
        int value2=itemCount[xpos][ypos];
        //if the square has an element draw it there.
        if(value2!=0)
        {
            //to make a transparent image do the following.
            //use srcand to draw the mask
            drawBitmap(hinstance,hdc,x,y,PACKAGEMASK,SRCAND);
            //use srcpaint to draw the image.
            drawBitmap(hinstance,hdc,x,y,PACKAGE,SRCPAINT);
        }
    }
    ReleaseDC(hwnd,hdc);
}

MAP::MAP()
{
}

MAP::MAP(HINSTANCE bhinstance,HWND bhwnd,char filename[50])
{
    update(bhinstance,bhwnd,filename);
}

void MAP::update(HINSTANCE bhinstance,HWND bhwnd,char filename[50])
{
    word tempChem;
    hwnd=bhwnd;
    hinstance=bhinstance;
    ifstream fin(filename);
    
    /*for(int g=i;g<COLS;g++)
    {
        for(int h=0;h<ROWS;h++)
        {
            position[h][g]=0;
        }
    }*/
    
    if(!fin.is_open())
    {
        MessageBox(hwnd,"You have beaten all of the levels in the game, feel free to expand upon the game with your own levels.","Congratulations",MB_OK);
        PostMessage(hwnd,WM_QUIT,0,0);
    }
    else
    {
        fin>>playerx>>playery;
        for(int i=0;i<COLS;i++)
        {
            for(int j=0;j<ROWS;j++)
            {
                fin>>square[j][i];
            }
        }
        fin.ignore();
        for(int k=0;k<COLS;k++)
        {
            for(int l=0;l<ROWS;l++)
            {
                fin>>tempChem;
                itemCount[l][k]=atoi(&tempChem[0]);
                if(itemCount[l][k]!=0)
                {
                    for(int m=0;m<=strlen(tempChem);m++)
                    {
                        tempChem[m-1]=tempChem[m];
                    }
                    strcpy(itemName[l][k],tempChem);
                }
            }
        }
    }
    fin.close();
}

#endif