#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

#include <sys/wait.h>

#define COUNT 1000
#define PERM 0644

int main(int argc, char *argv[])
{
	int index = 0;
	time_t now;
	int value;
	pid_t C1, C2;
	char outBuffer[128];

	//seed the random number with different values at different times
	srand((unsigned)time(&now));
	//srand(10);
	//Generate random numbers that are less than 100
	value = rand() % 100;
	sprintf(outBuffer, "Parent process: my value is %d and my index is %d\n", value, index);
	printf("%s", outBuffer);

	C1 = fork();
	if (C1 < 0)
	{
		printf("Error: fork 1 failed\n");
		return -2;
	}

	if (C1 == 0)
	{
		for (index = 1; index <= COUNT; index++)
		{
			sprintf(outBuffer, "Child 1: my value is %d and my index is %d \r\n", value, index);
			printf("%s", outBuffer);
			value++;
		}
	}

	else
	{
		C2 = fork();
		if (C2 < 0)
		{
			printf("Error: fork 1 failed\n");
			return -2;
		}

		if (C2 == 0)
		{
			sleep(10);
			for (index = 1; index <= COUNT; index++)
			{
				sprintf(outBuffer, "\tChild 2: my value is %d and my index is %d \r\n", value, index);
				printf("%s", outBuffer);
				value++;
			}
		}
		else
		{
			wait(0);
			wait(0);
		}
	}


	printf("process %d terminated\n", getpid());
	return 0;
}
