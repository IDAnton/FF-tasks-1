#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#define MAX_RAND 10

struct matrix{
    int is_init;
    int n, m;
    float** mat;
};
typedef struct matrix matrix;

matrix init(int n, int m){
    matrix res;
    res.n = n;
    res.m = m;
    res.mat = (float**)(malloc(sizeof (float*)*n));
    for(int i = 0; i < n; i++)
        res.mat[i] = (float*)(malloc(sizeof (float)*m));
    return res;
}

void free_matrix(matrix mat){
    for(int i = 0; i < mat.n; i++)
        free(mat.mat[i]);
}

matrix print(matrix a){
    for (int i = 0; i < a.n; i++){
        for (int j = 0; j < a.m; j++){
            if((int)a.mat[i][j] == a.mat[i][j])
                printf("%2d ", (int)a.mat[i][j]);
            else
                printf("%2f ", a.mat[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

matrix init_from_matrix(matrix a, int n, int m){
    matrix res = init(a.n - 1, a.m - 1);
    for(int i = 0; i < a.n; i++){
        for(int j = 0; j < a.m; j++){
            if ((i!=n) && (j!=m)) {
                if ((i<n) && (j<m))
                    res.mat[i][j] = a.mat[i][j];
                if ((i>n) && (j<m))
                    res.mat[i-1][j] = a.mat[i][j];
                if ((i<n) && (j>m))
                    res.mat[i][j - 1] = a.mat[i][j];
                if ((i>n) && (j>m))
                    res.mat[i-1][j-1] = a.mat[i][j];
            }
        }
    }
    return res;
}

matrix sum(matrix a, matrix b){
    matrix res = init(a.n, a.m);
    for (int i = 0; i < a.n; i++){
        for (int j = 0; j < a.m; j++){
            res.mat[i][j] = a.mat[i][j] + b.mat[i][j];
        }
    }
    return res;
}

matrix mult_on_number(matrix a, float b){
    matrix res = init(a.n, a.m);
    res.mat = a.mat;
    for (int i = 0; i < a.n; i++){
        for (int j = 0; j < a.m; j++){
            res.mat[i][j] *= b;
        }
    }
    return res;
}

matrix mult(matrix a, matrix b){
    matrix res = init(a.n, b.m);
    for (int i = 0; i < a.n; i++){
        for (int j = 0; j < b.m; j++){
            res.mat[i][j] = 0;
            for (int k = 0; k < a.m; k++){
                res.mat[i][j] += a.mat[i][k] * b.mat[k][j];
            }
        }
    }
    return res;
}

float det(matrix a){
    float res = 0;

    if(a.n == 1)
        return a.mat[0][0];

    if(a.n == 2)
        return a.mat[0][0]*a.mat[1][1] - a.mat[1][0]*a.mat[0][1];

    for (int i = 0; i < a.n; i++){
        matrix tmp_mat = init_from_matrix(a, 0, i);
        res += pow(-1, i) * a.mat[0][i] * det(tmp_mat);
    }
    return res;
}

matrix transpose(matrix mat){
    matrix res = init(mat.n, mat.m);
    for(int i = 0; i < mat.n; i++){
        for(int j = 0; j < mat.m; j++){
            res.mat[i][j] = mat.mat[j][i];
        }
    }
    return res;
}

matrix rev(matrix mat){
    matrix res = init(mat.n, mat.m);
    mat = transpose(mat);
    for (int i = 0; i < mat.n; i++){
        for (int j = 0; j < mat.m; j++){
            matrix tmp_mat = init_from_matrix(mat, i, j);
            res.mat[i][j] = pow(-1, i + j) * det(tmp_mat);
        }
    }
    float mdet = 1 / det(mat);
    return mult_on_number(res, mdet);
}

matrix input(){
    int n, m;
    printf("Enter matrix size N x M\n");
    scanf_s("%d %d", &m, &n);
    matrix res = init(n, m);
    printf("Enter matrix elements\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            scanf_s("%f", &res.mat[i][j]);
        }
    }
    res.is_init = 1;
    return res;
}

matrix init_rand(){
    int n, m;
    printf("Enter matrix size N x M (columns, rows)\n");
    scanf_s("%d %d", &n, &m);
    matrix res = init(n, m);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            res.mat[i][j] = (int)(rand() / (float)RAND_MAX * MAX_RAND * 2) - MAX_RAND;
        }
    }
    res.is_init = 1;
    return res;
}

matrix init_from_file(FILE * file){
    int n, m;
    fscanf(file, "%d %d", &n, &m);
    matrix res = init(n, m);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            fscanf(file, "%f", &res.mat[i][j]);
        }
    }
    fclose(file);
    res.is_init = 1;
    return res;
}

void write_to_file(FILE * file, matrix mat){
    fprintf(file, "%d %d\n", mat.n, mat.m);
    for (int i = 0; i < mat.n; i++){
        for (int j = 0; j < mat.m; j++){
            fprintf(file, "%f ", mat.mat[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
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
                printf("Enter matrix\n");
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
        printf("3)Multiply by number\n");
        printf("4)Multiply matrices\n");
        printf("5)Calculate reverse matrix\n");
        printf("6)Reinit matrices\n");
        printf("7)Save matrices to file\n");
        printf("8)Exit\n\n");
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
                c.is_init = 0;
                if ((a.n == a.m) && (b.n == b.m)) {
                    printf("Det (Matrix N1) = %f\n", det(a));
                    printf("Det (Matrix N2) = %f\n", det(b));
                }
                else
                    printf("Error: Matrices must be square for determinant calculation\n");
                break;
            }
            case 2: {
                c.is_init = 0;
                if ((a.n == b.n) && (a.m == b.m)) {
                    printf("Matrix N1 + Matrix N2\n");
                    c = sum(a, b);
                    print(c);
                }
                else
                    printf("Error: Matrices must have same dimension\n");
                break;
            }
            case 3: {
                printf("Enter number\n");
                float mult_number;
                scanf_s("%f", &mult_number);
                printf("\nMatrix N1 * %f\n\n", mult_number);
                c = mult_on_number(a, mult_number);
                print(c);
                break;
            }
            case 4: {
                if(a.n == b.m) {
                    printf("Matrix N1 x Matrix N2\n");
                    c = mult(a, b);
                    print(c);
                }
                else
                    printf("Error: Matrices must have same amount of rows and columns\n");
                break;
            }
            case 5: {
                if(a.n == a.m){
                    printf("Reverse Matrix N1\n");
                    c = rev(a);
                    print(c);
                }
                else
                    printf("Error: Matrix must be square\n");
                break;
            }
            case 6: {
                free_matrix(a);
                free_matrix(b);
                free_matrix(c);
                a.is_init = b.is_init = c.is_init = 0;
                continue;
            }
            case 7: {
                c.is_init = 0;
                printf("Select matrix for saving\n");
                scanf_s("%d", &user_input);
                system("cls");
                char file_name[30];
                FILE *file;
                printf("Enter file name\n");
                scanf("%s", file_name);
                file = fopen(file_name, "w");
                if (user_input == 1)
                    write_to_file(file, a);
                if (user_input == 2)
                    write_to_file(file, b);
                printf("Saved\n");
                break;
            }
            case 8: return;
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