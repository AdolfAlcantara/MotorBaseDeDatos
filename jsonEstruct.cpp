//
// Created by Chronos-Laptop on 27/8/2017.
//

#include "jsonEstruct.h"
jsonEstruct::jsonEstruct(ManejadorTablas *mt,char*arch)
{
    this->mt = mt;
    archivo = new DataFile(arch);
}

void jsonEstruct::Escribir()
{
//    BloqueTabla *bt = mt->mb->CargarBloqueT(mt->bm->PrimerBloqueTabla);
//    do{
//        for(std::list<Tabla*>::iterator t=bt->Tablas->begin();t!=bt->Tablas->end();t++){
//            Tabla *tabla = *t;
//            BloqueCampo*bc = new BloqueCampo(tabla->PrimerBloqueCampos);
//            bc->Cargar(archivo);
//            for(std::list<Campo*>::iterator c = bc->campos->begin();c!=bc->campos->end();c++){
//                Campo*c;
//            }
//        }
//    }while(bt->sig!=-1);
}

jsonEstruct::~jsonEstruct()
{

}
