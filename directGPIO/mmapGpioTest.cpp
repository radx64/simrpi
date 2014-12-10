#include "mmapGpio.h"
#include <stdio.h>
#include <vector>

using namespace std;

const int TICKS_TO_READ = 2000000;

FILE *data_fd = 0;
FILE *clock_fd = 0;

void saveDataToFile(vector<char> & clock, vector<char> & data)
{
	data_fd = fopen("data.txt", "w");
	clock_fd = fopen("clock.txt", "w");
	
	int i;
	for(i = 0 ; i < TICKS_TO_READ ; ++i)
	{
		fprintf(data_fd, "%d", data[i]);
		fprintf(clock_fd, "%d", clock[i]);
	}
	
	fclose(data_fd);
	fclose(clock_fd);
}

int main(void){
	vector<char> clock;
	vector<char> data;

	mmapGpio rpiGpio;
	rpiGpio.setPinDir(17,mmapGpio::INPUT);
	rpiGpio.setPinDir(18,mmapGpio::INPUT);

	for (int i = 0 ; i < TICKS_TO_READ ; ++i)
	{
		clock.push_back(rpiGpio.readPin(17));
		data.push_back(rpiGpio.readPin(18));
	}
	
	saveDataToFile(clock, data);

/*
	if(rpiGpio.readPin(17) == mmapGpio::HIGH)
		printf("Button not pressed\n");
	else
	{
		printf("Button is pressed....toggling LED\n");
		while(rpiGpio.readPin(17) == mmapGpio::LOW )
		{
			rpiGpio.writePinHigh(4);
			usleep(500000);
			rpiGpio.writePinLow(4);
			usleep(500000);
		}
	}
*/

return 0;
}
