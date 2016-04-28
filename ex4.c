/* EXERCICIO PARA DESENVOLVIMENTO DE UM METODO DE APRENDIZAGEM POR REPETICAO
 *
 * ALUNOS: Bruna Hori
 *         Jorge Edson Ribeiro 
 *         Joao Gabriel Gouveia
 *         Silas Marinho
 *
 *PROFESSOR ORIENTADOR: Dr. Ruben Carlo Benante
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int quant_linhas=0, linhas_enable=0;;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(void);
void sorteio(void);
void grava_data(void);
void nlinhas(void);

int main(void) {
    srand(time(NULL));
    grava_data();    
    sorteio();
    return 0;
}

void sorteio()
{
    int aleatorio=0, nota=0, x;
    FILE *arquivo;
    arquivo = fopen("special-1500-words.txt", "r");
    int i=0;
    if(arquivo==NULL)
    {
        printf("A biblioteca nao foi encontrada, por favor, coloque o arquivo da biblioteca no mesmo local do arquivo e reinicie.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        if(linhas_enable==0)
            nlinhas();
        char string[1000];
        char *pergunta;
        for(x=0;x<10;x++)
        {
            aleatorio= 1+rand()%quant_linhas;
            for(i=0;i<aleatorio;i++)
                fgets(string, sizeof(string), arquivo);
            pergunta=strtok(string, "::");
            printf("\nA Pergunta %d do banco de dados eh: %s\n", i, pergunta);
            printf("Pressione alguma tecla para continuar e ver a resposta... \n");
            __fpurge(stdin);
            getchar();
            pergunta=strtok(NULL, ":");
            printf("A resposta eh: %s\n", pergunta);
            printf("De uma nota a pergunta de 0 a 5: ");
            scanf("%d", &nota);
            grava_palavras(i, nota);
            rewind(arquivo);
        }
    }

    fclose(arquivo);
}

void grava_palavras(int _palavra, int _nota) /* funcao que grava a palavra*/

{
    FILE *palavrinha;
    palavrinha = fopen("palavras.txt", "a");
    fprintf(palavrinha, "%d %d\n", _palavra, _nota);      
}

void grava_data()
{
    char tempo[8], data[8];
    FILE *p;
    p = fopen("timeini.txt", "r+");
    if(p==NULL)
    {
        int dia, mes, ano;
        p=fopen("timeini.txt", "w");
        struct tm *local;
        time_t t;
        t= time(NULL);
        local=localtime(&t);
        dia=local->tm_mday;
        mes=local->tm_mon+1;
        ano=local->tm_year+1900;
        fprintf(p, "%d/%d/%d %s", dia, mes, ano, __TIME__);
    }
    else
    {
        fscanf(p, "%s" "%s", data, tempo);
        printf("Você ja comecou o teste, no dia %s, as %s\n", data, tempo);
    }
    fclose(p);
}

void nlinhas()
{
    char caractere;
    FILE *o, *w;
    o = fopen("special-1500-words.txt", "r");
    w = fopen("consulta_nota.txt", "r");
    while(!feof(o))
    {
        caractere = fgetc(o);
        if(caractere == '\n'){ /* eh uma quebra de linha?*/
            quant_linhas++;
        }
    }
    if(w==NULL)
    {
        w=fopen("consulta_nota.txt","w");
        int j;
        for(j=0;j<quant_linhas;j++)
            fprintf(w,"%d\n", j);
        fclose(w);
    }
    rewind(o);
    fclose(o);
    linhas_enable=1;
}

void computar(int linha, int nota)
{
    FILE *y;
    y = fopen("consulta_nota.txt", "r+");
    char caractere;
    int line=0;
    do
    {
        caractere=fgetc(y);
        if(caractere=='\n')
            line++;
    }while(linha!=line);
    fprintf(y, "%d %d", linha, nota);
    fclose(y);

}

