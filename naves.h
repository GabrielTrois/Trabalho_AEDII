#ifndef NAVES_H_INCLUDED
#define NAVES_H_INCLUDED

struct Passageiro {
    char nome[20];
    int idade;
    char planeta[20];
    int identificador;
};

struct Recurso {
    char compartimento1[20];
    char compartimento2[20];
    char compartimento3[20];
};


struct Naves {
    struct Passageiro* passageiro;
    struct Recurso recursos;
    int codigo;
    int tripulacao;
    int enfermos;
    int clandestinos;
    int nobres;

    int prioridade;
};

void descer(struct Naves v[], int n, int i);

void subir(struct Naves v[], int i);

void organiza_heap(struct Naves v[], int n);

bool checa_Heap(struct Naves v[], int n);

#endif // NAVES_H_INCLUDED
