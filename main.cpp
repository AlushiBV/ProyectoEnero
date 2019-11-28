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
    ofstream FicheroSalida;
    ifstream FicheroEntrada;


public:
    void NombreFichero(string User);
    void AgregarUsuario(string User);
    void CrearArchivo(string datos);
    void BuscarLinea();
    TipoLista Leer();

};

void ManejarArchivo::NombreFichero(string datos){
    FicheroNombre=datos.c_str();
}

void ManejarArchivo::CrearArchivo(string datos){
    FicheroSalida.open(FicheroNombre);
    FicheroSalida<<datos<<"\n";
    FicheroSalida.close();
}


void ManejarArchivo::AgregarUsuario(string User){
    TipoLista Lista = Leer();
    FicheroSalida.open(FicheroNombre);
    Lista.push_back(User);
    list<string>::iterator iterador=Lista.begin();
    for(; iterador!=Lista.end(); iterador++){
        FicheroSalida<<*iterador<<"\n"; // agregamos una linea de la lista al archivo
    }
    FicheroSalida.close();
}

void ManejarArchivo::BuscarLinea(){



}

TipoLista ManejarArchivo::Leer(){
    TipoLista Lista;
    string buffer;
    FicheroEntrada.open(FicheroNombre);
     while(!FicheroEntrada.eof())
    {
        getline(FicheroEntrada, buffer);
        if(buffer!=""){
            Lista.push_back(buffer); // agregamos la linea a la Lista
        }
    }
    FicheroEntrada.close();
    return Lista;
}



int main()
{
    ManejarArchivo reservaciones;
    TipoLista n;
    TipoLista z;
    string Plantilla_Vuelos[4] = {"ID: ", "Origen: ", "Destino: ", "Distancia: "};
    string Plantilla_Usuario[4] = {"ID_Pasaporte: ", "Nombres: ", "Apellidos: ", "Año Nacimiento: "};
    string in;
    string send="";

    cout<<"Ingrese el ID del vuelo: ";
    cin>>in;
    send=(Plantilla_Vuelos[0]+in)+"\n";

    reservaciones.NombreFichero(in+".txt");

    for(int i=1;i<4;i++){
        cout<<Plantilla_Vuelos[i];
        cin>>in;
        send=send+(Plantilla_Vuelos[i]+in)+"\n";
    }
    send=send+"####################### PASAJEROS ########################  \n";

    reservaciones.CrearArchivo(send);


    reservaciones.AgregarUsuario("numero de pasaporte");

    n = reservaciones.Leer();
    list<string>::iterator iterador;

    iterador=n.begin();
    for(; iterador!=n.end(); iterador++){
          cout<<*iterador<<endl;

    }

    return 0;
}
