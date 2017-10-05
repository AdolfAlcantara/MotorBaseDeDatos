//
// Created by Chronos-Laptop on 21/8/2017.
//

#include <cstdio>
#include "Registro.h"
Registro::Registro()
{

}
Registro::Registro(int tamano)
{
    strncpy(reg,"", sizeof(reg)-1);
    reg[19] = '\0';
    longitud = tamano;
    regdato=0;
    idc=-1;
}

void Registro::EscribirRegistro(char*d,int idc)
{
    strncpy(reg, d, sizeof(reg)-1);
    reg[19] = '\0';
    this->idc = idc;
}

void Registro::EscribirRegistro(int d,int idc)
{
    regdato=d;
    this->idc = idc;
}

Registro::~Registro()
{

}
