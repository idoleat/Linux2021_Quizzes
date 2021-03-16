#include<stdlib.h>

/* A struct hold all the information that ACORN need.
 */
struct ACORN {
    int precision_multiplier;
    int K; /* order */
    int N; /*  */
    long long int M;
    long long int seed;
    int auto_correct_seed; // it's a bool
    long long int *initial_value;
};

long long int power(long long base, int exp)
{
    long long result = 1;
    while (exp > 0){
        result *= base;
        exp -= 1;
    }

    return result;
}

void InitializeACORN(struct ACORN *acorn)
{
    acorn->precision_multiplier = 2; // due to long long it only can be up to 2
    acorn->K = 10000;
    acorn->N = 1;
    acorn->M = power(2, 30 * acorn->precision_multiplier);
    acorn->seed = 0;
    acorn->auto_correct_seed = 1;
    acorn->initial_value = NULL;
}

int IsSeedValid(struct ACORN *acorn)
{
    if (acorn->seed <= 0)
        return 0;
    if (acorn->seed % 2 == 0){
        /* This may cause collision with other seed. Could have a better way. */
        if (acorn->auto_correct_seed) acorn->seed -= 1; 
        return 0;
    }

    return 1;
}

void SetProperty(struct ACORN *acorn, int pricision, int order, int auto_correct){
    acorn->precision_multiplier = pricision;
    acorn->K = order;
    acorn->auto_correct_seed = auto_correct;
}

long long int *Random(int seed)
{
    struct ACORN acorn;
    InitializeACORN(&acorn);
}