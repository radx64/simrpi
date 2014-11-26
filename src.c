#include <wiringPi.h>
#include <stdio.h>

int counter = 0;
int counter_stop = 1000;
int data;

FILE *f = 0;

void clock_interrupt(void)
{
	data = digitalRead(1);
	fprintf(f, "%d", data);
	++counter;
}

int main(void)
{
	f = fopen("out", "w");

	wiringPiSetup();
	pinMode(0, INPUT);
	pinMode(1, INPUT);
	wiringPiISR(0, INT_EDGE_FALLING, clock_interrupt);

	int temp = 0;
	int i;

	while(counter < counter_stop){}

	fclose(f);

	return 0;
}
