/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Create.h
 * Author: bryan
 *
 * Created on 1 de abril de 2020, 12:16 AM
 */

#include <cstdlib>
#include <iostream>
#include "ListaCadena.h"
#ifndef CREATE_H
#define CREATE_H

using namespace std;

class Create {
public:
    string GetNombreTabla() const;
    void SetNombreTabla(string);
    Create();
    void SetLista(const ListaCadena& lista);
    ListaCadena lista;
    Create(const Create& orig);
    virtual ~Create();
private:
    string nombreTabla;
};

#endif /* CREATE_H */

