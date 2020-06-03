#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int *generateRule(int *array, int rule) {
	for (int i = 0; i < 8; i++) {
		if (rule % 2 == 0) {
			array[i] = 0;
		} else {
			array[i] = 1;
		}
		rule = rule / 2;
	}
	return array;
}

void printArray(int* array, int size) {
	char *buffer = calloc(sizeof(char),(size+1)*2);
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

int checkNeighbor(int *array, int *rule, int size, int index) {
	int sum = 0;
	if (index == 0) {
		sum += array[size-1]*2*2;
		sum += array[0]*2;
		sum += array[1];
	} else if (index == size-1) {
		sum += array[index-1]*2*2;
		sum += array[index]*2;
		sum += array[0];
	} else {
		sum += array[index-1]*2*2;
		sum += array[index]*2;
		sum += array[index+1];
	}

	return rule[sum];
}

int *updateArray(int *array, int *rule, int size) {
	int *temp = malloc(sizeof(int) * size);

	if (temp == NULL) {
		perror("Error Allocating Space for Buffer Array\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < size; i++) {
		temp[i] = checkNeighbor(array, rule, size, i);
	}

	free(array);
	return temp;
}

int main(int argc, char *argv[])
{
	if (argc != 4) {
		printf("Usage: ./a.out <size> <iterations> <rule: 0-255>\n");
		exit(EXIT_FAILURE);
	}

	int* rule = malloc(8 * sizeof(int));

	if (rule == NULL) {
		perror("Error Malocating Rule Array\n");
		exit(EXIT_FAILURE);
	}

	rule = generateRule(rule, atoi(argv[3]));

	int size = atoi(argv[1]);
	int* arr = malloc(sizeof(int) * size);

	if (arr == NULL) {
		perror("Error Allocating Automata Array\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < size; i++) {
		arr[i] = 0;
	}
	
	arr[size/2+1] = 1;

	printArray(arr, size);
	for (int i = 0; i < atoi(argv[2]); i++) {
		printArray(arr, size);
		arr = updateArray(arr, rule, size);
	}

	free(rule);
	free(arr);
	exit(EXIT_SUCCESS);
}
