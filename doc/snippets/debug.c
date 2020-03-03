// doc/snippets/debug.c
#include <fpnglib/debug.h>

int main(void)
{
  double a = 1.0;
  FPNGL_DEBUG("This will be displayed only in debug mode: %g\n",a);
}
