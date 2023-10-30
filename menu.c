#include <stdio.h>
#include <stdlib.h>
#include "consulta.c"

void printBarra()
{
    printf("----------------------------------------------------------------");
}

int menu()
{
    int resposta = 0;
    while (resposta < 1 || resposta > 8)
    {
        system("clear");
        printf("BEM VINDO AO MENU!!\n");
        printf("1 - Cadastrar um paciente\n");
        printf("2 - Cadastrar um medico\n");
        printf("3 - Cadastrar uma consulta\n");
        printf("4 - Cancelar uma consulta\n");
        printf("5 - Consultas por data\n");
        printf("6 - Consultas de um paciente pro nome ou código\n");
        printf("7 - Consultas de um medico por nome ou código\n");
        printf("8 - Funcao extra do grupo\n");
        printBarra();
        printf("\nSELECIONE UMA OPÇAO: ");
        scanf("%d", &resposta);
        system("clear");
    }

    return resposta;
}