#include <iostream>
#include <fstream>
#include <list>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef list<string> TipoLista;

class ManejarArchivo
{
    char const *FicheroNombre;
    fstream Fichero;
private:
    bool ExisteFichero(string Nombre);

public:
    bool EstablecerNombreFichero(string Nombre);
    void CrearFichero(string datos);
    void GuardarFichero(string User);
    TipoLista CargarFichero();

};

bool ManejarArchivo::EstablecerNombreFichero(string Nombre){
	Fichero.open(Nombre.c_str(), ios::in);
	FicheroNombre=Nombre.c_str();
	return ExisteFichero(Nombre);
}

bool ManejarArchivo::ExisteFichero(string Nombre){
	if(Fichero.is_open()){
       Fichero.close();
	   return true;
	}else{
	   Fichero.close();
	   return false;
	}
}

void ManejarArchivo::CrearFichero(string DatosCrearFichero){
    Fichero.open(FicheroNombre, ios::in);
    if(Fichero.is_open()){
       cout<<"Fichero, "<<FicheroNombre<< " Ya Existe\n";
    }else{
       Fichero.open(FicheroNombre, ios::out);
       Fichero<<DatosCrearFichero<<"\n";
    }
    Fichero.close();
}

void ManejarArchivo::GuardarFichero(string User){
    TipoLista Lista = CargarFichero();
    if(Lista.empty()){
            cout<<"Error!, La lista esta vacia\n";
        return;
    }
    Fichero.open(FicheroNombre,ios::out);
    Lista.push_back(User);
    list<string>::iterator iterador=Lista.begin();
    for(; iterador!=Lista.end(); iterador++){
        if(*iterador != ""){
            Fichero<<*iterador<<"\n"; // Se agrega una linea al fichero
        }
    }
    Fichero.close();
}

TipoLista ManejarArchivo::CargarFichero(){
    TipoLista Lista;
    string buffer;
    Fichero.open(FicheroNombre, ios::in);
    while(!Fichero.eof() && Fichero.is_open()){
        getline(Fichero, buffer);
        Lista.push_back(buffer); // Se lee una linea del fichero
    }
    Fichero.close();
    return Lista;
}



int main()
{
    ManejarArchivo Reservar;
    TipoLista Lista;
    string Plantilla_Vuelos[8] = {"ID: ", "Fecha del viaje: " , "Origen: ", "Destino: ", "Asiento: " , "Aerolinea: " , "Distancia: " , "####################### PASAJEROS ########################"};
    string Plantilla_Usuario[4] = {"ID_Pasaporte: ", "Nombres: ", "Apellidos: ", "Año Nacimiento: "};
    string LeidoDesdeConsola;
    string DatosParaGuardar="";
    int ElejirOpcion = 0;

    cout<<"1. Crear Registro de vuelo.\n";
    cout<<"2. Agregar Pasajeros.\n";
    cout<<"3. Ver Registro de Vuelo.\n";
    cin>> ElejirOpcion;

    if(ElejirOpcion == 1){
    cout<< "Ingrese el ID del vuelo: ";
    cin>> LeidoDesdeConsola;
    if(Reservar.EstablecerNombreFichero(LeidoDesdeConsola + ".txt")){
        cout<< "ID de Vuelo, "<< LeidoDesdeConsola << ".txt Ya Existe\n";
    }
    else{
	    DatosParaGuardar = (Plantilla_Vuelos[0] + LeidoDesdeConsola)+"\n";
	    for(int i=1; i<7; i++){
	        cout<< Plantilla_Vuelos[i];
	        cin>> LeidoDesdeConsola;
	        DatosParaGuardar = DatosParaGuardar + (Plantilla_Vuelos[i] + LeidoDesdeConsola) + "\n";
    	}
    DatosParaGuardar = DatosParaGuardar + Plantilla_Vuelos[7];
    cout<< DatosParaGuardar;
    Reservar.CrearFichero(DatosParaGuardar);
    }
    }

    if(ElejirOpcion == 2){
	cout<< "Ingrese el ID del Vuelo: ";
	cin>> LeidoDesdeConsola;
	if(Reservar.EstablecerNombreFichero(LeidoDesdeConsola + ".txt")){
	       cout<< "Ingrese el Numero de Pasaporte: ";
	       cin>> LeidoDesdeConsola;
	       Reservar.GuardarFichero(LeidoDesdeConsola);
	    }
	    else{
	        cout<< "Error!, "<< LeidoDesdeConsola << ".txt No Exsite\n";
	    }
    }

    if(ElejirOpcion == 3){
    cout<<"Ingrese el ID del Vuelo: ";
    cin>>LeidoDesdeConsola;
    Reservar.EstablecerNombreFichero(LeidoDesdeConsola+".txt");
    Lista = Reservar.CargarFichero();
    list<string>::iterator iterador;
    iterador=Lista.begin();
    for(; iterador!=Lista.end(); iterador++){
        cout<<*iterador<<endl;
    }
    }

    return 0;
}
