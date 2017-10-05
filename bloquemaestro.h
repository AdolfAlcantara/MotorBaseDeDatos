#ifndef BLOQUEMAESTRO_H
#define BLOQUEMAESTRO_H
#include "datafile.h"
#include "string.h"
#include <list>

class BloqueMaestro
{
    public:
        BloqueMaestro();
        void Escribir(DataFile*);
        void Cargar(DataFile*);
        virtual ~BloqueMaestro();

        //variables
        int sigBloqueDisponible;
        int TamanoBloque=512;
        int PrimerBloqueTabla =1;
        int UltimoBloqueTabla;
        std::list<int>FreeBucket;
    protected:

    private:
        char *toChar();
        void charToBloque(char*data);
};

#endif // BLOQUEMAESTRO_H
