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
    printf("2 - Listar Usuários e Automóveis por CPF.\n");
    printf("3 - Listar Usuários e Automóveis por nome.\n");
    printf("4 - Sair do programa\n");
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

FILE *Verificacao;
FichaDoUsuario verificado;

FichaDoUsuario total[100]; //Instância da estrutura FichaDoUsuario, 
//que contém as informações de um usuário

int verificaCPF (const void *x, const void *y){
    return strcmp(((FichaDoUsuario *)x)->cpf, ((FichaDoUsuario*)y)-> cpf);
}
/*verificaCPF aceita dois argumentos. São x e y, são ponteiros

(FichaDoUsuario *)x e (FichaDoUsuario *)y estão convertendo os 
ponteiros x e y em ponteiros do tipo FichaDoUsuario, presumindo que 
esses ponteiros apontam para objetos

((FichaDoUsuario *)x)->cpf e ((FichaDoUsuario *)y)->cpf estão acessando 
o campo cpf dos objetos FichaDoUsuario apontados pelos ponteiros x e y

strcmp é uma função que compara duas strings (ou neste caso, dois CPFs) 
e retorna um valor inteiro que indica se as strings são iguais ou qual delas 
é maior em ordem alfabética

Resultado: A função verificaCPF retorna o resultado da comparação dos CPFs 
usando strcmp. Se os CPFs forem iguais, a função retornará 0. Se o CPF em x 
for menor do que o CPF em y, ela retornará um valor negativo. Se o CPF em x 
for maior do que o CPF em y, ela retornará um valor positivo.
*/

int verificaNomeUsuario (const void *x, const void *y){
    return strcmp(((FichaDoUsuario *)x)->nomeCompleto, ((FichaDoUsuario *)y)-> nomeCompleto);
}

int cpfValido(char vetorCpf[11]){
    Verificacao = fopen("FichasUsuarios.bin", "rb");
    while(fread(&verificado, sizeof(FichaDoUsuario), 1, Verificacao)){
        if(strcmp(vetorCpf, verificado.cpf) == 0){
            return 1;
        }
    }
    fclose(Verificacao);
    return 0;
}
/*int cpfValido(char vetorCpf[11]): Define a função cpfValido, que recebe 
um único argumento, vetorCpf, que é um array de caracteres (string) contendo u
m CPF de 11 dígitos. 

Verificacao = fopen("FichasUsuarios.bin", "rb");: Abre o arquivo chamado 
"FichasUsuarios.bin" em modo de leitura binária ("rb"). O arquivo é 
associado a um ponteiro de arquivo chamado Verificacao.

while(fread(&verificado, sizeof(FichaDoUsuario), 1, Verificacao)): É um loop 
while que lê registros do arquivo binário e armazena os dados lidos na 
estrutura verificado, que é do tipo FichaDoUsuario. Ele lê 1 registro por vez.

if(strcmp(vetorCpf, verificado.cpf) == 0): Dentro do loop, compara o CPF 
(vetorCpf) fornecido como argumento com o CPF lido da estrutura verificado. 
Se eles forem iguais (a função strcmp retorna 0 quando as strings são iguais), 
a função retorna 1, o que geralmente indica que o CPF é válido e já existe no 
arquivo.
*/

//!!HERE

void ordemCpf() {
    int i = 0;
    Verificacao = fopen("FichasUsuarios.bin", "rb");
    while(fread(&total[i], sizeof(FichaDoUsuario), 1, Verificacao)){
        i++;
    }

    qsort(total, i, sizeof(FichaDoUsuario), verificaCPF);
    fclose(Verificacao);

    Verificacao = fopen("FichasUsuarios.bin", "wb");
    int tamanho = 0;
    while(tamanho < i){
        fwrite(&total[tamanho], 1, sizeof(FichaDoUsuario), Verificacao);
        tamanho++;
    }

    fclose(Verificacao);
}

void ordemNome() {
    int i = 0;
    Verificacao = fopen("FichasUsuarios.bin", "rb");
    while(fread(&total[i], sizeof(FichaDoUsuario), 1, Verificacao)){
        i++;
    }

    qsort(total, i, sizeof(FichaDoUsuario), verificaCPF);
    fclose(Verificacao);

    Verificacao = fopen("FichasUsuarios.bin", "wb");
    int tamanho = 0;
    while(tamanho < i){
        fwrite(&total[tamanho], 1, sizeof(FichaDoUsuario), Verificacao);
        tamanho++;
    }

    fclose(Verificacao);
}

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
    int indice = 0;
    char verificaCPF[11];
    int verificaCarro;
    int quantidadeUsuarios;
    int id;
    
    //Início do programa
    

    while (opcao != 4) {
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

                //!!HERE
                printf("Digite o nome completo do usuário: ");
                scanf(" %[^\n]", usuario.nomeCompleto);
                printf("Digite o CPF do usuário: ");
                scanf(" %s", verificaCPF);

                while(strlen(verificaCPF) != 11){
                    printf("CPF inválido! Não possui 11 dígitos! Por favor, digite um CPF válido.\n");
                    scanf(" %s", verificaCPF);
                }

                while(cpfValido(verificaCPF)){
                    printf("Já existe uma pessoa com esse CPF cadastrada. Digite outro CPF válido!\n");
                    scanf(" %s", verificaCPF);
                }

                strcpy(usuario.cpf, verificaCPF); //!!

                printf("Digite o telefone do usuário: ");
                scanf(" %s", usuario.telefone);

                printf("Quantos carros esse usuário possui? ");
                scanf("%d", &verificaCarro);

                while(verificaCarro == 0){
                    printf("É impossível cadastrar usuários sem carros, por favor, que digite um número maior que 0\n");
                    scanf("%d", &verificaCarro);
                }

                usuario.quantidadeAutomoveis = verificaCarro;

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

                ordemCpf();

                printf("Usuários cadastradas: \n");
                    while(fread(&usuario, sizeof(FichaDoUsuario), 1, arquivoUsuarios)){
                        printf("----------------------\n");
                        printf("- Nome Completo: %s \n- Telefone: %s \n- CPF: %s \n- Carros:\n", usuario.nomeCompleto, usuario.telefone, usuario.cpf);                        
                        for(int j = 0; j < usuario.quantidadeAutomoveis; j++){
                            printf("-> %s\n", usuario.carros[j]);
                        }
                        printf("----------------------\n");
                    }

                printf("Automóveis cadastrados: \n");
                while(fread(&carro, sizeof(FichaDoCarro), 1, arquivoAutomoveis)){
                        printf("----------------------\n");
                        printf("   Número de Registro: %s \n   Marca: %s\n   Modelo: %s\n   Ano: %s\n   Cor: %s\n   Placa: %s\n",
                                    carro.numDeRegistroDoVeiculo, carro.marca, carro.modelo, carro.ano, carro.cor, carro.placa);                
                }
                printf("----------------------\n");
                
                fclose(arquivoUsuarios);
                fclose(arquivoAutomoveis);

                break;
            case 3:
                arquivoUsuarios = fopen("FichasUsuarios.bin", "rb");
                arquivoAutomoveis = fopen("FichasAutomoveis.bin", "rb");
                /*Usando o modo de abertura "rb", significa "read" (leitura). 
                Isso indica que o arquivo será aberto no modo de leitura, 
                permitindo que leia o conteúdo do arquivo.*/

                ordemNome();

                printf("Usuários cadastradas: \n");
                    while(fread(&usuario, sizeof(FichaDoUsuario), 1, arquivoUsuarios)){
                        printf("----------------------\n");
                        printf("- Nome Completo: %s \n- Telefone: %s \n- CPF: %s \n- Carros:\n", usuario.nomeCompleto, usuario.telefone, usuario.cpf);                        
                        for(int j = 0; j < usuario.quantidadeAutomoveis; j++){
                            printf("-> %s\n", usuario.carros[j]);
                        }
                        printf("----------------------\n");
                    }

                printf("Automóveis cadastrados: \n");
                while(fread(&carro, sizeof(FichaDoCarro), 1, arquivoAutomoveis)){
                        printf("----------------------\n");
                        printf("   Número de Registro: %s \n   Marca: %s\n   Modelo: %s\n   Ano: %s\n   Cor: %s\n   Placa: %s\n",
                                    carro.numDeRegistroDoVeiculo, carro.marca, carro.modelo, carro.ano, carro.cor, carro.placa);                
                }
                printf("----------------------\n");
                
                fclose(arquivoUsuarios);
                fclose(arquivoAutomoveis);

                break;
            default:
                break;
        }
        if (opcao == 4) {
            printf("Obrigada por usar o programa! - Abritta\n");
            break; // Saída do loop após a opção 3 ser escolhida
        }

    }
    return 0;
}