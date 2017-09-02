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
    int Id,
    IdBloquePadre,
    PrimerBloqueCampos,
    UltimoBloqueCampos,
    PrimerBloqueDatos,
    UltimoBloqueDatos,
    PrimerBloqueHash,
    UltimoBloqueHash;

    /*El peso de las tablas es de 52 */

    //private:
    void charToBloque(char *data, int);
    char *toChar();


    //Atributos para manejar campos y registros

};

#endif // TABLA_H
