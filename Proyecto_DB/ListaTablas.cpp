/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListaTablas.cpp
 * Author: bryan
 * 
 * Created on 6 de abril de 2020, 03:26 PM
 */

#include "ListaTablas.h"

ListaTablas::ListaTablas() {
    this->primero = NULL;
    this->ultimo = NULL;
}

ListaTablas::ListaTablas(const ListaTablas& orig) {}

ListaTablas::~ListaTablas() {
    while (primero != NULL) {
        eliminarTabla(primero);
    }
}

NodoTabla* ListaTablas::GetPrimero() const {
    return primero;
}

void ListaTablas::SetPrimero(NodoTabla* primero) {
    this->primero = primero;
}

NodoTabla* ListaTablas::GetUltimo() const {
    return ultimo;
}

void ListaTablas::SetUltimo(NodoTabla* ultimo) {
    this->ultimo = ultimo;
}

NodoTabla* ListaTablas::GetNodo(int indice) {
    NodoTabla *actual = primero;
    int encontrado = 0;
    if (primero != NULL) {
        while ((actual != NULL) && (encontrado != 1)) {
            if (actual->indice == indice) {
                encontrado = 1;
                return actual;
            } actual = actual->siguiente;
        }
    }
}

NodoTabla* ListaTablas::buscarTabla(string nombreTabla) {
    NodoTabla *actual = primero;
    int encontrado = 0;
    if (primero != NULL) {
        while ((actual != NULL) && (encontrado != 1)) {
            if (actual->nombreTabla == nombreTabla) {
                encontrado = 1;
                return actual;
            } actual = actual->siguiente;
        }
        if (encontrado == 0) {
            return NULL;
        }
    }
}

void ListaTablas::desplegarTabla() {
    NodoTabla *actual = primero;//Deplegara en orden asendente mediante el indice
    if (primero != NULL) {
        while (actual != NULL) {//Continuara hasta finalizar la lista
            cout<<"\n\nInidice: "<<actual->indice<<endl;
            cout<<"Nombre de la Tabla: "<<actual->nombreTabla<<endl;
            cout<<"Cantidad de listas: "<<actual->listaColumnas.size()<<endl;
            actual = actual->siguiente;
        }
    } else {
        cout<<"\nLa lista se encuentra vacia.\n";
    }
}

void ListaTablas::eliminarTabla(NodoTabla *&eliminando) {
    NodoTabla *actual = primero;
    NodoTabla *anterior = NULL;
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
            anterior->listaColumnas.~ListaColumnas();
            anterior = NULL;
        }
    }
}

void ListaTablas::insertarTabla(string nombreTabla) {
    NodoTabla *agregar = new NodoTabla();//Crea un nuevo espacio en memoria
    agregar->nombreTabla = nombreTabla;
    agregar->listaColumnas = ListaColumnas();
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

int ListaTablas::size() {
    if (primero != NULL) {
        return (ultimo->indice + 1);
    } else {
        return 0;
    }
}

int ListaTablas::cantidadDatos() {
    int retornar = 0;
    for (int i = 0; i < this->size(); i++) {
        retornar += this->GetNodo(i)->listaColumnas.cantidadDatos();
    } return retornar;
}

int ListaTablas::cantidadColumnas() {
    int retornar = 0;
    for (int i = 0; i < this->size(); i++) {
        retornar += this->GetNodo(i)->listaColumnas.size();
    } return retornar;

}

string ListaTablas::graphvizTabla(int &contador, string nombreDB, bool todosLasTablas, int tabla) {
    string retornar = "";
    if (todosLasTablas) {
        for (int i = 0; i < this->size(); i++) {
            if (tabla == i) {
                 retornar += this->GetNodo(i)->nombreTabla + "[shape=box];\n";
                retornar += nombreDB + " -> " + this->GetNodo(i)->nombreTabla + ";\n";
                retornar += this->GetNodo(i)->listaColumnas.graphvizColumnas(contador, this->GetNodo(i)->nombreTabla);
            }           
        }
    } else {
        for (int i = 0; i < this->size(); i++) {
            retornar += this->GetNodo(i)->nombreTabla + "[shape=box];\n";
            retornar += nombreDB + " -> " + this->GetNodo(i)->nombreTabla + ";\n";
            retornar += this->GetNodo(i)->listaColumnas.graphvizColumnas(contador, this->GetNodo(i)->nombreTabla);
        }
    }
    return retornar;
}
