#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int minimum(int* arr, int n){
    int min = *arr;
    for(int i=1;i<n;i++)
        if(*(arr + i) < min)
            min = *(arr + i);
    return min;
}

int maximum(int* arr, int n){
    int max = *arr;
    for(int i=1;i<n;i++)
        if(*(arr + i) > max)
            max = *(arr + i);
    return max;
}

float avg(int* arr, int n){
    float avg = 0;
    for(int i=0;i<n;i++)
        avg += *(arr + i);
    return avg/n;
}

float rms(int* arr, int n){
    float avg = 0;
    float rms = 0;
    for(int i=0;i<n;i++) {
        avg += *(arr + i);
        rms += pow(*(arr + i), 2);
    }
    avg /= n;
    rms = pow(rms / n - pow (avg, 2), 0.5);
    return rms;
}

int main() {
    while (1){
        system("cls");
        int n;
        printf("Enter array size\n");
        scanf_s("%d", &n);
        printf("Enter elements of array\n");
        int *arr = (int *) malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
            scanf_s("%d", (arr + i));
        printf("Min %d\n", minimum(arr, n));
        printf("Max %d\n", maximum(arr, n));
        printf("Average %.3f\n", avg(arr, n));
        printf("Rms %.3f\n\n", rms(arr, n));
        free(arr);

        printf("1)Continue calculations\n2)Exit\n");
        scanf_s("%d", &n);
        if(n == 2)
            return 0;
    }
}
