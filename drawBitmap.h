
//drawBitmap.h


#ifndef _DRAWBITMAP_H
#define _DRAWBITMAP_H

#include<windows.h>

int drawBitmap(HINSTANCE hinstance,HDC hDestDC, int xDest, int yDest, int nResID,int method)
{
  HDC hSrcDC;           // source DC - memory device context
  HBITMAP hbitmap;      // handle to the bitmap resource
  BITMAP bmp;           // structure for bitmap info
  int nHeight, nWidth;  // bitmap dimensions

  // first load the bitmap resource
  if ((hbitmap = (HBITMAP)LoadImage(hinstance, MAKEINTRESOURCE(nResID),
                                    IMAGE_BITMAP, 0, 0,
                                    LR_CREATEDIBSECTION)) == NULL)
    return(FALSE);

  // create a DC for the bitmap to use
  if ((hSrcDC = CreateCompatibleDC(NULL)) == NULL)
    return(FALSE);

  // select the bitmap into the DC
  if (SelectObject(hSrcDC, hbitmap) == NULL)
    return(FALSE);

  // get image dimensions
  if (GetObject(hbitmap, sizeof(BITMAP), &bmp) == 0)
    return(FALSE);

  nWidth = bmp.bmWidth;
  nHeight = bmp.bmHeight;

  // copy image from one DC to the other
  if (BitBlt(hDestDC, xDest, yDest, nWidth, nHeight, hSrcDC, 0, 0,
             method) == NULL)
    return(FALSE);

  // kill the memory DC
  DeleteDC(hSrcDC);

  // return success!
  return(TRUE);
}

#endif