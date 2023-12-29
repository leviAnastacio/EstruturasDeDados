#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct no{
    int chave;
    char cor;
    struct no *pai, *esq, *dir;
}NO;
//variavel auxiliar para enderecar o no externo
NO externo = {0, 'N', NULL, NULL, NULL};
//funcao auxiliar de criacao de nos
NO *criarNO(int chave){
    NO *novoNo = (NO*)malloc(sizeof(NO));
    novoNo->cor = 'N';
    novoNo->chave = chave;
    novoNo->esq = &externo;
    novoNo->dir = &externo;
    novoNo->pai = &externo;
    return novoNo;
}
//rotacao a esquerda
void rotacaoE(NO **ptraiz, NO *x){
    NO *y = x->dir;
    x->dir = y->esq;
    if(y->esq != &externo){
        y->esq->pai = x;
    }

    y->pai = x->pai;

    if(x->pai == &externo){
        (*ptraiz) = y;
    }else if(x == x->pai->esq){
        x->pai->esq = y;
    }else{
        x->pai->dir = y;
    }

    y->esq = x;
    x->pai = y;
} 
  
//rotacao a direita
void rotacaoD(NO **ptraiz, NO* y) {
    NO* x = y->esq;
    y->esq = x->dir;

    if (x->dir != &externo) {
        x->dir->pai = y;
    }

    x->pai = y->pai;

    if (y->pai == &externo) {
        (*ptraiz) = x;
    } else if (y == y->pai->esq) {
        y->pai->esq = x;
    } else {
        y->pai->dir = x;
    }

    x->dir = y;
    y->pai = x;
}

//realiza a movimentacao de nos pais auxilando em casos de remocao
void moverPai(NO **ptraiz, NO *u, NO *v){
    if(u->pai == &externo){
        (*ptraiz) = v;
        if(v != &externo){
            v->pai = &externo;
        }
    }else{
        if(u == u->pai->esq){
            u->pai->esq = v;
        }else{
            u->pai->dir = v;
        }
        
        v->pai = u->pai;
        
        
    }
}
//funcao auxiliar na insercao, implica em rotacoes e recoloracoes
void RotaRN(NO **ptraiz, NO *z){
    while(z->pai->cor == 'R'){
        if(z->pai == z->pai->pai->esq){
            NO *y = z->pai->pai->dir;
            if(y->cor == 'R'){
                z->pai->cor = y->cor = 'N';
                z->pai->pai->cor = 'R';
                z = z->pai->pai;
            }else{
                if(z == z->pai->dir){
                    z = z->pai;
                    rotacaoE(ptraiz, z);
                }
                z->pai->cor = 'N';
                z->pai->pai->cor = 'R';
                rotacaoD(ptraiz, z->pai->pai);
            }
        }else{
            NO *y = z->pai->pai->esq;
            if(y->cor == 'R'){
                z->pai->cor = y->cor = 'N';
                z->pai->pai->cor = 'R';
                z = z->pai->pai;
            }else{
                if(z == z->pai->esq){
                    z = z->pai;
                    rotacaoD(ptraiz, z);
                }
                z->pai->cor = 'N';
                z->pai->pai->cor = 'R';
                rotacaoE(ptraiz, z->pai->pai);
            }   
        }
    }
    (*ptraiz)->cor = 'N';
}

//funcao de insercao de nos
void inserirRN(NO *z, NO **ptraiz){
    NO *y = &externo;
    NO *pt = (*ptraiz);
    while(pt != &externo){
        y = pt;
        if(z->chave == pt->chave){
            y = NULL;
            pt = &externo;
        }else{
            if(z->chave < pt->chave){
                pt = pt->esq;
            }else{
                pt = pt->dir;
            }
        }
    }
    if(y != NULL){
        z->pai = y;
        if(y == &externo){
            (*ptraiz) = z;
        }else{
            if(z->chave < y->chave){
                y->esq = z;
            }else{
                y->dir = z;
            }
        }
    }

    z->esq = z->dir = &externo;
    z->cor = 'R';
    RotaRN(ptraiz, z);
}
//calcula o no com a menor chave dentro da rubro-negra
NO *NoMinimo(NO *x){
    while(x->esq != &externo){
        x = x->esq;
    }
    return x;
}
//funcao auxiliar na remocao, implica em rotacoes e recoloracoes
void RotaRemoverRn(NO **ptraiz, NO *x){
    while(x != (*ptraiz) && x->cor == 'N'){
        if(x == x->pai->esq){
            NO *w = x->pai->dir;
            if(w->cor == 'R'){
                x->pai->cor = 'R';
                w->cor = 'N';
                rotacaoE(ptraiz, x->pai);
                w = x->pai->dir;
            }
            if(w->dir->cor == 'N' && w->esq->cor == 'N'){
                w->cor = 'R';
                x = x->pai;
            }else{
                if(w->dir->cor == 'N'){
                    w->esq->cor = 'N';
                    w->cor = 'R';
                    rotacaoD(ptraiz, w);
                    w = x->pai->dir;
                }
                w->cor = x->pai->cor;
                x->pai->cor = 'N';
                w->dir->cor = 'N';
                rotacaoE(ptraiz, x->pai);
                x = (*ptraiz);
            }
        }else{
            NO *w = x->pai->esq;
            if(w->cor == 'R'){
                w->cor = 'N';
                x->pai->cor = 'R';
                rotacaoD(ptraiz, x->pai);
                w = x->pai->esq;
            }
            if(w->esq->cor == 'N' && w->dir->cor == 'N'){
                w->cor = 'R';
                x = x->pai;
            }else{
                if(w->esq->cor == 'N'){
                    w->dir->cor = 'N';
                    w->cor = 'R';
                    rotacaoE(ptraiz, w);
                    w = x->pai->esq;
                }
                w->cor = x->pai->cor;
                x->pai->cor = 'N';
                w->esq->cor = 'N';
                rotacaoD(ptraiz, x->pai);
                x = (*ptraiz);
            }
        }
    }
    x->cor = 'N';
}
//funcao de remocao
void RemoverRn(NO *z, NO **ptraiz){
    NO *y = z;
    char corOriginal = y->cor;
    NO *x = NULL;
    if(z->esq == &externo){
        x = z->dir;
        moverPai(ptraiz, z, z->dir);
    }else if(z->dir == &externo){
        x = z->esq;
        moverPai(ptraiz, z, z->esq);
    }else{
        y = NoMinimo(z->dir);
        corOriginal = y->cor;
        x = y->dir;
        if(y->pai == z){
            x->pai = y;
        }else{
            moverPai(ptraiz, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        moverPai(ptraiz, z, y); 
        y->esq = z->esq;
        y->esq->pai = y;
        y->cor = z->cor;
        
    }
    if(corOriginal == 'N'){
        RotaRemoverRn(ptraiz, x);
    }
}

//funcao que calcula a quantidade de nos na rubro-negra
int contarNos(NO *pt){
    if(pt == NULL || pt == &externo){
        return 0;
    }else{
        return 1 + contarNos(pt->esq) + contarNos(pt->dir);
    }
}
//funcao que calcula e verifica a consistencias entre as alturas negras das subarvores a partir da raiz
int alturaNegra(NO *ptraiz){
    if(ptraiz == NULL || ptraiz == &externo){
        return 1;
    }else{
        int altEsq = alturaNegra(ptraiz->esq);
        int altDir = alturaNegra(ptraiz->dir);
        if(altEsq != altDir){
            return 0;
        }else{
            return (ptraiz->cor == 'N') ? altEsq + 1 : altEsq;
        }
    }
}
//funcao que verifica se a arvore em questao é rubro-negra
int ehRN(NO *aux){
    //valida a raiz
    if(aux == NULL || aux == &externo){
        return 1;
    }

    //verifica se existem nos "Rubro-Rubro"
    if((aux->cor == 'R' && (aux->esq->cor == 'R' || aux->dir->cor == 'R')) || (aux->cor != 'R' && aux->cor != 'N')){
        return 0;
    }

    //valida a altura negra das duas subarvores
    int altNesq = alturaNegra(aux->esq);
    int altNdir = alturaNegra(aux->dir);
    if(altNesq == 0 || altNdir == 0 || altNdir != altNesq){
        return 0;
    }

    //valida as propriedades para as subarvores
    int subArvEsq = ehRN(aux->esq);
    int subArvDir = ehRN(aux->dir);
    if(subArvDir == 0 || subArvEsq == 0){
        return 0;
    }

    return 1;

}

void teste(){
    NO *raizes[1000];
    for(int i = 0; i < 1000; i++){
        raizes[i] = NULL;
    }

    int chavesInseridas[10000];
    bool chaveExistente;
    for (int i = 0; i < 10000; i++) {
        do{
            chaveExistente = false;
            chavesInseridas[i] = rand() % 100001;
            for (int j = 0; j < i; j++) {
                if (chavesInseridas[j] == chavesInseridas[i]) {
                    chaveExistente = true;
                    break;
                }
            }
        }while(chaveExistente);
    }

    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < 10000; j++){
            if(raizes[i] == NULL){
                raizes[i] = criarNO(chavesInseridas[j]);
            }else{
                inserirRN(criarNO(chavesInseridas[j]), &raizes[i]);
            }
        }
    }

    printf("Rubro-negras com 10000 nos inseridos!\n");

    for(int i = 0; i < 1; i++){
        int numNOs = contarNos(raizes[i]);
        int altNegra = alturaNegra(raizes[i]);
        printf("Rubro-negra numero %d\n", i+1);
        printf("Altura negra da rubro-negra: %d\nQuantidade de nos: %d\n", altNegra, numNOs);
        int valida = ehRN(raizes[i]);
        printf("A arvore eh rubro-negra?\n");
        if(valida == 0){
            printf("Nao eh rubro negra\n");
        }else{
            printf("Sim, a arvore eh rubro-negra\n");
        }

    }

    for(int i = 0; i < 1000; i++){
        NO *deletado = raizes[i];
        for(int j = 0; j < 1000; j++){
            RemoverRn(deletado, &raizes[i]);
        }   
    }
    
    printf("\n");
    printf("Rubro-negras com 1000 nos deletados!\n");

    for(int i = 0; i < 1; i++){
        printf("Rubro-negra numero %d\n", i+1);
        printf("Altura negra da rubro-negra: %d\nQuantidade de nos: %d\n", alturaNegra(raizes[i]), contarNos(raizes[i]));
        int valida = ehRN(raizes[i]);
        printf("A arvore eh rubro-negra?\n");
        if(valida == 0){
            printf("Nao eh rubro negra\n");
        }else{
            printf("Sim, a arvore eh rubro-negra\n");
        }
    }
}   

int main() {
    clock_t incioExecucao, fimExecucao;
    double tempo;
    incioExecucao = clock();
    teste();
    fimExecucao = clock();
    tempo = ((double)(fimExecucao - incioExecucao))/CLOCKS_PER_SEC;
    printf("Tempo de execucao: %.2f s\n", tempo);
    return 0;
}
