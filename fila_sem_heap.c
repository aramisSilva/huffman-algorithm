#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct no{
    int item;
    int prioridade;
    struct no *next;
}NO;

typedef struct Fila{
    struct no *head;
}FILA;

FILA* criar_fila_vazia()
{
    FILA *novo_no = (FILA*) malloc(sizeof(FILA));
    novo_no->head= NULL;
    return novo_no;
}

void enfileirar(FILA *pq, int item, int prioridade, FILE* arquivo){
    NO *novo_no = (NO*) malloc(sizeof(NO));
    novo_no->item = item;                                  // colocar tudo separado em funções.
    novo_no->prioridade = prioridade;                      // explicar besteiras com comentários no código do huffman
    int contador = 0;
    if((pq->head==NULL) || novo_no->prioridade > pq->head->prioridade){
        novo_no->next = pq->head;
        pq->head = novo_no;
    }
    else{
        NO *atual = pq->head;
        contador = 1;
        while((atual->next != NULL) && atual->next->prioridade > prioridade){
            atual = atual->next;
            contador++;
        }
        novo_no->next = atual->next;
        atual->next = novo_no;
    }
    fprintf(arquivo, "%d\n", contador);
}

NO* desenfileirar(FILA *pq){
    if(pq->head==NULL){
        return NULL;
    }
    else{
        NO *no = pq->head;
        pq->head = pq->head->next;
        no->next = NULL;
        return no;
    }
}

void print(FILA *no){
    NO *atual = no->head;
    printf("\n");
    while(atual->next != NULL){
        printf("%d ", atual->item);
        atual = atual->next;
    }
    printf("%d\n", atual->item);
}

int procurar(FILA* no, int item, int comparacoes){
    while(no->head->next !=NULL){
        if(no->head->item == item){
            comparacoes++;
            return comparacoes;
        }
        comparacoes++;
        no->head = no->head->next;
    }
}

int procurar2(FILA* no, int t){
    char nome[100];
    FILE* arquivo = fopen("dados.txt","wt");
    char str[100];
    int i;
    for(i=1;i<=t;i++){
        sprintf(str,"%d ",i);
        //strcat(str, " gol ");
        //sprintf(str,"%d\n", procurar(no,no->head->item,0));
        //strcat(str,"\n");
    }
    fputs(str,arquivo);
    fclose(arquivo);
}

/*int analise(FILA *no, int t){
    printf("\nDigite:\n1-Procurar\n2-Enfileirar\n3-Desenfileirar\n4-Imprimir a no\n5-Fechar Programa\n\n");
    int valor;
    scanf("%d", &valor);
    if(valor==1){
        procurar2(no,t);
        analise(no,t);
    }
    else if(valor==2){
        int item, prioridade;
        printf("Digite o item:");
        scanf("%d", &item);
        printf("Digite a prioridade:");
        scanf("%d", &prioridade);
        enfileirar(no,item,prioridade);
        analise(no,t);
    }
    else if(valor==3){
        desenfileirar(no);
        analise(no,t);
    }
    else if(valor==4){
        print(no);
        analise(no,t);
    }
    else if(valor==5){
        return 0;
    }
    else{
        printf("ERRO, VOLTE AO INICIO\n");
        analise(no,t);
    }
}*/

int main(){
    FILE *fp;
    fp = fopen ("auau", "w");
    FILA *no = (FILA*) malloc(sizeof(FILA));
    no = criar_fila_vazia();
    int i;
    int size = 20;
    for(i=25;i>=1;i--){
        enfileirar(no,i,i,fp);
    }
    //analise(no,size);
    return 0;
}
