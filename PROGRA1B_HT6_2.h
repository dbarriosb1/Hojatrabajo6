/*

Realice un programa que, dado el peso, la altura, la edad y el género (M/F) de un grupo de N personas
que pertenecen a un departamento de la república, obtenga un promedio de peso, altura y edad de esta
población. Los datos deben guardarse de forma ordenada por edad en un archivo de datos. Así mismo
el programa debe ser capaz leer los datos del archivo y generar un reporte con la media del peso, altura
y la edad.


*/
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <iomanip>      // std::setw
#include <vector>

using namespace std;

struct personas{
  float peso;
  float altura;
  int edad;
  string genero;
};

void pausar_pantalla(){
      // Pause
    string empty;
    cout << "\nPresione cualquier tecla para continuar \n";
    getline(cin,empty);
};

void limpiar_pantalla(){
  // limpiamos pantalla
  cout << "\033[2J\033[0;0H";
}

void ordenar(){
  // Declaramos la estructura en una variable
  personas temp;

  // Creamos un vector para el almacenamiento del archivo
  vector<personas> registros;


    // Ordenamiento
  // Declaracion del objeto para lectura de archivo
  ifstream db_read;
  db_read.open("registro_de_control.txt",ios::in);
	
  while(db_read>>temp.peso>>temp.altura>>temp.edad>>temp.genero){
    // Agregamos al vector el contenido del archivo.
    registros.push_back(temp);
  };
  // cerramos archivo.
  db_read.close();
  //Hacemos el ordenamiento del contenido del archivo y el ingreso.
    
  //Ordenamiento de BUBBLESORT por edad
  for(int i=0; i<registros.size(); i++) {
   for(int j=i+1; j<registros.size(); j++)
   {
      // Comparamos la edad
      if(registros[j].edad < registros[i].edad) {
         temp = registros[i];
         registros[i] = registros[j];
         registros[j] = temp;
      }
   }
  } 


    // remplazamos el archivo.
    ofstream db;
    db.open("registro_de_control.txt",ios::out);
    
    for (int i=0; i<registros.size(); i++){
      db << registros[i].peso <<"\t"<< registros[i].altura <<"\t"<< registros[i].edad <<"\t"<< registros[i].genero <<endl;
    }
    db.close();
}

void insert_data_db(){
	//declaracion de variables
  string genero;
  // Declaramos la estructura de personas a la variable x y temp
	personas x;

  // Declaracion del objeto para escribir en archivo
  ofstream db;
  

  //Ingreso de datos
	cout<<"*** Control de peso, la altura, la edad y el género ***\n*** En las Personas del departamente de Guatemala ***\n";
	
  cout<<"Indique peso de la persona:         "<<endl;
 	cin>>x.peso;
	cin.clear(); 
  
  cout<<"Indique altura de la persona:         "<<endl;
	cin>>x.altura;
  cin.clear(); 
	
  cout<<"Indique edad de la persona:         "<<endl;
	cin>>x.edad;
  //cin.clear(); 
	cin.ignore();
  
  // Hacemos la validación del ingreso de la información de genero.
  bool validacion=false;
  while (validacion==false) {
    cout<<"Indique genero de la persona (m=Masculino, f=Feminino): "<<endl;
    getline(cin,genero);    // obtenemos la variable

    // Realizamos la comparación
    if ((genero=="M") or (genero=="m")) {
      x.genero="M";
      validacion=true;
    } else if ((genero=="F") or (genero=="f")) {
      x.genero="F";
      validacion=true;
    } else {
      cout << "Indico una opción invalida!!! \n Vuelva a intentarlo .... \n";
    }
  }  //Termina el While
  cin.clear(); 

	//Insercion de datos a un archivo
	try {
		// Abrimos el archivo para insertar nuevo registro, o generamos un nuevo archivo
    db.open("registro_de_control.txt",ios::app);
    // Grabamos la linea del archivo.  
   
    // Graba registro de x
    db << x.peso <<"\t"<< x.altura <<"\t"<< x.edad <<"\t"<< x.genero <<endl;
		
    // Cerramos el archivo
    db.close();
	}

	catch(exception X){
		cout<<"Error en la manipulacion del archivo"<<endl;
		
    // Esto es una pausa para ingresar enter
    cout << "Presione enter para continuar.... "<< endl;
    

    pausar_pantalla();
    limpiar_pantalla();
	}
  
  // Ordenamos al ingresar un nuevo registro en el archivo
  ordenar();
}

void leer_data_db(){
  //declaracion de variables y objetos
  personas x;

  int i=0;
  float prom_peso, prom_altura, prom_edad;
	ifstream db;	
	
  try{
		db.open("registro_de_control.txt",ios::in);	
    
    limpiar_pantalla();
		cout<<"Datos del archivo:"<<endl;
		cout<<" Peso|"<<"      Altura      |"<<"  Edad|"<<"  Genero|"<<endl;		
		while (db>>x.peso>>x.altura>>x.edad>>x.genero){
			cout<<setw(5)<<x.peso<<"|"<<setw(10)<<x.altura<<setw(9)<<"|"<<setw(3)<<x.edad<<setw(4)<<"|"<<setw(4)<< x.genero<<setw(5)<<"|"<<endl;
      // Contamos las lineas de registro
      i++;					
      
      // sumamos todos los campos para su promedio
			prom_edad+=x.edad;
      prom_altura+=x.altura;
      prom_peso+=x.peso;
		}	
		db.close();	
    
    // Sacamos todos lo promedios
    prom_edad=prom_edad/i;
    prom_altura=prom_altura/i;
    prom_peso=prom_peso/i;
		
		cout<<"Promedio de Peso: "<<prom_peso<<endl;
		cout<<"Promedio de Altura: "<<prom_altura<<endl;
    cout<<"Promedio de Edad: "<<prom_edad<<endl;
    cin.ignore();
    pausar_pantalla();
	}
	catch(exception& X){
		cout<<"Error en la manipulacion del archivo"<<endl;
		cout<<"Error: "<<X.what()<<endl;
		pausar_pantalla();
	}
};

void mp(){
	int resp;
	do {
    // limpiamos pantalla
    limpiar_pantalla();
		cout<<"--------------------------"<<"\n";
		cout<<" Menu Principal"<<"\n";
		cout<<"-------------------"<<"\n";
		cout<<" 1 - Ingresar registro "<<"\n";
		cout<<" 2 - Reporte "<<"\n";
		cout<<" 3 - Salir"<<"\n";
		cout<<"--------------------------"<<"\n";
		cout<<" Seleccione su opcion: ";
		cin>>resp;
		if (resp==1){		
			  // limpiamos pantalla
      limpiar_pantalla();
			insert_data_db();			
		}
		else if (resp==2){		
      leer_data_db();
		}
		else if (resp==3)
			break;
		else 
			break;
		
	} while(resp!=3);	
}



int main(){
  mp();

return 0;
};
