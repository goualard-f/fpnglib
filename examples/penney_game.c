/* An implementation of Penney's Game.
   See https://en.wikipedia.org/wiki/Penney%27s_game

	Copyright 2019--2020 University of Nantes, France.

	This file is part of the FPNGlib library.

	The FPNGlib library is free software; you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by the 
	Free Software Foundation; either version 3 of the License, or (at your
	option) any later version.
	
	The FPNGlib library is distributed in the hope that it will be useful, but
	WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
	or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.
	
	You should have received copies of the GNU General Public License and the
	GNU Lesser General Public License along with the FPNGlib Library.  If not,
	see https://www.gnu.org/licenses/. 	
	
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <fpnglib/mt19937ar.h>
#include <fpnglib/irng_t.h>
#include <fpnglib/irange.h>


// See initializing the Random Number Generator
const uint32_t seed = 42;

// Correspondence between 0 and 1 and 'H' and 'T'
const char HT[2] = {'H', 'T'};

// Shifting the past results one place to the left to accommodate for the new result
void shift(char buffer[4], char ht)
{
	buffer[0] = buffer[1];
	buffer[1] = buffer[2];
	buffer[2] = ht;
}

void penney(const char seq[4], fpngl_irng_t *irng)
{
	char seq_machine[4] = {seq[1] == 'H' ? 'T' : 'H',
												 seq[0], seq[1], '\0'};
	printf("My sequence: %s\n",seq_machine);
	char draws[4] = "___"; // Buffer to remember the past 3 draws
	printf("Draws: ");
	while (1) {
		char draw = HT[fpngl_ubound32(irng,2)];
		printf("%c",draw);
		fflush(stdout);
		sleep(1);
		shift(draws,draw);
		if (!strcmp(seq,draws)) {
			printf("\nYou win!\n");
			return;
		} else {
			if (!strcmp(seq_machine,draws)) {
				printf("\nI win!\n");
				return;
			}
		}
	}
}

int main(void)
{
	fpngl_irng_t *irng = fpngl_irng_new32(fpngl_mt19937v32(seed));
	
	bool end = false;
	while (!end) {
		char sequence[4];
		printf("Your sequence H/T (or E to stop)? ");
		scanf("%3s",sequence);
		end = (!strcmp(sequence,"E"));
		if (!end) {
			penney(sequence,irng);
		}
	}
	fpngl_irng_delete(irng);

}
