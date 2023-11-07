#include <stdio.h>
#include <stdlib.h>
#include "consulta.c"

void printBarra()
{
    printf("----------------------------------------------------------------\n");
}

int menu()
{
    int resposta = -1;
    while (resposta < 0 || resposta > 8)
    {
        printBarra();
        printf("BEM VINDO AO MENU!!\n\n");
        printf("1 - Cadastrar um paciente\n");
        printf("2 - Cadastrar um medico\n");
        printf("3 - Cadastrar uma consulta\n");
        printf("4 - Cancelar uma consulta\n");
        printf("5 - Consultas por data\n");
        printf("6 - Consultas de um paciente por nome ou código\n");
        printf("7 - Consultas de um medico por nome ou código\n");
        printf("8 - Adicionar feedback de paciente\n");
        printf("0 - SAIR\n");

        printBarra();
        printf("SELECIONE UMA OPÇAO: ");
        scanf("%d", &resposta);
        printBarra();
    }

    return resposta;
}