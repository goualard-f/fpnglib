// doc/snippets/lambda.c
#include <stdio.h>
#include <fpnglib/constants32.h>
#include <fpnglib/constants64.h>

int main(void)
{
  printf("Single precision smallest positive normal: %g\n",
         fpngl_lambda32);
  printf("Double precision smallest positive normal: %g\n",
         fpngl_lambda64);
}
