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

int8_t*
seprint(int8_t *buf, int8_t *e, int8_t *fmt, ...)
{
	int8_t *p;
	va_list args;

	va_start(args, fmt);
	p = vseprint(buf, e, fmt, args);
	va_end(args);
	return p;
}
