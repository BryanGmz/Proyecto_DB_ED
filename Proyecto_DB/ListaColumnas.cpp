/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListaColumnas.cpp
 * Author: bryan
 * 
 * Created on 6 de abril de 2020, 02:59 PM
 */

#include "ListaColumnas.h"
#include <sstream>

ListaColumnas::ListaColumnas() {
    this->primero = NULL;
    this->ultimo = NULL;
}

ListaColumnas::ListaColumnas(const ListaColumnas& orig) {}

ListaColumnas::~ListaColumnas() {
    while (primero != NULL) {
        eliminarColumna(primero);
    }
}

NodoColumna* ListaColumnas::GetPrimero() const {
    return primero;
}

void ListaColumnas::SetPrimero(NodoColumna* primero) {
    this->primero = primero;
}

NodoColumna* ListaColumnas::GetUltimo() const {
    return ultimo;
}

void ListaColumnas::SetUltimo(NodoColumna* ultimo) {
    this->ultimo = ultimo;
}

NodoColumna* ListaColumnas::GetNodo(int indice) {
    NodoColumna* actual = primero;
    int encontrado = 0;
    if (primero != NULL) {
        while (actual != NULL && encontrado != 1) {
            if (actual->indice == indice) {
                encontrado = 1;
                return actual;
            } actual = actual->siguiente;
        }
    }
}

NodoColumna* ListaColumnas::buscarColumna(string nombreColumna) {
    NodoColumna* actual = primero;
    int encontrado = 0;
    if (primero != NULL) {
        while (actual != NULL && encontrado != 1) {
            if (actual->nombreColumna == nombreColumna) {
                encontrado = 1;
                return actual;
            } actual = actual->siguiente;
        }
        if (encontrado == 0) {
            return NULL;//Si no se a encontrado la columna
        }
    }
}

void ListaColumnas::desplegarColumnas() {
    NodoColumna* actual = primero;
    if(primero != NULL){
	while(actual != NULL){
            cout<<("\nIndice: ")<<actual->indice<<endl;
            cout<<("Columna: ")<<actual->nombreColumna<<endl;
            cout<<("Tipo de Dato: ")<<actual->tipoDato<<endl;
            cout<<"Tamaño de la TablaHash: "<<actual->tablaHash.size()<<"\n"<<endl;
            actual = actual->siguiente;
	}
    } else {
        cout<<("\nLa lista se encuentra vacia\n");
    }
}

void ListaColumnas::eliminarColumna(NodoColumna *&eliminando) {
    NodoColumna *actual = primero;
    NodoColumna *anterior = NULL;
    int encontrado;
    if (primero != NULL) {
        while (actual != NULL && encontrado != 1) {
            if(actual->indice == eliminando->indice){
                if(actual == primero){
                    primero = NULL;
                    ultimo = NULL;
                } else if (actual == ultimo){
                    anterior->siguiente = NULL;
                    ultimo = anterior;
                } else {
                    anterior->siguiente = NULL;
                    ultimo = anterior;
                }
                encontrado = 1;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        if(encontrado != 0){
            anterior->tablaHash.~ListaHash();
            anterior = NULL;
        }
    } 
}

void ListaColumnas::insertarColumna(string nombreColumna, int tipoDato) {
    NodoColumna* agregar = new NodoColumna();
    agregar->tablaHash = ListaHash();
    agregar->nombreColumna = nombreColumna;
    agregar->tipoDato = tipoDato;
    if (primero == NULL) {
        agregar->indice = 0;
        primero = agregar;
        primero->siguiente = NULL;
        ultimo = agregar;
    } else {
        agregar->indice = ((ultimo->indice) + 1);
        ultimo->siguiente = agregar;
        agregar->siguiente = NULL;
        ultimo = agregar;
    } 
}

int ListaColumnas::size() {
    if (primero != NULL) {
        return (ultimo->indice + 1);
    } else {
        return 0;
    }
}

int ListaColumnas::cantidadDatos() {
    int retornar = 0;
    for (int i = 0; i < this->size(); i++) {
        retornar += this->GetNodo(i)->tablaHash.cantidadDatos();
    } return retornar;
}

int ListaColumnas::cantidadFilas(int tipoDato) {
    int cantidad = 0;
    for (int i = 0; i < size(); i++) {
        if (this->GetNodo(i)->tipoDato == tipoDato) {
            if (this->GetNodo(i)->tablaHash.cantidadDatos() > cantidad) {
                cantidad += this->GetNodo(i)->tablaHash.cantidadDatos();
            }
        }
    } return cantidad;
}

string ListaColumnas::graphvizColumnas(int& contador, string nombreTabla) {
    string retornar = "";
    string aux = "";
    for (int i = 0; i < this->size(); i++) {
        retornar += "node" + static_cast<ostringstream*>(&(ostringstream() << contador))->str() + "[label=\"<f0> " + this->GetNodo(i)->nombreColumna + "\"];\n";
        aux = "node"+ static_cast<ostringstream*>(&(ostringstream() << contador))->str() + ":f0";
        contador++;
        retornar += nombreTabla + " -> " + aux + ";\n";
        retornar += aux + " -> " + "node" + static_cast<ostringstream*>(&(ostringstream() << contador))->str() + ":f0\n";
        retornar += this->GetNodo(i)->tablaHash.graphivzHash(contador);
    } return retornar;
}
