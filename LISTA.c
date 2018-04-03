
#include "LISTA.h"
#include <stdio.h>
#include <stdlib.h>

int setIP(Apontador L,int rede, int ip, int ano, int mes, int dia)
{
	if(ip>=0 && ip<256)
	{
		if(rede == 16)
		{
			L->list16[ip][0] = ano;
			L->list16[ip][1] = mes;
			L->list16[ip][2] = dia;
		}
		else if(rede == 19)
		{
		    L->list19[ip][0] = ano;
			L->list19[ip][1] = mes;
			L->list19[ip][2] = dia;
		}
		else if(rede == 20)
		{	
			L->list20[ip][0] = ano;
			L->list20[ip][1] = mes;
			L->list20[ip][2] = dia;
		}	
	    return(0);
	}
	else return(1);
}

int getAno(Apontador L, int rede, int ip)
{
		if(rede == 16)
		{
			return(L->list16[ip][0]);
		}
		else if(rede == 19)
		{
			return(L->list19[ip][0]);
		}
		else if(rede == 20)
		{	
			return(L->list20[ip][0]);
		}
}

int getMes(Apontador L, int rede, int ip)
{
		if(rede == 16)
		{
			return(L->list16[ip][1]);
		}
		else if(rede == 19)
		{
			return(L->list19[ip][1]);
		}
		else if(rede == 20)
		{	
			return(L->list20[ip][1]);
		}
}


int getDia(Apontador L, int rede, int ip)
{
		if(rede == 16)
		{
			return(L->list16[ip][2]);
		}
		else if(rede == 19)
		{
			return(L->list19[ip][2]);
		}
		else if(rede == 20)
		{	
			return(L->list20[ip][2]);
		}
}


int gravaLista(Apontador L)
{
	FILE *saida;
	saida = fopen ("ip.csv", "w");
	if (saida == NULL) {
       printf ("Houve um erro ao abrir o arquivo: ip.csv\n");
       return 1;
    }

    int i;
    for (i = 1; i < 256; ++i)                                             //16
    {
    	int rede, ano, mes, dia;
    	rede = 16;
    	ano = getAno(L, rede, i);
    	mes = getMes(L, rede, i);
    	dia = getDia(L, rede, i);
    	fprintf(saida, "%d,%d,%d,%d,%d\n", rede, i, ano, mes, dia);   
    }
    for (i = 1; i < 256; ++i)                                             //19
    {
    	int rede, ano, mes, dia;
    	rede = 19;
    	ano = getAno(L,rede, i);
    	mes = getMes(L,rede, i);
    	dia = getDia(L,rede, i);
    	fprintf(saida, "%d,%d,%d,%d,%d\n", rede, i, ano, mes, dia);   
    }
    for (i = 1; i < 256; ++i)                                             //20
    {
    	int rede, ano, mes, dia;
    	rede = 20;
    	ano = getAno(L,rede, i);
    	mes = getMes(L,rede, i);
    	dia = getDia(L,rede, i);
    	fprintf(saida, "%d,%d,%d,%d,%d\n", rede, i, ano, mes, dia);     
    }

    fclose(saida);

}
