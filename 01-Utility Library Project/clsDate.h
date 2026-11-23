#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include "clsDate.h"
using namespace std;


class clsDate
{
	vector<int> SplitString(string Date) {
		vector<int> DateDigits;
		size_t pos = 0;
		string sWord = "";
		string delimiter = "/";

		while ((pos = Date.find(delimiter)) != string::npos) {
			sWord = Date.substr(0, pos);
			if (sWord != "") {
				DateDigits.push_back(stoi(sWord));
			}
			Date.erase(0, pos + delimiter.length());
		}

		if (Date != "") {
			DateDigits.push_back(stoi(Date));
		}

		return DateDigits;
	}



private:
	int _Day = 1;
	int _Month = 1;
	int _Year = 1900;

public:
	static bool IsLeapYear(int Year) {
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}
	bool IsLeapYear() {
		return IsLeapYear(_Year);
	}
	static short GetNumberOfDaysInMonth(short Year, short Month) {

		if (Month < 1 || Month > 12) {
			return 0;
		}

		int DaysInMonth[13] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : DaysInMonth[Month - 1];


	}

	short GetNumberOfDaysInMonth() {
		return GetNumberOfDaysInMonth(_Year, _Month);
	}

	static clsDate SetDateFromDays(short Year, short Days) {
		clsDate Date;
		Date._Year = Year;
		Date._Month = 1;

		while (Days > GetNumberOfDaysInMonth(Year, Date._Month)) {

			Days -= GetNumberOfDaysInMonth(Year, Date._Month);
			Date._Month++;
		}
		Date._Day = Days;

		return Date;

	}

	clsDate() {

		time_t now = time(nullptr);
		tm localTime{};
		localtime_s(&localTime, &now);
		char buffer[100];
		
		
	}
	clsDate(string Date) {
		vector<int> DateDigits = SplitString(Date);
		_Day = DateDigits[0];
		_Month = DateDigits[1];
		_Year = DateDigits[2];
	}
	clsDate(int Day, int Month, int Year) {
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	clsDate(short Year, short Days) {
		clsDate Date = SetDateFromDays(Year, Days);
		_Day = Date._Day;
		_Month = Date._Month;
		_Year = Date._Year;

	}
	void SetDate(int Day, int Month, int Year) {
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	static string GetSystemDateTimeString()
	{
		//system datetime string
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute)
			+ ":" + to_string(Second));

	}

	static string GetMonthName(short MonthNum) {
		string MonthNames[13] = { "", "January", "February", "March", "April",
								 "May", "June", "July", "August", "September",
								 "October", "November", "December" };

		return MonthNames[MonthNum];
	}
	string GetMonthName() {
		return GetMonthName(_Month);
	}
	static short GetDayOrder(short Year, short Month, short Day) {

		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;
		// Gregorian:
		//0:sun, 1:Mon, 2:Tue...etc
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}
	short GetDayOrder() {
		return GetDayOrder(_Year, _Month, _Day);
	}
	static string GetWeekDayName(short DayOrder) {

		string DayNames[7] = { "Sunday", "Monday", "Tuesday", "Wednesday",
							 "Thursday", "Friday", "Saturday" };
		return DayNames[DayOrder];
	}
	string GetWeekDayName() {
		return GetWeekDayName(GetDayOrder());
	}
	static void PrintMonthCalendar(short Year, short Month) {

		short Current = GetDayOrder(Year, Month, 1);
		short NumberOfDays = GetNumberOfDaysInMonth(Year, Month);

		cout << "-------------------------" << GetMonthName(Month) << "------------------------" << endl;
		int i = 0;
		for (i = 0; i < Current; i++) {
			printf(" ");
		}
		printf("Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
		for (short Day = 1; Day <= NumberOfDays; Day++) {
			printf("%5d", Day);

			if (++i == 7) {
				i = 0;
				cout << endl;
			}
		}
		printf("\n _________________________________\n");
	}
	void PrintMonthCalendar() {
		PrintMonthCalendar(_Year, _Month);
	}
	static void PrintYearCalendar(short Year) {
		printf("\n  _________________________________\n");
		printf("\n       Calendar - %d\n", Year);
		printf("  _________________________________\n");

		for (short Month = 1; Month <= 12; Month++) {
			PrintMonthCalendar(Year, Month);
		}
	}
	void PrintYearCalendar() {
		PrintYearCalendar(_Year);
	}
	static short CountDaysFromYearStartToDate(short Year, short Month, short Day) {

		short Sum = 0;

		for (short i = 1; i <= Month - 1; i++) {
			Sum += GetNumberOfDaysInMonth(Year, i);
		}
		Sum = Sum + Day;
		return Sum;

	}

	short CountDaysFromYearStartToDate() {
		return CountDaysFromYearStartToDate(_Year, _Month, _Day);
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year < Date2._Year) ? true : ((Date1._Year ==
			Date2._Year) ? (Date1._Month < Date2._Month ? true : (Date1._Month ==
				Date2._Month ? Date1._Day < Date2._Day : false)) : false);
	}
	bool IsDate1BeforeDate2(clsDate Date2) {
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsTwoDatesEqual(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year == Date2._Year) && (Date1._Month == Date2._Month) && (Date1._Day == Date2._Day);

	}
	bool IsTwoDatesEqual(clsDate Date2) {

		return IsTwoDatesEqual(*this, Date2);
	}
	static bool IsMonthLastMonthInTheYear(short Month) {
		return Month == 12;
	}

	bool IsMonthLastMonthInTheYear() {
		return IsMonthLastMonthInTheYear(_Month);
	}

	static bool IsDayLastDayInYear(short Day, short Month, short Year) {
		if (Month < 1 || Month > 12) {
			return false;
		}
		return Month == 12 && Day == GetNumberOfDaysInMonth(Year, 12);
	}
	bool IsDayLastDayInYear() {
		return IsDayLastDayInYear(_Day, _Month, _Year);
	}
	static bool IsDayLastDayInMonth(short Day, short Month, short Year) {
		if (Month < 1 || Month > 12) {
			return false;
		}
		return Day == GetNumberOfDaysInMonth(Year, Month);
	}
	bool IsDayLastDayInMonth() {
		return IsDayLastDayInMonth(_Day, _Month, _Year);
	}

	static string IncreaseDateByOneDay(clsDate Date) {
		if (IsDayLastDayInMonth(Date._Day, Date._Month, Date._Year) && IsMonthLastMonthInTheYear(Date._Month)) {
			Date._Day = 1;
			Date._Month = 1;
			Date._Year++;
		}
		else if (IsDayLastDayInMonth(Date._Day, Date._Month, Date._Year) && !IsMonthLastMonthInTheYear(Date._Month)) {

			Date._Day = 1;
			Date._Month++;
		}
		else {
			Date._Day++;
		}

		return to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
	}
	string IncreaseDateByOneDay() {
		return IncreaseDateByOneDay(*this);
	}
	static short CountDaysFromYearStartToDate(clsDate Date) {

		short Sum = 0;

		for (short i = 1; i <= Date._Month - 1; i++) {
			Sum += GetNumberOfDaysInMonth(Date._Year, i);
		}
		Sum = Sum + Date._Day;
		return Sum;

	}
	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;
		TempDate._Year = Date1._Year;
		TempDate._Month = Date1._Month;
		TempDate._Day = Date1._Day;
		Date1._Year = Date2._Year;
		Date1._Month = Date2._Month;
		Date1._Day = Date2._Day;
		Date2._Year = TempDate._Year;
		Date2._Month = TempDate._Month;
		Date2._Day = TempDate._Day;
	}
	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short SwapFlagValue = 1;
		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}
		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}
		return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;
	}
	int GetDifferenceBetweenTwoDates(clsDate Date, bool IncludeEndDay = false) {
		return GetDifferenceInDays(*this, Date);
	}
	static clsDate IncreaseDateByXDays(clsDate Date, short Days)
	{
		for (short i = 0; i < Days; i++)
			Date = IncreaseDateByOneDay(Date);
		return Date;
	}
	clsDate IncreaseDateByXDays(short Days) {
		return IncreaseDateByXDays(*this, Days);
	}
	static clsDate IncreaseDateByOneWeek(clsDate Date)
	{
		return IncreaseDateByXDays(Date, 7);
	}
	clsDate IncreaseDateByOneWeek() {
		return IncreaseDateByOneWeek(*this);
	}
	static clsDate IncreaseDateByXWeek(clsDate Date, short Weeks)
	{
		for (short i = 0; i < Weeks; i++)
			Date = IncreaseDateByOneWeek(Date);
		return Date;
	}
	clsDate IncreaseDateByXWeek(short Weeks) {
		return IncreaseDateByXWeek(*this, Weeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate Date)
	{
		if (Date._Month == 12)
		{
			Date._Month = 1;
			Date._Year++;
		}
		else
		{
			Date._Month++;
		}

		short NumberOfDaysInCurrentMonth = GetNumberOfDaysInMonth(Date._Month, Date._Year);
		if (Date._Day > NumberOfDaysInCurrentMonth)
		{
			Date._Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}
	clsDate IncreaseDateByOneMonth() {
		return IncreaseDateByOneMonth(*this);
	}
	static clsDate IncreaseDateByXMonth(clsDate Date, short Months)
	{
		for (short i = 0; i < Months; i++)
			Date = IncreaseDateByOneMonth(Date);
		return Date;
	}
	clsDate IncreaseDateByXMonth(short Months) {
		return IncreaseDateByXMonth(*this, Months);
	}

	static clsDate IncreaseDateByOneYear(clsDate Date)
	{
		return IncreaseDateByXMonth(Date, 12);
	}
	clsDate IncreaseDateByOneYear() {
		return IncreaseDateByOneYear(*this);
	}
	static clsDate IncreaseDateByXYears(clsDate Date, short Years)
	{
		for (short i = 0; i < Years; i++)
			Date = IncreaseDateByOneYear(Date);
		return Date;
	}
	clsDate IncreaseDateByXYears(short Years) {
		return IncreaseDateByXYears(*this, Years);
	}

	static clsDate IncreaseDateByXYearsFaster(clsDate Date, short Years)
	{
		return IncreaseDateByXMonth(Date, Years * 12);
	}
	clsDate IncreaseDateByXYearsFaster(short Years) {
		return IncreaseDateByXYearsFaster(*this, Years);
	}

	static clsDate IncreaseDateByADecade(clsDate Date)
	{
		return IncreaseDateByXYears(Date, 10);
	}
	clsDate IncreaseDateByADecade() {
		return IncreaseDateByADecade(*this);
	}
	static clsDate IncreaseDateByXDecades(clsDate Date, short Decades)
	{
		for (short i = 0; i < Decades; i++)
			Date = IncreaseDateByADecade(Date);
		return Date;
	}
	clsDate IncreaseDateByXDecades(short Decades) {
		return IncreaseDateByXDecades(*this, Decades);
	}
	static clsDate IncreaseDateByOneCentury(clsDate Date)
	{
		return IncreaseDateByXYears(Date, 100);
	}
	clsDate IncreaseDateByOneCentury() {
		return IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByXCenturies(clsDate Date, short Centuries)
	{
		for (short i = 0; i < Centuries; i++)
			Date = IncreaseDateByOneCentury(Date);
		return Date;
	}
	clsDate IncreaseDateByXCenturies(short Centuries) {
		return IncreaseDateByXCenturies(*this, Centuries);
	}
	static clsDate IncreaseDateByOneMillennium(clsDate Date)
	{
		return IncreaseDateByXYears(Date, 1000);
	}
	clsDate IncreaseDateByOneMillennium() {
		return IncreaseDateByOneMillennium(*this);
	}
	static bool IsFirstDayInMonth(clsDate Date)
	{
		return (Date._Day == 1);
	}
	bool IsFirstDayInMonth() {
		return IsFirstDayInMonth(*this);
	}

	static bool IsFirstMonthInYear(clsDate Date)
	{
		return (Date._Month == 1);
	}
	bool IsFirstMonthInYear() {
		return IsFirstMonthInYear(*this);
	}
	static clsDate DecreaseDateByOneDay(clsDate Date)
	{
		if (IsFirstDayInMonth(Date))
		{
			if (IsFirstMonthInYear(Date))
			{
				Date._Month = 12;
				Date._Day = 31;
				Date._Year--;
			}
			else
			{
				Date._Day = GetNumberOfDaysInMonth(Date._Month - 1, Date._Year);
				Date._Month--;
			}
		}
		else
		{
			Date._Day--;
		}
		return Date;
	}
	clsDate DecreaseDateByOneDay() {
		return DecreaseDateByOneDay(*this);
	}


	static clsDate DecreaseDateByXDays(clsDate Date, short Days)
	{
		for (short i = 0; i < Days; i++)
			Date = DecreaseDateByOneDay(Date);
		return Date;
	}
	clsDate DecreaseDateByXDays(short Days) {
		return DecreaseDateByXDays(*this, Days);
	}
	static clsDate DecreaseDateByOneWeek(clsDate Date)
	{
		for (short i = 0; i < 7; i++)
			Date = DecreaseDateByOneDay(Date);
		return Date;
	}
	clsDate DecreaseDateByOneWeek() {
		return DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeek(clsDate Date, short Weeks)
	{
		for (short i = 0; i < Weeks; i++)
			Date = DecreaseDateByOneWeek(Date);
		return Date;
	}
	clsDate DecreaseDateByXWeek(short Weeks) {
		return DecreaseDateByXWeek(*this, Weeks);
	}
	static clsDate DecreaseDateByOneMonth(clsDate Date)
	{
		if (Date._Month == 1)
		{
			Date._Month = 12;
			Date._Year--;
		}
		else
		{
			Date._Month--;
		}

		short DaysInMonth = GetNumberOfDaysInMonth(Date._Month, Date._Year);
		if (Date._Day > DaysInMonth)
			Date._Day = DaysInMonth;

		return Date;
	}
	clsDate DecreaseDateByOneMonth() {
		return DecreaseDateByOneMonth(*this);
	}
	static clsDate DecreaseDateByXMonth(clsDate Date, short Months)
	{
		for (short i = 0; i < Months; i++)
			Date = DecreaseDateByOneMonth(Date);
		return Date;
	}

	clsDate DecreaseDateByXMonth(short Months) {
		return DecreaseDateByXMonth(*this, Months);
	}

	static clsDate DecreaseDateByOneYear(clsDate Date)
	{
		return DecreaseDateByXMonth(Date, 12);
	}
	clsDate DecreaseDateByOneYear() {
		return DecreaseDateByOneYear(*this);
	}
	static clsDate DecreaseDateByXYears(clsDate Date, short Years)
	{
		for (short i = 0; i < Years; i++)
			Date = DecreaseDateByOneYear(Date);
		return Date;
	}
	clsDate DecreaseDateByXYears(short Years) {
		return DecreaseDateByXYears(*this, Years);
	}
	static clsDate DecreaseDateByXYearsFaster(clsDate Date, short Years)
	{
		Date._Year -= Years;
		return Date;
	}
	clsDate DecreaseDateByXYearsFaster(short Years) {
		return DecreaseDateByXYearsFaster(*this, Years);
	}

	static clsDate DecreaseDateByADecade(clsDate Date)
	{
		return DecreaseDateByXYears(Date, 10);
	}
	clsDate DecreaseDateByADecade() {
		return DecreaseDateByADecade(*this);
	}
	static clsDate DecreaseDateByXDecades(clsDate Date, short Decades)
	{
		for (short i = 0; i < Decades; i++)
			Date = DecreaseDateByADecade(Date);
		return Date;
	}
	clsDate DecreaseDateByXDecades(short Decades) {
		return DecreaseDateByXDecades(*this, Decades);
	}
	static clsDate DecreaseDateByOneCentury(clsDate Date)
	{
		return DecreaseDateByXYears(Date, 100);
	}
	clsDate DecreaseDateByOneCentury() {
		return DecreaseDateByOneCentury(*this);
	}
	static clsDate DecreaseDateByXCenturies(clsDate Date, short Centuries)
	{
		for (short i = 0; i < Centuries; i++)
			Date = DecreaseDateByOneCentury(Date);
		return Date;
	}
	clsDate DecreaseDateByXCenturies(short Centuries) {
		return DecreaseDateByXCenturies(*this, Centuries);
	}
	static clsDate DecreaseDateByOneMillennium(clsDate Date)
	{
		return DecreaseDateByXYears(Date, 1000);
	}
	clsDate DecreaseDateByOneMillennium() {
		return DecreaseDateByOneMillennium(*this);
	}
	static clsDate DecreaseDateByXMillennia(clsDate Date, short Millennia) {
		return DecreaseDateByXYears(Date, Millennia * 1000);
	}
	clsDate DecreaseDateByXMillennia(short Millennia) {
		return DecreaseDateByXYears(*this, Millennia * 1000);
	}
	static short DayOfWeekOrder(clsDate Date)
	{
		short a, y, m;
		a = (14 - Date._Month) / 12;
		y = Date._Year - a;
		m = Date._Month + (12 * a) - 2;
		// Gregorian:
		//0:sun, 1:Mon, 2:Tue...etc
		return (Date._Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}
	short DayOfWeekOrder() {
		return DayOfWeekOrder(*this);
	}
	static string GetDayName(short DayOrder) {

		switch (DayOrder) {
		case 0:
			return "Sunday";
			break;
		case 1:
			return "Monday";
			break;
		case 2:
			return "Tuesday";
			break;
		case 3:
			return "Wednesday";
			break;
		case 4:
			return "Thursday";
			break;
		case 5:
			return "Friday";
			break;

		case 6:
			return "Saturday";
			break;

		default:return "Invalid Day";
		}
	}

	static string ISDayEndOfWeeK(short DayOrder, string EndOfWeek) {
		string DayName = GetDayName(DayOrder);
		if (DayName == EndOfWeek)
			return "Yes It is End Of Week\n";
		else
			return "No Not The End Of The Week\n";
	}
	static string ISDayABusinessDay(short DayOrder) {

		if (DayOrder != 5 && DayOrder != 6)
			return "Yes it`s a Business Day\n";
		else
			return "No Not A business Day\n";
	}
	static bool IsWeekEnd(clsDate Date) {
		return (DayOfWeekOrder(Date) == 5 || DayOfWeekOrder(Date) == 6);
	}
	bool IsWeekEnd() {
		return IsWeekEnd(*this);
	}
	static short DaysUntilTheEndOfWeek(clsDate Date, short DayOrder) {

		return 6 - DayOrder;
	}
	short DaysUntilTheEndOfWeek(short DayOrder) {
		return DaysUntilTheEndOfWeek(*this, DayOrder);
	}
	static short DaysUntilTheEndOfMonth(clsDate Date) {

		short MonthDayCount = GetNumberOfDaysInMonth(Date._Month, Date._Year);
		return MonthDayCount - Date._Day;
	}
	short DaysUntilTheEndOfMonth() {
		return DaysUntilTheEndOfMonth(*this);
	}
	static short CalculateVacationDaysWithoutWeekends(clsDate Date1, clsDate Date2)
	{
		short ActualDays = 0;

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			if (!IsWeekEnd(Date1))
				ActualDays++;

			Date1 = IncreaseDateByOneDay(Date1);
		}
		return ActualDays;
	}
	short CalculateVacationDaysWithoutWeekends(clsDate Date2) {
		return CalculateVacationDaysWithoutWeekends(*this, Date2);
	}
	static short CalculateWeekends(clsDate Date1, clsDate Date2)
	{
		short Weekends = 0;

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			if (IsWeekEnd(Date1))
				Weekends++;

			Date1 = IncreaseDateByOneDay(Date1);
		}
		return Weekends;
	}
	short CalculateWeekends(clsDate Date2) {
		return CalculateWeekends(*this, Date2);
	}
	static clsDate GetBackFromVacationDate(clsDate Date, short Days) {

		clsDate EndMonthDate;
		EndMonthDate._Day = GetNumberOfDaysInMonth(Date._Month, Date._Year);
		EndMonthDate._Month = Date._Month;
		EndMonthDate._Year = Date._Year;

		short Weekends = CalculateWeekends(Date, EndMonthDate);

		Days += Weekends;
		clsDate Date2 = IncreaseDateByXDays(Date, Days);

		return Date2;

	}
	clsDate GetBackFromVacationDate(short Days) {
		return GetBackFromVacationDate(*this, Days);
	}
	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return !IsDate1BeforeDate2(Date1, Date2) && !IsTwoDatesEqual(Date1, Date2);
	}
	bool IsDate1AfterDate2(clsDate Date2) {
		return IsDate1AfterDate2(*this, Date2);
	}
	static bool IsPeriod1OverlapPeriod2(clsDate Enter1, clsDate Exit1, clsDate Enter2, clsDate Exit2) {
		return IsDate1BeforeDate2(Enter1, Exit2) && IsDate1AfterDate2(Exit1, Enter2);
	}
	short GetPeriodLengthInDays(clsDate Enter, clsDate Exit) {
		return GetDifferenceInDays(Enter, Exit, true);
	}
	bool IsDateInRange(clsDate Date, clsDate Enter, clsDate Exit) {
		return IsDate1BeforeDate2(Date, Exit) && IsDate1AfterDate2(Date, Enter);
	}
	short GetOverlapDaysCount(clsDate Enter1, clsDate Exit1, clsDate Enter2, clsDate Exit2) {
		if (!IsPeriod1OverlapPeriod2(Enter1, Exit1, Enter2, Exit2))
			return 0;
		clsDate FromDate = IsDate1AfterDate2(Enter1, Enter2) ? Enter1 : Enter2;
		clsDate ToDate = IsDate1BeforeDate2(Exit1, Exit2) ? Exit1 : Exit2;
		return GetDifferenceInDays(FromDate, ToDate, true);
	}

	static bool IsDateValid(clsDate Date)
	{
		if (Date._Day < 1 || Date._Month < 1 || Date._Year < 1)
			return false;

		short MonthDayCount = GetNumberOfDaysInMonth(Date._Month, Date._Year);
		if (Date._Day != 0 && Date._Day <= MonthDayCount)
			return true;
		else
			return false;
		if (Date._Month != 0 && Date._Month <= 12)
			return true;
		else
			return false;
	}

	static string FormatDate(clsDate Date, string Format) {

		for (int i = 0; i < Format.length(); i++) {
			Format.find("DD") != string::npos ? Format.replace(Format.find("DD"), 2, (Date._Day < 10 ? "0" : "") + to_string(Date._Day)) : Format;
			Format.find("MM") != string::npos ? Format.replace(Format.find("MM"), 2, (Date._Month < 10 ? "0" : "") + to_string(Date._Month)) : Format;
			Format.find("YYYY") != string::npos ? Format.replace(Format.find("YYYY"), 4, to_string(Date._Year)) : Format;
		}
		return Format;


	}
	string FormatDate(string Format) {
		return FormatDate(*this, Format);
	}
	static string DateToString(clsDate Date)
	{
		return  to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
	}
	string DateToString() {
		return DateToString(*this);
	}

	void Print() {
		cout << "Date: " << _Day << "/" << _Month << "/" << _Year << endl;
	}

};

