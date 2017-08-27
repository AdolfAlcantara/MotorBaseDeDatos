#ifndef MANEJADORBLOQUES_H
#define MANEJADORBLOQUES_H
#include "bloquetabla.h"
#include "bloquemaestro.h"
#include "bloquecampo.h"
#include "bloqueregistro.h"

class ManejadorBloques
{
    public:
        ManejadorBloques(DataFile*);
        void FormatearDataFile();
        void ActualizarBloqueMaestro();
        virtual ~ManejadorBloques();

    //bloqueTabla
    BloqueTabla* AsigNBloqueT();
    BloqueTabla* CargarBloqueT(int);

    //bloqueCampos
    BloqueCampo * AsigNBloqueC(Tabla*);
    void EscribirCampo(Tabla*,char*n,int tipo);
    Campo *getCampo(Tabla *t,char*n);

    //bloqueRegistros
    BloqueRegistro *AsigNBloqueR(Tabla*);
    void EscribirRegistro(Tabla*,Campo*,char*);

    //protected:

    //private:
        DataFile *archivo;
        BloqueMaestro *bm;


};

#endif // MANEJADORBLOQUES_H
