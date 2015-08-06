////////////////////////////////////////////////////////////////////////////////
//
//	CString: CString_int.cpp (last update: Feb  6, 2005)
//


#include "CString.h"
#include <ctype.h>

//入出バッファ・スワップ単位
#define BUFFER_SWAP 256


/* operator base ------------------------------------------------------------ */

//文字列の連結 [for internal use]
CString CString::_add(int nLen1, LPCSTR lpsz1, int nLen2, LPCSTR lpsz2){
	assert(nLen1 >= 0 && lpsz1);
	assert(nLen2 >= 0 && lpsz2);

	int   nLen =nLen1 + nLen2;
	char* lpac =new char [nLen + 1];
	assert(lpac);

	::memcpy(lpac,         lpsz1, nLen1);
	::memcpy(lpac + nLen1, lpsz2, nLen2 + 1);

	return CString(nLen, lpac);
}


/* substring ---------------------------------------------------------------- */

//部分文字列の取得 [for internal use]
CString CString::_sub(LPCSTR lpsz, int nBegin, int nEnd){
	assert(lpsz);
	assert(0 <= nBegin && nBegin <= nEnd);

	int   nLen =nEnd - nBegin;
	char* lpac =new char [nLen + 1];
	assert(lpac);

	::memcpy(lpac, lpsz + nBegin, nLen);
	lpac[nLen] ='\0';

	return CString(nLen, lpac);
}


/* search & replace --------------------------------------------------------- */

//パターン検索 [fot internal use]
LPCSTR CString::_search(int nLen1, LPCSTR lpsz1, int nLen2, LPCSTR lpsz2, UINT uFlags, Charset cs){
	assert(nLen1 >= 0 && lpsz1);
	assert(nLen2 >= 0 && lpsz2);

	if (uFlags & SSF_REVERSE){

		char* lpac1 =new char [nLen1 + 1];
		char* lpac2 =new char [nLen2 + 1];
		assert(lpac1 && lpac2);

		LPCSTR p =_search(
			nLen1, _invert(nLen1, lpac1, lpsz1, cs),
			nLen2, _invert(nLen2, lpac2, lpsz2, cs),
			uFlags & ~SSF_REVERSE,
			cs);

		delete [] lpac1;
		delete [] lpac2;

		return (p) ? lpsz1 + (nLen1 - nLen2) - (p - lpac1) : NULL;
	}

	//----------------------------------------------------------

	const char* p    =lpsz1;
	const char* pEnd =lpsz1 + nLen1;

	char cPrev ='\0';

	if (uFlags & SSF_TOKEN){
	
		while (p < pEnd){

			if (::memcmp(p, lpsz2, nLen2) == 0){
				if (::strchr(m_szTokenize, cPrev) && ::strchr(m_szTokenize, p[nLen2])) return p;
			}

			cPrev =*p;
			p +=seq(p, cs);
		}
	}
	else {
	
		while (p < pEnd){

			if (::memcmp(p, lpsz2, nLen2) == 0) return p;

			cPrev =*p;
			p +=seq(p, cs);
		}
	}

	return NULL;
}

//パターン置換 [for internal use]
LPSTR CString::_replace(int* lpnLen, int nLenSrc, LPCSTR lpszSrc, int nLen1, LPCSTR lpsz1, int nLen2, LPCSTR lpsz2, UINT uFlags, Charset cs){
	assert(lpnLen);
	assert(nLen1 >= 0 && lpsz1 && lpsz1[0]);
	assert(nLen2 >= 0 && lpsz2);

	if (uFlags & SSF_REVERSE){

		char* lpacSrc =new char [nLenSrc + 1];
		char* lpac1   =new char [nLen1 + 1];
		char* lpac2   =new char [nLen2 + 1];		
		assert(lpacSrc && lpac1 && lpac2);

		int   nLen;
		LPSTR lpsz =_replace(
			&nLen,
			nLenSrc, _invert(nLenSrc, lpacSrc, lpszSrc, cs),
			nLen1,   _invert(nLen1,   lpac1,   lpsz1,   cs),
			nLen2,   _invert(nLen2,   lpac2,   lpsz2,   cs),
			uFlags & ~SSF_REVERSE, cs);

		delete [] lpacSrc;
		delete [] lpac1;
		delete [] lpac2;

		char* lpac =new char [nLen + 1];
		assert(lpac);
			
		_invert(nLen, lpac, lpsz, cs);
		
		delete [] lpsz;

		*lpnLen =nLen;

		return lpac;
	}

	//----------------------------------------------------------

	int  nCount =0;

	const char** lpalpcIndex =new const char* [(nLenSrc + nLen1 - 1)/nLen1];
	assert(lpalpcIndex);

	bool bAll  =((uFlags & SSF_ALL) != 0);
	char cPrev ='\0';

	const char* q    =lpszSrc;
	const char* qEnd =lpszSrc + nLenSrc;

	if (uFlags & SSF_TOKEN){

		while (q < qEnd){

			if (::memcmp(q, lpsz1, nLen1) == 0){

				if (::strchr(m_szTokenize, cPrev) && ::strchr(m_szTokenize, q[nLen1])){

					lpalpcIndex[nCount++] =q;
					cPrev =q[nLen1 - 1];

					q +=nLen1;

					if (bAll) continue; else break;
				}
			}

			cPrev =*q;
			q +=seq(q, cs);
		}
	}
	else {

		while (q < qEnd){

			if (::memcmp(q, lpsz1, nLen1) == 0){

				lpalpcIndex[nCount++] =q;
				cPrev =q[nLen1 - 1];

				q +=nLen1;

				if (bAll) continue; else break;
			}

			cPrev =*q;
			q +=seq(q, cs);
		}
	}

	//----------------------------------------------------------

	int   nLen =nLenSrc + (nLen2 - nLen1)*nCount;
	char* lpac =new char [nLen + 1];
	assert(lpac);

	char* p;
	p =lpac;
	q =lpszSrc;

	int i;
	for (i=0; i<nCount; ++i){

		int nSeq =lpalpcIndex[i] - q;

		::memcpy(p, q, nSeq);
		p +=nSeq;
		q +=nSeq;

		::memcpy(p, lpsz2, nLen2);
		p +=nLen2;
		q +=nLen1;
	}
	::strcpy(p, q);
		
	delete [] lpalpcIndex;

	*lpnLen =nLen;

	return lpac;
}



/* conversion --------------------------------------------------------------- */

//転置 [for internal use]
LPSTR CString::_invert(int nLen, char* lpac, LPCSTR lpsz, Charset cs){
	assert(nLen >= 0 && lpac && lpsz);

	char*       p =lpac + nLen;
	const char* q =lpsz;

	*p ='\0';

	while (*q){

		int nSeq =seq(q, cs);

		p -=nSeq;
		::memcpy(p, q, nSeq);
		q +=nSeq;
	}

	return lpac;
}

//ケース変換 (大文字) [for internal use]
LPSTR CString::_toUpper(char* lpac, LPCSTR lpsz, Charset cs){
	assert(lpac && lpsz);

	char*       p =lpac;
	const char* q =lpsz;

	while (*q){

		if (isascii(*q)){
			*p++ =::toupper(*q++);
		}
		else {

			int nSeq =seq(q, cs);

			::memcpy(p, q, nSeq);
			p +=nSeq;
			q +=nSeq;
		}
	}
	*p ='\0';

	return lpac;
}

//ケース変換 (小文字) [for internal use]
LPSTR CString::_toLower(char* lpac, LPCSTR lpsz, Charset cs){
	assert(lpac && lpsz);

	char*       p =lpac;
	const char* q =lpsz;

	while (*q){

		if (isascii(*q)){
			*p++ =tolower(*q++);
		}
		else {

			int nSeq =seq(q, cs);

			::memcpy(p, q, nSeq);
			p +=nSeq;
			q +=nSeq;
		}
	}
	*p ='\0';

	return lpac;
}

//トリミング [for internal use]
LPSTR CString::_trim(int* lpnLen, LPCSTR lpsz, Charset cs){
	assert(lpnLen && lpsz);

	const char* p =lpsz;

	while (*p && isspace(*p)) ++p;

	const char* lpcBegin =p;
	const char* q =p;

	while (*p){
		if (!isspace(*p)){
			q =p;
		}
		p++;
	}
	q++;

	const char* lpcEnd =q;

	//----------------------------------------------------------

	int   nLen =lpcEnd - lpcBegin;
	char* lpac =new char [nLen + 1];
	assert(lpac);

	::memcpy(lpac, lpcBegin, nLen);
	lpac[nLen] ='\0';

	*lpnLen =nLen;

	return lpac;
}

//タブ化 [for internal use]
LPSTR CString::_entab(int* lpnLen, LPCSTR lpsz, int nStep, Charset cs){
	assert(lpnLen && lpsz && nStep >= 0);

	int   nLen;
	char* lpac;

	const char* p =lpsz;

	if (nStep){

		int nCount =0;

		while (*p){

			if (*p == '\t')
				nCount +=nStep - (nCount % nStep);
			else if (*p == ' ')
				++nCount;
			else 
				break;

			++p;
		}

		int nTabs   =nCount / nStep;
		int nSpaces =nCount - nStep*nTabs;
		int nRemain =::strlen(p);

		nLen =nTabs + nSpaces + nRemain;
		lpac =new char [nLen + 1];
		assert(lpac);

		char* q =lpac;

		::memset(q, '\t', nTabs);
		q +=nTabs;
		::memset(q, ' ', nSpaces);
		q +=nSpaces;
		::memcpy(q, p, nRemain + 1);
	}
	else {

		while (*p){
			if (*p != '\t' && *p != ' ') break;
			++p;
		}

		nLen =::strlen(p);
		lpac =new char [nLen + 1];
		assert(lpac);

		::memcpy(lpac, p, nLen + 1);
	}

	*lpnLen =nLen;
		
	return lpac;
}

//タブ解除 [for internal use]
LPSTR CString::_detab(int* lpnLen, LPCSTR lpsz, int nStep, Charset cs){
	assert(lpnLen && lpsz && nStep >= 0);

	int   nLen;
	char* lpac;

	const char* p =lpsz;

	if (nStep){

		int nCount =0;

		while (*p){

			if (*p == '\t')
				nCount +=nStep - (nCount % nStep);
			else if (*p == ' ')
				++nCount;
			else 
				break;

			++p;
		}

		int nRemain =::strlen(p);

		nLen =nCount + nRemain;
		lpac =new char [nLen + 1];
		assert(lpac);

		::memset(lpac, ' ', nCount);
		::memcpy(lpac + nCount, p, nRemain + 1);
	}
	else {

		while (*p){
			if (*p != '\t' && *p != ' ') break;
			++p;
		}

		nLen =::strlen(p);
		lpac =new char [nLen + 1];
		assert(lpac);

		::memcpy(lpac, p, nLen + 1);
	}

	*lpnLen =nLen;
		
	return lpac;
}


/* I/O utility -------------------------------------------------------------- */

//ファイル入力 (１行) [for internal use]
LPSTR CString::_readLine(int* lpnLen, int* lpnExitCode, FILE* fp, Charset cs){
	assert(lpnLen && lpnExitCode && fp);

	//primary buffer
	int  nSize1 =0;
	char acBuf1[BUFFER_SWAP];

	//secondary buffer
	int   nSize2   =0;		
	char* lpacBuf2 =NULL;

	int nCode;

	for (;;){

		nCode =::fgetc(fp);
		if (nCode == EOF) goto __EXIT;

		char c =(char)nCode;
		if (!c || c == '\n') goto __EXIT;

		int nSeq =seq(&c, cs);

		if (nSize1 + nSeq >= BUFFER_SWAP){

			int   nSize =nSize2 + nSize1;
			char* lpac  =new char [nSize];
			assert(lpac);

			::memcpy(lpac,          lpacBuf2, nSize2);
			::memcpy(lpac + nSize2, acBuf1,   nSize1);

			delete [] lpacBuf2;

			nSize2   =nSize;
			lpacBuf2 =lpac;

			//clear the primary buffer
			nSize1 =0;
		}

		acBuf1[nSize1] =c;

		int i;
		for (i=1; i<nSeq; ++i){

			nCode =::fgetc(fp);
			if (nCode == EOF) goto __ERROR;

			char c =(char)nCode;
			if (!c || c == '\n') goto __ERROR;

			acBuf1[nSize1 + i] =c;
		}

		nSize1 +=nSeq;
	}

	//----------------------------------------------------------
__EXIT:
	{
		int nLen =nSize2 + nSize1;

		char* lpac = new char [nLen + 1];
		assert(lpac);

		::memcpy(lpac,          lpacBuf2, nSize2);
		::memcpy(lpac + nSize2, acBuf1,   nSize1);
		lpac[nLen] ='\0';

		delete [] lpacBuf2;

		*lpnLen      =nLen;
		*lpnExitCode =nCode;

		return lpac;
	}

	//----------------------------------------------------------
__ERROR:

	return NULL;
}


//[EOF]
