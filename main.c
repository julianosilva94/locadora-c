#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/*Protótipos MAIN*/
void menuFilmes(),menuClientes(),menuControle();

int main(){

    setlocale(LC_ALL,"portuguese");

    int op;

    //Menu Principal
    do{
        printf("\n\n\t\t\t***** LOCADORA NETFLIX *****\n\n\n");

        printf("(1) Filmes\n");
        printf("\n(2) Clientes\n");
        printf("\n(3) Controle do emp/dev\n");
        printf("\n(0) Sair\n");
        printf("\nOpção:\t");
        scanf("%i", &op);

        system("CLS");

        switch(op){
        case 1:
            menuFilmes();
            break;
        case 2:
            menuClientes();
            break;
        case 3:
            menuControle();
            break;
        case 0:
            break;
        default:
            printf("\n\n\t\t\t*****Opção Inválida!******\n\n");
            break;
        }
    }while(op != 0);

    return 0;
}
