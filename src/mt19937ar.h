/* Original 32 bits Mersenne Twister by Nishimura & Matsumoto.

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

#ifndef __mt19937ar_h__
#define __mt19937ar__h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>
#include <fpnglib/irng32_t.h>

#ifdef __cplusplus
extern "C" {
#endif
	// Initialization of MT19937 with an integer. The seed shall not be 0, since
	// that value is used to signal that MT19937 was initialized with an array and
	// not a single value.
	fpngl_irng32_t *fpngl_mt19937v32(uint32_t seed);
	// Initialization of MT19937 with an array of integers. The seed is then set to 0
	// The array used for the initialization cannot be retrieved afterwards.
	fpngl_irng32_t *fpngl_mt19937v32_by_array(const uint32_t init_key[],
																						uint32_t key_length);
	

#ifdef __cplusplus
}
#endif
	
#endif // __mt19937ar_h__
