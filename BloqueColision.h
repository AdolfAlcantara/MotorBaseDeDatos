//
// Created by Chronos-Laptop on 2/9/2017.
//

#ifndef DB_MOTOR_BLOQUECOLISION_H
#define DB_MOTOR_BLOQUECOLISION_H
#include "Idx_Entry.h"
#include "datafile.h"
#include <list>

class BloqueColision
{
public:
    BloqueColision(int);
    void insert_Idx_Entry(Idx_Entry*);
    Idx_Entry* buscar_Idx_Entry(char*n);
    void Escribir(DataFile*arch);
    void Cargar(DataFile*arch);
    virtual ~BloqueColision();

    //atributos
    int numeroBloque,
        cantIdxEntrysEntrys,
        sig,
        tamanoBloque=512;
    std::list<Idx_Entry*>*IdxEntries;

    //el bloque tiene la capacidad de soportar 17 IdxEntry's
    //512-4-4-4 =500/28(peso de IdxEntry) = 17.85

private:
    char *toChar();
    void fromChar(char*data);

};


#endif //DB_MOTOR_BLOQUECOLISION_H
