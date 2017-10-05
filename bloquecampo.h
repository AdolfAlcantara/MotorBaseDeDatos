#ifndef BLOQUECAMPO_H
#define BLOQUECAMPO_H
#include <list>
#include "campo.h"
#include "datafile.h"

class BloqueCampo
{
    public:
        BloqueCampo(int);
        void Escribir(DataFile*);
        void Cargar(DataFile*);
        void EscribirCampo(DataFile* arc,char*n,int tipo,int idc);
//        void LeerCampos(DataFile*); //usar una list de los nombres
        Campo* getCampo(char*);// buscar en la lista por nombre y extraser segun la cantidad
        virtual ~BloqueCampo();



        //variables
        int NumeroBloque;
        int TamanoBloque =512;
        int sig=-1;
        int cantCampos=0;
//        int TamanoCampos = 36; //ver clase campo
//        int TamanoHeader = 16; //4 atributos int

//        actualmente caben 13 campos por bloque
//        (512-16)/36 = 13.714

        std::list<Campo*>*campos;
    protected:

    private:

        char*toChar();
        void charToBloque(char*);
};

#endif // BLOQUECAMPO_H
