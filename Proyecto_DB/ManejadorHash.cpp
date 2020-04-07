/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ManejadorHash.cpp
 * Author: bryan
 * 
 * Created on 6 de abril de 2020, 05:33 PM
 */

#include "ManejadorHash.h"
#include <iostream>

ManejadorHash::ManejadorHash() {}

ManejadorHash::ManejadorHash(const ManejadorHash& orig) {}

ManejadorHash::~ManejadorHash() {}

bool ManejadorHash::digito(string comprobar){
    for (int i = 0; i < comprobar.length(); i++) {
        if (!isdigit(comprobar[i])) {
            return false;
        }
    } return true;
}

bool ManejadorHash::decimal(string comprobar){
    bool banderaPunto = false;
    for (int i = 0; i < comprobar.length(); i++) {
        if (!isdigit(comprobar[i])) {
            if (comprobar[i] != '.') {
                return false;
            } else {
                if (banderaPunto == true || comprobar[0] == '.') {
                    return false;
                } else {
                    banderaPunto = true;
                }
            }
        }
    } return true;
}

int ManejadorHash::funcionHash(long long llave, int sizeTabla){
    return (llave%sizeTabla);
}

int ManejadorHash::charANumero(char convertir){
    return convertir;
}

long long ManejadorHash::cadenaANumero(string valor){
    long long llave;
    for (int i = 0; i < valor.length(); i++) {
        if (i == 0) {
            llave = (charANumero(valor[i]) * (i + 1));
        } else {
            llave += (charANumero(valor[i]) * (i + 1));
        }
    }
    return llave;
}

int ManejadorHash::llave(int tipoDato, string cadena, int sizeTablaHash) {
    switch (tipoDato) {
        case 1: return (funcionHash(cadenaANumero(cadena), sizeTablaHash));
        case 2: return (funcionHash(charANumero(cadena[0]), sizeTablaHash));
        case 3: return (funcionHash(atoi(cadena.c_str()), sizeTablaHash));
        case 4: return (funcionHash(cadenaANumero(cadena), sizeTablaHash));
    }
}

int ManejadorHash::dato(int tipoDato, string cadena) {
    switch (tipoDato) {
        case 1: return cadenaANumero(cadena);
        case 2: return charANumero(cadena[0]);
        case 3: return atoi(cadena.c_str());
        case 4: return cadenaANumero(cadena);
    }
}