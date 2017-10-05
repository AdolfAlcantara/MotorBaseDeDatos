#include "bloquemaestro.h"

BloqueMaestro::BloqueMaestro()
{
    sigBloqueDisponible=1;
    UltimoBloqueTabla=0;
}

void BloqueMaestro::Escribir(DataFile*archivo)
{
    char*data = this->toChar();
    int pos = 0*TamanoBloque;
    archivo->Escribir(data,pos,TamanoBloque);
}

void BloqueMaestro::Cargar(DataFile*archivo)
{
    int pos = 0*TamanoBloque;
    char *data = archivo->Leer(pos, TamanoBloque);
    charToBloque(data);
}

char * BloqueMaestro::toChar()
{
    char *data  = new char [TamanoBloque];
    int pos =0;
    memcpy(&data[pos],&sigBloqueDisponible,4);
    pos+=4;
    memcpy(&data[pos],&TamanoBloque,4);
    pos+=4;
    memcpy(&data[pos],&PrimerBloqueTabla,4);
    pos+=4;
    memcpy(&data[pos],&UltimoBloqueTabla,4);
    pos+=4;
    int tam = FreeBucket.size();
    memcpy(&data[pos],&tam,4);
    pos+=4;
    if(tam!=0){
        for(std::list<int>::iterator it=FreeBucket.begin();it!=FreeBucket.end();it++){
            int x = *it;
            memcpy(&data[pos],&x,4);
            pos+=4;
        }
    }
    return data;
}

void BloqueMaestro::charToBloque(char *data)
{
    int pos =0;
    memcpy(&sigBloqueDisponible,&data[pos],4);
    pos+=4;
    memcpy(&TamanoBloque,&data[pos],4);
    pos+=4;
    memcpy(&PrimerBloqueTabla,&data[pos],4);
    pos+=4;
    memcpy(&UltimoBloqueTabla,&data[pos],4);
    pos+=4;
    int tam=0;
    memcpy(&tam,&data[pos],4);
    pos+=4;
    if(tam!=0){
        for(int i=0;i<tam;i++){
            int x=0;
            memcpy(&x,&data[pos],4);
            pos+=4;
            FreeBucket.push_back(x);
        }
    }
}

BloqueMaestro::~BloqueMaestro()
{
    //dtor
}
