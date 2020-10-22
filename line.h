//------------------------------------------------------
//THE FOLLOWING FUNCTION WAS NOT CREATED BY ME, MATHEW POLZIN. IT WAS FOUND ONLINE
//------------------------------------------------------


//line.h


#ifndef __LINE_H_
#define __LINE_H_

#include<iostream.h>
#include<math.h>
#include<windows.h>
#include<windowsx.h>

void pixel(HDC hdc,int x, int y,int r,int g,int b)
{
    SetPixelV(hdc,x,y,RGB(r,g,b));
}

	void pixelLine(HDC hdc,int x0, int y0, int x1, int y1, COLORREF color)
    {
        int dy = y1 - y0;
        int dx = x1 - x0;
        int stepx, stepy;

        if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
        if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }

        SetPixelV(hdc,x0,y0,color);
		SetPixelV(hdc,x1,y1,color);
        if (dx > dy) {
            int length = (dx - 1) >> 2;
            int extras = (dx - 1) & 3;
            int incr2 = (dy << 2) - (dx << 1);
            if (incr2 < 0) {
                int c = dy << 1;
                int incr1 = c << 1;
                int d =  incr1 - dx;
                for (int i = 0; i < length; i++) {
                    x0 += stepx;
                    x1 -= stepx;
                    if (d < 0) {						// Pattern:
                        SetPixelV(hdc,x0,y0,color);			//
                        SetPixelV(hdc,x0+=stepx,y0,color);	//  x o o
                        SetPixelV(hdc,x1,y1,color);			//
                        SetPixelV(hdc,x1-=stepx,y1,color);
                        d += incr1;
                    } else {
                        if (d < c) {							// Pattern:
                            SetPixelV(hdc,x0,y0,color);				//      o
                            SetPixelV(hdc,x0+=stepx,y0 += stepy,color);		//  x o
                            SetPixelV(hdc,x1,y1,color);				//
                            SetPixelV(hdc,x1-=stepx,y1 -= stepy,color);
                        } else {
                            SetPixelV(hdc, x0, y0 += stepy,color);			// Pattern:
                            SetPixelV(hdc, x0 += stepx, y0,color);			//    o o 
                            SetPixelV(hdc, x1, y1 -= stepy,color);			//  x
                            SetPixelV(hdc, x1 -= stepx, y1,color);			//
                        }
                        d += incr2;
                    }
                }
                if (extras > 0) {
                    if (d < 0) {
                        SetPixelV(hdc, x0 += stepx, y0,color);
                        if (extras > 1) SetPixelV(hdc, x0 += stepx, y0,color);
                        if (extras > 2) SetPixelV(hdc, x1 -= stepx, y1,color);
                    } else
                    if (d < c) {
                        SetPixelV(hdc, x0 += stepx, y0,color);
                        if (extras > 1) SetPixelV(hdc, x0 += stepx, y0 += stepy,color);
                        if (extras > 2) SetPixelV(hdc, x1 -= stepx, y1,color);
                    } else {
                        SetPixelV(hdc, x0 += stepx, y0 += stepy,color);
                        if (extras > 1) SetPixelV(hdc, x0 += stepx, y0,color);
                        if (extras > 2) SetPixelV(hdc, x1 -= stepx, y1 -= stepy,color);
                    }
                }
            } else {
                int c = (dy - dx) << 1;
                int incr1 = c << 1;
                int d =  incr1 + dx;
                for (int i = 0; i < length; i++) {
                    x0 += stepx;
                    x1 -= stepx;
                    if (d > 0) {
                        SetPixelV(hdc, x0, y0 += stepy,color);			// Pattern:
                        SetPixelV(hdc, x0 += stepx, y0 += stepy,color);		//      o
                        SetPixelV(hdc, x1, y1 -= stepy,color);			//    o
                        SetPixelV(hdc, x1 -= stepx, y1 -= stepy,color);		//  x
                        d += incr1;
                    } else {
                        if (d < c) {
                            SetPixelV(hdc, x0, y0,color);				// Pattern:
                            SetPixelV(hdc, x0 += stepx, y0 += stepy,color);       //      o
                            SetPixelV(hdc, x1, y1,color);                         //  x o
                            SetPixelV(hdc, x1 -= stepx, y1 -= stepy,color);       //
                        } else {
                            SetPixelV(hdc, x0, y0 += stepy,color);			// Pattern:
                            SetPixelV(hdc, x0 += stepx, y0,color);			//    o o
                            SetPixelV(hdc, x1, y1 -= stepy,color);			//  x
                            SetPixelV(hdc, x1 -= stepx, y1,color);			//
                        }
                        d += incr2;
                    }
                }
                if (extras > 0) {
                    if (d > 0) {
                        SetPixelV(hdc, x0 += stepx, y0 += stepy,color);
                        if (extras > 1) SetPixelV(hdc, x0 += stepx, y0 += stepy,color);
                        if (extras > 2) SetPixelV(hdc, x1 -= stepx, y1 -= stepy,color);
                    } else
                    if (d < c) {
                        SetPixelV(hdc, x0 += stepx, y0,color);
                        if (extras > 1) SetPixelV(hdc, x0 += stepx, y0 += stepy,color);
                        if (extras > 2) SetPixelV(hdc, x1 -= stepx, y1,color);
                    } else {
                        SetPixelV(hdc, x0 += stepx, y0 += stepy,color);
                        if (extras > 1) SetPixelV(hdc, x0 += stepx, y0,color);
                        if (extras > 2) {
                            if (d > c)
                                SetPixelV(hdc, x1 -= stepx, y1 -= stepy,color);
                            else
                                SetPixelV(hdc, x1 -= stepx, y1,color);
                        }
                    }
                }
            }
        } else {
            int length = (dy - 1) >> 2;
            int extras = (dy - 1) & 3;
            int incr2 = (dx << 2) - (dy << 1);
            if (incr2 < 0) {
                int c = dx << 1;
                int incr1 = c << 1;
                int d =  incr1 - dy;
                for (int i = 0; i < length; i++) {
                    y0 += stepy;
                    y1 -= stepy;
                    if (d < 0) {
                        SetPixelV(hdc, x0, y0,color);
                        SetPixelV(hdc, x0, y0 += stepy,color);
                        SetPixelV(hdc, x1, y1,color);
                        SetPixelV(hdc, x1, y1 -= stepy,color);
                        d += incr1;
                    } else {
                        if (d < c) {
                            SetPixelV(hdc, x0, y0,color);
                            SetPixelV(hdc, x0 += stepx, y0 += stepy,color);
                            SetPixelV(hdc, x1, y1,color);
                            SetPixelV(hdc, x1 -= stepx, y1 -= stepy,color);
                        } else {
                            SetPixelV(hdc, x0 += stepx, y0,color);
                            SetPixelV(hdc, x0, y0 += stepy,color);
                            SetPixelV(hdc, x1 -= stepx, y1,color);
                            SetPixelV(hdc, x1, y1 -= stepy,color);
                        }
                        d += incr2;
                    }
                }
                if (extras > 0) {
                    if (d < 0) {
                        SetPixelV(hdc, x0, y0 += stepy,color);
                        if (extras > 1) SetPixelV(hdc, x0, y0 += stepy,color);
                        if (extras > 2) SetPixelV(hdc, x1, y1 -= stepy,color);
                    } else
                    if (d < c) {
                        SetPixelV(hdc, stepx, y0 += stepy,color);
                        if (extras > 1) SetPixelV(hdc, x0 += stepx, y0 += stepy,color);
                        if (extras > 2) SetPixelV(hdc, x1, y1 -= stepy,color);
                    } else {
                        SetPixelV(hdc, x0 += stepx, y0 += stepy,color);
                        if (extras > 1) SetPixelV(hdc, x0, y0 += stepy,color);
                        if (extras > 2) SetPixelV(hdc, x1 -= stepx, y1 -= stepy,color);
                    }
                }
            } else {
                int c = (dx - dy) << 1;
                int incr1 = c << 1;
                int d =  incr1 + dy;
                for (int i = 0; i < length; i++) {
                    y0 += stepy;
                    y1 -= stepy;
                    if (d > 0) {
                        SetPixelV(hdc, x0 += stepx, y0,color);
                        SetPixelV(hdc, x0 += stepx, y0 += stepy,color);
                        SetPixelV(hdc, x1 -= stepy, y1,color);
                        SetPixelV(hdc, x1 -= stepx, y1 -= stepy,color);
                        d += incr1;
                    } else {
                        if (d < c) {
                            SetPixelV(hdc, x0, y0,color);
                            SetPixelV(hdc, x0 += stepx, y0 += stepy,color);
                            SetPixelV(hdc, x1, y1,color);
                            SetPixelV(hdc, x1 -= stepx, y1 -= stepy,color);
                        } else {
                            SetPixelV(hdc, x0 += stepx, y0,color);
                            SetPixelV(hdc, x0, y0 += stepy,color);
                            SetPixelV(hdc, x1 -= stepx, y1,color);
                            SetPixelV(hdc, x1, y1 -= stepy,color);
                        }
                        d += incr2;
                    }
                }
                if (extras > 0) {
                    if (d > 0) {
                        SetPixelV(hdc, x0 += stepx, y0 += stepy,color);
                        if (extras > 1) SetPixelV(hdc, x0 += stepx, y0 += stepy,color);
                        if (extras > 2) SetPixelV(hdc, x1 -= stepx, y1 -= stepy,color);
                    } else
                    if (d < c) {
                        SetPixelV(hdc, x0, y0 += stepy,color);
                        if (extras > 1) SetPixelV(hdc, x0 += stepx, y0 += stepy,color);
                        if (extras > 2) SetPixelV(hdc, x1, y1 -= stepy,color);
                    } else {
                        SetPixelV(hdc, x0 += stepx, y0 += stepy,color);
                        if (extras > 1) SetPixelV(hdc, x0, y0 += stepy,color);
                        if (extras > 2) {
                            if (d > c)
                                SetPixelV(hdc, x1 -= stepx, y1 -= stepy,color);
                            else
                                SetPixelV(hdc, x1, y1 -= stepy,color);
                        }
                    }
                }
            }
        }
    }

#endif