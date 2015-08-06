////////////////////////////////////////////////////////////////////////////////
//
//	LibTest: CString.cpp (last update: Jan 30, 2005)
//


#include "CString.h"

//ά���ѥޥ���
#define STRING	    const CString&
#define NULL_STRING CString()


////////////////////////////////////////////////////////////////////////////////
//construction

//���󥹥ȥ饯��
CString::CString(STRING s){

	if (s.m_lpsz){

		int   nLen =s.m_nLen;
		char* lpac =new char [nLen + 1];
		assert(lpac);

		::memcpy(lpac, s.m_lpsz, nLen + 1);

		m_nLen =nLen;
		m_lpsz =lpac;	
	}
	else {
		m_nLen =0;
		m_lpsz =NULL;	
	}
}

//���󥹥ȥ饯��
CString::CString(LPCSTR lpsz){

	if (lpsz){

		int   nLen =::strlen(lpsz);
		char* lpac =new char [nLen + 1];
		assert(lpac);

		::memcpy(lpac, lpsz, nLen + 1);

		m_nLen =nLen;
		m_lpsz =lpac;	
	}
	else {
		m_nLen =0;
		m_lpsz =NULL;	
	}
}

//�ǥ��ȥ饯��
CString::~CString(){
	delete [] m_lpsz;
}


////////////////////////////////////////////////////////////////////////////////
//operator

//���� (1)
CString& CString::operator = (STRING s){

	LPSTR lpszPrev =m_lpsz;

	if (s.m_lpsz){

		int   nLen =s.m_nLen;
		char* lpac =new char [nLen + 1];
		assert(lpac);

		::memcpy(lpac, s.m_lpsz, nLen + 1);

		m_nLen =nLen;
		m_lpsz =lpac;	
	}
	else {
		m_nLen =0;
		m_lpsz =NULL;	
	}

	delete [] lpszPrev;

	return *this;
}

//���� (2)
CString& CString::operator = (LPCSTR lpsz){

	LPSTR lpszPrev =m_lpsz;

	if (lpsz){

		int   nLen =::strlen(lpsz);
		char* lpac =new char [nLen + 1];
		assert(lpac);

		::memcpy(lpac, lpsz, nLen + 1);

		m_nLen =nLen;
		m_lpsz =lpac;	
	}
	else {
		m_nLen =0;
		m_lpsz =NULL;	
	}

	delete [] lpszPrev;

	return *this;
}

//�û����� (1)
CString& CString::operator += (STRING s){

	LPSTR  lpsz1 =m_lpsz;
	LPCSTR lpsz2 =s.m_lpsz;

	if (lpsz1){

		if (lpsz2){

			int nLen1 =m_nLen;
			int nLen2 =s.m_nLen;

			int   nLen =nLen1 + nLen2;
			char* lpac =new char [nLen + 1];
			assert(lpac);

			::memcpy(lpac,         lpsz1, nLen1);
			::memcpy(lpac + nLen1, lpsz2, nLen2 + 1);

			m_nLen =nLen;
			m_lpsz =lpac;

			delete [] lpsz1;
		}
	}
	else {

		if (lpsz2){

			int   nLen =s.m_nLen;
			char* lpac = new char [nLen + 1];
			assert(lpac);

			::memcpy(lpac, lpsz2, nLen +1);

			m_nLen =nLen;
			m_lpsz =lpac;		
		}
		else {
			m_nLen =0;
			m_lpsz =NULL;
		}
	}

	return *this;
}

//�û����� (1)
CString& CString::operator += (LPCSTR lpsz2){

	LPSTR lpsz1 =m_lpsz;

	if (lpsz1){

		if (lpsz2){

			int nLen1 =m_nLen;
			int nLen2 =::strlen(lpsz2);

			int   nLen =nLen1 + nLen2;
			char* lpac =new char [nLen + 1];
			assert(lpac);

			::memcpy(lpac,         lpsz1, nLen1);
			::memcpy(lpac + nLen1, lpsz2, nLen2 + 1);

			m_nLen =nLen;
			m_lpsz =lpac;

			delete [] lpsz1;
		}
	}
	else {

		if (lpsz2){

			int   nLen =::strlen(lpsz2);
			char* lpac = new char [nLen + 1];
			assert(lpac);

			::memcpy(lpac, lpsz2, nLen +1);

			m_nLen =nLen;
			m_lpsz =lpac;		
		}
		else {
			m_nLen =0;
			m_lpsz =NULL;
		}
	}

	return *this;
}


////////////////////////////////////////////////////////////////////////////////
//substring

//��ʬʸ����μ��� (1)
CString CString::Sub(int nBegin, int nEnd) const {

	if (!m_lpsz) return NULL_STRING;

	if (nBegin < 0){
		nEnd +=nBegin;
		nBegin =0;
	}

	if (nEnd > m_nLen) nEnd =m_nLen;

	return (nBegin <= nEnd) ? _sub(m_lpsz, nBegin, nEnd) : NULL_STRING;
}

//��ʬʸ����μ��� (2)
CString CString::Sub(int nBegin) const {

	if (!m_lpsz) return NULL_STRING;

	int nEnd =m_nLen;

	if (nBegin < 0){
		nEnd +=nBegin;
		nBegin =0;			
	}

	if (nEnd > m_nLen) nEnd =m_nLen;

	return (nBegin <= nEnd) ? _sub(m_lpsz, nBegin, nEnd) : NULL_STRING;
}

//����ʬʸ����μ���
CString CString::Left(int nLen) const {

	if (!m_lpsz || nLen < 0) return NULL_STRING;

	return _sub(m_lpsz, 0, (nLen <= m_nLen) ? nLen : m_nLen);
}

//����ʬʸ����μ���
CString CString::Right(int nLen) const {

	if (!m_lpsz || nLen < 0) return NULL_STRING;

	return _sub(m_lpsz, (nLen <= m_nLen) ? m_nLen - nLen : 0, m_nLen);
}


/* search & replacement ----------------------------------------------------- */

//�ѥ����󸡺� (1)
LPCSTR CString::Search(STRING s, UINT uFlags, Charset cs) const {
	return (m_lpsz && s.m_lpsz) ? _search(m_nLen, m_lpsz, s.m_nLen, s.m_lpsz, uFlags, cs) : NULL;
}

//�ѥ����󸡺� (2)
LPCSTR CString::Search(LPCSTR lpsz, UINT uFlags, Charset cs) const {
	return (m_lpsz && lpsz) ? _search(m_nLen, m_lpsz, ::strlen(lpsz), lpsz, uFlags, cs) : NULL;
}

//�ѥ����󸡺� (����ǥ���: 1)
int CString::Find(LPCSTR lpsz, UINT uFlags, Charset cs) const {

	if (!m_lpsz || !lpsz) return NOT_FOUND;

	LPCSTR p =_search(m_nLen, m_lpsz, ::strlen(lpsz), lpsz, uFlags, cs);

	return (p) ? p - m_lpsz : NOT_FOUND;
}

//�ѥ����󸡺� (����ǥ���: 2)
int CString::Find(STRING s, UINT uFlags, Charset cs) const {

	if (!m_lpsz || !s.m_lpsz) return NOT_FOUND;

	LPCSTR p =_search(m_nLen, m_lpsz, s.m_nLen, s.m_lpsz, uFlags, cs);

	return (p) ? p - m_lpsz : NOT_FOUND;
}

//�ѥ������ִ�
CString CString::Replace(LPCSTR lpsz1, LPCSTR lpsz2, UINT uFlags, Charset cs) const {

	if (!m_lpsz) return NULL_STRING;

	if (lpsz1 && *lpsz1){

		if (!lpsz2) lpsz2 ="";

		int   nLen;
		LPSTR lpsz =_replace(&nLen, m_nLen, m_lpsz, ::strlen(lpsz1), lpsz1, ::strlen(lpsz2), lpsz2, uFlags, cs);

		return CString(nLen, lpsz);
	}
	else {

		int   nLen =m_nLen;
		char* lpac =new char [nLen + 1];
		assert(lpac);

		::memcpy(lpac, m_lpsz, nLen + 1);

		return CString(nLen, lpac);	
	}
}


/* conversion --------------------------------------------------------------- */

//��ʸ���Ѵ�
CString CString::ToUpper(Charset cs) const {

	if (!m_lpsz) return NULL_STRING;

	char* lpac =new char [m_nLen + 1];
	assert(lpac);

	return CString(m_nLen, _toUpper(lpac, m_lpsz, cs));
}

//��ʸ���Ѵ�
CString CString::ToLower(Charset cs) const {

	if (!m_lpsz) return NULL_STRING;

	char* lpac =new char [m_nLen + 1];
	assert(lpac);

	return CString(m_nLen, _toLower(lpac, m_lpsz, cs));
}
	
//ž��
CString CString::Invert(Charset cs) const {

	if (!m_lpsz) return NULL_STRING;

	int   nLen =m_nLen;
	char* lpac =new char [nLen + 1];
	assert(lpac);

	return CString(nLen, _invert(nLen, lpac, m_lpsz, cs));
}

//�ȥ�ߥ�
CString CString::Trim(Charset cs) const {

	if (!m_lpsz) return NULL_STRING;

	int nLen;
	LPSTR lpsz =_trim(&nLen, m_lpsz, cs);

	return CString(nLen, lpsz);
}

//���ֲ�
CString CString::Entab(int nStep, Charset cs) const {

	if (!m_lpsz) return NULL_STRING;

	int nLen;
	LPSTR lpsz =_entab(&nLen, m_lpsz, nStep, cs);

	return CString(nLen, lpsz);
}

//���ֲ��
CString CString::Detab(int nStep, Charset cs) const {

	if (!m_lpsz) return NULL_STRING;

	int nLen;
	LPSTR lpsz =_detab(&nLen, m_lpsz, nStep, cs);

	return CString(nLen, lpsz);
}


////////////////////////////////////////////////////////////////////////////////
//I/O utility

//�ե��������� (����)
int CString::ReadLine(FILE* fp, Charset cs){

	if (fp){

		int nExitCode;

		int nLen;
		LPSTR lpsz =_readLine(&nLen, &nExitCode, fp, cs);

		delete [] m_lpsz;

		if (lpsz){
			m_nLen =nLen;
			m_lpsz =lpsz;
		}
		else {
			m_nLen =0;
			m_lpsz =NULL;
		}

		return nExitCode;
	}
	else {

		delete [] m_lpsz;

		m_lpsz =NULL;
		m_nLen =0;

		return -2;
	}
}

//�ե�������� (1)
int CString::Print(FILE* fp) const {

	if (fp){
		if (m_lpsz)
			return fputs(m_lpsz, fp);
		else
			return 0;
	}
	else
		return EOF;
}

//�ե�������� (2)
int CString::Put(FILE* fp) const {

	if (fp){
		if (m_lpsz){

			int nRes1 =fputs(m_lpsz, fp);
			if (nRes1 == EOF) return EOF;

			int nRes2 =fputc('\n', fp);
			if (nRes2 == EOF) return EOF;

			return nRes1 + nRes2;
		}
		else
			return 0;
	}
	else
		return EOF;
}


////////////////////////////////////////////////////////////////////////////////
//global function

//Ϣ�� (1)
CString operator + (STRING s1, STRING s2){

	if (s1.m_lpsz){
		if (s2.m_lpsz)
			return CString::_add(s1.m_nLen, s1.m_lpsz, s2.m_nLen, s2.m_lpsz);
		else
			return s1;
	}
	else {
		if (s2.m_lpsz)
			return s2;
		else
			return NULL_STRING;
	}
}

//�û� (2)
CString operator + (STRING s1, LPCSTR lpsz2){

	if (s1.m_lpsz){
		if (lpsz2)
			return CString::_add(s1.m_nLen, s1.m_lpsz, ::strlen(lpsz2), lpsz2);
		else
			return s1;
	}
	else {
		if (lpsz2)
			return CString(lpsz2);
		else
			return NULL_STRING;
	}
}

//�û� (3)
CString operator + (LPCSTR lpsz1, STRING s2){

	if (lpsz1){
		if (s2.m_lpsz)
			return CString::_add(::strlen(lpsz1), lpsz1, s2.m_nLen, s2.m_lpsz);
		else
			return CString(lpsz1);
	}
	else {
		if (s2.m_lpsz)
			return s2;
		else
			return NULL_STRING;
	}
}


//[EOF]