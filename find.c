/*
 * UNG's Not GNU
 *
 * Copyright (c) 2023, Jakob Kaivo <jkk@ung.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define _XOPEN_SOURCE 700
#include <errno.h>
#include <ftw.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static int find_ftw(const char *path, const struct stat *st, int flags, struct FTW *ftw)
{
	(void)st;
	(void)flags;
	(void)ftw;
	printf("%s\n", path);
	return 0;
}

static int find (const char *path, int argc, char *argv[])
{
	(void)argc; (void)argv;
	nftw(path, find_ftw, 0, 0);
	return 0;
}

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");

	int c;
	while ((c = getopt(argc, argv, "HL")) != -1) {
		switch(c) {
		case 'H':	/** ??? **/
			/* TODO */
			break;

		case 'L':	/** ??? **/
			/* TODO */
			break;

		default:
			return 1;
		}
	}

	int firstdir = optind;

	/* determine first operand */
	while (optind < argc) {
		if (argv[optind][0] == '-') {
			break;
		}
		if (!strcmp(argv[optind], "!")) {
			break;
		}
		if (!strcmp(argv[optind], "(")) {
			break;
		}
		optind++;
	}

	int lastdir = optind;

	if (firstdir == lastdir) {
		fprintf(stderr, "%s: missing path\n", argv[0]);
		return 1;
	}

	int ret = 0;
	for (int i = firstdir; i < lastdir; i++) {
		ret |= find(argv[i], argc, argv + optind);
	}

	return 0;
}
