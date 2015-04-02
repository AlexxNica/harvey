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

static Alarms	alarms;
static Rendez	alarmr;

void
alarmkproc(void* v)
{
	Proc *rp;
	uint32_t now;

	for(;;){
		now = sys->ticks;
		qlock(&alarms);
		while((rp = alarms.head) && rp->alarm <= now){
			if(rp->alarm != 0L){
				if(canqlock(&rp->debug)){
					if(!waserror()){
						postnote(rp, 0, "alarm", NUser);
						poperror();
					}
					qunlock(&rp->debug);
					rp->alarm = 0L;
				}else
					break;
			}
			alarms.head = rp->palarm;
		}
		qunlock(&alarms);

		sleep(&alarmr, return0, 0);
	}
}

/*
 *  called every clock tick
 */
void
checkalarms(void)
{
	Proc *p;
	uint32_t now;

	p = alarms.head;
	now = sys->ticks;

	if(p && p->alarm <= now)
		wakeup(&alarmr);
}

uint32_t
procalarm(uint32_t time)
{
	Proc **l, *f;
	uint32_t when, old;

	if(m->externup->alarm)
		old = tk2ms(m->externup->alarm - sys->ticks);
	else
		old = 0;
	if(time == 0) {
		m->externup->alarm = 0;
		return old;
	}
	when = ms2tk(time)+sys->ticks;

	qlock(&alarms);
	l = &alarms.head;
	for(f = *l; f; f = f->palarm) {
		if(m->externup == f){
			*l = f->palarm;
			break;
		}
		l = &f->palarm;
	}

	m->externup->palarm = 0;
	if(alarms.head) {
		l = &alarms.head;
		for(f = *l; f; f = f->palarm) {
			if(f->alarm > when) {
				m->externup->palarm = f;
				*l = m->externup;
				goto done;
			}
			l = &f->palarm;
		}
		*l = m->externup;
	}
	else
		alarms.head = m->externup;
done:
	m->externup->alarm = when;
	qunlock(&alarms);

	return old;
}
