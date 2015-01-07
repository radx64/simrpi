#include "mmapGpio.h"
#include <stdio.h>
#include <vector>

#define CYCLE_ETU 372
#define CHARACTER_FRAME_LONG 12

int atrData[] = {0x3B, 0x27, 0x00, 0x80, 0x65, 0xA2, 0x04, 0x01, 0x01, 0x37};

int characterFrame[CHARACTER_FRAME_LONG];

int calculateParityBit(int data)
{
	unsigned int v;  // neat hack to compute fast the parity of byte
	v = data;
	v ^= v >> 4;
	v &= 0xf;
	return (0x6996 >> v) & 1;
}

void calculateCharacterFrame(int data, int *characterFrame)
{
	characterFrame[0] = 0; 	//start
	characterFrame[1] = data & (0x01 << 7);
	characterFrame[2] = data & (0x01 << 6);
	characterFrame[3] = data & (0x01 << 5);
	characterFrame[4] = data & (0x01 << 4);
	characterFrame[5] = data & (0x01 << 3);
	characterFrame[6] = data & (0x01 << 2);
	characterFrame[7] = data & (0x01 << 1);
	characterFrame[8] = data & (0x01);

	characterFrame[9] = calculateParityBit(data);
	characterFrame[10] = 1;	//pause
	characterFrame[11] = 1; //pause

}

int main(void){

	mmapGpio rpiGpio;
	rpiGpio.setPinDir(18,mmapGpio::OUTPUT);
	rpiGpio.setPinDir(17,mmapGpio::INPUT);

	for(int character=0; character<10; ++character)
	{
		calculateCharacterFrame(atrData[character], characterFrame);

		for(int bit=0; bit<CHARACTER_FRAME_LONG; ++bit)
		{
			rpiGpio.writePinState(18, characterFrame[++bit]);

			for(int cycle=0; cycle<CYCLE_ETU; ++cycle)
			{
				rpiGpio.readPin(17); //just for delay need to specify cycleETU definition
			}
		}
	}

return 0;
}
