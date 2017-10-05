//
// Created by Chronos-Laptop on 27/8/2017.
//

#include <fstream>
#include "jsonEstruct.h"
jsonEstruct::jsonEstruct(ManejadorTablas *mt)
{
    this->mt = mt;
}

void jsonEstruct::Escribir()
{
    std::ofstream o(path);
    json j;
    std::list<Tabla*>*tablas = mt->CargarTablas();
    if(tablas->empty()){
        return;
    }
    j["Tablas"]={};
    int contTablas=0;
    for(std::list<Tabla*>::iterator it = tablas->begin();it!=tablas->end();it++){
        Tabla*t = *it;
        j["Tablas"][contTablas]["Nombre"] = t->nombre;
        if(t->cantCampos==0) {
//            o << setw(4) << j << endl;
            contTablas++;
            continue;
        }
        j["Tablas"][contTablas]["Campos"]={};
        int contCampos=0;
        std::list<Campo*>*campos = mt->mb->listarCampos(t);
        for(std::list<Campo*>::iterator ic = campos->begin();ic!=campos->end();ic++){
            Campo*c  = *ic;
            std::list<Registro*>*regs = mt->mb->listarRegistros(t,c);
            j["Tablas"][contTablas]["Campos"][contCampos]["Nombre"] = c->nombre;
            j["Tablas"][contTablas]["Campos"][contCampos]["Tipo"] = c->tipo;
            if(regs->empty()){
                contTablas++;
                contCampos++;
                continue;
            }
            if(c->tipo==0){
                std::list<int>registros;
                for(std::list<Registro*>::iterator ir = regs->begin();ir!=regs->end();ir++){
                    Registro*r = *ir;
                    registros.push_back(r->regdato);
                }
                j["Tablas"][contTablas]["Campos"][contCampos]["Registros"] = registros;
                registros.clear();
            }else{
                std::list<char*>registros;
                for(std::list<Registro*>::iterator ir = regs->begin();ir!=regs->end();ir++){
                    Registro*r = *ir;
                    char*regcadena = r->reg;
                    registros.push_back(regcadena);
                }
                j["Tablas"][contTablas]["Campos"][contCampos]["Registros"] = registros;
                registros.clear();
            }
            contCampos++;
        }
        contTablas++;
    }
    o<<std::setw(4)<<j<<endl;
}

void jsonEstruct::Leer()
{
    mt->mb->FormatearDataFile();
    mt->mb->AsigNBloqueT();

    std::ifstream i("../jsonfile");
    json j;
    i>>j;
    int cantTablas = j["Tablas"].size();
    for(int i=0;i<cantTablas;i++){
        std::string ntabla = j["Tablas"][i]["Nombre"].get<std::string>();
        char*nombretabla = new char[20];
        strcpy(nombretabla,ntabla.c_str());
        Tabla*t = mt->CrearTablas(nombretabla);
        int cantCampos = j["Tablas"][i]["Campos"].size();
        if(cantCampos==0){
            continue;
        }
        for(int c=0;c<cantCampos;c++){
            std::string ncampo = j["Tablas"][i]["Campos"][c]["Nombre"].get<std::string>();
            char * nombrecampo = new char[20];
            strcpy(nombrecampo,ncampo.c_str());
            int tipo = j["Tablas"][i]["Campos"][c]["Tipo"].get<int>();
            mt->mb->EscribirCampo(t,nombrecampo,tipo);
            Campo *campo = mt->mb->getCampo(t,nombrecampo);
            int cantRegistros = j["Tablas"][i]["Campos"][c]["Registros"].size();
            for(int r=0;r<cantRegistros;r++){
                if(campo->tipo==0){
                    int numero = j["Tablas"][i]["Campos"][c]["Registros"][r].get<int>();
                    std::string n = std::to_string(numero);
                    char const *nume = n.c_str();
                    char*numer = new char[4];
                    strcpy(numer,nume);
                    mt->mb->EscribirRegistro(t,campo,numer);
                }else{
                    std::string nregistro = j["Tablas"][i]["Campos"][c]["Registros"][r].get<std::string>();
                    char*nombreregistro = new char[20];
                    strcpy(nombreregistro,nregistro.c_str());
                    mt->mb->EscribirRegistro(t,campo,nombreregistro);
                }
            }
        }
    }
}

jsonEstruct::~jsonEstruct()
{

}
