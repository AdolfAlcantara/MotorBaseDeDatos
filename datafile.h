#ifndef DATAFILE_H
#define DATAFILE_H
#include <stdio.h>


class DataFile
{
    public:
        DataFile(char *path);
        void Abrir();
        void Cerrar();
        void Escribir(char*data,int pos, int longitud);
        char * Leer(int pos, int longitud);
        bool isEmpty();
        virtual ~DataFile();

   // protected:

 //   private:
        char *path;
        FILE *archivo;
};

#endif // DATAFILE_H
