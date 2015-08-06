////////////////////////////////////////////////////////////////////////////////
//
//  CDate.h (last update: Aug  2, 2005)
//


#ifndef __CDATE_H__
#define __CDATE_H__

#include <assert.h>

//略記用マクロ
#define _DATE const CDate&


typedef unsigned int UINT ; 

class CDate { 
public:

	int year;
	int month;
	int day;

	enum {
		JAN = 1, FEB = 2, MAR = 3, APR = 4, MAY = 5, JUN = 6,
		JUL = 7, AUG = 8, SEP = 9, OCT =10, NOV =11, DEC =12,
		SUN =0, MON =1, TUE =2, WED =3, THU =4, FRI =5, SAT =6
	};

	//construction
	CDate();
	CDate(_DATE);
	CDate(int y, int m, int d);

	//operator
	CDate&  operator = (_DATE);
	CDate&  operator += (int);
	CDate&  operator -= (int);
	CDate   operator ++ ();
	CDate   operator ++ (int);
	CDate   operator -- ();
	CDate   operator -- (int);

	//member access (setting)
	void    Set(int y, int m, int d);

	//operation
	bool    IsValid() const;
	UINT    DayOfWeek() const;

	//static members
	static bool  IsYearBissextile(int y);
	static bool  IsDateValid(int y, int m, int d);
	static int   LenOfMonth(int y, int m);
	static int   DayOfWeek(int y, int m, int d);
	static int   Compare(_DATE, _DATE);
	static CDate Today();

	//external operator
	friend int operator - (_DATE, _DATE);

protected:

	//static members
	static int   toInt(int y, int m, int d);

};

//external operator
CDate   operator + (_DATE, int);
CDate   operator - (_DATE, int);
bool    operator == (_DATE, _DATE);
bool    operator != (_DATE, _DATE);
bool    operator <  (_DATE, _DATE);
bool    operator <= (_DATE, _DATE);
bool    operator >  (_DATE, _DATE);
bool    operator >= (_DATE, _DATE);


/* construction ------------------------------------------------------------- */

//コンストラクタ
inline CDate::CDate(){
}

//コンストラクタ
inline CDate::CDate(_DATE d)
: year(d.year), month(d.month), day(d.day) {
}

//コンストラクタ
inline CDate::CDate(int nYear, int nMonth, int nDay)
: year(nYear), month(nMonth), day(nDay) {
}


/* member access (setting) -------------------------------------------------- */

//値の設定
inline void CDate::Set(int nYear, int nMonth, int nDay){
	year  =nYear;
	month =nMonth;
	day   =nDay;
}


/* operation ---------------------------------------------------------------- */

//有効性の判定
inline bool CDate::IsValid() const {
	return IsDateValid(year, month, day);
}

//曜 (曜日) の取得
inline UINT CDate::DayOfWeek() const {
	return DayOfWeek(year, month, day);
}


/* external operator -------------------------------------------------------- */

//等値比較
inline bool operator == (_DATE d1, _DATE d2){
	return (d1.year == d2.year && d1.month == d2.month && d1.day == d2.day);
}

//非等値比較
inline bool operator != (_DATE d1, _DATE d2){
	return (d1.year != d2.year || d1.month != d2.month || d1.day != d2.day);
}

//比較
inline bool operator < (_DATE d1, _DATE d2){
	return (CDate::Compare(d1, d2) < 0);
}

//比較
inline bool operator <= (_DATE d1, _DATE d2){
	return (CDate::Compare(d1, d2) <= 0);
}

//比較
inline bool operator > (_DATE d1, _DATE d2){
	return (CDate::Compare(d1, d2) > 0);
}

//比較
inline bool operator >= (_DATE d1, _DATE d2){
	return (CDate::Compare(d1, d2) >= 0);
}


//略記用マクロ解除
#undef _DATE

#endif //__CDATE_H__
//[EOF]
