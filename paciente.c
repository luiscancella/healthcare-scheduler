#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// PACIENTE = código, nome, endereco, telefone e data de nascimento

typedef struct
{

    char rua[100];
    char bairro[100];
    char cep[100];
    char cidade[100];
    int numero;
    char complemento[100];
} Endereco;

typedef struct
{
    char codigo[10];
    char nome[50];
    Endereco endereco;

} Paciente;

void criaPaciente()
{
    Paciente novoPaciente;
    int resposta = -1;
    FILE *arqPaciente = fopen("paciente.txt", "a");
    getchar(); // Para consumir o '\n' deixado pelo scanf

    printf("Digite o nome do paciente: ");
    fgets(novoPaciente.nome, sizeof(novoPaciente.nome), stdin);

    printf("\nDigite um codigo para o paciente: ");
    fgets(novoPaciente.codigo, sizeof(novoPaciente.codigo), stdin);

    printf("\nDigite o nome da rua do paciente: ");
    fgets(novoPaciente.endereco.rua, sizeof(novoPaciente.endereco.rua), stdin);

    printf("\nDigite o nome do bairro do paciente: ");
    fgets(novoPaciente.endereco.bairro, sizeof(novoPaciente.endereco.bairro), stdin);

    printf("\nDigite o CEP do paciente: ");
    fgets(novoPaciente.endereco.cep, sizeof(novoPaciente.endereco.cep), stdin);

    printf("\nDigite a cidade do paciente: ");
    fgets(novoPaciente.endereco.cidade, sizeof(novoPaciente.endereco.cidade), stdin);

    printf("\nDigite o numero do endereco do paciente: ");
    scanf("%d", &novoPaciente.endereco.numero);
    getchar(); // Para consumir o '\n' deixado pelo scanf

    while (resposta != 1 && resposta != 0)
    {
        printf("\n\nPara adicionar complemento digite 1, para deixar em branco digite 0: ");
        scanf("%d", &resposta);
        getchar(); // Para consumir o '\n' deixado pelo scanf
    }

    if (resposta == 1)
    {
        printf("\nDigite o complemento do endereco do paciente: ");
        fgets(novoPaciente.endereco.complemento, sizeof(novoPaciente.endereco.complemento), stdin);
    }
    else
    {
        strcpy(novoPaciente.endereco.complemento, "Sem complemento");
    }

    fprintf(arqPaciente, "%s", novoPaciente.nome);
    fprintf(arqPaciente, "%s", novoPaciente.codigo);
    fprintf(arqPaciente, "%s", novoPaciente.endereco.rua);
    fprintf(arqPaciente, "%s", novoPaciente.endereco.bairro);
    fprintf(arqPaciente, "%s", novoPaciente.endereco.cep);
    fprintf(arqPaciente, "%s", novoPaciente.endereco.cidade);
    fprintf(arqPaciente, "%d\n", novoPaciente.endereco.numero);
    fprintf(arqPaciente, "%s\n", novoPaciente.endereco.complemento);

    fclose(arqPaciente);
}

void lerPacientes(Paciente *arrPacientes)
{

    int i = 0;
    FILE *arqPaciente = fopen("paciente.txt", "r");
    char linha[100];

    if (arqPaciente == NULL)
    {
        printf("Erro ao abrir paciente.txt\n");
    }

    while (fgets((arrPacientes + i)->nome, sizeof(char) * 100, arqPaciente))
    {
        (arrPacientes + i)->nome[strcspn((arrPacientes + i)->nome, "\n")] = 0;

        fgets((arrPacientes + i)->codigo, sizeof(char) * 10, arqPaciente);
        (arrPacientes + i)->codigo[strcspn((arrPacientes + i)->codigo, "\n")] = 0;

        fgets((arrPacientes + i)->endereco.rua, sizeof(char) * 100, arqPaciente);
        (arrPacientes + i)->endereco.rua[strcspn((arrPacientes + i)->endereco.rua, "\n")] = 0;

        fgets((arrPacientes + i)->endereco.bairro, sizeof(char) * 100, arqPaciente);
        (arrPacientes + i)->endereco.bairro[strcspn((arrPacientes + i)->endereco.bairro, "\n")] = 0;

        fgets((arrPacientes + i)->endereco.cep, sizeof(char) * 100, arqPaciente);
        (arrPacientes + i)->endereco.cep[strcspn((arrPacientes + i)->endereco.cep, "\n")] = 0;

        fgets((arrPacientes + i)->endereco.cidade, sizeof(char) * 100, arqPaciente);
        (arrPacientes + i)->endereco.cidade[strcspn((arrPacientes + i)->endereco.cidade, "\n")] = 0;

        char numero[10];
        fgets(numero, sizeof(numero), arqPaciente);
        numero[strcspn(numero, "\n")] = 0;
        (arrPacientes + i)->endereco.numero = atoi(numero);

        fgets((arrPacientes + i)->endereco.complemento, sizeof(char) * 100, arqPaciente);
        (arrPacientes + i)->endereco.complemento[strcspn((arrPacientes + i)->endereco.complemento, "\n")] = 0;
        fgets(linha, sizeof(char) * 100, arqPaciente); // descartar linha entre dados
        i++;
    }
    fclose(arqPaciente);
    return i;
}

Paciente procuraPaciente(char codigo[], Paciente *arrPaciente, int tamanhoArr)
{

    Paciente resposta = {0};
    for (int i = 0; i < tamanhoArr; i++)
    {
        if (strcmp(codigo, (arrPaciente + i)->codigo) == 0)
        {
            resposta = *(arrPaciente + i);
        }
    }
    return resposta;
}