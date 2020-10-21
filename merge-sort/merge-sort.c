// Algoritmos e Estrutura de dados II
// Tarefa 02 - Eleicoes Otimizadas
// André Henrique Mendes de Carvalho
// RA: 133576

#include <stdio.h> 
#include <stdlib.h>

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1; // tamanho da array esquerda
    int n2 = r - m; // tamanho da array direita

    // cria uma array temporaria
    int L[n1], R[n2];

    // divide os dados da arr (principal) entre as duas temporarias L[n1] e R[n2]
    for(i=0; i<n1; i++) {
        L[i] = arr[l+i];
    }
    for(j=0; j<n2; j++) {
        R[j] = arr[m+1+j];
    }

    i = 0; // indice inicial da array da esquerda
    j = 0; // indice inicial da arrau da direita
    k = l; // indice inicial da array ordenada 
    while(i<n1 && j<n2) {
        if(L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // se sobrar algum elemento final no L[] -> aloca no final da lista
    while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    // se sobrar algum elemento final no R[] -> aloca no final da lista
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
}

void mergeSort(int arr[], int l, int r) {
    if(l<r) {
        int m = (l+r) / 2;

        // ordena a primeira e segunda metades
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}


void printArray(int e, int c, int V[e][c]) {
    int i, j;
    for(i=0; i<e; i++) {
        for(j=0; j<c; j++) {
            printf("%d ", V[i][j]);
        }
        printf("\n");
    }
}

int main() {
    
    int e, c;
    scanf("%d %d", &e, &c);
    // DEV ---
    //e = 10;
    //c = 5;

    int V[e][c];

    int i, j;
    for(i=0; i<e; i++) {
        for(j=0; j<3; j++) {
            scanf("%d", &V[i][j]);
            // DEV ---
            //V[i][j] = (rand() % 5) + 1;
        }
    }
    

    for(i=0; i<e; i++) {
        for(j=0; j<c; j++) {
            if((V[i][j]>c) || (V[i][j]<1)) {
                V[i][j] = 0;
            }
        }
    }
    for(i=0; i<e; i++) {
        if(V[i][0] != 0) {
            break;
        }
        if(i == e-1) {
            printf("0");
            return 0;
        }
    }

    // printa os 3 votos de cada eleitor
    //printf("\nMatriz principal:\n");
    //printArray(e, c, V);

    // Busca o voto principal de cada eleitor
    int primeiroTurno[e];
    for(i=0; i<e; i++) {
        primeiroTurno[i] = V[i][0];
    }

    // printa o voto principal de cada eleitor [ordenado]
    mergeSort(primeiroTurno, 0, e-1);
    //printf("\nPrimeiro turno ordenado\n");
    for(i=0; i<e; i++){
        //printf("%d ", primeiroTurno[i]);
    }
        

    // cria e zera o vetor com a quantidade de votos por candidatos
    int votos[c];
    for(i=0; i<c; i++) {
        votos[i] = 0;
    }

    // faz a contagem de votos de cada candidato
    j = 0;
    i = 0;

    while(j<c && i<e) {
        while(primeiroTurno[i] == 0) {
            i++;
        }
        if(primeiroTurno[i] == j+1) {
            votos[j] = votos[j] + 1;
            // printf("candidato %d +1\n", j+1);
            i++;
        } else {
            j++;
        }
    }
        
    // contabiliza as porcentagens
    // porcentagens[percentual][numero do candidato]
    float porcentagens[c][2];
    int soma = 0;
    for(i=0; i<c; i++) {
        soma = soma + votos[i];
    }
    for(i=0; i<c; i++) {
        porcentagens[i][0] = (float)(votos[i] * 100) / soma;
        porcentagens[i][1] = i+1;
    }

    // printa os votos e a porcentagem que cada candidato recebeu  
    for(i=0; i<c; i++){
        //printf("\ncandidato %.0f: %d votos - %.2f", porcentagens[i][1], votos[i], porcentagens[i][0]);
    }
        

    // cria e ordena uma lista dos mais votados [crescente]
    float porcentagemOrdenada[c];
    for(j=0; j<c; j++) {
        porcentagemOrdenada[j] = porcentagens[j][0];
    }

    mergeSort(porcentagemOrdenada, 0, c-1);

    for(i=0; i<c; i++) {
        //printf("\nporcentagem ordenada: %.2f", porcentagemOrdenada[i]);
    }
    
    float segundoTurno[2][3];
    // coluna 0 -> porcentagem de votos
    // coluna 1 -> numero do candidato
    // coluna 2 -> numero de votos
    // coluna 3 -> porcentagem final
    segundoTurno[0][0] = porcentagemOrdenada[c-1];
    segundoTurno[1][0] = porcentagemOrdenada[c-2];
    segundoTurno[0][2] = 0;
    segundoTurno[1][2] = 0;

    int ok = 0;
    int tk = 0;
    for(i=0; i<c; i++) {
        if((segundoTurno[0][0] == porcentagens[i][0]) && ok==0) {
            segundoTurno[0][1] = porcentagens[i][1];
            ok = 1;
        }
        else if((segundoTurno[1][0] == porcentagens[i][0]) && tk==0) {
            segundoTurno[1][1] = porcentagens[i][1];
            tk = 1;
        }
    }
    //printf("\nMais votados: %.0f %.2f", segundoTurno[0][1], segundoTurno[0][0]);
    //printf("\nMais votados: %.0f %.2f", segundoTurno[1][1], segundoTurno[1][0]);
    /*
    for(i=0; i<2; i++) {
        printf("\ncandidato %.0f: %.2f", segundoTurno[i][1], segundoTurno[i][0]);
    }
    */


    // verifica se alguem ganhou no primeiro turno
    printf("%.0f %.2f", segundoTurno[0][1], segundoTurno[0][0]);
    if(segundoTurno[0][0] >= 50) {
        return 0;
    }

   // Inicia segundo turno
    int k;
    for(i=0; i<e; i++) {
        for(k=0; k<c; k++) {
            if(V[i][k] == segundoTurno[0][1]) {
                segundoTurno[0][2]++;
                for(j=0; j<c; j++) {
                    V[i][j] = -1;
                }
            }
            else if(V[i][k] == segundoTurno[1][1]) {
                segundoTurno[1][2]++;
                for(j=0; j<c; j++) {
                    V[i][j] = -1;
                }
            }
        }
    }


    float somaVotos = segundoTurno[0][2] + segundoTurno[1][2];
    segundoTurno[0][3] = (segundoTurno[0][2] * 100) / somaVotos;
    segundoTurno[1][3] = (segundoTurno[1][2] * 100) / somaVotos;

    //printf("\n\n\ncandidato %.0f: %.0f votos -- %.2f", segundoTurno[0][1], segundoTurno[0][2], segundoTurno[0][3]);
    //printf("\ncandidato %.0f: %.0f votos -- %.2f", segundoTurno[1][1], segundoTurno[1][2], segundoTurno[1][3]);
    printf("\n");
    if(segundoTurno[0][2] > segundoTurno[1][2]) {
        printf("%.0f %.2f", segundoTurno[0][1], segundoTurno[0][3]);
        return 0;
    }
    if(segundoTurno[0][2] < segundoTurno[1][2]) {
        printf("%.0f %.2f", segundoTurno[1][1], segundoTurno[1][3]);
        return 0;
    }
    if(segundoTurno[0][1] < segundoTurno[1][1]) {
        printf("%.0f %.2f", segundoTurno[0][1], segundoTurno[0][3]);
        return 0;
    } else
    {
        printf("%.0f %.2f", segundoTurno[1][1], segundoTurno[1][3]);
        return 0;
    }
    
}