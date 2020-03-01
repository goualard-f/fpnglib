// doc/snippets/isimple.c
#include <stdio.h>
#include <fpnglib/mt19937ar.h>

const uint32_t seed = 13;

int main(void)
{
  fpngl_irng32_t *irng32 = fpngl_mt19937v32(seed);
  printf("%u\n",fpngl_irng32_next32(irng32));
  printf("%lu\n",fpngl_irng32_next64(irng32));
  fpngl_irng32_delete(irng32);
}
