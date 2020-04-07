/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListaSimpleCadenaInstrucciones.cpp
 * Author: bryan
 * 
 * Created on 31 de marzo de 2020, 10:40 PM
 */

#include <cstdlib>
#include <iostream>
#include "ListaCadena.h"

ListaCadena::ListaCadena() {
    this->primero = NULL;
    this->ultimo = NULL;
}

ListaCadena::ListaCadena(const ListaCadena& orig) {}

ListaCadena::~ListaCadena() {
    while (primero != NULL) {
        eliminar(primero);
    }
}

Nodo* ListaCadena::GetPrimero() const {
    return primero;
}

void ListaCadena::SetPrimero(Nodo* primero) {
    this->primero = primero;
}

Nodo* ListaCadena::GetUltimo() const {
    return ultimo;
}

void ListaCadena::SetUltimo(Nodo* ultimo) {
    this->ultimo = ultimo;
}

void ListaCadena::insertar(string insertar, int tipoDato) {
    Nodo* agregar = new Nodo();
    agregar->dato = insertar;
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


void ListaCadena::insertarInsert(string valor, string insertarColumna) {
    Nodo* agregar = new Nodo();
    agregar->dato = valor;
    agregar->columna = insertarColumna;
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

int ListaCadena::size() {
    if (primero != NULL) {
        return (ultimo->indice + 1);
    } else {
        return 0;
    }
}


void ListaCadena::desplegarLista() {
    Nodo* actual = primero;
    if(primero != NULL){
	while(actual != NULL){
            cout<<("\nDato: ")<<actual->dato<<endl;
            cout<<("Tipo Dato: ")<<actual->tipoDato<<endl;
            cout<<("Indice: ")<<actual->indice<<endl;
            cout<<"Columna: "<<actual->columna<<"\n"<<endl;
            actual = actual->siguiente;
	}
    } else {
        cout<<("\nLa lista se encuentra vacia\n\n");
    }
}

void ListaCadena::eliminar(Nodo *&eliminando) {
    Nodo *actual = primero;
    Nodo *anterior = NULL;
    int encontrado;
    if (primero != NULL) {
        while (actual != NULL && encontrado != 1) {
            if(actual->dato == eliminando->dato){
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

Nodo* ListaCadena::GetNodo(int indice) {
    Nodo* actual = primero;
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

