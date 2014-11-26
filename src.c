#include <wiringPi.h>
#include <stdio.h>

int counter = 0;
int counter_stop = 10;

void clock_interrupt(void)
{
	printf("ISR\n");
	++counter;
}

int main(void)
{
	FILE *f = fopen("out", "w");

	wiringPiSetup();
	pinMode(0, INPUT);
	pullUpDnControl(0, PUD_DOWN);
	wiringPiISR(0, INT_EDGE_FALLING, clock_interrupt);

	int temp = 0;
	int i;

	while(counter < counter_stop)
	{
		temp = digitalRead(0); 
		fprintf(f, "%d", temp);
		delay(500);
	}

	fclose(f);

	return 0;
}
