#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Substituição trivial - "troca os elementos de posição"
/*
  (1): Copia o valor da pos mais à esquerda do vetor, p/ a var aux  
  (2): Altera o valor do vetor na pos desejada (mais à esquerda) p/ o do index min
  (3): Modifica o valor do index min, atribuindo o valor de aux
*/
void SwapElements (int *vetor, int i, int j) {
  int tmp = vetor[i]; // (1)
  vetor[i] = vetor[j]; // (2)
  vetor[j] = tmp; // (3)
}

void BubbleSort (int *vetor, int tamanho) {

  // For aninhado p/ percorrer o vetor e fazer as iterações
  for(int i=0; i<tamanho; i++) {
    for(int j=0; j<tamanho-1-i; j++) {
      // se o elem da pos atual é maior do que o da próxima pos, "troca-se os elementos de posição"
      if(vetor[j] > vetor[j+1]) {
      SwapElements (vetor, j, j+1);
      }
    }
  }
}

void BubbleSortRec (int *vetor, int tamanho) {

  // A função é chamada recursivamente para prosseguir com as iterações   
  int j;
  if(tamanho > 0) {
    for(j=0; j<tamanho-1; j++) {
      // se o elem da pos atual é maior do que o da próxima pos, "troca-se os elementos de posição"
      if(vetor[j] > vetor[j+1]) {
        SwapElements(vetor,j,j+1);
      }
      BubbleSortRec (vetor, tamanho-1); 
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

    SwapElements(vetor, i, ind_min);
  }
}

void SelectionSortRec (int *vetor, int tamanho) {

  int j;
  if (tamanho > 0) {
    int max = tamanho;
    for(j = tamanho - 1; j>=0 ; j--) {
      // Identificação do elemento máximo
      if(vetor[j] > vetor[max])
        max = j; // atualiza a posição em que o elem max está
      }
    SwapElements(vetor, tamanho, max);
    SelectionSortRec(vetor, tamanho-1);
  }
}

void InsertionSort (int *vetor, int tamanho) {

  // Deve-se criar um tam temp (gradativo) de deck p/ facilitar a ordenação
  // Os elementos à esquerda da chave devem trocar de pos com ela, caso forem maiores
  for (int i = 1; i < tamanho; i++) {
    for (int j = i; j > 0 && vetor[j-1] > vetor[j]; j--) {
      int key = vetor[j]; //armazena a chave (elem "fixo" q será comparado)
      vetor[j] = vetor[j-1]; 
      vetor[j-1] = key;
    }
  }
}

void InsertionSortRec (int *vetor, int tamanho) {
  if (tamanho > 0) {
    InsertionSortRec (vetor, tamanho-1);
    int key = vetor[tamanho];
    int j = tamanho - 1;
    while ( (j>=0) && (key < vetor[j]) ) {
      vetor[j+1] = vetor[j];
      j--;
    }
    vetor[j+1] = key;
  }
}

void PrintElements (int *A, int tamanho) {
  int i;
  for (i = 0; i < tamanho; i++) {
    printf("%d, ", A[i]);
  }
  printf("\n");
}

/*Função que retorna 1 se a ordenação estiver correta e 0 caso contrário.*/
int Sorting_Verification (int *A, int tamanho) {
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

printf("Este programa possui como finalidade calcular o tempo de resposta da ordenacao dos algoritmos Bubble Sort, Selection Sort e Insertion Sort...\n");
printf("O calculo sera feito com 10, 100, 1.000, 10.000, 100.000 e 250.000 elementos!\n\n");

/*
printf("\n\t\t Pressione [ENTER] para iniciar... \n");
while(getch() != 13); // captura o char ENTER do teclado (cod 13 na tabela ASCII)

system("cls||clear"); //limpa a tela (windows ou linux)

*/

printf("Benchmark com funcoes ITERATIVAS: \n\n");

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
    //PrintElements(v1, tamanho);
    BubbleSort (v1, tamanho);
    //PrintElements(v1, tamanho);
    end = clock();
    elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
    if(k>=1000) {
      printf("|%d.000 elementos|\n", k/1000);
      printf("Tempo de execucao (BubbleSort): %.2fs\n", elapsed_time);
    }
    else {
      printf("|%d elementos|\n", k);
      printf("Tempo de execucao (BubbleSort): %.2fs\n", elapsed_time);
    }
    if (!Sorting_Verification(v1, tamanho)) {
      printf("Erro: a ordenacao do BubbleSort nao esta correta!\n");
    } 

    start = clock();
    //PrintElements(v2, tamanho);
    SelectionSort (v2, tamanho);
    //PrintElements(v2, tamanho);
    end = clock();
    elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
    if(k>=1000)
      printf("Tempo de execucao (SelectionSort): %.2fs\n", elapsed_time);
    else
      printf("Tempo de execucao (SelectionSort): %.2fs\n", elapsed_time);
    if (!Sorting_Verification(v2, tamanho)) {
      printf("Erro: a ordenacao do SelectionSort nao esta correta!\n");
    }
  
    start = clock();
    //PrintElements(v3, tamanho);
    InsertionSort (v3, tamanho);
    //PrintElements(v3, tamanho);
    end = clock();
    elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
    if(k>=1000)
      printf("Tempo de execucao (InsertionSort): %.2fs\n", elapsed_time);
    else
      printf("Tempo de execucao (InsertionSort): %.2fs\n", elapsed_time);
    if (!Sorting_Verification(v3, tamanho)) {
      printf("Erro: a ordenacao do InsertionSort nao esta correta!\n");
    }

    free(v1);
    free(v2);
    free(v3);

    printf("\n");

  }

// CÁLCULO DO TEMPO DE RESPOSTA P/ 250.000 ELEMENTOS
  tamanho = 250000;

  printf("Aguarde o benchmark para 250.000 elementos...\n\n");

  int *v1 = (int *)malloc(tamanho * sizeof(int));
  int *v2 = (int *)malloc(tamanho * sizeof(int));
  int *v3 = (int *)malloc(tamanho * sizeof(int));

  for (i = 0; i < tamanho; i++) {
    v1[i] = rand() % (tamanho+1);
    v2[i] = rand() % (tamanho+1);
    v3[i] = rand() % (tamanho+1);
  }  

  start = clock();
  //PrintElements(v1, tamanho);
  BubbleSort (v1, tamanho);
  //PrintElements(v1, tamanho);
  end = clock();
  elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
  printf("|250.000 elementos|\n");
  printf("Tempo de execucao (BubbleSort): %.2fs\n", elapsed_time);
  if (!Sorting_Verification(v1, tamanho)) {
    printf("Erro: a ordenacao do BubbleSort nao esta correta!\n");
  } 

  start = clock();
  //PrintElements(v2, tamanho);
  SelectionSort (v2, tamanho);
  //PrintElements(v2, tamanho);
  end = clock();
  elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
  printf("Tempo de execucao (SelectionSort): %.2fs\n", elapsed_time);
  if (!Sorting_Verification(v2, tamanho)) {
    printf("Erro: a ordenacao do SelectionSort nao esta correta!\n");
  }

  start = clock();
  //PrintElements(v3, tamanho);
  InsertionSort (v3, tamanho);
  //PrintElements(v3, tamanho);
  end = clock();
  elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
  printf("Tempo de execucao (InsertionSort): %.2fs\n", elapsed_time);
  if (!Sorting_Verification(v3, tamanho)) {
    printf("Erro: a ordenacao do InsertionSort nao esta correta!\n");
  }

  printf("\n");

  free (v1);
  free (v2);  
  free (v3);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

printf("Atencao!!!\nA analise do tempo de execucao, com recursividade, pode deixar de rodar em muitos computadores (principalmente para 250k elementos)!\n\n");
printf("Benchmark com funcoes RECURSIVAS: \n\n");

// CÁLCULO DO TEMPO DE RESPOSTA P/ 10, 100, 1.000, 10.000 E 100.000 ELEMENTOS
  for (int k=10; k<=100000; k = k * 10) {
    tamanho = 10;

    int *v4 = (int *)malloc(tamanho * sizeof(int));
    int *v5 = (int *)malloc(tamanho * sizeof(int));
    int *v6 = (int *)malloc(tamanho * sizeof(int));

    for (i = 0; i < tamanho; i++) {
      v4[i] = rand() % (tamanho+1);
      v5[i] = rand() % (tamanho+1);
      v6[i] = rand() % (tamanho+1);
    }  

    start = clock();
    //PrintElements(v1, tamanho);
    BubbleSortRec (v4, tamanho);
    //PrintElements(v1, tamanho);
    end = clock();
    elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
    if(k>=1000) {
      printf("|%d.000 elementos|\n", k/1000);
      printf("Tempo de execucao (BubbleSort): %.2fs\n", elapsed_time);
    }
    else {
      printf("|%d elementos|\n", k);
      printf("Tempo de execucao (BubbleSort): %.2fs\n", elapsed_time);
    }
    if (!Sorting_Verification(v4, tamanho)) {
      printf("Erro: a ordenacao do BubbleSort nao esta correta!\n");
    } 

    start = clock();
    //PrintElements(v5, tamanho);
    SelectionSortRec (v5, tamanho);
    //PrintElements(v5, tamanho);
    end = clock();
    elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
    if(k>=1000)
      printf("Tempo de execucao (SelectionSort): %.2fs\n", elapsed_time);
    else
      printf("Tempo de execucao (SelectionSort): %.2fs\n", elapsed_time);
    if (!Sorting_Verification(v5, tamanho)) {
      printf("Erro: a ordenacao do SelectionSort nao esta correta!\n");
    }
  
    start = clock();
    //PrintElements(v6, tamanho);
    InsertionSortRec (v6, tamanho);
    //PrintElements(v6, tamanho);
    end = clock();
    elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
    if(k>=1000)
      printf("Tempo de execucao (InsertionSort): %.2fs\n", elapsed_time);
    else
      printf("Tempo de execucao (InsertionSort): %.2fs\n", elapsed_time);
    if (!Sorting_Verification(v6, tamanho)) {
      printf("Erro: a ordenacao do InsertionSort nao esta correta!\n");
    }

    free(v4);
    free(v5);
    free(v6);

    printf("\n");

  }

// CÁLCULO DO TEMPO DE RESPOSTA P/ 250.000 ELEMENTOS
  tamanho = 250000;

  printf("Aguarde o benchmark para 250.000 elementos...\n\n");

  int *v4 = (int *)malloc(tamanho * sizeof(int));
  int *v5 = (int *)malloc(tamanho * sizeof(int));
  int *v6 = (int *)malloc(tamanho * sizeof(int));

  for (i = 0; i < tamanho; i++) {
    v4[i] = rand() % (tamanho+1);
    v5[i] = rand() % (tamanho+1);
    v6[i] = rand() % (tamanho+1);
  }  

  start = clock();
  //PrintElements(v4, tamanho);
  BubbleSortRec (v4, tamanho);
  //PrintElements(v4, tamanho);
  end = clock();
  elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
  printf("|250.000 elementos|\n");
  printf("Tempo de execucao (BubbleSort): %.2fs\n", elapsed_time);
  if (!Sorting_Verification(v4, tamanho)) {
    printf("Erro: a ordenacao do BubbleSort nao esta correta!\n");
  } 

  start = clock();
  //PrintElements(v5, tamanho);
  SelectionSortRec (v5, tamanho);
  //PrintElements(v5, tamanho);
  end = clock();
  elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
  printf("Tempo de execucao (SelectionSort): %.2fs\n", elapsed_time);
  if (!Sorting_Verification(v5, tamanho)) {
    printf("Erro: a ordenacao do SelectionSort nao esta correta!\n");
  }

  start = clock();
  //PrintElements(v6, tamanho);
  InsertionSortRec (v6, tamanho);
  //PrintElements(v6, tamanho);
  end = clock();
  elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
  printf("Tempo de execucao (InsertionSort): %.2fs\n", elapsed_time);
  if (!Sorting_Verification(v6, tamanho)) {
    printf("Erro: a ordenacao do InsertionSort nao esta correta!\n");
  }

  printf("\n");

  free (v4);
  free (v5);  
  free (v6);

  return 0;
}
