//
// Created by Chronos-Laptop on 7/8/2017.
//

#include <cstring>
#include "campo.h"
#include "datafile.h"

Campo::Campo()
{
    strncpy(this->nombre, "", sizeof(this->nombre) - 1);
    nombre[19] = '\0';
    tipo=0;
    longitud=0;
    IdBloquePadre=-1;
}

Campo::Campo(char *nom, int t)
{
    strncpy(nombre,nom, sizeof(nombre)-1);
    nombre[19] = '\0';
    tipo = t;
    if(t==0){
        longitud = 4;
    }else{
        longitud = 20;
    }
    IdBloquePadre=-1;
}


char * Campo::toChar()
{
    char *data = new char[28];
    int pos = 0;
    memcpy(&data[pos],&nombre[0],20);
    pos+=20;
    memcpy(&data[pos],&tipo,4);
    pos+=4;
    memcpy(&data[pos],&longitud,4);
    pos+=4;
    return data;
}

void Campo::charToBloque(char*data)
{
    int pos =0;
    memcpy(&nombre[0],&data[pos],20);
    pos+=20;
    memcpy(&tipo,&data[pos],4);
    pos+=4;
    memcpy(&longitud,&data[pos],4);
    pos+=4;
}

Campo::~Campo()
{

}
