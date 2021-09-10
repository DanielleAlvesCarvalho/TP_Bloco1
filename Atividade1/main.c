#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_VEICULOS 10
#define TIMER 10

//definição da struct placa
typedef struct{
    char letrasPlaca[4];
    char numPlaca[5];
} Placa;

//definição da struct veículo
typedef struct {
	char marca[40], modelo[40], situacao[10];
	int anoFabricacao;
	Placa placa;
} Veiculo;

//inicio do programa
int main(){
    //permite o uso de acentos
    setlocale(LC_ALL, "Portuguese");

    //declara a struct
    Veiculo v[MAX_VEICULOS];

    //chama a função menu
    menu(v);
}

//menu
void menu(Veiculo *v){

    //declaração das variaveis
	int opc, ano;
	char modelo[40];

    //limpa a tela
    system("cls");

    //visualização do menu
	printf("----------------------------Menu----------------------------\n\n");
	printf("\n 1 - Listar os veículos cadastrados");
	printf("\n 2 - Inserir um novo veículo");
	printf("\n 3 - Listar os veículos filtrando-se por ano de fabricação");
	printf("\n 4 - Listar os veículos filtrando-se pelo modelo");
	printf("\n 5 - Sair \n");
	printf("\nDigite a opção desejada: ");
	scanf("%d", &opc);

	//limpa o buffer
    getchar();

    //analisa a opção desejada e encaminha o programa para função correspondente
	switch(opc){
		case 1:
			Lista(v);
			break;
		case 2:
			Cadastro(v);
			break;
		case 3:
            printf("Digite o ano de fabricação:");
            scanf("%d", &ano);
			ListaPorAno(v,ano);
			break;
		case 4:
			printf("Digite o modelo:");
			scanf("%s", &modelo);
			ListaPorModelo(v,modelo);
			break;
		case 5:
			exit(1);
			break;
		default:
			printf("Opção Inválida");
			break;
	}
}

//cadastro
void Cadastro(Veiculo *v) {

    //declaração das variaveis
	int i, veiculos;
	char situacao[] = "ativo";

    veiculos = 0;
    //verifica qual célula do vetor esta vazia
    for(i = 0; i < MAX_VEICULOS; i++){
        if(strcmp(v[i].situacao, situacao) != 0) {

            system("cls");

            //começa o cadastro
            printf("\n--------Cadastro de veículo---------\n");

            printf("\nMarca do veículo..................: ");
            scanf("%s", &v[i].marca);

            printf("\nModelo do veículo.................: ");
            scanf("%s", &v[i].modelo);

            printf("\nAno de fabricação do veículo......: ");
            scanf("%d", &v[i].anoFabricacao);

            printf("\nPlaca do veículo (apenas letras)..: ");
            scanf("%s", &v[i].placa.letrasPlaca);

            printf("\nPlaca do veículo (apenas numeros).: ");
            scanf("%s", &v[i].placa.numPlaca);

            //indica que aquela celula do vetor v esta cheia
            strcpy(v[i].situacao,"ativo");
            system("cls");
            OrdenaVetores(v);
            printf("Veículo cadastrado com sucesso! :)");
            Redirecionar(v, 1);
        } else {
            veiculos++;
        }
    }
    if(veiculos == MAX_VEICULOS){
        printf("\nCapacidade máxima (%d) de veículos cadastrados atingida!!!\n", MAX_VEICULOS);
        Redirecionar(v, 1);
    }
}

//ordena os vetores por ordem de ano de fabricação
void OrdenaVetores(Veiculo *v) {

    //declaração das variaveis
    Veiculo aux;
	int i, count, opc;

    //ordena os vetores por ordem de ano de fabricação usando o método bubblesort
    for(count = 1; count < MAX_VEICULOS; count++) {
        for(i = 0; i < MAX_VEICULOS - 1; i++){
            if(v[i].anoFabricacao > v[i + 1].anoFabricacao){

                //guarda o valor da celula de um vetor em uma variavel auxiliar
                aux.anoFabricacao = v[i].anoFabricacao;
                strcpy(aux.marca, v[i].marca);
                strcpy(aux.modelo, v[i].modelo);
                strcpy(aux.placa.letrasPlaca, v[i].placa.letrasPlaca);
                strcpy(aux.placa.numPlaca, v[i].placa.numPlaca);
                strcpy(aux.situacao, v[i].situacao);

                //substitui o valor da celula do vetor pela celula do vetor seguinte
                v[i].anoFabricacao = v[i + 1].anoFabricacao;
                strcpy(v[i].marca, v[i + 1].marca);
                strcpy(v[i].modelo, v[i + 1].modelo);
                strcpy(v[i].placa.letrasPlaca, v[i + 1].placa.letrasPlaca);
                strcpy(v[i].placa.numPlaca, v[i + 1].placa.numPlaca);
                strcpy(v[i].situacao, v[i + 1].situacao);

                //atribui o conteudo da variavel auxiliar na celula do proximo vetor
                v[i + 1].anoFabricacao = aux.anoFabricacao;
                strcpy(v[i + 1].marca, aux.marca);
                strcpy(v[i + 1].modelo, aux.modelo);
                strcpy(v[i + 1].placa.letrasPlaca, aux.placa.letrasPlaca);
                strcpy(v[i + 1].placa.numPlaca, aux.placa.numPlaca);
                strcpy(v[i + 1].situacao, aux.situacao);
            }
        }
    }
}

//lista
int Lista(Veiculo *v){
	int i, veiculos;
    char situacao[] = "ativo";

	system("cls");

    veiculos = 0;
	for(i = 0; i < MAX_VEICULOS; i++){
        if(strcmp(v[i].situacao, situacao) == 0){
            printf("\n------------Veículo------------\n");
            printf("\nMarca do veículo ..............: %s",v[i].marca);
            printf("\nModelo do veículo..............: %s",v[i].modelo);
            printf("\nAno de fabricação do veículo...: %d",v[i].anoFabricacao);
            printf("\nPlaca do veículo...............: %s-%i \n\n",v[i].placa.letrasPlaca, v[i].placa.numPlaca);
            veiculos++;
        }
	}
    if(veiculos == 0){
        printf("\nNenhum veículo registrado no sistema.\n\n\n");
    }
	Redirecionar(v, 2);
}

//listagem por ano
int ListaPorAno(Veiculo *v, int *ano){
    int i, veiculos;
    char situacao[] = "ativo";

	system("cls");

	veiculos = 0;
	for(i = 0; i < MAX_VEICULOS; i++){
        if(strcmp(v[i].situacao, situacao) == 0 && v[i].anoFabricacao == ano){
            printf("\n------------Veículo------------\n");
            printf("\nMarca do veículo ..............: %s",v[i].marca);
            printf("\nModelo do veículo..............: %s",v[i].modelo);
            printf("\nAno de fabricação do veículo...: %d",v[i].anoFabricacao);
            printf("\nPlaca do veículo...............: %s-%i \n\n",v[i].placa.letrasPlaca, v[i].placa.numPlaca);
            veiculos++;
        }
	}
    if(veiculos == 0){
        printf("\nNenhum veículo com ano %d encontrado no sistema.\n\n\n", ano);
    }
	Redirecionar(v, 3);
}

//listagem por modelo
int ListaPorModelo(Veiculo *v, char *modelo){
    int i, veiculos;
    char situacao[] = "ativo";

	system("cls");

	veiculos = 0;
	for(i = 0; i < MAX_VEICULOS; i++){
        if(strcmp(v[i].situacao, situacao) == 0 && strcmp(v[i].modelo, modelo) == 0 ){
            printf("\n------------Veículo------------\n");
            printf("\nMarca do veículo ..............: %s",v[i].marca);
            printf("\nModelo do veículo..............: %s",v[i].modelo);
            printf("\nAno de fabricação do veículo...: %d",v[i].anoFabricacao);
            printf("\nPlaca do veículo...............: %s-%i \n\n",v[i].placa.letrasPlaca, v[i].placa.numPlaca);
            veiculos++;
        }
	}
    if(veiculos == 0){
        printf("\nNenhum veículo com modelo %s encontrado no sistema.\n\n\n", modelo);
    }
	Redirecionar(v, 4);
}

//redireciona o usuario para o menu
void Redirecionar(Veiculo *v, int caminho){

    int opc;

    printf("\nDeseja voltar para o menu?");
    printf("\n1 - Sim");
    printf("\n2 - Não");
    printf("\nDigite a opção desejada: ");
    scanf("%d", &opc);

    if(opc == 1){
        menu(v);
    } else {
        switch(caminho){
            case 1:
                Cadastro(v);
                break;
            case 2:
                exit(1);
                break;
            case 3:
                exit(1);
                break;
            case 4:
                exit(1);
                break;
        }
    }
}
