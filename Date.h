#pragma once
#include <iostream>
#include <string>
class Date {
private:
	bool leapyear;
	int day;
	int month;
	int year;
	bool leap(int y)const {
		return ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0);
	};
	int maxday()const {
		int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		if (leapyear)days[1] = 29;
		return days[month - 1];
	};
public:
	Date(int d, int m, int y) {
		this->year = y;
		this->leapyear = leap(y);
		if (m < 0 || m>12) this->month = 1;
		else this->month = m;
		if (d > maxday() || d < 0) this->day = 1;
		else this->day = d;
	}
	void setDay(int d) {
		if (d > maxday() || d < 0) this->day = 1;
		else this->day = d;
	}
	void setMonth(int m) {
		if (m < 0 || m>12) this->month = 1;
		else this->month = m;
	}
	void setYear(int y) {
		this->year = y;
		this->leapyear = leap(y);
	}
	int getDay()const {
		return this->day;
	}
	int getMonth()const {
		return this->month;
	}
	int getYear()const {
		return this->year;
	}
	bool getLeap()const {
		return this->leapyear;
	}
	Date& operator+=(int d) {
		if (day + d > maxday()) {
			d -= maxday() - day;
			if (++month > 12) {
				month = 1;
				year++;
			}
			while (d / maxday()) {
				if (++month > 12) {
					month = 1;
					year++;
				}
				d -= maxday();
			}
			day = d;
		}
		else day += d;
		return *this;
	};
	Date& operator-=(int d) {
		if (day - d < 1) {
			d -= day;
			if (--month == 0) {
				month = 12;
				year--;
			}
			while (d / maxday()) {
				d -= maxday();
				if (--month == 0) {
					month = 12;
					year--;
				}
			}
			day = maxday() - d;
		}
		else day -= d;
		return *this;
	};
	bool operator==(Date& dt)const {
		return this->day == dt.day && this->month == dt.month && this->year == dt.year;
	};
	bool operator!=(Date& dt)const {
		return !(*this == dt);
	}
	bool operator>(Date& dt)const {
		return (this->year > dt.year ||
			(this->year == dt.year && this->month > dt.month) ||
			(this->year == dt.year && this->month == dt.month && this->day > dt.day));
	}
	bool operator<(Date& dt)const {
		return (this->year < dt.year ||
			(this->year == dt.year && this->month < dt.month) ||
			(this->year == dt.year && this->month == dt.month && this->day < dt.day));
	}
	friend int operator-(Date& d1, Date& d2);
	friend std::ostream& operator<<(std::ostream&, const Date&);
};

std::ostream& operator<<(std::ostream& os, const Date& dt) {
	std::string m[] = { "January","February","March","April","May","June","July","August","September","October","November","December" };
	os << dt.day << " " << m[dt.month - 1] << " " << dt.year;
	return os;
}
int operator-(Date& d1, Date& d2) {
	int a, y, m, jdn1, jdn2;
	a = (14 - d1.getMonth()) / 12;
	y = d1.getYear() + 4800 - a;
	m = d1.getMonth() + 12 * a - 3;
	jdn1 = d1.getDay() + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
	a = (14 - d2.getMonth()) / 12;
	y = d2.getYear() + 4800 - a;
	m = d2.getMonth() + 12 * a - 3;
	jdn2 = d2.getDay() + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
	return jdn1 - jdn2;
}
