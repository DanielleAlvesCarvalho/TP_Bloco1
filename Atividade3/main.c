#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#define t 10

char ativo[10] = "ativo", inativo[10] = "inativo";
struct tm *data_hora_atual;

typedef struct{
    char nome[30];
    int anoNasc;
    float montante;
    int mesMontante;
    char situacao[10];
} Cliente;

void VerificaMes(Cliente *c, int tamanho){
    for(int i = 0; i <= tamanho; i++){
        if(strcmp(c[i].situacao,ativo) == 0){
            printf("Mês montante: %d\tMês atual: %d", c[i].mesMontante, data_hora_atual->tm_mon + 1);
            if(c[i].mesMontante != data_hora_atual->tm_mon + 1){
                printf("\nMontante do cliente %d zerado devido a virada do mês!\n", i+1);
                printf("\nValor do montante do mês passado: %.2f \n", c[i].montante);
                c[i].montante = 0;
                sleep(3);
            }
        }
    }
    Menu(c, tamanho, 1);
}

void Menu(Cliente *c, int tamanho, int verifica){
    int opc;

    if(verifica == 0){
        VerificaMes(c, tamanho);
    } else {
        verifica = 0;
    }

    system("cls");

    printf("----------------------Menu----------------------\n\n\n");
    printf("1 - Cadastrar novo cliente\n");
    printf("2 - Remover cliente\n");
    printf("3 - Atualizar montante de compras(mês %d)\n",data_hora_atual->tm_mon + 1);
    printf("4 - Listar melhor comprador\n");
    printf("5 - Listar o montante de um cliente específico\n");
    printf("0 - Sair");
    printf("\n\n\nDigite a opção desejada:");
    scanf("%d", &opc);

    switch(opc){
        case 1:
                Cadastrar(c, tamanho);
                break;
        case 2:
                RemoveCliente(c, tamanho);
                break;
        case 3:
                AtualizaMontante(c, tamanho);
                break;
        case 4:
                FiltroMontante(c, tamanho);
                break;
        case 5:
                FiltroCliente(c, tamanho);
                break;
        case 0:
                exit(1);
                break;
        default:
                printf("Opção Inválida!!!");
                sleep(2);
                Menu(c, tamanho, 1);
                break;
    }
}

void Cadastrar(Cliente *c, int tamanho){
    int clientes;

    system("cls");

    printf("----------------------Cadastro de cliente----------------------\n\n");
    for(int i = 0; i < tamanho; i++){
        if(strcmp(c[i].situacao,ativo) != 0){
            printf("\nCliente n°: %d\n", i + 1);
            printf("\nNome do Cliente: ");
            scanf("%s", &c[i].nome);
            printf("\nAno de Nascimento: ");
            scanf("%d", &c[i].anoNasc);
            printf("\nMontante de compras(mês %d): ",data_hora_atual->tm_mon + 1);
            scanf("%f", &c[i].montante);
            c[i].mesMontante = data_hora_atual->tm_mon + 1;
            strcpy(c[i].situacao,ativo);
            Redirecionar(c, 1, tamanho);
        } else {
            clientes++;
        }
    }
    if(clientes == tamanho) {
        Realocar(c, &tamanho);
    }
}

void Realocar(Cliente *c, int *tamanho){

    *tamanho = *tamanho + t;
    c = realloc(c,*tamanho*sizeof(Cliente));
    printf("Mais %d espaço(s) liberado(s)", t);
    sleep(1);
    Cadastrar(c, *tamanho);
}

int Lista(Cliente *c, int tamanho, int imprime){
    int clientes = 0;
    char ativo[10] = "ativo";
    system("cls");
    for(int i = 0; i <= tamanho; i++){
        if(strcmp(c[i].situacao,ativo) == 0){
            if(imprime == 1){
                ImprimeClientes(c, tamanho, i);
            }
            clientes++;
        }
    }
    return clientes;
}

void ImprimeClientes(Cliente *c, int tamanho, int i){
    printf("\nCliente n°: %d", i + 1);
    printf("\nNome do Cliente: %s", c[i].nome);
    printf("\nAno de Nascimento: %d", c[i].anoNasc);
    printf("\nMontante de compras(mês %d): %.2f\n",data_hora_atual->tm_mon + 1, c[i].montante);
}

void RemoveCliente(Cliente *c,int tamanho){
    char ativo[10] = "ativo", inativo[10] = "inativo";
    int n;
    if(Lista(c, tamanho, 1) == 0){
        printf("Nenhum cliente cadastrado!\n");
    } else {
        printf("\nDigite o número do cliente que deseja excluir: ");
        scanf("%d", &n);
        if(strcmp(c[n].situacao,ativo) == 0){
            strcpy(c[n-1].situacao,inativo);
            printf("\nCliente removido com sucesso!\n");
        } else {
            printf("\nNenhum cliente cadastrado com o número selecionado!\n");
        }
    }
    Redirecionar(c, 2, tamanho);
}

void AtualizaMontante(Cliente *c, int tamanho){
    int n;
    float valor;

    if(Lista(c, tamanho, 1) == 0){
        printf("Nenhum cliente cadastrado!\n");
    } else {
        printf("\nDigite o número do cliente que deseja alterar: ");
        scanf("%d", &n);
        if(strcmp(c[n].situacao,ativo) == 0){
            printf("\nDigite o valor que será adicionado ao montante: ");
            scanf("%f", &valor);
            c[n-1].montante = c[n-1].montante + valor;
        } else {
            printf("\nNenhum cliente cadastrado com o número selecionado!\n");
        }
    }
    Redirecionar(c, 3, tamanho);
}

void FiltroMontante(Cliente *c, int tamanho){
    float maiorMontante = MaiorMontante(c, tamanho);
    int i;
    if(Lista(c, tamanho, 0) == 0){
        printf("Nenhum cliente cadastrado!\n");
        Redirecionar(c, 4, tamanho);
    } else {
        for(i = 0; i < tamanho; i++){
            if(c[i].montante == maiorMontante){
                ImprimeClientes(c, tamanho, i);
            }
        }
    }
    Redirecionar(c, 4, tamanho);
}

MaiorMontante(Cliente *c, int tamanho){
    float montantes[tamanho], mt;
    int i, j;
    for(i = 0; i < tamanho; i++){
        if(strcmp(c[i].situacao,ativo) == 0){
            montantes[i] = c[i].montante;
        }
    }
    for(i = 0; i < tamanho; i++){
        for(j = i + 1; j < tamanho; j++){
            if(montantes[i] > montantes[j] && montantes[i] != 0 && montantes[j] != 0){
                mt = montantes[i];
                montantes[i] = montantes[j];
                montantes[j] = mt;
            }
        }
    }
    return mt;
}

void FiltroCliente(Cliente *c, int tamanho){
    char nome[30];
    int clientes, i;
    if(Lista(c, tamanho, 0) == 0){
        printf("Nenhum cliente cadastrado!\n");
    } else {
        printf("Digite o nome do cliente cadastrado: ");
        scanf("%s", &nome);

        for(i = 0; i < tamanho; i++){
            if(strcmp(c[i].nome,nome) == 0){
                ImprimeClientes(c, tamanho, i);
                clientes++;
            }
        }
            if(clientes == 0){
            printf("\nNenhum cliente cadastrado com esse nome!");
        }
    }
    Redirecionar(c, 5, tamanho);
}

void Redirecionar(Cliente *c, int caminho, int tamanho){

    int opc;

    printf("\nDeseja voltar para o menu?");
    printf("\n1 - Sim    2 - Não");
    printf("\nDigite a opção desejada: ");
    scanf("%d", &opc);

    if(opc == 1){
        Menu(c, tamanho, 0);
    } else {
        switch(caminho){
            case 1:
                Cadastrar(c, tamanho);
                break;
            default:
                exit(1);
                break;
        }
    }
}

int main(){
    time_t segundos;
    time(&segundos);
    data_hora_atual = localtime(&segundos);
    Cliente *c;
    int tamanho = t;
    c = malloc(tamanho*sizeof(Cliente));
    setlocale(LC_ALL, "Portuguese");
    Menu(c, tamanho, 0);
    free(c);
    return 0;
}
