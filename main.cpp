
//main.cpp


#include"gameClass.h"

MAP map;
PLAYER player;
HINSTANCE hinstance;
HWND hwndMain;
int level;
bool mixing;
char mixture[50];
bool splash;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "WindowsApp";

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    hinstance=hThisInstance;
    level=1;
    mixing=false;
    splash=true;

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) 7;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "CheMaster",       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           0,       /* Windows decides the position */
           0,       /* where the window ends up on the screen */
           DEFWINWIDTH,                 /* The programs width */
           DEFWINHEIGHT,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );
           
    map.update(hThisInstance,hwnd,"level1.cgl");
    player.update(hThisInstance,hwnd,map.playerx,map.playery,AC_WALK,DI_RIGHT);

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nFunsterStil);
    hwndMain=hwnd;

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int nextSquare;
    char chemname[50];
    int chemcount;
    HDC hdc;
    hdc=GetDC(hwnd);
    
    SetTextColor(hdc,RGB(255,255,255));
    SetBkColor(hdc,RGB(0,0,0));
    switch (message)                  /* handle the messages */
    {
        case WM_LBUTTONDOWN:
            if(splash)
            {
                splash=false;
                PostMessage(hwnd,WM_PAINT,0,0);
            }
            break;
        case WM_KEYDOWN:
            if(splash)
            {
                splash=false;
                PostMessage(hwnd,WM_PAINT,0,0);
            }
            if(mixing)
            {
                char tempKey[5];
                char disp[50];
                if(KEYSTATE(VK_ESCAPE))
                {
                    mixing=false;
                    pixelRect(hdc,DEFWINWIDTH-400,0,DEFWINWIDTH,100,RGB(0,0,0));
                }
                else if((wParam==108 || wParam==107 || wParam==187) && strlen(mixture)<45)
                {
                    int length=strlen(mixture);
                    mixture[length]='+';
                    mixture[length+1]='\0';
                    strcpy(disp,"Mixture: ");
                    strcat(disp,mixture);
                    TextOut(hdc,DEFMAPWIDTH-400,20,disp,strlen(disp));
                    drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2MASK,SRCAND);
                    drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2,SRCPAINT);
                }
                else if(wParam==8 && strlen(mixture)>0)
                {
                    mixture[strlen(mixture)-1]='\0';
                    pixelRect(hdc,DEFWINWIDTH-400,0,DEFWINWIDTH,100,RGB(0,0,0));
                    TextOut(hdc,DEFWINWIDTH-400,0,"Remember, shift is not valid.",strlen("Remember, shift is not valid."));
                    TextOut(hdc,DEFWINWIDTH-400,40,"Note: When writing equations remember that some atoms",strlen("Note: When writing equations remember that some atoms"));
                    TextOut(hdc,DEFWINWIDTH-400,60,"are diatomic, but please enter the elements of your",strlen("are diatomic, but please enter the elements of your"));
                    TextOut(hdc,DEFWINWIDTH-400,80,"equation as they are shown to the left in parenthesis.",strlen("equation as they are shown to the left in parenthesis."));
                    strcpy(disp,"Mixture: ");
                    strcat(disp,mixture);
                    TextOut(hdc,DEFWINWIDTH-400,20,disp,strlen(disp));
                    drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2MASK,SRCAND);
                    drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2,SRCPAINT);
                }
                else if(wParam==13)
                {
                    pixelRect(hdc,DEFWINWIDTH-400,0,DEFWINWIDTH,100,RGB(0,0,0));
                    if(!strcmp(mixture,"2H+1O") || !strcmp(mixture,"2H+O") || !strcmp(mixture,"O+2H") || !strcmp(mixture,"1O+2H"))
                    {
                        if(player.inv.hydrogen>=2 && player.inv.oxygen>=1)
                        {
                            player.inv.water+=2;
                            player.inv.hydrogen-=2;
                            player.inv.oxygen-=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully created 2 moles of water!",strlen("You successfully created 2 moles of water!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"2H2O"))
                    {
                        if(player.inv.water>=2)
                        {
                            player.inv.water-=2;
                            player.inv.hydrogen+=2;
                            player.inv.oxygen+=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully decomposed 2 moles of water!",strlen("You successfully decomposed 2 moles of water!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"1H+1O") || !strcmp(mixture,"H+O") || !strcmp(mixture,"O+H") || !strcmp(mixture,"1O+1H"))
                    {
                        if(player.inv.hydrogen>=1 && player.inv.oxygen>=1)
                        {
                            player.inv.hydrogen-=1;
                            player.inv.hydroxide+=2;
                            player.inv.oxygen-=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully created 2 moles of Hydroxide!",strlen("You successfully created 2 moles of Hydroxide!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"2OH"))
                    {
                        if(player.inv.hydroxide>=2)
                        {
                            player.inv.hydrogen+=1;
                            player.inv.hydroxide-=2;
                            player.inv.oxygen+=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully decomposed 2 moles of Hydroxide!",strlen("You successfully decomposed 2 moles of Hydroxide!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"1C+1O") || !strcmp(mixture,"C+O") || !strcmp(mixture,"O+C") || !strcmp(mixture,"1O+1C"))
                    {
                        if(player.inv.carbon>=1 && player.inv.oxygen>=1)
                        {
                            player.inv.carbon-=1;
                            player.inv.carbondioxide+=1;
                            player.inv.oxygen-=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully created 1 mole of Carbon Dioxide!",strlen("You successfully created 1 mole of Carbon Dioxide!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"CO") || !strcmp(mixture,"1CO"))
                    {
                        if(player.inv.carbondioxide>=1)
                        {
                            player.inv.carbon+=1;
                            player.inv.carbondioxide-=1;
                            player.inv.oxygen+=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully decomposed 1 mole of Carbon Dioxide!",strlen("You successfully decomposed 1 moles of Carbon Dioxide!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"2Fe+O") || !strcmp(mixture,"2Fe+1O") || !strcmp(mixture,"O+2Fe") || !strcmp(mixture,"1O+2Fe"))
                    {
                        if(player.inv.iron>=2 && player.inv.oxygen>=1)
                        {
                            player.inv.iron-=2;
                            player.inv.ironoxide+=2;
                            player.inv.oxygen-=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully created 2 moles of Iron Oxide!",strlen("You successfully created 2 moles of Iron Oxide!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"2FeO"))
                    {
                        if(player.inv.ironoxide>=2)
                        {
                            player.inv.iron+=2;
                            player.inv.ironoxide-=2;
                            player.inv.oxygen+=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully decomposed 2 moles of Iron Oxide!",strlen("You successfully decomposed 2 moles of Iron Oxide!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"H+Cl") || !strcmp(mixture,"1H+1Cl") || !strcmp(mixture,"1Cl+1H") || !strcmp(mixture,"Cl+H"))
                    {
                        if(player.inv.hydrogen>=1 && player.inv.chlorine>=1)
                        {
                            player.inv.hydrogen-=1;
                            player.inv.hydrogenchloride+=2;
                            player.inv.chlorine-=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully created 2 moles of Hydrogen Chloride!",strlen("You successfully created 2 moles of Hydrogen Chloride!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"2HCl"))
                    {
                        if(player.inv.hydrogenchloride>=2)
                        {
                            player.inv.hydrogen+=1;
                            player.inv.hydrogenchloride-=2;
                            player.inv.chlorine+=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully decomposed 2 moles of Hydrogen Chloride!",strlen("You successfully decomposed 2 moles of Hydrogen Chloride!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"Fe+Cl") || !strcmp(mixture,"1Fe+1Cl") || !strcmp(mixture,"1Cl+1Fe") || !strcmp(mixture,"Cl+Fe"))
                    {
                        if(player.inv.iron>=1 && player.inv.chlorine>=1)
                        {
                            player.inv.iron-=1;
                            player.inv.ironchloride+=2;
                            player.inv.chlorine-=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully created 1 mole of Iron Chloride!",strlen("You successfully created 1 mole of Iron Chloride!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"FeCl") || !strcmp(mixture,"1FeCl"))
                    {
                        if(player.inv.ironchloride>=1)
                        {
                            player.inv.iron+=1;
                            player.inv.ironchloride-=1;
                            player.inv.chlorine+=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully decomposed 1 mole of Iron Chloride!",strlen("You successfully decomposed 1 mole of Iron Chloride!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"C+2H") || !strcmp(mixture,"1C+2H") || !strcmp(mixture,"2H+1C") || !strcmp(mixture,"2H+C"))
                    {
                        if(player.inv.carbon>=1 && player.inv.hydrogen>=2)
                        {
                            player.inv.carbon-=1;
                            player.inv.methane+=1;
                            player.inv.hydrogen-=2;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully created 1 mole of Methane!",strlen("You successfully created 1 mole of Methane!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"CH") || !strcmp(mixture,"1CH"))
                    {
                        if(player.inv.methane>=1)
                        {
                            player.inv.carbon+=1;
                            player.inv.methane-=1;
                            player.inv.hydrogen+=2;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully decomposed 1 mole of Methane!",strlen("You successfully decomposed 1 mole of Methane!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"H+2OH") || !strcmp(mixture,"1H+2OH") || !strcmp(mixture,"2OH+H") || !strcmp(mixture,"2OH+1H"))
                    {
                        if(player.inv.hydrogen>=1 && player.inv.hydroxide>=2)
                        {
                            player.inv.hydroxide-=2;
                            player.inv.water+=2;
                            player.inv.hydrogen-=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully created 1 mole of water!",strlen("You successfully created 1 mole of water!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"H+2CO") || !strcmp(mixture,"1H+2CO") || !strcmp(mixture,"2CO+1H") || !strcmp(mixture,"2CO+H"))
                    {
                        if(player.inv.hydrogen>=1 && player.inv.carbondioxide>=2)
                        {
                            player.inv.carbondioxide-=2;
                            player.inv.bicarbonate+=2;
                            player.inv.hydrogen-=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully created 2 moles of Bicarbonate!",strlen("You successfully created 2 moles of Bicarbonate!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"2HCO"))
                    {
                        if(player.inv.bicarbonate>=2)
                        {
                            player.inv.carbondioxide+=2;
                            player.inv.bicarbonate-=2;
                            player.inv.hydrogen+=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully decomposed 2 moles of Bicarbonate!",strlen("You successfully decomposed 2 moles of Bicarbonate!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"Fe+H2O") || !strcmp(mixture,"1Fe+1H2O") || !strcmp(mixture,"1H2O+1Fe") || !strcmp(mixture,"H2O+Fe"))
                    {
                        if(player.inv.iron>=1 && player.inv.water>=1)
                        {
                            player.inv.water-=1;
                            player.inv.ironoxide+=1;
                            player.inv.hydrogen+=1;
                            player.inv.iron-=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully created a single replacement reaction!",strlen("You successfully created a single replacement reaction!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"H+FeO") || !strcmp(mixture,"1H+1FeO") || !strcmp(mixture,"FeO+H") || !strcmp(mixture,"1FeO+1H"))
                    {
                        if(player.inv.hydrogen>=1 && player.inv.ironoxide>=1)
                        {
                            player.inv.water+=1;
                            player.inv.ironoxide-=1;
                            player.inv.hydrogen-=1;
                            player.inv.iron+=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully created a single replacement reaction!",strlen("You successfully created a single replacement reaction!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"H+FeCl") || !strcmp(mixture,"1H+1FeCl") || !strcmp(mixture,"1FeCl+1H") || !strcmp(mixture,"FeCl+H"))
                    {
                        if(player.inv.hydrogen>=1 && player.inv.ironchloride>=1)
                        {
                            player.inv.hydrogenchloride+=2;
                            player.inv.hydrogen-=1;
                            player.inv.ironchloride-=1;
                            player.inv.iron+=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully created a single replacement reaction!",strlen("You successfully created a single replacement reaction!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"Fe+2HCl") || !strcmp(mixture,"1Fe+2HCl") || !strcmp(mixture,"2HCl+1Fe") || !strcmp(mixture,"2HCl+Fe"))
                    {
                        if(player.inv.hydrogenchloride>=2 && player.inv.iron>=1)
                        {
                            player.inv.hydrogenchloride-=1;
                            player.inv.hydrogen+=1;
                            player.inv.ironchloride+=1;
                            player.inv.iron-=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully created a single replacement reaction!",strlen("You successfully created a single replacement reaction!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"FeCl+H2O") || !strcmp(mixture,"1FeCl+1H2O") || !strcmp(mixture,"H2O+FeCl") || !strcmp(mixture,"1H2O+1FeCl"))
                    {
                        if(player.inv.ironchloride>=1 && player.inv.water>=1)
                        {
                            player.inv.hydrogenchloride+=2;
                            player.inv.ironoxide+=1;
                            player.inv.ironchloride-=1;
                            player.inv.water-=1;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully created a double replacement reaction!",strlen("You successfully created a double replacement reaction!"));
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else if(!strcmp(mixture,"CH+2O") || !strcmp(mixture,"1CH+2O") || !strcmp(mixture,"2O+1CH") || !strcmp(mixture,"2O+CH"))
                    {
                        if(player.inv.methane>=1 && player.inv.oxygen>=2)
                        {
                            player.inv.methane-=1;
                            player.inv.oxygen-=2;
                            player.inv.carbondioxide+=1;
                            player.inv.water+=2;
                            TextOut(hdc,DEFWINWIDTH-400,0,"You successfully created a combustion reaction!",strlen("You successfully created a combustion reaction!"));
                            if(player.direction==DI_UP)
                            {
                                drawBitmap(hinstance,hdc,((player.x)*64+DEFMAPX),((player.y-1)*64+DEFMAPY),EXPLOSIONMASK,SRCAND);
                                drawBitmap(hinstance,hdc,((player.x)*64+DEFMAPX),((player.y-1)*64+DEFMAPY),EXPLOSION,SRCPAINT);
                                for(long i=0;i<100000000;i++)
                                {
                                }
                                if(map.square[player.x][player.y-1]==WOODDOOR)
                                {
                                    map.square[player.x][player.y-1]=WOODDOORBURNT;
                                }
                                map.draw(player.x,player.y-1);
                            }
                            if(player.direction==DI_RIGHT)
                            {
                                drawBitmap(hinstance,hdc,((player.x+1)*64+DEFMAPX),((player.y)*64+DEFMAPY),EXPLOSIONMASK,SRCAND);
                                drawBitmap(hinstance,hdc,((player.x+1)*64+DEFMAPX),((player.y)*64+DEFMAPY),EXPLOSION,SRCPAINT);
                                for(long i=0;i<100000000;i++)
                                {
                                }
                                if(map.square[player.x+1][player.y]==WOODDOOR)
                                {
                                    map.square[player.x+1][player.y]=WOODDOORBURNT;
                                }
                                map.draw(player.x+1,player.y);
                            }
                            if(player.direction==DI_DOWN)
                            {
                                drawBitmap(hinstance,hdc,((player.x)*64+DEFMAPX),((player.y+1)*64+DEFMAPY),EXPLOSIONMASK,SRCAND);
                                drawBitmap(hinstance,hdc,((player.x)*64+DEFMAPX),((player.y+1)*64+DEFMAPY),EXPLOSION,SRCPAINT);
                                for(long i=0;i<100000000;i++)
                                {
                                }
                                if(map.square[player.x][player.y+1]==WOODDOOR)
                                {
                                    map.square[player.x][player.y+1]=WOODDOORBURNT;
                                }
                                map.draw(player.x,player.y+1);
                            }
                            if(player.direction==DI_LEFT)
                            {
                                drawBitmap(hinstance,hdc,((player.x-1)*64+DEFMAPX),((player.y)*64+DEFMAPY),EXPLOSIONMASK,SRCAND);
                                drawBitmap(hinstance,hdc,((player.x-1)*64+DEFMAPX),((player.y)*64+DEFMAPY),EXPLOSION,SRCPAINT);
                                for(long i=0;i<100000000;i++)
                                {
                                }
                                if(map.square[player.x-1][player.y]==WOODDOOR)
                                {
                                    map.square[player.x-1][player.y]=WOODDOORBURNT;
                                }
                                map.draw(player.x-1,player.y);
                            }
                        }
                        else
                        {
                            TextOut(hdc,DEFWINWIDTH-400,0,"You do not have the resources to do that!",strlen("You do not have the resources to do that!"));
                        }
                    }
                    else
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"It isn't a good idea to mix those elements in those quantities.",strlen("It isn't a good idea to mix those elements in those quantities."));
                    }
                    drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2MASK,SRCAND);
                    drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2,SRCPAINT);
                    player.showInventory();
                    mixing=false;
                }
                else if(wParam!=16 && strlen(mixture)<45 && wParam!=8 && wParam>48 && wParam<90)
                {
                    pixelRect(hdc,DEFWINWIDTH-400,0,DEFWINWIDTH,100,RGB(0,0,0));
                    TextOut(hdc,DEFWINWIDTH-400,0,"Remember, shift is not valid.",strlen("Remember, shift is not valid."));
                    TextOut(hdc,DEFWINWIDTH-400,40,"Note: When writing equations remember that some atoms",strlen("Note: When writing equations remember that some atoms"));
                    TextOut(hdc,DEFWINWIDTH-400,60,"are diatomic, but please enter the elements of your",strlen("are diatomic, but please enter the elements of your"));
                    TextOut(hdc,DEFWINWIDTH-400,80,"equation as they are shown to the left in parenthesis.",strlen("equation as they are shown to the left in parenthesis."));
                    //itoa(wParam,&tempKey[0],10);
                    tempKey[0]=wParam;
                    tempKey[1]='\0';
                    strcat(mixture,tempKey);
                    if(strlen(mixture)>1)
                    {
                        if(mixture[strlen(mixture)-1]=='L' && mixture[strlen(mixture)-2]=='C')
                        {
                            mixture[strlen(mixture)-1]='l';
                        }
                        if(mixture[strlen(mixture)-1]=='E' && mixture[strlen(mixture)-2]=='F')
                        {
                            mixture[strlen(mixture)-1]='e';
                        }
                    }
                    strcpy(disp,"Mixture: ");
                    strcat(disp,mixture);
                    TextOut(hdc,DEFWINWIDTH-400,20,disp,strlen(disp));
                    drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2MASK,SRCAND);
                    drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2,SRCPAINT);
                }
            }
            else
            {
            if(KEYSTATE(0x57)) //w
            {
                pixelRect(hdc,DEFWINWIDTH-400,0,DEFWINWIDTH,100,RGB(0,0,0));
                if(player.direction==DI_UP)
                {
                    if(player.inv.water<1)
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"You don't have any water.",strlen("You don't have any water."));
                    }
                    else if(map.square[player.x][player.y-1]==HOLE)
                    {
                        map.square[player.x][player.y-1]=WATERHOLE;
                        map.draw(player.x,player.y-1);
                        player.inv.water--;
                        TextOut(hdc,DEFWINWIDTH-400,0,"1 mole of water was dumped in the hole.",strlen("1 mole of water was dumped in the hole."));
                        TextOut(hdc,DEFWINWIDTH-400,20,"Surprisingly this fills it enough for you to swim past it.",strlen("Surprisingly this fills it enough for you to swim past it."));
                    }
                    else
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"Why waste the water here?",strlen("Why waste the water here?"));
                    }
                }
                if(player.direction==DI_RIGHT)
                {
                    if(player.inv.water<1)
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"You don't have any water.",strlen("You don't have any water."));
                    }
                    else if(map.square[player.x+1][player.y]==HOLE)
                    {
                        map.square[player.x+1][player.y]=WATERHOLE;
                        map.draw(player.x+1,player.y);
                        player.inv.water--;
                        TextOut(hdc,DEFWINWIDTH-400,0,"1 mole of water was dumped in the hole.",strlen("1 mole of water was dumped in the hole."));
                        TextOut(hdc,DEFWINWIDTH-400,20,"Surprisingly this fills it enough for you to swim past it.",strlen("Surprisingly this fills it enough for you to swim past it."));
                    }
                    else
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"Why waste the water here?",strlen("Why waste the water here?"));
                    }
                }
                if(player.direction==DI_DOWN)
                {
                    if(player.inv.water<1)
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"You don't have any water.",strlen("You don't have any water."));
                    }
                    else if(map.square[player.x][player.y+1]==HOLE)
                    {
                        map.square[player.x][player.y+1]=WATERHOLE;
                        map.draw(player.x,player.y+1);
                        player.inv.water--;
                        TextOut(hdc,DEFWINWIDTH-400,0,"1 mole of water was dumped in the hole.",strlen("1 mole of water was dumped in the hole."));
                        TextOut(hdc,DEFWINWIDTH-400,20,"Surprisingly this fills it enough for you to swim past it.",strlen("Surprisingly this fills it enough for you to swim past it."));
                    }
                    else
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"Why waste the water here?",strlen("Why waste the water here?"));
                    }
                }
                if(player.direction==DI_LEFT)
                {
                    if(player.inv.water<1)
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"You don't have any water.",strlen("You don't have any water."));
                    }
                    else if(map.square[player.x-1][player.y]==HOLE)
                    {
                        map.square[player.x-1][player.y]=WATERHOLE;
                        map.draw(player.x-1,player.y);
                        player.inv.water--;
                        TextOut(hdc,DEFWINWIDTH-400,0,"1 mole of water was dumped in the hole.",strlen("1 mole of water was dumped in the hole."));
                        TextOut(hdc,DEFWINWIDTH-400,20,"Surprisingly this fills it enough for you to swim past it.",strlen("Surprisingly this fills it enough for you to swim past it."));          }
                    else
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"Why waste the water here?",strlen("Why waste the water here?"));
                    }
                }
                drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2MASK,SRCAND);
                drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2,SRCPAINT);
                player.showInventory();
            }
            if(KEYSTATE(0x52)) //r
            {
                pixelRect(hdc,DEFWINWIDTH-400,0,DEFWINWIDTH,100,RGB(0,0,0));
                if(player.direction==DI_UP)
                {
                    if(player.inv.ironoxide<1)
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"You don't have any Iron Oxide.",strlen("You don't have any Iron Oxide."));
                    }
                    else if(map.square[player.x][player.y-1]==METALDOOR)
                    {
                        map.square[player.x][player.y-1]=METALDOORRUSTED;
                        map.draw(player.x,player.y-1);
                        player.inv.ironoxide--;
                        TextOut(hdc,DEFWINWIDTH-400,0,"1 mole of Iron Oxide was applied to the door.",strlen("1 mole of Iron Oxide was applied to the door."));
                        TextOut(hdc,DEFWINWIDTH-400,20,"Surprisingly this causes the door to rust away.",strlen("Surprisingly this causes the door to rust away."));
                    }
                    else
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"Why waste the Iron Oxide here?",strlen("Why waste the Iron Oxide here?"));
                    }
                }
                if(player.direction==DI_RIGHT)
                {
                    if(player.inv.ironoxide<1)
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"You don't have any Iron Oxide.",strlen("You don't have any Iron Oxide."));
                    }
                    else if(map.square[player.x+1][player.y]==METALDOOR)
                    {
                        map.square[player.x+1][player.y]=METALDOORRUSTED;
                        map.draw(player.x+1,player.y);
                        player.inv.ironoxide--;
                        TextOut(hdc,DEFWINWIDTH-400,0,"1 mole of Iron Oxide was applied to the door.",strlen("1 mole of Iron Oxide was applied to the door."));
                        TextOut(hdc,DEFWINWIDTH-400,20,"Surprisingly this causes the door to rust away.",strlen("Surprisingly this causes the door to rust away."));
                    }
                    else
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"Why waste the Iron Oxide here?",strlen("Why waste the Iron Oxide here?"));
                    }
                }
                if(player.direction==DI_DOWN)
                {
                    if(player.inv.ironoxide<1)
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"You don't have any Iron Oxide.",strlen("You don't have any Iron Oxide."));
                    }
                    else if(map.square[player.x][player.y+1]==METALDOOR)
                    {
                        map.square[player.x][player.y+1]=METALDOORRUSTED;
                        map.draw(player.x,player.y+1);
                        player.inv.ironoxide--;
                        TextOut(hdc,DEFWINWIDTH-400,0,"1 mole of Iron Oxide was applied to the door.",strlen("1 mole of Iron Oxide was applied to the door."));
                        TextOut(hdc,DEFWINWIDTH-400,20,"Surprisingly this causes the door to rust away.",strlen("Surprisingly this causes the door to rust away."));
                    }
                    else
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"Why waste the Iron Oxide here?",strlen("Why waste the Iron Oxide here?"));
                    }
                }
                if(player.direction==DI_LEFT)
                {
                    if(player.inv.ironoxide<1)
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"You don't have any Iron Oxide.",strlen("You don't have any Iron Oxide."));
                    }
                    else if(map.square[player.x-1][player.y]==METALDOOR)
                    {
                        map.square[player.x-1][player.y]=METALDOORRUSTED;
                        map.draw(player.x-1,player.y);
                        player.inv.ironoxide--;
                        TextOut(hdc,DEFWINWIDTH-400,0,"1 mole of Iron Oxide was applied to the door.",strlen("1 mole of Iron Oxide was applied to the door."));
                        TextOut(hdc,DEFWINWIDTH-400,20,"Surprisingly this causes the door to rust away.",strlen("Surprisingly this causes the door to rust away."));
                    }
                    else
                    {
                        TextOut(hdc,DEFWINWIDTH-400,0,"Why waste the Iron Oxide here?",strlen("Why waste the Iron Oxide here?"));
                    }
                }
                drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2MASK,SRCAND);
                drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2,SRCPAINT);
                player.showInventory();
            }
            if(KEYSTATE(77))
            {
                mixing=true;
                strcpy(mixture,"");
                pixelRect(hdc,DEFWINWIDTH-400,0,DEFWINWIDTH,100,RGB(0,0,0));
                TextOut(hdc,DEFWINWIDTH-400,0,"Remember, shift is not valid.",strlen("Remember, shift is not valid."));
                TextOut(hdc,DEFWINWIDTH-400,20,"Mixture: ",strlen("Mixture: "));
                TextOut(hdc,DEFWINWIDTH-400,40,"Note: When writing equations remember that some atoms",strlen("Note: When writing equations remember that some atoms"));
                TextOut(hdc,DEFWINWIDTH-400,60,"are diatomic, but please enter the elements of your",strlen("are diatomic, but please enter the elements of your"));
                TextOut(hdc,DEFWINWIDTH-400,80,"equation as they are shown to the left in parenthesis.",strlen("equation as they are shown to the left in parenthesis."));
                drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2MASK,SRCAND);
                drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2,SRCPAINT);
            }
            if(KEYSTATE(73))
            {
                player.showInventory();
            }
            if(KEYSTATE(VK_SPACE))
            {
                if(player.direction==DI_UP)
                {
                    nextSquare=map.square[player.x][player.y-1];
                    chemcount=map.itemCount[player.x][player.y-1];
                    if(chemcount>0)
                    {
                        strcpy(chemname,map.itemName[player.x][player.y-1]);
                    }
                }
                if(player.direction==DI_RIGHT)
                {
                    nextSquare=map.square[player.x+1][player.y];
                    chemcount=map.itemCount[player.x+1][player.y];
                    if(chemcount>0)
                    {
                        strcpy(chemname,map.itemName[player.x+1][player.y]);
                    }
                }
                if(player.direction==DI_DOWN)
                {
                    nextSquare=map.square[player.x][player.y+1];
                    chemcount=map.itemCount[player.x][player.y+1];
                    if(chemcount>0)
                    {
                        strcpy(chemname,map.itemName[player.x][player.y+1]);
                    }
                }
                if(player.direction==DI_LEFT)
                {
                    nextSquare=map.square[player.x-1][player.y];
                    chemcount=map.itemCount[player.x-1][player.y];
                    if(chemcount>0)
                    {
                        strcpy(chemname,map.itemName[player.x-1][player.y]);
                    }
                }
                switch(nextSquare)
                {
                        case WOODDOORBURNT:
                            pixelRect(hdc,DEFWINWIDTH-400,0,DEFWINWIDTH,100,RGB(0,0,0));
                            TextOut(hdc,DEFWINWIDTH-400,0,"There is a door that has burned down in front of",strlen("There is a door that has burned down in front of"));
                            TextOut(hdc,DEFWINWIDTH-400,20,"you. You can walk through it to get to the other side.",strlen("you. You can walk through it to get to the other side."));
                            drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2MASK,SRCAND);
                            drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2,SRCPAINT);
                            break;
                        case WATERHOLE:
                            pixelRect(hdc,DEFWINWIDTH-400,0,DEFWINWIDTH,100,RGB(0,0,0));
                            TextOut(hdc,DEFWINWIDTH-400,0,"There is a hole filled with water in front of",strlen("There is a hole filled with water in front of"));
                            TextOut(hdc,DEFWINWIDTH-400,20,"you. You can swim through it to get to the other side.",strlen("you. You can swim through it to get to the other side."));
                            drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2MASK,SRCAND);
                            drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2,SRCPAINT);
                            break;
                        case ROCKWALL:
                            pixelRect(hdc,DEFWINWIDTH-400,0,DEFWINWIDTH,100,RGB(0,0,0));
                            TextOut(hdc,DEFWINWIDTH-400,0,"There appears to be a large boulder in front",strlen("There appears to be a large boulder in front"));
                            TextOut(hdc,DEFWINWIDTH-400,20,"of you. No use trying to get by it.",strlen("of you. No use trying to get by it."));
                            drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2MASK,SRCAND);
                            drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2,SRCPAINT);
                            break;
                        case WOODDOOR:
                            pixelRect(hdc,DEFWINWIDTH-400,0,DEFWINWIDTH,100,RGB(0,0,0));
                            TextOut(hdc,DEFWINWIDTH-400,0,"There appears to be a wooden door in front",strlen("There appears to be a wooden door in front"));
                            TextOut(hdc,DEFWINWIDTH-400,20,"of you. There might be a way to get by it, though.",strlen("of you. There might be a way to get by it, though."));
                            drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2MASK,SRCAND);
                            drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2,SRCPAINT);
                            break;
                        case METALDOOR:
                            pixelRect(hdc,DEFWINWIDTH-400,0,DEFWINWIDTH,100,RGB(0,0,0));
                            TextOut(hdc,DEFWINWIDTH-400,0,"There appears to be a metal door in front",strlen("There appears to be a metal door in front"));
                            TextOut(hdc,DEFWINWIDTH-400,20,"of you. There might be a way to get by it, though.",strlen("of you. There might be a way to get by it, though."));
                            drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2MASK,SRCAND);
                            drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2,SRCPAINT);
                            break;
                        case HOLE:
                            pixelRect(hdc,DEFWINWIDTH-400,0,DEFWINWIDTH,100,RGB(0,0,0));
                            TextOut(hdc,DEFWINWIDTH-400,0,"There appears to be a hole in front",strlen("There appears to be a hole in front"));
                            TextOut(hdc,DEFWINWIDTH-400,20,"of you. There might be a way to get by it, though.",strlen("of you. There might be a way to get by it, though."));
                            drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2MASK,SRCAND);
                            drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2,SRCPAINT);
                            break;
                        case EXIT:
                            pixelRect(hdc,DEFWINWIDTH-400,0,DEFWINWIDTH,100,RGB(0,0,0));
                            TextOut(hdc,DEFWINWIDTH-400,0,"The exit is just ahead. Pass through to move on.",strlen("The exit is just ahead. Pass through to move on."));
                            drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2MASK,SRCAND);
                            drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2,SRCPAINT);
                            break;
                        default:
                            pixelRect(hdc,DEFWINWIDTH-400,0,DEFWINWIDTH,100,RGB(0,0,0));
                            if(chemcount>0)
                            {
                                formulatoname(chemname);
                                char chemdisplayName[50];
                                char quantity[25];
                                char quant[5];
                                strcpy(quantity,"Quantity: ");
                                itoa(chemcount,&quant[0],10);
                                strcat(quantity,quant);
                                strcpy(chemdisplayName,"Chemical Name: ");
                                strcat(chemdisplayName,chemname);
                                TextOut(hdc,DEFWINWIDTH-400,0,"There is a chemical in front of you.",strlen("There is a chemical in front of you."));
                                TextOut(hdc,DEFWINWIDTH-400,20,chemdisplayName,strlen(chemdisplayName));
                                TextOut(hdc,DEFWINWIDTH-400,40,quantity,strlen(quantity));
                            }
                            else
                            {
                                TextOut(hdc,DEFWINWIDTH-400,0,"There is nothing but dirt in front of you.",strlen("There is nothing but dirt in front of you."));
                            }
                            drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2MASK,SRCAND);
                            drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2,SRCPAINT);
                            break;
                }
            }
            if(KEYSTATE(VK_UP))
            {
                if(player.y>0 && map.square[player.x][player.y-1]!=ROCKWALL && map.square[player.x][player.y-1]!=HOLE && map.square[player.x][player.y-1]!=METALDOOR && map.square[player.x][player.y-1]!=WOODDOOR)
                {
                    player.move(0,-1);
                    map.draw(player.x,player.y+1);
                }
                else
                {
                    map.draw(player.x,player.y);
                }
                player.direction=DI_UP;
            }
            if(KEYSTATE(VK_RIGHT))
            {
                if(player.x<ROWS && map.square[player.x+1][player.y]!=ROCKWALL && map.square[player.x+1][player.y]!=HOLE && map.square[player.x+1][player.y]!=METALDOOR && map.square[player.x+1][player.y]!=WOODDOOR)
                {
                    player.move(1,0);
                    map.draw(player.x-1,player.y);
                }
                else
                {
                    map.draw(player.x,player.y);
                }
                player.direction=DI_RIGHT;
            }
            if(KEYSTATE(VK_DOWN))
            {
                if(player.y<COLS && map.square[player.x][player.y+1]!=ROCKWALL && map.square[player.x][player.y+1]!=HOLE && map.square[player.x][player.y+1]!=METALDOOR && map.square[player.x][player.y+1]!=WOODDOOR)
                {
                    player.move(0,1);
                    map.draw(player.x,player.y-1);
                }
                else
                {
                    map.draw(player.x,player.y);
                }
                player.direction=DI_DOWN;
            }
            if(KEYSTATE(VK_LEFT))
            {
                if(player.x>0 && map.square[player.x-1][player.y]!=ROCKWALL && map.square[player.x-1][player.y]!=HOLE && map.square[player.x-1][player.y]!=METALDOOR && map.square[player.x-1][player.y]!=WOODDOOR)
                {
                    player.move(-1,0);
                    map.draw(player.x+1,player.y);
                }
                else
                {
                    map.draw(player.x,player.y);
                }
                player.direction=DI_LEFT;
            }
            if(map.square[player.x][player.y]==EXIT)
            {
                char nextlevel[50];
                char levelnum[5];
                level++;
                strcpy(nextlevel,"level");
                itoa(level,&levelnum[0],10);
                strcat(nextlevel,levelnum);
                strcat(nextlevel,".cgl");
                map.update(hinstance,hwndMain,nextlevel);
                player.update(hinstance,hwndMain,map.playerx,map.playery,AC_WALK,DI_RIGHT);
                PostMessage(hwnd,WM_PAINT,0,0);
            }
            else if(map.itemCount[player.x][player.y]>0)
            {
                if(!strcmp(map.itemName[player.x][player.y],"H"))
                {
                    player.inv.hydrogen+=map.itemCount[player.x][player.y];
                    map.itemCount[player.x][player.y]=0;
                }
                if(!strcmp(map.itemName[player.x][player.y],"O"))
                {
                    player.inv.oxygen+=map.itemCount[player.x][player.y];
                    map.itemCount[player.x][player.y]=0;
                }
                if(!strcmp(map.itemName[player.x][player.y],"Cl"))
                {
                    player.inv.chlorine+=map.itemCount[player.x][player.y];
                    map.itemCount[player.x][player.y]=0;
                }
                if(!strcmp(map.itemName[player.x][player.y],"Fe"))
                {
                    player.inv.iron+=map.itemCount[player.x][player.y];
                    map.itemCount[player.x][player.y]=0;
                }
                if(!strcmp(map.itemName[player.x][player.y],"C"))
                {
                    player.inv.carbon+=map.itemCount[player.x][player.y];
                    map.itemCount[player.x][player.y]=0;
                }
                if(!strcmp(map.itemName[player.x][player.y],"H2O"))
                {
                    player.inv.water+=map.itemCount[player.x][player.y];
                    map.itemCount[player.x][player.y]=0;
                }
                if(!strcmp(map.itemName[player.x][player.y],"OH"))
                {
                    player.inv.hydroxide+=map.itemCount[player.x][player.y];
                    map.itemCount[player.x][player.y]=0;
                }
                if(!strcmp(map.itemName[player.x][player.y],"CO"))
                {
                    player.inv.carbondioxide+=map.itemCount[player.x][player.y];
                    map.itemCount[player.x][player.y]=0;
                }
                if(!strcmp(map.itemName[player.x][player.y],"FeO"))
                {
                    player.inv.ironoxide+=map.itemCount[player.x][player.y];
                    map.itemCount[player.x][player.y]=0;
                }
                if(!strcmp(map.itemName[player.x][player.y],"HCl"))
                {
                    player.inv.hydrogenchloride+=map.itemCount[player.x][player.y];
                    map.itemCount[player.x][player.y]=0;
                }
                if(!strcmp(map.itemName[player.x][player.y],"FeCl"))
                {
                    player.inv.ironchloride+=map.itemCount[player.x][player.y];
                    map.itemCount[player.x][player.y]=0;
                }
                if(!strcmp(map.itemName[player.x][player.y],"CH"))
                {
                    player.inv.methane+=map.itemCount[player.x][player.y];
                    map.itemCount[player.x][player.y]=0;
                }
                if(!strcmp(map.itemName[player.x][player.y],"HCO"))
                {
                    player.inv.bicarbonate+=map.itemCount[player.x][player.y];
                    map.itemCount[player.x][player.y]=0;
                }
                map.draw(player.x,player.y);
                player.draw();
                player.showInventory();
            }
            player.draw();
            }
            break;
        case WM_PAINT:
            if(splash)
            {
                drawBitmap(hinstance,hdc,90,25,SPLASH,SRCCOPY);
            }
            else
            {
                pixelRect(hdc,0,0,DEFWINWIDTH,100,RGB(0,0,0));
                //drawBitmap(hinstance,hdc,0,0,TITLEBARMASK,SRCAND);
                //drawBitmap(hinstance,hdc,0,0,TITLEBAR,SRCPAINT);
                drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2MASK,SRCAND);
                drawBitmap(hinstance,hdc,DEFWINWIDTH-400,0,TITLEBAR2,SRCPAINT);
                map.draw();
                player.draw();
                player.showInventory();
            }
            return DefWindowProc (hwnd, message, wParam, lParam);
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            ReleaseDC(hwnd,hdc);
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    ReleaseDC(hwnd,hdc);

    return 0;
}


/*int ShowBitmapResource(HDC hDestDC, int xDest, int yDest, int nResID,int method)
{
  HDC hSrcDC;           // source DC - memory device context
  HBITMAP hbitmap;      // handle to the bitmap resource
  BITMAP bmp;           // structure for bitmap info
  int nHeight, nWidth;  // bitmap dimensions

  // first load the bitmap resource
  if ((hbitmap = (HBITMAP)LoadImage(hinstance, MAKEINTRESOURCE(nResID),
                                    IMAGE_BITMAP, 0, 0,
                                    LR_CREATEDIBSECTION)) == NULL)
    return(5);

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
}*/
