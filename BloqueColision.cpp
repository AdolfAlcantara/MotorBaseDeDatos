//
// Created by Chronos-Laptop on 2/9/2017.
//

#include <cstring>
#include <iostream>
#include "BloqueColision.h"
BloqueColision::BloqueColision(int nb)
{
    numeroBloque=nb;
    cantIdxEntrysEntrys=0;
    sig=-1;
    IdxEntries = new std::list<Idx_Entry*>;
}

void BloqueColision::Escribir(DataFile *arch)
{
    char*data = this->toChar();
    int pos=numeroBloque*tamanoBloque;
    arch->Escribir(data,pos,tamanoBloque);
}
void BloqueColision::Cargar(DataFile *arch)
{
    int pos = numeroBloque*tamanoBloque;
    char *data = arch->Leer(pos,tamanoBloque);
    fromChar(data);
}

void BloqueColision::insert_Idx_Entry(Idx_Entry *ide)
{
    IdxEntries->push_back(ide);
    cantIdxEntrysEntrys++;
}

Idx_Entry *BloqueColision::buscar_Idx_Entry(char *n)
{
    for(std::list<Idx_Entry*>::iterator it = IdxEntries->begin();it!=IdxEntries->end();it++) {
        Idx_Entry *ide = *it;
//        char *tempchar = ide->id;
//        std::cout<<ide->id<<std::endl;
        if(strcmp(n,ide->id)==0){
            return ide;
        }
    }
    return NULL;
}

char *BloqueColision::toChar()
{
    char*data = new char[tamanoBloque];
    int pos=0;
    memcpy(&data[pos],&numeroBloque,4);
    pos+=4;
    memcpy(&data[pos],&cantIdxEntrysEntrys,4);
    pos+=4;
    memcpy(&data[pos],&sig,4);
    pos+=4;
    std::cout<<IdxEntries->size()<<std::endl;
    for(std::list<Idx_Entry*>::iterator it = IdxEntries->begin();it!=IdxEntries->end();it++){
        Idx_Entry *ide = *it;
        std::cout<<ide->id<<std::endl;
        std::cout<<ide->numeroRegRel<<std::endl;
        std::cout<<ide->numeroBloque<<std::endl;
        memcpy(&data[pos],&ide->id[0],20);
        pos+= 20;
        memcpy(&data[pos],&ide->numeroBloque,4);
        pos+=4;
        memcpy(&data[pos],&ide->numeroRegRel,4);
        pos+=4;
    }

    return data;
}
void BloqueColision::fromChar(char *data)
{
    int pos=0;
    memcpy(&numeroBloque,&data[pos],4);
    pos+=4;
    memcpy(&cantIdxEntrysEntrys,&data[pos],4);
    pos+=4;
    memcpy(&sig,&data[pos],4);
    pos+=4;
    for(int i=0;i<cantIdxEntrysEntrys;i++){
        Idx_Entry *ide = new Idx_Entry();
        memcpy(&ide->id[0],&data[pos],20);
        pos+= 20;
        memcpy(&ide->numeroBloque, &data[pos],4);
        pos+=4;
        memcpy(&ide->numeroRegRel,&data[pos],4);
        pos+=4;
        IdxEntries->push_back(ide);
    }
}

BloqueColision::~BloqueColision()
{

}
