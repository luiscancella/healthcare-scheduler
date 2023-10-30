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

    // quantidadePacientes = lerPacientes(pacientes);
    quantidadeMedico = lerMedicos(medicos);
    // while (1)
    // {
    //     resposta = menu();
    //     if (resposta == 1)
    //     {
    //         criaPaciente();
    //     }
    //     else if (resposta == 2)
    //     {
    //         criaMedico();
    //     }
    //     else if (resposta == 3)
    //     {
    //         criaConsulta();
    //     }
    // }
    char *string = "M0001";
    Medico novoMed = procuraMedico(string, medicos, quantidadeMedico); // apagar
    if (novoMed.codigo)
        printf("%s", novoMed.nome);
    return 1;
}