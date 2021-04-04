#include <stdio.h>
#include <math.h>

int main(){
    int n, prime;
    scanf_s("%d", &n);
    for(int i = 2; i <= n; i++){
        prime = 1;
        for(int j = 2; j <= sqrt(i); j++){
            if(i % j == 0) {
                prime = 0;
                break;
            }
        }
        if(prime)
            printf("%d\n", i);
    }
    getch();
    return 0;
}