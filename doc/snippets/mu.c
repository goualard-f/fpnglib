// doc/snippets/mu.c
#include <stdio.h>
#include <math.h>
#include <fpnglib/constants32.h>
#include <fpnglib/constants64.h>

int main(void)
{
  printf("%d\n",nextafterf(0.0f,1.0f) == fpngl_mu32);
  printf("%d\n",nextafter(0.0,1.0) == fpngl_mu64);
}
