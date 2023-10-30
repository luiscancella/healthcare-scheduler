#include "menu.c"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Paciente pacientes[100] = {0};
    Consulta consultas[500] = {0};
    Medico medicos[10] = {0};
    int quantidadeMedico = 0, quantidadePacientes = 0, quantidadeConsultas = 0;

    int resposta = 0;

    quantidadePacientes = lerPacientes(pacientes);
    quantidadeMedico = lerMedicos(medicos);
    quantidadeConsultas = lerConsultas(consultas, medicos, pacientes);

    while (1)
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
            criaConsulta(quantidadeMedico, quantidadePacientes, medicos, pacientes, &quantidadeConsultas);
            quantidadeConsultas = lerConsultas(consultas, medicos, pacientes);
        }
    }

    return 1;
}