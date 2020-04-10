Proyecto_DB: main.o Arbol.o Create.o Insert.o ListaCadena.o ListaColumnas.o ListaDeDB.o ListaHash.o ListaTablas.o ManejadorCadenas.o ManejadorHash.o ManejadorQuery.o Select.o
	g++ main.o Arbol.o Create.o Insert.o ListaCadena.o ListaColumnas.o ListaDeDB.o ListaHash.o ListaTablas.o ManejadorCadenas.o ManejadorHash.o ManejadorQuery.o Select.o -o Proyecto_DB 
	./Proyecto_DB 

main.o: main.cpp
	g++ -c main.cpp

Arbol.o: Arbol.cpp Arbol.h
	g++ -c Arbol.cpp

Create.o: Create.cpp Create.h
	g++ -c Create.cpp

Insert.o: Insert.cpp Insert.h
	g++ -c Insert.cpp

ListaCadena.o: ListaCadena.cpp ListaCadena.h
	g++ -c ListaCadena.cpp

ListaColumnas.o: ListaColumnas.cpp ListaColumnas.h
	g++ -c ListaColumnas.cpp

ListaDeDB.o: ListaDeDB.cpp ListaDeDB.h
	g++ -c ListaDeDB.cpp

ListaHash.o: ListaHash.cpp ListaHash.h
	g++ -c ListaHash.cpp

ListaTablas.o: ListaTablas.cpp ListaTablas.h
	g++ -c ListaTablas.cpp

ManejadorCadenas.o: ManejadorCadenas.cpp ManejadorCadenas.h
	g++ -c ManejadorCadenas.cpp

ManejadorHash.o: ManejadorHash.cpp ManejadorHash.h
	g++ -c ManejadorHash.cpp

ManejadorQuery.o: ManejadorQuery.cpp ManejadorQuery.h
	g++ -c ManejadorQuery.cpp

Select.o: Select.cpp Select.h
	g++ -c Select.cpp

clear: 
	rm -rf *o Proyecto_DB
