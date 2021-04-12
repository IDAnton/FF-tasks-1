#include <stdio.h>
#include <stdlib.h>
#include "string_processing.h"

#define CLUSTER_SIZE 5
#define TERMINATOR '#'


char* trim_buffer(char* str, int size){
    char* new_str = (char*)malloc(sizeof(char)*size);
    for(int i = 0; i < size; i++)
        new_str[i] = str[i];
    new_str[size-1] = '\0';
    free(str);
    return new_str;
}

char* reallocate_memory(char* str, int* size){
    (*size)++;
    char* new_str = (char*)malloc(sizeof(char)*CLUSTER_SIZE*(*size));
    for(int i = 0; i < CLUSTER_SIZE*(*size); i++)
        new_str[i] = str[i];
    free(str);
    return new_str;
}

char* GetText(FILE* stream, char terminator){
    char* str = (char*)malloc(sizeof(char)*CLUSTER_SIZE);
    char input = '0';
    int size = 1, i = 0;
    while((input != terminator) && (input != EOF)){
        if(stream == NULL)
            input = getchar();
        else
            input = fgetc(stream);
        str[i] = input;
        i++;
        //printf("i = %d; size = %d; info = %d\n", i, size, i%CLUSTER_SIZE);
        if(i%CLUSTER_SIZE == 0)
            str = reallocate_memory(str, &size);
    }
    str = trim_buffer(str, i);
    return str;
}

void menu(){
    int input;
    char* str;
    while (1){
        printf("Text processing program. Select input source:\n\n");
        printf("1)Input from console\n");
        printf("2)Input from file\n");
        printf("3)Exit\n");
        scanf_s("%d", &input);
        getchar();
        system("cls");
        switch (input){
            case 1: {
                printf("Enter string\n\n");
                str = GetText(NULL, TERMINATOR);
                break;
            }
            case 2: {
                char file_name[30];
                printf("Enter file name\n");
                scanf("%s", file_name);
                FILE* file = fopen(file_name, "r");
                str = GetText(file, TERMINATOR);
                fclose(file);
                break;
            }
            case 3:
                return;
        }
        system("cls");
        printf("RAW TEXT:\n%s\n\n", str);
        correct_string(str, get_str_len(str)-1);
        printf("PROCESSED TEXT:\n%s\n\nPress any key to continue ", str);
        scanf_s("%d", &input);
        system("cls");
        free(str);
    }
}

int main(){
    menu();
    return 0;
}
