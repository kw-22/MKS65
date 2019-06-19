#include <stdio.h>
#include <stdlib.h>



/*********************
 *      problem 1    *
 *********************/

//computes the sum of multiples of a or b below max
int sum_multiple(int a, int b, int max)
{
	int sum = 0;

	for (int i = 1; i < max; i++)
		if (i % a == 0 || i % b == 0) sum += i;

	return sum;
}


/*******************
 *    problem 2    *
 *******************/

//computes the sum of the even Fib #s not exceeding max
int even_fib_sum(int max)
{
	int sum = 2;

	if (max < 8) return sum; //only Fib # less than 8 is 2

	//terms of Fibonacci seq
	int f1 = 1;
	int f2 = 2;
	int f3 = 3;

	while (f3 <= max) {
		if (f3 % 2 == 0) sum += f3; //add to sum

		//update values
		f1 = f2;
		f2 = f3;
		f3 = f1 + f2;
	}

	return sum;
}


/*******************
 *    problem 5    *
 *******************/

//computes the smallest positive number evenly divisible by all of the #s from 1 to max
int super_lcm(int max)
{
	int n = 1; //starting factor
	int ans = 1;

	while (n <= max) {
		//if ans does not already have n as a factor
		if (ans % n != 0) {
			//if ans and n are not mutually exclusive, multiply ans by whatever prime factors in n
			//that are not in ans
			if (n % (ans % n) == 0)
				ans *= n / (ans % n);
			else //mutually exclusive
				ans *= n;
		}
		n++; //increment to the next #
	}

	return ans;
}


/*******************
 *    problem 6    *
 *******************/

//finds the positive differnce between the square of the sum and the sum of the squares of the first
//n natural #s
int sum_square_diff(int n)
{
	int sum_square = n * (n + 1) * (2 * n +1) / 6;
	int square_sum = n * n * (n + 1) * (n + 1) / 4;
	return square_sum - sum_square;
}


/*******************
 *    problem 7    *
 *******************/

//finds the nth prime # by using def of prime
int prime_finder(int n)
{
	int primes[n]; //holds array of primes
	primes[0] = 2; //first prime #
	int pos = 1; //pos of next prime
	int num = 3; //next # to test
	while (pos < n) {
		int success = 0; //# of times a prime from array failed to be factor of num

		for (int i = 0; i < pos; i++) {
			//if factor is found
			if (num % primes[i] == 0) {
				num++;
				break;
			}
			success++;

		}
		//else add prime
		if (success == pos) {
			primes[pos] = num;
			pos++;
			num++;
		}
	}

	return primes[n - 1];
}

int main()
{
	//printf("The sum of the multiples of 3 or 5 less than 10 is: %d\n", sum_multiple(3, 5, 10));
	printf("The sum of the multiples of 3 or 5 less than 1000 is: %d\n\n", sum_multiple(3, 5, 1000));

	//printf("The sum of the even-valued terms of the Fibonacci sequence not exceeding 10 is: %d\n", even_fib_sum(10));
	printf("The sum of the even-valued terms of the Fibonacci sequence not exceeding 4000000 is: %d\n\n", even_fib_sum(4000000));

	//for (int i = 1; i < 23; i++) printf("The smallest integer with 1-%d as factors is: %d\n", i, super_lcm(i));
	printf("The smallest integer with 1-20 as factors is: %d\n\n", super_lcm(20));

	//printf("The difference between the sum of the squares of the first 10 natural #s is: %d\n", sum_square_diff(10));
	printf("The difference between the sum of the squares of the first 100 natural #s is: %d\n\n", sum_square_diff(100));

	//printf("The 6th prime is: %d\n", prime_finder(6));
	printf("The 10001th prime is: %d\n", prime_finder(10001));

	return 0;
}
