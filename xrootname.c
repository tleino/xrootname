/*
 * ISC License
 *
 * Copyright (c) 2022, Tommi Leino <namhas@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
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

#include <X11/Xlib.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Display *dpy;

static void setstatus(char *str);

int
main(int argc, char **argv)
{
	char *s = NULL;
	size_t sz = 0;
	ssize_t len;

	if (!(dpy = XOpenDisplay(NULL)))
		err(1, "cannot open display");

	for (;;) {
		len = getline(&s, &sz, stdin);

		if (feof(stdin))
			break;
		else if (len <= 0)
			err(1, "getline");

		s[strcspn(s, "\r\n")] = '\0';
		setstatus(s);
	}

	if (s != NULL)
		free(s);

	XCloseDisplay(dpy);
	return 0;
}

static void
setstatus(char *str)
{
	XStoreName(dpy, DefaultRootWindow(dpy), str);
	XSync(dpy, False);
}
