/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ManejadorHash.h
 * Author: bryan
 *
 * Created on 6 de abril de 2020, 05:33 PM
 */

#ifndef MANEJADORHASH_H
#define MANEJADORHASH_H
#include "ManejadorCadenas.h"

using namespace std;

class ManejadorHash {
public:
    ManejadorHash();
    ManejadorHash(const ManejadorHash& orig);
    virtual ~ManejadorHash();
    bool digito(string);
    bool decimal(string);
    int charANumero(char);
    long long cadenaANumero(string valor);
    int funcionHash(long long, int);
    int llave(int, string, int);
    int dato(int, string);
private:
    
};

#endif /* MANEJADORHASH_H */

