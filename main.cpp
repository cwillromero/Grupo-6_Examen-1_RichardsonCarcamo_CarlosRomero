#include "snake.h"
#include <string>
#include <iostream>
#include <ncurses.h>

using namespace std;
string getstring();

int main()
{
	cout << "Ingrese su nobre: " << endl;
	string nombreJugador = "";
	cin >> nombreJugador;
	cout << "Bienvenido " << nombreJugador<< endl;

	
	//printw("Ingrese su nombre");
	//string nombreJugador = getstring();
	//char salto = getch();
	/*while(salto != "\n"){


	}*/

	//printw( "Saludos, " );
	//printw( getstring());
    snakeclass s;
    s.comenzarJuego();
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
