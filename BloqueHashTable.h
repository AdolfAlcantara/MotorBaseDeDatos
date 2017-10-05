//
// Created by Chronos-Laptop on 2/9/2017.
//

#ifndef DB_MOTOR_BLOQUEHASHTABLE_H
#define DB_MOTOR_BLOQUEHASHTABLE_H
#include <array>
#include "Idx_Entry.h"
#include "Entry.h"
#include "datafile.h"
#include <vector>


class BloqueHashTable
{
public:
    BloqueHashTable(int nb,int tam);
    void insertEntry(Idx_Entry*);
    int Buscar(char*n);
    int hashear(char*n);
    void Escribir(DataFile*arch);
    void Cargar(DataFile*arch);
    virtual ~BloqueHashTable();

    //atributos
    int numeroBloque,
        tamanoBloque=512,
        tamanoBloqueHT,
        cantEntrysActuales,
        cantEntrysPosibles,
        tamanoHeader = 16;

    //cantEntrysPosibles = (tamanoBloque-tamanoHeader)/8(tamano de Entry's);

    std::vector<Entry>Entries;


    //cantid de entradas posibles determinadas por la formula:
    // tamanoBloque -header =  newtamanoBloque/tamanoEntry = cantEntrysPosibles

private:
    char *toChar();
    void fromChar(char*data);


};


#endif //DB_MOTOR_BLOQUEHASHTABLE_H
