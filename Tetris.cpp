/*
*
*
*
*
*/
#include <iostream>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
/*& 0x1F --- & B1 1111*/
using namespace std;
/*
'1' il campo è vuoto
'1' il campo è occupato da un blocco statico
'2' il campo è occupato da un blocco mobile
'3' il campo è occupato dal perno

'1' empty field
'1' static tetrimino's block
'2' dinamic tetrimino's block
'3' tetrimino's pivvot
*/
bool collisione, gameover = false, creazione = true;
int a, n, f, score, tetris, type, rotaz = 0, x, y, tempRot, tot = 0;
char in;
char field [23] [12];
const char blocco [7 /*Blocco Block*/][4/*Orientamento Positioning*/][5 /*colonna Column*/][5 /*Riga Row*/]{
	///////////////////////////// BLOCCO 1 (T)
	{
		///////////////////////// POSIZIONI
		{
			{'0','0','0','0','0'},
			{'0','0','2','0','0'},
			{'0','2','3','2','0'},
			{'0','0','0','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','2','0','0'},
			{'0','0','3','2','0'},
			{'0','0','2','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','0','0','0'},
			{'0','2','3','2','0'},
			{'0','0','2','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','2','0','0'},
			{'0','2','3','0','0'},
			{'0','0','2','0','0'},
			{'0','0','0','0','0'}
		}
		////////////////////////////////////
	},
	////////////////////////////////////////
	///////////////////////////// BLOCCO 2 (I)
	{
		///////////////////////// POSIZIONI
		{
			{'0','0','2','0','0'},
			{'0','0','2','0','0'},
			{'0','0','3','0','0'},
			{'0','0','2','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','0','0','0'},
			{'0','2','3','2','2'},
			{'0','0','0','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','2','0','0'},
			{'0','0','2','0','0'},
			{'0','0','3','0','0'},
			{'0','0','2','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','0','0','0'},
			{'0','2','3','2','2'},
			{'0','0','0','0','0'},
			{'0','0','0','0','0'}
		}
		////////////////////////////////////
	},
	////////////////////////////////////////
	///////////////////////////// BLOCCO 3 (L)
	{
		///////////////////////// POSIZIONI
		{
			{'0','0','0','0','0'},
			{'0','0','2','0','0'},
			{'0','0','3','0','0'},
			{'0','0','2','2','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','0','0','0'},
			{'0','2','3','2','0'},
			{'0','2','0','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','2','2','0','0'},
			{'0','0','3','0','0'},
			{'0','0','2','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','0','2','0'},
			{'0','2','3','2','0'},
			{'0','0','0','0','0'},
			{'0','0','0','0','0'}
		}
		////////////////////////////////////
	},
	////////////////////////////////////////
	///////////////////////////// BLOCCO 4 (Lr)
	{
		///////////////////////// POSIZIONI
		{
			{'0','0','0','0','0'},
			{'0','0','2','0','0'},
			{'0','0','3','0','0'},
			{'0','2','2','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','2','0','0','0'},
			{'0','2','3','2','0'},
			{'0','0','0','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','2','2','0'},
			{'0','0','3','0','0'},
			{'0','0','2','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','0','0','0'},
			{'0','2','3','2','0'},
			{'0','0','0','2','0'},
			{'0','0','0','0','0'}
		}
		////////////////////////////////////
	},
	////////////////////////////////////////
	///////////////////////////// BLOCCO 5 (N)
	{
		///////////////////////// POSIZIONI
		{
			{'0','0','0','0','0'},
			{'0','0','0','2','0'},
			{'0','0','3','2','0'},
			{'0','0','2','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','0','0','0'},
			{'0','2','3','0','0'},
			{'0','0','2','2','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','0','2','0'},
			{'0','0','3','2','0'},
			{'0','0','2','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','0','0','0'},
			{'0','2','3','0','0'},
			{'0','0','2','2','0'},
			{'0','0','0','0','0'}
		}
		////////////////////////////////////
	},
	////////////////////////////////////////
	///////////////////////////// BLOCCO 6 (Nr)
	{
		///////////////////////// POSIZIONI
		{
			{'0','0','0','0','0'},
			{'0','0','2','0','0'},
			{'0','0','3','2','0'},
			{'0','0','0','2','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','0','0','0'},
			{'0','0','3','2','0'},
			{'0','2','2','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','2','0','0'},
			{'0','0','3','2','0'},
			{'0','0','0','2','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','0','0','0'},
			{'0','0','3','2','0'},
			{'0','2','2','0','0'},
			{'0','0','0','0','0'}
		}
		////////////////////////////////////
	},
	////////////////////////////////////////
	///////////////////////////// BLOCCO 7 (O)
	{
		///////////////////////// POSIZIONI
		{
			{'0','0','0','0','0'},
			{'0','0','2','2','0'},
			{'0','0','3','2','0'},
			{'0','0','0','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','2','2','0'},
			{'0','0','3','2','0'},
			{'0','0','0','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','2','2','0'},
			{'0','0','3','2','0'},
			{'0','0','0','0','0'},
			{'0','0','0','0','0'}
		},
		{
			{'0','0','0','0','0'},
			{'0','0','2','2','0'},
			{'0','0','3','2','0'},
			{'0','0','0','0','0'},
			{'0','0','0','0','0'}
		}
		////////////////////////////////////
	}
	////////////////////////////////////////

};




/////////////////////////////////////////////////////////////////////////
//////////////////////// INIZIO PROGRAMMA ///////////////////////////////
///////////////////////////// START /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
void select(){
	cout<<"Select language -- Selezione lingua:\n\nENG: e\n\nITA: i";
	in=getch();
}
void title(){			//TITOLO TITLE
	//system("color 60");
	system("cls");
	cout<<"   oooooooooo           o\n";
	cout<<"   oooooooooo           o\n";
	cout<<"   oo  oo  oo           o\n";
	cout<<"       oo               o\n";
	cout<<"       oo               o\n";
	cout<<"       oo               o                o\n";
	cout<<"       oo               o\n";
	cout<<"       oo      oooo     ooooo   o ooo    o    oooo\n";
	cout<<"       oo     o    o    o       oo   o   o   o\n";
	cout<<"       oo    o      o   o       o        o   o\n";
	cout<<"       oo    oooooooo   o       o        o   oooooo\n";
	cout<<"       oo    o          o       o        o        o\n";
	cout<<"      oooo    o          o      o        o   o    o\n";
	cout<<"      oooo     ooooo      ooo   o        o    oooo\n";
	cout<<"\n\n                              ASCII TETRIS\n\n                                 PREMI UN TASTO PER CONTINUARE\n\nComandi (control keys):\tW, A, S, D\n";
};
void start(){			//FUNZIONE CHE INIZIALIZZA STATI DI VARIABILI
	for(a=0; a<22; a++){
		for(n=1; n<11;n++){
			field[a][n]= '0';
		}
	}
	for(n=1; n<11; n++){
		field [22] [n] = '1';
	}
	for(a=0; a<22; a++){
		field[a][0]= '1';
		field[a][11]= '1';
	}
}
void frame(){			//FUNZIONE CHE STAMPA IL CAMPO DI GIOCO
/////////////////////////////////////////////
	system("cls");
	cout<<"\t\t\t\t------------\n";
	for(a = 0; a < 22; a++){
		cout<<"\t\t\t\t|";
		for(n = 1; n < 11;n++){
			if(field [a] [n]!='0'){
				if(field [a] [n] == '1')cout<<"O";
				else {
					cout<<"X";
					creazione = false;
				}
			}else{
				cout<<" ";
			}		
		}
		cout<<"|";
		if(a == 6)cout<<"\t"<<tot;
		cout<<"\n";
	}
	cout<<"\t\t\t\t------------"<<"\tPunteggio: "<<score<<"\n";
}
void linefull(){		//FUNZIONE CHE ELIMINA LINEE PIENE, RIALLINEA IL CAMPO E SEGNA IL PUNTEGGIO
	int point = 0;
	for(a=0;a<22;a++){
		if(field[a][1]=='1'&&field[a][2]=='1'&&field[a][3]=='1'&&field[a][4]=='1'&&field[a][5]=='1'&&field[a][6]=='1'&&field[a][7]=='1'&&field[a][8]=='1'&&field[a][9]=='1'&&field[a][10]=='1'){
			for(n=1;n<11;n++){
				field[a][n] = '0';
			}
			for(f=a;f>0;f--){
				for(n=1;n<11;n++){
					field[f][n] = field [f-1][n];
				}
			}
			point+=1;
		}
	}
	if (point == 4) tetris +=1;
	score += point;
}
void collision(){		//FUNZIONE CHE VERIFICA COLLISIONE TRA TETRAMINI E BLOCCHI FISSI
	collisione = false;
	for(a=0; a<23; a++){
		for(n=1; n<11; n++){
			if(field[a][n] == '3' || field[a][n] == '2'){
			if (field[a][n] == '3'){
				x=n;
				y=a;
			}
				if(field[a+1][n] == '1'){
					collisione = true;
				}
			}
		}	
	}
	if(collisione == true){
		for(a=y-2; a<y+3; a++){
			for(n=x-2; n<x+3; n++){
				if(field[a][n] == '2' || field[a][n] == '3')
					field[a][n] = '1';
			}
		}
		
		linefull();
	}
}
void gameOver(){		//FUNZIONE CHE STAMPA LA SCHERMATA DI GAME OVER
	while(in!='q'){
		system("cls");
		cout<<"\n\n\n\t\t\t\tGAME\n\n\t\t\t\tOVER\n\n\n\t\t\tHai totalizzato\t"<<score<<" punti(score)\n\t\t\teseguendo (with)\t"<<tetris<<" Tetris\n\n";
		cout<<"\n\n\n\t\t\t\tPREMERE (press) \"q\" PER USCIRE DAL GIOCO (to exit)";
		in=getch();
	}
}
void createObject(){	//FUNZIONE CHE crea un tetramino in caso di campo libero e richiama gameover(); in caso di camp occupato
	type = (rand()+tot) % 7;
	/*GENERA NUMERO CASUALE DA 0 A 6 PER GENERARE IL TETRAMINO*/
	for(a=0 ;a<5 ;a++){
		for(n=0 ;n<5 ; n++){
			if(field[a][n+3] == '1'){
				if(blocco [type /**/][rotaz][a][n] == '2'||'3'){
					gameover=true;
				}
			}
		}
	}
	for(a=0 ;a<5 ;a++){
		for(n=0 ;n<5 ; n++){
			field[a][n+3] = blocco [type][rotaz][a][n];
		}
	}
}

void left(){		//FUNZIONE CHE MUOVE IL BLOCCO VERSO SINISTRA
	collisione = false;
	for(a=0;a<22;a++){
		for(n=1;n<11;n++){
			if(field[a][n] == '2'||field[a][n] == '3'){
				if(field[a][n] == '3'){
					y=a;
					x=n;
				}
				if(field[a][n-1] == '1'){
					collisione = true;
				}
			}
		}
	}
	if(collisione == false){
		for(a=y-2;a<y+3;a++){
			for(n=x-2;n<x+3;n++){
				if(field[a][n] == '2'||field[a][n] == '3'){
					field[a][n-1] = field [a][n];
					field[a][n] = '0';
				}
			}
		}
	}
}
void right(){			//FUNZIONE CHE MUOVE IL BLOCCO VERSO DESTRA
	collisione = false;
	for(a=0;a<22;a++){
		for(n=1;n<11;n++){
			if(field[a][n] == '2'||field[a][n] == '3'){
				if(field[a][n] == '3'){
					y=a;
					x=n;
				}
				if(field[a][n+1] == '1'){
					collisione = true;
				}
			}
		}
	}
	if(collisione == false){
		for(a=y-2; a<y+3; a++){
			for(n=x+2;n>x-3;n--){
				if(field[a][n] == '2'||field[a][n] == '3'){
					field[a][n+1] = field [a][n];
					field[a][n] = '0';
				}
			}
		}
	}
}
void down(){			//FUNZIONE CHE MUOVE IL BLOCCO VERSO IL BASSO
	collisione = false;
	for(a=0;a<22;a++){
		for(n=1;n<11;n++){
			if(field[a][n] == '2'||field[a][n] == '3'){
				if(field[a][n] == '3'){
					y=a;
					x=n;
				}
				if(field[a+1][n] == '1'){
					collisione = true;
				}
			}
		}
	}
	if(collisione == false){
		for(a=y+2; a>y-3; a--){
			for(n=x-2; n<x+3; n++){
				if(field[a][n] == '2'||field[a][n] == '3'){
					field[a+1][n] = field [a][n];
					field[a][n] = '0';
				}
			}
		}
	}
	collision();
}
void rot(){			//FUNZIONE CHE RUOTA IL BLOCCO
	collisione = false;
	for(a=0; a<22; a++){
		for(n=1; n<11; n++){
			/*if(field[a][n] == '2'){
				field[a][n] = '0';
			}else */if(field[a][n] == '3'){
				y=a-2;
				x=n-2;
			}
		}
	}
	if(rotaz == 3) tempRot = 0;
	else tempRot = rotaz + 1;
	for(a=0 ;a<5 ;a++){
		for(n=0 ;n<5 ; n++){
			if(field[a+y][n+x]=='1'&&blocco [type][tempRot][a][n] == '2') collisione = true;
		}
	}
	/***************OK***********/
	if(collisione == false){
		rotaz = tempRot;
		for(a=0 ;a<5 ;a++){
			for(n=0 ;n<5 ; n++){
				if(field[a+y][n+x] == '2')
					field[a+y][n+x] = '0';
				if(field[a+y][n+x] == '0')
					field[a+y][n+x] = blocco [type][rotaz][a][n];
			}
		}
	}
}

void getIn(){
	if(in == 'a'){
		tot+=1;
		left();
	}else if(in == 'd'){
		tot+=1;
		right();
	}else if(in == 's'){
		tot+=1;
		down();
	}else if(in == 'w'){
		tot+=1;
		rot();
	}
	creazione = true;
}


main(){
	title();
	getch();/////////////////////////////////////
	start();
	/////////////////////////////////////////////
	createObject();
	frame();
	while(gameover == false){
		if(creazione == true){
			createObject();
		}
		in = (getch() | 0x20);
		getIn();
		frame();
		/////////////////////////////////////
	}
		gameOver();
		return 0;
	////
	/**PER TERMINARE PROGRAMMA SENZA GAME OVER**/
	////
}
