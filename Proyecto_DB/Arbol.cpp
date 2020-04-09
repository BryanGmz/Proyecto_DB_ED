/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Arbol.cpp
 * Author: bryan
 * 
 * Created on 4 de abril de 2020, 09:33 PM
 */

#include "Arbol.h"
#include <sstream>

Arbol::Arbol() {
    this->cantidadDatosArbol = 0;
    this->raiz = NULL;
}

Arbol::Arbol(const Arbol& orig) {
}

Arbol::~Arbol() {
    while (raiz != NULL) {
        eliminarHoja(raiz);
    }
}

int Arbol::getCantidadDatosArbol() const {
    return cantidadDatosArbol;
}

void Arbol::setCantidadDatosArbol(int cantidadDatosArbol) {
    this->cantidadDatosArbol = cantidadDatosArbol;
}

NodoHoja* Arbol::getRaiz() const {
    return raiz;
}

void Arbol::setRaiz(NodoHoja* raiz) {
    this->raiz = raiz;
}

//Valor de la hoja 
//Columna del valor
//Dato es con el que se guardara en el arbol AVL
bool Arbol::ingresarDatosHoja(string valor, string columna, int dato) {
    NodoHoja* recorrer = raiz;//Nodo a recorrer 
    NodoHoja* nuevaHoja;
    NodoHoja* padreAnterior;//Padre anterior
    agregarAtributosHoja(nuevaHoja, valor, columna, dato);//Agrega los atributos a la hoja
    if (!comprobarExistencia(recorrer, nuevaHoja->dato)) {
        padreAnterior = raiz;
        insertarHoja(recorrer, nuevaHoja, padreAnterior);
        return true;//Significa que a sido ingresado con exito
    } else {
        return false;//Significa que hay una colision retorna false
    }
}


void Arbol::insertarHoja(NodoHoja *recorrer, NodoHoja* nuevaHoja, NodoHoja *PadreAnterior) {
    if (raiz == NULL) {//Significa que es la primer hoja en el arbol
        raiz = nuevaHoja;
        raiz->padre = NULL;
        cantidadDatosArbol++;
    } else {
        if (nuevaHoja->dato < recorrer->dato) {//Signigica que se agregara en el lado izquierdo del que se esta recorriendo
            if (recorrer->izquierdo != NULL) {//Significa que el nodo que se esta recorriendo tiene un hijo en el lado izquierdo
                PadreAnterior = recorrer->izquierdo;//Agrega a su padre al nodo que se esta reccoriendo
                insertarHoja(recorrer->izquierdo, nuevaHoja, PadreAnterior);//Se llama de nuevo hasta encontrar el sitio de la hoja
                calcularAltura(recorrer);
                equilibrar(recorrer);
            } else {//Siginifica que el nodo izquierdo no tiene hoja
                recorrer->izquierdo = nuevaHoja;
                nuevaHoja->padre = PadreAnterior;
                cantidadDatosArbol++;
                return;
            }
        } else if(nuevaHoja->dato > recorrer->dato) {//Signigica que se agregara en el lado derecho del que se esta recorriendo
            if (recorrer->derecho != NULL) {//Significa que el nodo que se esta recorriendo tiene un hijo en el lado derecho
                PadreAnterior = recorrer->derecho;//Apuntara al nodo derecho como el padre
                insertarHoja(recorrer->derecho, nuevaHoja, PadreAnterior);
                calcularAltura(recorrer);
                equilibrar(recorrer);
            } else {//Siginifica que el nodo derecho no tiene hoja
                recorrer->derecho = nuevaHoja;
                nuevaHoja->padre = PadreAnterior;
                cantidadDatosArbol++;
                return;
            }
        }
    }
}

void Arbol::equilibrar(NodoHoja *recorrer) {
    if (recorrer != NULL) {
        if ((recorrer->fe == 2) || (recorrer->fe == -2))  {//Significa que es necesario equilibrar el arbol
            cout<<"Es necesario equilibrar el arbol"<<endl;
            NodoHoja *PadreAnterior = recorrer;
            NodoHoja *hijo = PadreAnterior->derecho;//Comprobando del lado derecho
            if ((PadreAnterior->fe > 1) && (hijo->fe > 0)) {//Comprobar si se necesita Rotacion Simple a la izquierda
                cout<<"Rotacion Simple a la Izquierda."<<endl;
                cout<<" Padre: "<<PadreAnterior->dato<<" Hijo: "<<hijo->dato<<endl;
                rotarDD(PadreAnterior, hijo); 
                return;
            } else if((PadreAnterior->fe > 1) && (hijo->fe < 0)){//Comprobar si se necesita Rotacion Derecha, Izquierda 
                cout<<"Rotacion derecha izquierda."<<endl;
                cout<<" Padre: "<<PadreAnterior->dato<<" Hijo: "<<hijo->dato<<endl;
                rotarDI(PadreAnterior, hijo);
                return;
            } else {//Inciar comprobacion de equilibrio del lado izquierdo
                PadreAnterior = recorrer;
                hijo = PadreAnterior->izquierdo;//Comprobar del lado izquierdo
                if ((PadreAnterior->fe < -1) && (hijo->fe < 0)) {//Comprobar si necesita Rotacion Simple a la Derecha
                    cout<<"Rotacion Simple a la Derecha."<<endl;
                    cout<<" Padre: "<<PadreAnterior->dato<<" Hijo: "<<hijo->dato<<endl;
                    rotarII(PadreAnterior, hijo);
                    return;
                } else if((PadreAnterior->fe < -1) && (hijo->fe > 0)) {//Comprobar si necesita Rotacion Izquierda Derecha
                    cout<<"Rotacion izquierda derecha."<<endl;
                    cout<<" Padre: "<<PadreAnterior->dato<<" Hijo: "<<hijo->dato<<endl;
                    rotarID(PadreAnterior, hijo);
                    return;
                }
            }
        }
    }
}

//Rotar Doblemente a la Derecha
void Arbol::rotarDD(NodoHoja *padreAnterior, NodoHoja *hijo){
    if (padreAnterior == raiz) {//Se modificara la raiz
        raiz = hijo;
        NodoHoja *aux = hijo->izquierdo;
        hijo->izquierdo = padreAnterior;//El hijo del lado izquierdo apuntara al padre
        padreAnterior->padre = hijo;//El padre apuntara al hijo
        padreAnterior->derecho = aux;//El padre apuntara a tierra
        if (padreAnterior->derecho != NULL) {
            padreAnterior->derecho->padre = padreAnterior;
        }
        hijo->padre = NULL;//Como ahora el hijo es la raiz su padre apuntara a tierra
    } else {
        NodoHoja *abuelo = padreAnterior->padre;
        abuelo->derecho = padreAnterior->derecho;//El padre del padre apuntara ahora al lado derecho del padre
        hijo->padre = abuelo;//El padre del hijo apuntara al padre del padre
        padreAnterior->derecho = hijo->izquierdo;
        if (padreAnterior->derecho != NULL) {
            padreAnterior->derecho->padre = padreAnterior;//Como ahora el padre apuntara a tierra
        }
        hijo->izquierdo = padreAnterior;//La hoja izquierda apuntara ahora al padre anterior
        padreAnterior->padre = hijo;//El padre anterior apuntara ahora al hijo
    }
}

//Rotar Doblemente a la Izquierda
void Arbol::rotarII(NodoHoja *padreAnterior, NodoHoja *hijo){
    if (padreAnterior == raiz) {//Se modificara la raiz
        raiz = hijo;
        NodoHoja *aux = hijo->derecho;
        hijo->derecho = padreAnterior;//El hijo del lado derecho debe de apuntar al padre anterior
        padreAnterior->padre = hijo;//El padre debera de apuntar a su nuevo padre
        padreAnterior->izquierdo = aux;//El padre anterior en la hoja izquierda apuntadra ala hoja derecha
        if (padreAnterior->izquierdo != NULL) {
            padreAnterior->izquierdo->padre =  padreAnterior;
        }
        hijo->padre = NULL;//Como ahora el hijo es la raiz su padre apuntara a tierra
    } else {
        NodoHoja *abuelo = padreAnterior->padre;
        abuelo->izquierdo = padreAnterior->izquierdo;//El padre del padre apuntara ahora al lado izquierdo del padre anterior
        hijo->padre = abuelo;//El padre del hijo apuntara al padre del padre
        padreAnterior->izquierdo = hijo->derecho;//Como ahora el padre apuntara a tierra
        if (padreAnterior->izquierdo != NULL) {
            padreAnterior->izquierdo->padre = padreAnterior;
        }
        hijo->derecho = padreAnterior;//La hoja derecha del padre apuntara ahora al padre anterior
        padreAnterior->padre = hijo;//El padre anterior apuntara ahora al hijo
    }
}

//Rotar a la Derecha luego a la izquierda
void Arbol::rotarDI(NodoHoja *padreAnterior, NodoHoja *hijo){
    if (padreAnterior == raiz){//Se modificara la raiz
        NodoHoja *nieto = hijo->izquierdo;
        raiz = nieto; //Cambiar el apuntador de la raíz.
        nieto->padre = NULL; //Como el nieto ahora es la raiz apuntara a tierra
        nieto->derecho = hijo; //El nuevo padre debe apuntar a la hoja izquierda.		
        hijo->padre = nieto; //El hijo debe apuntar a su nuevo padre que ahora es el nieto.
        hijo->izquierdo = NULL; //La hoja izquierda apuntara a tierra porque ya no tendra hojas
        nieto->izquierdo = padreAnterior; //El nieto en su hoja izquierda apuntara al hijo.
        if(padreAnterior->izquierdo == NULL){
            padreAnterior->izquierdo = NULL; //El padre anterior debe apuntar ahora a tierra
	}
        padreAnterior->derecho = NULL; //el padre anterior en el lado derecho apuntara a tierra
        padreAnterior->padre = nieto; //Apuntar ahora al nieto
    } else {
        NodoHoja *abuelo = padreAnterior->padre;
        NodoHoja *nieto = hijo->izquierdo; 
        nieto->padre = abuelo; //Ahora el nieto debe de apuntar al abuelo
        abuelo->derecho = nieto;
        nieto->derecho = hijo; //El nieto debe apuntar al hijo izquierdo.		
        hijo->padre = nieto; //El hijo debe apuntar a su nuevo padre.
        hijo->izquierdo = NULL; //Apuntar a tierra al hijo izquierdo ya que bo tendra hojas			
	nieto->izquierdo = padreAnterior; //El nuevo padre debe apuntar al hoja derecha.
	if(padreAnterior->izquierdo == NULL){
            padreAnterior->izquierdo = NULL; //El padre anterior debe apuntar ahora a tierra
	}
        padreAnterior->derecho = NULL; //El padrea anterior debe apuntar ahora a tierra
        padreAnterior->padre = nieto; //El padre anterior debe de apuntar ahora al nieto
    }
}

//Rotar a la Izquierda luego a la derecha
void Arbol::rotarID(NodoHoja *padreAnterior, NodoHoja *hijo){
    if (padreAnterior == raiz){//Se modificara la raiz
        NodoHoja *nieto = hijo->derecho; 
        raiz = nieto; //Cambiar el apuntador de la raíz.
        nieto->padre = NULL; //Ahora como el nieto ahora es la raiz su padre debe de apuntar a tierra
        nieto->izquierdo = hijo; //El padre nuevo ahora debe de apuntar ala hoja izquierda.		
        hijo->padre = nieto; //La hoja debe realizar un cambio de apuntadores en padre.
        hijo->derecho = NULL;//Ahora como el hijo no tendara hojas del lado derecho debe de apuntar a tierra
        padreAnterior->izquierdo = NULL; //El padre anterior debe apuntar ahora a tierra
        nieto->derecho = padreAnterior; //El nieto en su hoja derecha debe de apuntar al padre anterior.
        if(padreAnterior->derecho == NULL){
            padreAnterior->derecho = NULL; //Como se realizaron cambio de apuntadores ahora el padre anterior en su hoja derecha debe de apuntar a tierra
	}
	padreAnterior->padre = nieto; //Se realiza el cambio de apuntadores en padre
    } else {
        NodoHoja *abuelo = padreAnterior->padre;
        NodoHoja *nieto = hijo->derecho; 
        nieto->padre = abuelo; //Como se realizara cambios se debe de apuntar al abuelo 
	abuelo->izquierdo = nieto; //El abuelo ahora debera de apuntar al nieto
        nieto->izquierdo = hijo; //El nieto debe de apuntar a la hoja izquierda.		
        hijo->padre = nieto; //El nodo hoja debera realizar cambios en el apuntador de padre.
        hijo->derecho = NULL; //Ahora el hijo como no tendra hijos de la hoja derecha debera de apuntar a tierra
        nieto->derecho = padreAnterior; //El nieto ahora debera de apuntar a la hoja derecha.
        padreAnterior->izquierdo = NULL; //Ahora el padre anterior en la hoja izquierda debera de apuntar a tierra
        if(padreAnterior->derecho == NULL){
            padreAnterior->derecho = NULL; //Asegurar que el padre anterior en su nodo hoja del lado derecho apunte a tierra
	}
        padreAnterior->padre=nieto; //Apuntar al nuevo padre ...
    }
}

//Calcula la altura de la rama
int Arbol::calcularAltura(NodoHoja* recorrer){
    if (recorrer == NULL) {//Si el nodo esta vacio entonces no tiene hijos
        return 0;
    } else {
        recorrer->alturaIzquierdo = calcularAltura(recorrer->izquierdo);//Calcula la altura de la hoja izquierda
        recorrer->alturaDerecho = calcularAltura(recorrer->derecho);//Calcula la altura de la hoja derecha
        recorrer->fe = (recorrer->alturaDerecho - recorrer->alturaIzquierdo);//Calcula el factor de equilibrio
        if (recorrer->alturaIzquierdo > recorrer->alturaDerecho) {
            return recorrer->alturaIzquierdo + 1;
        } else {
            return recorrer->alturaDerecho + 1;
        }
    }
}

void Arbol::agregarAtributosHoja(NodoHoja *&hojaNuevo, string valor, string columna, int dato){
    hojaNuevo = new NodoHoja();//Crea espacio en memoria
    hojaNuevo->dato = dato;
    hojaNuevo->valor = valor;
    hojaNuevo->columna = columna;
    hojaNuevo->izquierdo = NULL; //Punteros a Tierra
    hojaNuevo->derecho = NULL; //Punteros a Tierra
    hojaNuevo->alturaDerecho = 0; //Asigna el valor inicial de la altura derecha de la hoja
    hojaNuevo->alturaIzquierdo = 0; //Asigna el valor inicial de la altura izquierdo de la hoja
    hojaNuevo->fe = (hojaNuevo->alturaDerecho - hojaNuevo->alturaIzquierdo);//Calcula el valor de FE
}

//Funcion que comprueba la exitencia del dato o llave
//Devuelve true si existe el dato y false si no
bool Arbol::comprobarExistencia(NodoHoja* recorrer, int datoBuscando) {
    if (recorrer == NULL) {
        return false;
    } else {
        if (datoBuscando < recorrer->dato) { //Busca en el lado izquierdo de la hoja
            comprobarExistencia(recorrer->izquierdo, datoBuscando);
        } else if (datoBuscando > recorrer->dato) { //Busca en el lado dercho de la hoja
            comprobarExistencia(recorrer->derecho, datoBuscando);
        } else {
            return true;
        }
    }
}

string Arbol::graphivzArbol(NodoHoja* recorrer, int &contador, string sNodo) {
    if (recorrer != NULL) {
        string retornar = "";
        string nodo = "";
        string nodoAuxD= "";
        string nodoAuxI= "";
        if (recorrer == raiz) {
            retornar += "node" + static_cast<ostringstream*>(&(ostringstream() << contador))->str() +" [label = \"<f0> " + recorrer->valor + " \"];\n";
            nodo = "node" + static_cast<ostringstream*>(&(ostringstream() << contador))->str() + ":f0";
            contador++;
        } else {
            nodo = sNodo;
        }
        if (recorrer->derecho != NULL) {
            string nodoAux2 = "node" + static_cast<ostringstream*>(&(ostringstream() << contador))->str() +" [label = \"<f0> " + recorrer->derecho->valor + " \"];\n";
            retornar += nodoAux2 + "\n";
            nodoAuxD = "node" + static_cast<ostringstream*>(&(ostringstream() << contador))->str() + ":f0";
            retornar += nodo;
            retornar += " -> ";
            retornar += nodoAuxD;
            retornar += ";\n";
            contador++;
        } 
        if (recorrer->izquierdo != NULL) {
            string nodoAux2 = "node" + static_cast<ostringstream*>(&(ostringstream() << contador))->str() +" [label = \"<f0> " + recorrer->izquierdo->valor + " \"];\n";
            retornar += nodoAux2 + "\n";
            nodoAuxI = "node" + static_cast<ostringstream*>(&(ostringstream() << contador))->str() + ":f0";
            retornar += nodo;
            retornar += " -> ";
            retornar += nodoAuxI;
            retornar += ";\n";
            contador++;
        } 
        retornar += graphivzArbol(recorrer->izquierdo, contador, nodoAuxI);
        retornar += graphivzArbol(recorrer->derecho, contador, nodoAuxD);
        return retornar;
    } return "";
}

int Arbol::tipoDato(string cadena){
    if (digito(cadena)) {
        return 3;
    } else if  (decimal(cadena)) {
        return 4;
    } else {
        if (cadena.length() == 1) {
            return 2;
        } else {
            return 1;
        }
    }
}

bool Arbol::digito(string comprobar){
    for (int i = 0; i < comprobar.length(); i++) {
        if (!isdigit(comprobar[i])) {
            return false;
        }
    } return true;
}

bool Arbol::decimal(string comprobar){
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

string Arbol::seleccionar(NodoHoja *recorrer, string cadena, bool comprobacion, int tipoCondicion) {
    if (recorrer != NULL) {
        if (comprobacion) {
            string retornar = "";
            string aux = seleccionar(recorrer->izquierdo, cadena, true, tipoCondicion);
            if (aux[0] != '\0') {
                retornar += aux;
            }
            if (validarCondicion(cadena, tipoDato(cadena), recorrer->valor, tipoCondicion)) {
                retornar += recorrer->valor + "\n";
            }
            aux = seleccionar(recorrer->derecho,  cadena, true, tipoCondicion);
            if (aux[0] != '\0') {
                retornar += aux;
            }
            return retornar;
        } else {
            string retornar = "";
            string aux = seleccionar(recorrer->izquierdo, "", false, 0);
            if (aux[0] != '\0') {
                retornar += aux;
            }
            retornar += recorrer->valor + "\n";
            aux = seleccionar(recorrer->derecho, "", false, 0);
            if (aux[0] != '\0') {
                retornar += aux;
            }
            return retornar;
        }
    } else {
        return "\0";
    }
}

int Arbol::charANumero(char convertir){
    return convertir;
}

bool Arbol::validarCondicion(string cadena, int tipoDato, string comprobacion, int tipoCondicion) {
    switch (tipoCondicion) {
        case 1://Condicional Igual
            switch (tipoDato){
                case 1:
                    return (cadena.length() == comprobacion.length());
                case 2:
                    return (cadena[0] == comprobacion[0]);
                case 3:
                    return (atoi(cadena.c_str()) == atoi(comprobacion.c_str()));
                case 4:
                    return (atof(cadena.c_str()) == atof(comprobacion.c_str()));
            }
        case 2://Condicional menor
            switch (tipoDato){
                case 1:
                    return (comprobacion.length() < cadena.length());
                case 2:
                    return (charANumero(comprobacion[0]) < charANumero(cadena[0]));
                case 3:
                    return (atoi(comprobacion.c_str()) < atoi(cadena.c_str()));
                case 4:
                    return (atof(comprobacion.c_str()) < atof(cadena.c_str()));
            }
        case 3:
            switch (tipoDato){
                case 1:
                    return (comprobacion.length() > cadena.length());
                case 2:
                    return (charANumero(comprobacion[0]) > charANumero(cadena[0]));
                case 3:
                    return (atoi(comprobacion.c_str()) > atoi(cadena.c_str()));
                case 4:
                    return (atof(comprobacion.c_str()) > atof(cadena.c_str()));
            }
        case 4:
            switch (tipoDato){
                case 1:
                    return (comprobacion.length() <= cadena.length());
                case 2:
                    return (charANumero(comprobacion[0]) <= charANumero(cadena[0]));
                case 3:
                    return (atoi(comprobacion.c_str()) <= atoi(cadena.c_str()));
                case 4:
                    return (atof(comprobacion.c_str()) <= atof(cadena.c_str()));
            }
        case 5:
            switch (tipoDato){
                case 1:
                    return (comprobacion.length() >= cadena.length());
                case 2:
                    return (charANumero(comprobacion[0]) >= charANumero(cadena[0]));
                case 3:
                    return (atoi(comprobacion.c_str()) >= atoi(cadena.c_str()));
                case 4:
                    return (atof(comprobacion.c_str()) >= atof(cadena.c_str()));
            }
        case 6:
            switch (tipoDato){
                case 1:
                    return (comprobacion.length() != cadena.length());
                case 2:
                    return (charANumero(comprobacion[0]) != charANumero(cadena[0]));
                case 3:
                    return (atoi(comprobacion.c_str()) != atoi(cadena.c_str()));
                case 4:
                    return (atof(comprobacion.c_str()) != atof(cadena.c_str()));
            }
    } return false;
}

void Arbol::verArbol(NodoHoja *recorrer, int n){
    if(recorrer == NULL) {
        return; 
    }
    verArbol(recorrer->derecho, n + 1);
    for(int i=0; i<n; i++)
        cout<<"   ";
        cout<< recorrer->dato <<endl;
        verArbol(recorrer->izquierdo, n + 1);
}

bool Arbol::buscarHoja(NodoHoja *recorrer, int llave){
    if (recorrer == NULL){
        cout<<"Arbol Vacio o el nodo no existe"<<endl;
        return false;
    } else {
        if(llave < recorrer->dato){
            return buscarHoja(recorrer->izquierdo, llave);
        } else if (llave > recorrer->dato){
            return buscarHoja(recorrer->derecho, llave);
        } else {
            cout<<"Padre: "<<recorrer->padre->dato<<" Nodo buscado: "<<recorrer->dato<<endl;
            cout<<"\n\nDatos de Hoja: "<<endl;
            cout<<"Llave: "<<recorrer->dato<<endl;
            cout<<"Valor: "<<recorrer->valor<<endl;
            cout<<"Columna: "<<recorrer->columna<<endl;
            return true;
        }
    }
}

void Arbol::eliminarHoja(NodoHoja* recorrer) {
    if (recorrer != NULL) { 	
    	if (recorrer->dato == raiz->dato){
            raiz = NULL;
	} else {
            recorrer = NULL;
        }
    }
}
