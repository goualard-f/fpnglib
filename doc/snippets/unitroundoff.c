// doc/snippets/unitroundoff.c
#include <stdio.h>
#include <fpnglib/constants32.h>
#include <fpnglib/constants64.h>

int main(void)
{
	printf("Single precision unit roundoff: %g\n",fpngl_u32);
	printf("Double precision unit roundoff: %g\n",fpngl_u64);
}
