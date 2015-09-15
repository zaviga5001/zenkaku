////////////////////////////////////////////////////////////////////////////////
//
//	hash.h (last update: Jan 31, 2005)
//


#ifndef __CHASHFUNC_H__
#define __CHASHFUNC_H__

//integer
int Hash(const char&);
int Hash(const short&);
int Hash(const long&);
int Hash(const int&);

//integer (unsigned)
int Hash(const unsigned char&);
int Hash(const unsigned short&);
int Hash(const unsigned long&);
int Hash(const unsigned int&);

//boolean
int Hash(const bool&);

//floating point
int Hash(const float&);
int Hash(const double&);

//pointer
int Hash(void* const &);
int Hash(const void* const &);

#endif //__CHASHFUNC_H__
//[EOF]