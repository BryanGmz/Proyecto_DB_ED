/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListaTablas.h
 * Author: bryan
 *
 * Created on 6 de abril de 2020, 03:26 PM
 */

#ifndef LISTATABLAS_H
#define LISTATABLAS_H

#include "ListaColumnas.h"


typedef struct NodoTabla{
    ListaColumnas listaColumnas;//Lista de columnas que posee una tabla
    int indice;//Inidice de la tabla
    string nombreTabla;
    struct NodoTabla* siguiente;
} NodoTabla;

class ListaTablas {
public:
    ListaTablas();
    ListaTablas(const ListaTablas& orig);
    virtual ~ListaTablas();
    NodoTabla* GetPrimero() const;
    NodoTabla* GetUltimo() const;
    NodoTabla* GetNodo(int);
    NodoTabla* buscarTabla(string);
    int size();
    void insertarTabla(string);
    void eliminarTabla(NodoTabla*&);
    void desplegarTabla();
    void SetPrimero(NodoTabla* primero);
    void SetUltimo(NodoTabla* ultimo);
    int cantidadDatos();
    int cantidadColumnas();
    string graphvizTabla(int &, string, bool, int);
private:
    NodoTabla* primero;
    NodoTabla* ultimo;
};

#endif /* LISTATABLAS_H */

