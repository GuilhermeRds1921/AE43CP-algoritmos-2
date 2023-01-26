#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int Recursao(int a, int b){
    int val;
    if(b == 0)
        return 1;
    else if(b == 1)
        return a;
    else{
        if(b%2==0){
            val = Recursao(a, b/2);
            return val * val;
        }
        else{
            val = Recursao(a, (b-1)/2);
            return val * val * a;
        }
    }
}
int main() {
    int a, b, val;
    do{
        scanf("%d %d", &a, &b);
        if(a<0 || b<0)
            printf("valores invalidos\n");
    }while(a<=0 && b<=0);
    val = Recursao(a,b);
    printf("%d", val);
    return 0;
}
