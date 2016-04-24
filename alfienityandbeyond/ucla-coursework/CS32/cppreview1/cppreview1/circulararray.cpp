#include "circulararray.h";

AvgLastNDigits::AvgLastNDigits() {
	for (int i = 0; i < 10; i++)
		circArray[i] = 0;
	
	index = 0;
	numDigits = 0;
	average = 0;
	runningSum = 0;
}

AvgLastNDigits::~AvgLastNDigits() {}

int AvgLastNDigits::getAverageLastNDigits() const {	
	return average;
}

void AvgLastNDigits::pushAnotherDigit(int value) {
	// Have a circular array to continuously take in the last N digits
	circArray[index] = value;
	index = (index + 1) % 10;

	// Keep track of the running sum to maintain the average of last N digits
	if (numDigits < 10)
		numDigits++;

	runningSum += value;
	average = runningSum / numDigits;
}