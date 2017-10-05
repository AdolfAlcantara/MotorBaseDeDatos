

//.,;Created////
// Created by Chronos-Laptop on 7/8/2017.
//

#ifndef DB_MOTOR_CAMPO_H
#define DB_MOTOR_CAMPO_H

class Campo
{
    public:
        Campo();
        Campo(char*nom,int t,int idc);

//        void Escribir(DataFile*,int pos);
//        void Cargar();
        virtual ~Campo();

        char nombre[20];
        int tipo;
        int longitud;
        int IdBloquePadre;
        int IdCampo;

    //tamano del campo es 36

//    private:
        char*toChar();
        void charToBloque(char*);


};


#endif //DB_MOTOR_CAMPO_H
