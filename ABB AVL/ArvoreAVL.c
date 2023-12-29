#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define V 1
#define F 0

typedef struct no{
    int chave, bal;
    struct no *esq, *dir;
}NO;

int altura(NO *pt){//funcao que calcula a altura da arvore AVL
    if(pt == NULL){
        return 0;
    }else{
        int altEsq = altura(pt->esq);
        int altDir = altura(pt->dir);
        if(altDir>altEsq){//verifica a maior subarvores e a retorna
            return altDir + 1;
        }else{
            return altEsq + 1;
        }
    }
}

void ehAVL(NO *pt, int *verifica){//funcao verifica se a arvore eh ou nao AVL
    if(pt != NULL){
        int altEsq = altura(pt->esq);
        int altDir = altura(pt->dir);
        int subArvEsq, subArvDir;
        ehAVL(pt->dir, &subArvDir);//verifica subarvore direita
        ehAVL(pt->esq, &subArvEsq);//verifica subarvore a esquerda

        if ((pt->bal != (altDir - altEsq)) || ((pt->bal < -1) && (pt->bal > 1) && (!subArvEsq && !subArvDir))){
            *verifica = F;
        }


    }
}


int contarNos(NO *pt){//conta quantos nos a AVL possui
    if(pt == NULL){
        return 0;
    }else{
        return 1 + contarNos(pt->esq) + contarNos(pt->dir);//numero de nos nas subarvores esquerda e direita
    }
}


void caso1_Adc(NO **ptAcessado, int *h){//Rotação a esquerda
    NO *auxU = (*ptAcessado)->esq;
    if(auxU->bal == -1){ //simples
        (*ptAcessado)->esq = auxU->dir;
        auxU->dir = (*ptAcessado);
        (*ptAcessado) = auxU;
        (*ptAcessado)->dir->bal = 0;
    }else{//dupla
        NO *auxV = auxU->dir;
        auxU->dir = auxV->esq;
        auxV->esq = auxU;
        (*ptAcessado)->esq = auxV->dir;
        auxV->dir = (*ptAcessado);

        if(auxV->bal == 1){
            (*ptAcessado)->bal = 0;
            auxU->bal = -1;
        }else if(auxV->bal == 0){
            (*ptAcessado)->bal = 0;
            auxU->bal = 0;
        }else{
            (*ptAcessado)->bal = 1;
            auxU->bal = 0;
        }
        (*ptAcessado) = auxV;
    }
    (*ptAcessado)->bal = 0;
    *h = F;
}

void caso2_Adc(NO **ptAcessado, int *h){//rotacao a direita
    NO *auxU = (*ptAcessado)->dir;
    if(auxU->bal == 1){//simples
        (*ptAcessado)->dir = auxU->esq;
        auxU->esq = (*ptAcessado);
        (*ptAcessado) = auxU;
        (*ptAcessado)->esq->bal = 0;
    }else{//dupla
        NO *auxV = auxU->esq;
        auxU->esq = auxV->dir;
        auxV->dir = auxU;
        (*ptAcessado)->dir = auxV->esq;
        auxV->esq = (*ptAcessado);
        
        if(auxV->bal == 1){
            (*ptAcessado)->bal = -1;
            auxU->bal = 0;
        }else if(auxV->bal == 0){
            (*ptAcessado)->bal = 0;
            auxU->bal = 0;
        }else{
            (*ptAcessado)->bal = 0;
            auxU->bal = 1;
        }
        (*ptAcessado) = auxV;
    }
    (*ptAcessado)->bal = 0;
    *h = F;
}

void adc(int chave, NO **ptAcessado, int *h, int *qtd){//funcao de adicao de nos na AVL
    if((*ptAcessado) == NULL){
        NO *novoNO = (NO*)malloc(sizeof(NO));
        novoNO->chave = chave;
        novoNO->bal = 0;
        novoNO->dir = NULL;
        novoNO->esq = NULL;

        *h = V;
        (*ptAcessado) = novoNO;
        (*qtd)++;
    }else{
        if(chave != (*ptAcessado)->chave){
            if(chave < (*ptAcessado)->chave){//adiçao a esquerda
                adc(chave, &(*ptAcessado)->esq, h, qtd);
                if(*h){//caso a altura tenha sido alterada
                    if((*ptAcessado)->bal == 1){
                        (*ptAcessado)->bal = 0;
                        *h = F;
                    }else{
                        if((*ptAcessado)->bal == 0){
                            (*ptAcessado)->bal = -1;
                        }else{
                            if((*ptAcessado)->bal == -1){
                                caso1_Adc(ptAcessado, h);
                            }
                        }
                    }
                }
            }else{//adicao a direita
                adc(chave, &(*ptAcessado)->dir, h, qtd);
                if(*h){
                    if ((*ptAcessado)->bal == -1){
                        (*ptAcessado)->bal = 0;
                        *h = F;
                    }else{
                        if((*ptAcessado)->bal == 0){
                            (*ptAcessado)->bal = 1;
                        }else{
                            if((*ptAcessado)->bal == 1){  
                                caso2_Adc(ptAcessado, h);
                            }
                        }
                    }
                }
            }
        }else{
            *h = F;//altura nao se alterou
        }
    }
}

void caso1_rmv(NO **ptAcessado, int *h){//rotacao a esquerda
    NO *auxU = (*ptAcessado)->esq;
    if(auxU->bal <= 0){//simples
        (*ptAcessado)->esq = auxU->dir;
        auxU->dir = (*ptAcessado);
        (*ptAcessado) = auxU;

        if(auxU->bal == -1){
            auxU->bal = 0;
            (*ptAcessado)->dir->bal = 0;
            *h = V;
        }else{
            auxU->bal = 1;
            (*ptAcessado)->dir->bal = -1;
            *h = F;
        }
    }else{//dupla
        NO *auxV = auxU->dir;
        auxU->dir = auxV->esq;
        auxV->esq = auxU;
        (*ptAcessado)->esq = auxV->dir;
        auxV->dir = (*ptAcessado);
        (*ptAcessado) = auxV;

        if(auxV->bal == -1){
            auxU->bal = 0;
            (*ptAcessado)->dir->bal = 1;
        }else{
            if(auxV->bal == 0){
                auxU->bal = 0;
                (*ptAcessado)->dir->bal = 0;
            }else{
                if(auxV->bal == 1){
                    auxU->bal = -1;
                    (*ptAcessado)->dir->bal = 0;
                }
            }
        }
        (*ptAcessado)->bal = 0;
        *h = V;
    }
}

void caso2_rmv(NO **ptAcessado, int *h){//rotacao a direita
    NO *auxU = (*ptAcessado)->dir;
    if(auxU->bal >= 0) { //simples
        (*ptAcessado)->dir = auxU->esq;
        auxU->esq = (*ptAcessado);
        *ptAcessado = auxU;

        if((*ptAcessado)->bal == 1){
            auxU->bal = 0;
            (*ptAcessado)->esq->bal = 0;
            *h = V;
        }else{
            auxU->bal = -1;
            (*ptAcessado)->esq->bal = 1;
            *h = F;
        }
    }else{//dupla
        NO *auxV = auxU->esq;
        auxU->esq = auxV->dir;
        auxV->dir = auxU;
        (*ptAcessado)->dir = auxV->esq;
        auxV->esq = (*ptAcessado);
        (*ptAcessado) = auxV;

        if(auxV->bal == 1){
            auxU->bal = 0;
            (*ptAcessado)->esq->bal = -1;
        }else{
            if(auxV->bal == 0){
                auxU->bal = 0;
                (*ptAcessado)->esq->bal = 0;
            }else{
                if(auxV->bal == -1){
                    auxU->bal = 1;
                    (*ptAcessado)->esq->bal = 0;
                }
            }
        }
        (*ptAcessado)->bal = 0;
        *h = V;
    }
}

void TrocarNOS(NO **pt, NO **s){
    NO *ptAux;
    int balAux;

    ptAux = *s;
    *s = *pt;
    *pt = ptAux;

    ptAux = (*s)->esq; //troca à esquerda
    (*s)->esq = (*pt)->esq;
    (*pt)->esq = ptAux;

    ptAux = (*s)->dir; // troca à direita
    (*s)->dir = (*pt)->dir;
    (*pt)->dir = ptAux;

    balAux = (*s)->bal; // troca do bal
    (*s)->bal = (*pt)->bal;
    (*pt)->bal = balAux;
}

void balancear(NO **ptAcessado, char x, int *h){//funcao para balancear toda a AVL
    if(*h){
        if(x == 'D'){
            if((*ptAcessado)->bal == 1){
                (*ptAcessado)->bal = 0;            
            }else{
                if((*ptAcessado)->bal == 0){
                    (*ptAcessado)->bal = -1;
                    *h = F;
                }else{
                    caso1_rmv(ptAcessado, h);
                }
            }
        }else{
            if((*ptAcessado)->bal == -1){
                (*ptAcessado)->bal = 0;
            }else{
                if((*ptAcessado)->bal == 0){
                    (*ptAcessado)->bal = 1;
                    *h = F;
                }else{
                    caso2_rmv(ptAcessado, h);
                }
            }
        }
    }
}

void rmv(int chave, NO **ptAcessado, int *h, int *qtd){//funcao de remocao
    if((*ptAcessado) == NULL){
        *h = F;
    }else{
        if(chave < (*ptAcessado)->chave){//remocao a esquerda
            rmv(chave, &(*ptAcessado)->esq, h, qtd);
            balancear(ptAcessado, 'E', h);
        }else{
            if(chave > (*ptAcessado)->chave){//remocao a direita
                rmv(chave, &(*ptAcessado)->dir, h, qtd);
                balancear(ptAcessado, 'D', h);
            }else{//encontrou o no a ser removido
                NO *aux = (*ptAcessado);
                if((*ptAcessado)->esq == NULL){
                    (*ptAcessado) = (*ptAcessado)->dir;
                    *h = V;
                    (*qtd)--;
                    free(aux);
                }else{
                    if((*ptAcessado)->dir == NULL){
                        (*ptAcessado) = (*ptAcessado)->esq;
                        *h = V;
                        (*qtd)--;
                        free(aux);
                    }else{
                        NO *s = (*ptAcessado)->dir;
                        if(s->esq == NULL){
                            s->esq = (*ptAcessado)->esq;
                            s->bal = (*ptAcessado)->bal;
                            *ptAcessado = s;
                            *h = V;
                            (*qtd)--;
                            free(aux);
                        }else{
                            NO *paiS;
                            while(s->esq != NULL){
                                paiS = s;
                                s = s->esq;
                            }
                            TrocarNOS(ptAcessado, &(paiS)->esq);
                            rmv(chave, &(*ptAcessado)->dir, h, qtd);
                        }
                        balancear(ptAcessado, 'D', h);
                    }
                }
            }
        }
    }
}

void teste(){
    int h, verifica;
    NO *raizes[1000];//raiz de cada AVL
    for(int i = 0; i < 1000; i++){
        raizes[i] = NULL;
    }
    
    int quantidades[1000];//contador que diz respeito ao numero de nos em cada AVL
    for(int i = 0; i < 1000; i++){
        quantidades[i] = 0;
    }
    

    for(int i = 0; i < 1000; i++){//Adicao de 10000 nos em cada AVL
        while(quantidades[i] < 10000){
            int chavesInseridas = rand() % 100001;
            adc(chavesInseridas, &raizes[i], &h, &quantidades[i]);
        }
    }

    printf("Avls com 10000 nos inseridos!\n");
    for(int i = 0; i < 1000; i++){
        printf("AVL numero %d\n", i+1);
        printf("Altura da AVL: %d\nQuantidade de nos: %d\n", contarNos(raizes[i]), altura(raizes[i]));
        ehAVL(raizes[i], &verifica);
        printf("Eh AVL? \n");
        if(verifica){
            printf("SIM\n");
        }else{
            printf("NAO\n");
            verifica = V;
        }
    }

    for(int i = 0; i < 1000; i++){//remocao de 1000 nos em cada AVL
        while(quantidades[i] > 9000){
            int chavesExcluidas = rand() % 100001;
            rmv(chavesExcluidas, &raizes[i], &h, &quantidades[i]);
        }
    }

    printf("AVLs com 1000 nos removidos");
    for(int i = 0; i < 1000; i++){
        printf("AVL numero %d\n", i+1);
        printf("Altura da AVL: %d\nQuantidade de nos: %d\n",altura(raizes[i]), contarNos(raizes[i]));
        ehAVL(raizes[i], &verifica);
        printf("Eh AVL? \n");
        if(verifica){
            printf("SIM\n");
        }else{
            printf("NAO\n");
            verifica = V;
        }
    

    }
    

}

void imprimirInOrdem(NO *raiz) {
    if (raiz != NULL) {
        imprimirInOrdem(raiz->esq);   
        printf("%d ", raiz->chave); 
        imprimirInOrdem(raiz->dir);   
    }
}



int main(){
    clock_t inicioExecucao, fimExecucao;
    double tempo;
    inicioExecucao = clock();
    teste();
    fimExecucao = clock();
    tempo = ((double)(fimExecucao - inicioExecucao)) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %.2f s\n", tempo);
    return 0;
}
    



  
    
    
