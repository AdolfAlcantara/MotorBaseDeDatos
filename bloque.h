#ifndef BLOQUE_H
#define BLOQUE_H
#include "datafile.h"
#include <string.h>

class Bloque
{
    public:
        Bloque(DataFile*);
        void Escribir();
        void Cargar();
        void setSig(int );
        int getSig();
        virtual ~Bloque();

    protected:

    private:
        int NumeroBloque;
        int TamanoBloque=512;
        int sig=-1;
        DataFile *archivo;
        char* toChar();
        void charToBloque(char *data);

};

#endif // BLOQUE_H
