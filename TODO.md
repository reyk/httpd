OpenBSD httpd TODO
==================

There is no official bug tracker at the moment.  You can look at the
OpenBSD lists and the following summary which might be incomplete or
outdated:

#20150102-01 return **OPEN**
----------------------------

redirects / return 301 etc.: This can be done without regex by
using a few built-in variables.  Current workaround is to either do it
in the fastcgi backend or with, ahem, html refresh.  btw., nginx'
"return 444;" is such an ugly workaround...

#20150102-02 basic auth **OPEN**
--------------------------------

We don't have a satisfying implementation for authentication yet.  But
it is needed and will be done.

#20150102-03 block/deny **OPEN**
--------------------------------

We cannot deny access to specific locations but the current workaround
is to set a non-accessible root:

        location "*/.*" {
                # mkdir -m 0 /var/www/forbidden
                root "/forbidden"
        }

#20150102-04 server aliases **CLOSED**
--------------------------------------

Update: server aliases and multiple listen statements are supported:

> Support alias names and multiple listen statements per server block.
The implementation is done in the parser by expanding each
alias/listen into an independent server configuration; this makes it
easier to handle internally without adding additional loops or
conditions.

	server "www.example.com" {
		alias "example.com"
		listen on * port 80
		listen on * tls port 443
	}

Server aliases and a few restrictions of the grammar: Individual
server blocks can currently only have one name and listen statement.
This will be fixed in the parser later.  To avoid too much repeating
configuration, I currently use includes:

        server "www.example.com" {
                listen on $ip4_addr port 80
                include "/etc/httpd/example.com.inc"
        }
        server "www.example.com" {
                listen on $ip6_addr port 80
                include "/etc/httpd/example.com.inc"
        }
        server "www.example.com" {
                listen on $ip4_addr tls port 443
                include "/etc/httpd/example.com.ssl"
                include "/etc/httpd/example.com.inc"
        }
        server "www.example.com" {
                listen on $ip6_addr tls port 443
                include "/etc/httpd/example.com.ssl"
                include "/etc/httpd/example.com.inc"
        }

#20150102-05 charsets **OPEN**
------------------------------

Some minor things, eg. charsets (for auto index), fixes, ...

#20150102-06 FAQ **OPEN**
-------------------------

The web server needs some more FAQ-style documentation in addition to
our excellent man pages and examples.  Examples for each CMS would go
beyond the scope of them, and probably don't fit into the OpenBSD FAQ.
So I'm thinking about putting something on http://bsd.plumbing/.

#20150102-07 root strip **CLOSED**
----------------------------------

Update: committed.

Finish httpd URI stripping by Christopher Zimmermann.
