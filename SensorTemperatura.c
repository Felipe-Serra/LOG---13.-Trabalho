#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE *arq;

void delay(int sec){ 

   int milli_s = 1000 * sec;
   clock_t start_time = clock();
   while (clock() < start_time + milli_s);
}

int temperatura () {

    int temp, sinal;

    time_t current_time;

    char* c_time_string;
    current_time = time(NULL);
    c_time_string = ctime(&current_time);

sinal = rand()%1023;
temp = (sinal*500)/1023;

printf("Temperatura:%d\n",temp);

FILE *arq;

   arq = fopen("temperatura.txt", "a");

    if(temp>=60){

     fprintf(arq, "Temperatura: %d° Data: %s\n", temp, c_time_string);
    }
}

int main () {
    
    srand(time(NULL));

 for(; ; ){ 

 delay(1);  
 temperatura(); 

    if(kbhit()){

     break;
    }
}
fclose(arq);
}