#ifndef __PNG_H
#define __PNG_H

struct ACORN *NewACORN();
void SetProperty(struct ACORN *acorn, int pricision, int order, int auto_correct);
void SetInitialValue(struct ACORN *acorn, long long int *initVal, int size);
void FreeACORN(struct ACORN *acorn);
float *RandomArray(struct ACORN *acorn, long long seed, int length);
float Random(struct ACORN *acorn, long long seed);

#endif