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
}

void Registro::EscribirRegistro(char*d)
{
    strncpy(reg, d, sizeof(reg)-1);
    reg[19] = '\0';
}

void Registro::EscribirRegistro(int d)
{
    regdato=d;
}

Registro::~Registro()
{

}
