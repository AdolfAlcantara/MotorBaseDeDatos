#include "manejadortablas.h"
#include <iostream>
ManejadorTablas::ManejadorTablas(DataFile*arch)
{
    archivo = arch;
    mb = new ManejadorBloques(archivo);
    bm= mb->bm;
}

Tabla* ManejadorTablas::CrearTablas(char nombre[20])
{

    BloqueTabla *bt = mb->CargarBloqueT(bm->UltimoBloqueTabla);

    Tabla*newTable;
    list<Tabla*>::iterator it = bt->Tablas->end();
    it--;
    Tabla *t = *it;
    if(bt->CantidadTablas==0){
        newTable = new Tabla(nombre,0,bt->NumeroBloque);
        bt->Tablas->push_back(newTable);
        bt->CantidadTablas++;
        bt->Escribir(archivo);
    }else if(bt->CantidadTablas<9){
        newTable = new Tabla(nombre,t->Id+1,bt->NumeroBloque);
        bt->Tablas->push_back(newTable);
        bt->CantidadTablas++;
        bt->Escribir(archivo);
    }else{
        BloqueTabla *bt2 = mb->AsigNBloqueT();
        newTable = new Tabla(nombre,t->Id+1,bt2->NumeroBloque);
        bt2->Tablas->push_back(newTable);
        bt2->CantidadTablas++;
        bt2->Escribir(archivo);
    }
    return newTable;
}

Tabla *ManejadorTablas::BuscarTabla(char*nom)
{

    LlenarListaBloquesTabla();
    for(list<BloqueTabla*>::iterator bt = BloquesTablas.begin(); bt !=BloquesTablas.end(); bt++){
        BloqueTabla *bt2  = *bt;
        for(list<Tabla*>::iterator t = bt2->Tablas->begin(); t !=bt2->Tablas->end(); t++ ){
            Tabla* t2 = *t;
            if(strcmp(nom,t2->nombre)==0){
                return t2;
            }
        }
    }
    return 0;
}

void ManejadorTablas::ListarTablas()
{
    LlenarListaBloquesTabla();
    archivo->Abrir();
    for(list<BloqueTabla*>::iterator bt = BloquesTablas.begin(); bt !=BloquesTablas.end(); bt++){
        BloqueTabla *bt2  = *bt;
        for(list<Tabla*>::iterator t = bt2->Tablas->begin(); t !=bt2->Tablas->end(); t++ ){
            Tabla *t2 = *t;
            cout<<"nombre: "<<t2->nombre<<", Id: "<<t2->Id<<", idbp: "<<t2->IdBloquePadre<<endl;
            cout<<"pbc: "<<t2->PrimerBloqueCampos<<", ubc: "<<t2->UltimoBloqueCampos<<endl;
            cout<<"pbr: "<<t2->PrimerBloqueDatos<<", ubr: "<<t2->UltimoBloqueDatos<<endl;
        }
    }
}

//void ManejadorTablas::ListarCampos()
//{
//    LlenarListaBloquesTabla();
//    for(list<BloqueTabla*>::iterator bt = BloquesTablas.begin(); bt !=BloquesTablas.end(); bt++){
//        BloqueTabla *bt2  = *bt;
//        bt2->Cargar(archivo);
//        cout<<bt2->Tablas->size()<<endl;
//        for(list<Tabla*>::iterator t = bt2->Tablas->begin(); t !=bt2->Tablas->end(); t++ ){
//            Tabla *t2 = *t;
//            cout<<"nombre: "<<t2->nombre<<", Id: "<<t2->Id<<", idbp: "<<t2->IdBloquePadre<<endl;
//            cout<<"pbc: "<<t2->PrimerBloqueCampos<<", ubc: "<<t2->UltimoBloqueCampos<<endl;
//        }
//    }
//}


//carga todas las tablas den una lista
std::list<Tabla*>* ManejadorTablas::CargarTablas()
{
    std::list<Tabla*>*tablas = new std::list<Tabla*>;
    int siguiente = bm->PrimerBloqueTabla;
    do{
        BloqueTabla*bt = new BloqueTabla(siguiente);
        bt->Cargar(archivo);
        for(std::list<Tabla*>::iterator it = bt->Tablas->begin();it!=bt->Tablas->end();it++){
            Tabla*t = *it;
            tablas->push_back(t);
        }
        siguiente = bt->sig;
    }while(siguiente!=-1);
    return tablas;
}

void ManejadorTablas::LlenarListaBloquesTabla()
{
    if(BloquesTablas.size()!=0){
        BloquesTablas.clear();
    }
    int siguiente = 1;
    archivo->Abrir();
    do{
        BloqueTabla *bt = mb->CargarBloqueT(siguiente);
//        bt->Cargar(archivo);
        BloquesTablas.push_back(bt);
        siguiente = bt->sig;
    }while(siguiente!=-1);
    archivo->Cerrar();
}

ManejadorTablas::~ManejadorTablas()
{
    //dtor
}
