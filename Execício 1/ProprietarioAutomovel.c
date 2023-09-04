#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

//funções
void abertura(){ //Printar a abertura do sistema
    printf("---------------------------\n");
    printf(" Gerenciamento de Veículos \n");
    printf("---------------------------\n");
    printf("Desenvolvido para simplificar e otimizar a tarefa de administrar \ne controlar informações sobre seus automóveis, proporcionando aos\nproprietários uma maneira conveniente e eficaz de gerenciar seus veículos.\n");
    printf("---------------------------\n");
    printf("Por favor, escolha uma das opções a seguir:\n");
    printf("1 - Cadastrar novo Usuário e seu Automóvel\n");
    printf("2 - Listar Usuários e Automoveis\n");
    printf("3 - Sair do programa\n");
    printf("Opção: ");
}

/*Criando a struct dos dados do cliente */
typedef struct {
    char nomeCompleto[100];
    char telefone[13];
    char cpf[11];
    int quantidadeAutomoveis;
    char carros[MAX][7];
} FichaDoUsuario;

/*Criando as structs */
typedef struct {
    char numDeRegistroDoVeiculo[12];
    char marca[30];
    char modelo[30];
    char ano[4];
    char cor[30];
    char placa[8];
} FichaDoCarro;

/*Criando as variáveis aluno e carro que serão do tipo struct fichaDoUsuario
e  fichaDoCarro*/
FichaDoUsuario usuario;
FichaDoCarro carro;

//Main
int main() {

    FILE *arquivoUsuarios;
    FILE *arquivoAutomoveis;
    int opcao = 0;
    int j = 0;
    int k = 0;
    int quantidadeUsuarios;
    int id;
    
    //Início do programa
    

    while (opcao != 3) {
        abertura();
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                printf("Quantas pessoas serão cadastradas? ");
                scanf("%d", &quantidadeUsuarios);
                for(int k = 0; k < quantidadeUsuarios; k++){
                /*Usando o modo de abertura "ab", significa "append" (anexar). 
                Isso indica que o arquivo será aberto no modo de escrita de anexação, 
                onde novos dados serão acrescentados ao final do arquivo, 
                preservando os dados existentes.*/
                arquivoUsuarios = fopen("FichasUsuarios.bin", "ab");
                arquivoAutomoveis = fopen("FichasAutomoveis.bin", "ab");

                printf("Digite o nome completo do usuário: ");
                scanf(" %[^\n]", usuario.nomeCompleto);
                printf("Digite o CPF do usuário: ");
                scanf(" %s", usuario.cpf);
                printf("Digite o telefone do usuário: ");
                scanf(" %s", usuario.telefone);

                printf("Quantos carros esse usuário possui? ");
                scanf("%d", &usuario.quantidadeAutomoveis);

                for(int j = 0; j < usuario.quantidadeAutomoveis; j++){
                    printf("Digite o número de registro do Automóvel: ");
                    scanf(" %[^\n]", carro.numDeRegistroDoVeiculo);

                    printf("Digite a marca do Automóvel: ");
                    scanf(" %[^\n]", carro.marca);

                    printf("Digite o modelo do Automóvel: ");
                    scanf(" %[^\n]", carro.modelo);

                    printf("Digite o ano do Automóvel: ");
                    scanf(" %[^\n]", carro.ano);

                    printf("Digite a cor do Automóvel: ");
                    scanf(" %[^\n]", carro.cor);

                    printf("Digite a placa do Automóvel: ");
                    scanf(" %[^\n]", carro.placa);
                    strcpy(usuario.carros[j], carro.placa);
                    /*um elemento específico no array de strings carros 
                    dentro da estrutura usuario.*/
                            
                    fwrite(&carro,1, sizeof(FichaDoCarro), arquivoAutomoveis);
                    /*Usando a função fwrite para escrever os dados de uma variável do tipo 
                    FichaDoCarro (sendo o tipo de estrutura que define os detalhes de um carro) 
                    no arquivo arquivoAutomoveis*/
                }
                fwrite(&usuario,1, sizeof(FichaDoUsuario), arquivoUsuarios);
                /*Usando a função fwrite para escrever os dados de uma variável do tipo 
                FichaDoUsuario (sendo o tipo de estrutura que define os detalhes de um usuário) 
                no arquivo arquivoUsuarios*/

                fclose(arquivoUsuarios);
                fclose(arquivoAutomoveis);
            }
            printf("\n\nUsuário cadastrado\n\n");
            break;
        case 2:
            arquivoUsuarios = fopen("FichasUsuarios.bin", "rb");
            arquivoAutomoveis = fopen("FichasAutomoveis.bin", "rb");
            /*Usando o modo de abertura "rb", significa "read" (leitura). 
            Isso indica que o arquivo será aberto no modo de leitura, 
            permitindo que leia o conteúdo do arquivo.*/

            char nomeBusca[100];
            int usuarioEncontrado = 0;

            printf("Digite o nome completo do usuário: ");
            scanf(" %[^\n]", nomeBusca);

            while (fread(&usuario, sizeof(FichaDoUsuario), 1, arquivoUsuarios)) {
                if (strcmp(nomeBusca, usuario.nomeCompleto) == 0) {
                    usuarioEncontrado = 1;

                    printf("---------------------------\n");
                    printf("- Nome Completo: %s \n- Telefone: %s \n- CPF: %s \n- Carros:\n", usuario.nomeCompleto, usuario.telefone, usuario.cpf);
                    for (int j = 0; j < usuario.quantidadeAutomoveis; j++) {
                        printf("-> %s\n", usuario.carros[j]);

                        // Procurar o carro correspondente no arquivo de automóveis
                        fseek(arquivoAutomoveis, 0, SEEK_SET);
                        while (fread(&carro, sizeof(FichaDoCarro), 1, arquivoAutomoveis)) {
                            if (strcmp(usuario.carros[j], carro.placa) == 0) {
                                printf("   Detalhes do carro:\n");
                                printf("   Número de Registro: %s \n   Marca: %s\n   Modelo: %s\n   Ano: %s\n   Cor: %s\n   Placa: %s\n",
                                    carro.numDeRegistroDoVeiculo, carro.marca, carro.modelo, carro.ano, carro.cor, carro.placa);
                                printf("---------------------------\n");
                            }
                        }
                    }
                }
            }
            if (!usuarioEncontrado) {
                printf("Usuário não encontrado.\n");
            }
                    
            fclose(arquivoUsuarios);
            fclose(arquivoAutomoveis);
            break;

            default:
                break;
        }
        if (opcao == 3) {
            printf("Obrigada por usar o programa! - Abritta\n");
            break; // Saída do loop após a opção 3 ser escolhida
        }

    }
    return 0;
}