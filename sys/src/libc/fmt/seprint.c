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

char*
seprint(char *buf, char *e, char *fmt, ...)
{
	va_list va, args;
	char *p;

	va_start(va, fmt);
	va_copy(args, va);
	va_end(va);
	p = vseprint(buf, e, fmt, args);
	va_end(args);
	return p;
}
