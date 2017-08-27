#include "manejadorbloques.h"
#include <iostream>
ManejadorBloques::ManejadorBloques(DataFile*arch)
{
    archivo = arch;
    bm= new BloqueMaestro();
    archivo->Abrir();
    if(!archivo->isEmpty()){
        bm->Cargar(archivo);
    }
    archivo->Cerrar();

}

/*--------------------------------------------HEADER-----------------------------*/
void ManejadorBloques::FormatearDataFile()
{
    bm->Escribir(archivo);
}

void ManejadorBloques::ActualizarBloqueMaestro()
{
    bm->sigBloqueDisponible++;
    bm->Escribir(archivo);
}

/*------------------------------------------BLOQUE TABLA------------------------------*/

BloqueTabla* ManejadorBloques::AsigNBloqueT()
{
    BloqueTabla*bt;
     if(bm->sigBloqueDisponible==1){
        bt = new BloqueTabla(bm->sigBloqueDisponible);
        bm->UltimoBloqueTabla = bm->sigBloqueDisponible;
        ActualizarBloqueMaestro();
        bt->Escribir(archivo);
        return bt;
     }
    bt = CargarBloqueT(bm->UltimoBloqueTabla);
    BloqueTabla *bt2 = new BloqueTabla(bm->sigBloqueDisponible);
    bt ->sig = bt2->NumeroBloque;
    bm->UltimoBloqueTabla = bt2->NumeroBloque;
    ActualizarBloqueMaestro();
    bt->Escribir(archivo);
    bt2->Escribir(archivo);
    return bt2;
}

BloqueTabla* ManejadorBloques::CargarBloqueT(int n)
{
    BloqueTabla *bt = new BloqueTabla(n);
    bt->Cargar(archivo);
    return bt;
}

/*-------------------------------------BLOQUE CAMPO-----------------------------------*/

BloqueCampo * ManejadorBloques::AsigNBloqueC(Tabla *t)
{
    BloqueTabla *bt = CargarBloqueT(t->IdBloquePadre);
    for(std::list<Tabla*>::iterator it = bt->Tablas->begin();it!=bt->Tablas->end();it++){
        Tabla *t2  = *it;
        if(t2->Id == t->Id){
            if(t2->PrimerBloqueCampos==-1){
                t2->PrimerBloqueCampos = bm->sigBloqueDisponible;
                t2->UltimoBloqueCampos = bm->sigBloqueDisponible;
            }else{
                t2->UltimoBloqueCampos = bm->sigBloqueDisponible;
            }
            ActualizarBloqueMaestro();
            bt->Escribir(archivo);
            BloqueCampo*bc = new BloqueCampo(t2->UltimoBloqueCampos);
            bc->Escribir(archivo);
            return bc;
        }
    }
}

void ManejadorBloques::EscribirCampo(Tabla *t,char*n,int tipo)
{
    BloqueCampo *bc;
    BloqueTabla *bt = CargarBloqueT(t->IdBloquePadre);
    t = bt->getTabla(t->Id);
    if(t->PrimerBloqueCampos==-1){
        bc = AsigNBloqueC(t);
        bc->EscribirCampo(archivo,n,tipo);
    }else {
        bc = new BloqueCampo(t->UltimoBloqueCampos);
        bc->Cargar(archivo);
        if (bc->cantCampos < 17) {
            bc->EscribirCampo(archivo, n, tipo);
        }
        else {
            BloqueCampo *bc2 =  AsigNBloqueC(t);
            BloqueTabla *bt = CargarBloqueT(t->IdBloquePadre);
            Tabla*t = bt->getTabla(t->Id);
            bc2->sig = t->UltimoBloqueCampos;
            bc2->EscribirCampo(archivo, n, tipo);
        }
    }
}

Campo * ManejadorBloques::getCampo(Tabla *t,char*n)
{
    BloqueTabla *bt = CargarBloqueT(t->IdBloquePadre);
    Tabla *t2= bt->getTabla(t->Id);
    int siguiente = t2->PrimerBloqueCampos;
    do {
        BloqueCampo *bc = new BloqueCampo(siguiente);
        bc->Cargar(archivo);
        Campo *c = bc->getCampo(n);
        if(c==0){
            siguiente = bc->sig;
        }else{
            return c;
        }
    }while(siguiente!=-1);
}

/*------------------------------------------BLOQUE REGISTRO--------------------------------*/

BloqueRegistro *ManejadorBloques::AsigNBloqueR(Tabla *t)
{
    BloqueTabla *bt = CargarBloqueT(t->IdBloquePadre);
        Tabla *t2 = bt->getTabla(t->Id);
            if (t2->PrimerBloqueDatos == -1) {
                t2->PrimerBloqueDatos = bm->sigBloqueDisponible;
                t2->UltimoBloqueDatos = bm->sigBloqueDisponible;
            }
            else {
                t2->UltimoBloqueDatos = bm->sigBloqueDisponible;
            }
            ActualizarBloqueMaestro();
            bt->Escribir(archivo);
            BloqueRegistro *br = new BloqueRegistro(t2->UltimoBloqueDatos);
            return br;
}

void ManejadorBloques::EscribirRegistro(Tabla *t, Campo *c, char *d)
{
    BloqueRegistro *br;
    BloqueTabla *bt = CargarBloqueT(t->IdBloquePadre);
    Tabla*t2 = bt->getTabla(t->Id);
    if(t2->PrimerBloqueDatos==-1){
        br = AsigNBloqueR(t2);
        br->AgregarRegistro(archivo,d,c->longitud);
        br->Escribir(archivo);
    }else{
        br = new BloqueRegistro(t2->UltimoBloqueDatos);
        br->Cargar(archivo);
        if(br->getEspacioDisp()> c->longitud){
            br->AgregarRegistro(archivo,d,c->longitud);
            br->Escribir(archivo);
        }else{
            BloqueRegistro *br2 = AsigNBloqueR(t2);
            br2->AgregarRegistro(archivo,d,c->longitud);
            br->sig = br2->NumeroBloque;
            br->Escribir(archivo);
            br2->Escribir(archivo);
        }
    }
}


ManejadorBloques::~ManejadorBloques()
{
    //dtor
}

