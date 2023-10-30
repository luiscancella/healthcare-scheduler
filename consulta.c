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

void criaConsulta()
{

    Consulta novaConsulta;
    Medico medico;
    Paciente paciente;
    char codMedico[12], codPaciente[12];

    printf("Entre com o codigo do medico");
    scanf("%s", &codMedico);

    printf("Entre com o codigo do paciente");
    scanf("%s", &codPaciente);

    printf("Digite o codigo de consulta: ");
    scanf("%s", novaConsulta.codigoConsulta);

    printf("Digite o codigo do paciente: ");
    scanf("%s", codPaciente);

    printf("Digite o codigo do medico: ");
    scanf("%s", codMedico);

    printf("Digite o dia da consulta: ");
    scanf("%d", &novaConsulta.data.dia);

    printf("Digite o mes da consulta: ");
    scanf("%d", &novaConsulta.data.mes);

    printf("Digite o ano da consulta: ");
    scanf("%d", &novaConsulta.data.ano);

    printf("Digite a hora da consulta: ");
    scanf("%d", &novaConsulta.data.hora);

    printf("Digite a hora da consulta: ");
    scanf("%d", &novaConsulta.data.minutos);
}