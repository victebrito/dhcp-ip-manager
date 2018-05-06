

#include "func.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(int argc, char *argv[])
{
	//////////////////////////////////////////////////////////
	//Menu
  if (argc > 1)
  {
  	if(strcmp(argv[1], "-h") == 0){
  		showMenu();
  		return(0);
  	}
  	if(strcmp(argv[1], "-H") == 0){
  		showMenu();
  		return(0);
  	}
  	if(strcmp(argv[1], "--help") == 0){
  		showMenu();
  		return(0);
  	}
  	if(strcmp(argv[1], "-HELP") == 0){
  		showMenu();
  		return(0);
  	}
    else
    {
      printf ("Argumento invalido.\n Tente a ajuda: -h ou --help\n");
      return(1);
    }
  }
	//////////////////////////////////////////////////////////
	//ENTRA ARQUIVOS - log

	FILE *fileip;
	fileip = fopen ("ip.csv", "r");
	if (fileip == NULL) {
       printf ("Houve um erro ao abrir o arquivo ip.csv.\n");
       return 1;
    }
    
    Lista ListaIP;
    int rede, ip, ano, mes, dia;
    while (!feof(fileip))
    {
    	rede = 0;
    	ip   = 0;
    	ano  = 0;
    	mes  = 0;
    	dia  = 0;
    	fscanf(fileip, "%d,%d,%d,%d,%d", &rede, &ip, &ano, &mes, &dia );
    	if (setIP( &ListaIP, rede, ip, ano, mes, dia) == 1)
    		printf("IP invalido\n");

    }
    fclose(fileip);

	//////////////////////////////////////////////////////////
	//ENTRA ARQUIVOS - servidor
	//argv[1] é nome do arquivo entry que contem o nome dos logs
  system("rm ip.csv");
  system("rm LogNames");
  int teste = system("find  /var/log/messages-* > LogNames");
  if (teste == -1)
  {
    printf ("Erro ao gerar nomes dos arquivos de log.\n 'find  /var/log/messages-* >> LogNames'\n");
    return 1;
  }

  FILE *entry;
  entry = fopen ("LogNames", "r");
  if (entry == NULL) {
     printf ("Houve um erro ao abrir o arquivo: %s\n", "LogNames");
    return 1;
  } 

  int numLinha = 0;
  //Só funciona até 100 arquivos de log
  char strNames[100][50];
  while (!feof(entry))
  { 
    fgets(strNames[numLinha], 50, entry);
    //retira o : de depois do nome
    strNames[numLinha][26] = '\0';
    //printf ("%s\n", strNames[numLinha]);
    numLinha++;
  }
  fclose(entry); 
  

  int j = 0;
  for( j=0; j<numLinha -1 ; j++)
  {

  	FILE *log;
  	//log = fopen (argv[1], "r");
    log = fopen (strNames[j], "r");
  	if (log == NULL) {
         printf ("Houve um erro ao abrir o arquivo: %s\n", strNames[j]);
         return 1;
      }

      char string[100];
      while (!feof(log))
      {
         fgets(string, 100, log);
         //Verifica se a linha é DHCPACK
         if(comparaValido(string) == 0)
         {
              int mes = leMes(string);
              int ano = leAno(mes); 
              int dia = leDia(string);
         		int rede = leRede(string);
         		int ip = leIp(string);
         		if(mes!=99 && ano != 99 && dia != 99)
         		atualizaIP(&ListaIP, rede, ip, ano, mes, dia);
         }
      }
      fclose(log);
  }
	//////////////////////////////////////////////////////////
	//SALVA IP.LOG ATUALIZADO
  gravaLista(&ListaIP);

	//////////////////////////////////////////////////////////
	//LISTA IPS SEM USO POR 3 MESES - não util no servidor. Front end fará esse tratamento
	//listaInativos(&ListaIP);
 	return(0);
}

