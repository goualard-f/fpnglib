// doc/snippets/warning.c
#include <fpnglib/debug.h>

int main(void)
{
  double a = 1.0;
  FPNGL_WARNING("This will be displayed in debug/info mode: %g\n",a);
}
