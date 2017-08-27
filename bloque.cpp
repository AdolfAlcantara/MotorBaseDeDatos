#include "bloque.h"

Bloque::Bloque(DataFile*arch)
{
    sig=0;
    archivo = arch;
}

void Bloque::Escribir()
{
    char*data = this->toChar();
    int pos = NumeroBloque*TamanoBloque;
    archivo->Escribir(data,pos,TamanoBloque);
}

void Bloque::Cargar()
{
    int pos = NumeroBloque*TamanoBloque;
    char *data = archivo->Leer(pos, TamanoBloque);
    charToBloque(data);
}

char * Bloque::toChar()
{
    char *data  = new char [TamanoBloque];
    int pos =0;
    memcpy(&data[pos],&NumeroBloque,4);
    pos+=4;
    memcpy(&data[pos],&TamanoBloque,4);
    pos+=4;
    memcpy(&data[pos],&sig,4);
    pos+=4;
    return data;

}

void Bloque::charToBloque(char *data)
{
    int pos =0;
    memcpy(&NumeroBloque,&data[pos],4);
    pos+=4;
    memcpy(&TamanoBloque,&data[pos],4);
    pos+=4;
    memcpy(&sig,&data[pos],4);
    pos+=4;
}


Bloque::~Bloque()
{
    //dtor
}
