
//conversion.h


#ifndef _CONVERSION_H
#define _CONVERSION_H

#include<iostream.h>
#include<stdlib.h>

void formulatoname(char chemname[50])
{
    if(!strcmp(chemname,"Cl"))
    {
        strcpy(chemname,"Chlorine");
    }
    else if(!strcmp(chemname,"H"))
    {
        strcpy(chemname,"Hydrogen");
    }
    else if(!strcmp(chemname,"O"))
    {
        strcpy(chemname,"Oxygen");
    }
    else if(!strcmp(chemname,"Fe"))
    {
        strcpy(chemname,"Iron");
    }
    else if(!strcmp(chemname,"C"))
    {
        strcpy(chemname,"Carbon");
    }
    else if(!strcmp(chemname,"H2O"))
    {
        strcpy(chemname,"Water");
    }
    else if(!strcmp(chemname,"OH"))
    {
        strcpy(chemname,"Hydroxide");
    }
    else if(!strcmp(chemname,"CO"))
    {
        strcpy(chemname,"Carbon Dioxide");
    }
    else if(!strcmp(chemname,"FeO"))
    {
        strcpy(chemname,"Iron Oxide");
    }
    else if(!strcmp(chemname,"HCl"))
    {
        strcpy(chemname,"Hydrogen Chloride");
    }
    else if(!strcmp(chemname,"FeCl"))
    {
        strcpy(chemname,"Iron Chloride");
    }
    else if(!strcmp(chemname,"CH"))
    {
        strcpy(chemname,"Methane");
    }
    else if(!strcmp(chemname,"HCO"))
    {
        strcpy(chemname,"Bicarbonate");
    }
}

void sitoa(char text[500],short num)
{
    itoa((int)num,text,10);
}

#endif