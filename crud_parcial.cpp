#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
const char *nombre_archivo = "archivo.dat";

struct Trabajador {
	int codigo_empleado;
	char nombres[50];
	char apellidos[50];
	char puesto[50];
	float sueldo;
	float bono;
};

void ingresar();
void abrir();
void modificar();
void buscar_codigo();
void eliminar_codigo();

main(){
	abrir();
	
	int opcion;
	
	do{
		cout<<"Ingrese la opcion que desea realizar: "<<endl;
		cout<<"1 - Ingresar"<<endl;
		cout<<"2 - Buscar"<<endl;
		cout<<"3 - Modificar"<<endl;
		cout<<"4 - Eliminar"<<endl;
		cout<<"5 - Salir"<<endl;
		cout<<"Ingrese una opcion: ";
		cin>>opcion;
		
		system("cls");
		switch(opcion){
			case 1:{
				ingresar();
				break;
			}
			case 2:{
				buscar_codigo();
				break;
			}
			case 3:{
				modificar();
				break;
			}
			case 4:{
				eliminar_codigo();
				break;
			}
			case 5:{
				return 0;
				break;
			}
		}
	}while(opcion != 5);
	
}

void abrir(){

	system("cls");
	FILE* archivo = fopen(nombre_archivo,"rb");
	if (!archivo){
		archivo = fopen(nombre_archivo,"w+b");
	}

	Trabajador trabajador;
	int registro = 0;
	fread(&trabajador,sizeof(Trabajador),1,archivo);
	
	cout<<"________________________________________________________________________________________________________________________"<<endl;
	cout<<"id |"<<"Codigo  |"<<"Nombres      |"<<"Apellidos      |"<<"Puesto      |"<<"Sueldo Base    |"<<"Bonificacion    |"<<"Sueldo Total    |"<<endl;
	
	do{
		cout<<"____________________________________________________________________________________________________________________"<<endl;
		
		float sueldo_total;
		sueldo_total = trabajador.sueldo + trabajador.bono;
		cout<<registro<<" | "<<trabajador.codigo_empleado<<" | "<<trabajador.nombres<<" | "<<trabajador.apellidos<<" | "<<trabajador.puesto<<" | "<<trabajador.sueldo<<" | "<<trabajador.bono<<" | "<<sueldo_total<<endl;
		fread(&trabajador,sizeof(Trabajador),1,archivo);
		registro +=1;
	} while(feof(archivo)==0);

	fclose(archivo);
}

void ingresar(){
	char continuar;
	FILE* archivo = fopen(nombre_archivo,"ab");
	Trabajador trabajador;
	string nombre,apellido, puesto;

	do{
		fflush(stdin);
		cout<<"Ingrese el codigo de empleado: ";
		cin>>trabajador.codigo_empleado;
		cin.ignore();
		cout<<"Ingrese los nombres: ";
		getline(cin,nombre);
		strcpy(trabajador.nombres,nombre.c_str());
		cout<<"Ingrese los apellidos: ";
		getline(cin,apellido);
		strcpy(trabajador.apellidos,apellido.c_str());
		cout<<"Ingrese el puesto: ";
		getline(cin,puesto);
		strcpy(trabajador.puesto,puesto.c_str());
		cout<<"Ingrese el sueldo base: ";
		cin>>trabajador.sueldo;
		cout<<"Ingrese la bonificacion: ";
		cin>>trabajador.bono;

		fwrite(&trabajador,sizeof(Trabajador),1,archivo);

		cout<<"Desea ingresar otro dato (s/n): ";
		cin>>continuar;
	}while(continuar == 's'||continuar == 'S');

	fclose(archivo);
	abrir();
}

void modificar (){
	FILE* archivo = fopen(nombre_archivo, "r+b");
	int id;
	string nombre, apellido, puesto;
	Trabajador trabajador;
	
	cout<<"Ingrese el ID que desea modificar: ";
	cin>>id;
	fseek(archivo, id*sizeof(Trabajador), SEEK_SET);
	
	cout<<"Ingrese el codigo de empleado: ";
		cin>>trabajador.codigo_empleado;
		cin.ignore();
		cout<<"Ingrese los nombres: ";
		getline(cin,nombre);
		strcpy(trabajador.nombres,nombre.c_str());
		cout<<"Ingrese los apellidos: ";
		getline(cin,apellido);
		strcpy(trabajador.apellidos,apellido.c_str());
		cout<<"Ingrese el puesto: ";
		getline(cin,puesto);
		strcpy(trabajador.puesto,puesto.c_str());
		cout<<"Ingrese el sueldo base: ";
		cin>>trabajador.sueldo;
		cout<<"Ingrese la bonificacion: ";
		cin>>trabajador.bono;
	
	fwrite(&trabajador, sizeof(Trabajador), 1, archivo);
	fclose(archivo);
	abrir();
}

void buscar_codigo(){

	FILE* archivo = fopen(nombre_archivo,"rb");	
	int pos=0,indice=0,cod=0;

	cout<<"Que codigo desea ver: ";
	cin>>cod;

	Trabajador trabajador;
	fread(&trabajador,sizeof(Trabajador),1,archivo);	

	do{
		if(trabajador.codigo_empleado == cod){
	  	cout<<"Codigo: "<<trabajador.codigo_empleado<<endl;
	  	cout<<"Nombres: "<<trabajador.nombres<<endl;
	  	cout<<"Apellidos: "<<trabajador.apellidos<<endl;
	  	cout<<"Puesto: "<<trabajador.puesto<<endl;
	  	cout<<"Sueldo base: "<<trabajador.sueldo<<endl;
	  	cout<<"Bonificacion: "<<trabajador.bono<<endl;
	  	cout<<"Sueldo total: "<<trabajador.sueldo + trabajador.bono<<endl;
	  }

	  fread(&trabajador,sizeof(Trabajador),1,archivo);	

	} while(feof(archivo)==0);

	fclose(archivo);
}

void eliminar_codigo(){
	FILE* archivo = fopen(nombre_archivo,"r+b");	
	int pos=0,indice=0,cod=0;

	cout<<"Que codigo desea eliminar: ";
	cin>>cod;

	Trabajador trabajador;
	fread(&trabajador,sizeof(Trabajador),1,archivo);
	
	FILE* temporal = fopen("temp.dat","w+b");	

	do{
		if(trabajador.codigo_empleado == cod){
		  	cout<<"Codigo: "<<trabajador.codigo_empleado<<endl;
		  	cout<<"Nombres: "<<trabajador.nombres<<endl;
		  	cout<<"Apellidos: "<<trabajador.apellidos<<endl;
		  	cout<<"Puesto: "<<trabajador.puesto<<endl;
		  	cout<<"Sueldo base: "<<trabajador.sueldo<<endl;
		  	cout<<"Bonificacion: "<<trabajador.bono<<endl;
		  	cout<<"Sueldo total: "<<trabajador.sueldo + trabajador.bono<<endl;
  	
	  }else{
	  	fwrite(&trabajador,sizeof(Trabajador),1,temporal);
	  }
	  
	  fread(&trabajador,sizeof(Trabajador),1,archivo);	

	} while(feof(archivo)==0);

	fclose(archivo);
	fclose(temporal);
	
	remove("archivo.dat");
	rename("temp.dat", "archivo.dat");
	abrir();
}
