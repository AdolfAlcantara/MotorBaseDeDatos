//
// Created by Chronos-Laptop on 2/9/2017.
//

#ifndef DB_MOTOR_IDX_ENTRY_H
#define DB_MOTOR_IDX_ENTRY_H

//tamano de los Idx_Entry es de 28 bytes


class Idx_Entry
{
public:
    Idx_Entry();
    Idx_Entry(int nb, int nrr,char*n);
    virtual ~Idx_Entry();

    //atributos
    char id[20];
    int numeroBloque,
        numeroRegRel;


};


#endif //DB_MOTOR_IDX_ENTRY_H
