//
// Created by Chronos-Laptop on 21/8/2017.
//

#include <iostream>
#include "bloqueregistro.h"
BloqueRegistro::BloqueRegistro(int n)
{
    NumeroBloque =n;
    cantRegCad=0;
    cantRegInt=0;
    sig=-1;
    registros = new std::list<Registro*>;
}

void BloqueRegistro::Escribir(DataFile *archivo)
{
    char*data = this->toChar();
    int pos = NumeroBloque*TamanoBloque;
    archivo->Escribir(data,pos,TamanoBloque);
}
void BloqueRegistro::Cargar(DataFile *archivo)
{
    int pos = NumeroBloque*TamanoBloque;
    char *data = archivo->Leer(pos,TamanoBloque);
    fromChar(data);
}

void BloqueRegistro::AgregarRegistro(DataFile*arch,char *d, int tamano)
{
    Registro *r = new Registro(tamano);

    if(tamano==20) {
        r->EscribirRegistro(d);
        cantRegCad++;
    }
    else{
        char data[10];
        memcpy(&data[0],&d[0], sizeof(data));
        int numero;
        sscanf(data,"%id",&numero);
        r->EscribirRegistro(numero);
        cantRegInt++;
    }
    registros->push_back(r);

}

int BloqueRegistro::getEspacioDisp()
{
    int tam = 16+(cantRegCad*28)+(cantRegInt*8);
    return 512-tam;
}


char *BloqueRegistro::toChar()
{
    char*data  = new char[TamanoBloque];
    int pos=0;
    memcpy(&data[pos],&NumeroBloque,4);
    pos+=4;
    memcpy(&data[pos],&cantRegInt,4);
    pos+=4;
    memcpy(&data[pos],&cantRegCad,4);
    pos+=4;
    memcpy(&data[pos],&sig,4);
    pos+=4;
    for(std::list<Registro*>::iterator it = registros->begin();it!=registros->end();it++){
        Registro *r = *it;
        memcpy(&data[pos],&r->longitud,4);
        pos+=4;
        if(r->longitud==20) {
            std::cout<<r->reg<<std::endl;
            memcpy(&data[pos], &r->reg[0], 20);
            pos += 20;
        }else{
            memcpy(&data[pos],&r->regdato,4);
            pos+=4;
        }
    }
    return data;
}
void BloqueRegistro::fromChar(char *data)
{
    int pos=0;
    memcpy(&NumeroBloque,&data[pos],4);
    pos+=4;
    memcpy(&cantRegInt,&data[pos],4);
    pos+=4;
    memcpy(&cantRegCad,&data[pos],4);
    pos+=4;
    memcpy(&sig,&data[pos],4);
    pos+=4;
    int sum = cantRegCad+cantRegInt;
    for(int i=0;i<sum;i++){
        Registro *reg;
        int tam = 0;
        memcpy(&tam,&data[pos],4);
        pos+=4;
        reg = new Registro(tam);
        if(tam==20) {
            memcpy(&reg->reg[0], &data[pos], tam);
            pos+=tam;
        }else{
            memcpy(&reg->regdato,&data[pos],4);
            pos+=4;
        }
        registros->push_back(reg);
    }
}

BloqueRegistro::~BloqueRegistro()
{

}
