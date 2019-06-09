#include <iostream>

using namespace std;

//Estrutura
struct no
{
	int info;
	struct no *prox;	
};

typedef struct no *ptrNo;

//Escopo
void insere();
void removeFila();
void removePilha();
void removeElemento();
void exibe();
void listaVazia();


int main(){
	int op;
	do {
		cout << "1 -> Insere" << endl;
		cout << "2 -> Remove Fila" << endl;
		cout << "3 -> Remove Pilha" << endl;
		cout << "4 -> Remove Elemento Especifico" << endl;
		cout << "5 -> Exibe Lista" << endl;
		cout << "0 -> Sair" << endl;
		
		cin >> op;

		switch(op){
			case 1: insere();         break;
			case 2: removeFila();     break;
			case 3: removePilha();    break;
			case 4: removeElemento(); break;
			case 5: exibe();          break;
		}
	}while(op != 0);
}


//var local e att as funções