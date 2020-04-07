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
int colisionLineal(int, int);
bool comprobarElTipoDatoColumna(int, string);
bool esCaracter(string);
bool esDecimal(string);
bool esNumero(string);
ListaDeDB listaDB = ListaDeDB();
ManejadorQuery manejadorQuery = ManejadorQuery();
ManejadorHash manejadorHash = ManejadorHash();
NodoDB *DBActual;

int main(int argc, char** argv) {
    menu();
//    Arbol arbol = Arbol();
//    string valor = "";
//    string columna = "";
//    int contador;
//    int opcion = 1;
//    while (opcion != 0) {
////        cout<<"Ingresa valor:"<<endl;
////        getline(cin, valor, '\n');
////        cout<<"Ingresa columna:"<<endl;
////        getline(cin, columna, '\n');
//        cout<<"Ingrese Llave: "<<endl;
//        scanf("%d", &contador);
//        arbol.ingresarDatosHoja(valor, columna, contador);
//        
//        arbol.verArbol(arbol.getRaiz(), 0);
////        cout<<"Cantidad de Datos: "<<arbol.getCantidadDatosArbol()<<endl;
////        arbol.inorden(arbol.getRaiz());
//        contador++;
//    }
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
    while (opcion != 5) {
        string query;
        dbActual();
        cout<<("\n|-------------------------------------------|");
        cout<<("\n|                 ° MENU °                  |");
        cout<<("\n|---------------------|---------------------|");
        cout<<("\n| 1. Ejecutar Query   | 2. Reportes         |");
        cout<<("\n|---------------------|---------------------|");
        cout<<("\n| 3. Cambiar DB       | 4. Crear DB         |");
        cout<<("\n|---------------------|---------------------|");
        cout<<("\n| 5. Salir            |                     |");
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
                cout<<("\n\n Programa finalizado...\n\n");
                break;
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
        cout<<("\n| 2. Cantidad de datos                      |");
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
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
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
                    cout<<"-> Select <-"<<endl;
                    Select sel = Select(); 
                    manejadorQuery.select(valor, mc, sel);
                    cout<<"\n\nDatos: Seleccionar"<<endl;
                    if (!sel.IsTodosCampos()) {
                        sel.listaColumnas.desplegarLista();
                    } else {
                        cout<<"Todos los campos: "<<endl;
                    }
                    cout<<"Tabla: "<<sel.GetNombreTabla()<<endl;
                    if (!sel.IsSinCondicional()) {
                        cout<<"Columna: "<<sel.GetColumnaCodicion()<<endl;
                        cout<<"Condicion: "<<sel.GetCondicional()<<endl;
                    } cout<<"";
                } else if ((valor[i] == 'C' || valor[i] == 'c') && (valor[i + 5] == 'E' || valor[i + 5] == 'e')){
//                    cout<<"-> Create <-"<<endl;
                    Create crear = manejadorQuery.create(valor, mc);
//                    cout<<"\n\nDatos Crear: "<<endl;
//                    cout<<"Tabla: "<<crear.GetNombreTabla()<<endl;
//                    crear.lista.desplegarLista();
                    queryCrear(crear);
                    cout<<"";
                } else if ((valor[i] == 'I' || valor[i] == 'i') && (valor[i + 5] == 'T' || valor[i + 5] == 't')){
//                    cout<<"-> Insert <-"<<endl;
                    Insert inserte = Insert();
                    manejadorQuery.insert(valor, mc, inserte);
                    if (inserte.listaColumnas.size() != 0) {
                        queryInsert(inserte);
                    } cout<<"";
                } else {
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
                                cout<<"\nDato: << "<<insert.listaColumnas.GetNodo(i)->dato<<" >> Ingresado a la Columna: << "<<insert.listaColumnas.GetNodo(i)->columna<<" >>"<<endl;
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
                    cout<<"Cantidad de Datos: "<<arbol->arbolAVL.getCantidadDatosArbol()<<endl;
                    cout<<""<<endl;
                } else {
                    cout<<"\nLo siento el dato: << "<<insert.listaColumnas.GetNodo(i)->dato<<" >> no corresponde al tipo de dato de la columna: << "<<insert.listaColumnas.GetNodo(i)->columna<<" >>"<<endl;
                } cout<<"";
            } else {
                cout<<"\nLo siento no existe la columna: << "<<insert.listaColumnas.GetNodo(i)->columna<<" >> en la tabla: << "<<insert.GetNombreTabla()<<" >>"<<endl;
            } cout<<"";
        } cout<<"";
    } else {
        cout<<"\nLo siento no existe la tabla: << "<<insert.GetNombreTabla()<<" >> en la DB: << "<<DBActual->nombreDB<<" >>"<<endl;
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
                cout<<"\nLa Columna: << "<<crear.lista.GetNodo(i)->dato<<" >> Ya existe en la tabla."<<endl;
            } 
        }
        tabla->listaColumnas.desplegarColumnas();
    } else {
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
        DBActual = listaDB.buscarDB(nombreDB);
    } else {
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
    } 
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
