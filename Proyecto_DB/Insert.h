/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Insert.h
 * Author: bryan
 *
 * Created on 1 de abril de 2020, 12:13 AM
 */

#include <cstdlib>
#include <iostream>
#include "ListaCadena.h"
#ifndef INSERT_H
#define INSERT_H

using namespace std;

class Insert {
public:
    string GetNombreTabla() const;
    void SetNombreTabla(string nombreTabla);
    ListaCadena listaColumnas;
    Insert();
    Insert(const Insert& orig);
    virtual ~Insert();
private:
    string nombreTabla;
};

#endif /* INSERT_H */

