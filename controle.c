#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <locale.h>

/*Prototipação*/
int devolucao(),novoEmprestimo();
void consultarEmprestimos();
int fseek(FILE *fp, long numbytes, int origem);

struct controle{
    int id;
    int idFilme;
    int idCliente;
    char dataLocacao[11];
    char dataDevolucao[11];
    float preco;
    int devolvido;
    //int pago;

}controles;

struct filme{

    int id;
    char nome[60];
    char genero[15];
    int anoLanc;
    char diretor[45];
    int ativo;
    int locado;

}filmes;

struct cliente{

    int id;
    char nome[50];
    char sobrenome[50];
    char cpf[20];
    char endereco[200];
    char dependente[50];
    int qtdLocados;

}clientes;

FILE *arquivoControle;
FILE *arquivoFilme;
FILE *arquivoCliente;

/*Inicio da Função menu controle*/
void menuControle(){

    setlocale(LC_ALL,"portuguese");

    int op;

    /*Menu Controle*/
    do{
        system("CLS");
        printf("\n\n\t\t\t***** MENU CONTROLE *****\n\n\n");

        printf("(1) Empréstimo\n");
        printf("\n(2) Devolução\n");
        printf("\n(3) Consultar Empréstimos\n");
        printf("\n(0) Voltar\n");
        printf("\nOpção:\t");
        scanf("%i", &op);

        system("CLS");

        switch(op){
        case 1:
            novoEmprestimo();
            break;
        case 2:
            devolucao();
            break;
        case 3:
            consultarEmprestimos();
            break;
        case 0:
            break;
        default:
            printf("\n\nOpção Inválida!\n\n");
            system("pause");
            break;
        }
    }while(op != 0);
}

int novoEmprestimo(){

    int r,r2,r3, id, id_filme, id_cliente,pago,lanc, confirm, qtd;
    char nomefilme[200], nomecliente[200];

    free(arquivoControle);
    free(arquivoCliente);
    free(arquivoFilme);

    printf("\nInsira o ID do filme: ");
    scanf("%i", &id_filme);

    printf("\nInsira o ID do cliente: ");
    scanf("%i", &id_cliente);

    arquivoFilme = fopen("filmes.dat", "r");
    arquivoCliente = fopen("clientes.dat", "r");


    while(!feof(arquivoFilme)){
        if(fread(&filmes, sizeof(struct filme), 1, arquivoFilme)){
            if(filmes.id == id_filme){
                strcat(nomefilme, filmes.nome);
                break;
            }
        }
    }

    while(!feof(arquivoCliente)){
        if(fread(&clientes, sizeof(struct cliente), 1, arquivoCliente)){
            if(clientes.id == id_cliente){
                strcat(nomecliente, clientes.nome);
                strcat(nomecliente, " ");
                strcat(nomecliente, clientes.sobrenome);
                break;
            }
        }
    }

    fclose(arquivoFilme);
    fclose(arquivoCliente);

    controles.id = 0;

    arquivoControle = fopen("controles.dat", "r");

    if(arquivoControle != NULL){
        while(!feof(arquivoControle)){
            fread(&controles, sizeof(struct controle), 1, arquivoControle);
        }
    }

    fclose(arquivoControle);

    id = controles.id + 1;
    controles.id = id;

    controles.idFilme = id_filme;
    controles.idCliente = id_cliente;

    printf("\nInsira a data de hoje: (formato dd/mm/aaaa)\t");
    fflush(stdin);
    gets(controles.dataLocacao);

    printf("\nInsira a data de devolução: (formato dd/mm/aaaa)\t");
    fflush(stdin);
    gets(controles.dataDevolucao);

    printf("\nO filme é lancamento ? 1 - Sim 0 - Não\t");
    printf("\nOpção:\t");
    scanf("%i", &lanc);
    if(lanc == 1)
        controles.preco = 5.25;
    else
        controles.preco = 3.25;

    /*printf("\nVai se pago agora ? 1 - Sim 0 - Não\t");
    scanf("%i", &pago);
    if(pago == 1)
        controles.pago = 1;
    else
        controles.pago = 0;*/

    controles.devolvido = 0;

    printf("\nFilme: %s", nomefilme);
    printf("\nCliente: %s", nomecliente);
    printf("\nData de Devolução: %s", controles.dataDevolucao);
    printf("\nPreço: R$ %.2f", controles.preco);
    printf("\nConfirma emprestimo? 1 - Sim 0 - Não\t");
    printf("\nOpção:\t");
    scanf("%i", &confirm);
    if(confirm != 1)
        return 0;

    arquivoControle = fopen("controles.dat", "a+");

    r = fwrite(&controles, sizeof(struct controle), 1, arquivoControle);

    fclose(arquivoControle);

    arquivoCliente = fopen("clientes.dat", "r+");

    qtd = 0;

    while(!feof(arquivoCliente)){
        if(fread(&clientes, sizeof(struct cliente), 1, arquivoCliente)){
            if(clientes.id == id_cliente){
                qtd = clientes.qtdLocados + 1;
                clientes.qtdLocados = qtd;
                break;
            }
        }
    }

    fseek(arquivoCliente, (id_cliente - 1)*sizeof(struct cliente), SEEK_SET);
    r2 = fwrite(&clientes, sizeof(struct cliente), 1, arquivoCliente);

    fclose(arquivoCliente);

    arquivoFilme = fopen("filmes.dat", "r+");

    while(!feof(arquivoFilme)){
       if(fread(&filmes, sizeof(struct filme), 1, arquivoFilme)){

            if(filmes.id == id_cliente){

                filmes.locado = 1;
                break;
            }
       }
    }

    fseek(arquivoFilme, (id_filme - 1)*sizeof(struct filme), SEEK_SET);
    r3 = fwrite(&filmes, sizeof(struct filme), 1, arquivoFilme);

    fclose(arquivoFilme);

    if(r && r2 && r3)
        printf("\n\n--- EMPRÉSTIMO REGISTRADO ---\n");

    system("pause");

    return 0;
}

int devolucao(){

    int id_emp,r, r2,r3, qtd, id_cliente, id_filme, confirm, existe;

    printf("\nInsira o ID do empréstimo: ");
    scanf("%i", &id_emp);

    arquivoControle = fopen("controles.dat", "r");

    while(!feof(arquivoControle)){
            if(fread(&controles, sizeof(struct controle), 1, arquivoControle)){
                if(controles.id == id_emp){
                    existe = 1;
                    controles.devolvido = 1;
                    id_cliente = controles.idCliente;
                    id_filme = controles.idFilme;
                    break;
                }
            }
    }

    if(existe != 1){
        printf("\n\n EMPRÉSTIMO INVÁLIDO\n\n");
        system("pause");
        return 0;
    }

    fclose(arquivoControle);

    printf("\n\nValor a cobrar R$ %.2f\n", controles.preco);

    printf("\nConfirma devolução?  1 - SIM \t 0 - NÃO\n");
    printf("\nOpção:\t");
    scanf("%i", &confirm);

    if(confirm != 1)
        return 0;

    arquivoControle = fopen("controles.dat", "r+");

    fseek(arquivoControle, (id_emp - 1)*sizeof(struct controle), SEEK_SET);
    r = fwrite(&controles, sizeof(struct controle), 1, arquivoControle);

    fclose(arquivoControle);

    arquivoCliente = fopen("clientes.dat", "r");

    qtd = 0;

    while(!feof(arquivoCliente)){
        if(fread(&clientes, sizeof(struct cliente), 1, arquivoCliente)){
            if(clientes.id == id_cliente){
                break;
            }
        }
    }
    fclose(arquivoCliente);

    qtd = clientes.qtdLocados - 1;
    clientes.qtdLocados = qtd;

    arquivoCliente = fopen("clientes.dat", "r+");
    fseek(arquivoCliente, (id_cliente - 1)*sizeof(struct cliente), SEEK_SET);
    r2 = fwrite(&clientes, sizeof(struct cliente), 1, arquivoCliente);
    fclose(arquivoCliente);

    free(arquivoFilme);

    arquivoFilme = fopen("filmes.dat", "r");

    while(!feof(arquivoFilme)){
       if(fread(&filmes, sizeof(struct filme), 1, arquivoFilme)){
            if(filmes.id == id_filme){
                break;
            }
       }
    }

    fclose(arquivoFilme);

    arquivoFilme = fopen("filmes.dat", "r+");

    fseek(arquivoFilme, (id_filme - 1)*sizeof(struct filme), SEEK_SET);

    filmes.locado = 0;

    r3 = fwrite(&filmes, sizeof(struct filme), 1, arquivoFilme);
    fclose(arquivoFilme);

    if(r && r2 && r3)
        printf("\n\n####### FILME DEVOLVIDO ########\n\n");

    system("pause");
}

void consultarEmprestimos(){

    char devolvido[10], pago;

    arquivoControle = fopen("controles.dat", "r");

    printf("\n########## LISTA DE EMPRESTIMOS ##########\n");

    while(!feof(arquivoControle)){
            if(fread(&controles, sizeof(struct controle), 1, arquivoControle)){

                if(controles.devolvido == 1)
                    strcpy(devolvido, "SIM");
                else
                    strcpy(devolvido, "NÃO");

                /*
                if(controles.pago == 1)
                    pago = 'S';
                else
                    pago = 'N';
                */
                printf("\n####################\n");
                printf("\nID: %i", controles.id);
                printf("\nID do Filme: %i", controles.idFilme);
                printf("\nID do Cliente: %i", controles.idCliente);
                printf("\nData Devolução: %s", controles.dataDevolucao);
                printf("\nData Retirada: %s", controles.dataLocacao);
                printf("\n\nPreço: R$ %.2f", controles.preco);
                printf("\n\nDevolvido: %s\n", devolvido);
                //printf("\nPago: %c\n", pago);
            }
    }
    printf("\n####################\n");
    system("pause");
}
