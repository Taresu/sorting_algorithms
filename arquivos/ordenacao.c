#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void BubbleSort (int *vetor, int tamanho) {

  // If aninhado p/ percorrer o vetor e fazer as iterações
  for(int i=0; i<tamanho; i++) {
    for(int j=0; j<tamanho-1; j++) {
      // se o elem da pos atual é maior do que o da próxima pos, "troca-se os elementos de posição"
      if(vetor[j] > vetor[j+1]) {
        int aux = vetor[j]; // var auxiliar recebe o valor do vet na pos atual
        vetor[j] = vetor[j+1];
        vetor[j+1] = aux;
      }
    }
  }
}

void SelectionSort (int *vetor, int tamanho) {

  for(int i = 0; i<tamanho ; i++) {
    
    // Identificação do index mínimo
    int ind_min = i; // índice do valor mínimo (p/ iterações ainda não feitas)
    for(int j = i + 1; j<tamanho ; j++) {
      if(vetor[j] < vetor[ind_min])
        ind_min = j; // atualiza a posição em que o elem min está
    }

    // Substituição trivial - "troca os elementos de posição"
    /*
    (1): Copia o valor da pos mais à esquerda do vetor, p/ a var aux  
    (2): Altera o valor do vetor na pos desejada (mais à esquerda) p/ o do index min
    (3): Modifica o valor do index min, atribuindo o valor de aux
    */
    int aux = vetor[i]; // (1)
    vetor[i] = vetor[ind_min]; // (2)
    vetor[ind_min] = aux; // (3)
  }
}

void InsertionSort (int *vetor, int tamanho) {

  // Deve-se criar um tam temp (gradativo) de deck p/ facilitar a ordenação
  // Os elementos à esquerda da chave devem trocar de pos com ela, caso forem maiores
  for (int i = 1; i < tamanho; i++) {
    for (int j = i; j > 0 && vetor[j-1] > vetor[j]; j--) {
      int key = vetor[j]; //armazena a chave (elem "fixo" q será comp/do)
      vetor[j] = vetor[j-1]; 
      vetor[j-1] = key;
    }
  }
}

void Imprimir (int *A, int tamanho) {
  int i;
  for (i = 0; i < tamanho; i++) {
    printf("%d, ", A[i]);
  }
  printf("\n");
}

/*Função que retorna 1 se a ordenação estiver correta e 0 caso contrário.*/
int Verifica_Ordenacao (int *A, int tamanho) {
  int i;
  for (i = 0; i < tamanho-1; i++) {
    if (A[i] > A[i+1]) {
      return 0;
    }
  }
  return 1;
}

int main () {

  clock_t start, end;
  double elapsed_time;
  srand(time(NULL));

  int i;

  int tamanho;

// CÁLCULO DO TEMPO DE RESPOSTA P/ 10, 100, 1.000, 10.000 E 100.000 ELEMENTOS
  for (int k=10; k<=100000; k = k * 10) {
    tamanho = k;

    int *v1 = (int *)malloc(tamanho * sizeof(int));
    int *v2 = (int *)malloc(tamanho * sizeof(int));
    int *v3 = (int *)malloc(tamanho * sizeof(int));

    for (i = 0; i < tamanho; i++) {
      v1[i] = rand() % (tamanho+1);
      v2[i] = rand() % (tamanho+1);
      v3[i] = rand() % (tamanho+1);
    }  

    start = clock();
    //Imprimir(v1, tamanho);
    BubbleSort (v1, tamanho);
    //Imprimir(v1, tamanho);
    end = clock();
    elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
    if(k>=1000)
      printf("Tempo de execucao p/ %d.000 elementos (BubbleSort): %.2f\n", k/1000, elapsed_time);
    else
      printf("Tempo de execucao p/ %d elementos (BubbleSort): %.2f\n", k, elapsed_time);
    if (!Verifica_Ordenacao(v1, tamanho)) {
      printf("Erro: a ordenacao do BubbleSort nao esta correta!\n");
    } 

    start = clock();
    //Imprimir(v2, tamanho);
    SelectionSort (v2, tamanho);
    //Imprimir(v2, tamanho);
    end = clock();
    elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
    if(k>=1000)
      printf("Tempo de execucao p/ %d.000 elementos (SelectionSort): %.2f\n", k/1000, elapsed_time);
    else
      printf("Tempo de execucao p/ %d elementos (SelectionSort): %.2f\n", k, elapsed_time);
    if (!Verifica_Ordenacao(v2, tamanho)) {
      printf("Erro: a ordenacao do SelectionSort nao esta correta!\n");
    }
  
    start = clock();
    //Imprimir(v3, tamanho);
    InsertionSort (v3, tamanho);
    //Imprimir(v3, tamanho);
    end = clock();
    elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
    if(k>=1000)
      printf("Tempo de execucao p/ %d.000 elementos (InsertionSort): %.2f\n", k/1000, elapsed_time);
    else
      printf("Tempo de execucao p/ %d elementos (InsertionSort): %.2f\n", k, elapsed_time);
    if (!Verifica_Ordenacao(v3, tamanho)) {
      printf("Erro: a ordenacao do InsertionSort nao esta correta!\n");
    }

    free(v1);
    free(v2);
    free(v3);

    printf("\n");

  }

// CÁLCULO DO TEMPO DE RESPOSTA P/ 250.000 ELEMENTOS
  tamanho = 250000;

  printf("Aguarde o benchmark com 250.000 elementos\n\n");

  int *v1 = (int *)malloc(tamanho * sizeof(int));
  int *v2 = (int *)malloc(tamanho * sizeof(int));
  int *v3 = (int *)malloc(tamanho * sizeof(int));

  for (i = 0; i < tamanho; i++) {
    v1[i] = rand() % (tamanho+1);
    v2[i] = rand() % (tamanho+1);
    v3[i] = rand() % (tamanho+1);
  }  

  start = clock();
  //Imprimir(v1, tamanho);
  BubbleSort (v1, tamanho);
  //Imprimir(v1, tamanho);
  end = clock();
  elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
  printf("Tempo de execucao p/ %d.000 elementos (BubbleSort): %.2f\n", tamanho/1000, elapsed_time);
  if (!Verifica_Ordenacao(v1, tamanho)) {
    printf("Erro: a ordenacao do BubbleSort nao esta correta!\n");
  } 

  start = clock();
  //Imprimir(v2, tamanho);
  SelectionSort (v2, tamanho);
  //Imprimir(v2, tamanho);
  end = clock();
  elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
  printf("Tempo de execucao p/ %d.000 elementos (SelectionSort): %.2f\n", tamanho/1000, elapsed_time);
  if (!Verifica_Ordenacao(v2, tamanho)) {
    printf("Erro: a ordenacao do SelectionSort nao esta correta!\n");
  }

  start = clock();
  //Imprimir(v3, tamanho);
  InsertionSort (v3, tamanho);
  //Imprimir(v3, tamanho);
  end = clock();
  elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
  printf("Tempo de execucao p/ %d.000 elementos (InsertionSort): %.2f\n", tamanho/1000, elapsed_time);
  if (!Verifica_Ordenacao(v3, tamanho)) {
    printf("Erro: a ordenacao do InsertionSort nao esta correta!\n");
  }

  printf("\n");

  free (v1);
  free (v2);  
  free (v3);

  return 0;
}
