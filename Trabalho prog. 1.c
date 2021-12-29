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

int achou=0, indice=0;
int index;

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
    system("del ferramentas.dat");
    system("ren ArquivoAuxiliar.dat ferramentas.dat");
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
        printf("I - Inclusão\n");
        printf("G - Consulta Geral\n");
        printf("E - Consulta Específica\n");
        printf("A - Alteração\n");
        printf("X - Exclusão\n"); //Não funcional
        printf("F - Fim do Programa\n");
        printf("\nDigite a opção desejada: ");
        scanf("%c%*c", &opcao);
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
  printf("Valor total em estoque %.2f\n", fer.totalEstoque);
}

void inserirferramenta() {
    printf("O código desta ferrmaneta será: %i", random());
    
    printf("Digite o nome da ferramenta: ");
    gets(fer[indice].nome);

    printf("Digite a quantidade de ferramentas: ");
    scanf("%i%*c", &fer[indice].qtde);

    printf("Digite o preço de ferramentas: ");
    scanf("%f%*c", &fer[indice].preco);

    fer[indice].totalEstoque = (fer[indice].qtde * fer[indice].preco);
    printf("Valor total em estoque %.2f", fer[indice].totalEstoque);
    
}

void inclusao() {
    fseek(arq, 0, SEEK_SET);

    // Para garantir que a ferramenta não seja cadastrada duas vezes
    while(fread(&fer, sizeof(fer), 1, arq)) {
   	    if(fer[indice].codigo==index) {
	        achou=1;
	        break;
        }
    }

    if(achou==1) {
        char visu;
        printf("\nCódigo da ferramenta já cadastrado! Deseja visualizar os dados das ferramentas cadastradas?");
        scanf("%c", &visu);
        if(visu=='s' || visu=='C') {
            consultaG();
        }
    }

    else {
   	    fer[indice].codigo=index;
   	   
        inserirferramenta();
        indice++;
        fwrite(&fer, sizeof(fer), 1, arq);
        printf("\n\nFerramenta cadastrada com sucesso!!\n");  
    }
   system("pause");
}

void consultaG() {
    system("cls");
    printf("\n*********Ferramentas Cadastradas********\n");
    fseek(arq, 0, SEEK_SET);
    
    while (fread(&fer, sizeof(fer), 1, arq)) {
       if(fer[indice].codigo!=9999) {
       	    exibeferramenta (fer);
	    }
    }
    limpaBufferTeclado();
    system("pause");
    limpaBufferTeclado();
}

void consultaE() {
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
        else printf("\nLimite de ferramentas cadastradas atingido!!\n");
    }
   if(achou!=1) {
   	  printf( "\n\n\nCódigo não encontrado\n\n");
      system("pause");
    }

}

void alteracao() {
    char resp;
    fseek(arq, 0, SEEK_SET);
    
    printf("Digite o código do produto a ser consultado: ");
    scanf("%i", &index);

    while(fread(&fer, sizeof(fer), 1, arq)) {
   	    if(fer[indice].codigo==index) {
	        achou=1;
	        break;
        }
    }

    if(achou==1) {
       exibeferramenta (fer[indice]);
       printf("\nDeseja realmente alterar? (S/N)");
       scanf("%c%*c",&resp);

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
	        arqAux = fopen("ArquivoAuxiliar.dat", "w");

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
