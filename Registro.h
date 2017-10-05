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

    void EscribirRegistro(char*d,int idc);
    void EscribirRegistro(int d,int idc);

    virtual ~Registro();

    char reg[20];
    int regdato;
    int longitud;
    int idc;

    /*
     * Registros de cadena pesan 28
     * Registros de int 12
     * */
};


#endif //DB_MOTOR_REGISTRO_H
