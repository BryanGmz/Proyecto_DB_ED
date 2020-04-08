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

ListaColumnas::ListaColumnas() {
    this->primero = NULL;
    this->ultimo = NULL;
}

ListaColumnas::ListaColumnas(const ListaColumnas& orig) {}

ListaColumnas::~ListaColumnas() {}

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
