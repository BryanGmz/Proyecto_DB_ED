/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Arbol.h
 * Author: bryan
 *
 * Created on 4 de abril de 2020, 09:33 PM
 */

#include <cstdlib>
#include <iostream>
#ifndef ARBOL_H
#define ARBOL_H

using namespace std;

typedef struct NodoHoja{
    int dato;//El espacio donde se guardara el número solicitado en el arbol 
    int fe;//Factor de equilibrio
    int alturaIzquierdo;//Altura del lado izquiero
    int alturaDerecho;//Altura del lado derecho
    
    struct NodoHoja* izquierdo;//Nodo Hoja Izquierdo
    struct NodoHoja* derecho;//Nodo Hoja Derecho
    struct NodoHoja* padre;//Nodo Padre
    
    string valor;//Valor de la hoja
    string columna;//Columna donde se encuentra el valor
} NodoHoja;


class Arbol {
public:
    Arbol();
    Arbol(const Arbol& orig);
    virtual ~Arbol();
    bool ingresarDatosHoja(string, string, int);//Nueva hoja string
    void insertarHoja(NodoHoja*, NodoHoja*, NodoHoja*);
    void equilibrar(NodoHoja *);
    void rotarDD(NodoHoja *, NodoHoja *);
    void rotarDI(NodoHoja *, NodoHoja *);
    void rotarII(NodoHoja *, NodoHoja *);
    void rotarID(NodoHoja *, NodoHoja *);
    void agregarAtributosHoja(NodoHoja *&, string, string, int);
    bool comprobarExistencia(NodoHoja*, int);
    int calcularAltura(NodoHoja*);
    void postorden(NodoHoja *);
    void inorden(NodoHoja *);
    void preorden(NodoHoja *);
    void verArbol(NodoHoja*, int);
    bool buscarHoja(NodoHoja *, int);
    int getCantidadDatosArbol() const;
    void setCantidadDatosArbol(int cantidadDatosArbol);
    NodoHoja* getRaiz() const;
    bool digito(string);
    bool decimal(string);
    int tipoDato(string);
    void setRaiz(NodoHoja* raiz);
    int charANumero(char);
    bool validarCondicion(string, int, string, int);
    string seleccionar(NodoHoja *, string, bool, int);
    //Retorna la lista seleccionada, la cadena de la condicional, bandera si viene con condicional, tiṕ de dato para realizar la comparacion
    
private:
    int cantidadDatosArbol;
    NodoHoja* raiz;//Este es el Nodo Raiz
};

#endif /* ARBOL_H */

