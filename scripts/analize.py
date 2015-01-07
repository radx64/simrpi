ATR_CYCLES = 372


def main():
	datafile = open('data.txt', 'r')
	decoded = ""
	lastbit = '0'
	bit = '0'
	counter = 1

	while 1:
		datafile.seek(1,1)
		lastbit = bit
		readObject = datafile.read(1)
		if not readObject:
			break

		bit = readObject
		counter += 1

		if lastbit != bit:
			counter = 1

		if (counter % ATR_CYCLES/2 == 0) and not (counter % ATR_CYCLES == 0) :
			decoded += bit

	print decoded


if __name__ == '__main__':
	main()


"""
      *    *    *    *    *    *     
	1111100000111110000000000000000
"""
