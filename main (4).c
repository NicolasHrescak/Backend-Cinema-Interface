#include <stdio.h>                                  
#include <stdlib.h> //Professor, deixo aqui desde já esclarecido que tivemos algumas dúvidas bem grandes em relação as matrizes Platéia (chamada de matriz durante o código)                                                                                                                                                      
#include <string.h> //e a matriz Ocupação (chamada de matrizOcupacao) durante o código, durante o seu arquivo de exemplo o senhor chama a todo momento que o arquivo                                                                                                                                                         
#include <ctype.h>  //deveria chamar a matriz Platéia (que é a numérica) no entanto quando o senhor a chama no seu exemplo a matriz que aparece é a matriz Ocupação (a de -)                                                                                                                                                                
                    //e não a numérica, ficamos em duvida com a qual deveriamos manipular e mesmo após perguntar para o senhor no canvas não nos foi sanado a nossa dúvida.   
                    //Optamos por manipular a matrizOcupacao como a do exemplo do arquivo do projeto
                    
// Função para criar uma matriz m x n
int** criaMatriz(int m, int n) {
    int **matriz = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        matriz[i] = (int *)malloc(n * sizeof(int));
    }
    return matriz;
}

void encerra(char *mensagem) {
    printf("%s\n", mensagem);
    exit(1);
}

void iniPlateia(FILE *fp, char **matrizOcupacao, int m, int n) {    //funcao pega do exemplo do professor como pedido no slide
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            fprintf(fp, "-"); /* Escreve '-' em cada posição da matriz */
            matrizOcupacao[i][j] = '-'; /* Inicializa a matriz com '-' */
        }
        fprintf(fp, "\n"); /* Pula linha no arquivo */
    }
}

    
void carregaPlateia(char nomeArq[], char **p, int m, int n) {       //funcao pega do exemplo do professor como pedido no slide
    int i, j;
    FILE *fp; /* Ponteiro para o arquivo de plateia. */
    if ((fp = fopen(nomeArq, "r")) == NULL) { /* Tenta abrir. */
        /* Se não encontrou o arquivo, ele é criado com a opção "w+". */
        if ((fp = fopen(nomeArq, "w+")) == NULL) /* Verifica criação. */
            encerra("Falha na criacao do arquivo de plateia!");
        /* Inicializa plateia nova (gravação), fecha e reabre para leitura. */
        iniPlateia(fp, p, m, n); /* Uma função que escreve no arquivo a matriz inicial. */
        fclose(fp); /* Fecha arquivo: grava dados e disponibiliza para outro uso. */
        if ((fp = fopen(nomeArq, "r")) == NULL) /* Reabre para leitura da matriz inicial. */
            encerra("Falha na abertura do arquivo de plateia!");
        printf("Primeiro acesso ao programa: arquivo de plateia criado\n");
    }
    /* Lê o arquivo e carrega os dados (atualiza) a matriz plateia. */
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            fscanf(fp, " %c", &p[i][j]);
        }
    }
    fclose(fp); /* Fecha o arquivo (garante a gravação da matriz inicial). */
}

// Função para liberar a memória da matriz
void liberaMatriz(int **matriz, int m) {
    for (int i = 0; i < m; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// Função para liberar a memória da matriz de caracteres
void liberaMatrizCaract(char **matriz, int m) {
    for (int i = 0; i < m; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// Função para limpar o buffer de entrada
void limpaBuffer() { 
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int input0a4(const char *frase) { //função que verifica apenas valores de 0 a 4 para o MENU.
    char input[50];
    int verifica, valor;

    do {
        verifica = 1;

        printf("%s", frase);
        scanf("%s", input);
        limpaBuffer();

        // Verifica se todos os caracteres são dígitos
        for (int i = 0; i < strlen(input); i++) {
            if (!isdigit(input[i])) {
                verifica = 0;
                break;
            }
        }

        if (verifica) {
            valor = atoi(input);
            if (valor < 0 || valor > 4) {
                verifica = 0;
            }
        }

        if (!verifica) {
            printf("Entrada inválida. Por favor, digite um número entre 0 e 4.\n");
        }

    } while (!verifica);

    return valor;
}

int input1a120(const char *frase) { //função para validar numeros de 1 a 120 para validar as POLTRONAS
    char input[50];
    int verifica, valor;

    do {
        verifica = 1;

        printf("%s", frase);
        scanf("%s", input);
        limpaBuffer();

        // Verifica se todos os caracteres são dígitos
        for (int i = 0; i < strlen(input); i++) {
            if (!isdigit(input[i])) {
                verifica = 0;
                break;
            }
        }

        if (verifica) {
            valor = atoi(input);
            if (valor < 1 || valor > 120) {
                verifica = 0;
            }
        }

        if (!verifica) {
            printf("Entrada inválida. Por favor, digite um número entre 1 e 120.\n");
        }

    } while (!verifica);

    return valor;
}

void atualizaPlateia(char **matrizOcupacao, int **matriz, int *meia, int *inteira, int *ingressos, int m, int n) { //Funcao que serve para atualizar a ocupacao caso ja exista algo
    for (int i = 0; i < m; i++) {                                                                                   // escrito no arquivo
        for (int j = 0; j < n; j++) {
            if(matrizOcupacao[i][j]!='m'&& matrizOcupacao[i][j] != 'M' && matrizOcupacao[i][j] != 'i' && matrizOcupacao[i][j] != 'I' &&matrizOcupacao[i][j] != '-'){
            printf("O arquivo possui caracteres estranhos diferente dos permitidos, será contabilizando como poltrona vazia ( - ) suas posições!\n");
            matrizOcupacao[i][j] = '-'; //Este if serve para verificar caso exista caracteres diferentes dos permitidos, caso existe será transformado em - (poltrona vazia)
            } 
            if (matrizOcupacao[i][j] == 'm' || matrizOcupacao[i][j] == 'M') {
                (*meia)++;
                (*ingressos)++;
                matriz[i][j] = 0; // Marca a poltrona como ocupada com espaço
            } else if (matrizOcupacao[i][j] == 'i' || matrizOcupacao[i][j] == 'I') {
                (*inteira)++;
                (*ingressos)++;
                matriz[i][j] = 0; // Marca a poltrona como ocupada com espaço
            }
        }
    }
}

void atualizaArquivo(char nomeArq[], char **matrizOcupacao, int m, int n) { //Funcao que serve para atualizar o arquivo após algo ser alterado na matrizes de caracteres(ocupacao)
    FILE *fp = fopen(nomeArq, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(fp, "%c ", matrizOcupacao[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

int main() {
    int m = 10;
    int n = 12;
    int **matriz = criaMatriz(m, n);
    char **matrizOcupacao;
    char nomeArq[] = "plateia.txt";
    int i = 1;
    char condicao;
    char tipo = ' ';
    int meia = 0;
    int inteira = 0;
    int ingresso = 0;
    int quociente;
    int resto;
    int devolvePol;
    char poltrona; 
    int decisao = 1;
    
     // Inicializa a matriz dos lugares
    for (int k = 0; k < m; k++) {
        for (int j = 0; j < n; j++) {
            matriz[k][j] = i++;
        }
    }
    
    matrizOcupacao = (char **)malloc(m * sizeof(char *)); //Alocando memória para a matriz da ocupação 
    for (int i = 0; i < m; i++){
        matrizOcupacao[i] = (char *)malloc(n * sizeof(char));
    }
    
    carregaPlateia(nomeArq, matrizOcupacao, m, n); //Carregamento da 1° vez do arquivo
    atualizaPlateia(matrizOcupacao, matriz, &meia, &inteira, &ingresso, m, n); //Chamada para verificar se ja existe algo no arquivo

    while (1) {
        printf("--------------------------------\n");
        printf("              MENU              \n");
        printf("--------------------------------\n");

        printf("0 - Sair do Programa\n1 - Mostrar Plateia\n2 - Mostrar Ocupação\n3 - Vender Ingresso\n4 - Devolução\n");
        printf("--------------------------------\n");
        
        condicao = input0a4("Escolha uma opcão "); // Ok funcionando

        switch (condicao) {
            case 0:
                printf("Obrigado por usar o sistema!\n");
                atualizaArquivo(nomeArq, matrizOcupacao,  m,  n);// Necessário para caso alguem inicie o código com o arquivo aberto com caracteres estranhos, não use nenhuma
                                                                //opção e já feche novamente com o zero, pois do contrário no arquivo não seria escrito por cima com (-)
                liberaMatriz(matriz, m);
                liberaMatrizCaract(matrizOcupacao, m);
                return 0;

            case 3: 
                printf("--- Venda de ingressos Cinema 'Ciber'\n\n");
                printf("Ocupação da sala:\n");
                for (int k = 0; k < m; k++) {
                    for (int j = 0; j < n; j++) {
                        if (matriz[k][j] == 0){
                            printf("     ");
                        }
                        else
                            printf("%3d ", matriz[k][j]);
                    }
                    printf("\n");
                }
                do{

                   poltrona = input1a120("Escolha sua poltrona <1..120>: ");
                        quociente = (poltrona - 1) / 12; //Esquema para organizar corretamente as linhas e colunas pois como vetores começam no índice zero, é necessário o calculo
                        resto = (poltrona - 1) % 12;

                        if (matrizOcupacao[quociente][resto] != '-') {
                            printf("Este lugar está ocupado, escolha outro\n");
                        } else {
                            printf("O lugar não está ocupado, prosseguindo...\n");
                            
                        //

                ingresso++;
                for (int k = 0; k < m; k++) {
                    for (int j = 0; j < n; j++) {
                        if (matriz[k][j] == poltrona) {
                            matriz[k][j] = 0; // Marca a poltrona como ocupada com espaço
                            
                        }
                    }
                }

                while (tipo != 'm' && tipo != 'M' && tipo != 'i' && tipo != 'I') {
                    printf("Qual é o tipo de ingresso? m para meia e i para inteira: ");
                    scanf(" %c", &tipo);
                    if (tipo == 'm' || tipo == 'M') {
                        matrizOcupacao[quociente][resto] = 'm';
                        meia++;
                    } else if (tipo == 'i' || tipo == 'I') {
                        matrizOcupacao[quociente][resto] = 'i';
                        inteira++;
                    } else {
                        printf("Tipo de ingresso inválido, tente novamente\n");
                    }
                }
                tipo = ' ';
                
                atualizaArquivo(nomeArq, matrizOcupacao,  m,  n);
                
                        }
                
                printf("Deseja comprar mais algum ingresso? 0 para não e 1 para sim\n");
                do{
                    scanf("%d",&decisao);
                    if(decisao!=0 && decisao!= 1){
                        printf("Coloque um valor válido!\n");
                    }
                }while(decisao!=0 && decisao!=1);
            
            }while(decisao==1);
            break;

            case 1:
                printf("Plateia\n");
                printf("-----------------------------------------------\n");

                for (int k = 0; k < m; k++) {
                    for (int j = 0; j < n; j++) {
                        if (matriz[k][j] == 0) // Verifica se o vetor é igual a zero e se for, imprime o lugar vazio
                            printf("    ");
                        else
                            printf("%3d ", matriz[k][j]);
                    }
                    printf("\n");
                }
                printf("-----------------------------------------------\n");
                printf("FIM DA PLATEIA\n");

                break;

            case 2:
                printf("--- Relatório de ocupação ---\n");
                for (int k = 0; k < m; k++) {
                    for (int j = 0; j < n; j++) {
                        printf("%3c ", matrizOcupacao[k][j]);
                    }
                    printf("\n");
                }
                printf("A plateia possui 120 lugares\n");
                printf("Foram vendidos %d ingressos, sendo\n%d - meias\n%d - inteiras\n", ingresso, meia, inteira);
                printf("\n");
                break;
                
            case 4:
            do{
                    poltrona = input1a120("Qual é a poltrona que você deseja devolver? ");
                    
                    quociente = (poltrona - 1) / 12;
                    resto = (poltrona - 1) % 12;
                    
                    if(matriz[quociente][resto]==0){
                        if(matrizOcupacao[quociente][resto] == 'm'|| matrizOcupacao[quociente][resto] == 'M'){
                            meia--;
                    }
                        if(matrizOcupacao[quociente][resto] == 'i'|| matrizOcupacao[quociente][resto] == 'I'){
                            inteira--;
                    }
                        ingresso--;
                        matrizOcupacao[quociente][resto]='-';
                        matriz[quociente][resto]=poltrona;
                        printf("Ingresso Devolvido!\n");
                    }
                    else{
                            printf("Este lugar não está ocupado para devolver!\n");

                    }
                atualizaArquivo(nomeArq, matrizOcupacao,  m,  n);    
                printf("Deseja devolver mais algum ingresso? 0 para não e 1 para sim\n");
                do{
                    scanf("%d",&decisao);
                    if(decisao!=0 && decisao!= 1){
                        printf("Coloque um valor válido!\n");
                    }
                }while(decisao!=0 && decisao!=1);

            }while(decisao == 1);
            break;
        
        }
    }
    printf("\nObrigado por usar o sistema!");

    return 0;
}

