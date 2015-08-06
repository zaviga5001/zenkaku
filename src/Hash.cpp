////////////////////////////////////////////////////////////////////////////////
//
//	HashFunc.cpp (last update: Jan 29, 2005)
//


#include "Hash.h"
#include <string.h>


////////////////////////////////////////////////////////////////////////////////
//integer

//�ϥå���ؿ� (char)
int Hash(const char& cKey){
	return cKey;
}

//�ϥå���ؿ� (short)
int Hash(const short& sKey){
	return sKey;
}

//�ϥå���ؿ� (long)
int Hash(const long& lKey){
	return (lKey >= 0) ? lKey : lKey^0xFFFFFFFF;
}

//�ϥå���ؿ� (int)
int Hash(const int& nKey){
	return (nKey >= 0) ? nKey : nKey^0xFFFFFFFF;
}


////////////////////////////////////////////////////////////////////////////////
//integer (unsigned)

//�ϥå���ؿ� (unsigned char)
int Hash(const unsigned char& byKey){
	return byKey;
}

//�ϥå���ؿ� (unsigned short)
int Hash(const unsigned short& usKey){
	return usKey;
}

//�ϥå���ؿ� (unsigned long)
int Hash(const unsigned long& lKey){
	return (lKey & 0x80000000) ? lKey^0xFFFFFFFF : lKey;
}

//�ϥå���ؿ� (unsigned int)
int Hash(const unsigned int& uKey){
	return (uKey & 0x80000000) ? uKey^0xFFFFFFFF : uKey;
}


////////////////////////////////////////////////////////////////////////////////
//boolean

//�ϥå���ؿ� (bool)
int Hash(const bool& bKey){
	return (bKey) ? 1 : 0;
}


////////////////////////////////////////////////////////////////////////////////
//floating point

//�ϥå���ؿ� (float)
int Hash(const float& fKey){

	unsigned long ul =*(unsigned long*)&fKey;
	if (ul & 0x80000000) ul ^=0xFFFFFFFF;

	return (int)ul;
}

//�ϥå���ؿ� (double)
int Hash(const double& dKey){

	unsigned long aul[2];
	::memcpy(aul, &dKey, sizeof(double));

	unsigned long ul =aul[0]^aul[1];
	if (ul & 0x80000000) ul ^=0xFFFFFFFF;

	return (int)ul;
}


////////////////////////////////////////////////////////////////////////////////
//pointer

//�ϥå���ؿ� (void*)
int Hash(void * const & lpvKey){

	unsigned long ul =(unsigned long)lpvKey;

	return ul & 0x80000000 ? ul^0xFFFFFFFF : ul;
}

//�ϥå���ؿ� (const void*)
int Hash(const void * const & lpvKey){

	unsigned long ul =(unsigned long)lpvKey;

	return ul & 0x80000000 ? ul^0xFFFFFFFF : ul;
}


//[EOF]
