#include <ncurses.h>
#include <string>
using namespace std;
/*DEL EJEMPLO CON INPUT*/
void strat_ncurses(bool useRaw,bool usenoECho);
void printMenu(WINDOW * menu,string choices[],int size,int highlight);
int main(int argc,char** argv){
//Esto es un comentario
initscr();
noecho();
cbreak();

int yMax,xMax;
getmaxyx(stdscr,yMax,xMax);
WINDOW * menu=newwin(6,xMax-12,yMax-8,5);
box(menu,0,0);
refresh();
wrefresh(menu);
keypad(menu,true);
string opciones[5]={"1-","2-","3-","4-","5-"};
int subrayar=0;
int Resp;
while(true){
	for(int i=0;i<5;i++){
		if(i==subrayar){
			wattron(menu,A_REVERSE);
			mvwprintw(menu,i+1,1,opciones[i].c_str());
			wattroff(menu,A_REVERSE);
		}//fin del if
	}//fin del for.
	Resp=wgetch(menu);
	switch(Resp){
		case KEY_UP:{
			subrayar--;
			if(subrayar==-1){
				subrayar=0;
			}
			break;
			    }
		case KEY_DOWN:{
			subrayar++;
			if(subrayar==5){
				subrayar=4;
			}
			break;
			      }
		default:

			break;
	}//Fin del switch
	if(Resp==10){
		break;
	}

}//Fin del while
	printw("Tu eleccion fue: %s",opciones[subrayar].c_str());
getch();
endwin();
return 0;
}
