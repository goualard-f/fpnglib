/* Implementation of xorgens algorithms by Richard P. Brent.

	 The code given here is a slight modification of the files xorgens.h and xorgens.c 
	 available at https://maths-people.anu.edu.au/~brent/random.html to obey the 
	 conventions of FPNGlib. The original copyright statement is given after this
	 comment.

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

/* xorgens.h version 3.06, R. P. Brent, 20080920..20171215

==========================================================================
|                                                                        |
|  Copyright (C) 2004, 2006, 2008, 2017 R. P. Brent.                                 |
|                                                                        |
|  This program is free software; you can redistribute it and/or         |
|  modify it under the terms of the GNU General Public License,          |
|  version 2, June 1991, as published by the Free Software Foundation.   |
|  For details see http://www.gnu.org/copyleft/gpl.html .                |
|                                                                        |
|  If you would like to use this software but the GNU GPL creates legal  |
|  problems, then please contact the author to negotiate a special       |
|  agreement.                                                            |
|                                                                        |
==========================================================================
*/

#ifndef __xorgens_h__
#define __xorgens_h__

//#include <fpnglib/fpngl_config.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

	uint32_t  xor4096iv32(uint32_t seed);  /* integer random number generator */
	uint64_t  xor4096iv64(uint64_t seed);  /* integer random number generator */

	float xor4096rv32(uint64_t seed);  /* real random number generator */
	double xor4096rv64(uint64_t seed);  /* real random number generator */
	
#ifdef __cplusplus
}
#endif

#endif // __fpngl_xorgens_h__
