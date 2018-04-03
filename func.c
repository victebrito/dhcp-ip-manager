
#include "func.h"

void showMenu()
{
	printf("\n");
	printf("------------------------------------------------------------------------------------------\n");
	printf("---                            ATUALIZA IP v1.3  20170217                              ---\n");
	printf("------------------------------------------------------------------------------------------\n");
	printf("-victor.emanuel.brito@gmail.com                                                        ---\n");
	printf("-victorb@qui.ufmg.br                                                                   ---\n");
	printf("------------------------------------------------------------------------------------------\n");
	printf("                                                                                          \n");
	printf("Esse programa é útil para saber a data do último acesso de cada IP na rede do departamento\n");
	printf("                                                                                          \n");
	printf("USO: copie o programa e os dois arquivos necessários para o funcionamento na mesma pasta. \n");
	printf("     use o comando:                                                                       \n");
	printf("                                                                                          \n");
	printf("     ./atualizaIP                                                                         \n");
	printf("                                                                                          \n");
	printf("                                                                                          \n");
	printf("Entrada: arquivo ip.csv, gerado na última data gravada e arquivo messages-xxxxxxxx        \n");
	printf("                                                                                          \n");
	printf("Saida: ip.csv, que contem o registro de acesso de todos os IPs.                           \n");
	printf("       Guarde o ip.csv para a entrada da próxima execução.                                \n");
	printf("                                                                                          \n"); 
	printf("                                                                                          \n");
	printf("                                                                                          \n");
	printf("                                                                                          \n");
	printf("                                                                                          \n");
	printf("                                                                                          \n");
	printf("DICA:O arquivo messages-xxxxxxxx é gerado pelo dhcp do servidor, sendo xx a data.         \n");
	printf("     pode ser obtido em: /var/log/         \n");
	printf("                                                                                          \n");
	printf("O arquivo messages-xxxxxxxx mais antigo suportado é de 11 meses anteriores ao mes atual   \n");
	printf("------------------------------------------------------------------------------------------\n");
	printf("                                                                                          \n");

}

int copiaString(char *chegada, char *saida, int tamanho)            //OK
{
	int i;
	for (int i = 0; i < tamanho; ++i)
	{
		saida[i] = chegada[i];
	}
	return 0;
}


int comparaValido(char *s)                                          //OK
{
	char teste[15];
	if(s[21] == 'd')
	{
		//copia string do char 21 até o 35
		copiaString(&s[28], teste, 7);
		if (strcmp(teste, "DHCPACK") == 0)	
			return(0);
	}
	return(1);
}

int leDia(char *s)                                                  //OK
{
	int dia=99;
	int uni = 99;
	int dec = 0;
	
	if( s[5] > 47 && s[5] < 58 )
	{
		uni = s[5]-48;
		if( s[4] > 47 && s[4] < 58 )
		{
			dec = s[4]-48;
		}
	}
	dia = uni + 10*dec;
	return dia;
}

int leMes(char *s)                                                   //OK
{
	int mes=99;
	//
	if(s[0] == 'F')
	{
		mes = 2;
	}
	else if(s[0] == 'S')
	{
		mes = 9;
	}
	else if(s[0] == 'O')
	{
		mes = 10;
	}
	else if(s[0] == 'N')
	{
		mes = 11;
	}
	else if(s[0] == 'D')
	{
		mes = 12;
	}
	else if(s[0] == 'M')
	{
		if(s[2] == 'r')
		{
			mes = 3;
		}
		if(s[2] == 'y')
		{
			mes = 5;
		}
	}
	else if(s[0] == 'A')
	{
		if(s[2] == 'r')
		{
			mes = 4;
		}
		if(s[2] == 'g')
		{
			mes = 8;
		}
	}
	else if(s[0] == 'J')
	{
		if(s[1] == 'a')
		{
			mes = 1;
		}
		else if(s[2] == 'n')
		{
			mes = 6;
		}
		else if(s[2] == 'l')
		{
			mes = 7;
		}
	}
	return mes;
}


int leAno(int mes)
{
	//OBTEM A DATA
	//Lê dia, ano, mes
	//	int tm_mday
	//	int tm_mon +1
	//	int tm_year	 +1900
	struct tm * timeinfo;
	time_t rawtime;
	time (&rawtime);
	timeinfo = localtime (&rawtime);

	int anoA = timeinfo->tm_year + 1900;
	int mesA = timeinfo->tm_mon + 1;
	if (mes == 99)
		return(99);
	//meses correspondem. Mesmo ano
	else if (mesA == mes )
		return (anoA);
	//Meses não correspondentes, mesmo ano
	else if(mes < mesA )
		return (anoA);
	//Meses não correspondem, virada de ano,  
	else if(mes == 10 || mes == 11 || mes == 12)
	{
		if (mesA == 1 || mesA == 2)
		{
			//Virada de ano, Lê registros de até outubro do outro ano
			//retorna ano anterior
			return(anoA-1);
		}

	}
	else
		printf("Registro muito antigo, mes: %d\n", mes);
		printf("Registro mais antigo suportado: outubro/%d\n", anoA-1);
	return(0);	
} 


int leRede(char *s)                                                    //OK
{
	int rede=99;
	int uni = 0;
	int dec = 0;
	
	if( s[48] > 47 && s[48] < 58 )
	{
		uni = s[48]-48;
		if( s[47] > 47 && s[47] < 58 )
		{
			dec = s[47]-48;
		}
	}
	rede = uni + 10*dec;
	return rede;
}

int leIp(char *s)                                                      //OK
{
	int ip=0;
	int uni = 0;
	int dec = 0;
	int cen = 0;

	if( s[52] > 47 && s[52] < 58 )
	{
		uni = s[52]-48;
		if( s[51] > 47 && s[51] < 58 )
		{
			dec = s[51]-48;
			if( s[50] > 47 && s[50] < 58 )
			{
				cen = s[50]-48;
			}
		}
	}
	else	if( s[51] > 47 && s[51] < 58 )
			{
				uni = s[51]-48;
				if( s[50] > 47 && s[50] < 58 )
				{
					dec = s[50]-48;
				}
			}
	else 	if( s[50] > 47 && s[50] < 58 )
			{
				uni = s[50]-48;
			}

	ip = uni + 10*dec + 100*cen;
	return ip;
}


int atualizaIP(Apontador L,int rede,int ip,int ano,int mes,int dia)
{
	int anoVlho, mesVlho, diaVlho;
	anoVlho = getAno(L, rede, ip);
	mesVlho = getMes(L, rede, ip);
	diaVlho = getDia(L, rede, ip);

	if(ano>anoVlho)
	{
		setIP(L, rede, ip, ano, mes, dia);
	}
	else if(ano==anoVlho && mes>mesVlho)
	{
		setIP(L, rede, ip, ano, mes, dia);	
	}
	else if(ano==anoVlho && mes==mesVlho && dia>diaVlho)
	{
		setIP(L, rede, ip, ano, mes, dia);	
	}
	else
	{
		return(1); //ultimo acesso mais recente já registrado
	}
	return(0);     //ultimo acesso mais recente atualizado
}

int diasOff(Apontador L, int rede, int ip, int ano, int mes, int dia)
{
	int meses = 0;
	int dias = 0;
	int anos = 0;
	//Retorna tempo de inatividade
	int mesL = getMes(L, rede, ip);
	int diaL = getDia(L, rede, ip);
	int anoL = getAno(L, rede, ip);

	//se ip nunca usado
	if (anoL == 99 && mesL == 99 && diaL == 99)
		return(-1);

	anos = ano - anoL;
	meses = mes - mesL;
	dias = dia - diaL;

	//ano virado


	dias = dias + meses*30 + anos*360;
	return (dias);
}

void listaInativos(Apontador L)
{
	//OBTEM A DATA
	//Lê dia, ano, mes
	//	int tm_mday
	//	int tm_mon +1
	//	int tm_year	 +1900
	struct tm * timeinfo;
	time_t rawtime;
	time (&rawtime);
	timeinfo = localtime (&rawtime);

	int ano = timeinfo->tm_year + 1900;
	int mes = timeinfo->tm_mon + 1;
	int dia = timeinfo->tm_mday;

	//CALCULA O TEMPO INATIVO DE CADA IP, SO FOR MAIOR QUE 90 dias IMPRIME NA TELA
	int i,j,rede, diasinativo; 

    printf("\nIPs não usados:\n\n");
    int flag = 1;

    for(i=0; i<3; i++)
    {
    	if(i==0)
        {
        	rede = 16;
    	}
        else if(i==1)
        {
            rede = 19;
        }
        else if(i==2)
        {
            rede = 20;
        }
        for(j=1; j<256; j++)
        {
            diasinativo = diasOff(L, rede, j, ano, mes, dia);
            if (diasinativo == -1)
            {
            	printf("ip: 150.164.%d.%d nunca usado\n", rede, j);
            	flag = 0;
            }
            if (diasinativo > 90)
            {
	            printf("ip: %d, dias: %d\n", j, diasinativo );
            	flag = 0;
            }
       	}
    }
    if (flag == 1)
    {
		printf(" Nenhum IP não usado nos últimos 90 dias\n\n");    
    }
    else
    {
		printf("\nFim da lista\n\n");    	
    }

}


