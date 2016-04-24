#include "circulararray.h";
#include "heartstrings.h";
#include "intlist.h";
#include <string>;
#include <iostream>;

using namespace std;

int main() {
	/*
	string visitorName;
	cout << "The return of Alfred Lucero to the world of C++" << endl;
	cout << "Who approaches from afar? ";
	getline(cin, visitorName);
	cout << visitorName << " decides to venture with Alfred Lucero" << endl;

	AvgLastNDigits avgNDigits;
	cout << "Let's have some fun and keep track of the average of the last N digits inputted" << endl;
	cout << "Input a negative number to exit out of the continuous stream of integers" << endl;
	while(true) {
		int pushDigit = 0;
		cout << "Enter an integer: ";
		cin >> pushDigit;

		if (pushDigit < 0)
			break;

		avgNDigits.pushAnotherDigit(pushDigit);
		cout << "Here is the running average " << avgNDigits.getAverageLastNDigits() << endl;
	}
	cout << endl << endl;
	
	cin.ignore(10000, '\n');

	string strToReverse;
	cout << "Now let's pull your heartstrings!" << endl;
	cout << "Give me a string to reverse ";
	getline(cin, strToReverse);
	
	Heartstrings heartstrings(strToReverse);
	heartstrings.reverse();
	cout << "The string reversed is now " << heartstrings.getHeartstring() << endl;

	string nstr;
	cout << endl << endl;
	cout << "Now let's reset the string so please input one ";
	cin >> nstr;
	heartstrings.setHeartstring(nstr);
	cout << "Give me another string and I will tell you if it is an anagram of the preceding one" << endl;
	cout << "Input another string: ";
	string cmpStr;
	cin >> cmpStr;
	bool isAnagram = heartstrings.anagram(cmpStr);
	if (isAnagram)
		cout << "The string you compared " << cmpStr << " is an anagram of the original string" << endl;
	else
		cout << "The string you compared " << cmpStr << " is not an anagram of the original string" << endl;
	*/

	IntList intlist;
	intlist.insertInt(10);
	intlist.insertInt(5);
	intlist.insertInt(12);
	intlist.printIntList();
	cout << "The sum of the integer list is: " <<  intlist.getSumIntList() << endl;
	intlist.deleteInt(5);
	intlist.printIntList();
	cout << endl;
	intlist.insertInt(12);
	intlist.insertInt(17);
	intlist.printIntList();
	cout << "The sum of the integer list is: " << intlist.getSumIntList() << endl;
	

}
