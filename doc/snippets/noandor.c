// doc/snippets/noandor.c
#include <stdio.h>
#include <fpnglib/constants64.h>

int main(void)
{
  printf("noand64 mask: %lx\n",fpngl_noand64);
  printf("noor64 mask: %lx\n",fpngl_noor64);
}
