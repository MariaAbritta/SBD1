#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//funções
void abertura(){ //Printar a abertura do sistema
    printf("------------------------------\n");
    printf("         Seu Automóvel        \n");
    printf("------------------------------\n");
    printf("Nome do aluno ......: ");
}

//Main
int main() {

    /*Criando as structs */
    struct fichaDoUsuario{
        char nomeCompleto[5000];
        char telefone[5000];
    };

    /*Criando as structs */
    struct fichaDoCarro{
        float numDeRegistroDoVeiculo[5000];
        char marca[5000];
        char modelo[5000];
        float ano[5000];
        char cor[5000];
        char placa[5000];
    };

    /*Criando as variáveis aluno e carro que serão do tipo struct fichaDoUsuario
    e  fichaDoCarro*/
    struct fichaDoUsuario usuario;
    struct fichaDoCarro carro;

    //Início do programa
    abertura();
}