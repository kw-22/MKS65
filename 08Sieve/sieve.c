#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* #include <sys/time.h> */
#include "sieve.h"
/* #define free(x) [>no-op<] */

int sieve(int target)
{
	/* double start, end, total; */
	/* struct timeval timecheck; */

	if (target == 1)
		return 2;
	else {
		register int len = log(target) * target * 1.13;
		char *nums = calloc(len, sizeof(char));

		target -= 1;

		register unsigned int pos = 3; //initial starting position (equiv. to prime #)

		while (target) {
			while(nums[pos]) //whether # has been marked as composite
				pos += 2;

			register unsigned int n = pos;
			while (n < len) {
				if (!nums[n]) //mark # as composite
					nums[n] = 1;
				n += pos << 1; //computes all multiples of pos, skipping all even ones
			}

			target -= 1;
		}

		free(nums);
		return pos;
	}

	/* gettimeofday(&timecheck, NULL); */
	/* start = (long)timecheck.tv_sec * 1000 + (double)timecheck.tv_usec / 1000; */
	/* gettimeofday(&timecheck, NULL); */
	/* end = (long)timecheck.tv_sec * 1000 + (double)timecheck.tv_usec / 1000; */
	/* total = end - start; */
	/* printf("time: %lf", total); */
}
