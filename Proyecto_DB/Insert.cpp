/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Insert.cpp
 * Author: bryan
 * 
 * Created on 1 de abril de 2020, 12:13 AM
 */

#include "Insert.h"

Insert::Insert() {
    listaColumnas = ListaCadena();
}

Insert::Insert(const Insert& orig) {
}

Insert::~Insert() {
}

string Insert::GetNombreTabla() const {
    return nombreTabla;
}

void Insert::SetNombreTabla(string nombreTabla) {
    this->nombreTabla = nombreTabla;
}