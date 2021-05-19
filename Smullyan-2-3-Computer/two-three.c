#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG
#undef DEBUG
#ifdef DEBUG
#define dprintf(fmt...)    printf(fmt)
#else
#define dprintf(fmt...)
#endif

long int getlen(long int input)
{
	int length = 0;
	if (input < 10)
		return 1;

	while (input) {
		input = input / 10;
		length++;
	}

	return length;
	
}

char *stringify(long int input)
{
	long int length = getlen(input);
	char *ret;
	long int count = length;

	ret = malloc((length + 1)*sizeof(char));

	if (!ret)
		return NULL;

	ret[length] = '\0';
	ret[0] = '0';
	count = length;

	while (input) {
		char c = '0' + (input  % 10);
		ret[--count] = c;
		input = input / 10;
	}

	return ret;
}

int allowed(char *input)
{
	int length = strlen(input);
	int i;

	if (length < 2)
		return 0;

	if (input[0] != '2' && input[0] != '3')
		return 0;

	for (i = 0; i < length; i++) {
		if (input[i] == '0')
			return 0;
	}

	return 1;
}

char *compute(char *input)
{
	if (allowed(input) == 0)
		return NULL;

	if (input[0] == '3') {
		char *next_input = &input[1];
		char *y = compute(next_input);
		int length;
		char *ret;
		if (!y)
			return y;
		length = strlen(y);
		
		ret = malloc((2*length + 2)*sizeof(char));
		if (!ret)
			return NULL;
		strncpy(ret, y, length + 1);
		ret[length] = '2';
		strncpy(&ret[length + 1], y, length + 1);
		free(y);
		return ret;
	}


	if (input[0] == '2') {
		char *next_input = &input[1];
		int length = strlen(next_input);
		char *ret = malloc((length + 1)*sizeof(char));
		strncpy(ret, next_input, length + 1);
		return ret;
	}

	return NULL;
}

#define MAX_DESCENDENTS 500
#define MAX_LENGTH 100000
char *descendents[MAX_DESCENDENTS];

void compute_generations(unsigned long val)
{
	long int k;
	int generation = 0;
	int repeats = 0;
	int too_long = 0;

	char *cur, *next;

	cur = stringify(val);

	do {
		int j;
		for (j = 0; j < generation; j++)
			if (strcmp(descendents[j], cur) == 0)
				repeats = 1;

		descendents[generation++] = cur;
		if (strlen(cur) > MAX_LENGTH)
			too_long  = 1;

		if (repeats || too_long || generation >= MAX_DESCENDENTS)
			break;
		
		cur = compute(cur);
	} while (cur != NULL);

	if (generation == 1)
		free(descendents[0]);
	else if (generation > 1) {
		for (k = 0; k < generation; k++) {
			if (k == 0)
				printf("======================================\n");

			printf("[%3d] : %s\n", k, descendents[k]);
			free(descendents[k]);
		}

		printf("%s %s %s\n",
			repeats ? "[REPEATS]" : "",
			too_long ? "[TOO LONG]" : "",
			generation >= MAX_DESCENDENTS ? "[TOO MANY DESCENDENTS]" : "");
	}
}

int main(void)
{
	long int i;
	for (i = 0; i < 100000; i++)
		compute_generations(i);

	return 0;
}
