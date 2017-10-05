#include "bloquecampo.h"
#include <string.h>
BloqueCampo::BloqueCampo(int nb)
{
    NumeroBloque  = nb;
    campos = new std::list<Campo*>;
}

void BloqueCampo::Escribir(DataFile *arch)
{
    char*data = this->toChar();
    int pos = NumeroBloque*TamanoBloque;
    arch->Escribir(data,pos,TamanoBloque);
}

void BloqueCampo::Cargar(DataFile *arch)
{
    int pos = NumeroBloque*TamanoBloque;
    char*data = arch->Leer(pos,TamanoBloque);
    charToBloque(data);
}

void BloqueCampo::EscribirCampo(DataFile*arch,char*n,int tipo, int idc)
{
    Campo *c = new Campo(n, tipo,idc);
    c->IdBloquePadre = NumeroBloque;
    campos->push_back(c);
    cantCampos++;
    Escribir(arch);
}

//void BloqueCampo::LeerCampos(DataFile*arch)
//{
//    int pos = NumeroBloque*TamanoBloque;
//    char*data = arch->Cargar(pos, TamanoBloque);
//    for(int i=0;i<cantCampos;i++){
//        Campo *c = new Campo();
//        c->charToBloque(&data[pos]);
//        campos->push_back(c);
//        pos+=28;
//    }
//}

Campo* BloqueCampo::getCampo(char*nom)
{
    for(std::list<Campo*>::iterator it = campos->begin();it!=campos->end();it++) {
        Campo *c = *it;
        if (strcmp(c->nombre, nom) == 0) {
            return c;
        }
    }
    return 0;
}

char * BloqueCampo::toChar()
{
    char * data = new char[TamanoBloque];
    int pos = 0;
    memcpy(&data[pos],&NumeroBloque,4);
    pos+=4;
    memcpy(&data[pos],&TamanoBloque,4);
    pos+=4;
    memcpy(&data[pos],&sig,4);
    pos+=4;
    memcpy(&data[pos],&cantCampos,4);
    pos+=4;
//    memcpy(&data[pos],&TamanoCampos,4);
//    pos+=4;
//    memcpy(&data[pos],&TamanoHeader,4);
//    pos+=4;
    for(std::list<Campo*>::iterator it = campos->begin();it!=campos->end();it++){
        Campo *c = *it;
        memcpy(&data[pos],&c->nombre[0],20);
        pos+=20;
        memcpy(&data[pos],&c->tipo,4);
        pos+=4;
        memcpy(&data[pos],&c->longitud,4);
        pos+=4;
        memcpy(&data[pos],&c->IdBloquePadre,4);
        pos+=4;
        memcpy(&data[pos],&c->IdCampo,4);
        pos+=4;
    }
    return data;
}

void BloqueCampo::charToBloque(char *data)
{
    int pos=0;
    memcpy(&NumeroBloque,&data[pos],4);
    pos+=4;
    memcpy(&TamanoBloque,&data[pos],4);
    pos+=4;
    memcpy(&sig,&data[pos],4);
    pos+=4;
    memcpy(&cantCampos,&data[pos],4);
    pos+=4;
//    memcpy(&TamanoCampos,&data[pos],4);
//    pos+=4;
//    memcpy(&TamanoHeader,&data[pos],4);
//    pos+=4;
    for(int i=0;i<cantCampos;i++){
        Campo *c = new Campo();
        memcpy(&c->nombre[0],&data[pos],20);
        pos+=20;
        memcpy(&c->tipo,&data[pos],4);
        pos+=4;
        memcpy(&c->longitud,&data[pos],4);
        pos+=4;
        memcpy(&c->IdBloquePadre,&data[pos],4);
        pos+=4;
        memcpy(&c->IdCampo,&data[pos],4);
        pos+=4;
        campos->push_back(c);
    }
}

BloqueCampo::~BloqueCampo()
{
    //dtor
}
