#ifndef LISTA_H_
#define LISTA_H_


typedef struct List_s *Apontador;

typedef struct List_s {
	int list16[256][3];
	int list19[256][3];
	int list20[256][3];

}Lista;


int setIP(Apontador L,int rede, int ip, int ano, int mes, int dia);

int getAno(Apontador L, int rede, int ip);

int getMes(Apontador L, int rede, int ip);

int getDia(Apontador L, int rede, int ip);

int gravaLista(Apontador L);

#endif