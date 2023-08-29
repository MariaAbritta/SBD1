#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "JogoDaForca.h"

//Variáveis globais
char palavraSecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesDados = 0;

//funções
void abertura(){ //Printar a abertura do jogo
    printf("------------------------------\n");
    printf("         Jogo da Forca        \n");
    printf("------------------------------\n");
}

void chute(){ //Captura um novo chute
    char chute;
    scanf(" %c", &chute);
    //espaço -> ignorar o espaço que se da para rodar o código

    chutes[(chutesDados)] = chute;
    chutesDados++;
}

void desenhaForca(){

    int erros = chutesErrados();
 
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for (int i = 0; i < strlen(palavraSecreta); i++)
    {

        int achou = jaChutou(palavraSecreta[i]);

        if (achou)
        {
            printf("%c ", palavraSecreta[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}

void adicionaPalavra(){
    char quer;

    printf("Você deseja adicionar uma nova palavra no jogo? (S/N)");
    scanf(" %c", &quer);

    if(quer == 'S'){
        char novaPalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra?");
        scanf("%s", novaPalavra);

        FILE* f;

        f = fopen("Palavras.txt", "r+");
        if(f == 0){
            printf("Desculpe, banco de dados não disponível.\n");
            exit(1);
        }

        int quantidade;
        fscanf(f, "%d", &quantidade);
        quantidade++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", quantidade);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novaPalavra);

        fclose(f);
    }
}

void escolhePalavra(){
    FILE* f;

    f = fopen("Palavras.txt", "r");
    if(f == 0){
        printf("Desculpe, banco de dados não disponível.\n");
        exit(1);
    }

    int quantidadePalavras;
    fscanf(f, "%d", &quantidadePalavras);
    //fscanf -> Ler algo de dentro de um arquivo

    srand(time(0));
    int randomico = rand() % quantidadePalavras;

    for (int i = 0; i <= randomico; i++){
        fscanf(f, "%s", palavraSecreta);
    }

    fclose(f);
}

int acertou(){
    for (int i = 0; i < strlen(palavraSecreta); i++)
    {
        if (!jaChutou(palavraSecreta[i]))
        {
            return 0;
        }
    }

    return 1;
}

int chutesErrados(){
    int erros = 0;

    for (int i = 0; i < chutesDados; i++)
    {
        int existe = 0;
        for (int j = 0; j < strlen(palavraSecreta); j++)
        {
            if (chutes[i] == palavraSecreta[j])
            {
                existe = 1;
                break;
            }
        }

        if (!existe)
            erros++;
    }
    return erros;
}

int enforcou(){

    return chutesErrados() >= 5;
}

int jaChutou(char letra){
    int achou = 0;
    for (int j = 0; j < chutesDados; j++)
    {
        if (chutes[j] == letra)
        {
            achou = 1;
            break;
        }
    }
    return achou;
}

//Main
int main(){

    escolhePalavra(palavraSecreta);
    abertura();

    do
    {

        desenhaForca(palavraSecreta, chutes, chutesDados);
        chute(chutes, &chutesDados);

    } while (!acertou() && !enforcou());
    //não acertou e não enforcou

    if(acertou()){
        printf("\nParabéns, você ganhou!\n");
    }else{
        printf("\nPuxa você foi enforcado!\n");
        printf("A palavra secreta era: *%s*!\n", palavraSecreta);
    }

    adicionaPalavra();
}
