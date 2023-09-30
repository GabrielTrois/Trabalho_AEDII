#include <stdio.h>
#include <stdlib.h>
#include "naves.h"
#include "naves.c"

int main() {

    FILE * file1 = fopen ("Naves.csv", "r");
    if (! file1 ) {
        printf (" Erro ao abrir o arquivo .\n");
        return 1;
    }

    FILE * file2 = fopen ("Tripulacao.csv", "r");
    if (! file2 ) {
        printf (" Erro ao abrir o arquivo .\n");
        return 1;
    }

    FILE * file3 = fopen ("Recursos.csv", "r");
    if (! file3 ) {
        printf (" Erro ao abrir o arquivo .\n");
        return 1;
    }

    struct Naves naves[1000];
    struct Tripulacao passageiro[330];
    struct RecursosLista recursos[100];

    int read = 0;
    int records = 0;

    int i, j, k = 0;

    do{
        read = fscanf(file1,
                            "%50[^,],%50[^,],%50[^,],%d,%d,%d,%d,%d\n",
                            naves[records].recursos.compartimento1,
                            naves[records].recursos.compartimento2,
                            naves[records].recursos.compartimento3,
                            &naves[records].recursos.code[0],
                            &naves[records].recursos.code[1],
                            &naves[records].recursos.code[2],
                            &naves[records].lotacao,
                            &naves[records].prioridade);

        if(read == 8){
            records++;
        }

        if (read != 8 && !feof(file1)){
            printf("Formato de arquivo incorreto.\n");
            return 1;
        }

        if (ferror(file1)){
            printf("Erro ao ler o arquivo.\n");
        }
    } while (!feof(file1));

    read = 0;
    records = 0;

    do{
        read = fscanf(file2,
                            "%50[^,],%d,%d,%d,%d,%d,%d,%50[^,],%d,%d\n",
                            passageiro[records].nome,
                            &passageiro[records].idade,
                            &passageiro[records].IsCrianca,
                            &passageiro[records].IsIdoso,
                            &passageiro[records].IsEnfermo,
                            &passageiro[records].IsClandestino,
                            &passageiro[records].IsNobre,
                            passageiro[records].planeta,
                            &passageiro[records].prioridade_pessoal,
                            &passageiro[records].identificador);

        if(read == 10){
            records++;
        }

        if (read != 10 && !feof(file2)){
            printf("Formato de arquivo incorreto.\n");
            return 1;
        }

        if (ferror(file2)){
            printf("Erro ao ler o arquivo.\n");
        }

    } while (!feof(file2));

    read = 0;
    records = 0;

    do{
        read = fscanf(file3,
                            "%50[^,],%d,%d\n",
                            recursos[records].nome,
                            &recursos[records].codigo,
                            &recursos[records].prioridade);

        if(read == 3){
            records++;
        }

        if (read != 3 && !feof(file3)){
            printf("Formato de arquivo incorreto.\n");
            return 1;
        }

        if (ferror(file3)){
            printf("Erro ao ler o arquivo.\n");
        }

    } while (!feof(file3));

    fclose(file1);
    fclose(file2);
    fclose(file3);

    for(i = 0; i < 330; i++) {
        naves[i].passageiro = (struct Tripulacao*)malloc(naves[i].lotacao*sizeof(struct Tripulacao));
        for(j = 0; j < naves[i].lotacao; j++) {
            
            strcpy(naves[i].passageiro[j].nome, passageiro[k].nome);
            naves[i].passageiro[j].idade = passageiro[k].idade;
            
            naves[i].passageiro[j].IsCrianca = passageiro[k].IsCrianca;
            naves[i].passageiro[j].IsIdoso = passageiro[k].IsIdoso;
            naves[i].passageiro[j].IsClandestino = passageiro[k].IsClandestino;
            naves[i].passageiro[j].IsNobre = passageiro[k].IsNobre;
            
            naves[i].passageiro[j].identificador = passageiro[k].identificador;
            naves[i].passageiro[j].prioridade_pessoal = passageiro[k].prioridade_pessoal;

            k++;
        }
    }
    free(passageiro);

    /*------------------------------------------------------------------------------*/

    organiza_heap(naves, ultima_nave);
    
printf("\nNaves: %d\n", ultima_nave);

    remove_nave(naves);

    printf("\nNaves: %d\n", ultima_nave);

    remove_nave(naves);

    printf("\nNaves: %d\n", ultima_nave);

    return 0;
}
