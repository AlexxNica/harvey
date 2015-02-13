/*
 * This file is part of the UCB release of Plan 9. It is subject to the license
 * terms in the LICENSE file found in the top-level directory of this
 * distribution and at http://akaros.cs.berkeley.edu/files/Plan9License. No
 * part of the UCB release of Plan 9, including this file, may be copied,
 * modified, propagated, or distributed except according to the terms contained
 * in the LICENSE file.
 */

#include <u.h>
#include <libc.h>

void*	listalloc(int32_t, int32_t);

void *
listalloc(int32_t n, int32_t size)
{
	int8_t *p, *base;

	size = (size+sizeof(ulong)-1)/sizeof(ulong)*sizeof(ulong);
	p = base = malloc(n*size);
	while(--n > 0){
		*(int8_t**)p = p+size;
		p += size;
	}
	*(int8_t**)p = 0;
	return base;
}
