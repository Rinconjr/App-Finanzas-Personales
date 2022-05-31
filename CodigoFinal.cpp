#include <iostream>
#include <fstream>
#include <ctime> //Para trabajar con la fecha
#include <vector> //Para trabajar con vectores
#include <string>
#include <cctype>

/*Maximo de personas en la "Base de datos", se puede cambiar cuando uno desee
Esta es necesaria para declarar los arreglos mas adelante*/
#define MAX 5

using namespace std;

//Variables globales
int tamUsuarios = 0;
int tamDatos = 0;
int posUsuario = 0;
int contConfigInicial = 0;
int tamFinanzas = 0;

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

struct fecha{
    int dd;
    int mm;
    int aa;
};

struct movimiento{
    fecha f;
    char nomM; //I = Ingreso, E = Egreso
    char expl[50];
    float valor;
};

struct deudas{
    fecha f;
    char nomD[50];
    float valor;
};

struct finanzas{
    char nomF; 
    int tamMov;
    int tamDeudas;
    movimiento arrMovimientos[10];
    deudas arrDeudas[10];
};

//Funciones necesarias (Faltan)
void menu(usuario arrUsuarios[], dato arrDatos[], finanzas arrFinanzas[]);
void menuPrograma(usuario arrUsuarios[], dato arrDatos[], finanzas arrFinanzas[]);
void iniciarSesion(usuario arrUsuarios[], dato arrDatos[], finanzas arrFinanzas[]);
void crearCuenta(usuario arrUsuarios[]);
void configInicial(usuario arrUsuarios[], dato arrDatos[]);
void mostrarDatosPersonales(dato arrDatos[]);
void mostrarIngresos(finanzas arrFinanzas[]);
void nuevoIngreso(finanzas arrFinanzas[]);
void modificarIngresos(finanzas arrFinanzas[]);
void registrarIngresos(finanzas arrFinanzas[]);
void registrarEgresos(dato arrDatos[], finanzas arrFinanzas[]);
void salir(usuario arrUsuarios[], dato arrDatos[], finanzas arrFinanzas[]);

int main(){
    usuario arrUsuarios[MAX];
    dato arrDatos[MAX];
    finanzas arrFinanzas[MAX];

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
        exit(1);
    }

    while (!entradaD.eof()){
        entradaD >> d.nombre >> d.apellido >> d.edad >> d.ocupacion;
        if(!entradaD.eof()){
            arrDatos[tamDatos] = d;
            tamDatos++;
        }
    }

    //Flujo de datos Finanzas.dat
    ifstream entradaF("Finanzas.dat");

    if(!entradaF){
        cout << "Error abriendo el archivo Finanzas.dat";
        exit(1);
    }

    while (!entradaF.eof()){
        entradaF.read(reinterpret_cast<char *> (& arrFinanzas[tamFinanzas]), sizeof(finanzas));
        if(!entradaF.eof()){
            tamFinanzas++;
        }
    }

    entradaF.close();

    menu(arrUsuarios, arrDatos, arrFinanzas);

    return 0;
}

void iniciarSesion(usuario arrUsuarios[], dato arrDatos[], finanzas arrFinanzas[]){
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
        menuPrograma(arrUsuarios, arrDatos, arrFinanzas);
    }
}

void crearCuenta(usuario arrUsuarios[]){
    usuario e;
    bool aux = false;

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
        arrDatos[posUsuario].nombre = " ";
        arrDatos[posUsuario].apellido = " ";
        arrDatos[posUsuario].edad = 0;
        arrDatos[posUsuario].ocupacion = " ";
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
                    tamFinanzas++;
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

void mostrarDatosPersonales(dato arrDatos[]){
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

void mostrarIngresos(finanzas arrFinanzas[]){
    float contIngresos = 0;
    int aux = 0;

    //Esto comprueba si hay algun ingreso
    for (int i=0; i<arrFinanzas[posUsuario].tamMov; i++){
        if(arrFinanzas[posUsuario].arrMovimientos[i].nomM == 'I'){
            aux++;
        }
    }

    if (aux == 0){
        cout << "No cuenta con ningun ingreso registrado en la cuenta. " << endl;
    }
    else{
        cout << "Estos son los ingresos registrados: " << endl;
        for (int i=0; i<arrFinanzas[posUsuario].tamMov; i++){
            if(arrFinanzas[posUsuario].arrMovimientos[i].nomM == 'I'){
                cout << "------------------" << endl;
                cout << "#" << i+1 << endl;
                cout << "Fecha Movimiento: " << arrFinanzas[posUsuario].arrMovimientos[i].f.dd << "/" << arrFinanzas[posUsuario].arrMovimientos[i].f.mm << "/" << arrFinanzas[posUsuario].arrMovimientos[i].f.aa << endl;
                cout << arrFinanzas[posUsuario].arrMovimientos[i].expl << endl;
                cout << "Valor: $" << arrFinanzas[posUsuario].arrMovimientos[i].valor << endl;
                contIngresos = contIngresos + arrFinanzas[posUsuario].arrMovimientos[i].valor;
                cout << "------------------" << endl;
            }
        }

        cout << "Ingresos totales desde que se usa la aplicacion: $" << contIngresos << endl;
    } 
}

void nuevoIngreso(finanzas arrFinanzas[]){
    int aux = arrFinanzas[posUsuario].tamMov;

    cout << "Porfavor digite el dia del movimiento: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[aux].f.dd;

    cout << "Porfavor digite el mes del movimiento: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[aux].f.mm;

    cout << "Porfavor digite el anio del movimiento: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[aux].f.aa;

    arrFinanzas[posUsuario].arrMovimientos[aux].nomM = 'I';

    cout << "Porfavor ingrese una breve explicacion de este ingreso (PALABRAS PEGADAS): ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[aux].expl;

    cout << "Ingrese el valor de este: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[aux].valor;

    arrFinanzas[posUsuario].tamMov++;
}

void modificarIngresos(finanzas arrFinanzas[]){
    int ingMod;

    mostrarIngresos(arrFinanzas);

    cout << "Porfavor digite el # del ingreso que desea modificar: ";
    cin >> ingMod;

    ingMod--;

    cout << "Porfavor digite el dia del ingreso: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[ingMod].f.dd;

    cout << "Porfavor digite el mes del ingreso: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[ingMod].f.mm;

    cout << "Porfavor digite el anio del ingreso: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[ingMod].f.aa;

    arrFinanzas[posUsuario].arrMovimientos[ingMod].nomM = 'I';

    cout << "Porfavor ingrese una breve explicacion de este ingreso: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[ingMod].expl;

    cout << "Ingrese el valor de este: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[ingMod].valor;
}

void registrarIngresos(finanzas arrFinanzas[]){
    int opcion;
    
    do{
        system("cls");
        cout << "\t--Bienvenido a Registrar Ingresos-- " << endl;
        cout << "1. Nuevo Ingreso. " << endl;
        cout << "2. Modificar Ingreso. " << endl;
		cout << "3. Mostrar Ingresos. " << endl;
		cout << "4. Guardar (Volver) " << endl;
		
        cout << "Ingrese la opcion que desea utilizar: ";
        cin >> opcion;

        switch(opcion){
            case 1: 
                system("cls");
                    nuevoIngreso(arrFinanzas);
                system("pause");
            break;

            case 2:
                system("cls");
                    modificarIngresos(arrFinanzas);
                system("pause");
            break;

            case 3:
                system("cls");
                    mostrarIngresos(arrFinanzas);
                system("pause");
            break;

            case 4:
                system("cls");
                    cout << "Ingresos Guardados." << endl;
            break;

            default: //Si llega a ingresar una opcion no valida, salta este mensaje y se devuelve al menu.
                system("cls");
                cout << "No ingreso una opcion valida." << endl;
                system("pause");
        }
    }while (opcion != 4);
}

void mostrarEgresos(finanzas arrFinanzas[]){
    float contEgresos = 0;
    int aux = 0;

    //Esto comprueba si hay algun ingreso
    for (int i=0; i<arrFinanzas[posUsuario].tamMov; i++){
        if(arrFinanzas[posUsuario].arrMovimientos[i].nomM == 'E'){
            aux++;
        }
    }

    if (aux == 0){
        cout << "No cuenta con ningun egreso registrado en la cuenta. " << endl;
    }
    else{
        cout << "Estos son los egresos registrados: " << endl;
        for (int i=0; i<arrFinanzas[posUsuario].tamMov; i++){
            if(arrFinanzas[posUsuario].arrMovimientos[i].nomM == 'E'){
                cout << "------------------" << endl;
                cout << "#" << i+1 << endl;
                cout << "Fecha Movimiento: " << arrFinanzas[posUsuario].arrMovimientos[i].f.dd << "/" << arrFinanzas[posUsuario].arrMovimientos[i].f.mm << "/" << arrFinanzas[posUsuario].arrMovimientos[i].f.aa << endl;
                cout << arrFinanzas[posUsuario].arrMovimientos[i].expl << endl;
                cout << "Valor: $" << arrFinanzas[posUsuario].arrMovimientos[i].valor << endl;
                contEgresos = contEgresos + arrFinanzas[posUsuario].arrMovimientos[i].valor;
                cout << "------------------" << endl;
            }
        }
        cout << "Egresos totales desde que se usa la aplicacion: $" << contEgresos << endl;
    }
}

void nuevoEgreso(finanzas arrFinanzas[]){
    int aux = arrFinanzas[posUsuario].tamMov;

    cout << "Porfavor digite el dia del egreso: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[aux].f.dd;

    cout << "Porfavor digite el mes del egreso: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[aux].f.mm;

    cout << "Porfavor digite el anio del egreso: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[aux].f.aa;

    arrFinanzas[posUsuario].arrMovimientos[aux].nomM = 'E';

    cout << "Porfavor ingrese una breve explicacion de este egreso (PALABRAS PEGADAS): ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[aux].expl;

    cout << "Ingrese el valor de este: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[aux].valor;
    arrFinanzas[posUsuario].arrMovimientos[aux].valor = 0 - arrFinanzas[posUsuario].arrMovimientos[aux].valor;

    arrFinanzas[posUsuario].tamMov++;
}

void modificarEgreso(finanzas arrFinanzas[]){
    int ingMod;

    mostrarEgresos(arrFinanzas);

    cout << "Porfavor digite el # del egreso que desea modificar: ";
    cin >> ingMod;

    ingMod--;

    cout << "Porfavor digite el dia del egreso: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[ingMod].f.dd;

    cout << "Porfavor digite el mes del egreso: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[ingMod].f.mm;

    cout << "Porfavor digite el anio del egreso: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[ingMod].f.aa;

    arrFinanzas[posUsuario].arrMovimientos[ingMod].nomM = 'E';

    cout << "Porfavor ingrese una breve explicacion de este egreso (PALABRAS PEGADAS): ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[ingMod].expl;

    cout << "Ingrese el valor de este: ";
    cin >> arrFinanzas[posUsuario].arrMovimientos[ingMod].valor;
    arrFinanzas[posUsuario].arrMovimientos[ingMod].valor = 0 - arrFinanzas[posUsuario].arrMovimientos[ingMod].valor;
}

void registrarEgresos(finanzas arrFinanzas[]){
    int opcion;
    
    do{
        system("cls");
        cout << "\t--Bienvenido a Registrar Ingresos-- " << endl;
        cout << "1. Nuevo Egreso. " << endl;
        cout << "2. Modificar Egreso. " << endl;
		cout << "3. Mostrar Egresos. " << endl;
		cout << "4. Guardar (Volver) " << endl;
		
        cout << "Ingrese la opcion que desea utilizar: ";
        cin >> opcion;

        switch(opcion){
            case 1: 
                system("cls");
                    nuevoEgreso(arrFinanzas);
                system("pause");
            break;

            case 2:
                system("cls");
                    modificarEgreso(arrFinanzas);
                system("pause");
            break;

            case 3:
                system("cls");
                    mostrarEgresos(arrFinanzas);
                system("pause");
            break;

            case 4:
                system("cls");
                    cout << "Egresos Guardados." << endl;
            break;

            default: //Si llega a ingresar una opcion no valida, salta este mensaje y se devuelve al menu.
                system("cls");
                cout << "No ingreso una opcion valida." << endl;
                system("pause");
        }
    }while (opcion != 4);
}

void verMovimientos(finanzas arrFinanzas[]){
    if (arrFinanzas[posUsuario].tamMov == 0){
        cout << "No tiene movimientos registrados en esta cuenta. " << endl;
    }
    else{
        cout << "Estos son todos los movimientos registrados: " << endl;
        for (int i=0; i<arrFinanzas[posUsuario].tamMov; i++){
            cout << "------------------" << endl;
            cout << "#" << i+1 << endl;
            cout << "Fecha Movimiento: " << arrFinanzas[posUsuario].arrMovimientos[i].f.dd << "/" << arrFinanzas[posUsuario].arrMovimientos[i].f.mm << "/" << arrFinanzas[posUsuario].arrMovimientos[i].f.aa << endl;
            cout << arrFinanzas[posUsuario].arrMovimientos[i].expl << endl;
            cout << "Valor: $" << arrFinanzas[posUsuario].arrMovimientos[i].valor << endl;
            cout << "------------------" << endl;
        }
    } 
}

void verCartera(finanzas arrFinanzas[]){
    float dineroDisponible = 0;
    float deudasValor = 0;

    for (int i=0; i<arrFinanzas[posUsuario].tamMov; i++){
        dineroDisponible = dineroDisponible + arrFinanzas[posUsuario].arrMovimientos[i].valor;
    }

    for (int i=0; i<arrFinanzas[posUsuario].tamDeudas; i++){
        deudasValor = deudasValor + arrFinanzas[posUsuario].arrDeudas[i].valor;
    }

    if (dineroDisponible < 0){
        cout << "Se recomienda prestar mas atencion a sus gastos, estos superan sus ingresos, en este momento esta en una deuda de: $" << dineroDisponible << endl;
    }
    else{
        cout << "Felicitaciones, ha estado controlando sus gastos, usted tiene un dinero disponible de: $" << dineroDisponible << endl;
        if (deudasValor != 0){
            cout << "Sin embargo, tenga en cuenta que tiene deudas con un valor de: $" << deudasValor << endl;
        }
    }
}

void mostrarDeudas(finanzas arrFinanzas[]){
    float contDeuda = 0;

    if (arrFinanzas[posUsuario].tamDeudas == 0){
        cout << "No tiene registrada ninguna deuda. Felicitaciones! " << endl;
    }
    else{
        cout << "Estas son las deudas pendientes: " << endl;
        for (int i=0; i<arrFinanzas[posUsuario].tamDeudas; i++){
            cout << "------------------" << endl;
            cout << "#" << i+1 << endl;
            cout << "Fecha Deuda: " << arrFinanzas[posUsuario].arrDeudas[i].f.dd << "/" << arrFinanzas[posUsuario].arrDeudas[i].f.mm << "/" << arrFinanzas[posUsuario].arrDeudas[i].f.aa << endl;
            cout << arrFinanzas[posUsuario].arrDeudas[i].nomD << endl;
            cout << "Valor: $" << arrFinanzas[posUsuario].arrDeudas[i].valor << endl;
            contDeuda = contDeuda + arrFinanzas[posUsuario].arrDeudas[i].valor;
            cout << "------------------" << endl;
        }

        cout << "El valor total de las deudas son: $" << contDeuda << ", tenga presente esto. " << endl;
    }
}

void nuevaDeuda(finanzas arrFinanzas[]){
    int aux = arrFinanzas[posUsuario].tamDeudas;

    cout << "Porfavor digite el dia de su deuda: ";
    cin >> arrFinanzas[posUsuario].arrDeudas[aux].f.dd;

    cout << "Porfavor digite el mes de su deuda: ";
    cin >> arrFinanzas[posUsuario].arrDeudas[aux].f.mm;

    cout << "Porfavor digite el anio de su deuda: ";
    cin >> arrFinanzas[posUsuario].arrDeudas[aux].f.aa;

    cout << "Porfavor ingrese una breve explicacion de esta deuda: ";
    cin >> arrFinanzas[posUsuario].arrDeudas[aux].nomD;

    cout << "Ingrese el valor de este: ";
    cin >> arrFinanzas[posUsuario].arrDeudas[aux].valor;

    arrFinanzas[posUsuario].tamDeudas++;
}

void eliminarDeuda(finanzas arrFinanzas[]){
    int deudaMod;

    mostrarDeudas(arrFinanzas);

    cout << "Porfavor digite el # de la deuda que desea eliminar porque ya pago: ";
    cin >> deudaMod;

    deudaMod--;

    //Elimina la deuda del # ingresado por el usuario
    for (int i=deudaMod; i<arrFinanzas[posUsuario].tamDeudas;i++){
        arrFinanzas[posUsuario].arrDeudas[i] = arrFinanzas[posUsuario].arrDeudas[i+1];
    }

    arrFinanzas[posUsuario].tamDeudas--;

    system("cls");
    cout << "Felicitaciones, deuda eliminada." << endl;
}

void modificarDeuda(finanzas arrFinanzas[]){
    int deudaMod;

    mostrarDeudas(arrFinanzas);


    cout << "Porfavor digite el # de la deuda que desea modificar: ";
    cin >> deudaMod;

    deudaMod--;

    cout << "Porfavor digite el dia de la deuda: ";
    cin >> arrFinanzas[posUsuario].arrDeudas[deudaMod].f.dd;

    cout << "Porfavor digite el mes de la deuda: ";
    cin >> arrFinanzas[posUsuario].arrDeudas[deudaMod].f.mm;

    cout << "Porfavor digite el anio de la deuda: ";
    cin >> arrFinanzas[posUsuario].arrDeudas[deudaMod].f.aa;

    cout << "Porfavor ingrese una breve explicacion de esta deuda (PALABRAS PEGADAS): ";
    cin >> arrFinanzas[posUsuario].arrDeudas[deudaMod].nomD;

    cout << "Ingrese el valor de este: ";
    cin >> arrFinanzas[posUsuario].arrDeudas[deudaMod].valor;
}

void verDeudas(finanzas arrFinanzas[]){
    int opcion;
    
    do{
        system("cls");
        cout << "\t--Bienvenido a Ver Deudas-- " << endl;
        cout << "1. Nueva Deuda. " << endl;
        cout << "2. Eliminar Deuda. " << endl;
		cout << "3. Modificar Deuda. " << endl;
        cout << "4. Mostrar Deudas. " << endl;
		cout << "5. Guardar (Volver) " << endl;
		
        cout << "Ingrese la opcion que desea utilizar: ";
        cin >> opcion;

        switch(opcion){
            case 1: 
                system("cls");
                    nuevaDeuda(arrFinanzas);
                system("pause");
            break;

            case 2:
                system("cls");
                    eliminarDeuda(arrFinanzas);
                system("pause");
            break;

            case 3:
                system("cls");
                    modificarDeuda(arrFinanzas);
                system("pause");
            break;

            case 4:
                system("cls");
                    mostrarDeudas(arrFinanzas);
                system("pause");
            break;

            case 5:
                system("cls");
                    cout << "Deudas Guardadas." << endl;
            break;

            default: //Si llega a ingresar una opcion no valida, salta este mensaje y se devuelve al menu.
                system("cls");
                cout << "No ingreso una opcion valida." << endl;
                system("pause");
        }
    }while (opcion != 5);
}

void salir(usuario arrUsuarios[], dato arrDatos[], finanzas arrFinanzas[]){
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

    for(int i=0; i<tamDatos; i++){
        salidaD << arrDatos[i].nombre << " " << arrDatos[i].apellido << " " << arrDatos[i].edad << " " << arrDatos[i].ocupacion << " " << endl;
    }

    salidaD.close();

    //Salida a archivo de Finanzas.dat
    ofstream salidaF("Finanzas.dat", ios::binary);

    if(!salidaF){
        cout << "Error creando el archivo de salida. ";
        exit(1);
    }

    for (int i=0; i<tamFinanzas; i++){
        salidaF.write((char *) &arrFinanzas[i], sizeof(finanzas));
    }
    salidaF.close();
    
}

void menu(usuario arrUsuarios[], dato arrDatos[], finanzas arrFinanzas[]){
    int opcion;
    //Menu con diferentes opciones.
    do{
        system("cls");
        cout << "TamDatos: " << tamDatos;
        cout << "TamUsuarios: " << tamUsuarios;
        cout << "TamFinanzas: " << tamFinanzas;
        cout << "\t --Bienvenido a la aplicacion de finanzas personales--" << endl;
        cout << "1. Iniciar Sesion." << endl;
		cout << "2. Crear Cuenta." << endl;
		cout << "3. Salir " << endl;
		
        cout << "Ingrese la opcion que desea utilizar: ";
        cin >> opcion;

        switch(opcion){
            case 1: //Opcion iniciar sesion
                system("cls");
                    iniciarSesion(arrUsuarios, arrDatos, arrFinanzas);
                system("pause");
            break;

            case 2: //Opcion crear cuenta
                system("cls");
                    crearCuenta(arrUsuarios);
                system("pause");
            break;

            case 3: //Opcion salirse del programa.
                system("cls");
                salir(arrUsuarios, arrDatos, arrFinanzas);
                cout << "Muchas gracias por usar el programa.";
            break;

            default: //Si llega a ingresar una opcion no valida, salta este mensaje y se devuelve al menu.
                system("cls");
                cout << "No ingreso una opcion valida." << endl;
        }
    }while (opcion != 3);
}

void menuPrograma(usuario arrUsuarios[], dato arrDatos[], finanzas arrFinanzas[]){
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

    //Libreria ctime para estructurar los datos tm para poder ser utilizados al desplegar la fecha
    vector<string> dia_semana;
    dia_semana.push_back("Domingo");
    dia_semana.push_back("Lunes");
    dia_semana.push_back("Martes");
    dia_semana.push_back("Miercoles");
    dia_semana.push_back("Jueves");
    dia_semana.push_back("Viernes");
    dia_semana.push_back("Sabado");

    vector<string> mes;
    mes.push_back("Enero");
    mes.push_back("Febrero");
    mes.push_back("Marzo");
    mes.push_back("Abril");
    mes.push_back("Mayo");
    mes.push_back("Junio");
    mes.push_back("Julio");
    mes.push_back("Agosto");
    mes.push_back("Septiembre");
    mes.push_back("Octubre");
    mes.push_back("Noviembre");
    mes.push_back("Diciembre"); 

    //Menu con diferentes opciones.
    do{
        //Calcular la hora y fecha actual cada que se devuelva al menu
        time_t now = time(0);
        tm *time = localtime(&now);
        int year = 1900 + time->tm_year;

        //Capitaliza la primera letra del nombre de usuario
        string nombre = arrUsuarios[posUsuario].nombre;
        nombre[0] = toupper(nombre[0]);

        system("cls");
        cout << "\t" << nombre << ", Bienvenido al programa \n\tHoy es: " << dia_semana[time->tm_wday] << ", " << time->tm_mday << " de " << mes[time->tm_mon] << " del " << year << endl;
        cout << "\tHora actual: " << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec << endl;
        cout << "1. Mostrar datos personales." << endl;
		cout << "2. Ingresos." << endl;
        cout << "3. Egresos." << endl;
        cout << "4. Ver Cartera." << endl;
        cout << "5. Ver Movimientos." << endl;
        cout << "6. Deudas Pendientes." << endl;
		cout << "7. Cerrar sesion. " << endl;

        cout << "tamDatos:" << tamDatos << endl;
		
        cout << "Ingrese la opcion que desea utilizar: ";
        cin >> opcion;

        switch(opcion){
            case 1: 
                system("cls");
                    mostrarDatosPersonales(arrDatos);
                system("pause");
            break;

            case 2: 
                system("cls");
                    registrarIngresos(arrFinanzas);
                system("pause");
            break;

            case 3: 
                system("cls");
                    registrarEgresos(arrFinanzas);
                system("pause");
            break;

            case 4: 
                system("cls");
                    verCartera(arrFinanzas);
                system("pause");
            break;

            case 5: 
                system("cls");
                    verMovimientos(arrFinanzas);
                system("pause");
            break;

            case 6: 
                system("cls");
                    verDeudas(arrFinanzas);
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
