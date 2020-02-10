/* Debugging facilities for the development of the library itself.

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

#ifndef __fpngl_debug_h__
#define __fpngl_debug_h__

#include <fpnglib/fpngl_config.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !NDEBUG
	/*
		Macro to output debugging messages to `stderr` if the library is compiled
		with debugging information enabled.
	*/
# define FPNGL_DEBUG(...)														\
	do {																							\
		fprintf(stderr,__VA_ARGS__);										\
		fflush(stderr);																	\
	}	while (0)

	/*
		Macro to output warning messages to `stderr` if the library is compiled
		with debugging information enabled.
	 */
# define FPNGL_WARNING(...)													\
	do {																							\
		fprintf(stderr,__VA_ARGS__);										\
		fflush(stderr);																	\
	}	while (0)

	/*
		Macro to output the contents of an integer array to stderr if the 
		library is compiled	with debugging information enabled.
	 */
# define FPNGL_INTARRAY(T,n)											\
	do {																						\
	for (uint32_t i_ = 0; i_ < n; ++i_) {						\
		FPNGL_DEBUG("%x ",T[i_]);											\
	}																								\
	FPNGL_DEBUG("\n");															\
	} while(0)
#else
# define FPNGL_DEBUG(...) do {} while (0)
# define FPNGL_WARNING(...) do {} while (0)
# define FPNGL_INTARRAY(T,n) do {} while (0)
#endif
	
#ifdef __cplusplus
}
#endif

#endif // __fpngl_debug_h__
