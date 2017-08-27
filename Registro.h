//
// Created by Chronos-Laptop on 21/8/2017.
//

#ifndef DB_MOTOR_REGISTRO_H
#define DB_MOTOR_REGISTRO_H
#include "campo.h"
#include <cstring>


class Registro
{
public:
    Registro();
    Registro(int);

    void EscribirRegistro(char*d);
    void EscribirRegistro(int d);

    virtual ~Registro();

    char reg[20];
    int regdato;
    int longitud;

};


#endif //DB_MOTOR_REGISTRO_H
