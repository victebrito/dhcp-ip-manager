
#ifndef func_H_
#define func_H_


#include "LISTA.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



void showMenu();

int copiaString(char *chegada, char *saida, int tamanho);

int comparaValido(char *s);      

int leDia(char *s);   

int leMes(char *s); 

int leAno(int mes);

int leRede(char *s);

int leIp(char *s);    

int atualizaIP(Apontador L,int rede,int ip,int ano,int mes,int dia);

void listaInativos(Apontador L);



#endif