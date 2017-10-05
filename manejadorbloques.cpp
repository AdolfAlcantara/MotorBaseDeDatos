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

void ManejadorBloques::LlenarMasterBlockBucket(int pri, int fin)
{
    int contador=0;
    for(int i =pri;i<=fin;i++){
        bm->FreeBucket.push_back(i);
        contador++;
    }
    bm->Escribir(archivo);
}

int ManejadorBloques::SigBloqueDisponible()
{
    int x;
    if(!bm->FreeBucket.empty()){
        x= *bm->FreeBucket.begin();
        bm->FreeBucket.remove(*bm->FreeBucket.begin());
    }else{
        x = bm->sigBloqueDisponible;
        bm->sigBloqueDisponible++;
    }
    bm->Escribir(archivo);
    return x;
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
    int x = SigBloqueDisponible();
     if(x==1){
         bt = new BloqueTabla(x);
         bm->UltimoBloqueTabla = x;
         bm->Escribir(archivo);
//        ActualizarBloqueMaestro();
         bt->Escribir(archivo);
         return bt;
     }
    bt = CargarBloqueT(bm->UltimoBloqueTabla);
    BloqueTabla *bt2 = new BloqueTabla(SigBloqueDisponible());
    bt ->sig = bt2->NumeroBloque;
    bm->UltimoBloqueTabla = bt2->NumeroBloque;
    bm->Escribir(archivo);
//    ActualizarBloqueMaestro();
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
    Tabla *t2  = bt->getTabla(t->Id);
    if(t2->PrimerBloqueCampos==-1){
        int x = SigBloqueDisponible();
        t2->PrimerBloqueCampos = x;
        t2->UltimoBloqueCampos = x;
        bt->Escribir(archivo);
    }else{
        t2->UltimoBloqueCampos = SigBloqueDisponible();
        bt->Escribir(archivo);
    }
//            ActualizarBloqueMaestro();
    BloqueCampo*bc = new BloqueCampo(t2->UltimoBloqueCampos);
    bc->Escribir(archivo);
    return bc;
}

void ManejadorBloques::EscribirCampo(Tabla *t,char*n,int tipo)
{
    BloqueCampo *bc;
    BloqueTabla *bt = CargarBloqueT(t->IdBloquePadre);
    Tabla *t2 = bt->getTabla(t->Id);
    if (t2->PrimerBloqueCampos == -1) {
        bc = AsigNBloqueC(t2);
        bc->EscribirCampo(archivo, n, tipo, t2->cantCampos);
    }
    else {
        bc = new BloqueCampo(t2->UltimoBloqueCampos);
        bc->Cargar(archivo);
        if (bc->cantCampos < 13) {
            bc->EscribirCampo(archivo, n, tipo, t2->cantCampos);
        }
        else {
            BloqueCampo *bc2 = AsigNBloqueC(t2);
            bc2->EscribirCampo(archivo, n, tipo, t2->cantCampos);
            bc2->Escribir(archivo);
            bc->sig = bc->NumeroBloque;
            bc->Escribir(archivo);
        }
    }
    BloqueTabla*bt2 = CargarBloqueT(t2->IdBloquePadre);
    Tabla *t3 = bt2->getTabla(t2->Id);
    t3->cantCampos++;
    bt2->Escribir(archivo);
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

std::list<Campo *> *ManejadorBloques::listarCampos(Tabla *t)
{
    std::list<Campo*>*campos = new std::list<Campo*>;
    int siguiente  = t->PrimerBloqueCampos;
    do{
        BloqueCampo*bc = new BloqueCampo(siguiente);
        bc->Cargar(archivo);
        for(std::list<Campo*>::iterator it = bc->campos->begin();it!=bc->campos->end();it++){
            Campo*c = *it;
            campos->push_back(c);
        }
        siguiente = bc->sig;
    }while(siguiente!=-1);
    return campos;
}

/*------------------------------------------BLOQUE REGISTRO--------------------------------*/

BloqueRegistro *ManejadorBloques::AsigNBloqueR(Tabla *t)
{
    BloqueTabla *bt = CargarBloqueT(t->IdBloquePadre);
        Tabla *t2 = bt->getTabla(t->Id);
            if (t2->PrimerBloqueDatos == -1) {
                int x = SigBloqueDisponible();
                t2->PrimerBloqueDatos = x;
                t2->UltimoBloqueDatos = x;
            }
            else {
                t2->UltimoBloqueDatos = SigBloqueDisponible();
            }
//            ActualizarBloqueMaestro();
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
        br->AgregarRegistro(archivo,d,c->longitud,c->IdCampo);
        br->Escribir(archivo);
    }else{
        br = new BloqueRegistro(t2->UltimoBloqueDatos);
        br->Cargar(archivo);
        if(br->getEspacioDisp()> c->longitud){
            br->AgregarRegistro(archivo,d,c->longitud,c->IdCampo);
            br->Escribir(archivo);
        }else{
            BloqueRegistro *br2 = AsigNBloqueR(t2);
            br2->AgregarRegistro(archivo,d,c->longitud,c->IdCampo);
            br->sig = br2->NumeroBloque;
            br->Escribir(archivo);
            br2->Escribir(archivo);
        }
    }
    delete(t2);
    delete(bt);

    BloqueTabla *bt2 = CargarBloqueT(t->IdBloquePadre);
    Tabla*t3 = bt2->getTabla(t->Id);
    BloqueHashTable *bh;
    BloqueColision *bc;
    Idx_Entry *IdxEnt = new Idx_Entry(br->NumeroBloque,br->getPosicion(archivo,d),d);
    if(t3->PrimerBloqueHash==-1){
        bh = AsigNBloqueHT(t3);
        int pos = bh->hashear(d);
        std::cout<<"pos: "<<pos<<std::endl;
        bc = AsigNBloqueCol(bh,pos,IdxEnt);
        bh->cantEntrysActuales++;
    }else{
        bh = CargarBloqueHT(t3);
        int pos = bh->hashear(d);
        std::cout<<"pos: "<<pos<<std::endl;
        if(bh->Entries[pos].PrimerBloqueColision==-1){
            bc = AsigNBloqueCol(bh,pos,IdxEnt);
            bh->cantEntrysActuales++;
        }else {
            bc = new BloqueColision(bh->Entries[pos].UltimoBloqueColision);
            bc->Cargar(archivo);
            if (bc->cantIdxEntrysEntrys >= 17) {
                BloqueColision *bc2 = AsigNBloqueCol(bh, pos, IdxEnt);
                bc2->insert_Idx_Entry(IdxEnt);
                bc2->Escribir(archivo);
                bc->sig = bc2->numeroBloque;
            }
        }
    }
    bh->Escribir(archivo);
    bc->insert_Idx_Entry(IdxEnt);
    bc->Escribir(archivo);
    delete(bt2);
    delete(t3);
    delete (bc);
    delete(bh);
//    delete(bh);
//    delete(bc);
//    delete(IdxEnt);
}

std::list<Registro *> *ManejadorBloques::listarRegistros(Tabla *t, Campo *c)
{
    std::list<Registro*>*regs = new std::list<Registro*>;
    int siguiente = t->PrimerBloqueDatos;
    int idc = c->IdCampo;
    while(siguiente!=-1){
        BloqueRegistro*br = new BloqueRegistro(siguiente);
        br->Cargar(archivo);
        for(std::list<Registro*>::iterator it  = br->registros->begin();it!=br->registros->end();it++){
            Registro*r = *it;
            if(r->idc == idc){
                regs->push_back(r);
            }
        }
        siguiente = br->sig;
    };
    return regs;
}

Registro* ManejadorBloques::buscarReg(Tabla *t,char*n)
{
    BloqueTabla*bt = CargarBloqueT(t->IdBloquePadre);
    Tabla*t2 = bt->getTabla(t->Id);
    BloqueHashTable *bh = CargarBloqueHT(t2);
    int siguiente  = bh->Buscar(n);
//    std::cout<<siguiente<<std::endl;
    do{
        BloqueColision *bc = new BloqueColision(siguiente);
        bc->Cargar(archivo);
//        std::cout<<bc->cantIdxEntrysEntrys<<std::endl;
//        std::cout<<bc->IdxEntries->size()<<std::endl;
        Idx_Entry*ide = bc->buscar_Idx_Entry(n);
        if(ide!=NULL){
            BloqueRegistro*br = new BloqueRegistro(ide->numeroBloque);
            br->Cargar(archivo);
            char*data  = br->toChar();
            int pos = ide->numeroRegRel;
            int tam = 0;
            memcpy(&tam,&data[pos],4);
            pos+=4;
            Registro*reg = new Registro(tam);
            if(reg->longitud==20){
                memcpy(&reg->reg[0],&data[pos],20);
                pos+=20;
            }else{
                memcpy(&reg->regdato,&data[pos],4);
                pos+=4;
            }
            memcpy(&reg->idc,&data[pos],4);
            pos+=4;
            return reg;
        }
        siguiente = bc->sig;
    }while(siguiente!=-1);
    std::cout<<"No existe tal registro"<<std::endl;
    return 0;
}


/*-------------------------------BloqueHashTable-------------------------------*/
BloqueHashTable* ManejadorBloques::CargarBloqueHT(Tabla*t)
{
    BloqueTabla *bt = CargarBloqueT(t->IdBloquePadre);
    Tabla *t2 = bt->getTabla(t->Id);
    BloqueHashTable*bh;
    if (t2->PrimerBloqueHash == t2->UltimoBloqueHash) {
        bh = new BloqueHashTable(t2->PrimerBloqueHash, 512);
        bh->Cargar(archivo);
//        delete(t2);
//        delete(bt);
        return bh;
    }
    else {
        int tam = t2->UltimoBloqueHash - t2->PrimerBloqueHash + 1;
        bh = new BloqueHashTable(t2->PrimerBloqueHash, tam);
        bh->Cargar(archivo);
//        delete(t2);
//        delete(bt);
        return bh;
    }

}



BloqueHashTable* ManejadorBloques::AsigNBloqueHT(Tabla*t)
{
    BloqueHashTable *bh;
    BloqueTabla *bt = CargarBloqueT(t->IdBloquePadre);
    Tabla *t2 = bt->getTabla(t->Id);
    if(t2->PrimerBloqueHash==-1){
        int x = SigBloqueDisponible();
        t2->PrimerBloqueHash=x;
        t2->UltimoBloqueHash=x;
        bh = new BloqueHashTable(t2->UltimoBloqueHash,512);//es el primer bloque hash
//        bh->Escribir(archivo);
//        ActualizarBloqueMaestro();
    }else{
//        if(t2->PrimerBloqueHash==t2->UltimoBloqueHash){
            int tam = ((t2->UltimoBloqueHash-t2->PrimerBloqueHash)+1)*2;
            t2->PrimerBloqueHash=bm->sigBloqueDisponible;
            bm->sigBloqueDisponible+=(tam-1);
            t2->UltimoBloqueHash=bm->sigBloqueDisponible;
            bm->sigBloqueDisponible++;
            bm->Escribir(archivo);
            bh = new BloqueHashTable(t2->PrimerBloqueHash,tam*512);
            //rehashing
//            bh->Escribir(archivo);
//        }
    }

    bh->Escribir(archivo);
    bt->Escribir(archivo);
//    delete(t2);
//    delete(bt);
    return bh;

}

/*-------------------------------BloqueColision-----------------------------------*/

BloqueColision *ManejadorBloques::AsigNBloqueCol(BloqueHashTable*bh,int pos, Idx_Entry*idx)
{
    if(bh->Entries[pos].PrimerBloqueColision==-1){
        int x = SigBloqueDisponible();
        bh->Entries[pos].PrimerBloqueColision = x;
        bh->Entries[pos].UltimoBloqueColision = x;
    }else{
        bh->Entries[pos].UltimoBloqueColision=SigBloqueDisponible();
    }
    BloqueColision*bc = new BloqueColision(bh->Entries[pos].UltimoBloqueColision);
//    bc->insert_Idx_Entry(idx);
//    bc->Escribir(archivo);
//    bh->cantEntrysActuales++;
    bh->Escribir(archivo);
    return bc;
}



ManejadorBloques::~ManejadorBloques()
{
    //dtor
}
