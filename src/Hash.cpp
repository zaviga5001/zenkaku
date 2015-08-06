////////////////////////////////////////////////////////////////////////////////
//
//	HashFunc.cpp (last update: Jan 29, 2005)
//


#include "Hash.h"
#include <string.h>


////////////////////////////////////////////////////////////////////////////////
//integer

//ハッシュ関数 (char)
int Hash(const char& cKey){
	return cKey;
}

//ハッシュ関数 (short)
int Hash(const short& sKey){
	return sKey;
}

//ハッシュ関数 (long)
int Hash(const long& lKey){
	return (lKey >= 0) ? lKey : lKey^0xFFFFFFFF;
}

//ハッシュ関数 (int)
int Hash(const int& nKey){
	return (nKey >= 0) ? nKey : nKey^0xFFFFFFFF;
}


////////////////////////////////////////////////////////////////////////////////
//integer (unsigned)

//ハッシュ関数 (unsigned char)
int Hash(const unsigned char& byKey){
	return byKey;
}

//ハッシュ関数 (unsigned short)
int Hash(const unsigned short& usKey){
	return usKey;
}

//ハッシュ関数 (unsigned long)
int Hash(const unsigned long& lKey){
	return (lKey & 0x80000000) ? lKey^0xFFFFFFFF : lKey;
}

//ハッシュ関数 (unsigned int)
int Hash(const unsigned int& uKey){
	return (uKey & 0x80000000) ? uKey^0xFFFFFFFF : uKey;
}


////////////////////////////////////////////////////////////////////////////////
//boolean

//ハッシュ関数 (bool)
int Hash(const bool& bKey){
	return (bKey) ? 1 : 0;
}


////////////////////////////////////////////////////////////////////////////////
//floating point

//ハッシュ関数 (float)
int Hash(const float& fKey){

	unsigned long ul =*(unsigned long*)&fKey;
	if (ul & 0x80000000) ul ^=0xFFFFFFFF;

	return (int)ul;
}

//ハッシュ関数 (double)
int Hash(const double& dKey){

	unsigned long aul[2];
	::memcpy(aul, &dKey, sizeof(double));

	unsigned long ul =aul[0]^aul[1];
	if (ul & 0x80000000) ul ^=0xFFFFFFFF;

	return (int)ul;
}


////////////////////////////////////////////////////////////////////////////////
//pointer

//ハッシュ関数 (void*)
int Hash(void * const & lpvKey){

	unsigned long ul =(unsigned long)lpvKey;

	return ul & 0x80000000 ? ul^0xFFFFFFFF : ul;
}

//ハッシュ関数 (const void*)
int Hash(const void * const & lpvKey){

	unsigned long ul =(unsigned long)lpvKey;

	return ul & 0x80000000 ? ul^0xFFFFFFFF : ul;
}


//[EOF]
