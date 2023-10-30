
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char codigo[10];
    char nome[50];
    char telefone[15];
    char especialidade[50];
} Medico;

void criaMedico()
{
    Medico novoMedico;
    FILE *arqMedico = fopen("medico.txt", "a");
    getchar(); // Para consumir o '\n' deixado pelo scanf

    printf("Digite o nome do Medico: ");
    fgets(novoMedico.nome, sizeof(novoMedico.nome), stdin);

    printf("\nDigite um codigo para o Medico: ");
    fgets(novoMedico.codigo, sizeof(novoMedico.codigo), stdin);

    printf("\nDigite o telefone do Medico: ");
    fgets(novoMedico.telefone, sizeof(novoMedico.telefone), stdin);

    printf("\nDigite a especialidade do Medico: ");
    fgets(novoMedico.especialidade, sizeof(novoMedico.especialidade), stdin);

    fprintf(arqMedico, "%s", novoMedico.nome);
    fprintf(arqMedico, "%s", novoMedico.codigo);
    fprintf(arqMedico, "%s", novoMedico.telefone);
    fprintf(arqMedico, "%s\n", novoMedico.especialidade);

    fclose(arqMedico);
}

int lerMedicos(Medico *arrMedicos)
{

    int i = 0;
    FILE *arqMedico = fopen("medico.txt", "r");
    char linha[100];

    if (arqMedico == NULL)
    {
        printf("Erro ao abrir paciente.txt\n");
    }

    while (fgets((arrMedicos + i)->nome, sizeof(char) * 100, arqMedico))
    {
        (arrMedicos + i)->nome[strcspn((arrMedicos + i)->nome, "\n")] = 0;

        fgets((arrMedicos + i)->codigo, sizeof(char) * 10, arqMedico);
        (arrMedicos + i)->codigo[strcspn((arrMedicos + i)->codigo, "\n")] = 0;

        fgets((arrMedicos + i)->telefone, sizeof(char) * 100, arqMedico);
        (arrMedicos + i)->telefone[strcspn((arrMedicos + i)->telefone, "\n")] = 0;

        fgets((arrMedicos + i)->especialidade, sizeof(char) * 100, arqMedico);
        (arrMedicos + i)->especialidade[strcspn((arrMedicos + i)->especialidade, "\n")] = 0;

        fgets(linha, sizeof(char) * 100, arqMedico); // descartar linha entre dados
        i++;
    }

    fclose(arqMedico);
    return i;
}

Medico procuraMedico(char codigo[], Medico *arrMedico, int tamanhoArr)
{

    Medico resposta = {0};
    for (int i = 0; i < tamanhoArr; i++)
    {
        if (strcmp(codigo, (arrMedico + i)->codigo) == 0)
        {
            resposta = *(arrMedico + i);
        }
    }
    return resposta;
}