#include <iostream>
#include <vector>
#include "manejadortablas.h"
#include "json.hpp"
#include <fstream>
#include "jsonEstruct.h"

using namespace std;
using json = nlohmann::json;


//struct jsonTabla{
//    std::list<Campo>*campos =new std::list<Campo>;
//};

int main() {

    char path[] = "C:\\Users\\Chronos-Laptop\\Documents\\ED1\\DB_MOTOR\\nuevo";
    DataFile *archivo = new DataFile(path);
    ManejadorTablas *MT = new ManejadorTablas(archivo);
//
    MT->mb->FormatearDataFile();
    MT->mb->AsigNBloqueT();
//
//
    Tabla*t = MT->CrearTablas("Personas");
    MT->mb->EscribirCampo(t,"Nombre",1);
//    MT->mb->EscribirCampo(t,"Edad",0);
//    MT->CrearTablas("Animales");
//    Tabla*t  = MT->BuscarTabla("Personas");
    Campo*c = MT->mb->getCampo(t,"Nombre");
//    Campo*c2 = MT->mb->getCampo(t,"Edad");
//    MT->mb->EscribirRegistro(t,c,"Raul");
//    MT->mb->EscribirRegistro(t,c,"Reiner");
//    MT->mb->EscribirRegistro(t,c,"Davila");
//    MT->mb->EscribirRegistro(t,c,"David");
//    MT->mb->EscribirRegistro(t,c2,"21");
//    MT->mb->EscribirRegistro(t,c2,"20");
//    MT->mb->EscribirRegistro(t,c2,"19");
//    MT->mb->EscribirRegistro(t,c,"Leonardo");
//    for(int i=0;i<100;i++){
//        Tabla *t = MT->CrearTablas("Tabla");
//        for(int j=0;j<10;j++){
//            Campo *c;
//            if(j%2==0) {
//                MT->mb->EscribirCampo(t, "Campo0", 0);
//                c = MT->mb->getCampo(t, "Campo0");
//                for(int k=0;k<20;k++){
//                    MT->mb->EscribirRegistro(t,c,"123");
//                }
//            }else{
//                MT->mb->EscribirCampo(t,"Campo1",1);
//                c = MT->mb->getCampo(t,"Campo1");
//                for(int k =0;k<20;k++){
//                    MT->mb->EscribirRegistro(t,c,"ED2");
//                }
//            }
//        }
//    }


//    MT->mb->EscribirRegistro(t2,c,"Davila");
//    MT->mb->EscribirRegistro(t2,c,"Reiner");
//
//    Tabla *t3 = MT->BuscarTabla("Tabla");
//    BloqueCampo*bc = new BloqueCampo(t3->UltimoBloqueCampos);
//    BloqueRegistro *br = new BloqueRegistro(t3->UltimoBloqueDatos);
//    bc->Cargar(archivo);
//    br->Cargar(archivo);
//
//    std::list<Campo*>::iterator it = bc->campos->begin();
//    for(int i=0;i<bc->campos->size();i++){
//        Campo*c = *it;
//        cout<<"Nombre: "<<c->nombre<<endl;
//        cout<<"Longitd: "<<c->longitud<<endl;
//        it++;
//    }


//    std::list<Registro*>::iterator it2 = br->registros->begin();
//    for(int i=0;i<br->registros->size();i++){
//        Registro*r = *it2;
//        cout<<"Nombre: "<<r->reg<<endl;
//        cout<<"Longitd: "<<r->regdato<<endl;
//        it2++;
//    }



//    for(int x=0;x<10;x++) {
//        MT->CrearTablas("Tabla1");
//        for(int y=0;y<10;y++){
//            Tabla *t2 = MT->BuscarTabla("Tabla1");
//            if(y%2==0)
//                MT->mb->EscribirCampo(t2,"Campo0",0);
//            else
//                MT->mb->EscribirCampo(t2,"Campo1",1);
//            Tabla *t3 = MT->BuscarTabla("Tabla1");
//            BloqueCampo*bc = new BloqueCampo(t3->UltimoBloqueCampos);
//            bc->Cargar(archivo);
//            cout<<t3->PrimerBloqueCampos<<endl;
//            cout<<t3->UltimoBloqueCampos<<endl;
//            cout<<bc->cantCampos<<endl;
//            cout<<bc->campos->size()<<endl;
//            cout<<"----"<<endl;
//        }
//    }



//    cout<<"----------------------"<<endl;
//    MT->ListarTablas();



//    char *numero = "123";
//
//    char num[19];
//    memcpy(&num,&numero[0], sizeof(num)-1);
//    num[18] = '\0';
//    int x;
//    cout<<num<<endl;
//    cout<<num+1<<endl;
//    sscanf(num,"%id",&x);
//
//    cout<<x<<endl;
//    cout<<x+1<<endl;
//

//    MT->ListarTablas();


//   json j;
//    j["Tabla"]={};
//    j["Tabla"][0]["Nombre"] = "Tabla1";
//    j["Tabla"][0]["Campos"]={};
//    j["Tabla"][0]["Campos"][0]["Nombre"]="Edad";
//    j["Tabla"][0]["Campos"][1]["Nombre"]="Altura";
//    j["Tabla"][1]["Nombre"] = "Tabla2";
//    j["Tabla"][1]["Tamano"] = 512;
//
//
//    std::ofstream o("../jsonfile");
//    o<<std::setw(4)<<j<<std::endl;


//    jsonEstruct *jsone = new jsonEstruct(MT);
//    jsone->Escribir();
//    jsone->Leer();

//    cout<<t->PrimerBloqueHash<<","<<t->UltimoBloqueHash<<endl;
//    BloqueHashTable *bh  = MT->mb->CargarBloqueHT(t);
////    cout<<bh->numeroBloque<<endl;
////    cout<<bh->cantEntrysActuales<<endl;
//    for(int i=0;i<bh->cantEntrysPosibles;i++){
//        cout<<"i: "<<i<<endl;
//        cout<<"pbc: "<<bh->Entries[i].PrimerBloqueColision<<endl;
//        cout<<"ubc: "<<bh->Entries[i].UltimoBloqueColision<<endl;
//    }


//    int pos = bh->hashear("Raul");
//    cout<<pos<<endl;
//    Entry*e = new Entry();
//    std::vector<Entry>Entries;
//    Entries = std::vector<Entry>(10,*e);
//
//    Entries[8].PrimerBloqueColision = 5;
//    Entries[8].UltimoBloqueColision = 10;
//    for(int i=0;i<10;i++){
//        cout<<Entries[i].PrimerBloqueColision<<endl;
//        cout<<Entries[i].UltimoBloqueColision<<endl;
//    }

    stringstream ss;
    std::string s;
    for(int i=0;i<100;i++){
        ss<<"Registro";
        ss<<i;
        s = ss.str();
        char *reg = new char[s.length()+1];
        std::copy(s.c_str(),s.c_str()+s.length()+1,reg);
        MT->mb->EscribirRegistro(t,c,reg);
        ss.str(std::string());
        delete[] reg;
    }

//    Registro*reg = MT->mb->buscarReg(t,"Registro50");
//    cout<<"Reg: "<<reg->reg<<endl;
//    cout<<"Idc: "<<reg->idc<<endl;
//    cout<<"Longitud: "<<reg->longitud<<endl;
//    cout<<"Regdato: "<<reg->regdato<<endl;


//    Registro*reg = MT->mb->buscarReg(t,"Raul");
//    cout<<reg->reg<<endl;
}
