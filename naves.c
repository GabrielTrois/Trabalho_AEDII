#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "naves.h"
#define size 10

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

        // Chama heapify_down recursivamente no novo nó raiz
        descer(v, n, raiz);
    }
}

// Função para realizar o heapify-up (subir) em um heap
void subir(struct Naves v[], int i) {
    int pai = (i - 1) / 2;

    // Enquanto o nó atual não for a raiz e for maior que seu pai, troca-os
    while (i > 0 && v[i].prioridade > v[pai].prioridade) {
        troca(&v[i], &v[pai]);
        i = pai;
        pai = (i - 1) / 2;
    }
}

void organiza_heap(struct Naves v[], int n) {
    // Chama a função heapify_down para todos os nós não-folha
    int i;
    for (i = n / 2 - 1; i >= 0; i--) {
        descer(v, n, i);
    }
}

bool checa_Heap(struct Naves v[], int n) {
    int i;

    for(i = 0; i < n / 2; i++) {
        if(v[i].prioridade < v[2*i].prioridade) return false;

        if((2*i)+1 <= n) {
            if(v[i].prioridade < v[(2*i)+1].prioridade) return false;
        }
    }
    return true;
}

void imprime_Heap(struct Naves v[], int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("%d ", v[i].prioridade);
    }
}