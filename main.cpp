#include <iostream>
#include <fstream>
#include <list>
#include <stdio.h>
#include <string.h>


using namespace std;

const string VuelosPlantilla = "ID";
typedef list<string> TipoLista;


class ManejarArchivo
{
private:
    char const *FicheroNombre;
    fstream Fichero;

public:
    bool EstablecerNombreFichero(string Nombre);
    void AgregarUsuario(string User);
    void CrearArchivo(string datos);
    TipoLista Leer();

};

bool ManejarArchivo::EstablecerNombreFichero(string Nombre){
       Fichero.open(Nombre.c_str(), ios::in);
       if(Fichero.is_open()){
           //cout<<"Fichero, "<<Nombre<< "Abierto con Exito\n";
           FicheroNombre=Nombre.c_str();
           Fichero.close();
           return true;
       }else{
           //cout<<"Fichero, "<<Nombre<< "No se Pudo Abrir\n";
           FicheroNombre=Nombre.c_str();
           Fichero.close();
           return false;
    }

}

void ManejarArchivo::CrearArchivo(string DatosCrearFichero){
    Fichero.open(FicheroNombre, ios::in);
    if(Fichero.is_open()){
       cout<<"Fichero, "<<FicheroNombre<< " Ya Existe\n";
    }else{
       Fichero.open(FicheroNombre, ios::out);
       Fichero<<DatosCrearFichero<<"\n";
    }
    Fichero.close();
}

void ManejarArchivo::AgregarUsuario(string User){
    TipoLista Lista = Leer();
    if(Lista.empty()){
        return;
    }
    Fichero.open(FicheroNombre,ios::out);
    Lista.push_back(User);
    list<string>::iterator iterador=Lista.begin();
    for(; iterador!=Lista.end(); iterador++){
        Fichero<<*iterador<<"\n"; // agregamos una linea de la lista al archivo
    }
    Fichero.close();
}

TipoLista ManejarArchivo::Leer(){
    TipoLista Lista;
    string buffer;
    Fichero.open(FicheroNombre, ios::in);
    if(Fichero.fail()){
       cout<<"Error!, "<<FicheroNombre<<" No existe o esta vacio.\n";
       return Lista;
    }
    while(!Fichero.eof()){
        getline(Fichero, buffer);
        if(buffer!=""){
            Lista.push_back(buffer); // agregamos la linea a la Lista
        }
    }
    Fichero.close();
    return Lista;
}



int main()
{
    ManejarArchivo Reservar;
    TipoLista n;
    TipoLista z;
    string Plantilla_Vuelos[5] = {"ID: ", "Origen: ", "Destino: ", "Distancia: ","####################### PASAJEROS ########################  \n"};
    string Plantilla_Usuario[4] = {"ID_Pasaporte: ", "Nombres: ", "Apellidos: ", "Año Nacimiento: "};
    string in;
    string send="";
    int opt=0;

    cout<<"1. Crear Registro de vuelo.\n";
    cout<<"2. Agregar Pasajeros.\n";
    cout<<"3. Ver Registro de Vuelo.\n";
    cin>>opt;

    if(opt == 1){
    cout<<"Ingrese el ID del vuelo: ";
    cin>>in;
        if(Reservar.EstablecerNombreFichero(in + ".txt")){
            cout<<"ID de Vuelo, "<<in<< " Ya Existe\n";
        }
        else{
            send=(Plantilla_Vuelos[0] + in)+"\n";
            for(int i=1; i<4; i++){
                cout<<Plantilla_Vuelos[i];
                cin>>in;
                send=send + (Plantilla_Vuelos[i] + in)+"\n";
            }
            send=send+Plantilla_Vuelos[4];
            Reservar.CrearArchivo(send);
        }
    }


    if(opt == 2){
    cout<<"Ingrese el ID del Vuelo: ";
    cin>>in;
    if(Reservar.EstablecerNombreFichero(in + ".txt")){
           cout<<"Ingrese el Numro de Pasaporte: ";
           cin>>in;
           Reservar.AgregarUsuario(in);
        }
        else{
            cout<<"ID de Vuelo, "<<in<< " Ya Existe\n";
        }

    }


    if(opt == 3){
    cout<<"Ingrese el ID del Vuelo: ";
    cin>>in;
    Reservar.EstablecerNombreFichero(in+".txt");
    n = Reservar.Leer();
    list<string>::iterator iterador;

    iterador=n.begin();
    for(; iterador!=n.end(); iterador++){
        cout<<*iterador<<endl;
    }
    }


    return 0;
