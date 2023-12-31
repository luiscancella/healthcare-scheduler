#include "menu.c"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Paciente pacientes[100] = {0};
    Consulta consultas[500] = {0};
    Medico medicos[10] = {0};
    int quantidadeMedico = 0, quantidadePacientes = 0, quantidadeConsultas = 0;
    char textoResposta[50];

    int resposta = -1;
    quantidadePacientes = lerPacientes(pacientes);
    quantidadeMedico = lerMedicos(medicos);
    quantidadeConsultas = lerConsultas(consultas, medicos, pacientes);
    printf("\nConsultas: %d \nPacientes: %d \nMedicos: %d\n\n", quantidadeConsultas, quantidadePacientes, quantidadeMedico);

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
            scanf("%s", textoResposta);
            cancelarConsulta(textoResposta, consultas, quantidadeConsultas);
        }
        else if (resposta == 5)
        {
            consultasPorData(consultas, quantidadeConsultas);
        }
        else if (resposta == 6)
        {
            consultasPorPaciente(consultas, quantidadeConsultas);
        }
        else if (resposta == 7)
        {
            printf("=-=-=-=-=-= PESQUISA DE CONSULTA POR MEDICO =-=-=-=-=-=\n\n");
            printf("Digite o Nome ou Codigo do Medico ----> ");
            scanf("%s", textoResposta);
            consultasPorMedico(textoResposta, consultas, quantidadeConsultas);
        }

        else if (resposta == 8)
        {
            adicionarFeedback(consultas, quantidadeConsultas);
        }
    }

    return 1;
}