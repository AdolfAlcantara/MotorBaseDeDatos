#ifndef TABLA_H
#define TABLA_H
#include <string.h>
#include <list>
#include "datafile.h"
#include "Registro.h"

class Tabla
{
public:
    Tabla();
    Tabla(char *nombre, int id, int idbp);
//    std::list<Registro> getRegistros();
//    std::list<Campo> getCampos();

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
    UltimoBloqueHash,
    cantCampos;

    /*El peso de las tablas es de 56 */

    //private:
    void charToBloque(char *data, int);
    char *toChar();


    //Atributos para manejar campos y registros

};

#endif // TABLA_H
