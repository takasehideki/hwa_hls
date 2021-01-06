#include "ap_int.h"

typedef ap_int<10> coef_t;
typedef ap_uint<16> data_t;
typedef ap_uint<20> acc_t;

void fir(data_t *y, data_t x);
