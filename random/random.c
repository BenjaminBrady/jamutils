/* random: print cryptographically secure random numbers.
 *
 * This file is part of Jamutils.
 *
 * Copyright (C) 2021-2022 Benjamin Brady <benjamin@benjaminbrady.ie>
 *
 * Jamutils is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Jamutils is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Jamutils; see the file COPYING. If not, see <https://www.gnu.org/licenses/>.
 */
#include <limits.h>
#include <pwd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "arg.h"

#define _(a) (a)
#define ROL(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QUARTERROUND(a, b, c, d) ( \
		a += b, d ^= a, d = ROL(d, 16), \
		c += d, b ^= c, b = ROL(b, 12), \
		a += b, d ^= a, d = ROL(d,  8), \
		c += d, b ^= c, b = ROL(b,  7))
#define DOUBLEROUND(a) ( \
		QUARTERROUND(a[0], a[4], a[ 8], a[12]), \
		QUARTERROUND(a[1], a[5], a[ 9], a[13]), \
		QUARTERROUND(a[2], a[6], a[10], a[14]), \
		QUARTERROUND(a[3], a[7], a[11], a[15]), \
		QUARTERROUND(a[0], a[5], a[10], a[15]), \
		QUARTERROUND(a[1], a[6], a[11], a[12]), \
		QUARTERROUND(a[2], a[7], a[ 8], a[13]), \
		QUARTERROUND(a[3], a[4], a[ 9], a[14]))
#define COUNTER table[12]
#define SIGTOKEY(a) ((sig[4*a] << 24) + (sig[4*a+1] << 16) + \
		(sig[4*a+2] << 8) + (sig[4*a+3]))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

uint32_t get_csprng_output(void);
void chacha20(uint32_t out[16]);
uint32_t uniform_random(void);
void change_nonce(uint32_t rword);

int cflg, fflg, hflg;
char *argv0;
uint32_t table[16];
uint32_t max = RAND_MAX;

uint32_t
get_csprng_output(void)
{
	static int cnt = 16;
	static uint32_t out[16];

	++cnt;
	if (cnt >= 16) {
		cnt = 0;
		chacha20(out);
	};

	return out[cnt];
}

void
chacha20(uint32_t out[16])
{
	uint32_t x[16];

	x[ 0] = table[ 0];
	x[ 1] = table[ 1];
	x[ 2] = table[ 2];
	x[ 3] = table[ 3];
	x[ 4] = table[ 4];
	x[ 5] = table[ 5];
	x[ 6] = table[ 6];
	x[ 7] = table[ 7];
	x[ 8] = table[ 8];
	x[ 9] = table[ 9];
	x[10] = table[10];
	x[11] = table[11];
	x[12] = table[12];
	x[13] = table[13];
	x[14] = table[14];
	x[15] = table[15];

	DOUBLEROUND(x);
	DOUBLEROUND(x);
	DOUBLEROUND(x);
	DOUBLEROUND(x);
	DOUBLEROUND(x);
	DOUBLEROUND(x);
	DOUBLEROUND(x);
	DOUBLEROUND(x);
	DOUBLEROUND(x);
	DOUBLEROUND(x);

	out[ 0] = x[ 0] + table[ 0];
	out[ 1] = x[ 1] + table[ 1];
	out[ 2] = x[ 2] + table[ 2];
	out[ 3] = x[ 3] + table[ 3];
	out[ 4] = x[ 4] + table[ 4];
	out[ 5] = x[ 5] + table[ 5];
	out[ 6] = x[ 6] + table[ 6];
	out[ 7] = x[ 7] + table[ 7];
	out[ 8] = x[ 8] + table[ 8];
	out[ 9] = x[ 9] + table[ 9];
	out[10] = x[10] + table[10];
	out[11] = x[11] + table[11];
	out[12] = x[12] + table[12];
	out[13] = x[13] + table[13];
	out[14] = x[14] + table[14];
	out[15] = x[15] + table[15];

	++COUNTER;
	if (COUNTER == 0xffffffff) {
		change_nonce(out[13]);
		chacha20(out);
	};
}

uint32_t
uniform_random(void)
{
	uint64_t random, multiresult, threshold;
	uint32_t leftover;

	random = get_csprng_output();
	multiresult = random * max;
	leftover = multiresult;
	if (leftover < max) {
		threshold = -max % max;
		while (leftover < threshold) {
			random = get_csprng_output();
			multiresult = random * max;
			leftover = multiresult;
		};
	};

	return multiresult >> 32;
}

void
change_nonce(uint32_t rword)
{
	struct timespec ts;
	uint64_t nano;
	time_t sec;

	if (clock_gettime(CLOCK_REALTIME, &ts) < 0) {
		perror("clock_gettime CLOCK_REALTIME");

		sec = time(NULL);
		if (sec == (time_t)-1) {
			perror("time");
			exit(2);
		} else {
			nano = sec*1000000000;
		};
	} else {
		nano = ts.tv_sec*1000000000 + ts.tv_nsec;
	};

	table[15] = nano; nano >>= 32;
	table[14] = nano;
	table[13] = rword;
}

int
main(int argc, char *argv[])
{
	int i, req, len;
	char *ins, *user;
	char sig[32];
	struct timespec ts;
	time_t sec;
	struct passwd *pws;
	double in;
	double sup = 9.007199254740992E15; /* Maximum int-accurate double */
	uint32_t key[16];
	uint64_t nano;

	ARGBEGIN{
	case 'f': fflg = 1; /* Fallthrough */
	case 'c': cflg = 1; max = 255; break;
	case 'h': hflg = 1; break;
	case 's': cflg = 0; fflg = 0; max = RAND_MAX; break;
	case 'm':
		if ((ins = ARGF()) == NULL) goto usage;
		cflg = 0;
		fflg = 0;
		in = atof(ins);
		if (in >= 1E0 && in <= 0xffffffff) {
			max = (uint32_t) in;
		} else {
			fputs(_("Invalid maximum\n"), stderr);
			return 1;
		};
		break;
	default:
usage:
		fprintf(stderr, "usage: %s [-h] [-c|-f|-s|-m int] [int]\n",
				argv0);
		return 1;
	}ARGEND;
	if (argc && !fflg) {
		in = atof(*argv);
		if (in >= 0E0 && in < sup) {
			req = (int) in;
		} else {
			fputs(_("Invalid quantity\n"), stderr);
			return 1;
		};
	} else req = 1;
	if (max != 0xffffffff) ++max;

	if (hflg) fprintf(stderr, _("CSPRNG codomain := [0, %u]\n"), max-1);

	/* Acquire the clock time (to ns accuracy if available) */
	if (clock_gettime(CLOCK_REALTIME, &ts) < 0) {
		perror("clock_gettime CLOCK_REALTIME");

		sec = time(NULL);
		if (sec == (time_t)-1) {
			perror("time");
			return 2;
		} else {
			nano = sec*1000000000;
			srand(sec);
		};
	} else {
		nano = ts.tv_sec*1000000000 + ts.tv_nsec;
		srand(ts.tv_sec);
	};

	/* Create a basic signature of the hostname and username */
	memset(sig, 0, sizeof(sig));
	if (gethostname(sig, 16+1) < 0) {
		perror("gethostname");
	};
	if (!(pws = getpwuid(geteuid()))) {
		perror("getpwuid");
	} else {
		user = pws->pw_name;
		len = strnlen(user, 16);

		len = MIN(len, 16);
		for (i = 0; i < len; ++i) sig[i+16] = user[i];
	};

	/* For generating the key */
	table[ 0] = 0x61707865;
	table[ 1] = 0x3320646E;
	table[ 2] = 0x79622D32;
	table[ 3] = 0x6B206574;
	table[ 4] = rand() ^ SIGTOKEY(0);
	table[ 5] = rand() ^ SIGTOKEY(1);
	table[ 6] = rand() ^ SIGTOKEY(2);
	table[ 7] = rand() ^ SIGTOKEY(3);
	table[ 8] = rand() ^ SIGTOKEY(4);
	table[ 9] = rand() ^ SIGTOKEY(5);
	table[10] = rand() ^ SIGTOKEY(6);
	table[11] = rand() ^ SIGTOKEY(7);
	table[12] = 0x10102001; /* Birthday (nothing-up-my-sleeve number) */
	table[13] = nano >> 32;
	table[14] = nano;
	table[15] = rand();
	/* Run ChaCha20 on the weak random data to establish a secure key */
	chacha20(key);

	/* For generating the output */
	table[ 4] = key[0] ^ key[ 8];
	table[ 5] = key[1] ^ key[ 9];
	table[ 6] = key[2] ^ key[10];
	table[ 7] = key[3] ^ key[11];
	table[ 8] = key[4] ^ key[12];
	table[ 9] = key[5] ^ nano;
	table[10] = key[6] ^ key[14];
	table[11] = key[7] ^ key[15];
	COUNTER = 0;
	change_nonce(key[13]);

	/* Write random numbers in a loop */
	if (cflg) {
		if (fflg) {
			for (;;) putchar(uniform_random());
		} else for (i = 0; i < req; ++i) putchar(uniform_random());
	} else {
		for (i = 0; i < req; ++i) printf("%u\n", uniform_random());
	};

	return 0;
}
