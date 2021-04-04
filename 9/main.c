#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#define MAX_RAND 10

struct matrix{
    int is_init;
    float m[3][3];
};
typedef struct matrix matrix;

matrix sum(matrix a, matrix b){
    matrix res;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            res.m[i][j] = a.m[i][j] + b.m[i][j];
        }
    }
    return res;
}

matrix diff(matrix a, matrix b){
    matrix res;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            res.m[i][j] = a.m[i][j] - b.m[i][j];
        }
    }
    return res;
}

matrix mult_on_number(matrix a, float b){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            a.m[i][j] *= b;
        }
    }
    return a;
}

matrix mult(matrix a, matrix b){
    matrix res;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            res.m[i][j] = 0;
            for (int k = 0; k < 3; k++){
                res.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return res;
}

float det2(float a, float b, float c, float d){
    return (a*d) - (b*c);
}

float det(matrix a){
    float res = 0;
    for (int i = 0; i < 3; i++){
        int c = (i + 1) % 3;
        int d = (i + 2) % 3;
        if (c > d){
            int tmp = c;
            c = d;
            d = tmp;
        }
        res += pow(-1, i) * a.m[0][i] * det2(a.m[1][c], a.m[1][d], a.m[2][c], a.m[2][d]);
    }
    return res;
}

matrix transpose(matrix mat){
    matrix tmp = mat;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            mat.m[i][j] = tmp.m[j][i];
        }
    }
    return mat;
}

matrix rev(matrix mat){
    matrix res;
    mat = transpose(mat);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            int a = (i + 1) % 3;
            int b = (i + 2) % 3;
            int c = (j + 1) % 3;
            int d = (j + 2) % 3;
            if (a > b){
                int tmp = a;
                a = b;
                b = tmp;
            }
            if (c > d){
                int tmp = c;
                c = d;
                d = tmp;
            }
            res.m[i][j] = pow(-1, i+j) * det2(mat.m[a][c], mat.m[a][d], mat.m[b][c], mat.m[b][d]);
        }
    }
    float mdet = 1 / det(mat);
    return mult_on_number(res, mdet);
}

matrix input(){
    matrix res;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            scanf_s("%f", &res.m[i][j]);
        }
    }
    res.is_init = 1;
    return res;
}

matrix init_rand(){
    matrix res;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            res.m[i][j] = (int)(rand()/(float)RAND_MAX * MAX_RAND *2 ) - MAX_RAND;
        }
    }
    res.is_init = 1;
    return res;
}

matrix init_from_file(FILE * file){
    matrix res;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            fscanf(file, "%f", &res.m[i][j]);
        }
    }
    fclose(file);
    res.is_init = 1;
    return res;
}

void write_to_file(FILE * file, matrix mat){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            fprintf(file, "%f ", mat.m[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

matrix print(matrix a){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf("%f ", a.m[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}


matrix init_menu(int number) {
    matrix res;
    res.is_init = 0;
    int user_input;
    while (res.is_init == 0) {
        system("cls");
        printf("INITIALIZATION OF MATRIX N%d\n\n", number);
        printf("1)Init matrix from keyboard\n");
        printf("2)Init matrix from file\n");
        printf("3)Init matrix with random numbers\n");
        scanf_s("%d", &user_input);
        system("cls");

        switch (user_input) {
            case 1: {
                printf("Enter matrix 3x3\n");
                res = input();
                break;
            }
            case 2: {
                char file_name[30];
                FILE *file;
                printf("Enter input file name\n");
                scanf("%s", file_name);
                file = fopen(file_name, "r");
                res = init_from_file(file);
                break;
            }
            case 3: {
                res = init_rand();
                break;
            }
        }
    }
    return res;
}

void main_menu(){
    matrix a, b, c;
    a.is_init = b.is_init = 0;
    int user_input;
    while (1) {
        if (a.is_init == 0)
            a = init_menu(1);
        if (b.is_init == 0)
            b = init_menu(2);

        system("cls");
        printf("1)Calculate determinants\n");
        printf("2)Calculate sum\n");
        printf("3)Multiply on number\n");
        printf("4)Multiply matrices\n");
        printf("5)Find reverse matrix\n");
        printf("6)Reinit matrices\n");
        printf("7)Exit\n\n");
        printf("Matrix N1\n");
        print(a);
        printf("Matrix N2\n");
        print(b);
        scanf_s("%d", &user_input);
        system("cls");
        printf("Matrix N1\n");
        print(a);
        printf("Matrix N2\n");
        print(b);
        c.is_init = 1;
        switch (user_input) {
            case 1: {
                printf("Det (Matrix N1) = %f\n", det(a));
                printf("Det (Matrix N2) = %f\n", det(b));
                c.is_init = 0;
                break;
            }
            case 2: {
                printf("Matrix N1 + Matrix N2\n");
                c = sum(a, b);
                print(c);
                break;
            }
            case 3: {
                printf("Enter number\n");
                scanf_s("%d", &user_input);
                printf("Matrix N1 * %d\n\n", user_input);
                c = mult_on_number(a, (float)user_input);
                print(c);
                break;
            }
            case 4: {
                printf("Matrix N1 x Matrix N2\n");
                c = mult(a, b);
                print(c);
                break;
            }
            case 5: {
                printf("Reverse Matrix N1\n");
                c = rev(a);
                print(c);
                break;
            }
            case 6: {
                a.is_init = 0;
                b.is_init = 0;
                continue;
            }
            case 7: return;
        }
        if(c.is_init){
            printf("1)Save result to file\n");
            printf("2)Continue without saving\n");
            scanf_s("%d", &user_input);
            if(user_input == 1){
                char file_name[30];
                FILE *file;
                printf("Enter file name\n");
                scanf("%s", file_name);
                printf("%s", file_name);
                file = fopen(file_name, "w");
                write_to_file(file, c);
            }
            continue;
        }
        scanf_s("%d", &user_input);
    }
}

int main(){
    srand(time(NULL));
    main_menu();
    return 0;
}