//
// Created by Chronos-Laptop on 27/8/2017.
//

#ifndef DB_MOTOR_JSONESTRUCT_H
#define DB_MOTOR_JSONESTRUCT_H
#include "datafile.h"
#include "json.hpp"
#include "manejadortablas.h"

using json = nlohmann::json;

class jsonEstruct
{
public:
    jsonEstruct(ManejadorTablas*);
    void Escribir();
    void Leer();



    virtual ~jsonEstruct();


    ManejadorTablas*mt;
    char*path = "..//jsonfile";
};


#endif //DB_MOTOR_JSONESTRUCT_H
