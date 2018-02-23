#include "snake.h"
#include <string>
#include <iostream>
#include <ncurses.h>

using namespace std;
string getstring();
//INiciar Juego
void comenzarJuego(snakeclass);

int main()
{	cout << "La serpiente se mueve con flechas "<<endl<<"Ingrese su nombre: " << endl;
	string nombreJugador = "";
	cin >> nombreJugador;
	cout << "Bienvenido " << nombreJugador<< endl;
	usleep(10);
	//comenzarJuego(serpiente);
	//printw("Ingrese su nombre");
	//string nombreJugador = getstring();
	//char salto = getch();
	/*while(salto != "\n"){


	}*/

	//printw( "Saludos, " );
	//printw( getstring());
    snakeclass serpiente;
    //move(50,50);
    //printw("Bienvenido a Snake");
    //getch();
    comenzarJuego(serpiente);
	endwin();
    return 0;
}


string getstring()
{
    std::string input;

   
    nocbreak();
    echo();

   
    int ch = getch();

    while ( ch != '\n' )
    {
        input.push_back( ch );
        ch = getch();
    }

   
    return input;
}

void comenzarJuego(snakeclass s){
    int alturaM, anchuraM;
    getmaxyx(stdscr, alturaM, anchuraM);
    while (true)
    {
        if (s.choqueSerpiente())
        {
            move(alturaM / 2, anchuraM / 2);
            printw("¡¡¡HAS PERDIDO!!!");
            break;
        }

        s.moverSerpiente();

        if (s.direction == 'q')
        {
            break;
        }

        usleep(s.velocidad);//tiempo de dormir uhzzzz
    }
}
