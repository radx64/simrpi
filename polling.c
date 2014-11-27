#include <wiringPi.h>
#include <stdio.h>

#define maxCounter 1000

int counter = 0;
int counter_stop = maxCounter;
int data[maxCounter];

FILE *f = 0;

void clock_interrupt(void)
{
	data[counter] = digitalRead(0);
	printf("%d", data[counter]);
	if((counter % 16) == 0) printf("\n");
	++counter;
}

void saveDataToFile(void)
{
	int i;
	for(i = 0; i<maxCounter;++i)
	{
		fprintf(f,"%d\n", data[i]);
	}
}

int main(void)
{
	f = fopen("out", "w");

	wiringPiSetup();
	pinMode(0, INPUT);
	pinMode(1, INPUT);
	wiringPiISR(1, INT_EDGE_RISING, clock_interrupt);

	int temp = 0;
	int i;

	while(counter < counter_stop){}

	saveDataToFile();
	fclose(f);

	return 0;
}
