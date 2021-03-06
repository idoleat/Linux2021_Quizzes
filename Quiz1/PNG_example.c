#include <stdlib.h>
#include <stdio.h>
#include "PNG.h"

int main(void){
    struct ACORN *acorn = NewACORN();
    long long int seed;
    int length;
    float *result;

    printf("Input a seed number: \n");
    scanf("%lld", &seed);
    printf("How many numbers do you want?\n");
    scanf("%d", &length);

    printf("%f\n", Random(acorn, seed));
    
    result = RandomArray(acorn, seed, length);

    printf("======result======\n");
    if(result == NULL) 
        printf("broken result!\n");
    else{
        for(int i=0; i<length; i++){
            printf("%f\n", result[i]);
        }
    }
    free(result);
    printf("==================");

    FreeACORN(acorn);
    return 0;
}