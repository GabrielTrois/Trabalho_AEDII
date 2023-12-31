#ifndef NAVES_H_INCLUDED
#define NAVES_H_INCLUDED

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

struct RecursosLista {
    char nome[50];
    int codigo;
    int prioridade;
};

struct Naves {
    struct Tripulacao* passageiro;
    struct Compartimentos recursos;

    int lotacao;

    int prioridade;
};

void imprime_nave(struct Naves v);

void imprime_tripulacao(struct Tripulacao t[], int size);

struct Naves criaNave();

void descer(struct Naves v[], int n, int i);

int subir(struct Naves v[], int i);

void organiza_heap(struct Naves v[], int n);

int inserir_nave(struct Naves v[], struct RecursosLista r[]);

void remove_heap(struct Naves v[]);

void remove_nave(struct Naves v[]);

#endif // NAVES_H_INCLUDED
