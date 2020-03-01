// doc/snippets/fsimple.c
#include <stdio.h>
#include <fpnglib/frng64_java.h>

const uint32_t seed = 13;

int main(void)
{
  fpngl_frng64_t *frng64 = fpngl_java(seed);
  printf("%a\n",fpngl_frng64_nextf64(frng64));
  fpngl_frng64_delete(frng64);
}
