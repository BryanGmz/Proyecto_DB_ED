/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListaDeDB.cpp
 * Author: bryan
 * 
 * Created on 6 de abril de 2020, 03:55 PM
 */

#include "ListaDeDB.h"

ListaDeDB::ListaDeDB() {
    this->primero = NULL;
    this->ultimo = NULL;
}

ListaDeDB::ListaDeDB(const ListaDeDB& orig) {}

ListaDeDB::~ListaDeDB() {}

NodoDB* ListaDeDB::GetPrimero() const {
    return primero;
}

void ListaDeDB::SetPrimero(NodoDB* primero) {
    this->primero = primero;
}

NodoDB* ListaDeDB::GetUltimo() const {
    return ultimo;
}

void ListaDeDB::SetUltimo(NodoDB* ultimo) {
    this->ultimo = ultimo;
}

NodoDB* ListaDeDB::GetNodo(int indice) {
    NodoDB *actual = primero;
    int encontrado = 0;
    if (primero != NULL) {
        while ((actual != NULL) && (encontrado != 1)) {
            if (actual->indice == indice) {
                encontrado = 1;
                return actual;
            } actual = actual->siguiente;
        }
        if (encontrado == 0) {
            cout<<"\nLo siento no se encuentra la DB.\n"<<endl;
            return NULL;
        }
    }
}

NodoDB* ListaDeDB::buscarDB(string nombreDB) {
    NodoDB *actual = primero;
    int encontrado = 0;
    if (primero != NULL) {
        while ((actual != NULL) && (encontrado != 1)) {
            if (actual->nombreDB == nombreDB) {
                encontrado = 1;
                return actual;
            } actual = actual->siguiente;
        }
        if (encontrado == 0) {
//            cout<<"\nLo siento no se encuentra la DB.\n"<<endl;
            return NULL;
        }
    }
}

void ListaDeDB::desplegarDB() {
    NodoDB *actual = primero;//Deplegara en orden asendente mediante el indice
    if (primero != NULL) {
        while (actual != NULL) {//Continuara hasta finalizar la lista
            cout<<"\nInidice: "<<actual->indice<<endl;
            cout<<"Nombre de la DB: "<<actual->nombreDB<<endl;
            cout<<"Cantidad de Tablas: "<<actual->listaTablas.size()<<endl;
            actual = actual->siguiente;
        }
    } else {
        cout<<"\nLa lista se encuentra vacia.\n";
    }
}

void ListaDeDB::eliminarDB(NodoDB *&eliminando) {
    NodoDB *actual = primero;
    NodoDB *anterior = NULL;
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

void ListaDeDB::insertarDB(string nombreDB) {
    NodoDB *agregar = new NodoDB();
    agregar->nombreDB = nombreDB;
    agregar->listaTablas = ListaTablas();
    if (primero == NULL) {//Significa que es la primer tupla a insertar
        agregar->indice = 0;//Le asigna el indice cero 
        primero = agregar;//El primero apuntara a agregar
        primero->siguiente = NULL;//El siguiente del primero apuntara a NULL porque no hay más datos en la lista
        ultimo = agregar;//El ultimo debe de apuntar al nodo agregado
    } else {
        agregar->indice = ((ultimo->indice) + 1);//Agrega el indice de la nueva tupla
        ultimo->siguiente = agregar;//Se debe de cambiar de apuntador al ultimo de la lista
        agregar->siguiente = NULL;//El siguiente de la nueva tupla apuntara a NULL porque no hay más datos en la lista
        ultimo =agregar;//El ultimo debe de apuntar al nodo agregado
    }
}

int ListaDeDB::size() {
    if (primero != NULL) {
        return (ultimo->indice + 1);
    } else {
        return 0;
    }
}
