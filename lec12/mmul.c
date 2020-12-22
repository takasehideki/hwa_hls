#include <stdio.h>
#include <stdlib.h>

#define P 16  /* the number of dimension */
#define ERROR_RATE 0.1

/* SW function as the baseline */
void mmul_sw(float a[P][P], float b[P][P], float c[P][P]) {
  int i, j, k;

  for (i = 0; i < P; i++) {
    for (j = 0; j < P; j++) {
      c[i][j] = 0;
      for (k = 0; k < P / 2; k++) {
        c[i][j] += a[i][k] * b[k][j];
        c[i][j] -= a[i][k + 1] * b[k + 1][j];
      }
    }
  }
}

/* HW function to be synthesized as a circuit */
void mmul_hw(float a[P][P], float b[P][P], float c[P][P]) {
  int i, j, k;

  Loop1: for (i = 0; i < P; i++) {
    Loop2: for (j = 0; j < P; j++) {
      c[i][j] = 0;
      Loop3: for (k = 0; k < P / 2; k++) {
        c[i][j] += a[i][k] * b[k][j];
        c[i][j] -= a[i][k + 1] * b[k + 1][j];
      }
    }
  }
}

int main()
{
  printf("Hello! mmul\n");
  float a[P][P], b[P][P], c[P][P], d[P][P];
  int i, j;

  /* initialize input data */
  for (i = 0; i < P; i++)
  {
    for (j = 0; j < P; j++)
    {
      a[i][j] = (rand() % 1000) / 100.0;
      b[i][j] = (rand() % 1000) / 100.0;
    }
  }

  /* execute both as SW and HW */
  mmul_sw(a, b, c);
  mmul_hw(a, b, d);

  /* check each result */
  int error = 0;
  for (i = 0; i < P; i++) {
    for (j = 0; j < P; j++) {
      if (c[i][j] - d[i][j] > ERROR_RATE) {
        printf("NG: ");
        error++;
      } else {
        printf("OK: ");
      }
      printf("a=%f, b=%f, sw=%f, hw=%f\n", a[i][j], b[i][j], c[i][j], d[i][j]);
    }
  }

  /* final answer?? */
  if (error)
    printf("TEST Failed (error: %d)\n", error);
  else
    printf("TEST Succeeded\n");

  printf("end mmul\n");

  return 0;
}