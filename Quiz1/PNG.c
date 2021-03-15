#include<stdlib.h>
#include<math.h>

struct ACORN {
    int precision_multiplier;
    int K;
    int N;
    int M;
    int seed;
    int auto_correct_seed; // it's a bool
    int *initial_value;
};

void initializeACORN(struct ACORN *acorn)
{
    acorn->precision_multiplier = 1;
    acorn->K = 10000;
    acorn->N = 1;
    acorn->M = pow(2, 30 * acorn->precision_multiplier); // Can I acutally use pow()? Or define a pow by myself?
    acorn->seed = 0;
    acorn->auto_correct_seed = 1;
    acorn->initial_value = NULL;
}

int IsSeedValid(struct ACORN *acorn)
{
    if (acorn->seed <= 0)
        return 0;
    if (acorn->seed % 2 == 0){
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

void Random()
{

}