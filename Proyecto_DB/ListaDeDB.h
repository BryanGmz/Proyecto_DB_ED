/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListaDeDB.h
 * Author: bryan
 *
 * Created on 6 de abril de 2020, 03:55 PM
 */

#ifndef LISTADEDB_H
#define LISTADEDB_H

#include "ListaTablas.h"


typedef struct NodoDB{
    ListaTablas listaTablas;//Lista de tablas que posee una DB
    int indice;//Inidice de la DB
    string nombreDB;
    struct NodoDB* siguiente;
} NodoDB;

class ListaDeDB {
public:
    ListaDeDB();
    ListaDeDB(const ListaDeDB& orig);
    virtual ~ListaDeDB();
    NodoDB* GetPrimero() const;
    NodoDB* GetUltimo() const;
    NodoDB* GetNodo(int);
    NodoDB* buscarDB(string);
    int size();
    void insertarDB(string);//Ingresar una nueva tabla a la lista
    void eliminarDB(NodoDB*&);
    void desplegarDB();
    void SetPrimero(NodoDB*);
    void SetUltimo(NodoDB*);
private:
    NodoDB* primero;
    NodoDB* ultimo;
};

#endif /* LISTADEDB_H */

