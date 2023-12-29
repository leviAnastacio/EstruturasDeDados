#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 99

typedef struct disciplina {
    int codDisc;
    char *nomeDisc;
    float notaFinal;
} DISCIPLINA;

typedef struct aluno {
    int matricula, qtdDisciplinas;
    char *nome;
    char *email;
    struct aluno *esq, *dir;
    DISCIPLINA *disciplinas;
} ALUNO;

ALUNO *raiz = NULL;

// Função para buscar um aluno na árvore
ALUNO *buscaAluno(ALUNO *aux, int matricula) {
    if (aux == NULL) {
        return NULL; // árvore vazia
    } else if (matricula == aux->matricula) {
        return aux; // achou!
    } else if (matricula < aux->matricula) {
        if (aux->esq != NULL) {
            return buscaAluno(aux->esq, matricula); // busca na subárvore-esquerda
        } else {
            return aux;
        }
    } else {
        if (aux->dir != NULL) {
            return buscaAluno(aux->dir, matricula); // busca na subárvore-direita
        } else {
            return aux;
        }
    }
}

// Função para adicionar um aluno à árvore
void addAluno(int matricula, int qtdDisciplinas, char *nome, char *email) {
    ALUNO *alunoBuscado = buscaAluno(raiz, matricula);
    if (alunoBuscado == NULL || alunoBuscado->matricula != matricula) {
        ALUNO *novoAluno = malloc(sizeof(ALUNO));
        novoAluno->matricula = matricula;
        novoAluno->qtdDisciplinas = qtdDisciplinas;

        novoAluno->nome = malloc(strlen(nome) + 1);
        strcpy(novoAluno->nome, nome);

        novoAluno->email = malloc(strlen(email) + 1);
        strcpy(novoAluno->email, email);

        novoAluno->disciplinas = malloc(qtdDisciplinas * sizeof(DISCIPLINA));
        for (int i = 0; i < qtdDisciplinas; i++) {
            novoAluno->disciplinas[i].nomeDisc = malloc(TAM);
            printf("Digite o nome da disciplina:\n");
            getchar();
            fgets(novoAluno->disciplinas[i].nomeDisc, TAM, stdin);
            novoAluno->disciplinas[i].nomeDisc[strcspn(novoAluno->disciplinas[i].nomeDisc, "\n")] = '\0';
            printf("Digite o codigo da disciplina:\n");
            scanf("%d", &novoAluno->disciplinas[i].codDisc);
            printf("Digite a nota final obtida na disciplina:\n");
            scanf("%f", &novoAluno->disciplinas[i].notaFinal);
        }

        novoAluno->esq = NULL;
        novoAluno->dir = NULL;

        if (alunoBuscado == NULL) {
            raiz = novoAluno;
        } else {
            if (matricula < alunoBuscado->matricula) {
                alunoBuscado->esq = novoAluno;
            } else {
                alunoBuscado->dir = novoAluno;
            }
        }
    } else {
        printf("Adicao invalida!!\nMatricula duplicada.\n");
    }
}

// Função para remover um aluno da árvore
ALUNO *rmvAluno(ALUNO *raiz, int matricula) {
    if (raiz->matricula == matricula) {
        ALUNO *aux1;
        if (raiz->dir == NULL && raiz->esq == NULL) { // Caso 1: o no a ser removido nao possui filhos.
            for (int i = 0; i < raiz->qtdDisciplinas; i++) {
                free(raiz->disciplinas[i].nomeDisc);
            }
            free(raiz->disciplinas);
            free(raiz);
            return NULL;
        } else if (raiz->dir == NULL && raiz->esq != NULL) { // Caso 2: o no a ser removido possui filho apenas na esquerda.
            aux1 = raiz->esq;
            free(raiz->disciplinas);
            free(raiz);
            return aux1;
        } else if (raiz->esq == NULL && raiz->dir != NULL) { // Caso 3: o no a ser removido possui filho apenas na direita.
            aux1 = raiz->dir;
            free(raiz->disciplinas);
            free(raiz);
            return aux1;
        } else { // Caso 4: o no a ser remvido possui filhos tanto na esquerda como na direita.
            ALUNO *aux2 = raiz->esq;
            while (aux2->dir != NULL) {
                aux2 = aux2->dir;
            }
            raiz->matricula = aux2->matricula;
            strcpy(raiz->nome, aux2->nome);
            strcpy(raiz->email, aux2->email);
            raiz->qtdDisciplinas = aux2->qtdDisciplinas;
            raiz->disciplinas = aux2->disciplinas;
            aux2->matricula = matricula;
            aux2->disciplinas = NULL;
            aux2->qtdDisciplinas = 0;
            raiz->esq = rmvAluno(raiz->esq, matricula);
            return raiz;
        }
    } else {
        if (matricula < raiz->matricula) {
            raiz->esq = rmvAluno(raiz->esq, matricula);
        } else {
            raiz->dir = rmvAluno(raiz->dir, matricula);
        }
        return raiz;
    }
}

// Função para alterar os dados de um aluno
void alterarDadosAluno(int matricula) {
    ALUNO *alunoDadosAlterados = buscaAluno(raiz, matricula);

    if (alunoDadosAlterados == NULL) {
        printf("Aluno nao encontrado.\n");
    } else {
        char resposta[4];
        printf("Gostaria de alterar o nome do aluno? [sim/nao]");
        scanf("%s", resposta);
        if (strcmp(resposta, "sim") == 0) {
            printf("Digite o novo nome do aluno:\n");
            char novoNome[TAM];
            getchar();
            fgets(novoNome, TAM, stdin);
            novoNome[strcspn(novoNome, "\n")] = '\0';

            free(alunoDadosAlterados->nome);

            alunoDadosAlterados->nome = malloc(strlen(novoNome) + 1);
            strcpy(alunoDadosAlterados->nome, novoNome);
        }

        printf("Gostaria de alterar o email do aluno? [sim/nao]");
        scanf("%s", resposta);
        if (strcmp(resposta, "sim") == 0) {
            printf("Digite o novo email do aluno:\n");
            char novoEmail[TAM];
            scanf("%s", novoEmail);

            free(alunoDadosAlterados->email);

            alunoDadosAlterados->email = malloc(strlen(novoEmail) + 1);
            strcpy(alunoDadosAlterados->email, novoEmail);
        }

        printf("Dados do aluno alterados com sucesso.\n");
    }
}

// Função para imprimir as disciplinas de um aluno
void imprimirDisciplinas(ALUNO *aluno) {
    for (int i = 0; i < aluno->qtdDisciplinas - 1; i++) {
        for (int j = i + 1; j < aluno->qtdDisciplinas; j++) {
            if (aluno->disciplinas[i].notaFinal < aluno->disciplinas[j].notaFinal) {
                DISCIPLINA aux = aluno->disciplinas[i];
                aluno->disciplinas[i] = aluno->disciplinas[j];
                aluno->disciplinas[j] = aux;
            }
        }
    }
    for (int i = 0; i < aluno->qtdDisciplinas; i++) {
        printf("   Disciplina [%d]:\n   Codigo: %d\n   Nome: %s\n   Nota final: %.2f\n", i + 1, aluno->disciplinas[i].codDisc, aluno->disciplinas[i].nomeDisc, aluno->disciplinas[i].notaFinal);
    }
}

// Função do menu principal
void menu() {
    printf("==================== MENU ====================\n");
    printf("[1] Cadastrar um aluno\n");
    printf("[2] Remover um aluno\n");
    printf("[3] Alterar dados de um aluno\n");
    printf("[4] Mostrar dados de um aluno\n");
    printf("[5] Sair\n");
    printf("==============================================\n");

    int opcao;
    printf("Digite a opcao desejada:\n");
    scanf("%d", &opcao);
    int matricula;
    switch (opcao) {
        case 1:
            printf("Digite os dados necessários para o cadastro de um novo aluno:\n");
            printf("Matricula do aluno:\n");
            scanf("%d", &matricula);

            printf("Nome do aluno:\n");
            char nome[TAM];
            getchar();
            fgets(nome, TAM, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Email do aluno:\n");
            char email[TAM];
            scanf("%s", email);

            printf("Quantidade de disciplinas cursadas pelo aluno:\n");
            int qtdDisciplinas;
            scanf("%d", &qtdDisciplinas);
            addAluno(matricula, qtdDisciplinas, nome, email);
            menu();
            break;
        case 2:
            printf("Digite a matricula do aluno que se deseja remover: ");
            scanf("%d", &matricula);
            ALUNO *alunoRemovido = malloc(sizeof(ALUNO));
            alunoRemovido = buscaAluno(raiz, matricula);
            if (alunoRemovido == NULL) {
                printf("O aluno que se deseja realizar a remocao, nao consta como cadastrado no sistema.\nVoltando para a pagina inicial...\n");
            } else {
                raiz = rmvAluno(raiz, matricula);
                printf("Aluno removido!\nVoltando para a pagina inicial...\n");
                free(alunoRemovido->disciplinas);
                free(alunoRemovido);
            }
            menu();
            break;
        case 3:
            printf("Digite a matricula do aluno o qual se deseja alterar dados: \n");
            scanf("%d", &matricula);
            alterarDadosAluno(matricula);
            menu();
            break;
        case 4:
            printf("Digite a matricula do aluno o qual se deseja mostrar os dados: \n");
            scanf("%d", &matricula);
            ALUNO *alunoBuscado = buscaAluno(raiz, matricula);
            if (alunoBuscado == NULL) {
                printf("Matricula invalida!\nVoltando para a pagina inicial...");
            } else {
                if (alunoBuscado->matricula == matricula) {
                    printf("=============== DADOS DO ALUNO ===============\n");
                    printf("-> Nome: %s\n", alunoBuscado->nome);
                    printf("-> Email: %s\n", alunoBuscado->email);
                    printf("-> Disciplinas cursadas: \n");
                    imprimirDisciplinas(alunoBuscado);
                } else {
                    printf("Aluno nao encontrado!\nVoltando para a pagina inicial...\n");
                }
            }
            menu();
            break;
        case 5:
            printf("Encerrando o programa...\n");
            exit(0);
            break;
        default:
            break;
    }
}

int main() {
    menu(); // Chama o menu principal
    return 0;
}
