#include <stdio.h>
#include <stdlib.h>

FILE *arq;
int temp;
char retorno[2];

void menu(){
    int opcao;
    do {         
        printf("LEITURA DE TEMPERATURA DO SENSOR\n");
        printf("1 - Exibir todas as temperaturas armazenadas no arquivo\n");
        printf("2 - Exibir a maior temperatura\n");
        printf("3 - Exibir a menor temperatura\n");
        printf("4 - Fim do Programa\n");
        printf("\nDigite a opção desejada: ");
        scanf(" %i%*c", &opcao);
        switch(opcao) {
            case 1: exibeTodas(); break;
            case 2: exibeMaior(); break;
            case 3: exibeMenor(); break;
            case 4: printf("\nFim do programa"); break;
            default : printf("Opção Inválida!!\n");
            system("pause");
            break;
        }
    } while (opcao != 4);
}

void testeArq(){
        
        arq = fopen("temperatura.txt", "rt");
        if (arq==NULL) {
		printf("Arquivo não existe.");
		exit(1);
        }
}

void exibeTodas(){

        testeArq();

        char c;

    	c=getc(arq);
	    while (c!=EOF){
	    printf("%c", c);
	    c=getc(arq);
	}
}

void comparação(){
    char texto[14], resto[34];
    int temp, menor, maior, e1, e2;

    while (fscanf (arq,"%s %d  %s %i", texto, &temp,  resto, &e1)!= EOF) {

        printf("%d\n",temp);

        if (temp > maior && temp>=60) {
           maior = temp;
           menor = maior;
        }
        else if (temp > maior && temp>=60) maior = temp;
        else if (temp < menor && temp>=60) menor = temp;
    }

    retorno[0]=maior;
    retorno[1]=menor;
}
void exibeMaior(){
    char texto[14], resto[34];
    int temp, menor=0, maior=0;
    
    testeArq();

    while (fscanf (arq,"%s %d  %s", texto, &temp, resto)!= EOF) {

        //printf("%d\n",temp);
        
        if (temp > maior) maior = temp;
    }

    printf("Maior valor de temperatura: %i\n\n", maior);

    fclose(arq);
}

void exibeMenor(){
    char texto[14], resto[34];
    int temp, base=60, maior=60, menor=1032;
    
    testeArq();
    
    while (fscanf (arq,"%s %d  %s", texto, &temp, resto)!= EOF) {

        //printf("%d\n",temp);

        if (temp > maior && temp>=60) {
           maior = temp;
           printf("Maior1:%i Menor1:%i\n",maior, menor);
        }

        else if (temp<maior && temp<menor && temp>=60){ menor = temp; printf("Menor2:%i\n",menor);};
    }

    printf("Menor valor de temperatura: %d\n\n", menor);

    fclose(arq);
}

int main(){
    
    menu();
}