#include "mmapGpio.h"
#include <stdio.h>
#include <vector>

using namespace std;

FILE *data_fd = 0;
FILE *clock_fd = 0;

void saveDataToFile(vector<char> & clock, vector<char> & data)
{
	data_fd = fopen("data.txt", "w");
	clock_fd = fopen("clock.txt", "w");
	
	int i;
	for(i = 0; i<100000;++i)
	{
		fprintf(data_fd, "%d\n", data[i]);
		fprintf(clock_fd, "%d\n", clock[i]);
	}
	
	fclose(data_fd);
	fclose(clock_fd);
}

int main(void){
	vector<char> clock;
	vector<char> data;

	mmapGpio rpiGpio; // instantiate an instance of the mmapGpio class
	rpiGpio.setPinDir(17,mmapGpio::INPUT); // set GPIO17 to input
	rpiGpio.setPinDir(18,mmapGpio::INPUT); // set GPIO4 to output

	for (int i = 0; i < 100000; ++i)
	{
		clock.push_back(rpiGpio.readPin(17));
		data.push_back(rpiGpio.readPin(18));
	}
	
	saveDataToFile(clock, data);

	/*if(rpiGpio.readPin(17) == mmapGpio::HIGH)
		printf("Button not pressed\n"); // if GPIO17 is HIGH button not pressed (due to pull-up resistor)
	else{
		printf("Button is pressed....toggling LED\n"); //else if GPIO17 is low button is pressed
	    while(rpiGpio.readPin(17) == mmapGpio::LOW ){ // repeat toggling of GPIO4 until GPIO17 goes back to HIGH i.e. button de-pressed
			rpiGpio.writePinHigh(4); // write GPIO4 pin high
			usleep(500000);
            rpiGpio.writePinLow(4); // write GPIO4 pin low
            usleep(500000);
		}
	}
    */

return 0;
}
