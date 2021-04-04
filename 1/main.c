#include <stdio.h>
#include <math.h>

int main() {
    int a, b, c;
    double x1, x2, d;
    printf("Ax^2 + Bx + C = 0\nEnter A,B,C\n");
    printf("A = ");
    scanf_s("%d", &a);
    printf("B = ");
    scanf_s("%d", &b);
    printf("C = ");
    scanf_s("%d", &c);

    if (a == 0){
        if (b == 0){
            if (c == 0)
                printf("x = any value");
            else
                printf("No solutions");
        }
        else{
            x1 = - (double) c/b;
            printf("x = %f", x1);
        }
    }
    else{
        d = b*b - 4*a*c;
        if (d < 0)
            printf("No solutions");
        if (d == 0) {
            x1 = (double) b / (2 * a);
            printf("x = %f", x1);
        }
        if (d > 0){
            x1 = (-b + sqrt(d)) / (2 * a);
            x2 = (-b - sqrt(d)) / (2 * a);
            printf("x1 = %f\nx2 = %f", x1,x2);
        }
    }
    getch();
    return 0;
}