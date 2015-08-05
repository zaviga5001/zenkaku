////////////////////////////////////////////////////////////////////////////////
//
//  CDate.cpp (last update: Jul 16, 2005)
//


#include "CDate.h"
#include <time.h>


//略記用マクロ
#define _DATE const CDate&


////////////////////////////////////////////////////////////////////////////////
//operator

//代入
CDate& CDate::operator = (_DATE d){

	year  =d.year;
	month =d.month;
	day   =d.day;

	return *this;
}

//加算代入
CDate& CDate::operator += (int n){
	assert(CDate::IsDateValid(year, month, day));

	day +=n;

	if (n >= 0){
		//to the future ----------------------------------------

		for (;;){

			int nLen =LenOfMonth(year, month);
			if (day <= nLen) break;

			day -=nLen;

			if (month == CDate::DEC){
				month =CDate::JAN;

				if (year == -1)
					year =1;
				else
					++year;
			}
			else
				++month;
		}
	}
	else {
		//to the past ------------------------------------------

		for (;;){

			if (day >= 1) break;

			if (month == JAN){

				if (year == 1)
					year =-1;
				else
					--year;

				month =DEC;
			}
			else
				--month;

			day +=LenOfMonth(year, month);
		}
	}

	return *this;
}

//減算代入
CDate& CDate::operator -= (int n){
	assert(CDate::IsDateValid(year, month, day));

	day -=n;

	if (n >= 0){
		//to the past ------------------------------------------

		for (;;){

			if (day >= 1) break;

			if (month == JAN){

				if (year == 1)
					year =-1;
				else
					--year;

				month =DEC;
			}
			else
				--month;

			day +=LenOfMonth(year, month);
		}
	}
	else {
		//to the future ----------------------------------------

		for (;;){

			int nLen =LenOfMonth(year, month);
			if (day <= nLen) break;

			day -=nLen;

			if (month == CDate::DEC){
				month =CDate::JAN;

				if (year == -1)
					year =1;
				else
					++year;
			}
			else
				++month;
		}
	}

	return *this;
}

//インクリメント (前置)
CDate CDate::operator ++ (){
	assert(IsDateValid(year, month, day));

	if (day == LenOfMonth(year, month)){
		day =1;

		if (month == DEC){
			month =JAN;

			if (year == -1)
				year =1;
			else
				++year;
		}
		else
			++month;
	}
	else
		++day;

	return CDate(year, month, day);
}

//インクリメント (後置)
CDate CDate::operator ++ (int){
	assert(IsDateValid(year, month, day));

	const int nYear  =year;
	const int nMonth =month;
	const int nDay   =day;

	if (day == LenOfMonth(year, month)){
		day =1;

		if (month == DEC){
			month =JAN;

			if (year == -1)
				year =1;
			else
				++year;
		}
		else
			++month;
	}
	else
		++day;

	return CDate(nYear, nMonth, nDay);
}

//デクリメント (前置)
CDate CDate::operator -- (){
	assert(IsDateValid(year, month, day));

	if (day == 1){

		if (month == JAN){

			if (year == 1)
				year =-1;
			else
				--year;

			month =DEC;
		}
		else
			--month;

		day =LenOfMonth(year, month);
	}
	else
		--day;

	return CDate(year, month, day);
}

//デクリメント (後置)
CDate CDate::operator -- (int){
	assert(IsDateValid(year, month, day));

	const int nYear  =year;
	const int nMonth =month;
	const int nDay   =day;

	if (day == 1){

		if (month == JAN){

			if (year == 1)
				year =-1;
			else
				--year;

			month =DEC;
		}
		else
			--month;

		day =LenOfMonth(year, month);
	}
	else
		--day;

	return CDate(nYear, nMonth, nDay);
}


////////////////////////////////////////////////////////////////////////////////
//static members

//閏年の判定
bool CDate::IsYearBissextile(int nYear){
	return !(nYear % 4) && (nYear % 100 || !(nYear % 400));
}

//日付データの有効性判定
bool CDate::IsDateValid(int nYear, int nMonth, int nDay){
	return (nYear && nMonth >= JAN && nMonth <= DEC && nDay >= 1 && nDay <= LenOfMonth(nYear, nMonth));
}

//起算日 (1/ 1/ 1) からの経過日数の算出 [for internal use]
int CDate::toInt(int nYear, int nMonth, int nDay){
	assert(IsDateValid(nYear, nMonth, nDay));

	static const int anCumm[] ={
		0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 
	};

	int n;

	if (nYear > 0){

		n =365*(nYear - 1) + (nYear - 1)/4 - (nYear - 1)/100 + (nYear - 1)/400;

		n +=(nMonth > FEB && IsYearBissextile(nYear))
			? anCumm[nMonth - 1] + 1
			: anCumm[nMonth - 1];
	}
	else {

		n =365*nYear + (nYear - 3)/4 - (nYear - 3)/100 + (nYear - 3)/400;

		n +=(nMonth > FEB && IsYearBissextile(nYear + 1))
			? anCumm[nMonth - 1] + 1
			: anCumm[nMonth - 1];
	}

	return n + (nDay - 1);
}

//「月の日数」の取得
int CDate::LenOfMonth(int nYear, int nMonth){
	assert(nYear && nMonth >= JAN && nMonth <= DEC);

	static const int anLen[] ={
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};

	return (IsYearBissextile(nYear) && nMonth == 2)
		? 29
		: anLen[nMonth - 1];
}

//「曜」の取得
int CDate::DayOfWeek(int nYear, int nMonth, int nDay){
	assert(IsDateValid(nYear, nMonth, nDay));

	int n =toInt(nYear, nMonth, nDay) + 1;

	return (n >= 0)
		? n % 7
		: 6 + n % 7;
}

//比較
int CDate::Compare(const CDate& d1, const CDate& d2){
	assert(IsDateValid(d1.year, d1.month, d1.day));
	assert(IsDateValid(d2.year, d2.month, d2.day));

	if (d1.year != d2.year)
		return (d1.year < d2.year) ? -1 : 1;

	if (d1.month != d2.month)
		return (d1.month < d2.month) ? -1 : 1;

	if (d1.day != d2.day)
		return (d1.day < d2.day) ? -1 : 1;

	return 0;
}

//「今日の日付」の取得
CDate CDate::Today(){

	time_t t;
	time(&t);

	tm* lpTm =gmtime(&t);

	return CDate(lpTm->tm_year + 1900, lpTm->tm_mon + 1, lpTm->tm_mday);
}


////////////////////////////////////////////////////////////////////////////////
//external operator

//加算
CDate operator + (const CDate& d, int n){
	assert(CDate::IsDateValid(d.year, d.month, d.day));

	int nYear  =d.year;
	int nMonth =d.month;
	int nDay   =d.day + n;

	if (n >= 0){
		//to the future ----------------------------------------

		for (;;){

			int nLen =CDate::LenOfMonth(nYear, nMonth);
			if (nDay <= nLen) break;

			nDay -=nLen;

			if (nMonth == CDate::DEC){
				nMonth =CDate::JAN;

				if (nYear == -1)
					nYear =1;
				else
					++nYear;
			}
			else
				++nMonth;
		}
	}
	else {
		//to the past ------------------------------------------

		for (;;){

			if (nDay >= 1) break;

			if (nMonth == CDate::JAN){

				if (nYear == 1)
					nYear =-1;
				else
					--nYear;

				nMonth =CDate::DEC;
			}
			else
				--nMonth;

			nDay +=CDate::LenOfMonth(nYear, nMonth);
		}
	}

	return CDate(nYear, nMonth, nDay);
}

//減算 (1)
CDate operator - (const CDate& d, int n){
	assert(CDate::IsDateValid(d.year, d.month, d.day));

	int nYear  =d.year;
	int nMonth =d.month;
	int nDay   =d.day - n;

	if (n >= 0){
		//to the past ------------------------------------------

		for (;;){

			if (nDay >= 1) break;

			if (nMonth == CDate::JAN){

				if (nYear == 1)
					nYear =-1;
				else
					--nYear;

				nMonth =CDate::DEC;
			}
			else
				--nMonth;

			nDay +=CDate::LenOfMonth(nYear, nMonth);
		}

	}
	else {
		//to the future ----------------------------------------

		for (;;){

			int nLen =CDate::LenOfMonth(nYear, nMonth);
			if (nDay <= nLen) break;

			nDay -=nLen;

			if (nMonth == CDate::DEC){
				nMonth =CDate::JAN;

				if (nYear == -1)
					nYear =1;
				else
					++nYear;
			}
			else
				++nMonth;
		}
	}

	return CDate(nYear, nMonth, nDay);
}

//減算 (2)
int operator - (_DATE d1, _DATE d2){
	return CDate::toInt(d1.year, d1.month, d1.day) - CDate::toInt(d2.year, d2.month, d2.day);
}


//[EOF]