/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ManejadorQuery.h
 * Author: bryan
 *
 * Created on 4 de abril de 2020, 05:49 PM
 */

#include <cstdlib>
#include <iostream>
#include "Create.h"
#include "Insert.h"
#include "Select.h"
#include "ManejadorCadenas.h"
#ifndef MANEJADORQUERY_H
#define MANEJADORQUERY_H

using namespace std;

class ManejadorQuery {
public:
    ManejadorQuery();
    ManejadorQuery(const ManejadorQuery& orig);
    virtual ~ManejadorQuery();
    int tipoDato(string);
    int condicion(string);
    Create create(string, ManejadorCadenas);
    void remplazar(string &, char, char);
    void select(string, ManejadorCadenas, Select &);
    void insertarALista(int, ListaCadena &, vector<string>);
    void insert(string, ManejadorCadenas mc, Insert &);
    void realizarTerceraParte(string, Insert &, ManejadorCadenas);
    void limpiarCadenaDeEspacios(int, string &);
    void limpiarCadenaDeEspaciosFinales(string &);
private:

};

#endif /* MANEJADORQUERY_H */

