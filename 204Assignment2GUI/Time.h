#pragma once
#include <iostream>
using namespace std;

class Time {

private:
	int hours; 
	int minutes; 
	int seconds;
	

public:
	Time();
	Time(int hours, int minutes, int seconds);
	Time(const Time &obj);
	void setTime(int hours, int minutes, int seconds);
	friend ostream& operator<<(ostream& out, const Time& obj);
	friend istream& operator>>(istream& in, Time& obj);
	bool operator == (const Time &obj);
	bool operator < (const Time &obj); 
	Time operator++(int);
	Time operator--(int);
	~Time();
	bool aORp; // am or pm : true for am , false for pm
	bool _12OR24; // format : true for 12 hours and false for 24
	void to24();
	void to12();
	int getHour();
	int getMin();
	int getSec();

	void addTime();

};

