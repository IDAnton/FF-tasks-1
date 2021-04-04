#include <stdio.h>
#include <math.h>
#include <float.h>

float func(float x){
    return tan(x*0.5 + 0.2) - pow(x, 2);
}

float func_d2(float x){
    return sin(x * 0.5 + 0.25) / 2 / cos(x * 0.5 + 0.25) - 2;
}

int integral(){
    float a, b, delta, tmp_y, y, x, res = 0, max_d2 = -FLT_MAX, accuracy;
    int n;
    printf("\nEnter A, B\n");
    scanf_s("%f %f", &a, &b);
    if (a >= b)
        return 1;
    printf("Enter number of segments\n");
    scanf_s("%d", &n);
    if (n <= 2)
        return 2;
    delta = (b - a) / n;
    tmp_y = func(a);
    x = a + delta;
    for (int i = 1; i <=n; i++){
        y = func(a + i * delta);
        res += (y + tmp_y)/2;
        tmp_y = y;
        if (func_d2(a + i * delta) > max_d2)
            max_d2 = func_d2(a + i * delta);
    }
    res = res * (b - a) / n;
    accuracy = pow(delta, 2) * (b - a) * max_d2 / 12;
    printf("Integral = %f\n", res);
    printf("Accuracy = %f\n", fabs(accuracy));
    return 0;
}

int main() {
    int error_code;
    char input;
    printf("Calculating integral of f(x) = tan(0.5x + 0.2) - x^2 from A to B\n");
    while (1){
        error_code = integral();
        if (error_code == 1)
            printf("Wrong integral limits (b > a), try again\n");
        if (error_code == 2)
            printf("Wrong number of segments, try again\n");
        if (error_code == 0){
            printf("Continue calculations ? (y/n)");
            scanf_s(" %c", &input);
            if (input == 'n')
                break;
        }
    }
    return 0;
}
