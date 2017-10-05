//
// Created by Chronos-Laptop on 2/9/2017.
//

#include <cstring>
#include <iostream>
#include "BloqueHashTable.h"
#include "BloqueColision.h"

BloqueHashTable::BloqueHashTable(int nb, int tam)
{
    numeroBloque =nb;
    tamanoBloqueHT =tam;
    cantEntrysActuales=0;
    //el tamano del entry como tal es 8 pero guardaremos tambien el valor
    //de la posicion en el array en el que se encuentra para que al cargarlo sepamos
    //en que posicion del array va
    cantEntrysPosibles = (tamanoBloqueHT-tamanoHeader)/12;
    Entry*e = new Entry();
    Entries = std::vector<Entry>(cantEntrysPosibles,*e);
//    for(int i=0;i<cantEntrysPosibles;i++){
//
//    }
}

void BloqueHashTable::Escribir(DataFile *arch)
{
    char *data = this->toChar();
    int pos = numeroBloque*tamanoBloque;
    arch->Escribir(data,pos,tamanoBloqueHT);
}

void BloqueHashTable::Cargar(DataFile *arch)
{
    int pos=numeroBloque*tamanoBloque;
    char *data = arch->Leer(pos,tamanoBloqueHT);
    fromChar(data);
}
void BloqueHashTable::insertEntry(Idx_Entry*ide)
{
    //manejador de bloques
}

//devuelve el int apuntador del primerbloquecolision de esa posicion
//la manda a llamar el BuscarReg del manejadordebloques(o es la idea)
int BloqueHashTable::Buscar(char *n)
{
    int pos =  hashear(n);
    int x = Entries[pos].PrimerBloqueColision;
    return x;
}

int BloqueHashTable::hashear(char *n)
{
    int value =0;
    for(int i=0;i<strlen(n);i++){
        value+=n[i];
    }
    return  (int)((value*strlen(n))%cantEntrysPosibles);
}

char *BloqueHashTable::toChar()
{
    char *data = new char[tamanoBloqueHT];
    int pos =0;
    memcpy(&data[pos],&numeroBloque,4);
    pos+=4;
    memcpy(&data[pos],&tamanoBloqueHT,4);
    pos+=4;
    memcpy(&data[pos],&cantEntrysActuales,4);
    pos+=4;
    memcpy(&data[pos],&cantEntrysPosibles,4);
    pos+=4;
    for(int i=0;i<cantEntrysPosibles;i++){
        if(Entries[i].PrimerBloqueColision!=-1){
            memcpy(&data[pos],&i,4);
            pos+=4;
            int pbc = Entries[i].PrimerBloqueColision;
            int ubc = Entries[i].UltimoBloqueColision;
//            std::cout<<"i: "<<i<<std::endl;
//            std::cout <<"pbc: " <<Entries[i].PrimerBloqueColision << std::endl;
//            std::cout <<"ubc: " << Entries[i].UltimoBloqueColision << std::endl;
            memcpy(&data[pos],&pbc,4);
            pos+=4;
            memcpy(&data[pos],&ubc,4);
            pos+=4;
        }
    }
    return data;
}

void BloqueHashTable::fromChar(char *data)
{
    int pos = 0;
    int contEntry = 0;
    memcpy(&numeroBloque, &data[pos], 4);
    pos += 4;
    memcpy(&tamanoBloqueHT, &data[pos], 4);
    pos += 4;
    memcpy(&cantEntrysActuales, &data[pos], 4);
    pos += 4;
    memcpy(&cantEntrysPosibles, &data[pos], 4);
    pos += 4;
    int postemp = 0;
    while (contEntry < cantEntrysActuales) {
        memcpy(&postemp, &data[pos], 4);
        pos += 4;
        if (Entries[postemp].PrimerBloqueColision = -1) {
            int pbc = 0;
            int ubc = 0;
            //        std::cout<<postemp<<std::endl;
            memcpy(&pbc, &data[pos], 4);
            pos += 4;
            //        std::cout<<"pbc: "<<pbc<<std::endl;
            Entries[postemp].PrimerBloqueColision = pbc;
            memcpy(&ubc, &data[pos], 4);
            pos += 4;
            //        std::cout<<"ubc: "<<ubc<<std::endl;
            Entries[postemp].UltimoBloqueColision = ubc;
        }
        contEntry++;
    }
}

BloqueHashTable::~BloqueHashTable()
{

}
