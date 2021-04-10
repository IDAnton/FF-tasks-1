#include <stdio.h>
#include <stdlib.h>

#define CLUSTER_SIZE 3
#define TERMINATOR '#'

void print(char* str, char terminator){
    int i = 0;
    while(str[i] != terminator) {
        putchar(str[i]);
        i++;
    }
}

char* trim_buffer(char* str, int size){
    char* new_str = (char*)malloc(sizeof(char)*size);
    for(int i = 0; i < size; i++)
        new_str[i] = str[i];
    free(str);
    return new_str;
}

char* reallocate_memory(char* str, int* size){
    (*size)++;
    char* new_str = (char*)malloc(sizeof(char)*CLUSTER_SIZE*(*size));
    for(int i = 0; i < CLUSTER_SIZE*(*size); i++)
        new_str[i] = str[i];
    free(str);
    printf("ee %d\n", *size);
    return new_str;
}

char* GetText(FILE* stream, char terminator){
    char* str = (char*)malloc(sizeof(char)*CLUSTER_SIZE);
    char input = '0', tmp;
    int size = 1, i = 0;

    while((input != terminator) && (input != EOF)){
        if(stream == NULL)
            input = getchar();
        else
            input = fgetc(stream);
        tmp = getchar();
        str[i] = input;
        i++;
        printf("i = %d; size = %d; info = %d\n", i, size, i%CLUSTER_SIZE);
        if(i%CLUSTER_SIZE == 0)
            str = reallocate_memory(str, &size);
    }
//    putchar(str[i-1]);
//    scanf_s("%d",&tmp);
//    if(str[i-1] != terminator)
//        str[i] = terminator;
    str = trim_buffer(str, i);
    return str;
}

void menu(){
    int input;
    while (1){
        printf("1)Input from console\n");
        printf("2)Input from file\n");
        printf("3)Input from exit\n");
        scanf_s("%d", &input);
        if (input == 3)
            return;
    }
}

int main(){
    char* str = GetText(NULL, TERMINATOR);
    print(str, TERMINATOR);
    return 0;
}
