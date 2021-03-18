#include <stdlib.h>
#include <stdio.h>

/* A struct hold all the information that ACORN need.
 */
struct ACORN {
    int precision_multiplier;
    int K; /* order */
    int N; /* amount of random numbers */
    long long int M; /* Modulus */
    long long int seed;
    int auto_correct_seed; // it's a bool
    long long int *initial_value;
    long long int *Y1;
    long long int *Y2;
};

long long int __power(long long base, int exp)
{
    long long result = 1;
    while (exp > 0){
        result *= base;
        exp -= 1;
    }

    return result;
}

void __initializeACORN(struct ACORN *acorn)
{
    acorn->precision_multiplier = 2; // due to long long it only can be up to 2
    acorn->K = 10000;
    acorn->N = 1;
    acorn->M = __power(2, 30 * acorn->precision_multiplier);
    acorn->seed = 0;
    acorn->auto_correct_seed = 1;
    acorn->initial_value = NULL;
    acorn->Y1 = NULL;
    acorn->Y2 = NULL;
}


/* To check the seed passed to Random() and RandomArray() is valid or not.
 */
int __isSeedValid(struct ACORN *acorn)
{
    if (acorn->seed <= 0){
        printf("[Error] Seed must greater than 0!");
        return 0;
    }
    if (acorn->seed % 2 == 0){
        /* This may cause collision with other seed. Could have a better way. */
        if (acorn->auto_correct_seed) acorn->seed -= 1;
        else {
            printf("[Error] Seed must be odd. Turn on auto_correct_seed or fix it manually.");
            return 0;
        }
    }
    if (acorn->seed >= acorn->M){
        printf("Seed must be smaller than M.");
        return 0;
    }

    if (acorn->seed < __power(10, 10))
        printf("Recommand using seed greater than 10^10 for better result.");

    return 1;
}

/* Get a initilaized ACORN struct. Return NULL on fail.
 */
struct ACORN *NewACORN()
{
    struct ACORN *acorn = malloc(sizeof(struct ACORN));
    if(acorn == NULL)
        return NULL;

    __initializeACORN(acorn);
    return acorn;
}

/* Use this function to set the value of pricision, order and auto_correct_seed.
 * Otherwies the default value will be used.
 */
void SetProperty(struct ACORN *acorn, int pricision, int order, int auto_correct)
{
    acorn->precision_multiplier = pricision;
    acorn->K = order;
    acorn->auto_correct_seed = auto_correct;
}


/* Use this function to explicitly specify the initial value for ACORN.  
 * Length of iniVal should be specified as well and K will be adjusted according to it.
 * Otherwise seed will be used as default initial values and default K will be used.
 */
void SetInitialValue(struct ACORN *acorn, long long int *initVal, int size)
{
    acorn->initial_value = initVal;
    acorn->K = size;
}

/* Free acron itself and the content it holds.
 */
void FreeACORN(struct ACORN *acorn)
{
    if (acorn->initial_value != NULL)
        free(acorn->initial_value);
    if (acorn->Y1 != NULL)
        free(acorn->Y1);
    if (acorn->Y2 != NULL)
        free(acorn->Y2);
    
    free(acorn);
}

/* Main API to generate an array of psuedorandom numbers. Will return NULL if seed and length is invalid.
 * Or unable to allocate memorry for results.
 */
float *RandomArray(struct ACORN *acorn, long long seed, int length)
{
    if (length <= 0)
        return NULL;

    acorn->seed = seed % acorn->M;
    if (!__isSeedValid(acorn))
        return NULL;

    acorn->N = length + 1; /* The first one is of seed and initial value */

    acorn->Y1 = (long long *)malloc(acorn->N * sizeof(long long int));
    acorn->Y2 = (long long *)malloc(acorn->N * sizeof(long long int));
    if(acorn->Y1 == NULL || acorn->Y2 == NULL)
        return NULL;

    for (int i=0; i<acorn->N; i++){
        acorn->Y1[i] = acorn->seed;
    }

    for (int i=0; i<acorn->K; i++){
        /* Set initial value */
        acorn->Y2[0] = acorn->initial_value == NULL ? acorn->seed : acorn->initial_value[i];
        for (int j=1; j<acorn->N; j++){
            acorn->Y2[j] = (acorn->Y1[j] + acorn->Y2[j-1]) % acorn->M;
            /* Assign Y2 value to Y1 to reuse Y1 */
            acorn->Y1[j] = acorn->Y2[j];
        }
    }

    /* Normalize the result*/
    float *result = malloc(sizeof(length * sizeof(float)));
    if(result == NULL)
        return NULL;

    for (int i=1; i<acorn->N; i++){
        result[i-1] = (float)acorn->Y2[i] / (float)acorn->M;
    }

    free(acorn->Y1);
    acorn->Y1 = NULL;
    free(acorn->Y2);
    acorn->Y2 = NULL;

    return result;
}

/* Main API to generate psuedorandom number. Will return -1.0 if seed is invalid.
 */
float Random(struct ACORN *acorn, long long seed)
{
    float *result = RandomArray(acorn, seed, 1);
    if(result == NULL)
        return -1.0;

    float number = *result;
    free(result);

    return number;
}

