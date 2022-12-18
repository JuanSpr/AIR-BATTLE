/*Jorge Ortega(2022119007) 
Juan Pardo (2022119015)  
Luis Brito(2022119035)*/
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <list>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA  77
#define ABAJO 80
#define ESPACIO 32
using namespace std;	
int i;
void gotoxy(int x,int y);
void cuadro();
void letras();
void borrarh(int x1,int y1);
void cursoroff();
void fin();
class NAVE{
	int x1,y1,salud, vidas;
	public:
		NAVE(int _x,int _y, int _salud, int _vidas): x1(_x), y1(_y), salud(_salud), vidas(_vidas){}
		void COR(){salud--;}
		int X(){return x1;}
		int Y(){return y1;}
		void dibujarh();
		void borrarh();
		void mover();
		void pintars();
		void morir();
		int vid(){return vidas;}
};
void NAVE :: dibujarh(){
	gotoxy(x1,y1);cout<<"   -----|-----";
	gotoxy(x1,y1+1);cout<<"*>=====[_]L)";
	gotoxy(x1,y1+2);cout<<"      -'-`-";
}
void NAVE::borrarh(){
	gotoxy(x1,y1);cout<<"              ";
	gotoxy(x1,y1+1);cout<<"            ";
	gotoxy(x1,y1+2);cout<<"             ";	
}
void NAVE::mover(){
	if(kbhit()){
		char tecla=getch();
		borrarh();
		if(tecla==IZQUIERDA && x1>24)x1-=2;
		if(tecla==DERECHA && x1<125)x1+=2;
		if(tecla==ARRIBA && y1>4)y1--;
		if(tecla==ABAJO && y1<30)y1++;
		if (tecla=='e')salud--;
		dibujarh();
		pintars();
	}
}
void NAVE::pintars(){
	gotoxy(100,2);cout<<"Vidas "<<vidas;
	gotoxy(130,2);cout<<"Salud";
	gotoxy(136,2);cout<<"    		";
	for(int i=0; i<salud ;i++ ){
		gotoxy(136+i,2);cout<<char(3);
	}
}
void NAVE::morir(){
	if(salud==0){
		borrarh();
		gotoxy(x1,y1);cout<<"   ****  ";
		gotoxy(x1,y1+1);cout<<"*********";
		gotoxy(x1,y1+1);cout<<" ***";
		Sleep(250);
		borrarh();
		gotoxy(x1,y1);cout<<"  * * *  ";
		gotoxy(x1,y1+1);cout<<"*  *** ";
		gotoxy(x1,y1+1);cout<<"*  * ";
		Sleep(250);
		borrarh();
		vidas--;
		salud=3;
		pintars();
		dibujarh();
	}
}

class OBJETIVO{
	int x2,y2;
	public:
		OBJETIVO(int _x2,int _y2):x2(_x2),y2(_y2){}
		void dibujar();
		void mover();	
		void choque(class NAVE &N);	
		int x(){return x2;}
		int y(){return y2;}
};
void OBJETIVO::dibujar(){
	gotoxy(x2,y2);cout<<char(186);
}
void OBJETIVO::mover(){
	gotoxy(x2,y2);cout<<" ";
	x2-=3;
	if (x2<23){
		y2=rand()%29+4;
		x2=139;
	}
	dibujar();
}
void OBJETIVO::choque(class NAVE &N){
	if(y2>=N.Y() && y2< N.Y()+3 && x2>=N.X() && x2<=N.X()+12){
		N.COR();
		N.borrarh();
		N.dibujarh();
		N.pintars();
		y2=rand()%29+4;
		x2=139;
	}
}

class BALA{
	int x3,y3;
	public:
		BALA(int _x3,int _y3):x3(_x3),y3(_y3){}
		void moverb();
		bool fuera();
		int x(){return x3;}
		int y(){return y3;}
};
void BALA::moverb(){
	gotoxy(x3,y3);cout<<" ";
		x3++;
		cout<<"=";
}
bool BALA::fuera(){
	if(x3==139){
		return true;
	}else{
		return false;
	}
}
int main(){
	char op='s';
	cursoroff();
	gotoxy(10,10);cout<<"Coloque pantalla completa y luego presione enter";
	getch();
	system("cls");
	cuadro();
	letras();
	getch();
	system("cls");
	cuadro();
	cursoroff();
	NAVE N(24,16,3,3);
	system("color 0A");
	N.dibujarh();
	N.pintars();
	list <OBJETIVO*> O;
	list <OBJETIVO*>::iterator ito;
	for(int i=0; i<10;i++){
		O.push_back(new OBJETIVO(118+rand()%21,rand()%29+4));
	}
	list<BALA*> B;
	list<BALA*>::iterator itb;
	bool game_over = false;
	int puntos=0;	
	while(!game_over){
		gotoxy(25,2);cout<<"Puntos: "<<puntos;
			if (kbhit()){
			char t=getch();
			if (t==ESPACIO){
				B.push_back(new BALA(N.X()+13,N.Y()+1));
			}
		}
		for(itb= B.begin(); itb != B.end();itb++){
			(*itb)->moverb();
			if((*itb)->fuera()){
				gotoxy((*itb)->x(),(*itb)->y());cout<<" ";
				delete (*itb);
				itb = B.erase(itb);
			}
		}
		for(ito= O.begin(); ito != O.end();ito++)	{
			(*ito)->mover();
			(*ito)->choque(N);
		}
		for(ito= O.begin(); ito != O.end();ito++){
			for(itb= B.begin(); itb != B.end();itb++){
				if((*ito)->y() == (*itb)->y() && ((*ito)->x()+1 == (*itb)->x() || (*ito)->x() == (*itb)->x())){
					gotoxy((*itb)->x(),(*itb)->y());cout<<"  ";
					delete(*itb);
					itb=B.erase(itb);
					
					O.push_back(new OBJETIVO(118+rand()%21,rand()%29+4));
					gotoxy((*ito)->x(),(*ito)->y());cout<<"  ";
					delete(*ito);
					ito=O.erase(ito);
					
					puntos+=5;
				}
			}
		}
		if(N.vid()==0){
			system("cls");
			cuadro();
			fin();
			
			game_over=true;
		}
		N.morir();
		N.mover();
		Sleep(30);	
	}
	getch();
	return 0;
}
void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }  
 void cursoroff(){
	HANDLE hCon;  
    hCon = GetStdHandle(STD_OUTPUT_HANDLE); 
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible= FALSE;
    SetConsoleCursorInfo(hCon,&cci);
}
void cuadro(){
	for(i=22;i<140;i++){
		gotoxy(i,3);cout<<char(205);
		gotoxy(i,33);cout<<char(205);
	}
	for(i=4;i<33;i++){
		gotoxy(22,i);cout<<char(186);
		gotoxy(140,i);cout<<char(186);
	}
	gotoxy(22,3);cout<<char(201);
	gotoxy(22,33);cout<<char(200);
	gotoxy(140,3);cout<<char(187);
	gotoxy(140,33);cout<<char(188);
}
void letras(){
	system("color 03");
	gotoxy(67,13);cout<<"   _     ___   ___ ";
	gotoxy(67,14);cout<<"  /_\\   |_ _| | _ \\";
	gotoxy(67,15);cout<<" / _ \\   | |  |   /";
	gotoxy(67,16);cout<<"/_/ \\_\\ |___| |_|_\\";                   ;
	gotoxy(63,17);cout<<"  ___          _     _     _     ";  
	gotoxy(63,18);cout<<" | _ )  __ _  | |_  | |_  | |  ___"; 
	gotoxy(63,19);cout<<" | _ \\ / _` | |  _| |  _| | | / -_)";
	gotoxy(63,20);cout<<" |___/ \\__,_|  \\__|  \\__| |_| \\___|";
	gotoxy(65,26);cout<<"Presione enter para continuar";
	gotoxy(54,28);cout<<"Controles: se mueve con las flechas del teclado";
	gotoxy(64,29);cout<<" Dispara con la tecla espaciadora";
	gotoxy(1,34);
}
void fin(){
	system("color 04");
	gotoxy(67,13);cout<<"  ___     _    __  __   ___ ";
	gotoxy(67,14);cout<<" / __|   /_\\  |  \\/  | | __|";
	gotoxy(67,15);cout<<"| (_ |  / _ \\ | |\\/| | | _| ";
	gotoxy(67,16);cout<<"\\___|  /_/ \\\\ |_|  |_| |___|";                   ;
	gotoxy(68,17);cout<<"  ___   __   __  ___   ___ ";  
	gotoxy(68,18);cout<<" / _ \\  \\ \\ / / | __| | _ \\"; 
	gotoxy(68,19);cout<<"| (_) |  \\ V /  | _|  |   /";
	gotoxy(68,20);cout<<" \\___/    \\_/   |___| |_|_\\";

}






