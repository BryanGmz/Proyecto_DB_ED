/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Select.h
 * Author: bryan
 *
 * Created on 1 de abril de 2020, 12:00 AM
 */

#include <cstdlib>
#include <iostream>
#include "ListaCadena.h"
#ifndef SELECT_H
#define SELECT_H

using namespace std;

class Select {
public:
    Select();
    Select(const Select& orig);
    virtual ~Select();
    ListaCadena listaColumnas;
    string GetColumnaCodicion() const;
    string GetCondicional() const;
    string GetNombreTabla() const;
    int GetTipo() const;
    bool IsTodosCampos() const;
    bool IsSinCondicional() const;
    void SetSinCondicional(bool sinCondicional);
    void SetTodosCampos(bool todosCampos);
    void SetListaColumnas(const ListaCadena& listaColumnas);
    void SetNombreTabla(string nombreTabla);
    void SetCondicional(string condicional);
    void SetColumnaCodicion(string columnaCodicion);
    void SetTipo(int tipo);
private:
    string nombreTabla;
    string columnaCodicion;
    string condicional;
    bool todosCampos;
    bool sinCondicional;
    int tipo;    
};

#endif /* SELECT_H */

