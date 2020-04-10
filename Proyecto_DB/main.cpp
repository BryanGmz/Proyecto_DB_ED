/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: bryan
 *
 * Created on 31 de marzo de 2020, 12:40 PM
 */

#include <cstdlib>
#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <time.h>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include "ManejadorCadenas.h"
#include "ManejadorHash.h"
#include "ListaCadena.h"
#include "ManejadorQuery.h"
#include "ListaDeDB.h"
#include "ListaTablas.h"
#include "ListaColumnas.h"
#include "ListaHash.h"
#include "Create.h"
#include "Insert.h"
#include "Select.h"
#include "Arbol.h"


using namespace std;

void querys(string, ManejadorCadenas);
void menu();
void menuReportes();
void dbActual();
void crearDB();
void cambiarDB();
void queryCrear(Create &crear);
void queryInsert(Insert &insert);
void querySelect(Select &select);
void realizarSelect(Select &, NodoTabla *, NodoColumna *, ListaCadena &);
void cantidadFilasDeUnMismoTipo();
void imprimirGraphviz();
int colisionLineal(int, int);
bool comprobarElTipoDatoColumna(int, string);
bool esCaracter(string);
bool esDecimal(string);
bool esNumero(string);
void imprimirSelect(ListaCadena &);
void limpiarCadena(int, ListaCadena &, vector<string>);
void ingresarAlLog(string concatenar);
void cantidadDatosDB();
ListaDeDB listaDB = ListaDeDB();
ManejadorQuery manejadorQuery = ManejadorQuery();
ManejadorHash manejadorHash = ManejadorHash();
ManejadorCadenas manejadorCadenas = ManejadorCadenas();
NodoDB *DBActual;
string logSalida = "";

int main(int argc, char** argv) {
    ingresarAlLog("Starting all servers...");
    ingresarAlLog("Starting Guatemala's Database...");
    menu();
    return 0;
}

void dbActual(){
    if (DBActual != NULL) {
        cout<<"\n\nDB: << "<<DBActual->nombreDB<<" >>"<<endl;
    } else {
        cout<<"\n\nDB: << "<<"Ninguna DB Cargado"<<" >>"<<endl;
    }
}

void menu() {
    int opcion;
    ManejadorCadenas manejador = ManejadorCadenas();
    while (opcion != 6) {
        string query;
        dbActual();
        cout<<("\n|-------------------------------------------|");
        cout<<("\n|                 ° MENU °                  |");
        cout<<("\n|---------------------|---------------------|");
        cout<<("\n| 1. Ejecutar Query   | 2. Reportes         |");
        cout<<("\n|---------------------|---------------------|");
        cout<<("\n| 3. Cambiar DB       | 4. Crear DB         |");
        cout<<("\n|---------------------|---------------------|");
        cout<<("\n| 5. Graphviz         | 6. Salir            |");
        cout<<("\n|---------------------|---------------------|");
        cout<<("\n\n Escoja una Opcion: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:   
                if (DBActual != NULL) {
                    cout<<("\nIngrese la query: \n");
                    getline(cin, query, '\n');
                    getline(cin, query, '\n');
                    querys(query, manejador);
                } else {
                    cout<<"\n ERROR: Debes de Seleccionar una DB"<<endl;
                }                
                break;
            case 2:
                menuReportes();
                break;
            case 3:
                cambiarDB();
                break;
            case 4:
                crearDB();
                break;
            case 5:
                imprimirGraphviz();
                break;
            case 6:
                cout<<("\n\n Programa finalizado...\n\n");
                listaDB.~ListaDeDB();
                exit(EXIT_SUCCESS);
            default:
                string consumir;
                cout<<("\n Opcion No Valida \n\n");
                cin>>consumir;
                break;
        } 
    }
}

void menuReportes() {
    int opcion;
    while (opcion != 6) {
        dbActual();
        cout<<("\n|-------------------------------------------|");
        cout<<("\n|             ° MENU REPORTES °             |");
        cout<<("\n|-------------------------------------------|");
        cout<<("\n| 1. Cantidad de datos en todas las DB      |");
        cout<<("\n|-------------------------------------------|");
        cout<<("\n| 2. Cantidad de datos en DB                |");
        cout<<("\n|-------------------------------------------|");
        cout<<("\n| 3. Cantidad de filas de un mismo tipo de  |");
        cout<<("\n|    dato en una tabla                      |");
        cout<<("\n|-------------------------------------------|");
        cout<<("\n| 4. Cantidad de todas las columnas de      |");
        cout<<("\n|    todas las tablas de la DB              |");
        cout<<("\n|-------------------------------------------|");
        cout<<("\n| 5. Log de la DB                           |");
        cout<<("\n|-------------------------------------------|");
        cout<<("\n| 6. Menu Principal                         |");
        cout<<("\n|-------------------------------------------|");
        cout<<("\n\n Escoja una Opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                cantidadDatosDB();
                break;
            case 2:
                if (DBActual != NULL) {
                    cout<<"\n\nDB: << "<<DBActual->nombreDB<<" >> DATOS: "<<DBActual->listaTablas.cantidadDatos()<<endl;
                } else {
                    cout<<"\n Ninguna DB"<<endl;
                }
                break;
            case 3:
                cantidadFilasDeUnMismoTipo();
                break;
            case 4:
                cout<<"\n\nDB: << "<<DBActual->nombreDB<<" >> Columnas: "<<DBActual->listaTablas.cantidadColumnas()<<endl;
                break;
            case 5:
                cout<<"\n\nArchivo Log..."<<endl<<endl;
                cout<<logSalida<<endl;
                break;
            case 6:
                menu();
            default:
                string consumir;
                cout<<("\n Opcion No Valida \n\n");
                cin>>consumir;
                break;
        }
    }
}

void querys(string valor, ManejadorCadenas mc){
    if (valor != " ") {
        for (int i = 0; i < valor.length(); i++) {
            if (valor[i] != ' ') {
                if ((valor[i] == 'S' || valor[i] == 's') && (valor[i + 5] == 'T' || valor[i + 5] == 't')) {
                    Select sel = Select(); 
                    manejadorQuery.select(valor, mc, sel);
                    querySelect(sel);
                    ingresarAlLog(" Query Realizada Select << " + valor + " >>...");
                    cout<<"";
                } else if ((valor[i] == 'C' || valor[i] == 'c') && (valor[i + 5] == 'E' || valor[i + 5] == 'e')){
                    Create crear = manejadorQuery.create(valor, mc);
                    queryCrear(crear);
                    ingresarAlLog(" Query Realizada Create << " + valor + " >>...");
                    cout<<"";
                } else if ((valor[i] == 'I' || valor[i] == 'i') && (valor[i + 5] == 'T' || valor[i + 5] == 't')){
                    Insert inserte = Insert();
                    manejadorQuery.insert(valor, mc, inserte);
                    if (inserte.listaColumnas.size() != 0) {
                        queryInsert(inserte);
                        ingresarAlLog(" Query Realizada Insert << " + valor + " >>...");
                    } cout<<"";
                } else {
                    ingresarAlLog(" ERROR: Query Instruccion Incorrecta << " + valor + " >>...");
                    cout<<" ERROR: Instruccion Incorecta.\n Vuelve a revisar tu entrada."<<endl;
                }
                break;
            }
        }
    } 
    cout<<"\nQuery Ejecutada\n"<<endl;
    manejadorQuery.~ManejadorQuery();
    menu();
}

void queryInsert(Insert &insert){
    if (DBActual->listaTablas.buscarTabla(insert.GetNombreTabla()) != NULL) {//Comprobar si existe la tabla en la DB
        NodoTabla *tablaIngresarDatos = DBActual->listaTablas.buscarTabla(insert.GetNombreTabla());
        for (int i = 0; i < insert.listaColumnas.size(); i++) {//Recorrera la lista del objeto insert comprobando si existe la columna
            bool banderaFin = false;
            if (tablaIngresarDatos->listaColumnas.buscarColumna(insert.listaColumnas.GetNodo(i)->columna)) {//Comprueba si existe la columna en la tabla
                //Comprobar el tipo de dato y compararlo al tipo de dato de la columna
                if (comprobarElTipoDatoColumna(tablaIngresarDatos->listaColumnas.buscarColumna(insert.listaColumnas.GetNodo(i)->columna)->tipoDato, insert.listaColumnas.GetNodo(i)->dato)) {
                    NodoColumna *columnaIngresar = tablaIngresarDatos->listaColumnas.buscarColumna(insert.listaColumnas.GetNodo(i)->columna);
                    int llave = manejadorHash.llave(columnaIngresar->tipoDato, insert.listaColumnas.GetNodo(i)->dato, columnaIngresar->tablaHash.size());
                    //Ingresar el arbol y comprobar si al ingresar hay una colision
                    NodoArbolAVL *arbol;
                    while (!banderaFin) {
                        arbol = columnaIngresar->tablaHash.GetNodo(llave);//Para ver en que posicion se guarda
                        if (arbol != NULL) {
                            if (arbol->arbolAVL.ingresarDatosHoja(insert.listaColumnas.GetNodo(i)->dato, insert.listaColumnas.GetNodo(i)->columna, manejadorHash.dato(columnaIngresar->tipoDato, insert.listaColumnas.GetNodo(i)->dato))) {
                                cout<<"\nDato: << "<<insert.listaColumnas.GetNodo(i)->dato<<" >> Ingresado a la Columna: << "<<insert.listaColumnas.GetNodo(i)->columna<<" >>\n";
                                columnaIngresar->tablaHash.realizarReHashing();//Comprueba si necesita realizarse un rehashing
                                banderaFin = true;
                            } else {
                                llave = colisionLineal(llave, columnaIngresar->tablaHash.size());
                            }
                        } else {
                            llave = colisionLineal(llave, columnaIngresar->tablaHash.size());
                        }
                    }
                    arbol->arbolAVL.verArbol(arbol->arbolAVL.getRaiz(), 0);
                    cout<<""<<endl;
                } else {
                    ingresarAlLog(" ERROR: El dato: << " + insert.listaColumnas.GetNodo(i)->dato + " >> no corresponde al tipo de dato de la columna << " + insert.listaColumnas.GetNodo(i)->columna + " >>...");
                    cout<<"\nLo siento el dato: << "<<insert.listaColumnas.GetNodo(i)->dato<<" >> no corresponde al tipo de dato de la columna: << "<<insert.listaColumnas.GetNodo(i)->columna<<" >>"<<endl;
                } cout<<"";
            } else {
                ingresarAlLog(" ERROR: No existe la columna: << " + insert.listaColumnas.GetNodo(i)->columna + " >> en la tabla: << " + insert.GetNombreTabla() + " >>...");
                cout<<"\nLo siento no existe la columna: << "<<insert.listaColumnas.GetNodo(i)->columna<<" >> en la tabla: << "<<insert.GetNombreTabla()<<" >>"<<endl;
            } cout<<"";
        } cout<<"";
    } else {
        ingresarAlLog(" ERROR: No existe la tabla: << " + insert.GetNombreTabla() + " >> en la DB: << " + DBActual->nombreDB + " >>...");
        cout<<"\nLo siento no existe la tabla: << "<<insert.GetNombreTabla()<<" >> en la DB: << "<<DBActual->nombreDB<<" >>"<<endl;
    } cout<<"";
}

void realizarSelect(Select &select, NodoTabla *aux, NodoColumna *auxColumna, ListaCadena &lista){
    if (select.IsTodosCampos()) {//Significa que seleccionara todos las columnas
        lista = ListaCadena();
        if (select.IsSinCondicional()) {
            for (int i = 0; i < aux->listaColumnas.size(); i++) {
                auxColumna = aux->listaColumnas.GetNodo(i);
                lista.insertar(auxColumna->tablaHash.datos(auxColumna->nombreColumna, "", false, 0), 0);
            }
        } else {
            for (int i = 0; i < aux->listaColumnas.size(); i++) {//recorre la tabla hash
                auxColumna = aux->listaColumnas.GetNodo(i);
                if (auxColumna->nombreColumna == select.GetColumnaCodicion()) {//comprueba si es la misma columna
                    lista.insertar(auxColumna->tablaHash.datos(auxColumna->nombreColumna, select.GetCondicional(), true, select.GetCondicion()), 0);
                }
            }
            if (lista.size() == 0) {
                ingresarAlLog(" ERROR: No existe la columna: << " + select.GetColumnaCodicion()+ " >> en la tabla: << " + select.GetNombreTabla() + " >>...");
                cout<<"Lo siento la columna << "<<select.GetColumnaCodicion()<<" >> no se encuntra en la tabla: << " <<select.GetNombreTabla();
            }
        } cout<<"";
    } else {
        lista = ListaCadena();
        if (select.IsSinCondicional()) {
            for (int i = 0; i < select.listaColumnas.size(); i++) {
                auxColumna = aux->listaColumnas.buscarColumna(select.listaColumnas.GetNodo(i)->dato);
                if (auxColumna != NULL) {
                    lista.insertar(auxColumna->tablaHash.datos(auxColumna->nombreColumna, "", false, 0), 0);
                } else {
                    ingresarAlLog(" ERROR: No existe la columna: << " + select.GetColumnaCodicion()+ " >> en la tabla: << " + select.GetNombreTabla() + " >>...");
                    cout<<"\nLo siento no existe la columna: <<"<<select.listaColumnas.GetNodo(i)->dato<<">> en la tabla: << "<<select.GetNombreTabla()<<" >>"<<endl;
                }
            }
        } else {
            for (int i = 0; i < select.listaColumnas.size(); i++) {
                auxColumna = aux->listaColumnas.buscarColumna(select.listaColumnas.GetNodo(i)->dato);
                if (auxColumna->nombreColumna == select.GetColumnaCodicion()) {//comprueba si es la misma columna
                    lista.insertar(auxColumna->tablaHash.datos(auxColumna->nombreColumna, select.GetCondicional(), true, select.GetCondicion()), 0);
                }
            }
            if (lista.size() == 0) {
                ingresarAlLog(" ERROR: No existe la columna: << " + select.GetColumnaCodicion()+ " >> en la tabla: << " + select.GetNombreTabla() + " >>...");
                cout<<"\nLo siento no existe la columna: << "<<select.GetColumnaCodicion()<<" >> en la tabla: << "<<select.GetNombreTabla()<<" >>"<<endl;
            } cout<<"";
        } cout<<"";
    } cout<<"";
}

void querySelect(Select &select) {
    NodoTabla *aux = DBActual->listaTablas.buscarTabla(select.GetNombreTabla());
    NodoColumna *auxColumna;
    ListaCadena lista;
    if (aux != NULL) {
        if (select.IsSinCondicional()) {
            realizarSelect(select, aux, auxColumna, lista);
            imprimirSelect(lista);
        } else {
            if (select.GetCondicion() != 0) {
                realizarSelect(select, aux, auxColumna, lista);
                imprimirSelect(lista);
            } else {
                ingresarAlLog(" ERROR: Condicional Incorrecta...");
                cout<<"\nLo siento la condicional no es correcta vuelve a revisar tu entrada"<<endl;
            } cout<<"";
        }
    } else {
        ingresarAlLog(" ERROR: No existe la tabla: << " + select.GetNombreTabla() + " >> en la DB: << " + DBActual->nombreDB + " >>...");
        cout<<"\nLo siento no existe la tabla: << "<<select.GetNombreTabla()<<" >> en la DB: << "<<DBActual->nombreDB<<" >>"<<endl;
    } cout<<"";
}

void queryCrear(Create &crear) {
    //Crea una nueva tabla
    NodoTabla *tabla;//Nueva Tabla
    if (DBActual->listaTablas.buscarTabla(crear.GetNombreTabla()) == NULL) {
        DBActual->listaTablas.insertarTabla(crear.GetNombreTabla());
        tabla = DBActual->listaTablas.buscarTabla(crear.GetNombreTabla());
        cout<<endl;
        for (int i = 0; i < crear.lista.size(); i++) {
            if (tabla->listaColumnas.buscarColumna(crear.lista.GetNodo(i)->dato) == NULL) {
                tabla->listaColumnas.insertarColumna(crear.lista.GetNodo(i)->dato, crear.lista.GetNodo(i)->tipoDato);
                cout<<"Agregado"<<endl;
            } else {
                ingresarAlLog(" ERROR: Ya existe la columna: << " + crear.lista.GetNodo(i)->dato + " >> en la tabla: << " + crear.GetNombreTabla() + " >>...");
                cout<<"\nLa Columna: << "<<crear.lista.GetNodo(i)->dato<<" >> Ya existe en la tabla."<<endl;
            } 
        }
    } else {
        ingresarAlLog(" ERROR: Ya existe la tabla: << " + crear.GetNombreTabla() + " >> en la DB: << " + DBActual->nombreDB + " >>...");
        cout<<"\n Lo siento ya existe una tabla con el mismo nombre."<<endl;
    }
}

void crearDB(){
    string nombreDB;
    cout<<"\nCreando DB: \nIngresa el Nombre: "<<endl;
    cin>>nombreDB;
    if (listaDB.buscarDB(nombreDB) == NULL) {
        cout<<"\n<< CREANDO DB >>"<<endl;
        listaDB.insertarDB(nombreDB);
        cout<<"\n<< DB CREADO >>"<<endl;
        ingresarAlLog(" Database << " + nombreDB + " >> Creado...");
        DBActual = listaDB.buscarDB(nombreDB);
    } else {
        ingresarAlLog(" ERROR: Database ya Existe << " + nombreDB + " >>...");
        cout<<"\nLo siento ya existe una Base de Datos con el mismo nombre."<<endl;
    }
    menu();
}

void cambiarDB(){
    int index;
    cout<<"\nSelecciona una DB ingresando el indice:"<<endl;
    listaDB.desplegarDB();
    cout<<"\nIngresa el indice: "; 
    scanf("%d", &index);
    if (listaDB.GetNodo(index) != NULL) {
        DBActual = listaDB.GetNodo(index);
        ingresarAlLog(" Database << " + DBActual->nombreDB + " >> Cambiado...");
    } cout<<"";
    menu();
}

bool esNumero(string entrada){
    for (int i = 0; i < entrada.length(); i++) {
        if (!isdigit(entrada[i])) {
            return false;
        }
    } return true;
}

bool esDecimal(string comprobar){
    bool banderaPunto = false;
    for (int i = 0; i < comprobar.length(); i++) {
        if (!isdigit(comprobar[i])) {
            if (comprobar[i] != '.') {
                return false;
            } else {
                if (banderaPunto == true || comprobar[0] == '.') {
                    return false;
                } else {
                    banderaPunto = true;
                }
            }
        }
    } return true;
}

bool esCaracter(string entrada){
    return (entrada.length() == 1);
}

bool comprobarElTipoDatoColumna(int tipoDato, string cadena){
    switch (tipoDato){
        case 1: return true;
        case 2: return (esCaracter(cadena));
        case 3: return (esNumero(cadena));
        case 4: return (esDecimal(cadena));
        default: return false;
    }
}

int colisionLineal(int llave, int sizeTablaHash) {
    if (llave >= (sizeTablaHash - 1)) {
        return 0;
    } else {
        return (llave + 1);
    }
}

void limpiarCadena(int size, ListaCadena &lista, vector<string> TempBuff){
    for (int i = 0; i < size; i++) {
        if (TempBuff[i] != "") {
            lista.insertar(TempBuff[i], 0);
        }
    }
}

void imprimirSelect(ListaCadena &lista){
    vector<string> TempBuff;
    ListaCadena auxLista;
    int size;
    int aux;
    if (lista.size() != 0) {
        manejadorCadenas.split(lista.GetNodo(0)->dato, *"\n", TempBuff, aux);
        limpiarCadena(aux, auxLista, TempBuff);
        aux = auxLista.size();
        for (int r = 0; r < aux; r++) {
            for (int i = 0; i < lista.size(); i++) {//recorre toda la lista que contiene las columnas
            manejadorCadenas.split(lista.GetNodo(i)->dato, *"\n", TempBuff, size);//splitea la cadena 
            if (r == 0) {
                if ((i + 1) == lista.size()) {
                    cout<<TempBuff[r]<<endl;
                } else {
                    cout<<TempBuff[r]<<"\t\t";
                }
            } else {
                if ((i + 1) == lista.size()) {
                    cout<<TempBuff[r]<<endl;
                } else {
                    cout<<TempBuff[r]<<"\t\t\t";
                }
            }
            } 
        }
    } else {
        cout<<"\nNingun Dato Encontrado"<<endl;
    }
}

void ingresarAlLog(string concatenar){
    char fecha[25];
    time_t current_time;
    current_time = time(NULL);
    ctime(&current_time);
    strcpy(fecha, ctime(&current_time));
    string salida = fecha;
    logSalida += salida + "  " + concatenar + "\n";
}

void cantidadDatosDB(){
    cout<<"\nGuatemala's Database: \n"<<endl;
    for (int i = 0; i < listaDB.size(); i++) {
        cout<<"DB: << "<<listaDB.GetNodo(i)->nombreDB<<" >> DATOS: "<<listaDB.GetNodo(i)->listaTablas.cantidadDatos()<<endl;
    }
}

void cantidadFilasDeUnMismoTipo(){
    NodoTabla *auxTabla;
    int opcion = 0;
    cout<<"\nSelecciona la tabla: "<<endl;
    for (int i = 0; i < DBActual->listaTablas.size(); i++) {
        cout<<"[ "<<(DBActual->listaTablas.GetNodo(i)->indice + 1)<<" ]"<<" Tabla: "<<DBActual->listaTablas.GetNodo(i)->nombreTabla<<endl;
    } 
    scanf("%d", &opcion);
    if (opcion <= DBActual->listaTablas.size()) {
        auxTabla = DBActual->listaTablas.GetNodo((opcion - 1));
        cout<<"\nSelecciona el Tipo de Dato: \n1. String \n2. Cadena \n3. Int \n4. Double\n";
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                cout<<"\nTabla: << "<<auxTabla->nombreTabla<<" >> Cantidad de Filas de Tipo String: "<<auxTabla->listaColumnas.cantidadFilas(1);
                break;
            case 2:
                cout<<"\nTabla: << "<<auxTabla->nombreTabla<<" >> Cantidad de Filas de Tipo Char: "<<auxTabla->listaColumnas.cantidadFilas(2);
                break;
            case 3:
                cout<<"\nTabla: << "<<auxTabla->nombreTabla<<" >> Cantidad de Filas de Tipo Int: "<<auxTabla->listaColumnas.cantidadFilas(3);
                break;
            case 4:
                cout<<"\nTabla: << "<<auxTabla->nombreTabla<<" >> Cantidad de Filas de Tipo Double: "<<auxTabla->listaColumnas.cantidadFilas(4);
                break;
            default:
                string consumir;
                cin>>consumir;
                cout<<"\nOpción Invalida.";
                break;
        }
    }
    menu();
}

void imprimirGraphviz(){
    if (DBActual != NULL) {
        int opcion = 0;
        int contador = 0;
        ofstream fs("archivo.dot");
        string graphivz = "digraph G {\n\n";
        graphivz += DBActual->nombreDB + "[shape=box];\n";
        graphivz += "rankdir=LR;\n";
        graphivz += "node [shape=record, width=.1, height=.1];\n\n";
        cout<<"[ 1 ] Graficar toda la estructura de la DB << "<<DBActual->nombreDB<<" >>"<<endl;
        cout<<"[ Cualquier otro número ] Graficar la estuctura de una tabla de la DB << "<<DBActual->nombreDB<<" >>"<<endl;
        scanf("%d", &opcion);
        if (opcion == 1) {
            graphivz += DBActual->listaTablas.graphvizTabla(contador, DBActual->nombreDB, false, 0);
            graphivz += "\n}";
            fs<<graphivz<<endl;
            fs.close();
            system("dot -Tpng archivo.dot -o imagen.png");
            system("nohup display ./imagen.png");
        } else {
            cout<<"Ingresa el numero de la tabla: "<<endl;
            for (int i = 0; i < DBActual->listaTablas.size(); i++) {
                cout<<"[ "<<(i+1)<<" ] Tabla << "<<DBActual->listaTablas.GetNodo(i)->nombreTabla<<" >>"<<endl;
            }
            scanf("%d", &opcion);
            if (opcion < DBActual->listaTablas.size() && opcion > 0) {
                graphivz += DBActual->listaTablas.graphvizTabla(contador, DBActual->nombreDB, true, (opcion - 1));
                graphivz += "\n}";
                fs<<graphivz<<endl;
                fs.close();
                system("dot -Tpng archivo.dot -o imagen.png");
                system("nohup display ./imagen.png");
            } else {
                cout<<"Opcion No Valida..."<<endl;
            }
        }
    } else {
        cout<<"Lo siento debes de cargar una DB"<<endl;
    }
    menu();
}