#ifndef MANEJADORBLOQUES_H
#define MANEJADORBLOQUES_H
#include "bloquetabla.h"
#include "bloquemaestro.h"
#include "bloquecampo.h"
#include "bloqueregistro.h"
#include "BloqueHashTable.h"
#include "BloqueColision.h"

class ManejadorBloques
{
    public:
        ManejadorBloques(DataFile*);
        void FormatearDataFile();
        void ActualizarBloqueMaestro();
        void LlenarMasterBlockBucket(int, int);
        int SigBloqueDisponible();
        virtual ~ManejadorBloques();

    //bloqueTabla
    BloqueTabla* AsigNBloqueT();
    BloqueTabla* CargarBloqueT(int);

    //bloqueCampos
    BloqueCampo * AsigNBloqueC(Tabla*);
    void EscribirCampo(Tabla*,char*n,int tipo);
    Campo *getCampo(Tabla *t,char*n);
    std::list<Campo*>* listarCampos(Tabla*t);

    //bloqueRegistros
    BloqueRegistro *AsigNBloqueR(Tabla*);
    void EscribirRegistro(Tabla*,Campo*,char*);
    std::list<Registro*>* listarRegistros(Tabla*t,Campo*C);
    Registro*buscarReg(Tabla*, char*n);

    //bloqueHashTable
    BloqueHashTable *AsigNBloqueHT(Tabla*);
    BloqueHashTable *CargarBloqueHT(Tabla *t);


    //bloqueColision
    BloqueColision *AsigNBloqueCol(BloqueHashTable*,int,Idx_Entry*);



    //private:
        DataFile *archivo;
        BloqueMaestro *bm;


};

#endif // MANEJADORBLOQUES_H
