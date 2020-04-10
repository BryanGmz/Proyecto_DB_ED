/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ManejadorCadenas.h
 * Author: bryan
 *
 * Created on 31 de marzo de 2020, 10:20 PM
 */
//
#include <cstdlib>
#include <iostream>
#include "ListaCadena.h"
#ifndef MANEJADORCADENAS_H
#define MANEJADORCADENAS_H

using namespace std;

class ManejadorCadenas {
public:
    ManejadorCadenas();
    ManejadorCadenas(const ManejadorCadenas& orig);
    int cuenta(string, const char, int&);
    void split(string, char , ListaCadena& , int&);
    virtual ~ManejadorCadenas();
private:

};

#endif /* MANEJADORCADENAS_H */

