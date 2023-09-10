#include <stdio.h>
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

    int read1 = 0;
    int records1 = 0;
    int read2 = 0;
    int records2 = 0;

    int i;

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

        for(i = 0; i < naves[records1].lotacao; i++){
            
            naves[records1].passageiro = (struct Tripulacao*)malloc(naves[records1].lotacao*sizeof(struct Tripulacao));

            read1 = fscanf(file2,
                                "%50[^,],%d,%d,%d,%d,%d,%d,%50[^,],%d,%d\n",
                                naves[records1].passageiro[records2].nome,
                                &naves[records1].passageiro[records2].idade,
                                &naves[records1].passageiro[records2].IsCrianca,
                                &naves[records1].passageiro[records2].IsIdoso,
                                &naves[records1].passageiro[records2].IsEnfermo,
                                &naves[records1].passageiro[records2].IsClandestino,
                                &naves[records1].passageiro[records2].IsNobre,
                                naves[records1].passageiro[records2].planeta,
                                &naves[records1].passageiro[records2].prioridade_pessoal,
                                &naves[records1].passageiro[records2].identificador);

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
        }
        records2 = 0;

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

    fclose(file1);
    fclose(file2);

    /*------------------------------------------------------------------------------*/

    return 0;
}
