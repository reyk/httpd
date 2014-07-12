/*	$OpenBSD$	*/

/*
 * Copyright (c) 2011 - 2014 Reyk Floeter <reyk@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/queue.h>
#include <sys/uio.h>

#include <net/if.h>
#include <net/pfvar.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <net/route.h>

#include <ctype.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <event.h>
#include <limits.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <ifaddrs.h>

#include <openssl/ssl.h>

#include "httpd.h"

int
config_init(struct httpd *env)
{
	struct privsep	*ps = env->sc_ps;
	u_int		 what;

	/* Global configuration */
	if (privsep_process == PROC_PARENT) {
		env->sc_prefork_server = SERVER_NUMPROC;

		ps->ps_what[PROC_PARENT] = CONFIG_ALL;
		ps->ps_what[PROC_SERVER] = CONFIG_SERVERS;
	}

	/* Other configuration */
	what = ps->ps_what[privsep_process];

	if (what & CONFIG_SERVERS) {
		if ((env->sc_servers =
		    calloc(1, sizeof(*env->sc_servers))) == NULL)
			return (-1);
		TAILQ_INIT(env->sc_servers);
	}

	return (0);
}

void
config_purge(struct httpd *env, u_int reset)
{
	struct privsep		*ps = env->sc_ps;
	struct server		*srv;
	u_int			 what;

	what = ps->ps_what[privsep_process] & reset;

	if (what & CONFIG_SERVERS && env->sc_servers != NULL) {
		while ((srv = TAILQ_FIRST(env->sc_servers)) != NULL) {
			TAILQ_REMOVE(env->sc_servers, srv, srv_entry);
			free(srv);
		}
	}
}

int
config_setreset(struct httpd *env, u_int reset)
{
	struct privsep	*ps = env->sc_ps;
	int		 id;

	for (id = 0; id < PROC_MAX; id++) {
		if ((reset & ps->ps_what[id]) == 0 ||
		    id == privsep_process)
			continue;
		proc_compose_imsg(ps, id, -1, IMSG_CTL_RESET, -1,
		    &reset, sizeof(reset));
	}

	return (0);
}

int
config_getreset(struct httpd *env, struct imsg *imsg)
{
	u_int		 mode;

	IMSG_SIZE_CHECK(imsg, &mode);
	memcpy(&mode, imsg->data, sizeof(mode));

	config_purge(env, mode);

	return (0);
}

int
config_getcfg(struct httpd *env, struct imsg *imsg)
{
	struct privsep		*ps = env->sc_ps;
	struct ctl_flags	 cf;
	u_int			 what;

	if (IMSG_DATA_SIZE(imsg) != sizeof(cf))
		return (0); /* ignore */

	/* Update runtime flags */
	memcpy(&cf, imsg->data, sizeof(cf));
	env->sc_opts = cf.cf_opts;
	env->sc_flags = cf.cf_flags;

	what = ps->ps_what[privsep_process];

	return (0);
}
