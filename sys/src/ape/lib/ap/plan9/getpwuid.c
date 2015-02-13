/*
 * This file is part of the UCB release of Plan 9. It is subject to the license
 * terms in the LICENSE file found in the top-level directory of this
 * distribution and at http://akaros.cs.berkeley.edu/files/Plan9License. No
 * part of the UCB release of Plan 9, including this file, may be copied,
 * modified, propagated, or distributed except according to the terms contained
 * in the LICENSE file.
 */

#include <stddef.h>
#include <pwd.h>
#include <string.h>

extern int _getpw(int *, int8_t **, int8_t **);

static struct passwd holdpw;
static int8_t dirbuf[40] = "/usr/";
static int8_t *rc = "/bin/rc";

struct passwd *
getpwuid(uid_t uid)
{
	int num;
	int8_t *nam, *mem;

	num = uid;
	nam = 0;
	mem = 0;
	if(_getpw(&num, &nam, &mem)){
		holdpw.pw_name = nam;
		holdpw.pw_uid = num;
		holdpw.pw_gid = num;
		strncpy(dirbuf+5, nam, sizeof(dirbuf)-6);
		holdpw.pw_dir = dirbuf;
		holdpw.pw_shell = rc;
		return &holdpw;
	}
	return NULL;
}
