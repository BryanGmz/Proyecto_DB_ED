/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Select.cpp
 * Author: bryan
 * 
 * Created on 1 de abril de 2020, 12:00 AM
 */

#include "Select.h"

Select::Select() {
    this->listaColumnas = ListaCadena();
}

Select::Select(const Select& orig) {
}

Select::~Select() {
}

string Select::GetColumnaCodicion() const {
    return columnaCodicion;
}

void Select::SetColumnaCodicion(string columnaCodicion) {
    this->columnaCodicion = columnaCodicion;
}

string Select::GetCondicional() const {
    return condicional;
}

void Select::SetCondicional(string condicional) {
    this->condicional = condicional;
}

string Select::GetNombreTabla() const {
    return nombreTabla;
}

void Select::SetNombreTabla(string nombreTabla) {
    this->nombreTabla = nombreTabla;
}

int Select::GetTipo() const {
    return tipo;
}

void Select::SetTipo(int tipo) {
    this->tipo = tipo;
}

bool Select::IsTodosCampos() const {
    return todosCampos;
}

void Select::SetTodosCampos(bool todosCampos) {
    this->todosCampos = todosCampos;
}

void Select::SetListaColumnas(const ListaCadena& lista) {
    this->listaColumnas = lista;
}

bool Select::IsSinCondicional() const {
    return sinCondicional;
}

void Select::SetSinCondicional(bool sinCondicional) {
    this->sinCondicional = sinCondicional;
}