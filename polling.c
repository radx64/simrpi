#include <wiringPi.h>
#include <stdio.h>

#define maxCounter 40000

int counter = 0;
int data[maxCounter];
int clock[maxCounter];

FILE *data_fd = 0;
FILE *clock_fd = 0;

void saveDataToFile(void)
{
	data_fd = fopen("data.txt", "w");
	clock_fd = fopen("clock.txt", "w");
	
	int i;
	for(i = 0; i<maxCounter;++i)
	{
		fprintf(data_fd, "%d\n", data[i]);
		fprintf(clock_fd, "%d\n", clock[i]);
	}
	
	fclose(data_fd);
	fclose(clock_fd);
}

int main(void)
{
	wiringPiSetup();
	pinMode(0, INPUT);
	pinMode(1, INPUT);

	while(counter < maxCounter)
	{
		data[counter] = digitalRead(0);
		clock[counter] = digitalRead(1);
		printf("%d\n", counter);
		counter++;
	}

	saveDataToFile();

	return 0;
}
