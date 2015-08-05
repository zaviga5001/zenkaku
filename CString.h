////////////////////////////////////////////////////////////////////////////////
//
//	LibTest: CString.h (last update: Jan 30, 2005)
//


#ifndef __CSTRING_H__
#define __CSTRING_H__

extern "C" {
#include <assert.h>
#include <stdio.h>
#include <string.h>
}

//NULL & NOT_FOUND
//#define NULL            0
#define NOT_FOUND		-1

//検索フラグ
#define SSF_DEFAULT     0x0
#define SSF_REVERSE		0x1
#define SSF_TOKEN		0x2
#define SSF_ALL			0x4

//略記用マクロ
#define STRING      const CString&
#define _DEFAULT    CString::m_defaultCharset

//汎用型定義
typedef unsigned char   BYTE;
typedef unsigned int    UINT;
typedef char*           LPSTR;
typedef const char*     LPCSTR;


class CString {
public:

	//character set IDs
	enum Charset {
		ASCII     =0x0,
		SHIFT_JIS =0x1,
		EUC_JP 	  =0x2,
	};

	//construction
	CString();
	CString(STRING);
	CString(LPCSTR);

	//destruction
	virtual ~CString();

	//member access (getting)
	int Len() const;

	//operator (cast)
	operator LPCSTR () const;

	//operator
	const char& operator [] (int nIndex) const;
	CString&    operator = (STRING);
	CString&    operator = (LPCSTR);
	CString&    operator += (STRING);
	CString&    operator += (LPCSTR);

	//substring
	CString Sub(int nBegin, int nEnd) const;
	CString Sub(int nBegin) const;
	CString Left(int nLen) const;
	CString Right(int nLen) const;

	//search
	LPCSTR  Search(STRING, UINT uFlags =0, Charset =_DEFAULT) const;
	LPCSTR  Search(LPCSTR, UINT uFlags =0, Charset =_DEFAULT) const;
	int     Find(STRING, UINT uFlags =0, Charset =_DEFAULT) const;
	int     Find(LPCSTR, UINT uFlags =0, Charset =_DEFAULT) const;
	CString Replace(LPCSTR tlpsz1, LPCSTR lpsz2, UINT uFlags =0, Charset =_DEFAULT) const;

	//conversion
	CString Invert(Charset =_DEFAULT) const;
	CString ToUpper(Charset =_DEFAULT) const;
	CString ToLower(Charset =_DEFAULT) const;
	CString Trim(Charset =_DEFAULT) const;
	CString Entab(int nStep, Charset =_DEFAULT) const;
	CString Detab(int nStep, Charset =_DEFAULT) const;

	//multi-byte character manipulation
	int     Count(Charset =_DEFAULT) const;
	int     Seek(int nPos, Charset =_DEFAULT) const;

	//I/O utility
	int     ReadLine(FILE* =stdin, Charset =_DEFAULT);
	int     Print(FILE* fp =stdout) const;
	int     Put(FILE* fp =stdout) const;


	//static members (CString_st.cpp) ------------------------

	static CString     add(LPCSTR, LPCSTR);
	static bool        equal(LPCSTR, LPCSTR);
	static int         compare(LPCSTR, LPCSTR, Charset =_DEFAULT);

	static CString     sub(LPCSTR, int nBegin, int nEnd);
	static CString     sub(LPCSTR, int nBegin);
	static CString     left(LPCSTR, int nLen);
	static CString     right(LPCSTR, int nLen);

	static char*        search(LPSTR, LPCSTR, UINT uFlags =0, Charset =_DEFAULT);
	static const char*  search(LPCSTR, LPCSTR, UINT uFlags =0, Charset =_DEFAULT);
	static int          find(LPCSTR, LPCSTR, UINT uFlags =0, Charset =_DEFAULT);
	static CString      replace(LPCSTR, LPCSTR lpsz1, LPCSTR lpsz2, UINT uFlags =0, Charset =_DEFAULT);	

	static CString      invert(LPCSTR, Charset =_DEFAULT);
	static CString      toUpper(LPCSTR, Charset =_DEFAULT);
	static CString      toLower(LPCSTR, Charset =_DEFAULT);
	static CString      trim(LPCSTR, Charset =_DEFAULT);
	static CString      entab(LPCSTR, int nStep, Charset =_DEFAULT);
	static CString      detab(LPCSTR, int nStep, Charset =_DEFAULT);

	static int          count(LPCSTR, Charset =_DEFAULT);
	static int          seek(LPCSTR, int nPos, Charset =_DEFAULT);
	static int          seq(const char*, Charset /*=_DEFAULT*/);

	static int          hash(STRING);

	static Charset      getDefaultCharset();
	static void         setDefaultCharset(Charset);

	
	//external functions ---------------------------------------

	friend CString  operator + (STRING, STRING);
	friend CString  operator + (STRING, LPCSTR);
	friend CString  operator + (LPCSTR, STRING);

	friend bool     operator == (STRING, STRING);
	friend bool     operator == (STRING, LPCSTR);
	friend bool     operator == (LPCSTR, STRING); 
	friend bool     operator != (STRING, STRING);
	friend bool     operator != (STRING, LPCSTR);
	friend bool     operator != (LPCSTR, STRING);

	friend bool     operator < (STRING, STRING);
	friend bool     operator < (STRING, LPCSTR);
	friend bool     operator < (LPCSTR, STRING);
	friend bool     operator <= (STRING, STRING);
	friend bool     operator <= (STRING, LPCSTR);
	friend bool     operator <= (LPCSTR, STRING);
	friend bool     operator > (STRING, STRING);
	friend bool     operator > (STRING, LPCSTR);
	friend bool     operator > (LPCSTR, STRING);
	friend bool     operator >= (STRING, STRING);
	friend bool     operator >= (STRING, LPCSTR);
	friend bool     operator >= (LPCSTR, STRING);

protected:

	//construction
	CString(int, LPSTR);

	//static members (CString_stin.cpp)
	static CString  _add(int nLen1, LPCSTR lpsz1, int nLen2, LPCSTR lpsz2);
	static CString  _sub(LPCSTR, int nBegin, int nEnd);
	static LPCSTR   _search(int, LPCSTR, int, LPCSTR, UINT uFlags, Charset);
	static LPSTR    _replace(int* lpnLen, int nLen, LPCSTR lpsz, int nLen1, LPCSTR lpsz1, int nLen2, LPCSTR lpsz2, UINT uFlags, Charset);
	static LPSTR    _invert(int nLen, char [], LPCSTR, Charset);
	static LPSTR    _toUpper(char [], LPCSTR, Charset);
	static LPSTR    _toLower(char [], LPCSTR, Charset);
	static LPSTR    _trim(int* lpnLen, LPCSTR, Charset);
	static LPSTR    _entab(int* lpnLen, LPCSTR, int nStep, Charset);
	static LPSTR    _detab(int* lpnLen, LPCSTR, int nStep, Charset);
	static LPSTR    _readLine(int* lpnLen, int* lpnExitCode, FILE*, Charset);

	int     m_nLen;
	LPSTR   m_lpsz;

	static char         m_szTokenize[256];
	static const int    m_anSeq[][256];
	static Charset      m_defaultCharset;


};


/* construction ------------------------------------------------------------- */

//コンストラクタ
inline CString::CString()
: m_nLen(0), m_lpsz(NULL){
}

//コンストラクタ [for internal use]
inline CString::CString(int nLen, LPSTR lpsz)
: m_nLen(nLen), m_lpsz(lpsz){
}


/* member access (getting) -------------------------------------------------- */

//文字列長の取得
inline int CString::Len() const {
	return m_nLen;
}


/* operator (cast) ---------------------------------------------------------- */

//キャスト (LPCSTR)
inline CString::operator LPCSTR () const {
	return m_lpsz;
}


/* operator ----------------------------------------------------------------- */

//要素参照
inline const char& CString::operator [] (int nIndex) const {
	assert(m_lpsz);
	assert(nIndex >=0);
	assert(nIndex <= m_nLen);
	return m_lpsz[nIndex];
}


/* multi-byte caracter manipulation ----------------------------------------- */

//文字数カウント
inline int CString::Count(Charset cs) const {
	return count(m_lpsz, cs);
}

//文字位置シーク
inline int CString::Seek(int nPos, Charset cs) const {
	return seek(m_lpsz, nPos, cs);
}


/* static members ----------------------------------------------------------- */

//デフォルト文字セットの設定取得
inline CString::Charset CString::getDefaultCharset(){
	return m_defaultCharset;
}
//デフォルト文字セットの設定
inline void CString::setDefaultCharset(Charset eEnc){
	m_defaultCharset =eEnc;
}


/* external operator -------------------------------------------------------- */

//等値判定 (1)
inline bool operator == (STRING s1, STRING s2){
	return CString::equal(s1.m_lpsz, s2.m_lpsz);
}
inline bool operator == (STRING s1, LPCSTR lpsz2){
	return CString::equal(s1.m_lpsz, lpsz2);
}
inline bool operator == (LPCSTR lpsz1, STRING s2){
	return CString::equal(lpsz1, s2.m_lpsz);
}

//非等値判定
inline bool operator != (STRING s1, STRING s2){
	return !CString::equal(s1.m_lpsz, s2.m_lpsz);
}
inline bool operator != (STRING s1, LPCSTR lpsz2){
	return !CString::equal(s1.m_lpsz, lpsz2);
}
inline bool operator != (LPCSTR lpsz1, STRING s2){
	return !CString::equal(lpsz1, s2.m_lpsz);
}

//辞書順比較 (<)
inline bool operator < (STRING s1, STRING s2){
	return (CString::compare(s1.m_lpsz, s2.m_lpsz) < 0);
}
inline bool operator < (STRING s1,LPCSTR lpsz2){
	return (CString::compare(s1.m_lpsz, lpsz2) < 0);
}
inline bool operator < (LPCSTR lpsz1, STRING s2){
	return (CString::compare(lpsz1, s2.m_lpsz) < 0);
}

//辞書順比較 (<=)
inline bool operator <= (STRING s1, STRING s2){
	return (CString::compare(s1.m_lpsz, s2.m_lpsz) <= 0);
}
inline bool operator <= (STRING s1,LPCSTR lpsz2){
	return (CString::compare(s1.m_lpsz, lpsz2) <= 0);
}
inline bool operator <= (LPCSTR lpsz1, STRING s2){
	return (CString::compare(lpsz1, s2.m_lpsz) <= 0);
}

//辞書順比較 (>)
inline bool operator > (STRING s1, STRING s2){
	return (CString::compare(s1.m_lpsz, s2.m_lpsz) > 0);
}
inline bool operator > (STRING s1,LPCSTR lpsz2){
	return (CString::compare(s1.m_lpsz, lpsz2) > 0);
}
inline bool operator > (LPCSTR lpsz1, STRING s2){
	return (CString::compare(lpsz1, s2.m_lpsz) > 0);
}

//辞書順比較 (>=)
inline bool operator >= (STRING s1, STRING s2){
	return (CString::compare(s1.m_lpsz, s2.m_lpsz) >= 0);
}
inline bool operator >= (STRING s1,LPCSTR lpsz2){
	return (CString::compare(s1.m_lpsz, lpsz2) >= 0);
}
inline bool operator >= (LPCSTR lpsz1, STRING s2){
	return (CString::compare(lpsz1, s2.m_lpsz) >= 0);
}


//略記用マクロ解除
#undef STRING
#undef _DEFAULT


#endif //__CSTRING_H__
//[EOF]
