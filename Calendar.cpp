#include <sstream>
#include <math.h>
#include "Calendar.h"

Calendar Calendar::getGreaterDate(Calendar date1, Calendar date2) {

	if (
		(date1.year > date2.year) or
		(date1.year == date2.year and date1.month > date2.month) or
		(date1.year == date2.year and date1.month == date2.month and date1.day >= date2.day)
	) {
	
		return date1; 
	
	} else {

		return date2;
	}
}

Calendar Calendar::getLowerDate(Calendar date1, Calendar date2) {

	if (
		(date1.year < date2.year) or
		(date1.year == date2.year and date1.month < date2.month) or
		(date1.year == date2.year and date1.month == date2.month and date1.day <= date2.day)
	) {
	
		return date1; 
	
	} else {

		return date2;
	}
}

bool Calendar::isYearLeap(int yearNum) {

	return yearNum%4 == 0 and yearNum%100 != 0 or yearNum%400 == 0;
}

bool Calendar::isYearLeap() {

	return Calendar::isYearLeap(year);
}


int Calendar::getMonthDaysCount(int monthNum, int yearNum) {

	if (monthNum <= 0 or monthNum > 12) {

		std::stringstream expt;
		expt << "Invalid Date. Month " << monthNum << " doesn't exist.";
		
		throw Exception(expt.str());

		return -1;
	}

	if (monthNum == 2) {
		return 28 + isYearLeap(yearNum);
	} else {
		if (monthNum <= 7) {
			return 30 + monthNum%2;
		} else {
			return 31 - monthNum%2;
		}
	}
}

int Calendar::getMonthDaysCount() {

	return Calendar::getMonthDaysCount(month, year);
}

int Calendar::getMonthDaysCount(Calendar date) {

	return Calendar::getMonthDaysCount(date.month, date.year);
}


bool Calendar::isDateValid(int d, int m, int y) {
	
	bool mnth = (m <= 12 and m > 0);
	bool yr = (y >= 1000 and y <= 9999);
	bool dy = (d > 0 and d <= Calendar::getMonthDaysCount(m, y));

	return mnth and yr and dy;
}

bool Calendar::isDateValid() {

	return Calendar::isDateValid(day, month, year);
}

bool Calendar::isDateValid(Calendar date) {

	return Calendar::isDateValid(date.day, date.month, date.year);
}

bool Calendar::isFormatValid(std::string dateFormat) {

	if (dateFormat.length() != 7) {
		return false;
	}

	int objs[7];
	for (int i = 0; i < 7; i++) {
		objs[i] = (int) dateFormat[i] - 48;
	}

	bool n1 = (objs[0] > 0 and objs[0] <= 4);
	bool n2 = (objs[2] > 0 and objs[2] <= 4);
	bool n3 = (objs[4] > 0 and objs[4] <= 4);

	bool dif = (objs[1] != objs[3]) and (objs[1] != objs[5]) and (objs[3] != objs[5]);

	bool w1 = (objs[1] == 20 or objs[1] == 29 or objs[1] == 41);
	bool w2 = (objs[3] == 20 or objs[3] == 29 or objs[3] == 41);
	bool w3 = (objs[5] == 20 or objs[5] == 29 or objs[5] == 41);

	return dif and n1 and n2 and n3 and w1 and w2 and w3;
}

void Calendar::setFormat(std::string dateFormat) {
	if (not Calendar::isFormatValid(dateFormat)) {
		throw Exception("Invalid Format for Date. Format: \"NTNTNTS\", where N is integer (count of elements of date), T is Type of format (D - Day, M - Month, Y - Year), S - Separator of date.");
	}

	format = dateFormat;
}


int Calendar::getDaysToStartYear(int d, int m, int y) {

	int sum = 0;
	for (int i = 1; i < m; i++) {
		sum += Calendar::getMonthDaysCount(i, y);
	}
	sum += d;

	return sum;
}

int Calendar::getDaysToStartYear() {

	return Calendar::getDaysToStartYear(day, month, year);
}

int Calendar::getDaysToStartYear(Calendar date) {

	return Calendar::getDaysToStartYear(date.day, date.month, date.year);
}


int Calendar::getDaysToEndYear(int d, int m, int y) {

	return (365 + Calendar::isYearLeap(y)) - Calendar::getDaysToStartYear(d, m, y); 
}

int Calendar::getDaysToEndYear() {

	return Calendar::getDaysToEndYear(day, month, year);
}

int Calendar::getDaysToEndYear(Calendar date) {

	return Calendar::getDaysToEndYear(date.day, date.month, date.year);
}


int Calendar::getDifBetweenDates(Calendar date1, Calendar date2) {

	Calendar minDate = Calendar::getLowerDate(date1, date2);
	Calendar maxDate = Calendar::getGreaterDate(date1, date2);

	int days = 0;

	for (int i = minDate.year; i < maxDate.year; i++) {
		days += 365 + isYearLeap(i);
	}

	days += maxDate.getDaysToStartYear();
	days -= minDate.getDaysToStartYear();

	return days;

}

int Calendar::getDifBetweenDates(int d, int m, int y, Calendar date) {

	Calendar date2(d, m, y);
	return Calendar::getDifBetweenDates(date, date2);
}

int Calendar::getDifBetweenDate(Calendar date) {
	return Calendar::getDifBetweenDates(day, month, year, date);
}


int Calendar::getWeekDay(int d, int m, int y) {
	int mdif = (14 - m) / 12;
	int ydif = y - mdif;
	int nmdif = m + 12 * mdif - 2;
	int daynum = (7000 + (d + ydif + ydif / 4 - ydif / 100 + ydif / 400 + (31 * nmdif) / 12)) % 7;
	return (daynum == 0 ? 7 : daynum);
}

int Calendar::getWeekDay() {
	return Calendar::getWeekDay(day, month, year);
}

int Calendar::getWeekDay(Calendar date) {
	return date.getWeekDay();
}


Calendar Calendar::incremDays(Calendar date, int days) {

	int newdays = date.getDaysToStartYear() + days;
	
	int nmonth = 1;
	int nyear = date.year;

	while (newdays > 365+isYearLeap(nyear)) {

		newdays -= 365+isYearLeap(nyear);
		nyear++;

	}

	while (newdays > Calendar::getMonthDaysCount(nmonth, nyear)) {
		
		newdays -= Calendar::getMonthDaysCount(nmonth, nyear);
		nmonth++;

		if (nmonth > 12) {
			nmonth = 1;
			nyear++;
		}
	}

	int nday = newdays;

	return Calendar(nday, nmonth, nyear);
}

Calendar Calendar::incremDays(int days) {

	Calendar date(day, month, year);
	return Calendar::incremDays(date, days);
}


Calendar Calendar::decremDays(Calendar date, int days) {

	int newdays = date.getDaysToStartYear() - days;

	int nyear = date.year;
	while (newdays <= 0) {

		newdays += 365 + isYearLeap(nyear-1);
		nyear -= 1;

	} 

	return Calendar(1, 1, nyear).incremDays(newdays-1);
}

Calendar Calendar::decremDays(int days) {

	Calendar date(day, month, year);
	return Calendar::decremDays(date, days);
}


std::string Calendar::toStrPartOfDate(Calendar date, int part, int size) {

	std::string result;
	
	for (int i = 0; i < size; i++) {
		result += '0';
	}

	int prt = (part == 20) ? date.day : (part == 29) ? date.month : date.year;
	for (int i = size; i > 0; i--) {

		int pt = prt/pow(10, size-i);
		result[i-1] = (char) (pt % 10 + 48);
	}

	return result;
}

std::string Calendar::getStringDate(Calendar date) {

	int objs[7];
	for (int i = 0; i < 7; i++) {
		objs[i] = (int) date.format[i] - 48;
	}

	std::string result = "";

	for (int i = 0; i < 3; i++) {
		
		result += Calendar::toStrPartOfDate(date, objs[2*i + 1], objs[2*i]);
		if (i != 2) {
			result += (char) (objs[6] + 48);
		}

	}

	return result;

}


Calendar::operator std::string() {

	Calendar date(day, month, year);
	date.setFormat(format);

	return Calendar::getStringDate(date);
}

std::istream& operator >> (std::istream& is, Calendar& date) {

	char sep;
	is >> date.day >> sep >> date.month >> sep >> date.year;
	return is; 
}

std::ostream& operator << (std::ostream& os, Calendar& date) {

	os << Calendar::getStringDate(date);
	return os;
}

Calendar operator + (Calendar& date, int days) {
	return date.incremDays(days);	
}

Calendar operator - (Calendar& date, int days) {
	return date.decremDays(days);	
}

int operator - (Calendar& date1, Calendar& date2) {

	return date1.getDifBetweenDate(date2);
}

Calendar::Calendar(int dayNum, int monthNum, int yearNum) {
	if (not Calendar::isDateValid(dayNum, monthNum, yearNum)) {
		throw Exception("Invalid Date Format. This date is doesn't exist.");
	}
		
	day = dayNum;
	month = monthNum;
	year = yearNum;
}

Calendar::Calendar(std::string date) {

	int m, d, y;
	char div1, div2;
	int tmp;

	if (date.length() != 10) {
		
		throw Exception("Invalid Date Format. Require 10 characters of Date.");

	} else {

		for (int i = 0; i < 10; i++) {
			if (date[i] == ' ') {
				date[i] = '-';
			}
		}

		std::stringstream input(date);
		input >> d >> div1 >> m >> div2 >> y;

		if (d >= 1000) {
			tmp = d;
			d = m;
			m = y;
			y = tmp;
		}

		if (m >= 1000) {
			tmp = y;
			y = m;
			m = tmp;
		}

		if (m > 12) {
			tmp = d;
			d = m;
			m = tmp;
		}

		if (not Calendar::isDateValid(d, m, y)) {

			throw Exception("Invalid Date Format. Day doesn't exist.");
		}
		
		day = d;
		month = m;
		year = y;
	}
}
