#ifndef NAVES_H_INCLUDED
#define NAVES_H_INCLUDED

#include <stdbool.h>

struct Tripulacao {
    char nome[50];
    int idade;

//  Checagem para prioridade pessoal
    int IsCrianca;
    int IsIdoso;
    int IsEnfermo;
    int IsClandestino;
    int IsNobre;

    char planeta[50];

    int prioridade_pessoal;
    int identificador;
};

struct Compartimentos {
    char compartimento1[50];
    char compartimento2[50];
    char compartimento3[50];

    int code[3];
};


struct Naves {
    struct Tripulacao* passageiro;
    struct Compartimentos recursos;

    int lotacao;

    int ultimo_codigo;

    int prioridade;
};

void descer(struct Naves v[], int n, int i);

void subir(struct Naves v[], int i);

void organiza_heap(struct Naves v[], int n);

bool checa_Heap(struct Naves v[], int n);

#endif // NAVES_H_INCLUDED
