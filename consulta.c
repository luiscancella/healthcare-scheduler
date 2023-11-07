#include "medico.c"
#include "paciente.c"
#include <stdbool.h>

typedef struct
{
    int dia;
    int mes;
    int ano;
    int hora;
    int minutos;
} Data;

typedef struct
{
    char codigoConsulta[10];
    Data data;
    Paciente paciente;
    Medico medico;
    int ativo;
    char feedback[500];
} Consulta;

int contaConsultasMedicosPorDia(Consulta consultas[], int dia, int mes, int ano, int quantidadeConsultas, Medico medico)
{

    int numConsultas = 0;

    for (int i = 0; i < quantidadeConsultas; i++)
    {
        if (consultas[i].data.dia == dia &&
            consultas[i].data.mes == mes &&
            consultas[i].data.ano == ano &&
            consultas[i].ativo &&
            !strcmp(consultas[i].medico.codigo, medico.codigo))
        {
            numConsultas++;
        }
    }
    return numConsultas;
}

bool checaHorario(Consulta consultas[], int dia, int mes, int ano, int hora, int minutos, int quantidadeConsultas, Medico medico)
{

    for (int i = 0; i < quantidadeConsultas; i++)
    {
        if (consultas[i].data.dia == dia &&
            consultas[i].data.mes == mes &&
            consultas[i].data.ano == ano &&
            consultas[i].ativo &&
            !strcmp(consultas[i].medico.codigo, medico.codigo) &&
            consultas[i].data.hora == hora)
        {

            if (consultas[i].data.minutos - minutos < 30)
            {
                return false;
            }
        }
    }
    return true;
}

void criaConsulta(int quantidadeMedico, int quantidadePaciente, Medico medicos[], Paciente pacientes[], int *qtdConsultas, Consulta consultas[])
{

    Consulta novaConsulta;
    Medico medico;
    Paciente paciente;
    char codMedico[12], codPaciente[12];
    FILE *arqConsultas = fopen("./consultas.txt", "a");

    printf("Digite com o codigo do medico: ");
    scanf("%s", codMedico);
    medico = procuraMedico(codMedico, medicos, quantidadeMedico);

    if (strcmp(medico.codigo, "") == 0)
    {
        printf("Medico nao encontrado!\n");
        return;
    }
    novaConsulta.medico = medico;

    printf("Digite com o codigo do paciente: ");
    scanf("%s", codPaciente);
    paciente = procuraPaciente(codPaciente, pacientes, quantidadePaciente);

    if (strcmp(paciente.codigo, "") == 0)
    {
        printf("Paciente nao encontrado!\n");
        return;
    }
    novaConsulta.paciente = paciente;

    sprintf(novaConsulta.codigoConsulta, "C%04d", (*qtdConsultas) + 1);

    printf("Digite o dia da consulta: ");
    scanf("%d", &novaConsulta.data.dia);

    printf("Digite o mes da consulta: ");
    scanf("%d", &novaConsulta.data.mes);

    printf("Digite o ano da consulta: ");
    scanf("%d", &novaConsulta.data.ano);

    printf("Digite a hora da consulta: ");
    scanf("%d", &novaConsulta.data.hora);

    printf("Digite o minuto da consulta: ");
    scanf("%d", &novaConsulta.data.minutos);

    if (contaConsultasMedicosPorDia(consultas, novaConsulta.data.dia, novaConsulta.data.mes, novaConsulta.data.ano, *qtdConsultas, medico) >= 2)
    {
        printf("Medico ja possui duas consultas nesse dia\n");
        return;
    }
    else if (contaConsultasMedicosPorDia(consultas, novaConsulta.data.dia, novaConsulta.data.mes, novaConsulta.data.ano, *qtdConsultas, medico) == 1)
    {
        if (!checaHorario(consultas, novaConsulta.data.dia, novaConsulta.data.mes, novaConsulta.data.ano, novaConsulta.data.hora, novaConsulta.data.minutos, *qtdConsultas, medico))
        {
            printf("\nMedico ja possui uma consulta nesse horario\n");
            return;
        }
    }
    else
    {
        fprintf(arqConsultas, "%s\n", novaConsulta.codigoConsulta);
        fprintf(arqConsultas, "%d\n", novaConsulta.data.dia);
        fprintf(arqConsultas, "%d\n", novaConsulta.data.mes);
        fprintf(arqConsultas, "%d\n", novaConsulta.data.ano);
        fprintf(arqConsultas, "%d\n", novaConsulta.data.hora);
        fprintf(arqConsultas, "%d\n", novaConsulta.data.minutos);
        fprintf(arqConsultas, "%s\n", novaConsulta.paciente.codigo);
        fprintf(arqConsultas, "%s\n", novaConsulta.medico.codigo);
        fprintf(arqConsultas, "1\n");
        fprintf(arqConsultas, "Sem Feedback\n\n");
    }

    fclose(arqConsultas);
    printf("Consulta criado com sucesso\n");
}

int lerConsultas(Consulta *arrConsultas, Medico medicos[], Paciente pacientes[])
{

    int i = 0;
    FILE *arqConsulta = fopen("consultas.txt", "r");
    char linha[100];

    if (arqConsulta == NULL)
    {
        printf("Erro ao abrir consultas.txt\n");
    }

    while (fgets((arrConsultas + i)->codigoConsulta, sizeof(char) * 100, arqConsulta))
    {
        (arrConsultas + i)->codigoConsulta[strcspn((arrConsultas + i)->codigoConsulta, "\n")] = 0;

        char numero[500];

        fgets(numero, sizeof(numero), arqConsulta);
        numero[strcspn(numero, "\n")] = 0;
        (arrConsultas + i)->data.dia = atoi(numero);

        fgets(numero, sizeof(numero), arqConsulta);
        numero[strcspn(numero, "\n")] = 0;
        (arrConsultas + i)->data.mes = atoi(numero);

        fgets(numero, sizeof(numero), arqConsulta);
        numero[strcspn(numero, "\n")] = 0;
        (arrConsultas + i)->data.ano = atoi(numero);

        fgets(numero, sizeof(numero), arqConsulta);
        numero[strcspn(numero, "\n")] = 0;
        (arrConsultas + i)->data.hora = atoi(numero);

        fgets(numero, sizeof(numero), arqConsulta);
        numero[strcspn(numero, "\n")] = 0;
        (arrConsultas + i)->data.minutos = atoi(numero);

        char codPaciente[10] = "";
        fgets(codPaciente, sizeof(char) * 10, arqConsulta);
        codPaciente[strcspn(codPaciente, "\n")] = 0;
        (arrConsultas + i)->paciente = procuraPaciente(codPaciente, pacientes, 100);

        char codMedico[10] = "";
        fgets(codMedico, sizeof(char) * 10, arqConsulta);
        codMedico[strcspn(codMedico, "\n")] = 0;
        (arrConsultas + i)->medico = procuraMedico(codMedico, medicos, 100);

        fgets(numero, sizeof(numero), arqConsulta);
        numero[strcspn(numero, "\n")] = 0;
        (arrConsultas + i)->ativo = atoi(numero);

        fgets((arrConsultas + i)->feedback, sizeof(char) * 500, arqConsulta);
        (arrConsultas + i)->feedback[strcspn((arrConsultas + i)->feedback, "\n")] = 0;

        fgets(linha, sizeof(char) * 100, arqConsulta); // descartar linha entre dados

        i++;
    }
    fclose(arqConsulta);
    return i;
}

void cancelarConsulta(char codigo[], Consulta *consultas, int tamanhoArr)
{

    int i = 0;
    FILE *arqConsulta = fopen("consultas.txt", "r");
    char linha[100];
    int existeConsulta = 0;

    if (arqConsulta == NULL)
    {
        printf("Erro ao abrir consultas.txt\n");
        return;
    }

    for (i = 0; i < tamanhoArr; i++)
    {
        if (strcmp(codigo, (consultas + i)->codigoConsulta) == 0)
        {
            (consultas + i)->ativo = 0;
            existeConsulta = 1;
        }
    }

    if (existeConsulta != 1)
    {
        printf("Consulta não existe!\n");
        return;
    }

    fclose(arqConsulta);
    arqConsulta = fopen("consultas.txt", "w");

    for (i = 0; i < tamanhoArr; i++)
    {
        fprintf(arqConsulta, "%s\n", (consultas + i)->codigoConsulta);
        fprintf(arqConsulta, "%d\n", (consultas + i)->data.dia);
        fprintf(arqConsulta, "%d\n", (consultas + i)->data.mes);
        fprintf(arqConsulta, "%d\n", (consultas + i)->data.ano);
        fprintf(arqConsulta, "%d\n", (consultas + i)->data.hora);
        fprintf(arqConsulta, "%d\n", (consultas + i)->data.minutos);
        fprintf(arqConsulta, "%s\n", (consultas + i)->paciente.codigo);
        fprintf(arqConsulta, "%s\n", (consultas + i)->medico.codigo);
        fprintf(arqConsulta, "%d\n", (consultas + i)->ativo);
        fprintf(arqConsulta, "%s\n\n", (consultas + i)->feedback);
    }
    fclose(arqConsulta);

    printf("Consulta cancelada com sucesso!\n");
}

void consultasPorData(Consulta consultas[], int quantidadeConsultas)
{
    int dia = 0, mes = 0, ano = 0;
    int numConsultas = 0;

    printf("Digite o dia: ");
    scanf("%d", &dia);
    printf("Digite o mes: ");
    scanf("%d", &mes);
    printf("Digite o ano: ");
    scanf("%d", &ano);

    for (int i = 0; i < quantidadeConsultas; i++)
    {
        if (consultas[i].data.dia == dia &&
            consultas[i].data.mes == mes &&
            consultas[i].data.ano == ano &&
            consultas[i].ativo)
        {
            numConsultas++;
            printf("Codigo da consulta: %s\n", consultas[i].codigoConsulta);
            printf("Nome do médico: %s\n", consultas[i].medico.nome);
            printf("Nome do paciente: %s\n", consultas[i].paciente.nome);
            printf("Horario: %d:%d\n", consultas[i].data.hora, consultas[i].data.minutos);
            printf("Feedback: %s\n\n", consultas[i].feedback);
        }
    }

    if (numConsultas == 0)
    {
        printf("Nao ha consultas nesse dia\n");
    }
    return;
}

void consultasPorPaciente(Consulta consultas[], int quantidadeConsultas)
{
    getchar(); // Para consumir o '\n' deixado pelo scanf
    char entrada[50];
    int numConsultas = 0;

    printf("Digite nome ou codigo do paciente: %s", entrada);
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = 0;

    for (int i = 0; i < quantidadeConsultas; i++)
    {

        if ((!(strcmp(entrada, consultas[i].paciente.codigo)) && consultas[i].ativo) ||
            (!(strcmp(entrada, consultas[i].paciente.nome)) && consultas[i].ativo))
        {
            numConsultas++;
            printf("Codigo da consulta: %s\n", consultas[i].codigoConsulta);
            printf("Nome do médico: %s\n", consultas[i].medico.nome);
            printf("Nome do paciente: %s\n", consultas[i].paciente.nome);
            printf("Horario: %d:%d\n", consultas[i].data.hora, consultas[i].data.minutos);
            printf("Feedback: %s\n\n", consultas[i].feedback);
        }
    }

    if (!numConsultas)
    {
        printf("Nenhuma consulta com esse nome ou codigo de paciente foi encontrada\n");
    }
    return;
}

void consultasPorMedico(char identificador[], Consulta consultas[], int quantidadeConsultas)
{
    int numConsultas = 1;
    int achouConsulta = 0;

    for (int i = 0; i < quantidadeConsultas; i++)
    {
        if (strcmp(identificador, consultas[i].medico.nome) == 0 || strcmp(identificador, consultas[i].medico.codigo) == 0)
        {
            printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
            printf("\n- CONSULTA %d:\n\n", numConsultas);
            printf("=-=-=-=DADOS DA CONSULTA=-=-=-=\n");
            printf("CODIGO DA CONSULTA: %s\n", consultas[i].codigoConsulta);
            printf("DATA: %d/%d/%d\n", consultas[i].data.dia, consultas[i].data.mes, consultas[i].data.ano);
            printf("FEEDBACK: %s\n", consultas[i].feedback);
            printf("\n=-=-=-=DADOS DO PACIENTE=-=-=-=\n");
            printf("NOME: %s\n", consultas[i].paciente.nome);
            printf("CODIGO: %s\n", consultas[i].paciente.codigo);
            printf("\n=-=-=-=DADOS DO MEDICO=-=-=-=\n");
            printf("NOME: %s\n", consultas[i].medico.nome);
            printf("CODIGO: %s\n", consultas[i].medico.codigo);

            achouConsulta = 1;
            numConsultas++;
        }
    }

    if (achouConsulta == 0)
    {
        printf("\nMedico nao existe ou nao possui consulta!\n");
    }

    printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

Consulta *procuraConsulta(char codigo[], Consulta *arrConsulta, int tamanhoArr)
{

    Consulta *resposta = {0};
    for (int i = 0; i < tamanhoArr; i++)
    {
        if (strcmp(codigo, (arrConsulta + i)->codigoConsulta) == 0)
        {
            resposta = (arrConsulta + i);
        }
    }
    return resposta;
}

void adicionarFeedback(Consulta *consultas, int numConsultas)
{
    char codConsulta[50];
    printf("Codigo da consulta: ");
    scanf("%s", codConsulta);

    Consulta *consultaPmudar = procuraConsulta(codConsulta, consultas, numConsultas);
    if (consultaPmudar != NULL)
    {
        printf("Feedback: ");
        getchar();
        fgets(consultaPmudar->feedback, sizeof(char) * 100, stdin);
        consultaPmudar->feedback[strcspn(consultaPmudar->feedback, "\n")] = 0;

        FILE *arqConsulta = fopen("consultas.txt", "w");
        for (int i = 0; i < numConsultas; i++)
        {
            fprintf(arqConsulta, "%s\n", (consultas + i)->codigoConsulta);
            fprintf(arqConsulta, "%d\n", (consultas + i)->data.dia);
            fprintf(arqConsulta, "%d\n", (consultas + i)->data.mes);
            fprintf(arqConsulta, "%d\n", (consultas + i)->data.ano);
            fprintf(arqConsulta, "%d\n", (consultas + i)->data.hora);
            fprintf(arqConsulta, "%d\n", (consultas + i)->data.minutos);
            fprintf(arqConsulta, "%s\n", (consultas + i)->paciente.codigo);
            fprintf(arqConsulta, "%s\n", (consultas + i)->medico.codigo);
            fprintf(arqConsulta, "%d\n", (consultas + i)->ativo);
            fprintf(arqConsulta, "%s\n\n", (consultas + i)->feedback);
        }
        fclose(arqConsulta);

        printf("Feedback adicionado com sucesso!\n");
    }
    else
    {
        printf("Consulta não encontrada!\n");
    }
    return;
}
