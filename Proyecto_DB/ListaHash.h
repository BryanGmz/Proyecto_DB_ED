/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListaHash.h
 * Author: bryan
 * 
 * Created on 6 de abril de 2020, 12:44 PM
 */

#include "Arbol.h"
#ifndef LISTAHASH_H
#define LISTAHASH_H

typedef struct NodoArbolAVL{
    Arbol arbolAVL;//Arbol AVL Donde se guardaran los datos de las columnas
    int indice;
    struct NodoArbolAVL* siguiente;
} NodoArbolAVL;

class ListaHash {
public:
    ListaHash();
    ListaHash(const ListaHash& orig);
    virtual ~ListaHash();
    NodoArbolAVL *GetPrimero() const;
    NodoArbolAVL *GetUltimo() const;
    NodoArbolAVL *GetNodo(int);
    int size();
    int cantidadDatos();
    string datos(string, string, bool, int);
    void realizarReHashing();
    void insertarNuevaTupla();
    void eliminarTupla(NodoArbolAVL*&);
    void desplegarLista();
    void SetPrimero(NodoArbolAVL*);
    void SetUltimo(NodoArbolAVL*);
private:
    NodoArbolAVL *primero;
    NodoArbolAVL *ultimo;
};

#endif /* LISTAHASH_H */

