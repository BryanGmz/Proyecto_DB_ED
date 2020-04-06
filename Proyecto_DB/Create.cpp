/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Create.cpp
 * Author: bryan
 * 
 * Created on 1 de abril de 2020, 12:16 AM
 */

#include "Create.h"

Create::Create() {
    this->lista = ListaCadena();
}

Create::Create(const Create& orig) {
}

Create::~Create() {
}

string Create::GetNombreTabla() const {
    return nombreTabla;
}

void Create::SetNombreTabla(string nombreTabla) {
    this->nombreTabla = nombreTabla;
}

void Create::SetLista(const ListaCadena& lista) {
    this->lista = lista;
}