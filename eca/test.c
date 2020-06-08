#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <sys/time.h>

void generateRandom(int *array, int size)
{
	srand(time(NULL));
	for (int i = 0; i < size; i++)
		array[i] = rand() % 3;
}

void printArray_1(int *array, int size)
{
	for (int i = 0; i < size; i++) {
		printf("%c", ((array[i] == 1) ? ' ' : '#'));
	}
	printf("\n");
}

void printArray0(int *array, int size)
{
	char *buffer = calloc(sizeof(char), (size+1));
	char character = ' ';

	for (int i = 0; i < size; i++) {
		if (array[i] == 1) {
			character = '#';
		} else {
			character = ' ';
		}
		buffer[i] = character;
	}

	printf("%s\n", buffer);
	free(buffer);
}

void printArray1(int *array, int size)
{
	char *buffer = calloc(sizeof(char), (size+1));

	for (int i = 0; i < size; i++) {
		char character = ' ';
		if (array[i] == 1)
			character = '#';
		buffer[i] = character;
	}

	printf("%s\n", buffer);
	free(buffer);
}

void printArray2(int *array, int size)
{
	char *buffer = calloc(sizeof(char), (size+1));

	for (int i = 0; i < size; i++) {
		char character = (array[i] == 1) ? ' ' : '#';
		buffer[i] = character;
	}

	printf("%s\n", buffer);
	free(buffer);
}

void printArray3(int *array, int size)
{
	char *buffer = calloc(sizeof(char), (size+1));

	for (int i = 0; i < size; i++) {
		buffer[i] = (array[i] == 1) ? ' ' : '#';
	}

	printf("%s\n", buffer);
	free(buffer);
}

void benchmark(int method, int *array, int iter, int size)
{
	struct timeval tv1, tv2;

	switch(method) {
	case -1:
		gettimeofday(&tv1, NULL);
		for (int i = 0; i < iter; i++) {
			printArray_1(array, size);
		}
		gettimeofday(&tv2, NULL);
		printf("Method -1: %f\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
		break;
	case 0:
		gettimeofday(&tv1, NULL);
		for (int i = 0; i < iter; i++) {
			printArray0(array, size);
		}
		gettimeofday(&tv2, NULL);
		printf("Method  0: %f\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
		break;
	case 1:
		gettimeofday(&tv1, NULL);
		for (int i = 0; i < iter; i++) {
			printArray1(array, size);
		}
		gettimeofday(&tv2, NULL);
		printf("Method  1: %f\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
		break;
	case 2:
		gettimeofday(&tv1, NULL);
		for (int i = 0; i < iter; i++) {
			printArray2(array, size);
		}
		gettimeofday(&tv2, NULL);
		printf("Method  2: %f\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
		break;
	case 3:
		gettimeofday(&tv1, NULL);
		for (int i = 0; i < iter; i++) {
			printArray3(array, size);
		}
		gettimeofday(&tv2, NULL);
		printf("Method  3: %f\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
		break;
	default:
		fprintf(stderr, "Invalid method passed\n");
	}
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		fprintf(stderr, "Usage ./a.out <size> <iter>\n");
		exit(EXIT_FAILURE);
	}

	int size = atoi(argv[1]);
	int iter = atoi(argv[2]);

	int *array = calloc(sizeof(int), size);

	generateRandom(array, size);

	for (int i = -1; i < 4; i++)
		benchmark(i, array, iter, size);

	exit(EXIT_SUCCESS);
}
