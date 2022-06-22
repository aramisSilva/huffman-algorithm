#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX 200

typedef struct paciente{
    int item;
    int prioridade;
}PACIENTE;

typedef struct fila_prioridade{
    int quantidade;
    PACIENTE dados[MAX];
}FILA_PRIO;

FILA_PRIO* criar_Fila()
{
    FILA_PRIO *fila;
    fila = (FILA_PRIO*) malloc(sizeof(FILA_PRIO));
    if(fila != NULL)
        fila->quantidade = 0;
    return fila;
}

void promoverElemento(FILA_PRIO* fila, int filho, FILE* arquivo){
    int contador = 0;
    int pai;
    struct paciente temp;
    pai = (filho - 1) / 2;
    while((filho > 0) && (fila->dados[pai].prioridade <= fila->dados[filho].prioridade)){
        temp = fila->dados[filho];
        fila->dados[filho] = fila->dados[pai];
        fila->dados[pai] = temp;

        filho = pai;
        pai = (pai - 1) / 2;

        contador++;
    }
    fprintf(arquivo, "%d\n", contador);
    fflush(arquivo);
}

int enfileirar(FILA_PRIO* fila, int item, int prioridade, FILE* arquivo){
    if(fila == NULL)
        return 0;
    if(fila->quantidade == MAX)//fila cheia
        return 0;
    fila->dados[fila->quantidade].item = item;
    fila->dados[fila->quantidade].prioridade = prioridade;
    promoverElemento(fila,fila->quantidade, arquivo);
    fila->quantidade++;
    return 1;
}

void rebaixarElemento(FILA_PRIO* fila, int pai){
    PACIENTE temp;
    int filho = 2 * pai + 1;
    while(filho < fila->quantidade){

        if(filho < fila->quantidade-1) /* verifica se tem 2 filhos */
            if(fila->dados[filho].prioridade < fila->dados[filho+1].prioridade)
                filho++; /*filho aponta para filho menor */

        if(fila->dados[pai].prioridade >= fila->dados[filho].prioridade)
            break; /* encontrou lugar */

        temp = fila->dados[pai];
        fila->dados[pai] = fila->dados[filho];
        fila->dados[filho] = temp;

        pai = filho;
        filho = 2 * pai + 1;
    }
}

int desenfileirar(FILA_PRIO* fila){
    if(fila == NULL)
        return 0;
    if(fila->quantidade == 0)
        return 0;

    fila->quantidade--;
    fila->dados[0] = fila->dados[fila->quantidade];
    rebaixarElemento(fila,0);
    return 1;
}

void print(FILA_PRIO* fila){
    if(fila==NULL){
        return;
    }
    int i;
    printf("\n");
    for(i=0;i<fila->quantidade;i++){
        printf("%d \n", fila->dados[i].item);
    }
}

int busca(FILA_PRIO* fila, int item, int comparacoes){
    if(fila == NULL || fila->quantidade == 0)
        return 0;
    fila->dados[fila->quantidade].item;
    printf("\n comparações: %d \n", fila->quantidade);
    return 1;
}

int analise(FILA_PRIO* fila, FILE* arquivo){
    printf("Digite:\n1-Procurar\n2-Enfileirar\n3-Desenfileirar\n4-Imprimir a fila\n5-Fechar Programa\n");
    int valor;
    scanf("%d", &valor);
    if(valor==1){
        int p;
        printf("Digite o item buscado:");
        scanf("%d", &p);
        busca(fila,p,0);
        analise(fila,arquivo);
    }
    else if(valor==2){
        int item, prioridade;
        printf("Digite o item:");
        scanf("%d", &item);
        printf("Digite a prioridade:");
        scanf("%d", &prioridade);
        enfileirar(fila,item,prioridade,arquivo);
        analise(fila,arquivo);
    }
    else if(valor==3){
        desenfileirar(fila);
        analise(fila,arquivo);
    }
    else if(valor==4){
        print(fila);
        analise(fila,arquivo);
    }
    else if(valor==5){
        return 0;
    }
    else{
        printf("ERRO, VOLTE AO INICIO\n");
        analise(fila,arquivo);
    }
}

int main(){
    /*PACIENTE itens[200]= {{1,1},{3,3},{5,5},{7,7},{9,9},{2,2},{4,4},{6,6},{8,8},{10,10},{11,11},{12,12},{14,14},{13,13},{15,15},
    {16,16},{18,18},{19,19},{17,17},{20,20},{21,21},{23,23},{25,25},{27,27},{28,28},{29,29},{22,22},{24,24},{26,26},{30,30},{31,31},
    {32,32},{33,33},{34,34},{35,35},{36,36},{37,37},{38,38},{39,39},{40,40},{42,42},{43,43},{41,41},{45,45},{44,44},{46,46},{47,47},
    {48,48},{49,49},{50,50},{52,52},{54,54},{56,56},{58,58},{60,60},{62,62},{64,64},{66,66},{68,68},{70,70},{72,72},{74,74},{76,76},
    {78,78},{80,80},{82,82},{84,84},{86,86},{88,88},{90,90},{92,92},{94,94},{96,96},{98,98},{100,100},{102,102},{104,104},{106,106},
    {108,108},{110,110},{112,112},{114,114},{116,116},{118,118},{120,120},{122,122},{124,124},{126,126},{128,128},{130,130},{132,132},
    {134,134},{136,136},{138,138},{140,140},{142,142},{144,144},{146,146},{148,148},{150,150},{152,152},{154,154},{156,156},{158,158},
    {160,160},{162,162},{164,164},{166,166},{168,168},{170,170},{172,172},{174,174},{176,176},{178,178},{180,180},{182,182},{184,184},
    {186,186},{188,188},{190,190},{192,192},{194,194},{196,196},{198,198},{200,200},{51,51},{53,53},{55,55},{57,57},{59,59},{61,61},
    {63,63},{65,65},{67,67},{69,69},{71,71},{73,73},{75,75},{77,77},{79,79},{81,81},{83,83},{85,85},{87,87},{89,89},{91,91},{93,93},
    {95,95},{97,97},{99,99},{101,101},{103,103},{105,105},{107,107},{109,109},{111,111},{113,113},{115,115},{117,117},{119,119},{121,121},
    {123,123},{125,125},{127,127},{129,129},{131,131},{133,133},{135,135},{137,137},{139,139},{141,141},{143,143},{145,145},{147,147},
    {149,149},{151,151},{153,153},{155,155},{157,157},{159,159},{161,161},{163,163},{165,165},{167,167},{169,169},{171,171},{173,173},
    {175,175},{177,177},{179,179},{181,181},{183,183},{185,185},{187,187},{189,189},{191,191},{193,193},{195,195},{197,197},{199,199}};
    */

    FILE *fp;
    fp = fopen ("miau", "w");
   
    FILA_PRIO* fila = (FILA_PRIO*)malloc(sizeof(FILA_PRIO));
    fila = criar_Fila();
    int i;
    for(i=1;i<=25;i++){
        enfileirar(fila,i,i,fp);
    }
    printf("\n");
    //analise(fila, fp);
    fclose(fp);
    return 0;
}
