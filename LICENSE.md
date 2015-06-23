License
=======

httpd is free software under OpenBSD's ISC-style license.

* httpd is based on OpenBSD relayd
* Most of the code has been written by Reyk Floeter <reyk@openbsd.org>
* And initially also by Pierre-Yves Ritschard <pyr@openbsd.org>
* FastCGI code has been written by Florian Obser <florian@openbsd.org>
* Please refer to the individual source files for other copyright holders!
* Files in rfc/ are provided as reference; see their "Copyright Notice"

> Copyright (c) 2007-2015 Reyk Floeter <reyk@openbsd.org>
> 
> Permission to use, copy, modify, and distribute this software for any
> purpose with or without fee is hereby granted, provided that the above
> copyright notice and this permission notice appear in all copies.
> 
> THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
> WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
> MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
> ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
> WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
> ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
> OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

* One exception is
[`patterns.c`](https://github.com/reyk/httpd/blob/master/httpd/patterns.c)
that is derived from the pattern matching code in Lua's `lstrlib.c`.

> Copyright (c) 2015 Reyk Floeter <reyk@openbsd.org>
> Copyright (C) 1994-2015 Lua.org, PUC-Rio.
>
> Permission is hereby granted, free of charge, to any person obtaining
> a copy of this software and associated documentation files (the
> "Software"), to deal in the Software without restriction, including
> without limitation the rights to use, copy, modify, merge, publish,
> distribute, sublicense, and/or sell copies of the Software, and to
> permit persons to whom the Software is furnished to do so, subject to
> the following conditions:
>
> The above copyright notice and this permission notice shall be
> included in all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
> EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
> MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
> IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
> CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
> TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
> SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
>
> Derived from Lua 5.3.1:
> $Id: patterns.c,v 1.2 2015/06/23 15:35:20 semarie Exp $
> Standard library for string operations and pattern-matching
