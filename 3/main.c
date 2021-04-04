#include <stdio.h>
#include <math.h>

int main() {
    double result, tmp_pi = 0, pi = 4;
    int precision, i = 1;
    printf("Enter precision of Pi calculation in digits: ");
    scanf_s("%d", &precision);
    for (i = 1 ; ; i ++){
        if (fabs(pi - tmp_pi) <= 1/pow(10, precision))
            break;
        tmp_pi = pi;
        pi +=  4 / ((2*i + 1) *  pow(-1, i));
    }
    result = (pi + tmp_pi) / 2;
    printf("Pi = %.*f\n",precision, (double)(((int)(result*pow(10,precision)))/pow(10,precision)));
    printf("%d iterations", i - 1);
    return 0;
}