//
// Created by Chronos-Laptop on 21/8/2017.
//

#ifndef DB_MOTOR_BLOQUEREGISTRO_H
#define DB_MOTOR_BLOQUEREGISTRO_H
#include "Registro.h"
#include "datafile.h"
#include <list>

class BloqueRegistro
{
public:
    BloqueRegistro(int n);
    virtual ~BloqueRegistro();

    void Escribir(DataFile*);
    void Cargar(DataFile *);
    void AgregarRegistro(DataFile*,char*, int tamano);
    int getEspacioDisp();
    char *toChar();
    void fromChar(char*);


    int NumeroBloque;
    int TamanoBloque = 512;
    int cantRegInt;
    int cantRegCad;
    int sig;
    std::list<Registro*>*registros;

};


#endif //DB_MOTOR_BLOQUEREGISTRO_H
