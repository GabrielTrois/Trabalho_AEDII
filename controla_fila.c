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

    struct Naves naves[1000];
    struct Tripulacao passageiro[330];

    int read1 = 0;
    int records1 = 0;
    int read2 = 0;
    int records2 = 0;

    int i, j;

    do{
        read2 = fscanf(file1,
                            "%50[^,],%50[^,],%50[^,],%d,%d,%d,%d,%d\n",
                            naves[records1].recursos.compartimento1,
                            naves[records1].recursos.compartimento2,
                            naves[records1].recursos.compartimento3,
                            &naves[records1].recursos.code[0],
                            &naves[records1].recursos.code[1],
                            &naves[records1].recursos.code[2],
                            &naves[records1].lotacao,
                            &naves[records1].prioridade);

                            naves->ultimo_codigo = records1;
        if(read2 == 8){
            records1++;
        }

        if (read2 != 8 && !feof(file1)){
            printf("Formato de arquivo incorreto.\n");
            return 1;
        }

        if (ferror(file1)){
            printf("Erro ao ler o arquivo.\n");
        }
    } while (!feof(file1));

    do{
        read1 = fscanf(file2,
                            "%50[^,],%d,%d,%d,%d,%d,%d,%50[^,],%d,%d\n",
                            passageiro[records2].nome,
                            &passageiro[records2].idade,
                            &passageiro[records2].IsCrianca,
                            &passageiro[records2].IsIdoso,
                            &passageiro[records2].IsEnfermo,
                            &passageiro[records2].IsClandestino,
                            &passageiro[records2].IsNobre,
                            passageiro[records2].planeta,
                            &passageiro[records2].prioridade_pessoal,
                            &passageiro[records2].identificador);

        if(read1 == 10){
            records2++;
        }

        if (read1 != 10 && !feof(file2)){
            printf("Formato de arquivo incorreto.\n");
            return 1;
        }

        if (ferror(file2)){
            printf("Erro ao ler o arquivo.\n");
        }

    } while (!feof(file2));

    fclose(file1);
    fclose(file2);

    for(i = 0; i < 330; i++) {
        naves[i].passageiro = (struct Tripulacao*)malloc(naves[i].lotacao*sizeof(struct Tripulacao));
        for(j = 0; j < naves[i].lotacao; j++) {
            
            strcpy(naves[i].passageiro[j].nome, passageiro[j].nome);
            naves[i].passageiro[j].idade = passageiro[j].idade;
            
            naves[i].passageiro[j].IsCrianca = passageiro[j].IsCrianca;
            naves[i].passageiro[j].IsIdoso = passageiro[j].IsIdoso;
            naves[i].passageiro[j].IsClandestino = passageiro[j].IsClandestino;
            naves[i].passageiro[j].IsNobre = passageiro[j].IsNobre;
            
            naves[i].passageiro[j].identificador = passageiro[j].identificador;
            naves[i].passageiro[j].prioridade_pessoal = passageiro[j].prioridade_pessoal;
        }
    }

    /*------------------------------------------------------------------------------*/

    imprime_nave(naves[0]);

    //imprime_tripulacao(naves[0].passageiro, naves[0].lotacao);

    return 0;
}
