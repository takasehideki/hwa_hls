#include "ap_int.h"

typedef ap_int<16> coef_t;
typedef ap_int<16> data_t;
typedef ap_int<24> acc_t;

void fir(data_t *y, data_t x);
