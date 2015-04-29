#Definition des cibles particulieres
.PHONY : clean, mrproper

#Desactivation des règles implicites du Makefile
.SUFFIXES :

#Option de compilation
CFLAGS = -Wall -std=gnu++0x -lboost_regex -lmysqlcppconn -lmysqlclient

#Suppression des fichiers objets temporaires
CLEAN = rm -rf *.o

#Fichier Objet
OBJ_FILES = main.o H1.o Meta.o Link.o ListLink.o Title.o DbaLink.o

all : $(OBJ_FILES)
	g++ $(OBJ_FILES) -o crawler $(CFLAGS) && $(CLEAN)

main.o : main.cpp
	g++ -c main.cpp -o main.o $(CFLAGS)

H1.o : ModelClasse/H1.cpp
	g++ -c ModelClasse/H1.cpp -o H1.o $(CFLAGS)

Meta.o : ModelClasse/Meta.cpp
	g++ -c ModelClasse/Meta.cpp -o Meta.o $(CFLAGS)

Title.o : ModelClasse/Title.cpp
	g++ -c ModelClasse/Title.cpp -o Title.o $(CFLAGS)

Link.o : ModelClasse/Link.cpp
	g++ -c ModelClasse/Link.cpp -o Link.o $(CFLAGS)

DbaLink.o : Dba/DbaLink.cpp
	g++ -c Dba/DbaLink.cpp -o DbaLink.o $(CFLAGS)

ListLink.o : ModelClasse/ListLink.cpp
	g++ -c ModelClasse/ListLink.cpp -o ListLink.o $(CFLAGS)




