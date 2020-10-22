
//player.h


#ifndef _PLAYER_H
#define _PLAYER_H

#include<iostream.h>
#include"defvals.h"
#include"rectangle.h"
#include<windows.h>
#include"resource.h"
#include"drawBitmap.h"

#define AC_WALK 1
#define AC_SWIM 2
#define DI_UP 1
#define DI_RIGHT 2
#define DI_DOWN 3
#define DI_LEFT 4

//structs
struct INVENTORY
{
    int oxygen;
    int chlorine;
    int hydrogen;
    int iron;
    int carbon;
    int water;
    int hydroxide;
    int carbondioxide;
    int ironoxide;
    int hydrogenchloride;
    int ironchloride;
    int methane;
    int bicarbonate;
};

//global vars

//function inits

//playerclass
class PLAYER
{
public:
    HWND hwnd;
    HINSTANCE hinstance;
    int x;
    int y;
    int action; //AC_WALK, AC_SWIM
    int direction; //DI_UP, DI_RIGHT, DI_DOWN, DI_LEFT
    INVENTORY inv;
    
    //funcs
    PLAYER();
    PLAYER(HINSTANCE bhinstance,HWND bhwnd,int xpos,int ypos,int bAction,int bDirection);
    void update(HINSTANCE bhinstance,HWND bhwnd,int xpos,int ypos,int bAction,int bDirection);
    void move(int xOff,int yOff);
    void zeroInv();
    void draw();
    void showInventory();
    //void erasePlayer();
};

void PLAYER::showInventory()
{
    char h[25],o[25],cl[25],fe[25],c[25],h2o[25],oh[25],co[25],feo[25],hcl[25],fecl[25],ch[25],hco[25];
    char h2[5],o2[5],cl2[5],fe2[5],c2[5],h2o2[5],oh2[5],co2[5],feo2[5],hcl2[5],fecl2[5],ch2[5],hco2[5];
    
    itoa(inv.hydrogen,&h2[0],10);
    itoa(inv.oxygen,&o2[0],10);
    itoa(inv.chlorine,&cl2[0],10);
    itoa(inv.iron,&fe2[0],10);
    itoa(inv.carbon,&c2[0],10);
    itoa(inv.water,&h2o2[0],10);
    itoa(inv.hydroxide,&oh2[0],10);
    itoa(inv.carbondioxide,&co2[0],10);
    itoa(inv.ironoxide,&feo2[0],10);
    itoa(inv.hydrogenchloride,&hcl2[0],10);
    itoa(inv.ironchloride,&fecl2[0],10);
    itoa(inv.methane,&ch2[0],10);
    itoa(inv.bicarbonate,&hco2[0],10);
    
    strcpy(h,"[H]Hydrogen: ");
    strcpy(o,"[O]Oxygen: ");
    strcpy(cl,"[Cl]Chlorine: ");
    strcpy(fe,"[Fe]Iron: ");
    strcpy(c,"[C]Carbon: ");
    strcpy(h2o,"[H2O]Water: ");
    strcpy(oh,"[OH]Hydroxide: ");
    strcpy(co,"[CO]Carbon Dioxide: ");
    strcpy(feo,"[FeO]Iron Oxide: ");
    strcpy(hcl,"[HCl]Hydrogen Chloride: ");
    strcpy(fecl,"[FeCl]Iron Chloride: ");
    strcpy(ch,"[CH]Methane: ");
    strcpy(hco,"[HCO]Bicarbonate: ");
    
    strcat(h,h2);
    strcat(o,o2);
    strcat(cl,cl2);
    strcat(fe,fe2);
    strcat(c,c2);
    strcat(h2o,h2o2);
    strcat(oh,oh2);
    strcat(co,co2);
    strcat(feo,feo2);
    strcat(hcl,hcl2);
    strcat(fecl,fecl2);
    strcat(ch,ch2);
    strcat(hco,hco2);
    HDC hdc;
    hdc=GetDC(hwnd);
    
    SetTextColor(hdc,RGB(50,250,200));
    SetBkColor(hdc,RGB(0,0,0));
    
    //pixelRect(hdc,0,0,DEFWINWIDTH-400,100,RGB(255,255,255));
    TextOut(hdc,0,0,h,strlen(h));
    TextOut(hdc,0,20,o,strlen(o));
    TextOut(hdc,0,40,cl,strlen(cl));
    TextOut(hdc,0,60,fe,strlen(fe));
    TextOut(hdc,0,80,c,strlen(c));
    
    TextOut(hdc,150,0,h2o,strlen(h2o));
    TextOut(hdc,150,20,oh,strlen(oh));
    TextOut(hdc,150,40,feo,strlen(feo));
    TextOut(hdc,150,60,co,strlen(co));
    TextOut(hdc,150,80,hcl,strlen(hcl));
    
    TextOut(hdc,350,0,fecl,strlen(fecl));
    TextOut(hdc,350,20,ch,strlen(ch));
    TextOut(hdc,350,40,hco,strlen(hco));
    
    drawBitmap(hinstance,hdc,0,0,TITLEBARMASK,SRCAND);
    drawBitmap(hinstance,hdc,0,0,TITLEBAR,SRCPAINT);
    
    ReleaseDC(hwnd,hdc);
}

void PLAYER::draw()
{
    HDC hdc;
    hdc=GetDC(hwnd);
    int xpos=(x*64)+DEFMAPX;
    int ypos=(y*64)+DEFMAPY;
    if(direction==DI_UP)
    {
        drawBitmap(hinstance,hdc,xpos,ypos,PLAYERUPMASK,SRCAND);
        drawBitmap(hinstance,hdc,xpos,ypos,PLAYERUP,SRCPAINT);
    }
    if(direction==DI_RIGHT)
    {
        drawBitmap(hinstance,hdc,xpos,ypos,PLAYERRIGHTMASK,SRCAND);
        drawBitmap(hinstance,hdc,xpos,ypos,PLAYERRIGHT,SRCPAINT);
    }
    if(direction==DI_DOWN)
    {
        drawBitmap(hinstance,hdc,xpos,ypos,PLAYERDOWNMASK,SRCAND);
        drawBitmap(hinstance,hdc,xpos,ypos,PLAYERDOWN,SRCPAINT);
    }
    if(direction==DI_LEFT)
    {
        drawBitmap(hinstance,hdc,xpos,ypos,PLAYERLEFTMASK,SRCAND);
        drawBitmap(hinstance,hdc,xpos,ypos,PLAYERLEFT,SRCPAINT);
    }
    ReleaseDC(hwnd,hdc);
}

PLAYER::PLAYER()
{
}

void PLAYER::zeroInv()
{
    inv.bicarbonate=0;
    inv.carbon=0;
    inv.carbondioxide=0;
    inv.chlorine=0;
    inv.hydrogen=0;
    inv.hydrogenchloride=0;
    inv.hydroxide=0;
    inv.iron=0;
    inv.ironchloride=0;
    inv.ironoxide=0;
    inv.methane=0;
    inv.oxygen=0;
    inv.water=0;
}

void PLAYER::move(int xOff,int yOff)
{
    x+=xOff;
    y+=yOff;
}

PLAYER::PLAYER(HINSTANCE bhinstance,HWND bhwnd,int xpos,int ypos,int bAction,int bDirection)
{
    update(bhinstance,bhwnd,xpos,ypos,bAction,bDirection);
}

void PLAYER::update(HINSTANCE bhinstance,HWND bhwnd,int xpos,int ypos,int bAction,int bDirection)
{
    x=xpos-1;
    y=ypos-1;
    action=bAction;
    direction=bDirection;
    zeroInv();
    hwnd=bhwnd;
    hinstance=bhinstance;
}

#endif