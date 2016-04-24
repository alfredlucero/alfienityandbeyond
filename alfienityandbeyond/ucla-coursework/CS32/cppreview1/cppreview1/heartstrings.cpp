#include "heartstrings.h";
#include <string>;
#include <algorithm>;
#include <iostream>;

Heartstrings::Heartstrings(string name) {
	str = name;
}

Heartstrings::~Heartstrings() {}

void Heartstrings::reverse() {
	int revIndex = str.size() - 1;
	for (int index = 0; index < revIndex; index++){
		char front = str[index];
		char toReverse = str[revIndex];
		str[index] = toReverse;
		str[revIndex] = front;
		revIndex--;
	}
}

bool Heartstrings::anagram(string s1) const {
	string temp = str;
	sort(temp.begin(), temp.end());
	sort(s1.begin(), s1.end());
	std::cout << s1 << " " << temp << std::endl;
	return (s1 == temp);
}

string Heartstrings::getHeartstring() const {
	return str;
}

void Heartstrings::setHeartstring(string nstr) {
	str = nstr;
}