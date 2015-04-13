typedef struct Mach Mach; extern Mach *m; // REMOVE ME
/*
 * This file is part of the UCB release of Plan 9. It is subject to the license
 * terms in the LICENSE file found in the top-level directory of this
 * distribution and at http://akaros.cs.berkeley.edu/files/Plan9License. No
 * part of the UCB release of Plan 9, including this file, may be copied,
 * modified, propagated, or distributed except according to the terms contained
 * in the LICENSE file.
 */

#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"
#include	"ip.h"

/*
 *  some hacks for commonality twixt inferno and plan9
 */

char*
commonuser(void)
{
	return m->externup->user;
}

Chan*
commonfdtochan(int fd, int mode, int a, int b)
{
	return fdtochan(fd, mode, a, b);
}

char*
commonerror(void)
{
	return m->externup->errstr;
}

char*
bootp(Ipifc* i)
{
	return "unimplmented";
}

int
bootpread(char* c, uint32_t n, int i)
{
	return	0;
}
