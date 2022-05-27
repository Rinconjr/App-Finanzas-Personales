#include <iostream>
#include <fstream>

/*Maximo de personas en la "Base de datos", se puede cambiar cuando uno desee
Esta es necesaria para declarar el arreglo mas adelante*/
#define MAX 5

using namespace std;

//Variables globales
int tamUsuarios = 0;
int tamDatos = 0;
int posUsuario = 0;
int contConfigInicial = 0;

//Estructuras necesarias
struct usuario{
    string nombre;
    string contra;
    bool nuevo;
};

struct dato{
    string nombre;
    string apellido;
    int edad;
    string ocupacion;
};

//Funciones necesarias
void menu(usuario arrUsuarios[], dato arrDatos[]);
void menuPrograma(usuario arrUsuarios[], dato arrDatos[]);
void iniciarSesion(usuario arrUsuarios[], dato arrDatos[]);
void crearCuenta(usuario arrUsuarios[]);
void configInicial(usuario arrUsuarios[], dato arrDatos[]);
void mostrarDatosPersonales(usuario arrUsuarios[], dato arrDatos[]);
void salir(usuario arrUsuarios[], dato arrDatos[]);

int main(){
    usuario arrUsuarios[5];
    dato arrDatos[5];

    //Flujo de datos de entrada de Usuarios.txt
    ifstream entradaU("Usuarios.txt", ios::in);
    usuario u;

    if (!entradaU){
        cout << "Error abriendo el archivo Usuarios.txt";
        exit(1);
    }

    while (!entradaU.eof()){
        entradaU >> u.nombre >> u.contra >> u.nuevo;
        if(!entradaU.eof()){
            arrUsuarios[tamUsuarios] = u;
            tamUsuarios++;
        }
    }

    entradaU.close();

    //Flujo de datos de entrada de Datos.txt
    ifstream entradaD("Datos.txt", ios::in);
    dato d;

    if (!entradaD){
        cout << "Error abriendo el archivo Datos.txt";
    }

    while (!entradaD.eof()){
        entradaD >> d.nombre >> d.apellido >> d.edad >> d.ocupacion;
        if(!entradaU.eof()){
            arrDatos[tamDatos] = d;
            tamDatos++;
        }
    }

    entradaD.close();

    menu(arrUsuarios, arrDatos);

    return 0;
}

void iniciarSesion(usuario arrUsuarios[], dato arrDatos[]){
    usuario e;
    bool aux = false;

    cout << "Porfavor ingrese su usuario: ";
    cin >> e.nombre;

    cout << "Porfavor ingrese su contrasenia: ";
    cin >> e.contra;

    for (int i=0; i<tamUsuarios; i++){
        if (e.nombre == arrUsuarios[i].nombre && e.contra == arrUsuarios[i].contra){
            aux = true;
            posUsuario = i;
        }
    }

    if (aux == false){
        cout << "Contrasenia o usuario incorrectos." << endl;
    }
    else{
        if(arrUsuarios[posUsuario].nuevo == true){
            contConfigInicial = 0;
        }
        menuPrograma(arrUsuarios, arrDatos);
    }
}

void crearCuenta(usuario arrUsuarios[]){
    usuario e;
    bool aux = false;
    
    cout << "Cuentas disponibles: " << endl;
    for (int i=0; i<tamUsuarios; i++){
        cout << "Nombre: " << arrUsuarios[i].nombre << endl;
        cout << "Contra: " << arrUsuarios[i].contra << endl;
    }

    cout << "\t--Bienvenido a crear cuenta--";
    cout << "\nPorfavor ingrese su usuario: ";
    cin >> e.nombre;

    cout << "Porfavor ingrese su contrasenia: ";
    cin>> e.contra;

    //Comprobar si el usuario ya existe en el programa
    for (int i=0; i<=tamUsuarios; i++){
        if (arrUsuarios[i].nombre == e.nombre){
            aux = true;
        }
    }

    //Si esto es falso, quiere decir que no se encontro otro usuario igual
    //Se procede normalmente
    if (aux == false){
        arrUsuarios[tamUsuarios] = e;
        arrUsuarios[tamUsuarios].nuevo = true;
        tamUsuarios++;
        system("cls");
        cout << "Usuario creado." << endl;
    }
    else{
        system("cls");
        cout << "El usuario ingresado ya existe." << endl;
        cout << "No se creo la cuenta. " << endl;
    }
}

void configInicial(usuario arrUsuarios[], dato arrDatos[]){
    int opcion;

    if (contConfigInicial == 0){
        arrDatos[posUsuario].edad = 0;
    }
    
    do{
        system("cls");
        cout << "\t --Bienvenido la configuracion inicial--" << endl;
        cout << "Estas son las opciones de configuracion: " << endl;
        cout << "1. Nombre: " << arrDatos[posUsuario].nombre << endl;
        cout << "2. Apellido: " << arrDatos[posUsuario].apellido << endl; 
		cout << "3. Edad: " << arrDatos[posUsuario].edad << endl;
        cout << "4. Ocupacion: " << arrDatos[posUsuario].ocupacion << endl;
		cout << "5. Guardar " << endl;

        cout << "Cont: " << contConfigInicial << endl;
		
        cout << "Ingrese la opcion que desea utilizar: ";
        cin >> opcion;

        switch(opcion){
            case 1: 
                system("cls");
                    cout << "Porfavor ingrese su nombre: ";
                    cin >> arrDatos[posUsuario].nombre;
                    contConfigInicial++;
                system("pause");
            break;

            case 2:
                system("cls");
                    cout << "Porfavor ingrese su apellido: ";
                    cin >> arrDatos[posUsuario].apellido;
                    contConfigInicial++;
                system("pause");
            break;

            case 3:
                system("cls");
                    cout << "Porfavor ingrese su edad: ";
                    cin >> arrDatos[posUsuario].edad;
                    contConfigInicial++;
                system("pause");
            break;

            case 4:
                system("cls");
                    cout << "Porfavor ingrese su ocupacion: ";
                    cin >> arrDatos[posUsuario].ocupacion;
                    contConfigInicial++;
                system("pause");
            break;

            case 5:
                system("cls");
                if (contConfigInicial >= 4){
                    cout << "Configuraciones iniciales guardadas." << endl;
                    arrUsuarios[posUsuario].nuevo = false;
                    tamDatos++;
                }
                else{
                    cout << "No ha terminado las configuraciones iniciales" << endl;
                }
            break;

            default: //Si llega a ingresar una opcion no valida, salta este mensaje y se devuelve al menu.
                system("cls");
                cout << "No ingreso una opcion valida." << endl;
                system("pause");
        }
    }while (opcion != 5);
}

void mostrarDatosPersonales(usuario arrUsuarios[], dato arrDatos[]){
    int opcion;
    
    do{
        system("cls");
        cout << "\t --Bienvenido sus datos personales--" << endl;
        cout << "Si desea modificar algun dato, seleccione la opcion: " << endl;
        cout << "1. Nombre: " << arrDatos[posUsuario].nombre << endl;
        cout << "2. Apellido: " << arrDatos[posUsuario].apellido << endl; 
		cout << "3. Edad: " << arrDatos[posUsuario].edad << endl;
        cout << "4. Ocupacion: " << arrDatos[posUsuario].ocupacion << endl;
		cout << "5. Guardar (Volver) " << endl;
		
        cout << "Ingrese la opcion que desea utilizar: ";
        cin >> opcion;

        switch(opcion){
            case 1: 
                system("cls");
                    cout << "Porfavor ingrese su nombre: ";
                    cin >> arrDatos[posUsuario].nombre;
                system("pause");
            break;

            case 2:
                system("cls");
                    cout << "Porfavor ingrese su apellido: ";
                    cin >> arrDatos[posUsuario].apellido;
                system("pause");
            break;

            case 3:
                system("cls");
                    cout << "Porfavor ingrese su edad: ";
                    cin >> arrDatos[posUsuario].edad;
                system("pause");
            break;

            case 4:
                system("cls");
                    cout << "Porfavor ingrese su ocupacion: ";
                    cin >> arrDatos[posUsuario].ocupacion;
                system("pause");
            break;

            case 5:
                system("cls");
                    cout << "Datos personales guardados." << endl;
            break;

            default: //Si llega a ingresar una opcion no valida, salta este mensaje y se devuelve al menu.
                system("cls");
                cout << "No ingreso una opcion valida." << endl;
                system("pause");
        }
    }while (opcion != 5);
}

void salir(usuario arrUsuarios[], dato arrDatos[]){
    //Salida a archivo Usuarios.txt
    ofstream salidaU("Usuarios.txt", ios::out);

    if (!salidaU){
        cout << "Error abriendo el archivo de salida Usuarios.txt";
        exit(1);
    }

    for (int i=0; i<tamUsuarios; i++){
        salidaU << arrUsuarios[i].nombre << " " << arrUsuarios[i].contra << " " << arrUsuarios[i].nuevo << " " << endl;
    }

    salidaU.close();

    //Salida a archivo Datos.txt
    ofstream salidaD("Datos.txt", ios::out);

    if(!salidaD){
        cout << "Error abriendo el archivo de salida Datos.txt";
        exit(1);
    }

    for(int i=0; i<=tamUsuarios; i++){
        salidaD << arrDatos[i].nombre << " " << arrDatos[i].apellido << " " << arrDatos[i].edad << " " << arrDatos[i].ocupacion << " " << endl;
    }

    salidaD.close();
    
}

void menu(usuario arrUsuarios[], dato arrDatos[]){
    int opcion;
    //Menu con diferentes opciones.
    do{
        system("cls");
        cout << "\t --Bienvenido al la aplicacion de finanzas personales--" << endl;
        cout << "1. Iniciar Sesion." << endl;
		cout << "2. Crear Cuenta." << endl;
		cout << "3. Salir " << endl;
		
        cout << "Ingrese la opcion que desea utilizar: ";
        cin >> opcion;

        switch(opcion){
            case 1: //Opcion iniciar sesion
                system("cls");
                    iniciarSesion(arrUsuarios, arrDatos);
                system("pause");
            break;

            case 2: //Opcion crear cuenta
                system("cls");
                    crearCuenta(arrUsuarios);
                system("pause");
            break;

            case 3: //Opcion salirse del programa.
                system("cls");
                salir(arrUsuarios, arrDatos);
                cout << "Muchas gracias por usar el programa.";
            break;

            default: //Si llega a ingresar una opcion no valida, salta este mensaje y se devuelve al menu.
                system("cls");
                cout << "No ingreso una opcion valida." << endl;
        }
    }while (opcion != 3);
}

void menuPrograma(usuario arrUsuarios[], dato arrDatos[]){
    int opcion;

    if (arrUsuarios[posUsuario].nuevo == true){
        do{
        system("cls");
        cout << "\t--" << arrUsuarios[posUsuario].nombre << ", Bienvenido a la configuracion inicial del programa--" << endl;
        cout << "Porfavor configure su perfil antes de usar la aplicacion." << endl;
        cout << "1. Configurar perfil." << endl;
		cout << "2. Listo. " << endl;
		
        cout << "Ingrese la opcion que desea utilizar: ";
        cin >> opcion;

        switch(opcion){
            case 1: 
                system("cls");
                    configInicial(arrUsuarios, arrDatos);
                system("pause");
            break;

            case 2: 
                system("cls");
                cout << "Bienvenido al programa de finanzas personales." << endl;
                system("pause");
            break;

            default: //Si llega a ingresar una opcion no valida, salta este mensaje y se devuelve al menu.
                system("cls");
                cout << "No ingreso una opcion valida." << endl;
                system("pause");
        }
    }while (opcion != 2);
    }

    //Menu con diferentes opciones.
    do{
        system("cls");
        cout << "\t--" << arrUsuarios[posUsuario].nombre << ", Bienvenido al programa--" << endl;
        cout << "1. Mostrar datos personales." << endl;
		cout << "2. Opcion 2." << endl;
        cout << "3. Opcion 3." << endl;
        cout << "4. Opcion 4." << endl;
        cout << "5. Opcion 5." << endl;
        cout << "6. Opcion 6." << endl;
		cout << "7. Cerrar sesion. " << endl;

        cout << "tamDatos:" << tamDatos << endl;
		
        cout << "Ingrese la opcion que desea utilizar: ";
        cin >> opcion;

        switch(opcion){
            case 1: 
                system("cls");
                    mostrarDatosPersonales(arrUsuarios, arrDatos);
                system("pause");
            break;

            case 2: 
                system("cls");
                    cout << "Opcion 2" << endl;
                system("pause");
            break;

            case 3: 
                system("cls");
                    cout << "Opcion 3" << endl;
                system("pause");
            break;

            case 4: 
                system("cls");
                    cout << "Opcion 4" << endl;
                system("pause");
            break;

            case 5: 
                system("cls");
                    cout << "Opcion 5" << endl;
                system("pause");
            break;

            case 6: 
                system("cls");
                    cout << "Opcion 6" << endl;
                system("pause");
            break;

            case 7: //Opcion salirse del programa.
                system("cls");
                cout << "Sesion cerrada." << endl;
            break;

            default: //Si llega a ingresar una opcion no valida, salta este mensaje y se devuelve al menu.
                system("cls");
                cout << "No ingreso una opcion valida." << endl;
                system("pause");
        }
    }while (opcion != 7);
}

