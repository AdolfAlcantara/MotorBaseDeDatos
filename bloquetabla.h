#ifndef BLOQUETABLA_H
#define BLOQUETABLA_H
#include "tabla.h"
#include "datafile.h"
#include <list>

class BloqueTabla
{
    public:
        BloqueTabla(int nb);
        void Escribir(DataFile*);
        void Cargar(DataFile*);
        Tabla*getTabla(int id);
        virtual ~BloqueTabla();

   //  protected:
        int NumeroBloque;
        int TamanoBloque=512;
        int sig=-1;
        int CantidadTablas =0;              //es lo mismo que entradas
        std::list<Tabla*>*Tablas;

        /*
        El tamano del header de bloque tabla es de 16
        El tamano del las tablas es de 52
        512-16 = 496/52 = 9.27
        Cantidad de tablas disponibles por bloque   = 11
        */

    private:
        char *toChar();
        void charToBloque(char*data);
//        Tabla *getTable(int i);


};

#endif // BLOQUETABLA_H
