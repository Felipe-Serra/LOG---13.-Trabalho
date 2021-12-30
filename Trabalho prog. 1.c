#include <stdio.h>
#include <locale.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct ferramenta {
    int codigo;
    char nome[40];
    int qtde;
    float preco;
    float totalEstoque;
    float qtdeVenda;
    float custo;
} fer[17];

FILE *arq;

int achou=0, indice=0, index=0;
#define MAX 17

void limpaBufferTeclado();
void menu();
void exibeferramenta();
void inserirferramenta();
void inclusao();
void consultaG();
void consultaE();
void alteracao();
void exclusao();

int random() { 
    int x;
    srand(time(NULL));
    
    x = 1 + (rand() % 100);
    return x;
}

int main() {
    char nome_arquivo[]="ferramentas.txt";
    if (( arq = fopen( nome_arquivo, "r+"))==NULL){														
 	   if (( arq = fopen( nome_arquivo, "w+")) == NULL) {
          printf("O arquivo %s não pode ser aberto... \n ",nome_arquivo);
          printf("O programa termina aqui... \n\n");
          system("pause");
          exit(0);
        }
    }

    menu();

    printf("\nFechando o arquivo e saindo do programa...");
    fclose(arq);
    system("del ferramentas.txt");
    system("ren ArquivoAuxiliar.txt ferramentas.txt");
    return 0;
}

void limpaBufferTeclado() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void menu() {
    char opcao;
    do {         
        printf("Cadastro de Ferramentas\n");
        printf("I - Inclusão\n"); // Com problema ao finalizar
        printf("G - Consulta Geral\n"); // FUNCIONA, NÃO ALTERAR
        printf("E - Consulta Específica\n"); // FUNCIONA, NÃO ALTERAR
        printf("A - Alteração\n");
        printf("X - Exclusão\n"); //Não funcional
        printf("F - Fim do Programa\n");
        printf("\nDigite a opção desejada: ");
        scanf(" %c%*c", &opcao);
        switch(opcao) {
            case 'i':
                case 'I': inclusao(); break;
            case 'g':
                case 'G': consultaG(); break;
            case 'e':
                case 'E': consultaE(); break;
            case 'a':
                case 'A': alteracao(); break;
            case 'x':
                case 'X': exclusao(); break;
            case 'f':
                case 'F': printf("\nFim do programa"); break;
            default : printf("Opção Inválida!!\n");
        }
        
        limpaBufferTeclado();
    } while (opcao != 'f' && opcao != 'F');
}

void exibeferramenta (struct ferramenta fer) {
  printf ("Dados do registro\n");
  printf ("Código da ferramenta: %i\n", fer.codigo);
  printf ("Nome da ferramenta: %s\n", fer.nome);
  printf ("Qtde da ferramenta: %i\n", fer.qtde);
  printf ("Preço da ferramenta: %5.2f\n", fer.preco);
  printf("Valor total em estoque %.2f\n\n", fer.totalEstoque);
}

void inserirferramenta() {
    printf("O código desta ferrmaneta será: "); //%i\n", random());
    //fer[indice].codigo=random();
    scanf(" %i%*c", &fer[indice].codigo);
    
    printf("Digite o nome da ferramenta: ");
    gets(fer[indice].nome);

    printf("Digite a quantidade de ferramentas: ");
    scanf(" %i%*c", &fer[indice].qtde);

    printf("Digite o preço de ferramentas: ");
    scanf(" %f%*c", &fer[indice].preco);

    fer[indice].totalEstoque = (fer[indice].qtde * fer[indice].preco);
    printf("Valor total em estoque %.2f", fer[indice].totalEstoque);
    
}

void inclusao() {
    char nome[40];
    fseek(arq, 0, SEEK_SET);
    // Para garantir que a ferramenta não seja cadastrada duas vezes
    printf("Digite o nome da ferramenta a ser cadastrada: "); gets(nome);

    while(fread(&fer, sizeof(fer), 2, arq)) {
   	    if(strncmp(fer[indice].nome, nome, 40)==0) {
	        achou=1;
	        break;
        }
    }
    
    if(achou==1) {
        char visu;
        printf("\nNome da ferramenta já cadastrado! Deseja visualizar os dados das ferramentas cadastradas? ");
        scanf("%c", &visu);
        if(visu=='s' || visu=='S') {
            consultaG();
            limpaBufferTeclado();
        }
    }

    else {
   	    inserirferramenta();
        indice++;
        fwrite(&fer, sizeof(fer), 1, arq);
        printf("\n\nFerramenta cadastrada com sucesso!!\n");  
    }
   system("pause");
}

// FUNCIONA, NÃO ALTERAR
void consultaG() {
    system("cls");
    indice=0;
    printf("\n*********Ferramentas Cadastradas********\n");
    fseek(arq, 0, SEEK_SET);
    
    while (fread(&fer, sizeof(fer), 1, arq)) {
       if(fer[indice].codigo!=9999) {
       	    exibeferramenta (fer[indice]);
            indice++;
	    }
    }
    system("pause");
}
// FUNCIONA, NÃO ALTERAR
void consultaE() {
    indice=0;
    system("cls"); //Limpa a tela 
    printf("\n*********Ferramentas Cadastradas********\n");
    fseek(arq, 0, SEEK_SET);
    printf("Digite o código da ferramenta:");
    scanf("%i", &index);
      
   while(fread(&fer, sizeof(fer), 1, arq)) {
   	    if(fer[indice].codigo==index && fer[indice].codigo!=9999) {
            exibeferramenta (fer[indice]);

            system("pause");
            achou=1;
        }
        else if(fer[indice].codigo>=9999) printf("\nLimite de ferramentas cadastradas atingido!!\n");
    }
   if(achou!=1) {
   	  printf( "\n\n\nCódigo não encontrado\n\n");
      system("pause");
    }

}

void alteracao() {
    char resp;
    indice=0;
    fseek(arq, 0, SEEK_SET);
    
    printf("Digite o código do produto a ser consultado: ");
    scanf(" %i%*c", &index);

    while(fread(&fer, sizeof(fer), 1, arq)) {
   	    if(fer[indice].codigo==index) {
	        achou=1;
	        break;
        }
    }

    if(achou==1) {
       exibeferramenta (fer[indice]);
       printf("\nDeseja realmente alterar? (S/N) ");
       scanf(" %c%*c",&resp);

	   if((resp=='s') || (resp == 'S')) {
            inserirferramenta();
		    fseek(arq, sizeof(fer) * -1, SEEK_CUR);
	        fwrite(&fer, sizeof(fer), 1, arq);
	        printf("\nDados foram alterados\n");
        }  
        else printf("\nDados não foram alterados\n");             
    }

   else printf("\nCódigo não cadastrado\n");  
   system("pause");
}

void exclusao() {
    char resp;
    FILE *arqAux;

    system("cls");
    fseek(arq, 0, SEEK_SET);

    printf("Digite o código da ferramenta:");
    scanf("%i%*c", &index);

    while(fread(&fer, sizeof(fer), 1, arq)) {
   	    if(fer[indice].codigo==index) {
	        achou=1;
	        break;
        }
    }

    if(achou==1) {
       exibeferramenta (fer[indice]);
       printf("\nDeseja realmente excluir ? (S/N)");
       scanf("%c%*c",&resp);
	   if((resp=='s') || (resp == 'S')) {
	        arqAux = fopen("ArquivoAuxiliar.txt", "w");

            while (fread(&fer, sizeof(fer), 1, arq)) {
                if(fer[indice].codigo!=9999)
                    fwrite(&fer, sizeof(fer), 1, arqAux);
            }
        }
	    else printf("\nDados não foram excluidos!!!\n");    
    }
    else printf("\nCódigo não cadastrado\n");
    fclose(arqAux);      
    system("pause");
}
