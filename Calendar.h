#include <iostream>
#include <string.h>

#pragma once //Cnnct 1 times

class Calendar {

public:

	int day, month, year;
	std::string format = "2D2M4Y-";

	//basic functions
	//

	bool isYearLeap();
	int getMonthDaysCount();
	bool isDateValid();
	void setFormat(std::string dateFormat);
	int getDaysToStartYear();
	int getDaysToEndYear();
	int getDifBetweenDate(Calendar date);
	int getWeekDay();

	Calendar incremDays(int days);
	Calendar decremDays(int days);

	static bool isYearLeap(int yearNum);
	static int getMonthDaysCount(int monthNum, int yearNum);
	static bool isDateValid(int d, int m, int y);
	static bool isFormatValid(std::string dateFormat);
	static int getDaysToStartYear(int d, int m, int y);
	static int getDaysToEndYear(int d, int m, int y);
	static int getDifBetweenDates(int d, int m, int y, Calendar date);
	static int getWeekDay(int d, int m, int y);

	static int getMonthDaysCount(Calendar date);
	static bool isDateValid(Calendar date);
	static int getDaysToStartYear(Calendar date);
	static int getDaysToEndYear(Calendar date);
	static int getDifBetweenDates(Calendar date1, Calendar date2);
	static int getWeekDay(Calendar date);

	static Calendar getGreaterDate(Calendar date1, Calendar date2);
	static Calendar getLowerDate(Calendar date1, Calendar date2);
	static Calendar incremDays(Calendar date, int days);
	static Calendar decremDays(Calendar date, int days);

	static std::string getStringDate(Calendar date);

	static std::string toStrPartOfDate(Calendar date, int part, int size);


	//construct
	//
	Calendar(std::string date);
	Calendar(int dayNum, int monthNum, int yearNum);

	
	//operator
	//
	operator std::string();


	//exception class
	class Exception: public std::exception {

	public:

		std::string errorInfo;

		Exception(std::string info) {
			errorInfo = "Calendar Error: " + info;
		}

		virtual const char* what() const throw() {
			return errorInfo.c_str();
		}
	};
};

std::istream& operator >> (std::istream& is, Calendar& date);
std::ostream& operator << (std::ostream& os, Calendar& date);

Calendar operator + (Calendar& date, int days);
Calendar operator - (Calendar& date, int days);
int operator - (Calendar& date1, Calendar& date2);