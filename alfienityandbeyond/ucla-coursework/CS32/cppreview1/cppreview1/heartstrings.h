#ifndef HEARTSTRINGS_INCLUDED
#define HEARTSTRINGS_INCLUDED
#include <string>

using std::string;

class Heartstrings {
public:
	Heartstrings(string name);
	~Heartstrings();
	void reverse();
	bool anagram(string s1) const;
	string getHeartstring() const;
	void setHeartstring(string nstr);
private:
	string str;
};

#endif // HEARTSTRINGS_INCLUDED