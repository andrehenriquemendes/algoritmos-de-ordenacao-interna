#include <stdio.h>
#include <stdlib.h>

void swap(int *i, int *max) {
    int temp = *i;
    *i = *max;
    *max = temp;
}

void printArray(int v[], int size) {
    int i;
    for(i=0; i<size; i++) {
        printf("%d ", v[i]);
    }
}

void maxHeapify(int a[], int i, int size) {
    // printf("size: %d\n", size);
    int max;
    int l, r;
    // calculo da posicao dos nos filhos
    l = (2*i)+1;
    r = (2*i)+2;

    if((l<=size) && (a[l] > a[i])) {
        max = l;
    }
    else {
        max = i;
    }
        
    
    if((r<=size) && (a[r] > a[max])) {
        max = r;
    }
        
    
    if(max != i) {
        swap(&a[i], &a[max]);
        
        maxHeapify(a, max, size);
    }
}

void buildMaxHeap(int a[], int size) {
    int i;
    for(i=(size/2); i>=0; i--) {
        maxHeapify(a, i, size);
    }
}

int heapExtractMax(int a[], int size) {
    
    int max = a[0];
    a[0] = a[size];
    a[size] = NULL;

    maxHeapify(a, 0, size-1);

    return max;
}

int* heapSort(int a[], int size) {
    buildMaxHeap(a, size);
    int *v;
    v = (int *) malloc(size * sizeof(int));  // vetor de saida
    
    while(size >= 0) {
        v[size] = heapExtractMax(a, size);
        size--;
    }
    
    return v;
}

int main() {
    // fazer o scanf
    int n;
    scanf("%d", &n);

    int *a;
    a = (int *) malloc(n * sizeof(int));

    int i;
    for (i=0; i<n; i++) {
        scanf("%d", &a[i]);
    }
    //buildMaxHeap(a, n-1);
    int *v;
    v = heapSort(a, n-1);


    printArray(v, n);
    return 0;
}