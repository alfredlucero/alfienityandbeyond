class AvgLastNDigits {
public:
	AvgLastNDigits();
	~AvgLastNDigits();
	int getAverageLastNDigits() const;
	void pushAnotherDigit(int value);

private:
	int index;
	int numDigits;
	int average;
	int runningSum;
	int circArray[10];
};