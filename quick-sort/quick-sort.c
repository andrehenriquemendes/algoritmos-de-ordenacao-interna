#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[16];
    int age;
    int index;
} Person;

void swap(Person *a, Person *b) {
    Person temp = *a;
    *a = *b;
    *b = temp;
}

int mediana(Person arr[], int p, int r) {
    int mid = (p+r) / 2;
    int a = arr[p].age;
    int b = arr[mid].age;
    int c = arr[r].age;

    int medianaIndice = 0;

    if(a<b) {
        if(b<c)
            medianaIndice = mid;
        else if(a<c)
            medianaIndice = r;
        else
            medianaIndice = p;
    } else if(c<b)
        medianaIndice = mid;
    else if(c<a)
        medianaIndice = r;
    else
        medianaIndice = p;

    swap(&arr[medianaIndice], &arr[r]);

    return arr[r].age;
}   

int partition(Person arr[], int p, int r) {
    int pivo = mediana(arr, p, r);
    int i = p-1;
    
    int j;
    for(j=p; j<=r-1; j++) {
        if(arr[j].age <= pivo)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[r]);
    return (i+1);

}

void quickSort(Person arr[], int p, int r) {
    if(p<r) {
        int q = partition(arr, p, r);

        quickSort(arr, p, q-1);
        quickSort(arr, q+1, r);
    }
}

void printArray(int arr[], int size) {
    int i;
    for(i=0; i<size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int cases;
    scanf("%d", &cases);

    Person listPersons[cases];
    int i, j;
    for(i=0; i<cases; i++) {
        scanf("%s %d", &listPersons[i].name, &listPersons[i].age);
        listPersons[i].index = i;
    }
    int p, m;
    scanf("%d %d", &p, &m);

    quickSort(listPersons, 0, cases-1);
    int op = 0;
    for(i=0; i<cases; i++) {
        for(j=i+1; j<cases; j++) {
            if(listPersons[i].age == listPersons[j].age) {
                if(listPersons[i].index > listPersons[j].index) {
                    op = 1;
                }
            }
        }
    }
    if(op == 0)
        printf("yes\n");
    else if(op == 1)
        printf("no\n");

    for(i=p-1; i<p+m-1; i++) {
        printf("%s %d\n", listPersons[i].name, listPersons[i].age);
    }
    
    

    return 0;
}