/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListaHash.cpp
 * Author: bryan
 * 
 * Created on 6 de abril de 2020, 12:44 PM
 */

#include "ListaHash.h"
#include "ListaCadena.h"

ListaHash::ListaHash() {
    this->primero = NULL;
    this->ultimo = NULL;
    for (int i = 0; i < 5; i++) {
        this->insertarNuevaTupla();
    }
}

ListaHash::ListaHash(const ListaHash& orig) {}

ListaHash::~ListaHash() {}

NodoArbolAVL* ListaHash::GetPrimero() const {
    return primero;
}

void ListaHash::SetPrimero(NodoArbolAVL* primero) {
    this->primero = primero;
}

NodoArbolAVL* ListaHash::GetUltimo() const {
    return ultimo;
}

void ListaHash::SetUltimo(NodoArbolAVL* ultimo) {
    this->ultimo = ultimo;
}

void ListaHash::insertarNuevaTupla() {
    NodoArbolAVL *agregar = new NodoArbolAVL();//Crea un nuevo espacio en memoria
    agregar->arbolAVL = Arbol();//Crea una nueva estructura de Arbol AVL para poder ingresar los datos
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

int ListaHash::size() {
    if (primero != NULL) {
        return (ultimo->indice + 1);
    } else {
        return 0;
    }
}

void ListaHash::desplegarLista() {
    NodoArbolAVL *actual = primero;//Deplegara en orden asendente mediante el indice
    if (primero != NULL) {
        while (actual != NULL) {//Continuara hasta finalizar la lista
            cout<<"\n\nInidice: "<<actual->indice<<endl;
            actual->arbolAVL.verArbol(actual->arbolAVL.getRaiz(), 0);
            actual = actual->siguiente;
        }
    } else {
        cout<<"\nLa lista se encuentra vacia.\n";
    }
}

void ListaHash::eliminarTupla(NodoArbolAVL *&eliminando) {
    NodoArbolAVL *actual = primero;
    NodoArbolAVL *anterior = NULL;
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

NodoArbolAVL* ListaHash::GetNodo(int indice) {
    NodoArbolAVL *actual = primero;
    int encontrado = 0;
    if (primero != NULL) {
        while ((actual != NULL) && (encontrado != 1)) {
            if (actual->indice == indice) {
                encontrado = 1;
                return actual;
            } actual = actual->siguiente;
        } return NULL;
    } return NULL;
}

void ListaHash::realizarReHashing() {
    int items = 0;
    NodoArbolAVL *aux;
    for (int i = 0; i < this->size(); i++) {
        aux = GetNodo(i);
        if (aux != NULL) {
            if (aux->arbolAVL.getCantidadDatosArbol() != 0) {
                items++;
            }
        }   
    }
    float factorDeCarga = ((items*100/this->size()*100)/100);//Se calcula el factor de carga
    if (factorDeCarga > 60) {//Comprobando Factor de Carga
        cout<<"\nRealizando ReHashing FC: "<<factorDeCarga<<endl;
        this->insertarNuevaTupla();
    }
}

string ListaHash::datos(string columna, string cadenaCondicion, bool condicion, int tipo){
    string retornar = "<< " + columna + " >>\n";
    NodoArbolAVL *aux;
    for (int i = 0; i < this->size(); i++) {
        aux = this->GetNodo(i);
        retornar += aux->arbolAVL.seleccionar(aux->arbolAVL.getRaiz(), cadenaCondicion, condicion, tipo);
    }
    return retornar;
}

int ListaHash::cantidadDatos(){
    int retornar = 0;
    for (int i = 0; i < this->size(); i++) {
        retornar += this->GetNodo(i)->arbolAVL.getCantidadDatosArbol();
    } return retornar;
}