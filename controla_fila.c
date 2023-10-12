#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
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

    int atual = 1;
    int op;
    int mensagem = 1;
    
    while(1) {
        printf("Existe %d naves na fila\n", ultima_nave + 1);
        printf("Exibindo nave na posicao %d da fila\n\n", atual);
        imprime_nave(naves[atual-1]);

        printf("1 - Exibir nave\n");
        printf("2 - Adicionar nave\n");
        printf("3 - Liberar Nave\n");
        printf("4 - Imprime fila completa\n");
        printf("5 - Imprime passageiros da nave\n");
        if(mensagem == 1) {
            printf("6 - Exibir mensagens(1)\n");
        } else {
            printf("6 - Exibir mensagens\n");
        }

        printf("Digite a operacao: ");
        scanf("%d", &op);
        printf("\n");

        switch (op)
        {
        case 1:
            printf("Digite a posicao da nave na fila: ");
            scanf("%d", &atual);
            if(atual > ultima_nave + 1 || atual < 1) {
                printf("Posicao fora da fila\n\n");
                system("pause");
                atual = 1;
            }
            break;
        case 2:
            printf("Insira as informacoes da Nave\n");
            system("pause");
            system("cls");
            printf("Nave inserida na posicao %d\n", inserir_nave(naves, recursos));
            system("pause");
            break;
        
        case 3:
            remove_nave(naves);
            printf("Nave(s) Removida(s)\n");
            system("pause");
            break;

        case 4:
            system("cls");
            for(i = 0; i < ultima_nave + 1; i++){
                printf("Exibindo nave na posicao %d da fila\n\n", i+1);
                imprime_nave(naves[i]);
                printf("\n");
            }
            system("pause");
            break;
        
        case 5:
            system("cls");
            printf("Exibindo Tripulantes da Nave de posicao %d da fila\n\n");
            imprime_tripulacao(naves[atual-1].passageiro, naves[atual-1].lotacao);
            system("pause");
            break;

        case 6:
            system("cls");
            printf("IMPORTANTE - Novas instrucoes\n");
            printf("Foi observado dilatacoes na fenda de passagem das naves, permitindo que mais naves passem de uma vez.\n");
            printf("Esta anomalia causa com que a fenda se abra em ate X vezes, sendo X a quantidade da naves na fila que carregam permutacoes dos mesmos recursos\n");
            printf("Porem tome cuidado!!! Ao passar muitas naves ao mesmo tempo ha a chance da fenda fechar destruindo as naves\n");
            mensagem = 0;
            system("pause");
            break;
        
        default:
            printf("Insira uma operacao valida\n");
            system("pause");
            break;
        }

        system("cls");
    }

    return 0;
}
