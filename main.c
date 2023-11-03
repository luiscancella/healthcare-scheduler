#include "menu.c"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Paciente pacientes[100] = {0};
    Consulta consultas[500] = {0};
    Medico medicos[10] = {0};
    int quantidadeMedico = 0, quantidadePacientes = 0, quantidadeConsultas = 0;
    char codConsulta[30];

    int resposta = -1;

    quantidadePacientes = lerPacientes(pacientes);
    quantidadeMedico = lerMedicos(medicos);
    quantidadeConsultas = lerConsultas(consultas, medicos, pacientes);

    // consultasPorMedico("M0001", consultas, quantidadeConsultas);

    system("pause");

    while (resposta != 0)
    {
        resposta = menu();
        if (resposta == 1)
        {
            criaPaciente(&quantidadePacientes);
            quantidadePacientes = lerPacientes(pacientes);
        }
        else if (resposta == 2)
        {
            criaMedico(&quantidadeMedico);
            quantidadeMedico = lerMedicos(medicos);
        }
        else if (resposta == 3)
        {
            criaConsulta(quantidadeMedico, quantidadePacientes, medicos, pacientes, &quantidadeConsultas, consultas);
            quantidadeConsultas = lerConsultas(consultas, medicos, pacientes);
        }
        else if (resposta == 4)
        {
            printf("Digite o codigo da consulta ----> ");
            scanf("%s", codConsulta);
            cancelarConsulta(codConsulta, consultas, quantidadeConsultas);
            system("pause");
        }
    }

    return 1;
}