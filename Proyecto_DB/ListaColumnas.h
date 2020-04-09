/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListaColumnas.h
 * Author: bryan
 *
 * Created on 6 de abril de 2020, 02:59 PM
 */

#ifndef LISTACOLUMNAS_H
#define LISTACOLUMNAS_H

#include "ListaHash.h"


typedef struct NodoColumna{
    ListaHash tablaHash;//Almacenamiento de datos de la columna
    int indice;//Inidice del dato en la lista
    string nombreColumna;//Nombre de la columna
    int tipoDato;//Tipo de dato que almacena esta columna: 1 -> String, 2 -> Char, 3 -> Integer, 4 -> Double
    struct NodoColumna* siguiente;
} NodoColumna;

class ListaColumnas {
public:
    ListaColumnas();
    ListaColumnas(const ListaColumnas& orig);
    virtual ~ListaColumnas();
    NodoColumna* GetPrimero() const;
    NodoColumna* GetUltimo() const;
    NodoColumna* GetNodo(int);
    NodoColumna* buscarColumna(string);
    int size();
    int cantidadDatos();
    int cantidadFilas(int);
    string graphvizColumnas(int &, string);
    void insertarColumna(string, int);//Ingresar una nueva columna a la tabla
    void eliminarColumna(NodoColumna*&);
    void desplegarColumnas();
    void SetPrimero(NodoColumna*);
    void SetUltimo(NodoColumna*);
private:
    NodoColumna* primero;
    NodoColumna* ultimo;
};

#endif /* LISTACOLUMNAS_H */

