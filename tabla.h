#ifndef TABLA_H
#define TABLA_H
#include <string.h>
#include "datafile.h"

class Tabla
{
public:
    Tabla();
    Tabla(char *nombre, int id, int idbp);
    virtual ~Tabla();

    //

    //protected:
    char nombre[20];
    int Id;
    int IdBloquePadre;
    int PrimerBloqueCampos;
    int UltimoBloqueCampos;
    int PrimerBloqueDatos;
    int UltimoBloqueDatos;

    /*El peso de las tablas es de 44 */

    //private:
    void charToBloque(char *data, int);
    char *toChar();


    //Atributos para manejar campos y registros

};

#endif // TABLA_H
