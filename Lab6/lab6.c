#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define THREADS 8

int *primes;
int counter = 0;
pthread_mutex_t mutex;

void *prime(int n)
{
	bool isPrime = true;
    
	if (n == 0 || n == 1)
	{
		return 0;
	}

	for (int i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
		{
			isPrime = false;
			break;
		}
	}

	if (isPrime == true)
	{
		pthread_mutex_lock(&mutex);
		primes[counter] = n;
		counter++;
		pthread_mutex_unlock(&mutex);
	}
	return 0;
}

void bubbleSort(int *array, const int length)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = i + 1; j < length; j++)
		{
			if (array[i] > array[j])
			{
				int tmp = array[j];
				array[j] = array[i];
				array[i] = tmp;
			}
		}
	}
}

int main()
{
	int min;
	int max;
	int threadsCreated = 0;
	pthread_mutex_init(&mutex, NULL);
	pthread_t threads[THREADS];

	printf("Podaj poczatek zakresu:\n");
	scanf("%d", &min);
	printf("Podaj koniec zakresu:\n");
	scanf("%d", &max);

	if (min > max || min < 0 || max < 0)
	{
		printf("Invalid input. Rerun and try again!\n");
		return 1;
	}

	primes = malloc(sizeof(int) * (max - min));

	for (int i = min; i <= max; i++)
	{

		int tmp = (i - min) % THREADS;

		pthread_create(&threads[tmp], NULL, prime, i);
		threadsCreated++;

		if (threadsCreated == THREADS)
		{
			for (int j = 0; j < THREADS; j++)
			{
				pthread_join(threads[j], NULL);
			}
			threadsCreated = 0;
		}
	}

	if (threadsCreated != 0)
	{
		for (int j = 0; j < threadsCreated; j++)
		{
			pthread_join(threads[j], NULL);
		}
	}

	if (counter != 0)
	{
		printf("Primes:\n");
		for (int i = 0; i < counter; i++)
		{
			printf("%d ", primes[i]);
		}
		printf("\n");
	}

	printf("Found %d prime number(s) in range(%d, %d).\n", counter, min, max);

	if (counter != 0)
	{
		bubbleSort(primes, counter);
		printf("Primes sorted:\n");
		for (int i = 0; i < counter; i++)
		{
			printf("%d ", primes[i]);
		}
		printf("\n");
	}
	return 0;
}