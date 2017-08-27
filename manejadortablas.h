#ifndef MANEJADORTABLAS_H
#define MANEJADORTABLAS_H
#include "bloquetabla.h"
#include "bloquemaestro.h"
#include "manejadorbloques.h"

using namespace std;

class ManejadorTablas
{
    public:
        ManejadorTablas(DataFile*);
        Tabla* CrearTablas(char nombre[20]);
        Tabla * BuscarTabla(char*nom);
        void ListarTablas();
//        void ListarCampos();
        void CargarTablas(BloqueTabla*);
        void LlenarListaBloquesTabla();


        virtual ~ManejadorTablas();

    //protected:
        list<BloqueTabla*> BloquesTablas;
        DataFile *archivo;
        BloqueMaestro *bm;
        ManejadorBloques *mb;

    private:

};

#endif // MANEJADORTABLAS_H
