#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "naves.h"

int id_global = 330;
int ultima_nave = 49;

// Função que imprime o conteudo da Nave
void imprime_nave(struct Naves nave) {
    printf("Capitao: %s\n", nave.passageiro[0].nome); //Primeiro passageiro é o capitão
    printf("Co-Capitao: %s\n", nave.passageiro[1].nome); //Segundo passageiro é o co-capitão
    printf("Lotacao da nave: %d\n", nave.lotacao);
    printf("Compartimentos:\n1: %s\n2: %s\n3: %s\n", nave.recursos.compartimento1, nave.recursos.compartimento2, nave.recursos.compartimento3);
    printf("Codigos de compartimentos: %d %d %d\n", nave.recursos.code[0], nave.recursos.code[1], nave.recursos.code[2]);
    printf("Prioridade: %d\n\n", nave.prioridade);
}

// Função que imprime as informações da Tripulação da Nave
void imprime_tripulacao(struct Tripulacao passageiros[], int size) {
    for(int i = 0; i < size; i++) {
        printf("Passageiro %d:\n", i+1);
        printf("Nome: %s\n", passageiros[i].nome);
        printf("Idade: %d\n", passageiros[i].idade);

        if(passageiros[i].IsEnfermo == 1) printf("*Enfermo*\n");

        if(passageiros[i].IsClandestino == 1) printf("*Clandestino*\n");

        if(passageiros[i].IsNobre == 1) printf("*Nobre*\n");

        printf("ID: %d\n", passageiros[i].identificador);
        printf("Prioridade pessoal: %d\n\n", passageiros[i].prioridade_pessoal);
    }
}

// Função que criar naves com todas as informações necessarias
struct Naves criaNave() {
    struct Naves temp; // Nave temporaria

    int i;

    srand(time(NULL));

    temp.prioridade = 10; // Prioridade inicial

    printf("Digite a quantidade de passageiros da Nave: ");
    scanf("%d", &temp.lotacao);
    while(temp.lotacao < 2 || temp.lotacao > 12) {
        printf("Sua tripulacao deve ser no minimo 2 e maximo 12: ");
        scanf("%d", &temp.lotacao);
    }

    temp.passageiro = (struct Tripulacao*)malloc(temp.lotacao*sizeof(struct Tripulacao));

//  Define passageiros da Nave
    for(i = 0; i < temp.lotacao; i++) {
        temp.passageiro[i].prioridade_pessoal = 2;
        temp.passageiro[i].IsCrianca = 0;
        temp.passageiro[i].IsIdoso = 0;
        temp.passageiro[i].IsEnfermo = 0;
        temp.passageiro[i].IsNobre = 0;
        temp.passageiro[i].IsClandestino = 0;

        printf("Digite o nome do passageiro %d: ", i+1);
        scanf("%s", temp.passageiro[i].nome);
        printf("Digite a idade do passageiro %d: ", i+1);
        scanf("%d", &temp.passageiro[i].idade);
        printf("Digite o planeta do passageiro %d: ", i+1);
        scanf("%s", temp.passageiro[i].planeta);
        printf("1 - sim, 0 - nao\n");
        printf("O passageiro %d esta doente: ", i+1);
        scanf("%s", &temp.passageiro[i].IsEnfermo);
        printf("O passageiro %d e clandestino: ", i+1);
        scanf("%s", &temp.passageiro[i].IsClandestino);
        printf("O passageiro %d e nobre: ", i+1);
        scanf("%s", &temp.passageiro[i].IsNobre);

        printf("\n");

        id_global++; // Almenta o id global para definir novos Tripulantes

        temp.passageiro[i].identificador = id_global;

        if(temp.passageiro[i].idade < 18)  temp.passageiro[i].IsCrianca = 1;
        if(temp.passageiro[i].idade >= 60) temp.passageiro[i].IsIdoso = 1;

        if(temp.passageiro[i].IsCrianca == 1 || temp.passageiro[i].IsIdoso == 1) temp.passageiro[i].prioridade_pessoal *= 2;
        if(temp.passageiro[i].IsEnfermo == 1) temp.passageiro[i].prioridade_pessoal *= 2;
        if(temp.passageiro[i].IsClandestino == 1) temp.passageiro[i].prioridade_pessoal /= 2;
        if(temp.passageiro[i].IsNobre == 1) temp.passageiro[i].prioridade_pessoal *= 4;

        temp.prioridade += temp.passageiro[i].prioridade_pessoal;
    }
    
    for(i = 0; i < 3; i++) {
        printf("Digite o codigo do recurso do compartimento %d (1 - 6): ", i+1);
        scanf("%d", &temp.recursos.code[i]); // Define o codigo dos recursos
    }
    printf("\n");

    return temp;
}

// Função para descer termos em um heap
void descer(struct Naves v[], int n, int i) {
    int raiz = i; // Inicializa o índice do maior elemento como a raiz
    int esq = 2 * i + 1; // Índice do filho esquerdo
    int dir = 2 * i + 2; // Índice do filho direito

    // Verifica se o filho esquerdo é maior que o nó raiz
    if (esq < n && v[esq].prioridade > v[raiz].prioridade)
        raiz = esq;

    // Verifica se o filho direito é maior que o nó raiz
    if (dir < n && v[dir].prioridade > v[raiz].prioridade)
        raiz = dir;

    // Se o maior elemento não for a raiz, troca-os
    if (raiz != i) {
        struct Naves temp = v[i];
        v[i] = v[raiz];
        v[raiz] = temp;

        // Chama descer recursivamente no novo nó raiz
        descer(v, n, raiz);
    }
}

// Função para subir termos em um heap
int subir(struct Naves v[], int i) {
    int pai = (i - 1) / 2;

    // Enquanto o nó atual não for a raiz e for maior que seu pai, troca-os
    while (i > 0 && v[i].prioridade > v[pai].prioridade) {
        struct Naves temp = v[i];
        v[i] = v[pai];
        v[pai] = temp;
        i = pai;
        pai = (i - 1) / 2;
    }

    return i;
}

void organiza_heap(struct Naves v[], int n) {
    // Chama a função descer para todos os nós até a metade do vetor
    int i;
    for (i = n / 2 - 1; i >= 0; i--) {
        descer(v, n, i);
    }
}

// Função de inserção em um heap
int inserir_nave(struct Naves v[], struct RecursosLista r[]) {
    if(ultima_nave >= 1000) return -1; // 1000 é o limite de Naves na Fila

    ultima_nave++;

    v[ultima_nave] = criaNave(); // Chama criaNave()

//  Define os recursos usando o codigo dado e a lista de Recursos
    strcpy(v[ultima_nave].recursos.compartimento1, r[v[ultima_nave].recursos.code[0]-1].nome);
    strcpy(v[ultima_nave].recursos.compartimento2, r[v[ultima_nave].recursos.code[1]-1].nome);
    strcpy(v[ultima_nave].recursos.compartimento3, r[v[ultima_nave].recursos.code[2]-1].nome);
    
    v[ultima_nave].prioridade += r[v[ultima_nave].recursos.code[0]].prioridade;
    v[ultima_nave].prioridade += r[v[ultima_nave].recursos.code[1]].prioridade;
    v[ultima_nave].prioridade += r[v[ultima_nave].recursos.code[2]].prioridade;

    int p;

    printf("1 - sim, 0 - nao\n");
    printf("Deseja colocar uma prioridade ou calcular automaticamente (prioridade calculada = %d): ", v[ultima_nave].prioridade);
    scanf("%d", &p);

    if(p == 1) {
        printf("Digite a priridade: ");
        scanf("%d", &v[ultima_nave].prioridade);
    }

    int i = subir(v, ultima_nave); // Coloca termo no lugar certo do Heap
    
    return i + 1;
}

// Remove o primeiro termo de um Heap
void remove_heap(struct Naves v[]) {
    v[0] = v[ultima_nave];

    ultima_nave--;

    descer(v, ultima_nave, 0);
}

// Função de remoção na Fila, com o caso especial da abertura da fenda
void remove_nave(struct Naves v[]) {
    int i, j = 0;
    int *cont; // Salva o indice de Naves que carregam uma permutação dos mesmos recursos

    cont = (int*)malloc(sizeof(int));
    
    for(i = 1; i < ultima_nave; i++) { // Faz a checagem de cargas de recursos iguais
        if(v[0].recursos.code[0] == v[i].recursos.code[0] || v[0].recursos.code[0] == v[i].recursos.code[1] || v[0].recursos.code[0] == v[i].recursos.code[2]) {
            if(v[0].recursos.code[1] == v[i].recursos.code[0] || v[0].recursos.code[1] == v[i].recursos.code[1] || v[0].recursos.code[1] == v[i].recursos.code[2]) {
                if(v[0].recursos.code[2] == v[i].recursos.code[0] || v[0].recursos.code[2] == v[i].recursos.code[1] || v[0].recursos.code[2] == v[i].recursos.code[2]) {
                    cont[j] = i;
                    j++;
                    cont = realloc(cont, sizeof(int)*(j+1));
                }
            }
        }
    }

    remove_heap(v); // Remove termo que deveria ser removido

    int operation;

    int destruiu = 0;

    srand(time(NULL));

    if(j > 0) {
        printf("Foram encontradas %d naves carregando os mesmos materiais, deseja as %d primeiras da fila(1 - sim, 2 - nao): ", j, j);
        scanf("%d", &operation); // A escolha é dada ao operador se ele libera ou não naves para aproveitar a abertura da fenda

        if(operation == 1) {
            for(i = 0; i < j; i++) {
                if((rand()%10) == 1) {
                    destruiu++;
                }
                if(destruiu > 0) {
                    remove_heap(v); // Nave Destruida
                    destruiu++;
                } else {
                    remove_heap(v); // Remove
                }
            }
        if(destruiu > 0) printf("Fenda fechou abruptamente!! %d nave(s) destruida(s)\n", destruiu);
        }
    }
}
