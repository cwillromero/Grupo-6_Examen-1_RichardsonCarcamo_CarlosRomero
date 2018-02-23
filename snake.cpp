#include "snake.h"
#include <ncurses.h>

snakepart::snakepart(int col, int row)
{
    x = col;
    y = row;
}


snakepart::snakepart()
{
    x = 0;
    y = 0;
}


snakeclass::snakeclass()
{
	//inicializa los elementos
    initscr();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    //anchuraMaxima = 10;
    //alturaMaxima = 10;
    getmaxyx(stdscr, alturaMaxima, anchuraMaxima);

    // valores de variables
    cuerpoSerpiente = 'x'; //cuerpo de la serpiente
    bordeTablero = (char) 222;//contorno del tablero
    comidaSerpiente = '*'; //caracter de la comida
    comida.x = 0;//poscicion x de la comida
    comida.y = 0;//poscicion y de la comida

    // Colocacioón de la serpiente
    for (int i = 0; i < 5; i++)
    {
        snake.push_back(snakepart(20 + i, 5));
    }

    puntos = 0;
    velocidad = 100000;//velocidad de la serpiente
    get = false;
    direction = 'l';//primera dirreción de la serpiente
    srand(time(0));
    meterComida();//metodo que ingresa la comida

    // Limite de al parte de arriba
    for (int i = 0; i < anchuraMaxima - 1; i++)
    {
        move(0, i);
        addch(bordeTablero);
    }

    // limite de la parte de abajo
    for (int i = 0; i < anchuraMaxima - 1; i++)
    {
        move(alturaMaxima - 2, i);
        addch(bordeTablero);
    }

    // Limite de la parte izquierda
    for (int i = 0; i < alturaMaxima - 1; i++)
    {
        move(i, 0);
        addch(bordeTablero);
    }

    // limite de la parte derecha
    for (int i = 0; i < alturaMaxima - 1; i++)
    {
        move(i, anchuraMaxima - 1);
        addch(bordeTablero);
    }

    // snake body
    for (int i = 0; i < snake.size(); i++)
    {
        move(snake[i].y, snake[i].x);
        addch(cuerpoSerpiente);
    }

    //Impresión del Puntuaje
    move(alturaMaxima - 1, 0);
    printw("%d", puntos);

    // Impresion de comida
    move(comida.y, comida.x);
    addch(comidaSerpiente);

    refresh();
}

snakeclass::~snakeclass()
{
    nodelay(stdscr, false);
    getch();
    endwin();
}

void snakeclass::meterComida()
{
    while (1)
    {	//posiciones random de la comida
        int tmpx = rand() % anchuraMaxima + 1;
        int tmpy = rand() % alturaMaxima + 1;

        // Validación al momento de poner la comida de la serpiente
        if (tmpx >= anchuraMaxima - 2 || tmpy >= alturaMaxima - 3)
        {
            continue;
        }

        // meter la comida de la serpiente
        comida.x = tmpx;
        comida.y = tmpy;

        break;
    }

    // imprimir la comida-- Si no la ve, no se la come
    move(comida.y, comida.x);
    addch(comidaSerpiente);
    refresh();
}

bool snakeclass::choqueSerpiente()
{
    // validación cuando la serpiente choca con los bordes
    if (snake[0].x == 0 || snake[0].x == anchuraMaxima - 1 || snake[0].y == 0 || snake[0].y == alturaMaxima - 2 )
    {
        return true;
    }

    // validación cuando la serpiente choca con ella misma :V
    for (int i = 2; i < snake.size(); i++)
    {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
        {
            return true;
        }
    }

    // validación cuando la serpiente se come un asterisco
    if (snake[0].x == comida.x && snake[0].y == comida.y)
    {
        get = true;
        meterComida(); //añade mas comida
        puntos += 1; //un asterisco, un punto
        move(alturaMaxima - 1, 0);
	printw("Pixeles Comidos: ");
	move(alturaMaxima - 1, -3);
        printw("%d", puntos);
	move(alturaMaxima - 1, -6);
	printw("   ");
	move(alturaMaxima - 1, -9);
	printw("Puntaje: ");
	move(alturaMaxima - 1, -12);
        printw("%d",(puntos*100));
        //printw("%d", alturaMaxima);//impresion de la altura
        //printw("%d", anchuraMaxima); //impresion del ancho

        if (puntos % 100 == 0)
        {
            velocidad -= 10000;
        }
    }
    else
    {
        get = false;
    }

    return false;
}

void snakeclass::moverSerpiente()
{
	//moviento de la serpiente
    int temp = getch();
    switch(temp)
    {
    	//izquierda
        case KEY_LEFT:
            if (direction != 'r')
            {
                direction = 'l';
            }
            break;
        //arriba
        case KEY_UP:
            if (direction != 'd')
            {
                direction = 'u';
            }
            break;
        //derecha
        case KEY_RIGHT:
            if (direction != 'l')
            {
                direction = 'r';
            }
            break;
        //abajo
        case KEY_DOWN:
            if (direction != 'u')
            {
                direction = 'd';
            }
            break;

        case KEY_BACKSPACE:
            direction = 'q';
            break;
    }

    if (!get)
    {
        move(snake[snake.size() - 1].y, snake[snake.size() - 1].x);
        addch(' ');//Cambia la cola el ultimo elemento de la serpiente
        //por un espacio, para darle un estilo de movimiento
        refresh();//refresca la pantalla
        snake.pop_back();//elimina el ultimo elemento del vector
    }

    if (direction == 'l')
    {
        snake.insert(snake.begin(), snakepart(snake[0].x - 1, snake[0].y));
    }
    else if (direction == 'r')
    {
        snake.insert(snake.begin(), snakepart(snake[0].x + 1, snake[0].y));
    }
    else if (direction == 'u')
    {
        snake.insert(snake.begin(), snakepart(snake[0].x, snake[0].y - 1));
    }
    else if (direction == 'd')
    {
        snake.insert(snake.begin(), snakepart(snake[0].x, snake[0].y + 1));
    }

    move(snake[0].y, snake[0].x);
    addch(cuerpoSerpiente);
    refresh();
}


