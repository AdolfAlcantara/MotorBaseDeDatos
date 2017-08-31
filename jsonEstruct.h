//
// Created by Chronos-Laptop on 27/8/2017.
//

#ifndef DB_MOTOR_JSONESTRUCT_H
#define DB_MOTOR_JSONESTRUCT_H
#include "datafile.h"
#include "json.hpp"
#include "manejadortablas.h"

class jsonEstruct
{
public:
    jsonEstruct(ManejadorTablas*,char*);

    void Escribir();



    virtual ~jsonEstruct();


    ManejadorTablas*mt;
    DataFile*archivo;

};


#endif //DB_MOTOR_JSONESTRUCT_H
