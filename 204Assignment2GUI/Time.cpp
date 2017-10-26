#include "stdafx.h"
#include "Time.h"




Time::Time() {
	aORp = true;
	_12OR24 = true;
	hours = 0; 
	minutes = 0;
	seconds = 0;
}

Time::Time(int hours, int minutes, int seconds) {
	this->hours = hours;
	this->minutes = minutes;
	this->seconds = seconds;
}

Time::Time(const Time & obj) {
	this->hours = obj.hours;
	this->minutes = obj.minutes;
	this->seconds = obj.seconds;
}

void Time::setTime(int hours, int minutes, int seconds) {
	this->hours = hours;
	this->minutes = minutes;
	this->seconds = seconds;
}

bool Time::operator==(const Time & obj) {
	if (hours == obj.hours && minutes == obj.minutes && seconds == obj.seconds)
		return true;
	else
		return false;
}

bool Time::operator<(const Time & obj)
{
	if (hours < obj.hours)
		return true;
	else if (hours > obj.hours)
		return false;
	else
		if (minutes < obj.minutes)
			return true;
		else if (minutes > obj.minutes)
			return false;
		else
			if (seconds < obj.seconds)
				return true;
			else if (seconds < obj.seconds)
				return false;
			else
				return false; // at this point all equal
}

Time Time::operator++(int) {
	seconds++;
	if (seconds >= 60) {
		++minutes;
		seconds -= 60;
		if (minutes >= 60) {
			minutes -= 60;
			if (_12OR24 == true) {
				// if 12 hours 
				if (hours == 12) {
					hours = 1;
				} else if (hours == 11) {
					hours++;
					aORp ^= 1;
				} else {
					hours++;
				}
			} else {
				hours++;
				// if 24 hours 
				if (hours >= 24) {
					hours -= 24;
				}
			}
		}
	}
	return *this;
}

Time Time::operator--(int) {
	--seconds;
	if (seconds < 0) {
		--minutes;
		seconds += 60;
		if (minutes < 0) {
			minutes += 60;
			if (_12OR24 == true) {
				// if 12 hours 
				if (hours == 12) {
					hours--;
					aORp ^= 1;
				} else if (hours == 1) {
					hours = 12;
					aORp ^= 1;	
				} else {
					hours--;
				}
			}
			else {
				// if 24 hours 
				if (hours == 0) {
					hours = 23;
				} else {
					hours--;
				}
			}
		}
	}
	return *this;
}

Time::~Time()
{
}

void Time::to24() {

	if (aORp == true && hours == 12) {
		this->hours = 0;
	} else if (aORp == false && hours != 12) {
		this->hours += 12;
	}
}

void Time::to12() {
	if (hours < 12 && hours != 0) {
		aORp = true; 
	} else if (hours > 12) {
		aORp = false;
		hours -= 12;
	} else if (hours == 12){
		aORp = false;
	} else if (hours == 0){
		hours = 12;
		aORp = true;
	}
}

int Time::getHour()
{
	return hours;
}

int Time::getMin()
{
	return minutes;
}

int Time::getSec()
{
	return seconds;
}

void Time::addTime()
{
	seconds++;
}

ostream & operator<<(ostream & out, const Time & obj)
{
	out << "Hours : " << obj.hours << " Mins : " << obj.minutes << " Seconds : " << obj.seconds << endl;
	return out;
}

istream &operator >> (istream &in, Time & obj) {
	in >> obj.hours >> obj.minutes >> obj.seconds;
	return in;
}
