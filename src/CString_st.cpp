////////////////////////////////////////////////////////////////////////////////
//
//	CString: CString_stat.cpp (last update: Feb  5, 2005)
//


#include "CString.h"
#include <ctype.h>

//略記用マクロ
#define NULL_STRING CString()
#define E		    0


/* operator base ------------------------------------------------------------ */

//文字列の連結
CString CString::add(LPCSTR lpsz1, LPCSTR lpsz2){

	if (lpsz1){
		if (lpsz2)
			return _add(::strlen(lpsz1), lpsz1, ::strlen(lpsz2), lpsz2);
		else
			return CString(lpsz1);	
	}
	else {
		if (lpsz2)
			return CString(lpsz2);
		else
			return NULL_STRING;	
	}
}

//等値判定
bool CString::equal(LPCSTR lpsz1, LPCSTR lpsz2){

	if (lpsz1){

		if (lpsz2){

			const char* p1 =lpsz1;
			const char* p2 =lpsz2;

			while (*p1 == *p2){

				if (!*p1) return true;

				++p1;
				++p2;
			}
		}

		return false;
	}
	else {
		return !lpsz2;
	}
}

//辞書順比較
int CString::compare(LPCSTR lpsz1, LPCSTR lpsz2, Charset cs){

	if (!lpsz1) return (lpsz2) ? 1 : 0;
	if (!lpsz2) return -1;

	int nRes   =0;
	int nSub   =0;

	const char* p1 =lpsz1;
	const char* p2 =lpsz2;

	for (;;){
				
		unsigned char c1 =*p1;
		unsigned char c2 =*p2;

		if (c1 == c2){

			if (!c1) break;

			int nSeq =seq(p1, cs);

			int i;					
			for (i=1; i<nSeq; ++i){

				c1 =p1[i];
				c2 =p2[i];

				if (c1 != c2){
					return (c1 < c2) ? -(p1 - lpsz1 + 1) : (p2 - lpsz2 + 1);
				}
			}

			p1 +=nSeq;
			p2 +=nSeq;
		}
		else {

			nRes =(c1 < c2) ? -(p1 - lpsz1 + 1) : (p2 - lpsz2 + 1);

			c1 =toupper(c1);
			c2 =toupper(c2);

			if (!nSub){
				nSub =(c1 < c2) ? -(p1 - lpsz1 + 1) : (p2 - lpsz2 + 1);
			}

			if (c1 != c2) return nRes;

			++p1;
			++p2;
		}
	}

	return (nSub) ? nSub : nRes;
}


/* substring ---------------------------------------------------------------- */

//部分文字列の取得 (1)
CString CString::sub(LPCSTR lpsz, int nBegin, int nEnd){

	if (!lpsz) return NULL_STRING;

	if (nBegin < 0){
		nEnd +=nBegin;
		nBegin =0;
	}

	int nLen =::strlen(lpsz);
	if (nEnd > nLen) nEnd =nLen;

	return (nBegin <= nEnd) ? _sub(lpsz, nBegin, nEnd) : NULL_STRING;
}

//部分文字列の取得 (2)
CString CString::sub(LPCSTR lpsz, int nBegin){

	if (!lpsz) return NULL_STRING;

	int nEnd =::strlen(lpsz);

	if (nBegin < 0){
		nEnd +=nBegin;
		nBegin =0;		
	}

	return (nBegin <= nEnd) ? _sub(lpsz, nBegin, nEnd) : NULL_STRING;
}

//左部分文字列の取得
CString CString::left(LPCSTR lpsz, int nLen){

	if (!lpsz || nLen < 0) return NULL_STRING;

	int nEnd =::strlen(lpsz);
	if (nEnd > nLen) nEnd =nLen;

	return _sub(lpsz, 0, nEnd);
}

//右部分文字列の取得
CString CString::right(LPCSTR lpsz, int nLen){

	if (!lpsz || nLen < 0) return NULL_STRING;

	int nEnd =::strlen(lpsz);

	return _sub(lpsz, (nLen < nEnd) ? nEnd - nLen : 0, nEnd);
}


/* search & replacement ----------------------------------------------------- */

//パターン検索
LPSTR CString::search(LPSTR lpsz1, LPCSTR lpsz2, UINT uFlags, Charset cs){
	return (lpsz1 && lpsz2) ? (LPSTR)_search(::strlen(lpsz1), lpsz1, ::strlen(lpsz2), lpsz2, uFlags, cs) : NULL;
}

//パターン検索 (const)
LPCSTR CString::search(LPCSTR lpsz1, LPCSTR lpsz2, UINT uFlags, Charset cs){
	return (lpsz1 && lpsz2) ? _search(::strlen(lpsz1), lpsz1, ::strlen(lpsz2), lpsz2, uFlags, cs) : NULL;
}

//パターン検索 (インデクス)
int CString::find(LPCSTR lpsz1, LPCSTR lpsz2, UINT uFlags, Charset cs){

	if (!lpsz1 || !lpsz2) return NOT_FOUND;

	LPCSTR p =_search(::strlen(lpsz1), lpsz1, ::strlen(lpsz2), lpsz2, uFlags, cs);

	return (p) ? p - lpsz1 : NOT_FOUND;
}

//パターン置換
CString CString::replace(LPCSTR lpszSrc, LPCSTR lpsz1, LPCSTR lpsz2, UINT uFlags, Charset eEnc){

	if (!lpszSrc) return NULL_STRING;

	if (lpsz1 && *lpsz1){

		if (!lpsz2) lpsz2 ="";

		int   nLen;
		LPSTR lpsz =_replace(&nLen, ::strlen(lpszSrc), lpszSrc, ::strlen(lpsz1), lpsz1, ::strlen(lpsz2), lpsz2, uFlags, eEnc);

		return CString(nLen, lpsz);
	}
	else {

		int   nLen =::strlen(lpszSrc);
		char* lpac =new char [nLen + 1];
		assert(lpac);

		::memcpy(lpac, lpszSrc, nLen + 1);

		return CString(nLen, lpac);
	}
}


/* conversion --------------------------------------------------------------- */

//転置
CString CString::invert(LPCSTR lpsz, Charset cs){

	if (!lpsz) return NULL_STRING;

	int   nLen =::strlen(lpsz);
	char* lpac =new char [nLen + 1];
	assert(lpac);

	return CString(nLen, _invert(nLen, lpac, lpsz, cs));
}


//ケース変換 (大文字) 
CString CString::toUpper(LPCSTR lpsz, Charset cs){

	if (!lpsz) return NULL_STRING;

	int   nLen =::strlen(lpsz);
	char* lpac =new char [nLen +1];
	assert(lpac);

	return CString(nLen, _toUpper(lpac, lpsz, cs));
}

//ケース変換 (小文字) 
CString CString::toLower(LPCSTR lpsz, Charset cs){

	if (!lpsz) return NULL_STRING;

	int   nLen =::strlen(lpsz);
	char* lpac =new char [nLen +1];
	assert(lpac);

	return CString(nLen, _toLower(lpac, lpsz, cs));
}

//トリミング
CString CString::trim(LPCSTR lpsz2, Charset cs){

	if (!lpsz2) return NULL_STRING;

	int   nLen;
	LPSTR lpsz =_trim(&nLen, lpsz2, cs);

	return CString(nLen, lpsz);
}

//タブ化
CString CString::entab(LPCSTR lpsz2, int nStep, Charset cs){

	if (!lpsz2) return NULL_STRING;

	int nLen;
	LPSTR lpsz =_entab(&nLen, lpsz2, nStep, cs);

	return CString(nLen, lpsz);
}

//タブ解除
CString CString::detab(LPCSTR lpsz2, int nStep, Charset cs){

	if (!lpsz2) return NULL_STRING;

	int nLen;
	LPSTR lpsz =_detab(&nLen, lpsz2, nStep, cs);

	return CString(nLen, lpsz);
}


/* multi byte character manipulation ---------------------------------------- */

//文字数カウント
int CString::count(LPCSTR lpsz, Charset cs){
	
	if (!lpsz) return 0;

	int nRes =0;

	const char* p =lpsz;

	while (*p){
		++nRes;
		p +=seq(p, cs);
	}

	return nRes;
}

//文字位置シーク
int CString::seek(LPCSTR lpsz, int nPos, Charset cs){

	if (!lpsz || nPos < 0) return NOT_FOUND;

	int nCount =nPos;

	const char* p =lpsz;

	for (;;){

		if (!nCount) return p - lpsz;
		if (!*p) return NOT_FOUND;

		--nCount;
		p +=seq(p, cs);
	}
}

//シーケンスの取得
int CString::seq(const char* p, Charset eEnc){
#ifdef _DEBUG

	assert(p);

	int nRes =m_anSeq[eEnc][(unsigned char)*p];
	assert(nRes);

	return nRes;
#else
	return m_anSeq[eEnc][(unsigned char)*p];
#endif
}


/* hash function ------------------------------------------------------------ */

//ハッシュ関数
int CString::hash(const CString& s){

	char* p =s.m_lpsz;
	if (!p) return 0;

	int nRes =0;

	while (*p){
		nRes =31*nRes + *p;
		++p;
	}

	if (nRes < 0) nRes =-(nRes + 1);

	return nRes;
}


/* data --------------------------------------------------------------------- */

const int CString::m_anSeq[][256] ={
	{ //ASCII
		0, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		E, E, E, E, E, E, E, E,  E, E, E, E, E, E, E, E,
		E, E, E, E, E, E, E, E,  E, E, E, E, E, E, E, E,
		E, E, E, E, E, E, E, E,  E, E, E, E, E, E, E, E,
		E, E, E, E, E, E, E, E,  E, E, E, E, E, E, E, E,
		E, E, E, E, E, E, E, E,  E, E, E, E, E, E, E, E,
		E, E, E, E, E, E, E, E,  E, E, E, E, E, E, E, E,
		E, E, E, E, E, E, E, E,  E, E, E, E, E, E, E, E,
		E, E, E, E, E, E, E, E,  E, E, E, E, E, E, E, E
	},
	{ //SHIFT_JIS
		0, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		E, 2, 2, 2, 2, 2, 2, 2,  2, 2, 2, 2, 2, 2, 2, 2, //JIS漢字 (0x80除く)
		2, 2, 2, 2, 2, 2, 2, 2,  2, 2, 2, 2, 2, 2, 2, 2, //JIS漢字
		E, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, //半角カナ (0xA0除く)
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, //半角カナ
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, //半角カナ
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, //半角カナ
		2, 2, 2, 2, 2, 2, 2, 2,  2, 2, 2, 2, 2, 2, 2, 2, //JIS漢字
		E, E, E, E, E, E, E, E,  E, E, E, E, E, E, E, E
	},
	{ //EUC_JP
		0, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
		E, E, E, E, E, E, E, E,  E, E, E, E, E, E, 2, 3, //0x8E: 半角カナ, 0x8F: JIS補助漢字
		E, E, E, E, E, E, E, E,  E, E, E, E, E, E, E, E,
		E, 2, 2, 2, 2, 2, 2, 2,  2, 2, 2, 2, 2, 2, 2, 2, //JIS漢字 (0xA0 除く)
		2, 2, 2, 2, 2, 2, 2, 2,  2, 2, 2, 2, 2, 2, 2, 2, //JIS漢字
		2, 2, 2, 2, 2, 2, 2, 2,  2, 2, 2, 2, 2, 2, 2, 2, //JIS漢字
		2, 2, 2, 2, 2, 2, 2, 2,  2, 2, 2, 2, 2, 2, 2, 2, //JIS漢字
		2, 2, 2, 2, 2, 2, 2, 2,  2, 2, 2, 2, 2, 2, 2, 2, //JIS漢字
		2, 2, 2, 2, 2, 2, 2, 2,  2, 2, 2, 2, 2, 2, 2, E
	},
};


//トークン区切り文字セット
char CString::m_szTokenize[256] ="\t\n !\"#$%&'()*;,-./:;<=>?@[\\]^_`{|}~";

//デフォルト文字セット
CString::Charset CString::m_defaultCharset =SHIFT_JIS;


//[EOF]
