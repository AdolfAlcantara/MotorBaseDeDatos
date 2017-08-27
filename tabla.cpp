#include "tabla.h"
#include <iostream>

Tabla::Tabla()
{
    strncpy(this->nombre, "", sizeof(this->nombre) - 1);
    nombre[19] = '\0';
    Id = -1;
    IdBloquePadre = -1;
    PrimerBloqueCampos = -1;
    UltimoBloqueCampos = -1;
    PrimerBloqueDatos = -1;
    UltimoBloqueDatos = -1;
}

Tabla::Tabla(char *nombre, int id, int idbp)
{
    strncpy(this->nombre, nombre, sizeof(this->nombre) - 1);
    this->nombre[19] = '\0';
    this->Id = id;
    IdBloquePadre = idbp;
    PrimerBloqueCampos = -1;
    UltimoBloqueCampos = -1;
    PrimerBloqueDatos = -1;
    UltimoBloqueDatos = -1;
}

char *Tabla::toChar()
{
    char *data = new char[24];
    int pos = 0;
//    memcpy(&data[pos],&nombre,20);
//    pos+=20;
    memcpy(&data[pos], &Id, 4);
    pos += 4;
    memcpy(&data[pos], &IdBloquePadre, 4);
    pos += 4;
    memcpy(&data[pos], &PrimerBloqueCampos, 4);
    pos += 4;
    memcpy(&data[pos], &UltimoBloqueCampos, 4);
    pos += 4;
    memcpy(&data[pos], &PrimerBloqueDatos, 4);
    pos += 4;
    memcpy(&data[pos], &UltimoBloqueDatos, 4);
    pos += 4;
    return data;
}

void Tabla::charToBloque(char *data, int p)
{
    int pos = p;
//    memcpy(&nombre,&data[pos],20);
//    pos+=20;
    memcpy(&Id, &data[pos], 4);
    pos += 4;
    memcpy(&IdBloquePadre, &data[pos], 4);
    pos += 4;
    memcpy(&PrimerBloqueCampos, &data[pos], 4);
    pos += 4;
    memcpy(&UltimoBloqueCampos, &data[pos], 4);
    pos += 4;
    memcpy(&PrimerBloqueDatos, &data[pos], 4);
    pos += 4;
    memcpy(&UltimoBloqueDatos, &data[pos], 4);
    pos += 4;
}

Tabla::~Tabla()
{
    //dtor
}
