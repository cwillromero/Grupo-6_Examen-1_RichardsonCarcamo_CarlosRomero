#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <vector>
using namespace std;

#ifndef SNAKE_H
#define SNAKE_H

struct snakepart {
    int x, y;
    snakepart(int col, int row);
    snakepart();
};

class snakeclass {
    int puntos, velocidad;
    //static const int anchuraMaxima = 10;//Tamaño del tablero
    int anchuraMaxima;
    //static const int alturaMaxima = 10;//tamaño del tablero
    int alturaMaxima;
    char direction, cuerpoSerpiente, bordeTablero, comidaSerpiente;
    bool get;
    snakepart comida;
    vector<snakepart> snake;

    void meterComida();
    bool choqueSerpiente();
    void moverSerpiente();

    public:
        snakeclass();
        ~snakeclass();
        void comenzarJuego();
};

#endif
