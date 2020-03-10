// doc/snippets/irng.c
#include <stdio.h>
#include <fpnglib/irng_t.h>
#include <fpnglib/xorgens.h>

const uint32_t seed = 13;

void draw_twice(fpngl_irng_t *irng)
{
  printf("%lu\t%lu\n",fpngl_irng_next64(irng), fpngl_irng_next64(irng));
}

int main(void)
{
  fpngl_irng32_t *irng32 = fpngl_xor4096iv32(seed);
  fpngl_irng_t *irng = fpngl_irng_new32(irng32);
  draw_twice(irng);
  fpngl_irng_delete(irng);
  fpngl_irng64_t *irng64 = fpngl_xor4096iv64(seed);
  irng = fpngl_irng_new64(irng64);
  draw_twice(irng);
  fpngl_irng_delete(irng);
}
