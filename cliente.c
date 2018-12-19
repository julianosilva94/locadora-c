#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/*Prototipação*/
void novoCliente(), editarCliente();
int listarClientes();
int fseek(FILE *fp, long numbytes, int origem);

struct cliente{

    int id;
    char nome[50];
    char sobrenome[50];
    char cpf[20];
    char endereco[200];
    char dependente[50];
    int qtdLocados;

}clientes;

FILE *arquivoCliente;

/*Inicio da Função Menu Cliente*/
void menuClientes(){

    setlocale(LC_ALL,"portuguese");

    int op;

    /*Menu Clientes*/
    do{
        system("cls");
        printf("\n\n\t\t\t***** MENU CLIENTE *****\n\n\n");

        printf("(1) Cadastrar Cliente\n");
        printf("\n(2) Editar\n");
        printf("\n(3) Listar Clientes\n");
        printf("\n(0) Voltar\n");
        printf("\nOpção:\t");
        scanf("%i", &op);

        system("CLS");

        switch(op){
        case 1:
            novoCliente();
            break;
        case 2:
            editarCliente();
            break;
        case 3:
            listarClientes();
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

void novoCliente(){

    int r, id;

    //Lendo o ID

    clientes.id = 0;

    printf("++++++ NOVO CLIENTE ++++++\n\n");

    arquivoCliente = fopen("clientes.dat", "a+");
    if(arquivoCliente != NULL){

        while(!feof(arquivoCliente))
            fread(&clientes, sizeof(struct cliente), 1, arquivoCliente);

        fclose(arquivoCliente);
    }

    id = clientes.id + 1;

    clientes.id = id;

    //Cadastrando filme
    printf("Nome do cliente: ");
    fflush(stdin);
    gets(clientes.nome);

    printf("Sobrenome do cliente: ");
    gets(clientes.sobrenome);

    printf("CPF: ");
    gets(clientes.cpf);

    printf("Endereco completo: ");
    gets(clientes.endereco);

    printf("Dependente: ");
    gets(clientes.dependente);

    clientes.qtdLocados = 0;

    //Salvando o filme no arquivo
    arquivoCliente = fopen("clientes.dat", "a+");

    r = fwrite(&clientes, sizeof(struct cliente), 1, arquivoCliente);

    if(r)
        printf("--- CLIENTE REGISTRADO ---\n");

    printf("ID: %i\nNome: %s\nSobrenome: %s\nCPF: %s\nEndereco completo: %s\nDependente: %s\n\n",
           clientes.id, clientes.nome, clientes.sobrenome, clientes.cpf, clientes.endereco, clientes.dependente);

    fclose(arquivoCliente);

    system("pause");
}

void editarCliente(){

    /*prototipação de função*/
    int modificaNome(), modificaCPF(), modificaEndereco(), modificaDependente();

    int op;


    /*Menu*/
    do{
      system("CLS");

        printf("\n\n\t\t\t***** MENU DE EDICAO DE CLIENTES *****\n\n\n");
        printf("(1) Modificar nome completo do Cliente\n");
        printf("\n(2) Modificar CPF\n");
        printf("\n(3) Modificar endereco\n");
        printf("\n(4) Modificar dependente\n");
        printf("\n(0) Voltar\n");
        printf("\nOpção:\t");
        scanf("%i", &op);

        switch(op){

    case 1:
        modificaNome();
        break;
    case 2:
        modificaCPF();
        break;
    case 3:
        modificaEndereco();
        break;
    case 4:
        modificaDependente();
        break;
    case 0:
        break;
    default:
        printf("\n\nOpção Inválida!\n\n");
        system("pause");
       break;
        }

    }while(op !=0 );


}

int modificaNome(){

    int r, id_cliente;

    printf("Digite o ID do cliente: ");
    scanf("%i", &id_cliente);

    if(existeCliente(id_cliente) == 0)
        return 0;

    arquivoCliente = fopen("clientes.dat", "r+");

    rewind(arquivoCliente);

    while(!feof(arquivoCliente)){
        if(fread(&clientes, sizeof(struct cliente), 1, arquivoCliente)){
            if(clientes.id == id_cliente){

                printf("Informe o primeiro nome: ");
                fflush(stdin);
                gets(clientes.nome);

                printf("informe o sobrenome: ");
                fflush(stdin);
                gets(clientes.sobrenome);

                break;
            }
        }
    }

    fseek(arquivoCliente, (id_cliente - 1)*sizeof(struct cliente), SEEK_SET);
    r = fwrite(&clientes, sizeof(struct cliente), 1, arquivoCliente);

    if(r){
        printf("\nModificado com Sucesso!\n\n");
        system("pause");
    }
    fclose(arquivoCliente);
}


int modificaCPF(){

    int r, id_cliente;

    printf("Digite o ID do cliente: ");
    scanf("%i", &id_cliente);

    if(existeCliente(id_cliente) == 0)
        return 0;

    arquivoCliente = fopen("clientes.dat", "r+");

    rewind(arquivoCliente);

    while(!feof(arquivoCliente)){
        if(fread(&clientes, sizeof(struct cliente), 1, arquivoCliente)){
            if(clientes.id == id_cliente){

                printf("Informe o CPF: ");
                fflush(stdin);
                gets(clientes.cpf);

                break;
            }
        }
    }

    fseek(arquivoCliente, (id_cliente - 1)*sizeof(struct cliente), SEEK_SET);
    r = fwrite(&clientes, sizeof(struct cliente), 1, arquivoCliente);
    if(r){
        printf("\nModificado com Sucesso!\n\n");
        system("pause");
    }

    fclose(arquivoCliente);
}

int modificaEndereco(){

    int r, id_cliente;

    printf("Digite o ID do cliente: ");
    scanf("%i", &id_cliente);

    if(existeCliente(id_cliente) == 0)
        return;

    arquivoCliente = fopen("clientes.dat", "r+");

    rewind(arquivoCliente);

    while(!feof(arquivoCliente)){
        if(fread(&clientes, sizeof(struct cliente), 1, arquivoCliente)){
            if(clientes.id == id_cliente){

                printf("Informe o Endereco Complete: ");
                fflush(stdin);
                gets(clientes.endereco);

                break;
            }
        }
    }

    fseek(arquivoCliente, (id_cliente - 1)*sizeof(struct cliente), SEEK_SET);
    r = fwrite(&clientes, sizeof(struct cliente), 1, arquivoCliente);
    if(r){
        printf("\nModificado com Sucesso!\n\n");
        system("pause");
    }

    fclose(arquivoCliente);
}

int modificaDependente(){

    int r, id_cliente;

    printf("Digite o ID do cliente: ");
    scanf("%i", &id_cliente);

    if(existeCliente(id_cliente) == 0)
        return;

    arquivoCliente = fopen("clientes.dat", "r+");

    rewind(arquivoCliente);

    while(!feof(arquivoCliente)){
        if(fread(&clientes, sizeof(struct cliente), 1, arquivoCliente)){
            if(clientes.id == id_cliente){

                printf("Informe o Dependente: ");
                fflush(stdin);
                gets(clientes.dependente);

                break;
            }
        }
    }

    fseek(arquivoCliente, (id_cliente - 1)*sizeof(struct cliente), SEEK_SET);
    r = fwrite(&clientes, sizeof(struct cliente), 1, arquivoCliente);
    if(r){
        printf("\nModificado com Sucesso!\n\n");
        system("pause");
    }

    fclose(arquivoCliente);
}

int listarClientes(){

    int id_c, existe = 0;

    arquivoCliente = fopen("clientes.dat", "r");

    printf("\nDigite o ID do cliente OU 0 (zero) para listar todos clientes: ");
    scanf("%i", &id_c);

    /*if(id_c != 0){
        if(existeCliente(id_c) == 0)
            return 0;
    }*/

    while(!feof(arquivoCliente)){

       if(fread(&clientes, sizeof(struct cliente), 1, arquivoCliente)){

           if((clientes.id == id_c) || (id_c == 0)){
                existe = 1;
                printf("\n####################\n");
                printf("\nID: %i\nNome Completo: %s %s\nCPF: %s\nEndereco completo: %s\nDependente: %s\n\nQtd Filmes Locados: %i\n",
                        clientes.id, clientes.nome, clientes.sobrenome, clientes.cpf, clientes.endereco, clientes.dependente, clientes.qtdLocados);
           }

       }
    }
    printf("\n####################\n");

    fclose(arquivoCliente);

    if(existe == 0)
        printf("\n\nEste cliente não existe!!!\n\n");

    system("pause");
}

int existeCliente(int id){

    int existe = 0;

    arquivoCliente = fopen("clientes.dat", "r");

    while(!feof(arquivoCliente)){

       if(fread(&clientes, sizeof(struct cliente), 1, arquivoCliente)){
           if((clientes.id == id)){
               existe = 1;
               return existe;
           }
       }
    }

    fclose(arquivoCliente);

    printf("\n\nEste cliente não existe!!!\n\n");
    system("PAUSE");

    return existe;
}
