/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListaSimpleCadenaInstrucciones.h
 * Author: bryan
 *
 * Created on 31 de marzo de 2020, 10:40 PM
 */

#include <cstdlib>
#include <iostream>
#ifndef LISTACADENA_H
#define LISTACADENA_H

using namespace std;

typedef struct Nodo{
    string dato;
    string columna;//Para los insert
    int tipoDato;//1 -> String, 2 -> Char, 3 -> Integer, 4 -> Double
    int indice;
    struct Nodo* siguiente;
} Nodo;

class ListaCadena {
public:
    ListaCadena();
    ListaCadena(const ListaCadena& orig);
    virtual ~ListaCadena();
    Nodo* GetPrimero() const;
    Nodo* GetUltimo() const;
    Nodo* GetNodo(int);
    int size();
    void SetPrimero(Nodo*);
    void SetUltimo(Nodo*);
    void insertar(string, int);
    void insertarInsert(string, string);
    void eliminar(Nodo *&);
    void desplegarLista();
private:
    Nodo* primero;
    Nodo* ultimo;
};

#endif /* LISTACADENA_H */

