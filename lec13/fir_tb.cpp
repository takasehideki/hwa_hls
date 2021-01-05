#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fir(int *y, int x);

#define PREC 65536 // 2**16 sign + 15bit precision

int main()
{
  float fs = 44100.0;
  int len = 1000;

  float f0 = 20000.0;
  float sin_wave;
  int fir_out;

  int i;

  int error = 0;
  int fir_dat;
  FILE *fp;
  fp = fopen("./fir_tb.dat", "r");

  for( i = 0; i < len; i++){
    sin_wave = sin( 2.0 * M_PI * f0 * i / fs);

    fir( &fir_out, (int)(sin_wave * PREC));

    f0 = f0 - 10.0;

    fscanf(fp, "%d\n", &fir_dat);
    if (fir_out == fir_dat) {
      printf("OK: ");
    } else {
      printf("NG: ");
      error++;
    }
    printf("%d %f %f %f\n", i, sin_wave, (float)fir_out / PREC, (float)fir_dat / PREC);
  }
  fclose(fp);

  if (error)
    printf("TEST Failed (error: %d)\n", error);
  else
    printf("TEST Succeeded\n");

  return 0;
}
