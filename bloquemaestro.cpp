#include "bloquemaestro.h"

BloqueMaestro::BloqueMaestro()
{
    sigBloqueDisponible=1;
    UltimoBloqueTabla=0;
}

void BloqueMaestro::Escribir(DataFile*archivo)
{
    char*data = this->toChar();
    int pos = 0*TamanoBloque;
    archivo->Escribir(data,pos,TamanoBloque);
}

void BloqueMaestro::Cargar(DataFile*archivo)
{
    int pos = 0*TamanoBloque;
    char *data = archivo->Leer(pos, TamanoBloque);
    charToBloque(data);
}

char * BloqueMaestro::toChar()
{
    char *data  = new char [TamanoBloque];
    int pos =0;
    memcpy(&data[pos],&sigBloqueDisponible,4);
    pos+=4;
    memcpy(&data[pos],&TamanoBloque,4);
    pos+=4;
    memcpy(&data[pos],&PrimerBloqueTabla,4);
    pos+=4;
    memcpy(&data[pos],&UltimoBloqueTabla,4);
    pos+=4;
    return data;
}

void BloqueMaestro::charToBloque(char *data)
{
    int pos =0;
    memcpy(&sigBloqueDisponible,&data[pos],4);
    pos+=4;
    memcpy(&TamanoBloque,&data[pos],4);
    pos+=4;
    memcpy(&PrimerBloqueTabla,&data[pos],4);
    pos+=4;
    memcpy(&UltimoBloqueTabla,&data[pos],4);
    pos+=4;
}

BloqueMaestro::~BloqueMaestro()
{
    //dtor
}
