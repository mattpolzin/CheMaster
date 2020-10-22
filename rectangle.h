

//rectangle.h


#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include"line.h"

void pixelRect(HDC hdc,int x1,int y1,int x2,int y2,COLORREF color)
{
    if(x2>x1)
    {
        if(y2>y1)
        {
            for(int i=0;i<x2-x1;i++)
            {
                pixelLine(hdc,x1+i,y1,x1+i,y1+y2-y1,color);
            }
        }
        if(y1>y2)
        {
            for(int i=0;i<x2-x1;i++)
            {
                pixelLine(hdc,x1+i,y1,x1+i,y1-y2+y1,color);
            }
        }
    }
}

#endif