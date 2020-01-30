/* Original 64 bits Mersenne Twister by Nishimura & Matsumoto.

	 Some cosmetic modifications made for the FPNGlib library. The biggest 
	 modification is the creationg of a local state instead of a global state to allow
	 parallel calls and more than one MT.

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

#ifndef __mt19937_64_h__
#define __mt19937_64_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>
#include <fpnglib/irng64_t.h>

#ifdef __cplusplus
extern "C" {
#endif

	// Creating a MT19937-based RNG with a unique integer as seed.
	fpngl_irng64_t *fpngl_mt19937v64(uint64_t seed);

	// Initialization of MT19937 with an array of integers. The seed is then set to 0
	// The array used for the initialization cannot be retrieved afterwards.
	fpngl_irng64_t *fpngl_mt19937v64_by_array(const uint64_t init_key[],
																						uint64_t key_length);


#ifdef __cplusplus
}
#endif
	
#endif // __mt19937_64_h__
