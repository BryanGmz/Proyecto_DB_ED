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
#include <iostream>
#include <stdio.h>
#include "ManejadorCadenas.h"
#include "ListaCadena.h"
#include "ManejadorQuery.h"

#include "Create.h"
#include "Insert.h"
#include "Select.h"
#include "Arbol.h"

using namespace std;

void querys(string, ManejadorCadenas);
void menu();
void menuReportes();
void dbActual();

int main(int argc, char** argv) {
    //menu();
    Arbol arbol = Arbol();
    string valor = "";
    string columna = "";
    int contador;
    int opcion = 1;
    while (opcion != 0) {
//        cout<<"Ingresa valor:"<<endl;
//        getline(cin, valor, '\n');
//        cout<<"Ingresa columna:"<<endl;
//        getline(cin, columna, '\n');
        cout<<"Ingrese Llave: "<<endl;
        scanf("%d", &contador);
        arbol.ingresarDatosHoja(valor, columna, contador);
        
        arbol.verArbol(arbol.getRaiz(), 0);
//        cout<<"Cantidad de Datos: "<<arbol.getCantidadDatosArbol()<<endl;
//        arbol.inorden(arbol.getRaiz());
        contador++;
    }
    return 0;
}

void dbActual(){
    cout<<"\n\nDB: << "<<"Base de Datos"<<" >>"<<endl;
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
                cout<<("\nIngrese la query: \n");
                getline(cin, query, '\n');
                getline(cin, query, '\n');
                querys(query, manejador);
                break;
            case 2:
                menuReportes();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                cout<<("\n\n Programa finalizado...\n\n");
                break;
            default:
                cout<<("\n\n Opcion No Valida \n\n");
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
                cout<<("\n\n Opcion No Valida \n\n");
                break;
        }
    }
}

void querys(string valor, ManejadorCadenas mc){
    ManejadorQuery manejadorQuery = ManejadorQuery();
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
                    } 
                } else if ((valor[i] == 'C' || valor[i] == 'c') && (valor[i + 5] == 'E' || valor[i + 5] == 'e')){
                    cout<<"-> Create <-"<<endl;
                    Create crear = manejadorQuery.create(valor, mc);
                    cout<<"\n\nDatos Crear: "<<endl;
                    cout<<"Tabla: "<<crear.GetNombreTabla()<<endl;
                    crear.lista.desplegarLista();
                } else if ((valor[i] == 'I' || valor[i] == 'i') && (valor[i + 5] == 'T' || valor[i + 5] == 't')){
                    cout<<"-> Insert <-"<<endl;
                    Insert inserte = Insert();
                    manejadorQuery.insert(valor, mc, inserte);
                    cout<<"\n\nDatos Crear: "<<endl;
                    cout<<inserte.GetNombreTabla()<<endl;
                    inserte.listaColumnas.desplegarLista();
                } 
                break;
            }
        }
    } 
    cout<<"\n\nQuery Ejecutada\n"<<endl;
    manejadorQuery.~ManejadorQuery();
    menu();
}