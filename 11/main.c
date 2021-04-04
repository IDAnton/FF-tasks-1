#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LEN 100

void insert_symb(char* str, int n, int m, char symb){
    char tmp1, tmp2;
    for (int i = 0; i <= n; i++){
        if (i == m){
            tmp1 = str[i];
            str[i] = symb;
            tmp2 = str[i + 1];
            str[i + 1] = tmp1;
        }
        if (i > (m+1)){
            tmp1 = str[i];
            str[i] = tmp2;
            tmp2 = str[i + 1];
            str[i + 1] = tmp1;
            i++;
        }
    }
    str[n + 1] = '\0';
}


void delete_symb(char* str, int n, int m){
    for (int i = 0; i < (n-1); i++){
        if (i >= m)
            str[i] = str[i + 1];
    }
    str[n-1] = '\0';
}


void replace_symb(char* str, int m, char symb){
    str[m] = symb;
}


void correct_string(char* str, int n){
    if ((int)str[0] >= 97 && (int)str[0] <= 122)
        str[0] -= 32;

    for (int i = 0; i < n; i++){
        if (((str[i] == '.') || (str[i] == ',')) && (str[i] != ' ')){
            insert_symb(str, n, i + 1, ' ');
            i++;
        }
        if ((str[i] == str[i + 1]) && (str[i] == ' ')){
            delete_symb(str, n, i);
            i--;
        }
        if ((str[i] == ' ')&&((str[i+1] == '.') || (str[i+1] == ','))){
            delete_symb(str, n, i);
            i--;
        }
        if ((str[i] == '.')&&(int)str[i+2] >= 97 && (int)str[i+2] <= 122)
            str[i+2] -= 32;
    }
}


int main(){
    while (1){
        int n;
        char str[MAX_LEN];
        printf("Enter string\n");
        gets(str);
        correct_string(str, MAX_LEN);
        printf("RESULT: %s\n", str);
        printf("1)Continue\n2)Exit");
        scanf_s("%d", &n);
        getchar();
        if (n == 2){
            return 0;
        }
        system("cls");
    }
}
