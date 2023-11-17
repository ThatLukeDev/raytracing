// modified to be class-contained
/* Copyright (C) 1995-2018 Free Software Foundation, Inc.
 * This is derived from the Berkeley source:
 *			@(#)random.c		5.5 (Berkeley) 7/6/88
 * It was reworked for the GNU C Library by Roland McGrath.
 * Rewritten to use reentrant functions by Ulrich Drepper, 1995.
	 Copyright (C)Regents of the University of California.
	 All rights reserved.
*/

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <cstring>

#define TYPE_0		0
#define BREAK_0		8
#define DEG_0		0
#define SEP_0		0

#define TYPE_1		1
#define BREAK_1		32
#define DEG_1		7
#define SEP_1		3

#define TYPE_2		2
#define BREAK_2		64
#define DEG_2		15
#define SEP_2		1

#define TYPE_3		3
#define BREAK_3		128
#define DEG_3		31
#define SEP_3		3

#define TYPE_4		4
#define BREAK_4		256
#define DEG_4		63
#define SEP_4		1


// Array versions of the above information to make code run faster.
#define MAX_TYPES 5

static int32_t randtbl[DEG_3 + 1] =
{
	TYPE_3,
	-1726662223, 379960547, 1735697613, 1040273694, 1313901226,
	1627687941, -179304937, -2073333483, 1780058412, -1989503057,
	-615974602, 344556628, 939512070, -1249116260, 1507946756,
	-812545463, 154635395, 1388815473, -1926676823, 525320961,
	-1009028674, 968117788, -123449607, 1284210865, 435012392,
	-2017506339, -911064859, -370259173, 1132637927, 1398500161,
	-205601318,
};

static struct random_data unsafe_state =
{
	.fptr = &randtbl[SEP_3 + 1],
	.rptr = &randtbl[1],

	.state = &randtbl[1],

	.rand_type = TYPE_3,
	.rand_deg = DEG_3,
	.rand_sep = SEP_3,

	.end_ptr = &randtbl[sizeof (randtbl) / sizeof (randtbl[0])]
};


// __srandom_r (seed, &unsafe_state); -- changes seed

long int __random (void) {
	int32_t retval;
	random_r (&unsafe_state, &retval);
	return retval;
}

struct random_poly_info
{
	int seps[MAX_TYPES];
	int degrees[MAX_TYPES];
};
static constexpr struct random_poly_info random_poly_info =
{
	{ SEP_0, SEP_1, SEP_2, SEP_3, SEP_4 },
	{ DEG_0, DEG_1, DEG_2, DEG_3, DEG_4 }
};

int __srandom_r (unsigned int seed, struct random_data *buf)
{
	int type;
	int32_t *state;
	long int i;
	int32_t word;
	int32_t *dst;
	int kc;

	if (buf == NULL)
		goto fail;
	type = buf->rand_type;
	if ((unsigned int) type >= MAX_TYPES)
		goto fail;

	state = buf->state;
	/* We must make sure the seed is not 0.	Take arbitrarilyin this case.	*/
	if (seed == 0)
		seed = 1;
	state[0] = seed;
	if (type == TYPE_0)
		goto done;

	dst = state;
	word = seed;
	kc = buf->rand_deg;
	for (i = 1; i < kc; ++i)
		{
			/* This does:
					 state[i] = (16807 * state[i - 1]) % 2147483647;
				 but avoids overflowingbits.	*/
			long int hi = word / 127773;
			long int lo = word % 127773;
			word = lo - hi;
			if (word < 0)
				word += 2147483647;
			*++dst = word;
		}

	buf->fptr = &state[buf->rand_sep];
	buf->rptr = &state[0];
	kc *= 10;
	while (--kc >= 0)
		{
			int32_t discard;
			(void) random_r (buf, &discard);
		}

 done:
	return 0;

 fail:
	return -1;
}

int __random_r (struct random_data *buf, int32_t *result)
{
	int32_t *state;

	if (buf == NULL || result == NULL)
		return 0;

	state = buf->state;

	int32_t *fptr = buf->fptr;
	int32_t *rptr = buf->rptr;
	int32_t *end_ptr = buf->end_ptr;
	uint32_t val;

	val = *fptr += (uint32_t) *rptr;
	// Removing least random bit
	*result = val >> 1;
	++fptr;
	if (fptr >= end_ptr)
		{
			fptr = state;
			++rptr;
		}
	else
		{
			++rptr;
			if (rptr >= end_ptr)
				rptr = state;
		}
	buf->fptr = fptr;
	buf->rptr = rptr;
	return val >> 1;
}
