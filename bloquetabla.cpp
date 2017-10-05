#include <iostream>
#include "bloquetabla.h"
BloqueTabla::BloqueTabla(int nb)
{
    NumeroBloque = nb;
    Tablas = new std::list<Tabla*>;
}

Tabla* BloqueTabla::getTabla(int id)
{
    for(std::list<Tabla*>::iterator it = Tablas->begin();it!=Tablas->end();it++){
        Tabla*t = *it;
        if(t->Id == id ){
            return t;
        }
    }
    return 0;
}

void BloqueTabla::Escribir(DataFile*archivo)
{
    char*data = this->toChar();
    int pos = NumeroBloque*TamanoBloque;
    archivo->Escribir(data,pos,TamanoBloque);
}

void BloqueTabla::Cargar(DataFile*archivo)
{
    int pos = NumeroBloque*TamanoBloque;
    char *data = archivo->Leer(pos, TamanoBloque);
    charToBloque(data);
}

char* BloqueTabla::toChar()
{
    char *data = new char[TamanoBloque];
    int pos=0;
    memcpy(&data[pos],&NumeroBloque,4);
    pos+=4;
    memcpy(&data[pos],&TamanoBloque,4);
    pos+=4;
    memcpy(&data[pos],&sig,4);
    pos+=4;
    memcpy(&data[pos],&CantidadTablas,4);
    pos+=4;
    std::list<Tabla*>::iterator it;
    for(it=Tablas->begin();it!=Tablas->end();it++){
        //for(int i=0;i<CantidadTablas;i++) {
            Tabla *t = *it;
            //        char*newdata = t->toChar();
            //        memcpy(&data[pos],&newdata,24);
            //        pos+=44;
            memcpy(&data[pos],&t->nombre[0],20);
            pos+=20;
            memcpy(&data[pos], &t->Id, 4);
            pos += 4;
            memcpy(&data[pos], &t->IdBloquePadre, 4);
            pos += 4;
            memcpy(&data[pos],&t->cantCampos,4);
            pos+=4;
            memcpy(&data[pos], &t->PrimerBloqueCampos, 4);
            pos += 4;
            memcpy(&data[pos], &t->UltimoBloqueCampos, 4);
            pos += 4;
            memcpy(&data[pos], &t->PrimerBloqueDatos, 4);
            pos += 4;
            memcpy(&data[pos], &t->UltimoBloqueDatos, 4);
            pos += 4;
            memcpy(&data[pos],&t->PrimerBloqueHash,4);
            pos+=4;
            memcpy(&data[pos],&t->UltimoBloqueHash,4);
            pos+=4;
        //}
    }
    return data;
}

void BloqueTabla::charToBloque(char* data)
{
    int pos=0;
    memcpy(&NumeroBloque,&data[pos],4);
    pos+=4;
    memcpy(&TamanoBloque,&data[pos],4);
    pos+=4;
    memcpy(&sig,&data[pos],4);
    pos+=4;
    memcpy(&CantidadTablas,&data[pos],4);
    pos+=4;
    for(int i=0; i<CantidadTablas; i++){
        Tabla *t  = new Tabla();
//        t->charToBloque(data,pos);
//        Tablas->push_back(t);
        memcpy(&t->nombre[0],&data[pos],20);
        pos+=20;
        memcpy(&t->Id,&data[pos],4);
        pos+=4;
        memcpy(&t->IdBloquePadre,&data[pos],4);
        pos+=4;
        memcpy(&t->cantCampos,&data[pos],4);
        pos+=4;
        memcpy(&t->PrimerBloqueCampos,&data[pos],4);
        pos+=4;
        memcpy(&t->UltimoBloqueCampos,&data[pos],4);
        pos+=4;
        memcpy(&t->PrimerBloqueDatos,&data[pos],4);
        pos+=4;
        memcpy(&t->UltimoBloqueDatos,&data[pos],4);
        pos+=4;
        memcpy(&t->PrimerBloqueHash,&data[pos],4);
        pos+=4;
        memcpy(&t->UltimoBloqueHash,&data[pos],4);
        pos+=4;
        Tablas->push_back(t);
    }

}


BloqueTabla::~BloqueTabla()
{
    //dtor
}
