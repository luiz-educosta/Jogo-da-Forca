#include <stdio.h>
#include <string.h>
#include "forca.h"
#include <time.h>
#include <stdlib.h>


//variaveis globais
char palavrasecreta[TAMANHO_PALAVRA];
char chutes[TAMANHO_PALAVRA];
int chutesdados = 0;

void abertura(){
    printf("************************\n");
    printf("*     Jogo de Forca    *\n");
    printf("************************\n\n");
}

void chuta(){
    char chute;
    scanf(" %c", &chute);//dar espaço antes de colocar o %c para limpar o buffer
    chutes[chutesdados] = chute;
    chutesdados++;

}

int jachutou(char letra){
   
    int achou = 0;

    for (int j = 0; j < chutesdados; j++){
        if(chutes[j] == letra){
            achou = 1;
            break;
          }
    }

    return achou;
}

void desenhaforca(){

    int erros;

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));//utilizando if ternario
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

        for (int i = 0; i < strlen(palavrasecreta); i++){
          
            int achou = jachutou(palavrasecreta[i]);

            if (achou) {
                printf("%c ", palavrasecreta[i]);
            } else{
                printf("_");
            }
            
        }
        printf("\n");

}

void adicionapalavra(){

    char palavraparaadicionar;

    printf("Você deseja adicionar uma nova palavra no jogo? (S/N)\n");
    scanf(" %c", &palavraparaadicionar);

    if (palavraparaadicionar == 'S'){
        
        char novapalavra[TAMANHO_PALAVRA];

        printf("Qual a nova palavra que você deseja adicionar?\n");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");

        //tratamento se o arquivo estiver com erro
        if (f == 0 ) {
        printf("Desculpe, banco de dados não disponivel.\n\n");
        exit(1);
        }
        //lendo o número da primeira linha
        int qtd;

        fscanf(f, "%d", &qtd);
        qtd++;

        //posicionando a seta do FILE para o começo do arquivo
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd); //escrevendo por cima do número que estava indicando as palavras

        //posicionando a seta do FILE para o fim do arquivo
        fseek(f, 0, SEEK_END);
        fprintf(f,"\n%s", novapalavra);

        fclose(f);
    }
}

void escolhepalavra(){
    FILE* f;
    
    //abriu o arquivo
    f = fopen("palavras.txt","r");

    //tratamento se o arquivo estiver com erro
    if (f ==0 ) {
        printf("Desculpe, banco de dados não disponivel.\n\n");
        exit(1);
    }

    //a primeira linha vai ler quantas palavras tem
    int qntddepalavras;
    fscanf(f,"%d", &qntddepalavras);

    //gerando as palavras aleatórias
    srand(time(0));
    int randomico = rand() % qntddepalavras;

    for (int i = 0; i <= randomico; i++){
        fscanf(f,"%s", palavrasecreta);
    }

    fclose(f);
}

int acertou(){
    for(int i = 0; i < strlen(palavrasecreta); i++){
        if(!jachutou(palavrasecreta[i])){
            return 0;
        }
    }

    return 1;
}

int chuteserrados(){
    int erros = 0;

    for(int i = 0; i< chutesdados; i++){
        int existe = 0;

        for(int j = 0; j < strlen(palavrasecreta); j++){
            if (chutes[i] == palavrasecreta[j]){

                existe = 1;
                break;
            }
        }

        if(!existe) erros++;
    }

    return erros;
}

int enforcou(){
      
    return chutesdados() >= 5;
}

int main (){

    escolhepalavra();

    abertura();

    do {

        desenhaforca();

        chuta();

    } while (!acertou() && !enforcou());
   
    if (acertou()){
        printf("Você acertou a palavra, parabéns!!\n");
    }else{
        printf("Você perdeu! Tente na próxima!\n");
        printf("A palavra era:**%s**\n", palavrasecreta);
    }
    
    
    

}