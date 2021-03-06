/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ManejadorQuery.cpp
 * Author: bryan
 * 
 * Created on 4 de abril de 2020, 05:49 PM
 */


#include "ManejadorQuery.h"

#include <cstdlib>
#include <iostream>


ManejadorQuery::ManejadorQuery() {
}

ManejadorQuery::ManejadorQuery(const ManejadorQuery& orig) {
}

ManejadorQuery::~ManejadorQuery() {
}

void ManejadorQuery::remplazar(string &valor, char caracter, char remplazar){
    for (int i = 0; i < valor.length(); i++) {
        if(valor[i] == caracter){
            valor[i] = remplazar;
        }
    }
}


void ManejadorQuery::insert(string querySelect, ManejadorCadenas mc, Insert &insert) {
    ListaCadena TempBuff;
    ListaCadena temporal = ListaCadena();
    int totalVector;
    mc.split(querySelect, *"(", TempBuff, totalVector);
    insertarALista(totalVector, temporal, TempBuff);
    string primerParte = temporal.GetNodo(0)->dato;
    string segundaParte = temporal.GetNodo(1)->dato;
    string tercero = temporal.GetNodo(2)->dato;
    //Primer Parte
    mc.split(primerParte, *" ", TempBuff, totalVector);
    insertarALista(totalVector, temporal, TempBuff); 
    if (totalVector > 1) {
        limpiarCadenaDeEspacios(0, temporal.GetNodo(2)->dato);
        limpiarCadenaDeEspaciosFinales(temporal.GetNodo(2)->dato);
        insert.SetNombreTabla(temporal.GetNodo(2)->dato);
        //Segunda Parte
        mc.split(segundaParte, *")", TempBuff, totalVector);
        insertarALista(totalVector, temporal, TempBuff);
        if (totalVector > 0) {
            mc.split(temporal.GetNodo(0)->dato, *",", TempBuff, totalVector);
            insertarALista(totalVector, temporal, TempBuff);
            for (int i = 0; i < totalVector; i++) {
                limpiarCadenaDeEspacios(0, temporal.GetNodo(i)->dato);
                limpiarCadenaDeEspaciosFinales(temporal.GetNodo(i)->dato);
                insert.listaColumnas.insertarInsert("", temporal.GetNodo(i)->dato);//Agregando la Columna
            } cout<<"";
        } cout<<"";
        temporal.~ListaCadena();
        /* Tercera Parte */
        realizarTerceraParte(tercero, insert, mc);
    } cout<<"";
}

void ManejadorQuery::realizarTerceraParte(string terceraParte, Insert &it, ManejadorCadenas manejador){
    ListaCadena Tempo;
    int totalVector;
    ListaCadena temp = ListaCadena();
    //Tercera Parte
    manejador.split(terceraParte, *")", Tempo, totalVector);
    insertarALista(totalVector, temp, Tempo);
    if (totalVector > 0) {
        manejador.split(temp.GetNodo(0)->dato, *",", Tempo, totalVector);
        insertarALista(totalVector, temp, Tempo);
        if (totalVector > it.listaColumnas.size()) {
            it.listaColumnas.~ListaCadena();
            cout<<"\n ERROR: Lo siento error en la sintaxis aun falta una columna, para poder agregarle los valores. \n Vuelve a verficar tu entrada."<<endl<<endl;
        } else {
            for (int i = 0; i < totalVector; i++) {
                limpiarCadenaDeEspacios(0, temp.GetNodo(i)->dato);
                limpiarCadenaDeEspaciosFinales(temp.GetNodo(i)->dato);
                it.listaColumnas.GetNodo(i)->dato = temp.GetNodo(i)->dato;//Agregando los Valores
            } cout<<"";
        } cout<<"";
        temp.~ListaCadena();
    } cout<<"";
}


void ManejadorQuery::insertarALista(int size, ListaCadena &lista, ListaCadena &insertar){
    lista.~ListaCadena();
    for (int i = 0; i < size; i++) {
        if (insertar.GetNodo(i)->dato.compare(" ") > 0) {
            lista.insertar(insertar.GetNodo(i)->dato, 0);
        } cout<<"";
    } cout<<"";
}

void ManejadorQuery::select(string querySelect, ManejadorCadenas mc, Select &seleccionar) {
    ListaCadena tempLista = ListaCadena();
    ListaCadena TempBuff;
    int totalVector;
    //Primer Parte Separando FROM
    mc.split(querySelect, *"FROM", TempBuff, totalVector);
    insertarALista(totalVector, tempLista, TempBuff);
    if (totalVector > 0) {
        string parteUno = tempLista.GetNodo(0)->dato;
        string parteDos = tempLista.GetNodo(1)->dato;
        //Parte dos Espacios
        mc.split(parteUno, *" ", TempBuff, totalVector);
        insertarALista(totalVector, tempLista, TempBuff);
        //Si seleccionar todos y unicamente sin condicionales
        if (totalVector == 3) {
            if (tempLista.GetNodo(1)->dato == "*") {
                seleccionar.SetTodosCampos(true);
            } else{
                seleccionar.SetTodosCampos(false);
                limpiarCadenaDeEspacios(0, tempLista.GetNodo(1)->dato);
                limpiarCadenaDeEspaciosFinales(tempLista.GetNodo(1)->dato);
                seleccionar.listaColumnas.insertar(tempLista.GetNodo(1)->dato, 0);
            } cout<<"";
        } else {
            //Insertando Campos 
            seleccionar.SetTodosCampos(false);
            limpiarCadenaDeEspacios(6, parteUno);
            mc.split(parteUno, *",", TempBuff, totalVector);
            insertarALista(totalVector, tempLista, TempBuff);
            for (int i = 0; i < totalVector; i++) {
                limpiarCadenaDeEspacios(0, tempLista.GetNodo(i)->dato);
                limpiarCadenaDeEspaciosFinales(tempLista.GetNodo(i)->dato);
                seleccionar.listaColumnas.insertar(tempLista.GetNodo(i)->dato, 0);
            } cout<<"";
        } cout<<"";
        //Parte Dos
        mc.split(parteDos, *" ", TempBuff, totalVector);
        insertarALista(totalVector, tempLista, TempBuff);
        //Si viene sin condicionales
        if (totalVector == 2) {
            seleccionar.SetSinCondicional(true);
            remplazar(tempLista.GetNodo(1)->dato, ';', ' ');
            limpiarCadenaDeEspacios(0, tempLista.GetNodo(1)->dato);
            limpiarCadenaDeEspaciosFinales(tempLista.GetNodo(1)->dato);
            seleccionar.SetNombreTabla(tempLista.GetNodo(1)->dato);
        } else {
            //Con condicionales
            seleccionar.SetSinCondicional(false);
            limpiarCadenaDeEspacios(0, tempLista.GetNodo(1)->dato);
            limpiarCadenaDeEspaciosFinales(tempLista.GetNodo(1)->dato);
            seleccionar.SetNombreTabla(tempLista.GetNodo(1)->dato);
            limpiarCadenaDeEspacios(0, tempLista.GetNodo(3)->dato);
            limpiarCadenaDeEspaciosFinales(tempLista.GetNodo(3)->dato);
            seleccionar.SetColumnaCodicion(tempLista.GetNodo(3)->dato);
            limpiarCadenaDeEspacios(0, tempLista.GetNodo(4)->dato);
            limpiarCadenaDeEspaciosFinales(tempLista.GetNodo(4)->dato);
            seleccionar.SetCondicion(condicion(tempLista.GetNodo(4)->dato));
            remplazar(tempLista.GetNodo(5)->dato, ';', ' ');
            limpiarCadenaDeEspacios(0, tempLista.GetNodo(5)->dato);
            limpiarCadenaDeEspaciosFinales(tempLista.GetNodo(5)->dato);
            seleccionar.SetCondicional(tempLista.GetNodo(5)->dato);
        } cout<<"";
        TempBuff.~ListaCadena();
    } cout<<"";
}

Create ManejadorQuery::create(string queryCreate, ManejadorCadenas mc){
    Create crear = Create();
    ListaCadena listaValores = ListaCadena();
    ListaCadena listaAux = ListaCadena();
    ListaCadena TempBuff;
    int totalVector;
    //Primer Parte
    mc.split(queryCreate, *"(", TempBuff, totalVector);
    insertarALista(totalVector, listaValores, TempBuff);
    if (totalVector > 0) {
        string parteUno = listaValores.GetNodo(0)->dato;
        string parteDos = listaValores.GetNodo(1)->dato;
        mc.split(parteUno, *" ", TempBuff, totalVector);
        insertarALista(totalVector, listaValores, TempBuff);
        //Segunda Parte
        if (totalVector > 1) {
            limpiarCadenaDeEspacios(0, listaValores.GetNodo(2)->dato);
            limpiarCadenaDeEspaciosFinales(listaValores.GetNodo(2)->dato);  
            crear.SetNombreTabla(listaValores.GetNodo(2)->dato);
            //Tercera Parte
            mc.split(parteDos, *",", TempBuff, totalVector);
            insertarALista(totalVector, listaValores, TempBuff);
            for (int i = 0; i < totalVector; i++) {
                int aux;
                mc.split(listaValores.GetNodo(i)->dato, *" ", TempBuff, aux);
                insertarALista(aux, listaAux, TempBuff);
                limpiarCadenaDeEspacios(0, listaAux.GetNodo(0)->dato);
                limpiarCadenaDeEspacios(0, listaAux.GetNodo(1)->dato);
                crear.lista.insertar(listaAux.GetNodo(0)->dato, tipoDato(listaAux.GetNodo(1)->dato));
            } cout<<"";
            TempBuff.~ListaCadena();
            cout<<"";
        } cout<<"";
        listaValores.~ListaCadena();
    } cout<<"";
    return crear;
}

void ManejadorQuery::limpiarCadenaDeEspacios(int indiceIncial, string &cadena){
    for (int i = indiceIncial; i < cadena.length(); i++) {
        if (cadena[i] != ' ') {
            cadena = cadena.substr(i, (cadena.length()));
            break;
        } cout<<"";
    } cout<<"";
}

void ManejadorQuery::limpiarCadenaDeEspaciosFinales(string &cadena){
    for (int i = (cadena.length()-1); i > -1; i--) {
        if (cadena[i] != ' ') {
            cadena = cadena.substr(0, (i+1));
            break;
        } cout<<"";
    } cout<<"";
}

int ManejadorQuery::tipoDato(string dato) {
    remplazar(dato, ')', ' ');
    remplazar(dato, ';', ' ');
    if (dato == "String" || dato == "string  " || dato == "String  " || dato == "string  ") {
        return 1;
    } else if (dato == "Char" || dato == "char" || dato == "Char  " || dato == "char  ") {
        return 2;
    } else if (dato == "Integer" || dato == "integer" || dato == "int" || dato == "Int" || dato == "Integer  " || dato == "integer  " || dato == "int  " || dato == "Int  ")  {
        return 3;
    } else if (dato == "Double" || dato == "double" || dato == "Double  " || dato == "double  ") {
        return 4;
    }
}

int ManejadorQuery::condicion(string cadena){
    if (cadena == "=") {
        return 1;
    } else if (cadena == "<") {
        return 2;
    } else if (cadena == ">") {
        return 3;
    } else if (cadena == "<=") {
        return 4;
    } else if (cadena == ">=") {
        return 5;
    } else if (cadena == "!=") {
        return 6;
    } else {
        return 0;
    }
}