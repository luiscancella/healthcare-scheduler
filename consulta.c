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
} Consulta;

void criaConsulta(int quantidadeMedico, int quantidadePaciente, Medico medicos[], Paciente pacientes[])
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

    printf("Digite o codigo de consulta: ");
    scanf("%s", novaConsulta.codigoConsulta);

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

    fprintf(arqConsultas, "%s\n", novaConsulta.codigoConsulta);
    fprintf(arqConsultas, "%d\n", novaConsulta.data.dia);
    fprintf(arqConsultas, "%d\n", novaConsulta.data.mes);
    fprintf(arqConsultas, "%d\n", novaConsulta.data.ano);
    fprintf(arqConsultas, "%d\n", novaConsulta.data.hora);
    fprintf(arqConsultas, "%d\n", novaConsulta.data.minutos);
    fprintf(arqConsultas, "%s\n", novaConsulta.paciente.codigo);
    fprintf(arqConsultas, "%s\n\n", novaConsulta.medico.codigo);

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

        printf("dia: %s\n", (arrConsultas + i)->paciente.codigo);
        fgets(linha, sizeof(char) * 100, arqConsulta); // descartar linha entre dados

        i++;
    }
    fclose(arqConsulta);
    return i;
}