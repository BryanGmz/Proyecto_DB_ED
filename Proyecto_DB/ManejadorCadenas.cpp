/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ManejadorCadenas.cpp
 * Author: bryan
 * 
 * Created on 31 de marzo de 2020, 10:20 PM
 */

#include "ManejadorCadenas.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ManejadorCadenas::ManejadorCadenas() {}

ManejadorCadenas::ManejadorCadenas(const ManejadorCadenas& orig) {}

ManejadorCadenas::~ManejadorCadenas() {}


int ManejadorCadenas::cuenta(string s, const char separadorCte, int &totalCaracteres) {
    for (int i = 0; i < s.size(); i++)
        if (s[i] == separadorCte) totalCaracteres++;
}

void ManejadorCadenas::split(string linea, char separador, vector<string> &tempBuff, int &tamanioVector) {
    tempBuff.resize(0);
    tamanioVector = 0;
    int numero = -1;
    int numeroPosicion = -1;
    int valorNumero = 0;
    int totalChars = 0;
    int totalEspacios = linea.length();
    string valor;
    cuenta(linea, separador, totalChars);
    if (totalChars != 0) {
        while (numero < totalChars) {
            numero++;
            valorNumero = linea.find(separador, numeroPosicion + 1);
            valor = linea.substr(numeroPosicion + 1,valorNumero);
            valor = valor.substr(0, valor.find_first_of(separador));
            tempBuff.push_back(valor);
            numeroPosicion = valorNumero;
            totalEspacios++;
        }
        tamanioVector = tempBuff.size();
    } else {
        tamanioVector = 0;
    }
}