#include "medico.c"
#include "paciente.c"

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
} Consulta;

int contaConsultasMedicosPorDia(Consulta consultas[], int dia, int mes, int ano, int quantidadeConsultas, Medico medico)
{

    int numConsultas = 0;

    for (int i = 0; i < quantidadeConsultas; i++)
    {
        if (consultas[i].data.dia == dia &&
            consultas[i].data.mes == mes &&
            consultas[i].data.ano == ano &&
            !strcmp(consultas[i].medico.codigo, medico.codigo))
        {
            numConsultas++;
        }
    }
    printf("Medico %s possui %d consultas no dia %d/%d/%d\n", medico.nome, numConsultas, dia, mes, ano);
    return numConsultas;
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
        return;
    novaConsulta.medico = medico;

    printf("Digite com o codigo do paciente: ");
    scanf("%s", codPaciente);
    paciente = procuraPaciente(codPaciente, pacientes, quantidadePaciente);

    if (strcmp(paciente.codigo, "") == 0)
        return;
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
    else
    {
        fprintf(arqConsultas, "%s\n", novaConsulta.codigoConsulta);
        fprintf(arqConsultas, "%d\n", novaConsulta.data.dia);
        fprintf(arqConsultas, "%d\n", novaConsulta.data.mes);
        fprintf(arqConsultas, "%d\n", novaConsulta.data.ano);
        fprintf(arqConsultas, "%d\n", novaConsulta.data.hora);
        fprintf(arqConsultas, "%d\n", novaConsulta.data.minutos);
        fprintf(arqConsultas, "%s\n", novaConsulta.paciente.codigo);
        fprintf(arqConsultas, "%s\n\n", novaConsulta.medico.codigo);
        fprintf(arqConsultas, "1");
    }

    fclose(arqConsultas);
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

        char numero[10];

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

    for(i = 0; i < tamanhoArr; i++)
    {
        if(strcmp(codigo, (consultas + i)->codigoConsulta)==0)
        {
            (consultas + i)->ativo = 0;
            existeConsulta = 1;
        }
    }

    if(existeConsulta != 1)
    {
        printf("Consulta não existe!\n");
        return;
    }

    fclose(arqConsulta);
    arqConsulta = fopen("consultas.txt", "w");

    for(i = 0; i < tamanhoArr; i++)
    {
        fprintf(arqConsulta, "%s\n", (consultas + i)->codigoConsulta);
        fprintf(arqConsulta, "%d\n", (consultas + i)->data.dia);
        fprintf(arqConsulta, "%d\n", (consultas + i)->data.mes);
        fprintf(arqConsulta, "%d\n", (consultas + i)->data.ano);
        fprintf(arqConsulta, "%d\n", (consultas + i)->data.hora);
        fprintf(arqConsulta, "%d\n", (consultas + i)->data.minutos);
        fprintf(arqConsulta, "%s\n", (consultas + i)->paciente.codigo);
        fprintf(arqConsulta, "%s\n", (consultas + i)->medico.codigo);
        fprintf(arqConsulta, "%d\n\n", (consultas + i)->ativo);
    }
    fclose(arqConsulta);
    
    printf("Consulta cancelada com sucesso!\n");
}

void consultasPorMedico(char identificador[], Consulta consultas[], int quantidadeConsultas)
{
    int numConsultas = 1;

    for(int i = 0; i < quantidadeConsultas; i++)
    {
        if(strcmp(identificador, consultas[i].medico.nome) == 0 || strcmp(identificador, consultas[i].medico.codigo) == 0)
        {
            printf("- CONSULTA %d:\n\n", numConsultas);
            printf("=-=-=-=DADOS DA CONSULTA=-=-=-=\n");
            printf("CODIGO DA CONSULTA: %s\n", consultas[i].codigoConsulta);
            printf("DATA: %d/%d/%d\n", consultas[i].data.dia, consultas[i].data.mes, consultas[i].data.ano);
            printf("\n=-=-=-=DADOS DO PACIENTE=-=-=-=\n");
            printf("NOME: %s\n", consultas[i].paciente.nome);
            printf("CODIGO: %s\n", consultas[i].paciente.codigo);
            printf("\n=-=-=-=DADOS DO MEDICO=-=-=-=\n");
            printf("NOME: %s\n", consultas[i].medico.nome);
            printf("CODIGO: %s\n", consultas[i].medico.codigo);
            printf("\n\n");
        }
    }
}