#include "datafile.h"
#include <iostream>
DataFile::DataFile(char *path)
{
    this->path = path;
    //archivo=0;
}

void DataFile::Abrir()
{
    //std::cout<<"se abrio"<<std::endl;
    archivo  = fopen(path, "rb+");
}

void DataFile::Cerrar()
{
    //std::cout<<"se cerro"<<std::endl;
    fclose(archivo);
}

/* pos es el bloque donde se va a escribir*/
void DataFile::Escribir(char* data, int pos, int longitud)
{
    Abrir();
    if(fseek(archivo,pos,SEEK_SET)==0){
        fwrite(data,sizeof(char),longitud,archivo);
    }
    Cerrar();
}

char* DataFile::Leer(int pos, int longitud)
{
    Abrir();
    char  *buffer = new char[longitud];
    if(fseek(archivo,pos,SEEK_SET)==0){
        fread(buffer, sizeof(char),longitud,archivo);
    }
    Cerrar();
    return buffer;

}

bool DataFile::isEmpty()
{

    if(fseek(archivo,0,SEEK_END)==0){
        return (ftell(archivo)<=0);
    }
    return true;
}

DataFile::~DataFile()
{
    //dtor
}
