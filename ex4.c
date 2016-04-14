#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct st_lista
{
    char linha[1000];
    int nota;
    int status;//status-> se ja foi lido
    struct st_pilha *prox;
} lista;

int main(void) {
    srand(time(NULL));
    FILE *arquivo;
    arquivo = fopen("special-1500-words.txt", "r");
    int i=-1;
    if(arquivo==NULL)
    {
        printf("A biblioteca não foi encontrada por favor, coloque o arquivo da biblioteca no mesmo local do arquivo e reinicie.\n");
    }
    else
    {
        int quant_linhas = 0;
        char caractere;
        while(!feof(arquivo))
        {   
            caractere = fgetc(arquivo);
            if(caractere == '\n'){ // é uma quebra de linha?
                quant_linhas++;             
            } 
        }
        lista matadora[quant_linhas];
        rewind(arquivo);
        do
        {
            i++;
            fgets(matadora[i].linha, sizeof(matadora[i].linha), arquivo);
            printf("%s\n", matadora[i].linha);
        }while(!feof(arquivo));
    }
    fclose(arquivo);

    return 0;
}
