#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

/*Prototipação*/
void novoFilme(), procurarFilme();
int desativarFilme(), ativarFilme();

/* Struct do Cadastro de Filmes*/
struct filme{

    int id;
    char nome[60];
    char genero[15];
    int anoLanc;
    char diretor[45];
    int ativo;
    int locado;

}filmes;

//Criando Ponteiro do Arquivo
FILE *arquivoFilme;

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

void menuFilmes(){

    setlocale(LC_ALL,"portuguese");

    int op;

    do{
        system("CLS");

        printf("\n\n\t\t\t******** MENU FILMES *********\n\n\n");

        printf("\n(1) Cadastrar Filme\n");
        printf("\n(2) Ativar Filme\n");
        printf("\n(3) Desativar Filme\n");
        printf("\n(4) Procurar Filme\n");
        printf("\n(0) Voltar\n");
        printf("\nOpção:\t");
        scanf("%i", &op);

        system("CLS");

        switch(op){
        case 1:
            novoFilme();
            break;
        case 2:
            ativarFilme();
            break;
        case 3:
            desativarFilme();
            break;
        case 4:
            procurarFilme();
            break;
        case 0:
            break;
        default:
            printf("\n\n\t\t\t\tOpção Inválida!\n\n");
            system("pause");
            break;
        }
    }while(op != 0);

}

void novoFilme(){

    int r, id;

    //Lendo o ID
    //Id Começando Pelo 0
    filmes.id = 0;

    printf("\n\n\t\t\t\t********** NOVO FILME ***********\n\n");

    //Abrindo o Arquivo Filme A+ abre ou cria um arquivo texto para leitura
    arquivoFilme = fopen("filmes.dat", "r");

    //Se o ponteiro do Arquivo nao for nulo
    if(arquivoFilme != NULL){

        while(!feof(arquivoFilme))
            //Lê o arquivo e Armazena na Struct
            fread(&filmes, sizeof(struct filme), 1, arquivoFilme);

        fclose(arquivoFilme);
    }

    //Auto-Incremento de ID
    id = filmes.id + 1;

    filmes.id = id;

    //Cadastrando filme
    printf("Nome do filme: ");
    fflush(stdin);
    gets(filmes.nome);

    printf("Genero: ");
    gets(filmes.genero);

    printf("Ano de Lancamento: ");
    scanf("%i", &filmes.anoLanc);

    printf("Diretor: ");
    fflush(stdin);
    gets(filmes.diretor);

    filmes.ativo = 1;
    filmes.locado = 0;

    //Salvando o filme no arquivo
    arquivoFilme = fopen("filmes.dat", "a+");

    //Escreve no Arquivo
    r = fwrite(&filmes, sizeof(struct filme), 1, arquivoFilme);

    if(r)
        printf("--- FILME REGISTRADO ---\n");

    printf("ID: %i\nNome: %s\nGenero: %s\nAno de Lancamento: %i\nDiretor: %s\n\n\n",
           filmes.id, filmes.nome, filmes.genero, filmes.anoLanc, filmes.diretor);

    fclose(arquivoFilme);

    system("pause");
}

int desativarFilme(){

    int id_rem, r;

    gotoxy(10,10);
    arquivoFilme = fopen("filmes.dat", "r");

    printf("### LISTA DE FILMES ATIVOS ###\n\n");

    while(!feof(arquivoFilme)){
       if(fread(&filmes, sizeof(struct filme), 1, arquivoFilme)){
            if(filmes.ativo == 1)
                printf("ID: %i\tNome: %s\n", filmes.id, filmes.nome);
       }
    }

    fclose(arquivoFilme);

    free(arquivoFilme);

    gotoxy(1,1);
    printf("Informe o ID do filme que deseja DESATIVAR: ");
    scanf("%i", &id_rem);

    arquivoFilme = fopen("filmes.dat", "r");

    if(existeFilme(id_rem) == 0)
        return 0;

    //posiciona o cursor no começo do arquivo
    rewind(arquivoFilme);

    while(!feof(arquivoFilme)){
       if(fread(&filmes, sizeof(struct filme), 1, arquivoFilme)){

            if(filmes.id == id_rem){
                //printf("%i\n", filmes.ativo);
                break;
            }
       }
    }
    fclose(arquivoFilme);

    arquivoFilme = fopen("filmes.dat", "r+");
    rewind(arquivoFilme);

    //Esse Le de novo
    fseek(arquivoFilme, (id_rem - 1)*sizeof(struct filme), SEEK_SET);

    filmes.ativo = 0;
    //Grava o Arquivo
    r = fwrite(&filmes, sizeof(struct filme), 1, arquivoFilme);

    if(r)
        printf("\n\n\t\t\t\tFilme desativado com sucesso!\n\n\n");


    fclose(arquivoFilme);

    system("pause");
}

int ativarFilme(){

    int id_atv, r;

    gotoxy(10,10);
    arquivoFilme = fopen("filmes.dat", "r");

    printf("### LISTA DE FILMES DESATIVADOS ###\n\n");

    while(!feof(arquivoFilme)){
       if(fread(&filmes, sizeof(struct filme), 1, arquivoFilme)){
            if(filmes.ativo == 0)
                printf("ID: %i\tNome: %s\n", filmes.id, filmes.nome);
       }
    }

    fclose(arquivoFilme);

    free(arquivoFilme);

    gotoxy(1,1);
    printf("Informe o ID do filme que deseja ATIVAR: ");
    scanf("%i", &id_atv);

    arquivoFilme = fopen("filmes.dat", "r");

    if(existeFilme(id_atv) == 0)
        return 0;

    //posiciona o cursor no começo do arquivo
    rewind(arquivoFilme);

    while(!feof(arquivoFilme)){
       if(fread(&filmes, sizeof(struct filme), 1, arquivoFilme)){

            if(filmes.id == id_atv){
                //printf("%i\n", filmes.ativo);
                break;
            }
       }
    }
    fclose(arquivoFilme);

    arquivoFilme = fopen("filmes.dat", "r+");
    rewind(arquivoFilme);

    //Esse Le de novo
    fseek(arquivoFilme, (id_atv - 1)*sizeof(struct filme), SEEK_SET);

    filmes.ativo = 1;
    //Grava o Arquivo
    r = fwrite(&filmes, sizeof(struct filme), 1, arquivoFilme);

    if(r)
        printf("\n\n\t\t\t\tFilme ativado com sucesso!\n\n\n");


    fclose(arquivoFilme);

    system("pause");
}

void procurarFilme(){

    int id_f;
    char locado[25], ativo[25];

    arquivoFilme = fopen("filmes.dat", "r");

    printf("\n\n\t\t\t***Procura de Filmes***\n\n");

    printf("\n\nDigite o ID o filme OU 0 (zero) para listar todos: ");
    scanf("%i", &id_f);

    while(!feof(arquivoFilme)){

       if(fread(&filmes, sizeof(struct filme), 1, arquivoFilme)){

            if(filmes.locado == 1){
                strcpy(locado, "LOCADO");
            }else{
                strcpy(locado, "LIVRE PARA LOCAR");
            }

            if(filmes.ativo == 1){
                strcpy(ativo, "ATIVO");
            }else{
                strcpy(ativo, "DESATIVADO");
                strcpy(locado, "");
            }

            if((filmes.id == id_f) || (id_f == 0)){
                printf("\n####################\n");
                printf("\nID: %i\nNome: %s\nGenero: %s\nAno de Lancamento: %i\nDiretor: %s\n\n%s\n%s\n",
                filmes.id,filmes.nome, filmes.genero, filmes.anoLanc, filmes.diretor,locado,ativo);

            }

       }
    }
    printf("\n####################\n");

    fclose(arquivoFilme);

    system("pause");
}

int existeFilme(int id){

    int existe = 0;

    arquivoFilme = fopen("filmes.dat", "r");

    while(!feof(arquivoFilme)){

       if(fread(&filmes, sizeof(struct filme), 1, arquivoFilme)){
           if((filmes.id == id)){
               existe = 1;
               return existe;
           }
       }
    }

    printf("\n\n\t\t\t*****Este filme não existe!!!****\n\n");
    system("PAUSE");

    fclose(arquivoFilme);

    return existe;
}
